link_directories(${myproject_SOURCE_DIR}/lib/src/sublib1)
link_directories(${myproject_SOURCE_DIR}/lib/src/sublib2)

include_directories(${myproject_SOURCE_DIR}/lib/include/sublib1)
include_directories(${myproject_SOURCE_DIR}/lib/include/sublib2)

# testing files
add_executable(unit_tests sum_test.cpp
                          mult_test.cpp)
target_link_libraries(unit_tests mylib)


# - add_test() is not necessary when running ./unit_tests
# - add_test() is needed to use the command "make test". In this case, include enable_testing()
#   in source_dir/CMakeLists.txt

# # adding tests
# add_test(NAME tests COMMAND unit_tests)
