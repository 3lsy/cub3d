#!/bin/bash

PROGRAM_NAME="cub3D"

# Get all the process IDs (PIDs) of the running program
PIDS=$(pgrep -f "$PROGRAM_NAME")

# If the program is running (PIDs is not empty)
if [ -n "$PIDS" ]; then
    for PID in $PIDS; do
        # Get the memory usage in kilobytes (KB) for the specific PID
        MEMORY_KB=$(ps -o rss= -p $PID)

        # Convert to megabytes (MB)
        MEMORY_MB=$(echo "$MEMORY_KB / 1024" | bc -l)

        # Display the current memory usage with a timestamp
        echo "$(date): Memory Usage for $PROGRAM_NAME (PID $PID): $MEMORY_MB MB"
    done
else
    # If the program is not running, inform the user
    echo "$(date): $PROGRAM_NAME is not running"
fi
