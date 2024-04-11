#!/bin/bash

folder="./maps/invalid/"
chmod -r "./maps/invalid/forbidden.cub"
chmod -r "./textures/north_wall/forbidden_mario_cube.xpm"

for file in "$folder"*; do
    if [ -f "$file" ]; then
        echo "Test file: $file" >> output
        ./cub3d "$file" >> output 2>&1
    fi
done

chmod +r "./maps/invalid/forbidden.cub"
chmod +r "./textures/north_wall/forbidden_mario_cube.xpm"

diff snapshot output

rm output
