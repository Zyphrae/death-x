# v1.0.1

- Fixes duplicate package metadata that prevented Geode Index submission.
- Keeps the release limited to Windows and macOS.

# v1.0.0

- Initial public release.
- Places configurable X markers at death positions in normal, platformer, and dual mode.
- Optionally merges nearby deaths and increases the marker color intensity.
- Preserves high-count white markers when the marker limit is reached by removing the least-repeated marker first.
- Includes marker count, size, opacity, merge radius, start delay, and color-step settings.
- Adds a pause-menu button for clearing active markers.
- Detects common noclip behavior with or without Eclipse and can ignore the remainder of a noclip attempt.
- Prevents duplicate and nested death callbacks from creating extra markers.
- Includes Windows x64 and universal macOS support.
