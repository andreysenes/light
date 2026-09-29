#!/usr/bin/env bash
set -euo pipefail
DIR="$(cd "$(dirname "$0")" && pwd)"
SCAD="$DIR/stagemod_spot_v0.scad"
OUT="$DIR/stl"
mkdir -p "$OUT"

for part in body diffuser bottom_plate led_clip; do
  echo "Exporting $part..."
  openscad -q -D "PART=\"$part\"" -o "$OUT/spot_${part}.stl" "$SCAD"
done

echo "Done: $OUT"
