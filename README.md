# GraphGL

## Overview

GraphGL is a graphical utility for creating and managing graph representations. This README provides all necessary information to set up, configure, and use the project effectively.

---

## Prerequisites

Before building the project, ensure the following tools are installed:

- **Microsoft Visual C++ (MSVC)** compiler
- **CMake** (latest version recommended)

You may also need to adjust certain paths in the `CMakeLists.txt` file depending on your system configuration (see the "Path Adjustments" section below).

---

## Dependencies

The project relies on the following libraries:

### Required Dependencies

- **[GLEW](https://glew.sourceforge.net/)** (I used precompiled binaries)
- **[GLFW](https://www.glfw.org/)** (I used precompiled binaries)

### Included as Submodules

The repository includes these dependencies as submodules:

- **[FreeType](https://freetype.org/)**: Precompiled binaries from [this repository](https://github.com/ubawurinna/freetype-windows-binaries) were used. Note: These are for Windows, so alternative binaries may be needed for other platforms.
- **[glm](https://github.com/g-truc/glm)**
- **[stb](https://github.com/nothings/stb)**

To initialize the submodules, run the following commands after cloning the repository:

```bash
git submodule init
git submodule update
```

---

## Building the Project

1. Install the required dependencies (MSVC and CMake).
2. Configure and generate project files with CMake:

```bash
cmake -G "Visual Studio 17 2022" -A Win32 -S . -B build
```

3. Build the project:

```bash
cmake --build build
```

4. Run the executable from the `build` directory.

---

## Path Adjustments

Depending on your system setup, you may need to modify paths in the `CMakeLists.txt` file to correctly locate the required libraries. These paths include:

### Paths to Libraries

```cmake
# Paths to library directories
link_directories("${CMAKE_SOURCE_DIR}/dependencies/freetype/release static/vs2015-2022/win32")
link_directories("${CMAKE_SOURCE_DIR}/dependencies/glew-2.1.0/lib/Release/Win32")
link_directories("${CMAKE_SOURCE_DIR}/dependencies/glfw-3.4/lib-vc2022")

# Include directories
include_directories("${CMAKE_SOURCE_DIR}/dependencies/freetype/include")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/glew-2.1.0/include")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/glfw-3.4/include")
```

Adjust these paths as needed to match your specific directory structure and library versions.

---

## Usage

### Graph Management

- **Draw Vertices**: Press ***1*** to enable vertex drawing. Click on the canvas to place graph vertices. Numbering is automatic and cannot be modified at this stage.
- **Draw Edges**: Press ***2*** to enable edge drawing. Click on two vertices to create an edge between them. Edges are bidirectional and have a default length of 1.0.
- **Move Vertices**: Press ***3*** to enable vertex movement. Drag individual vertices or select and move multiple vertices at once.

### Saving Graphs

- **Save as Image**: Select the vertices to save and press `CTRL + S`. The image will be saved as a `.png` file with transparency in the `testfiles` folder (just create it first;).
- **Save as File**: Save the graph in a formatted file for future loading and editing.

