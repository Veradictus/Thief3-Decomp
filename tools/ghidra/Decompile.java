// Prints Ghidra's decompilation of the functions containing the given
// addresses, or of every function that references a given data address when it
// is prefixed with "refs:".
//
//   tools/ghidra_headless.py script tools/ghidra/Decompile.java 0x109b2010 refs:0x10f7af1c
//@category Thief3-Decomp

import java.util.LinkedHashSet;
import java.util.Set;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;

public class Decompile extends GhidraScript {

	private static final int MAX_REFERRERS = 12;

	@Override
	protected void run() throws Exception {
		Set<Function> functions = new LinkedHashSet<>();
		for (String arg : getScriptArgs()) {
			if (arg.startsWith("refs:")) {
				Address target = toAddr(Long.decode(arg.substring(5)));
				int n = 0;
				for (Reference r : getReferencesTo(target)) {
					Function f = getFunctionContaining(r.getFromAddress());
					if (f != null && functions.add(f) && ++n >= MAX_REFERRERS) {
						break;
					}
				}
				println(String.format("%s: %d referencing functions shown", arg, n));
			}
			else {
				Function f = getFunctionContaining(toAddr(Long.decode(arg)));
				if (f == null) {
					println(arg + ": not in a function");
				}
				else {
					functions.add(f);
				}
			}
		}

		DecompInterface decompiler = new DecompInterface();
		decompiler.openProgram(currentProgram);
		try {
			for (Function f : functions) {
				DecompileResults res = decompiler.decompileFunction(f, 60, monitor);
				println("==== " + f.getName() + " @ " + f.getEntryPoint());
				println(res.decompileCompleted() ? res.getDecompiledFunction().getC()
						: "decompile failed: " + res.getErrorMessage());
			}
		}
		finally {
			decompiler.dispose();
		}
	}
}
