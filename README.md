# Reinforcement Learning library in C++ (under construction)

## Documentation

To view the documentation, run

```
doxygen Doxyfile
```

and open the file `docs/html/index.html`.


## Creating and running examples

* Create file `examples/my_example.cpp` 

* Add the following lines at the end of `examples/CMakeLists.txt`:

```
add_executable(my_example my_example.cpp)
target_link_libraries(my_example rlcpp)
```

* Run 

```
$ bash scripts/compile.sh my_example && ./build/examples/my_example 
```


## Testing

### Creating a new test

* Create a file `test/my_test.cpp` using [Catch2](https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md)

* In the file `test/CMakeLists.txt`, include `my_test.cpp` in the list of files in `add_executable()`.

* Run

```
$ bash scripts/run_tests.sh
```
