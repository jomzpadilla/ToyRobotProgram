# XmlVSE
The Volscript Extension module for XML parsing.

# Building
XmlVSE uses CMake to create build systems and binaries. Build scripts are provided for convenience. Each build mode (`debug`, `release`) will be built in a separate build tree within the build directory. A CMake install target places the final binary and a seti.ini that refers to this binary in the `bin` directory, within an appropriate subdirectory. The build scripts will automatically run CMake install after a successful build.

- Windows:
  ```cmd
  build.bat --debug
  ```

- Linux:
  ```sh
  ./build.sh --debug
  ```

Accepted options are:
* `--debug` - build the library with debug information
* `--release` - build the library, optimizing for speed (no debug symbols)
* `--clean` - removes exisiting build files before running the build
* `--verbose` - show more information during a build
* `--strict` - treat warnings as errors
* `--test` - run unit tests - if no build mode is specified, assumes release
* `--pull` - pull down the latest VoltScript binary from Nexus, extract it into the bin/ directory, and use it to run unit tests. Mostly used in automated Jenkins builds.
* `--win32` - the build is for 32-bit (x86) Windows. This option is only valid on the Windows platform.

CMake can also run through another tool that reads the `CMakePresets.json` file, such as Visual Studio Code or Visual Studio. The preset file reproduces the behavior of the build scripts. Advanced users may choose to invoke CMake directly or create their own custom presets in `CMakeUserPresets.json`.

To build on Windows, it is recommended to use `vcvarsall.bat` to add all required tools to the prompt's `PATH` variable. Visual Studio creates shortcuts to this .bat file with various arguments in the start menu when installed. Use "x64 Native Tools Command Prompt for VS" when building a 64-bit DLL for use with the standalone VoltScript binary, or "x64_x86 Cross Tools Command Prompt for VS" when building a 32-bit DLL for use with the Notes client.

CMake will use the first `cl.exe` found in the path, and will not check any others. If you have errors related to undefined externals, make sure your `cl.exe` matches your desired build type. You can check by using the `where cl` command and looking at the first path returned. For example, if the path of the first `cl.exe` ends with `x86\cl.exe`, the command prompt is configured for 32-bit builds only.

# Tests
Unit tests and their dependencies are located in the `tests` directory, and reports are generated in the `tests/unit-test-reports` directory. Run the tests from this directory to prevent test artifacts from cluttering your local repository.
"# ToyRobotProgram" 
