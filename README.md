# Death X

A lightweight Geode mod for Geometry Dash that marks each death position with a small red X.

## Features

- Adds an X marker every time the player dies.
- Supports a configurable FIFO marker limit with a manual override up to 10000.
- Can merge nearby deaths into one marker and intensify marker color.
- Briefly glows the merged marker so repeated deaths are easier to read.
- Exposes marker size and opacity settings.
- Adds a pause-menu clear button for the current run.

## Support

- Geometry Dash: 2.2081
- Geode: 5.7.1 or compatible
- Packaged platform: macOS

The source is portable Geode/C++, but the current release package only includes a macOS binary. Build and merge the other platform binaries before marking Windows, Android, or iOS as supported.

## Build

Install the Geode CLI and SDK, then build from the repository root:

```sh
geode build --config Release
```

The packaged mod is written to:

```text
build/deathxteam.death_x.geode
```

## Install Locally

```sh
geode package install build/deathxteam.death_x.geode
```

Restart Geometry Dash after installing.

## Publishing Notes

To publish on the Geode index, create a public GitHub release with the built `.geode` file, then submit the direct download link with the Geode CLI. Do not claim non-macOS platforms until those binaries are included.
