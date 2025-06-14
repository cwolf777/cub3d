🕹️ **cub3d**

This repository contains a solution to the cub3d project from the **fourth circle** of the **42 school curriculum**.
The project implements a simple 3D game engine inspired by classic Wolfenstein 3D, demonstrating basic 3D graphics rendering techniques.
It leverages the MLX42 graphics library for efficient window management and rendering, and a custom libft for core utilities and memory handling.

🚀 **Project Overview**

cub3d uses raycasting to simulate a 3D environment on a 2D map.
The technique involves casting rays from the player’s viewpoint to detect walls and render vertical slices, creating a first-person perspective.

Key challenges include:

- Efficient raycasting calculations for wall detection

- Correct rendering of textures and shading

- Player movement and collision detection

- Real-time user input handling

**Wolfenstein 3D Inspiration:**

The rendering and gameplay mechanics are heavily inspired by the classic Wolfenstein 3D game, one of the first popular FPS games using raycasting.

🔧 **Key Features**
- 2D map parsing and validation

- Smooth player movement and rotation

- Textured walls with correct perspective

- Minimap rendering for orientation


💬 **Example Usage**

make

./cub3d maps/map.cub
