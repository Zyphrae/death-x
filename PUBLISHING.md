# Publishing Checklist

This repository is prepared for public source publishing and reproducible multi-platform builds on GitHub Actions.

Before submitting to the Geode index:

1. Push the complete source, logo, license, metadata, and workflow to the public GitHub repository.
2. Confirm the `Build Death X` workflow passes on Windows and macOS.
3. Download the merged `Death-X` Actions artifact and playtest it on every platform declared in `mod.json`.
4. Fix any reproducible crashes or common bugs before submitting.
5. Create and push a version tag matching `mod.json`, `v1.0.0`. The workflow will build and create the GitHub release automatically.
6. Never replace an existing release asset. Increase the version and create a new release instead.
7. Submit the direct release asset URL with `geode index mods create <download-url>`, or submit it from your account page on the Geode website.

For v1.0.0, the expected asset URL is:

`https://github.com/Zyphrae/death-x/releases/download/v1.0.0/deathxteam.death_x.geode`

The Index reviewer makes the final decision. Keep descriptions accurate, preserve the source history, use the Geode APIs, give nodes mod-prefixed IDs, and document any real incompatibilities.

Current platform status:

- macOS normal mode: heavily tested
- macOS platformer mode: preliminary testing passed; more testing planned
- macOS dual mode: tested
- Windows: package build verified; runtime playtest pending
- Android and iOS: not declared for the first release

Do not add Android or iOS to `mod.json` until their binaries are built and playtested.
