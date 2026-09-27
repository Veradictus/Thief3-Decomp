// Prints Ghidra's decompilation of the functions containing the given
// addresses, or of every function that references a given data address when it
// is prefixed with "refs:". With "out:<dir>", each function is written to
// <dir>/<ENTRY>.c instead (tools/agent/context.py caches them that way).
//
//   tools/ghidra_headless.py script tools/ghidra/Decompile.java 0x109b2010 refs:0x10f7af1c
//@category Thief3-Decomp

import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
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
		String outDir = null;
		for (String arg : getScriptArgs()) {
			if (arg.startsWith("out:")) {
				outDir = arg.substring(4);
			}
			else if (arg.startsWith("refs:")) {
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
				String header = "==== " + f.getName() + " @ " + f.getEntryPoint();
				String text = res.decompileCompleted() ? res.getDecompiledFunction().getC()
						: "decompile failed: " + res.getErrorMessage();
				if (outDir == null) {
					println(header);
					println(text);
					continue;
				}
				java.nio.file.Path file = java.nio.file.Path.of(outDir,
					String.format("%08X.c", f.getEntryPoint().getOffset()));
				Files.createDirectories(file.getParent());
				Files.writeString(file, "// " + header + "\n" + text, StandardCharsets.UTF_8);
				println("wrote " + file);
			}
		}
		finally {
			decompiler.dispose();
		}
	}
}
