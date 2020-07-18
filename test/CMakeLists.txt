link_libraries(${LIB_NAME})
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_BINARY_DIR}/include)

add_subdirectory(functions)

addtest(gradient_descent_test gradient_descent_test.cpp)