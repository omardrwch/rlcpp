# Template for simple projects using C++ and CMake


## Compiling and testing

* `lib`: folder containing a library, with sublibraries `sublib1` and `sublib1`
* `app`: folder containing apps that use the library, `subapp1` and `subapp2`
* `test`: unit tests, generates executable test file using [Catch2](https://github.com/catchorg/Catch2)

To compile:

```
mkdir build
cd build
cmake ..
make
cd ..
```

To run:

```
./build/app/subapp1
./build/app/subapp2
```


Other scripts:

* `compile.sh`: run commands to compile
* `clean.sh`: delete all files in build folder
* `run_tests.sh`: run unit tests


## Generating documentation using doxygen

Installing [doxygen](http://www.doxygen.nl/manual/starting.html):

```
sudo apt-get install doxygen
```

Creating a configuration file (named `Doxyfile` by default):

```
doxygen -g <config-file>
```

Tags in Doxyfile changed from default (more suggestions can be found in [this tutorial](http://www.yolinux.com/TUTORIALS/LinuxTutorialC++CodingStyle.html#DOXYGEN)):

* `PROJECT_NAME`: set to "My C++ Template"
* `OUTPUT_DIRECTORY`: folder where to put docs. Here, it is set to `docs`.
* `FULL_PATH_NAMES = NO`
* `INPUT = lib/`
* `RECURSIVE = YES`
* `GENERATE_TREEVIEW = YES`
* `HAVE_DOT = NO`

Generating the documentation:

```
doxygen <config-file>
```

Useful links:

* [C++ Coding Standards and Pratices](http://www.yolinux.com/TUTORIALS/LinuxTutorialC++CodingStyle.html#DOXYGEN)
* [Doxygen manual](http://www.doxygen.nl/manual/starting.html)
* [Documenting the code](http://www.doxygen.nl/manual/docblocks.html)
