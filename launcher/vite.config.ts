/// <reference types="vitest/config" />
import { svelte } from "@sveltejs/vite-plugin-svelte";
import { defineConfig } from "vite";

// Tauri expects a fixed dev port and serves dist/ in release builds.
export default defineConfig({
  plugins: [svelte()],
  resolve: {
    // Same aliases as tsconfig.json's "paths".
    alias: { $lib: "/src/lib", $components: "/src/components" },
  },
  clearScreen: false,
  server: { port: 1420, strictPort: true },
  envPrefix: ["VITE_", "TAURI_ENV_"],
  build: { target: "es2023", outDir: "dist", emptyOutDir: true },
  test: { include: ["src/**/*.test.ts"], environment: "node" },
});
