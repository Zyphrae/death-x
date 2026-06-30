# Building Death X on macOS

This repository contains the source files needed to build Death X as a Geode mod.
The current packaged release target is macOS.

## Requirements

- Geometry Dash 2.2081
- Geode SDK 5.7.1 or compatible
- CMake
- Xcode command line tools
- Geode CLI

## Build

Build and package with the Geode CLI:

```sh
geode build --config Release
```

The packaged `.geode` file should be written under `build/`.

If you build manually with CMake instead, set `GEODE_SDK` to your local SDK path first.

## Test

Install the built `.geode` into your Geometry Dash Geode mods folder, then start
Geometry Dash with Geode enabled.

The default settings are:

- Ignore Start Seconds: `0.5`
- Merge Nearby Deaths: off
- Deaths Per Color Step: `5`
- Maximum Marker Count: `50`
- Manual Marker Count Override: `0` (disabled)
