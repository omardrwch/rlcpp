link_directories(${RLCPP_SOURCE_DIR}/rlcpp/src/mdp 
                 ${RLCPP_SOURCE_DIR}/rlcpp/src/online
                 ${RLCPP_SOURCE_DIR}/rlcpp/src/utils)

include_directories(${RLCPP_SOURCE_DIR}/rlcpp/include/mdp
                    ${RLCPP_SOURCE_DIR}/rlcpp/include/online
                    ${RLCPP_SOURCE_DIR}/rlcpp/include/utils)
# testing files
add_executable(unit_tests main.cpp
                          space_test.cpp
                          random_test.cpp
                          vector_op_test.cpp)
target_link_libraries(unit_tests rlcpp)


# - add_test() is not necessary when running ./unit_tests
# - add_test() is needed to use the command "make test". In this case, include enable_testing()
#   in source_dir/CMakeLists.txt

# # adding tests
# add_test(NAME tests COMMAND unit_tests)
