link_libraries(${LIB_NAME})
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_BINARY_DIR}/include)

add_subdirectory(functions)
add_subdirectory(algorithms)

if(NEURAL_NET_TESTING)
add_subdirectory(neural_net)
endif()