// Applies the names recorded in symbols.txt to the analysed T3Main.exe, so
// that symbols.txt stays the name database: edit it, run
// `tools/ghidra_headless.py names`, and decompiles show the names. Bootstrap
// runs this before exporting, so names survive a rebuild of the database.
//
// A name is applied where Ghidra has only a default name (FUN_..., DAT_...), or
// a different user-defined one. Names from analysis (Function ID, demangled
// imports) are left alone. "Class::Method" names go into namespace Class.
// Objects get data of their recorded size: a dword when nothing is defined and
// the size is 4, otherwise an array of the element type already there (bytes
// when none), so exporting gives back the same size.
//
// Usage (headless): tools/ghidra_headless.py names [-i path]
//@category Thief3-Decomp

import java.io.File;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.util.Arrays;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import ghidra.app.script.GhidraScript;
import ghidra.app.util.NamespaceUtils;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.ArrayDataType;
import ghidra.program.model.data.DataType;
import ghidra.program.model.data.Undefined1DataType;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Namespace;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;

public class ImportNames extends GhidraScript {

	// Groups: 1 name, 2 address (hex), 3 type (function|object|label, optional), 4 size (hex, optional).
	private static final Pattern LINE = Pattern.compile(
		"^(\\S+) = [^:\\s]+:0x([0-9A-Fa-f]+);\\s*(?://.*?type:(\\w+))?(?:.*?size:0x([0-9A-Fa-f]+))?.*$");
	private static final Pattern DEFAULT_NAME = Pattern.compile(
		"^(FUN|DAT|LAB|PTR|SUB|OFF|EXT|UNK|switchdataD|caseD|thunk_FUN)_[0-9A-Fa-f]+.*$|^__imp_.*$");

	private int applied;

	@Override
	protected void run() throws Exception {
		String[] args = getScriptArgs();
		File in = args.length > 0 ? new File(args[0]) : askFile("symbols.txt to read", "Import");
		for (String line : Files.readAllLines(in.toPath(), StandardCharsets.UTF_8)) {
			Matcher m = LINE.matcher(line.trim());
			if (!m.matches() || DEFAULT_NAME.matcher(m.group(1)).matches()) {
				continue;
			}
			Address address = toAddr(Long.parseLong(m.group(2), 16));
			String type = m.group(3) != null ? m.group(3) : "label";
			long size = m.group(4) != null ? Long.parseLong(m.group(4), 16) : 0;
			apply(address, m.group(1), type, size);
		}
		println("applied " + applied + " names from " + in);
	}

	private void apply(Address address, String name, String type, long size) throws Exception {
		if (type.equals("object")) {
			defineData(address, size);
		}
		if (getFunctionAt(address) != null && getFunctionAt(address).isThunk()) {
			return; // import stubs: export derives their names from the import
		}
		Symbol current = type.equals("function") && getFunctionAt(address) != null
				? getFunctionAt(address).getSymbol()
				: currentProgram.getSymbolTable().getPrimarySymbol(address);
		if (current != null && current.getName(true).equals(name)) {
			return;
		}
		if (current != null && current.getSource() != SourceType.DEFAULT &&
			current.getSource() != SourceType.USER_DEFINED) {
			return; // analysis found a real name; symbols.txt carries it already
		}
		if (name.startsWith("?")) { // MSVC decorated name: a label, as Function ID adds them
			createLabel(address, name, false, SourceType.USER_DEFINED);
			applied++;
			return;
		}
		List<String> parts = Arrays.asList(name.split("::"));
		String simple = parts.get(parts.size() - 1);
		Namespace ns = parts.size() > 1
				? NamespaceUtils.createNamespaceHierarchy(String.join("::", parts.subList(0, parts.size() - 1)),
					null, currentProgram, SourceType.USER_DEFINED)
				: currentProgram.getGlobalNamespace();
		Function f = getFunctionAt(address);
		if (type.equals("function") && f != null) {
			f.getSymbol().setNameAndNamespace(simple, ns, SourceType.USER_DEFINED);
		}
		else {
			createLabel(address, simple, ns, true, SourceType.USER_DEFINED);
		}
		println(String.format("%s = %s", address, name));
		applied++;
	}

	private void defineData(Address address, long size) throws Exception {
		Data d = getDataAt(address);
		boolean defined = d != null && d.isDefined();
		if (size <= 0 || (defined && d.getLength() >= size)) {
			return;
		}
		if (!defined && size == 4) {
			createDWord(address);
			return;
		}
		DataType element = defined && size % d.getLength() == 0 ? d.getDataType() : Undefined1DataType.dataType;
		clearListing(address, address.add(size - 1));
		createData(address, new ArrayDataType(element, (int) (size / element.getLength()), element.getLength()));
	}
}
