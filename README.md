
# Experimental 3D Rendering Engine & TrenchBroom Pipeline

A lightweight, low-level 3D graphics rendering engine written from scratch in C++ and OpenGL. As of now intented to use together with my TrenchBroom mapParser. The example implementation reads a map data binary created with the mapParser and renders the texturized level geometry.

https://github.com/Jerrre/mapParser

<img width="372" height="226" alt="render - Trim (1)" src="https://github.com/user-attachments/assets/20e45223-86e9-4cae-928c-7cc426322f76" />

---

##  Tech Stack

* **Language:** C++
* **Graphics API:** OpenGL 3.3+ (Core Profile)
* **Libraries Utilized:** 
  * `GLFW` (Window & Context Creation)
  * `GLAD` (OpenGL Function Loading)
  * `GLM` (OpenGL mathematics)
  * `stb_image` (Lightweight, memory-efficient texture loading)
* **Build System:** CMake 3.15+

---

## How to Build and Run

### Prerequisites
* A compiler with **C++17** support (GCC, Clang, or MSVC)
* **CMake** 3.15+ installed

### Build Steps
```bash
# Configure and compile using CMake
mkdir build && cd build
cmake ..
make

# Run the compiled executable
./main
```
