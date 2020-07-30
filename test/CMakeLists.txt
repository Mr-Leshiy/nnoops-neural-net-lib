link_libraries(${LIB_NAME})
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_BINARY_DIR}/include)

add_subdirectory(functions)
add_subdirectory(algorithms)
add_subdirectory(neural_net)