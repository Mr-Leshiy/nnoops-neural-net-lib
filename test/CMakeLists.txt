link_libraries(${LIB_NAME})
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_BINARY_DIR}/include)

addtest(functions_test functions_test.cpp)