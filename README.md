## Requirements
* [CMake](https://cmake.org/)
    * Add this to your `PATH` during installation.
* [Vcpkg](https://github.com/microsoft/vcpkg)
    * Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg.
* [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
    * Required workload: "Desktop development with C++".

## Building

These instructions are for building the project from a PowerShell terminal.

1.  **Clone the repository and its submodules:**
    ```powershell
    git clone --recurse-submodules https://github.com/xSyphel/ENBHelperSE
    cd ENBHelperSE
    ```

2.  **Configure the project with CMake:**
    This command creates a `build` directory and prepares the project for compilation. It's crucial to include the `-DCMAKE_TOOLCHAIN_FILE` argument so CMake can find the libraries installed by vcpkg.
    ```powershell
    cmake -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" ../ENBHelperSE
    ```
    > **Note:** "../ENBHelperSE" assuming that you're compiling in a build folder outside of ENBHelperSE folder.

3.  **Compile the project:**
    This command builds the `Release` version of the plugin.
    ```powershell
    cmake --build . --config Release
    ```

4.  **Locate the DLL:**
    The compiled plugin, `ENBHelperSE.dll`, will be located in the `build/Release/` directory.