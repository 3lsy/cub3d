#!/bin/env bash

for map in maps/macros/*.cub; do
    echo -e "\n- Testing $map..."

    message=$(./cub3D "$map" 2>&1 || true)

    error=$(echo "$message" | grep "cub3D" || true)

    if [ -z "$error" ]; then
        echo "- No errors for $map! 😞❌"
    else
        echo "- Errors for $map: ✅🔥"
        echo -e "$message\n"
    fi
done
