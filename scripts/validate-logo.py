import struct
import sys
from pathlib import Path


path = Path(sys.argv[1] if len(sys.argv) > 1 else "logo.png")
data = path.read_bytes()

if len(data) > 5_000_000:
    raise ValueError("logo exceeds the 5 MB Geode Index limit")
if data[:8] != b"\x89PNG\r\n\x1a\n" or data[12:16] != b"IHDR":
    raise ValueError("logo must be a valid PNG")

width, height = struct.unpack(">II", data[16:24])
if width != height:
    raise ValueError(f"logo must be square, got {width}x{height}")
if width > 1024 or height > 1024:
    raise ValueError(f"logo exceeds the 1024x1024 Geode Index limit: {width}x{height}")

print(f"{path}: valid {width}x{height} PNG")
