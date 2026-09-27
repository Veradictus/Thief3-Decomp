// Prints the disassembly of the functions containing the given addresses, or
// of `count` instructions from an address given as "<addr>+<count>".
//
//   tools/ghidra_headless.py script tools/ghidra/Disassemble.java 0x10a51010 0x10a510c0+20
//@category Thief3-Decomp

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;

public class Disassemble extends GhidraScript {

	@Override
	protected void run() throws Exception {
		for (String arg : getScriptArgs()) {
			int plus = arg.indexOf('+');
			if (plus >= 0) {
				Address start = toAddr(Long.decode(arg.substring(0, plus)));
				int count = Integer.parseInt(arg.substring(plus + 1));
				println("==== " + start + " (" + count + " instructions)");
				Instruction insn = getInstructionContaining(start);
				for (int i = 0; insn != null && i < count; ++i, insn = insn.getNext()) {
					print(insn);
				}
				continue;
			}
			Function f = getFunctionContaining(toAddr(Long.decode(arg)));
			if (f == null) {
				println(arg + ": not in a function");
				continue;
			}
			println("==== " + f.getName() + " @ " + f.getEntryPoint());
			for (Instruction insn : currentProgram.getListing().getInstructions(f.getBody(), true)) {
				print(insn);
			}
		}
	}

	/** Prints one instruction, annotated with the called function's name if it's a call. */
	private void print(Instruction insn) {
		Function callee = null;
		String note = "";
		for (var ref : insn.getReferencesFrom()) {
			if (ref.getReferenceType().isCall()) {
				callee = getFunctionAt(ref.getToAddress());
			}
		}
		if (callee != null) {
			note = "  ; " + callee.getName();
		}
		println(String.format("%s  %s%s", insn.getAddress(), insn, note));
	}
}
