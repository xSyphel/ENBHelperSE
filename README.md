## Requirements
* [CMake](https://cmake.org/)
    * Add this to your `PATH` during installation.
* [Vcpkg](https://github.com/microsoft/vcpkg)
    * Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg.
* [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
    * Required workload: "Desktop development with C++".

## Building

powershell:[

# Clone the repository and its submodules
git clone --recurse-submodules https://github.com/xSyphel/ENBHelperSE
cd ENBHelperSE

# Configure the project with CMake. vcpkg will automatically install dependencies. (Build outside of the source directory)
cmake -B build -S .

# Build the project
cmake --build . --config Release

]