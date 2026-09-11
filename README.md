# Death X

A lightweight Geode mod for Geometry Dash that marks each death position with a small red X.

## Features

- Adds an X marker every time the player dies.
- Ignores noclip collision attempts unless they result in a real death.
- Detects noclip through Eclipse, ignore-damage state, or survived death collisions.
- Can ignore the rest of an attempt after noclip is used.
- Supports a configurable marker limit with a manual override up to 1000.
- Can merge nearby deaths into one marker and intensify marker color.
- Briefly glows the merged marker so repeated deaths are easier to read.
- Exposes marker size and opacity settings.
- Shows a pause-menu clear button only when the current run has markers.

Eclipse integration is optional.

## Support

- Geometry Dash: 2.2081
- Geode: 5.9.0 or compatible
- Packaged platforms: Windows and macOS

The first release intentionally does not declare Android or iOS support because those platforms have not been playtested.

The included GitHub Actions workflow builds all declared platforms and merges them into one downloadable artifact.

For a local Windows cross-build on macOS or Linux, install Zig, Ninja, and xwin; run `xwin splat`; set `ZIG_EXECUTABLE` and `XWIN_ROOT`; then pass `cmake/WindowsZigXwin.cmake` as the CMake toolchain file.

## Build

Install the Geode CLI and SDK, then build the required platforms from the repository root:

```sh
geode build --platform mac-os --config Release
geode build --platform windows --config Release
```

Merge the two generated packages into one release package:

```sh
mkdir -p release
cp build/deathxteam.death_x.geode release/deathxteam.death_x.geode
geode package merge \
  release/deathxteam.death_x.geode \
  build-win/deathxteam.death_x.geode
```

The merge command adds the other platform binaries to its first package argument.

## Install Locally

```sh
geode package install release/deathxteam.death_x.geode
```

Restart Geometry Dash after installing. Only install a package containing a binary for the device's platform.

## Publishing Notes

To publish on the Geode index, create a public GitHub release with the merged `.geode` file, then submit the direct download link with the Geode CLI.
