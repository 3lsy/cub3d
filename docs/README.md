# cub3d
A “*realistic*” 3D graphical representation of the inside of a maze from a first-person perspective using the Ray-Casting principles. 

Built in [miniLibX](https://github.com/42Paris/minilibx-linux), inspired on [Wolfenstein 3D](http://users.atw.hu/wolf3d/) which is the ancestor of games 
like Doom (Id Software, 1993), Doom II (Id Software, 1994), Duke Nukem 3D (3D Realm, 1996)
and Quake (Id Software, 1996), that are additional eternal milestones in the world of video games.

## How to build cub3d ? 🏗️
> [!NOTE]
> #### Requirements
> - Debian or Ubuntu base distro
> - gcc
> - make
> - X11 include files (package xorg)
> - XShm extension must be present (package libxext-dev)
> - Utility functions from BSD systems - development files (package libbsd-dev)
<details>
<summary><b>Setup the <i>miniLibX</i></b></summary>                                      

  Install required packages:
  ```bash
  sudo apt-get install gcc make xorg libxext-dev libbsd-dev
  ```
  After running make, the miniLibX will have generated some files that you must install:
  
  - **libmlx.a** and/or **libmlx_$(HOSTTYPE).a** in `/usr/X11/lib` or `/usr/local/lib`
  - **mlx.h** in `/usr/X11/include` or `/usr/local/include`
  - __man/man3/mlx*.1__ in `/usr/X11/man/man3` or `/usr/local/man/man3`
  
</details>
<details open>
<summary><b>Compile <i>cub3d</i></b></summary

  Just run `make` and let the magic happen 🪄
  ```bash
  make
  ```
</details>

## How to run cud3d ? ▶️

### Map files 🗺️

The program `cub3d` needs a map (with the `.cub` extension) as the first argument to generate the 3D world. 
You can choose, create or modify an existent map.

#### Map syntax

There are only 6 possible characters in the lexic of the map:
- **0**: Empty space.
- **1**: Wall.
- **N**: Player’s start position facing *North*.
- **S**: Player’s start position facing *South*.
- **E**: Player’s start position facing *East*.
- **W**: Player’s start position facing *West*.

Here is an example map:
```
111111
100101
101001
1100N1
111111
```

## Controls 🎮
<kbd>⎋ Esc</kbd> Close the window and quit the program cleanly.
### Camera
<kbd>←</kbd> Look left inside the <b>maze</b>.</br>
<kbd>→</kbd> Look right inside the <b>maze</b>.
### Movement
<kbd>W</kbd> Move <b>up</b> the point of view through the <b>maze</b>.</br>
<kbd>A</kbd> Move <b>left</b> the point of view through the <b>maze</b>.</br>
<kbd>S</kbd> Move <b>down</b> the point of view through the <b>maze</b>.</br>
<kbd>D</kbd> Move <b>right</b> the point of view through the <b>maze</b>.</br>
