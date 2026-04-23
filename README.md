## Requirements
* [CMake](https://cmake.org/)
    * Add this to your `PATH` during installation.
* [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
    * Required workload: "Desktop development with C++".
    * Includes a built-in vcpkg installation — no separate vcpkg setup required.
* [Vcpkg](https://github.com/microsoft/vcpkg) *(optional — only if not using VS 2022's built-in)*
    * If using a standalone installation, set the environment variable `VCPKG_ROOT` to the path of your vcpkg folder.

## Building

All dependencies, including CommonLibSSE-NG, are installed automatically by vcpkg when CMake configures the project. Although I do recommend cloning the CommonLibSSE-NG and using .gitignore on it.

1. **Clone the repository:**
    ```powershell
    git clone https://github.com/xSyphel/ENBHelperSE
    ```

2. **Open the folder in VS Code.**
    The [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extension will detect the included `CMakePresets.json` automatically.

3. **Select a configure preset:**
    Open the Command Palette (`Ctrl+Shift+P`) → CMake: Select Variant → choose Release.

4. **Build:**
    Press `F7` or run "CMake: Build" from the Command Palette. The compiled plugin will be at `build/release/Release/ENBHelperSE.dll`.