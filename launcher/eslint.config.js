// ESLint flat config: typed TypeScript rules for .ts and .svelte files, plus
// Svelte's own rules. Formatting is Prettier's job, not ESLint's.
import js from "@eslint/js";
import { defineConfig } from "eslint/config";
import svelte from "eslint-plugin-svelte";
import globals from "globals";
import ts from "typescript-eslint";
import svelteConfig from "./svelte.config.js";

export default defineConfig(
  { ignores: ["dist/", "src-tauri/", "node_modules/", ".yarn/"] },
  js.configs.recommended,
  ts.configs.strictTypeChecked,
  ts.configs.stylisticTypeChecked,
  svelte.configs.recommended,
  {
    languageOptions: {
      globals: { ...globals.browser },
      parserOptions: {
        projectService: { allowDefaultProject: ["*.config.js"] },
        tsconfigRootDir: import.meta.dirname,
        extraFileExtensions: [".svelte"],
      },
    },
    rules: {
      // Tauri command errors arrive as strings; `${e}` in messages is fine.
      "@typescript-eslint/restrict-template-expressions": ["error", { allowNumber: true }],
    },
  },
  {
    files: ["**/*.svelte", "**/*.svelte.ts"],
    languageOptions: { parserOptions: { parser: ts.parser, svelteConfig } },
  },
  {
    files: ["**/*.svelte"],
    rules: {
      // `void state.x` in an $effect reads a rune to subscribe to it.
      "@typescript-eslint/no-meaningless-void-operator": "off",
      // Typed linting cannot see other components' prop types inside .svelte
      // files, so it reports their callbacks as `any`; svelte-check (yarn
      // typecheck) checks those types properly.
      "@typescript-eslint/no-unsafe-argument": "off",
      "@typescript-eslint/no-unsafe-assignment": "off",
      "@typescript-eslint/no-unsafe-call": "off",
      "@typescript-eslint/no-unsafe-member-access": "off",
      "@typescript-eslint/no-unsafe-return": "off",
    },
  },
  { files: ["*.config.js"], extends: [ts.configs.disableTypeChecked] },
  {
    // Node scripts (the `yarn tauri` wrapper): Node's globals, no type information.
    files: ["scripts/*.js"],
    extends: [ts.configs.disableTypeChecked],
    languageOptions: { globals: { ...globals.node } },
  },
);
