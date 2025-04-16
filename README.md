# 🎮 cub3D - Raycasting Game Engine

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Language](https://img.shields.io/badge/language-C-green.svg)

## 📖 Overview

cub3D is a 3D game engine built from scratch using the raycasting technique made famous by Wolfenstein 3D, the first true First Person Shooter in gaming history. This project recreates the magic of early 3D games while exploring the elegant mathematical principles behind raycasting.

This implementation features:
- First-person perspective in a 3D maze
- Textured walls with different textures based on orientation
- Player movement using WASD keys
- Camera rotation using arrow keys or mouse
- Configurable maps via .cub files
- Customizable floor and ceiling colors

## 🔧 Technologies

- **Language**: C
- **Graphics Library**: MinilibX
- **Algorithm**: Raycasting
- **Build System**: Make

## 🚀 Installation

### Prerequisites

- GCC compiler
- Make
- MinilibX library
- Math library

### Compiling

Clone the repository and compile the project:

```bash
git clone https://github.com/yourusername/cub3d.git
cd cub3d
make
```

This will generate the `cub3d` executable.

## 🎮 Usage

Run the program with a map file:

```bash
./cub3d maps/map1.cub
```

### Controls

- **W**: Move forward
- **S**: Move backward
- **A**: Strafe left
- **D**: Strafe right
- **←**: Rotate camera left
- **→**: Rotate camera right
- **ESC**: Exit the game

## 🗺️ Map Format

Maps are defined in `.cub` files and must include:

### Textures (must be in .xpm format):
```
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
WE ./path/to/west_texture.xpm
EA ./path/to/east_texture.xpm
```

### Colors:
```
F 220,100,0    # Floor RGB color
C 225,30,0     # Ceiling RGB color
```

### Map:
- The map must be composed of only these characters:
  - `0`: Empty space
  - `1`: Wall
  - `N`, `S`, `E`, `W`: Player's starting position and orientation
- The map must be enclosed by walls
- Example of a valid map:
```
111111
100101
101001
1100N1
111111
```

## 🧩 Project Structure

```
.
├── includes/           # Header files
│   ├── cub3d.h         # Main header
│   └── parser.h        # Map parser header
├── libs/               # Libraries
│   ├── libft/          # Custom C library
│   └── getnextline/    # Line reader module
├── maps/               # Map files
│   ├── map1.cub
│   ├── mini_map.cub
│   └── ...
├── parsing/            # Map parsing code
│   ├── about_map.c
│   ├── data_checks.c
│   └── ...
├── src/                # Source code
│   ├── main.c          # Entry point
│   └── utils/          # Utility functions
│       ├── math_utils.c
│       ├── helpers.c
│       └── rendring/   # Rendering logic
│           ├── mlx_utils.c
│           ├── raycasting.c
│           └── ...
├── textures/           # Texture files in XPM format
│   ├── north.xpm
│   ├── south.xpm
│   └── ...
├── Makefile            # Build configuration
└── README.md           # Project documentation
```

## 🔍 The Raycasting Algorithm

This implementation uses the Digital Differential Analysis (DDA) algorithm for raycasting. The core principles are:

1. **Cast Rays**: For each vertical screen column, cast a ray from the player's position
2. **Find Walls**: Calculate intersections with horizontal and vertical grid lines
3. **Calculate Distance**: Determine the distance to the nearest wall
4. **Apply Fisheye Correction**: Correct the distortion caused by the projection
5. **Render Wall Slices**: Draw textured wall slices based on the ray intersection
6. **Apply Textures**: Map wall textures based on the orientation (N/S/E/W)

## 📊 Performance Optimizations

- Precomputed trigonometric values
- Distance calculations using Manhattan distance when appropriate
- Wall hit determination optimized for grid-based environments
- Texture mapping using bit shifts and fixed-point arithmetic

## 🤝 Contributing

Contributions are welcome! Feel free to submit a Pull Request.

## 📝 License

This project is licensed under the MIT License.

## 👥 Contributors

- ([@Matich](https://github.com/melhadou))
- ([@UN35](https://github.com/UN-35))

## 🙏 Acknowledgements

- Id Software for creating Wolfenstein 3D and pioneering raycasting techniques
- 1337 School for the project guidelines and requirements
- The MinilibX developers for the graphics library

---

*This project was created as part of the curriculum at [1337 School](https://1337.ma/)*
