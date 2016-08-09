# COMPILE

## Dependencies

**htd** has the following compilation dependencies:

* A recent C++11 compiler 
  * [g++](https://gcc.gnu.org/)
  * [Clang](http://clang.llvm.org/)
  * [Visual Studio](https://www.visualstudio.com/)
  * or some other compiler of your choice
* [CMake](http://cmake.org/) for generating the build scripts
* [Doxygen](www.doxygen.org/) for generating the documentation

**htd** was compiled and tested with the following versions of the dependencies mentioned above:

* g++ 4.9.2
* Clang 3.4
* Visual Studio 2015
* CMake 3.2
* Doxygen 1.8.6

Unless the developers of the dependencies introduce incompatible changes, compiling **htd** with later versions of the dependencies should work too. (Older versions might work if you're lucky.)

## Compilation

### UNIX

For the actual compilation step of **htd** just run `cmake <PATH_TO_HTD_SOURCE_DIRECTORY>` (you may want to select a desired *CMAKE_INSTALL_PREFIX* to choose the installation directory) and `make` in a directory of your choice. Via the commands `make test` and `make doc` you can run the test cases shipped with **htd** and create the API documentation of **htd** after the compilation step was finished.

### Windows

To generate the necessary project configuration for Visual Studio, run `cmake -G "Visual Studio 14 2015" -DCMAKE_CONFIGURATION_TYPES="Debug;Release" <PATH_TO_HTD_SOURCE_DIRECTORY>`. Afterwards you can use the Visual Studio C++ compiler to build **htd**.

# INSTALL

### UNIX

After compiling the library, you can install it as well as the front-end application **htd_main** and all required headers via `make install`. (Note that you must not delete the file `install_manifest.txt` generated in this step, because otherwise uninstalling **htd** cannot be done in an automated way any more.)

### Windows

Currently, **htd** cannot be installed via a single command. As a workaround you can copy the relevant binaries to a directory of your choice.

# UNINSTALL

### UNIX

If you decide to uninstall the library, you can easily do that via the command `make uninstall`. (If you deleted the file `install_manifest.txt` required for automated uninstallation it should also work to delete all folders related to **htd** in *CMAKE_INSTALL_PREFIX* manually.)

### Windows

Currently, **htd** cannot be uninstalled via a single command. As a workaround you can delete the generated and/or copied files manually.
