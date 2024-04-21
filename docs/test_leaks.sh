#!/bin/env bash

for map in maps/{valid,invalid,macros,tester}/*.cub; do
    echo "Testing $map..."

    # Run Valgrind to check for memory leaks
    valmessage=$(valgrind ./cub3D "$map" 2>&1 || true)

    # Check for the "no leaks are possible" message
    leaks=$(echo "$valmessage" | grep 'no leaks are possible' || true)

    if [ -n "$leaks" ]; then
        echo "No leaks for $map! ✅🔥"
    else
        echo "Errors for $map:"
        echo "$valmessage"
        echo "Leaks FAILURE for $map! 😞❌"
    fi
done