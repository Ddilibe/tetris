# **Detris: A Raylib-Powered C Tetris Experience** 🎮

"Detris" is a classic Tetris game implemented in C, leveraging the powerful `raylib` library for direct hardware access and straightforward graphical rendering. This project focuses on delivering clean, efficient game mechanics and robust state management for a polished and engaging retro gaming experience. It features various game states including a main menu, active gameplay, and high score tracking, along with precise block manipulation and dynamic collision detection.

## Installation

To get a local copy of Detris up and running on your system, follow these step-by-step instructions:

1.  **Clone the Repository**:
    Begin by cloning the project repository to your local machine:

    ```bash
    git clone git@github.com:Ddilibe/tetris.git
    cd tetris
    ```

2.  **Install Premake5**:
    Detris utilizes `Premake5` for cross-platform build configuration. Download the appropriate binary for your operating system from the [Premake website](https://premake.github.io/download/). Place the `premake5` executable in your system's PATH, or directly into the `build/` directory of the cloned repository. 

3.  **Generate Build Files**:
    Navigate to the `build/` directory and execute Premake to generate project files suitable for your development environment:

    *   For **MinGW-W64 (Windows/Linux via WSL)**:
        if you are using the W64devkit and have not added it to your system path encironment variable, you must use the W64devkit.exe terminal, not CMD.exe. If you want to use cmd.exe or any other terminal, please make sure that fcc/mingw-W64 is in your path environment variable.
        ```bash
        cd build
        premake5 gmake
        cd ..
        ```
    *   For **Visual Studio 2022 (Windows)**:
        - Run build-VisualStudio2022.bat
        - Double click the .sln file that is generated
        - Develop your game
        - You are good to go

    This process will create the necessary build configuration files (e.g., `Makefile`s or `.sln` files) within the `build/build_files` directory.

4.  **Build the Project**:
    Compile the source code using the generated build files:

    *   **Using `make` (MinGW-W64/Linux)**:
        ```bash
        # Example for a release x64 build
        mingw32-make config=release_x64 
        # Other configurations include: debug_x64, debug_x86, debug_arm64, release_x86, release_arm64
        ```
    *   **Using Visual Studio (Windows)**:
        Open the generated `raylib-quickstart.sln` file (or similar) located in `build/build_files` with Visual Studio 2022. Then, build the `tetris` project from within the IDE.
    *   **Using Macos**:
        Open the build folder, run `./premake5 gmake`. Return back to the root and run `make`. You are good to go.

## Usage

After successfully building the project, you can run the executable from your build output directory (e.g., `bin/release/tetris.exe` on Windows or `bin/release/tetris` on Linux).

Navigate and play Detris using the following interactive controls:

*   **Main Menu Navigation**:
    *   Use your `Mouse` to click on "Start Game", "High Scores", "Options", "Instructions", or "Exit" buttons.

*   **Gameplay Controls**:
    *   `Arrow Left` / `Arrow Right`: Move the currently falling block horizontally across the grid.
    *   `Arrow Down`: Accelerate the downward movement of the current block.
    *   `Arrow Up`: Unconventionally, this allows moving the block upwards for tactical repositioning.
    *   `R`: Rotate the current block clockwise.
    *   `P` or `Mouse Click` on "Pause" button: Pause the game and enter the Pause Menu.
    *   `Mouse Click` on "Reset" button (in-game): Immediately reset the current game session.
    *   `Mouse Click` on "Menu" button (in-game): Return to the Main Menu.

*   **Pause Menu Controls**:
    *   `P` or `Space`: Resume gameplay from the paused state.

## Features

*   🧱 **Core Tetris Gameplay**: Experience the timeless block dropping, moving, and line-clearing mechanics.
*   🔄 **Block Rotation**: Execute precise clockwise rotations for optimal block placement.
*   🚀 **Fast Drop**: Swiftly maneuver blocks to their desired positions with accelerated downward movement.
*   ⬆️ **Upward Movement**: A unique feature allowing blocks to be moved upwards for advanced tactical adjustments.
*   📊 **Score & Level System**: Track your progress with a dynamic scoring system and increasing difficulty levels.
*   🎮 **Intuitive Menus**: Navigate effortlessly through the Main Menu, Pause Menu, High Scores, and Instructions screens.
*   🎨 **Dynamic Coloring**: Blocks are rendered with a diverse palette of vibrant colors, enhancing visual appeal.
*   💥 **Collision Detection**: Robust algorithms ensure accurate detection of collisions with walls, the game floor, and other settled blocks.
*   💾 **Game State Management**: Comprehensive system to manage game progress, player scores, and block queues.
*   🗄️ **FIFO Block Queue**: Get a strategic advantage by previewing upcoming blocks in a First-In-First-Out queue.
*   📝 **Comprehensive Logging**: Integrated logger provides detailed debug, information, warning, and error messages for development and troubleshooting.
*   🌐 **Cross-Platform Compatibility**: The project is configured to build seamlessly across various platforms, supporting MinGW-W64 and Visual Studio 2022.
*   ⚙️ **Doxygen Integration**: Prepared for generating detailed source code documentation using Doxygen.
*   🐍 **Python Utilities**: Includes a supplementary Python script for visualizing and calculating bitwise grid operations, aiding development insights.

## Technologies Used

| Technology    | Description                                                     | Link                                                         |
| :------------ | :-------------------------------------------------------------- | :----------------------------------------------------------- |
| C             | The primary programming language underpinning all game logic and structure. | [Wikipedia](https://en.wikipedia.org/wiki/C_(programming_language)) |
| raylib        | A simple, easy-to-use library designed for learning videogames programming. | [raylib.com](https://www.raylib.com/)                        |
| Premake5      | A powerful command-line utility for generating project files for various IDEs and build systems. | [Premake](https://premake.github.io/)                        |
| Doxygen       | A widely used documentation generation tool for multiple programming languages including C. | [Doxygen](https://www.doxygen.nl/index.html)                 |
| MinGW-W64     | Minimalist GNU for Windows, providing a robust open-source C/C++ toolchain. | [MinGW-W64](https://mingw-w64.org/)                          |
| Visual Studio | Microsoft's comprehensive integrated development environment for Windows application development. | [Visual Studio](https://visualstudio.microsoft.com/)         |

## License

No explicit project-wide license file is provided. Users are advised to refer to individual source files for specific licensing details (e.g., `include/resource_dir.h` is MIT licensed, and `src/main.c` is marked with CC0 1.0 Public Domain).

## Author Info

Connect with the developer of this project!

*   **Dilibe**
*   [**LinkedIn**](https://www.linkedin.com/in/dilibe-fidelugwuowo)
*   [**Twitter**](https://x.com/therealdilibe)

## Badges

[![C Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![raylib](https://img.shields.io/badge/Powered%20by-raylib-orange.svg)](https://www.raylib.com/)
[![Premake5](https://img.shields.io/badge/Build%20System-Premake5-yellowgreen.svg)](https://premake.github.io/)
[![Documentation](https://img.shields.io/badge/Documentation%20Generated%20by-Doxygen-purple.svg)](https://www.doxygen.nl/)

[![Readme was generated by Dokugen](https://img.shields.io/badge/Readme%20was%20generated%20by-Dokugen-brightgreen)](https://www.npmjs.com/package/dokugen)