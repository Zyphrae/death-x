import json
import sys
from pathlib import Path


def reject_duplicate_fields(pairs):
    result = {}
    for key, value in pairs:
        if key in result:
            raise ValueError(f"duplicate field {key!r}")
        result[key] = value
    return result


path = Path(sys.argv[1] if len(sys.argv) > 1 else "mod.json")
with path.open(encoding="utf-8") as file:
    json.load(file, object_pairs_hook=reject_duplicate_fields)

print(f"{path}: valid JSON with no duplicate fields")
