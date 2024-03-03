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

## How to run cub3d ? 🕹️

### Configuration files

There are 3 types of elements to be configured inside a configuration file:
- [Wall textures](#wall-textures)
- [Floor and ceiling colors](#floor-and-ceiling-colors)
- [Map](#maps)

Where the *map* element must always be the last element declared on the configuration file.

The *wall textures* and the *floor and ceiling colors* configuration:
- Can be set in any order.
- Can be separated by one or more empty lines.
- Can have it's second argument separated by one or more spaces.

Here's an example of a minimalist configuration file.

`sample.cub`:
```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```
<details name="wall-textures">
<summary><b>Wall textures 🧱</b></summary>

Wall textures vary depending on which side the wall is facing (North, South, East, West).

##### Wall syntax

The texture elements must be declared in a specific order inside the configuration files.
```
<id> <./path_to_the_texture>
```
There are only 4 possible identifiers in the lexic of the texture elements:

| **ID** | **Description** |
|:--------:|:----------------|
| **NO** | North texture.|
| **SO** | South texture.|
| **WE** | West texture.|
| **EA** | East texture.|

Here is a valid example:
```
WE ./path_to_the_west_texture
```
</details>

<details name="floor-and-ceiling-colors">
<summary><b>Floor and ceiling colors 🎨</b></summary>

You can set the floor and ceiling colors inside the configuration file.

##### Floor and ceiling syntax

The texture elements must be declared in a specific order inside the configuration files.
```
<id> <[0,255],[0,255],[0,255]>
```
There are only 2 possible identifiers in the lexic of the floor and ceiling elements:

| **ID** | **Description** |
|:--------:|:----------------|
| **F** | Floor.|
| **C** | Ceiling.|

Here is a valid example:
```
C 225,30,0
```
</details>
<details name="maps">
<summary><b>Maps 🗺️</b></summary>

The program `cub3d` needs a map (with the `.cub` extension) as the first argument to generate the 3D world. 
You can choose, create or modify an existent map.

##### Map syntax

There are only 6 possible characters in the lexic of the map:

| **Char** | **Description** |
|:--------:|:----------------|
| **0** | Empty space.|
| **1** | Wall.|
| **N** | Player’s start position facing *North*.|
| **S** | Player’s start position facing *South*.|
| **E** | Player’s start position facing *East*.|
| **W** | Player’s start position facing *West*.|

The map must be closed/surrounded by walls, if not, the program returns an error.
Here is a valid example of a simple map:
```
111111
100101
101001
1100N1
111111
```
</details>



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
