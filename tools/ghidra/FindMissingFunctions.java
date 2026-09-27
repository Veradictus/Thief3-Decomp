// Creates functions for .text code that auto-analysis left undefined.
//
// T3Main.exe is MSVC 7.1 /O2 output: every function in the main part of .text
// starts on a 16-byte boundary and is padded with int3 (0xCC). Code that is
// only reachable through vtables or other pointer tables is often missed by
// auto-analysis. Function starts are recovered from three signals:
//   1. pointers in initialised data (.rdata/.data/...) into uncovered .text,
//   2. absolute operands of instructions into uncovered .text (e.g. the
//      __ehhandler$ stubs pushed by SEH prologues, which live in .text$x),
//   3. 16-byte-aligned code that directly follows int3 padding.
// Outside the EH funclet region (.text$x, which the linker places last), a
// referenced address only counts as a function start if it is 16-byte aligned
// after int3 padding: otherwise it is a label inside a function, such as an
// SEH __except handler named by a scope table. Defined data (jump tables) and
// pointer-looking dwords are never treated as code. Repeats until no new
// function is found. Needs write access; the caller re-runs auto-analysis.
//@category Thief3-Decomp

import java.util.ArrayList;
import java.util.List;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressRange;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.address.AddressSetView;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.mem.MemoryAccessException;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.scalar.Scalar;

public class FindMissingFunctions extends GhidraScript {

	private MemoryBlock text;
	private long textStart;
	private long textEnd; // exclusive
	private long funcletStart; // first EH funclet (.text$x); textEnd if none

	@Override
	protected void run() throws Exception {
		text = currentProgram.getMemory().getBlock(".text");
		if (text == null) {
			printerr("no .text block");
			return;
		}
		textStart = text.getStart().getOffset();
		textEnd = text.getEnd().getOffset() + 1;
		funcletStart = textEnd;
		for (Function f : currentProgram.getFunctionManager().getFunctions(text.getStart(), true)) {
			if (f.getName().startsWith("Unwind@")) {
				funcletStart = Math.min(funcletStart, f.getEntryPoint().getOffset());
			}
		}
		println(String.format("EH funclet region (.text$x) starts at %08x", funcletStart));

		println(String.format("before: %d functions, %.2f%% of .text covered",
			currentProgram.getFunctionManager().getFunctionCount(), coverage() * 100));

		int total = 0;
		for (int pass = 1; pass <= 8 && !monitor.isCancelled(); pass++) {
			int fromData = createAt(dataPointerTargets());
			int fromCode = createAt(operandTargets());
			int fromPadding = createAt(paddedStarts());
			int n = fromData + fromCode + fromPadding;
			total += n;
			println(String.format("pass %d: +%d functions (data pointers %d, operands %d, padding %d)",
				pass, n, fromData, fromCode, fromPadding));
			if (n == 0) {
				break;
			}
		}

		println(String.format("after: %d functions (+%d), %.2f%% of .text covered",
			currentProgram.getFunctionManager().getFunctionCount(), total, coverage() * 100));
	}

	private double coverage() {
		AddressSet covered = new AddressSet();
		for (Function f : currentProgram.getFunctionManager().getFunctions(text.getStart(), true)) {
			covered.add(f.getBody().intersectRange(text.getStart(), text.getEnd()));
		}
		long padding = 0;
		AddressSetView gaps = new AddressSet(text.getStart(), text.getEnd()).subtract(covered);
		for (AddressRange r : gaps) {
			if (isPadding(r)) {
				padding += r.getLength();
			}
		}
		return (double) (covered.getNumAddresses() + padding) / text.getSize();
	}

	private boolean isPadding(AddressRange r) {
		try {
			byte[] bytes = getBytes(r.getMinAddress(), (int) r.getLength());
			for (byte b : bytes) {
				if (b != (byte) 0xCC && b != (byte) 0x90) {
					return false;
				}
			}
			return true;
		}
		catch (MemoryAccessException e) {
			return false;
		}
	}

	private boolean inText(long va) {
		return va >= textStart && va < textEnd;
	}

	/** Referenced address that is plausibly a function entry rather than an inner label. */
	private boolean isEntryCandidate(Address a) throws MemoryAccessException {
		long va = a.getOffset();
		if (va >= funcletStart) {
			return isCandidate(a);
		}
		return (va & 15) == 0 && (getByte(toAddr(va - 1)) & 0xff) == 0xCC && isCandidate(a);
	}

	/** True if `a` is uncovered, not defined data, and not inside an instruction. */
	private boolean isCandidate(Address a) {
		if (getFunctionContaining(a) != null) {
			return false;
		}
		Data d = getDataContaining(a);
		if (d != null && d.isDefined()) {
			return false;
		}
		Instruction insn = getInstructionContaining(a);
		if (insn != null && !insn.getAddress().equals(a)) {
			return false;
		}
		try {
			int first = getByte(a) & 0xff;
			if (first == 0xCC || first == 0x00) {
				return false;
			}
			// A dword that points into .text is a jump-table entry, not code.
			long dword = getInt(a) & 0xffffffffL;
			if (inText(dword)) {
				return false;
			}
		}
		catch (MemoryAccessException e) {
			return false;
		}
		return true;
	}

	private List<Address> dataPointerTargets() throws MemoryAccessException {
		List<Address> out = new ArrayList<>();
		for (MemoryBlock b : currentProgram.getMemory().getBlocks()) {
			if (b.isExecute() || !b.isInitialized() || b.getName().equals(".rsrc") ||
				b.getName().equals("Headers") || b.getStart().getOffset() < textStart) {
				continue;
			}
			byte[] bytes = new byte[(int) b.getSize()];
			b.getBytes(b.getStart(), bytes);
			for (int off = 0; off + 4 <= bytes.length; off += 4) {
				long v = (bytes[off] & 0xffL) | (bytes[off + 1] & 0xffL) << 8 |
					(bytes[off + 2] & 0xffL) << 16 | (bytes[off + 3] & 0xffL) << 24;
				if (inText(v)) {
					Address a = toAddr(v);
					if (isEntryCandidate(a)) {
						out.add(a);
					}
				}
			}
		}
		return out;
	}

	private List<Address> operandTargets() throws MemoryAccessException {
		List<Address> out = new ArrayList<>();
		InstructionIterator it = currentProgram.getListing()
				.getInstructions(new AddressSet(text.getStart(), text.getEnd()), true);
		while (it.hasNext() && !monitor.isCancelled()) {
			Instruction insn = it.next();
			if (insn.getFlowType().isCall() || insn.getFlowType().isJump()) {
				continue; // direct flow targets are already followed by analysis
			}
			for (int op = 0; op < insn.getNumOperands(); op++) {
				for (Object o : insn.getOpObjects(op)) {
					long v;
					if (o instanceof Scalar s) {
						v = s.getUnsignedValue();
					}
					else if (o instanceof Address a) {
						v = a.getOffset();
					}
					else {
						continue;
					}
					if (inText(v)) {
						Address a = toAddr(v);
						if (isEntryCandidate(a)) {
							out.add(a);
						}
					}
				}
			}
		}
		return out;
	}

	private List<Address> paddedStarts() throws MemoryAccessException {
		List<Address> out = new ArrayList<>();
		AddressSet covered = new AddressSet();
		for (Function f : currentProgram.getFunctionManager().getFunctions(text.getStart(), true)) {
			covered.add(f.getBody());
		}
		AddressSetView gaps = new AddressSet(text.getStart(), text.getEnd()).subtract(covered);
		for (AddressRange r : gaps) {
			long lo = r.getMinAddress().getOffset();
			long hi = r.getMaxAddress().getOffset();
			for (long va = (lo + 15) & ~15L; va <= hi; va += 16) {
				Address a = toAddr(va);
				if ((getByte(toAddr(va - 1)) & 0xff) == 0xCC && isCandidate(a)) {
					out.add(a);
				}
			}
		}
		return out;
	}

	private int createAt(List<Address> starts) {
		int created = 0;
		for (Address a : starts) {
			if (monitor.isCancelled()) {
				break;
			}
			if (!isCandidate(a)) {
				continue; // covered by a function created earlier in this batch
			}
			if (getInstructionAt(a) == null && !disassemble(a)) {
				continue;
			}
			if (getInstructionAt(a) != null && createFunction(a, null) != null) {
				created++;
			}
		}
		return created;
	}
}
