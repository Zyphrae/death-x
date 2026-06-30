# Publishing Checklist

This repository is prepared for GitHub source publishing and a macOS Geode release package.

Before submitting to the Geode index:

1. Build the release package with `geode build --config Release`.
2. Test the package in Geometry Dash with Geode enabled.
3. Create a GitHub release and upload `build/deathxteam.death_x.geode`.
4. Submit the direct release asset URL with `geode index mods create <download-url>`.

Current platform status:

- macOS: packaged
- Windows: not packaged
- Android: not packaged
- iOS: not packaged

Do not add unsupported platforms back to `mod.json` until their binaries are built and included in the `.geode` package.
