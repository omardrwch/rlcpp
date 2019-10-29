link_directories(${RLCPP_SOURCE_DIR}/rlcpp/src/mdp
                 ${RLCPP_SOURCE_DIR}/rlcpp/src/online
                 ${RLCPP_SOURCE_DIR}/rlcpp/src/utils)

include_directories(${RLCPP_SOURCE_DIR}/rlcpp/include/mdp
                    ${RLCPP_SOURCE_DIR}/rlcpp/include/online
                    ${RLCPP_SOURCE_DIR}/rlcpp/include/utils)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(debug debug.cpp)
target_link_libraries(debug rlcpp)

add_executable(mdp_example mdp_example.cpp)
target_link_libraries(mdp_example rlcpp)

add_executable(vi_example vi_example.cpp)
target_link_libraries(vi_example rlcpp)

add_executable(ucbvi_example ucbvi_example.cpp)
target_link_libraries(ucbvi_example rlcpp ${CMAKE_THREAD_LIBS_INIT})

add_executable(gridworld_example gridworld_example.cpp)
target_link_libraries(gridworld_example rlcpp)


# add_executable(subapp1 subapp1/main.cpp)
# target_link_libraries(subapp1 rlcpp)

# add_executable(subapp2 subapp2/main.cpp)
# target_link_libraries(subapp2 rlcpp)
