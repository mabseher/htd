# COMPILE

## Dependencies

**htd** has the following compilation dependencies:

* A recent C++11 compiler 
  * [g++](https://gcc.gnu.org/)
  * [Clang](http://clang.llvm.org/)
  * or some other compiler of your choice
* [CMake](http://cmake.org/) for generating the build scripts
* [Doxygen](www.doxygen.org/) for generating the documentation

**htd** was compiled and tested with the following versions of the dependencies mentioned above:

* g++ 4.9.2
* Clang 3.4
* CMake 3.2
* Doxygen 1.8.6

Unless the developers of the dependencies introduce incompatible changes, compiling **htd** with later versions of the dependencies should work too. (Older versions might work if you're lucky.)

## Compilation

For the actual compilation step of **htd** just run `cmake <PATH_TO_HTD_SOURCE_DIRECTORY>` (you may want to select a desired *CMAKE_INSTALL_PREFIX* to choose the installation directory) and `make` in a directory of your choice. Via the commands `make test` and `make doc` you can run the test cases shipped with **htd** and create the API documentation of **htd** after the compilation step was finished.

# INSTALL

After compiling the library, you can install it as well as the front-end application **htd_main** and all required headers via `make install`. (Note that you must not delete the file `install_manifest.txt` generated in this step, because otherwise uninstalling **htd** cannot be done in an automated way any more.)

# UNINSTALL

If you decide to uninstall the library, you can easily do that via the command `make uninstall`. (If you deleted the file `install_manifest.txt` required for automated uninstallation it should also work to delete all folders related to **htd** in *CMAKE_INSTALL_PREFIX* manually.)
