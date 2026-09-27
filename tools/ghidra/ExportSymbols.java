// Writes a dtk-style symbols.txt from the analysed T3Main.exe:
//
//   <name> = <section>:0x<ADDRESS>; // type:function size:0x<N>
//   <name> = <section>:0x<ADDRESS>; // type:object size:0x<N>
//
// Functions: every non-external function. The extent runs from the entry point
// to the next function, minus int3 padding, so switch tables and EH-only
// handler blocks stay with their function. Names prefer a mangled MSVC label
// (from Function ID) over Ghidra's demangled form; unnamed functions keep
// Ghidra's FUN_xxxxxxxx.
// Objects: data defined inside .text (switch tables), import address table
// slots named __imp_<coff name> exactly as MSVC-compiled code references them
// (e.g. __imp__RegOpenKeyA@12), and data labels that analysis or a user named.
//
// Usage (headless): tools/ghidra_headless.py export [-o path]
//@category Thief3-Decomp

import java.io.File;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.TreeMap;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressRange;
import ghidra.program.model.address.AddressRangeIterator;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.mem.MemoryAccessException;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.ExternalLocation;
import ghidra.program.model.symbol.ExternalReference;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;

public class ExportSymbols extends GhidraScript {

	private record Entry(long address, String name, String section, String type, long size) {}

	private final TreeMap<Long, Entry> entries = new TreeMap<>();
	private final Set<String> usedNames = new HashSet<>();

	@Override
	protected void run() throws Exception {
		String[] args = getScriptArgs();
		File out = args.length > 0 ? new File(args[0]) : askFile("symbols.txt to write", "Export");

		exportFunctions();
		exportImports();
		exportDataLabels();

		try (PrintWriter w = new PrintWriter(out, StandardCharsets.UTF_8)) {
			w.print("# " + currentProgram.getName() + " symbols, exported by tools/ghidra/ExportSymbols.java\n");
			w.print("# <name> = <section>:0x<address>; // type:<function|object> size:0x<bytes>\n");
			for (Entry e : entries.values()) {
				w.printf("%s = %s:0x%08X; // type:%s size:0x%X\n", e.name, e.section, e.address,
					e.type, e.size);
			}
		}
		println("wrote " + entries.size() + " symbols to " + out);
	}

	/**
	 * C++ catch blocks: Ghidra makes them functions, but MSVC x86 emits them inline
	 * in the function that owns the try, so they stay part of that function.
	 */
	private static boolean isCatchBlock(Function f) {
		String n = f.getName();
		return n.startsWith("Catch@") || n.startsWith("Catch_All@");
	}

	private void exportFunctions() throws MemoryAccessException {
		List<Function> functions = new ArrayList<>();
		List<Function> catchBlocks = new ArrayList<>();
		for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
			MemoryBlock block = getMemoryBlock(f.getEntryPoint());
			if (!f.isExternal() && block != null && block.isExecute()) {
				(isCatchBlock(f) ? catchBlocks : functions).add(f);
			}
		}
		// Defined data inside code blocks: switch jump tables and their byte index tables.
		TreeMap<Long, Data> codeData = new TreeMap<>();
		for (MemoryBlock block : currentProgram.getMemory().getBlocks()) {
			if (block.isExecute()) {
				DataIterator it = currentProgram.getListing()
						.getDefinedData(new AddressSet(block.getStart(), block.getEnd()), true);
				while (it.hasNext()) {
					Data d = it.next();
					codeData.put(d.getAddress().getOffset(), d);
				}
			}
		}
		for (int i = 0; i < functions.size(); i++) {
			Function f = functions.get(i);
			long start = f.getEntryPoint().getOffset();
			MemoryBlock block = getMemoryBlock(f.getEntryPoint());
			Function next = i + 1 < functions.size() ? functions.get(i + 1) : null;
			boolean hasNext = next != null && block.contains(next.getEntryPoint());
			long limit = hasNext ? next.getEntryPoint().getOffset() : block.getEnd().getOffset() + 1;
			long end = bodyEnd(f, limit);
			for (Function c : catchBlocks) {
				long cs = c.getEntryPoint().getOffset();
				if (cs > start && cs < limit) {
					end = Math.max(end, bodyEnd(c, limit));
				}
			}
			// Everything up to the next function belongs to this one (switch tables,
			// handler blocks only reachable through EH tables), except the linker's
			// int3 padding. The block's last function ends at its body: after it
			// comes only the section's zero fill.
			if (hasNext) {
				end = Math.max(end, trimPadding(limit, end));
			}
			if (end <= start) {
				continue;
			}
			add(start, functionName(f), "function", end - start);
		}
		for (Data d : codeData.values()) {
			Symbol s = d.getPrimarySymbol();
			String name = s != null ? s.getName() : String.format("DAT_%08x", d.getAddress().getOffset());
			add(d.getAddress().getOffset(), name, "object", d.getLength());
		}
	}

	/** `end` moved back over trailing int3 (0xCC) bytes, but not below `floor`. */
	private long trimPadding(long end, long floor) throws MemoryAccessException {
		while (end > floor && (getByte(toAddr(end - 1)) & 0xff) == 0xCC) {
			end--;
		}
		return end;
	}

	/**
	 * End (exclusive) of the body ranges between the entry point and `limit` (the
	 * next function). Gaps inside, such as an inline switch table, are kept: delink
	 * treats switch tables as data. Body pieces past `limit` (shared tails) are not.
	 */
	private long bodyEnd(Function f, long limit) {
		long end = f.getEntryPoint().getOffset();
		AddressRangeIterator it = f.getBody().getAddressRanges(f.getEntryPoint(), true);
		while (it.hasNext()) {
			AddressRange r = it.next();
			if (r.getMinAddress().getOffset() >= limit) {
				break;
			}
			end = Math.max(end, Math.min(r.getMaxAddress().getOffset() + 1, limit));
		}
		return end;
	}

	/**
	 * The name to export for a function: its mangled MSVC label if one exists;
	 * for an unrenamed jmp-stub thunk, the target's COFF name if the target is
	 * an import, else a generic FUN_ name; otherwise Ghidra's own name
	 * (demangled, with any "FID_conflict:" prefix from Function ID stripped).
	 */
	private String functionName(Function f) {
		String mangled = mangledLabel(f.getEntryPoint());
		if (mangled != null) {
			return mangled;
		}
		if (f.isThunk()) {
			Function target = f.getThunkedFunction(true);
			if (target != null && target.isExternal()) {
				return coffName(target.getName(), target); // import library stub
			}
			// Ghidra names a jmp stub after its target; keep the real name for the target.
			if (f.getSymbol().getSource() != SourceType.USER_DEFINED) {
				return String.format("FUN_%08x", f.getEntryPoint().getOffset());
			}
		}
		String name = f.getName(true);
		if (name.startsWith("FID_conflict:")) {
			name = name.substring("FID_conflict:".length());
		}
		return name;
	}

	/** The first mangled (MSVC "?"-decorated) symbol at `a`, Function ID's or the user's, if any. */
	private String mangledLabel(Address a) {
		for (Symbol s : currentProgram.getSymbolTable().getSymbols(a)) {
			if (s.getName().startsWith("?")) {
				return s.getName();
			}
		}
		return null;
	}

	/** COFF symbol name MSVC gives a C function: _name, _name@N (stdcall), @name@N (fastcall). */
	private static String coffName(String name, Function f) {
		String cc = f.getCallingConventionName();
		int purge = f.getStackPurgeSize();
		boolean purgeKnown = purge >= 0 && purge != Function.UNKNOWN_STACK_DEPTH_CHANGE &&
			purge != Function.INVALID_STACK_DEPTH_CHANGE;
		if ("__cdecl".equals(cc) || !purgeKnown) {
			return "_" + name;
		}
		if ("__fastcall".equals(cc)) {
			return "@" + name + "@" + purge;
		}
		return "_" + name + "@" + purge;
	}

	/** Names import table slots __imp_<coff name>, from data references Ghidra resolved externally. */
	private void exportImports() {
		DataIterator it = currentProgram.getListing().getDefinedData(true);
		while (it.hasNext() && !monitor.isCancelled()) {
			Data d = it.next();
			MemoryBlock block = getMemoryBlock(d.getAddress());
			if (block == null || block.isExecute()) {
				continue;
			}
			for (Reference r : d.getReferencesFrom()) {
				if (!(r instanceof ExternalReference ext)) {
					continue;
				}
				ExternalLocation loc = ext.getExternalLocation();
				Function target = loc.getFunction();
				String label = loc.getLabel();
				String name = target != null ? "__imp_" + coffName(label, target) : "__imp__" + label;
				add(d.getAddress().getOffset(), name, "object", d.getLength());
			}
		}
	}

	private void exportDataLabels() {
		SymbolIterator it = currentProgram.getSymbolTable().getAllSymbols(false);
		while (it.hasNext() && !monitor.isCancelled()) {
			Symbol s = it.next();
			if (s.getSource() == SourceType.DEFAULT || s.isExternal() || !s.isPrimary() ||
				s.getAddress().getAddressSpace().isExternalSpace()) {
				continue;
			}
			MemoryBlock block = getMemoryBlock(s.getAddress());
			// Not real code/data: executable blocks (functions are exported separately),
			// PE headers, resources, and Ghidra's own internal blocks.
			if (block == null || block.isExecute() || block.getName().equals("Headers") ||
				block.getName().equals(".rsrc") || block.getName().equals("tdb")) {
				continue;
			}
			long address = s.getAddress().getOffset();
			if (entries.containsKey(address)) {
				continue;
			}
			String name = mangledLabel(s.getAddress());
			if (name == null) {
				name = s.getName(true);
			}
			Data d = getDataAt(s.getAddress());
			add(address, name, "object", d != null ? d.getLength() : 0);
		}
	}

	/** Records one address's entry (first writer wins), disambiguating a name already used elsewhere. */
	private void add(long address, String name, String type, long size) {
		if (entries.containsKey(address)) {
			return;
		}
		name = name.replaceAll("\\s+", "_");
		if (!usedNames.add(name)) {
			name = String.format("%s_%08x", name, address);
			usedNames.add(name);
		}
		MemoryBlock block = getMemoryBlock(toAddr(address));
		entries.put(address, new Entry(address, name, block.getName(), type, size));
	}
}
