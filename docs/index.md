---
layout: home
title: T3SDK
titleTemplate: "Thief: Deadly Shadows modding SDK"

hero:
  name: T3SDK
  text: "Fixes and mods for Thief: Deadly Shadows"
  tagline: A launcher, a mod loader and an engine API for the Steam release, and a matching decompilation of the game.
  image:
    src: /logo.svg
    alt: T3SDK
  actions:
    - theme: brand
      text: Play
      link: /guide/getting-started
    - theme: alt
      text: Make mods
      link: /modding/first-mod
    - theme: alt
      text: Contribute to the decomp
      link: /matching

features:
  - title: Play
    details: Download the launcher, install T3SDK and play at your monitor's resolution, in a borderless window, with widescreen menus and mods.
    link: /guide/getting-started
    linkText: Getting started
  - title: Make mods
    details: Write a mod DLL against a small C API, pack it as a .t3mod file and publish it in the mod index.
    link: /modding/first-mod
    linkText: Your first mod
  - title: Contribute to the decomp
    details: Rewrite the game's functions as C++ that its original compiler turns into the same bytes, and document the engine on the way.
    link: /matching
    linkText: How matching works
---

T3SDK works with the Steam release of Thief: Deadly Shadows (patch 1.1). It
contains nothing from the game: it changes your own copy, in memory, while it
runs. If you don't own the game yet, [buy it on Steam](https://store.steampowered.com/app/6980/).

Questions and help: the [Taffer Tavern on Discord](https://discord.gg/hdAXH73tEG).
Source code, releases and issues: [GitHub](https://github.com/Veradictus/Thief3-Decomp).
