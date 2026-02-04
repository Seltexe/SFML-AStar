# SFML A* implementation

Minimal A* C++ visual implementation using **SFML 2.6.2**,
**CMake**, and **vcpkg**.\
You can change the start and end positions, as long as adding weight to tiles
and choosing to allow diagonal travel or not.

This project was developed during my second year of Game Development at 
Game Academy as part of my C++ learning curriculum, with a focus on 
strengthening core programming skills.

------------------------------------------------------------------------

## 📁 Project Structure

    .
    ├── CMakeLists.txt
    ├── README.md
    ├── src/
    └── include/

------------------------------------------------------------------------

## 🔧 Requirements

-   **CMake** ≥ 3.15\
-   **C++20 compatible compiler**
    -   MSVC 2022 / GCC 12+ / Clang 15+
-   **vcpkg**
-   **SFML 2.6.2**


------------------------------------------------------------------------

## 🛠️ Build Instructions

### Windows (MSVC)

``` bash
cmake -B build -S . ^
  -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake

cmake --build build --config Release
```

### Linux / macOS

``` bash
cmake -B build -S .   -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake

cmake --build build
```

------------------------------------------------------------------------

## ▶️ Run

After building:

``` bash
./build/AStar
```

(On Windows: `AStar.exe`)

------------------------------------------------------------------------

## 📜 License

MIT License --- free to use, modify, and distribute.

------------------------------------------------------------------------

## ❤️ Credits

-   SFML
-   vcpkg
