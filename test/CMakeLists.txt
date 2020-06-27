link_libraries(${LIB_NAME})
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_BINARY_DIR}/include)

addtest(test1 class_A_test.cpp)