cmake_minimum_required(VERSION 3.5)


set(LIB_NAME nnoops-lib-cpp)
set(VERSION 0.1)


project(${LIB_NAME} VERSION ${VERSION} LANGUAGES C CXX)

include(GNUInstallDirs)
include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)
include(cmake/functions.cmake)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(CLANG_TIDY   "Enable clang-tidy checks during compilation" OFF)
option(ASAN         "Enable Address Sanitizer" OFF)
option(TSAN         "Enable Thread Sanitizer" OFF)
option(UBSAN        "Enable Undefined Behavior Sanitizer" OFF)
option(WERROR       "Treat warnings as errors" ON)
option(TESTING      "Build tests" ON)
option(SHARED       "Build shared lib" OFF)
option(BENCH        "Build benchmarks" OFF)
option(NEURAL_NET_TESTING "Build neural net tests" OFF)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


## setup compilation flags
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "^(AppleClang|Clang|GNU)$")
    if(WERROR)
        add_compile_options(-Werror)
    endif()
    # enable those flags
    add_cxx_flag(-Woverloaded-virtual) # warn if you overload (not override) a virtual function
    add_cxx_flag(-Wnon-virtual-dtor) # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
    add_cxx_flag(-Wreorder)          # field '$1' will be initialized after field '$2'
    add_flag(-Wall)
    add_flag(-Wextra)
    add_flag(-Wformat=2)               # warn on security issues around functions that format output (ie printf)
    add_flag(-Wmisleading-indentation) # (only in GCC >= 6.0) warn if indentation implies blocks where blocks do not exist
    add_flag(-Wduplicated-cond)        # (only in GCC >= 6.0) warn if if / else chain has duplicated conditions
    add_flag(-Wduplicated-branches)    # (only in GCC >= 7.0) warn if if / else branches have duplicated code
    add_flag(-Wnull-dereference)       # (only in GCC >= 6.0) warn if a null dereference is detected
    add_flag(-Wdouble-promotion)       # (GCC >= 4.6, Clang >= 3.8) warn if float is implicit promoted to double
    add_flag(-Wsign-compare)
    add_flag(-Wtype-limits)            # size_t - size_t >= 0 -> always true
    add_flag(-Wnused-lambda-capture)  # error if lambda capture is unused
    add_flag(-Wreturn-type)      # warning: control reaches end of non-void function [-Wreturn-type]
    add_flag(-Wsign-compare)     # warn the user if they compare a signed and unsigned numbers

    # disable errors
    add_flag(-Wno-unused-function)
    add_flag(-Wno-error=null-dereference)
    add_flag(-Wno-nonnull-compare)
    add_flag(-Wno-unknown-pragmas)
    add_cxx_flag(-Wno-literal-suffix)

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        # Release flags
        add_flag(-Ofast)
    else()
        # Debug flags
        add_flag(-Og)
        add_flag(-g)
    endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(/bigobj)
    if(WERROR)
        add_compile_options(/WX)                      # treats all compiler warnings as errors.
    endif()
    
    # using Visual Studio C++
    add_flag(/W4)                      # displays level 1, level 2, and level 3 warnings, and all level 4 (informational) warnings that are not turned off by default.
    add_flag(/permissive-)             # enforces standards conformance
    add_flag(/w14242)                  # 'identfier': conversion from 'type1' to 'type1', possible loss of data
    add_flag(/w14263)                  # 'function': member function does not override any base class virtual member function
    add_flag(/w14265)                  # 'classname': class has virtual functions, but destructor is not virtual instances of this class may not be destructed correctly
    add_flag(/w14296)                  # 'operator': expression is always 'boolean_value'
    add_flag(/w14826)                  # Conversion from 'type1' to 'type_2' is sign-extended. This may cause unexpected runtime behavior.
    add_flag(/w14640)                  # Enable warning on thread un-safe static member initialization

    # disable these warnings:
    # appears in the gtest library
    add_flag(/wd4389)                  # disable warning: 'operator' : signed/unsigned mismatch
    add_flag(/wd4455)                  # disable warning: 'operator ""s': literal suffix identifiers that do not start with an underscore are reserved
    add_flag(/wd4127)                  # disable warning: conditional expression is constant
    add_flag(/wd4505)                  # disable warning: warning C4505: 'dummy': unreferenced local function has been removed
    add_flag(/wd4244)                  # disable warning: conversion' conversion from 'type1' to 'type2', possible loss of data

    # https://stackoverflow.com/questions/5004858/why-is-stdmin-failing-when-windows-h-is-included
    add_flag(/DNOMINMAX)

    if(SHARED)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd") 
    else()
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    endif()
endif()


include_directories(include)
add_subdirectory(src)

if(TESTING)
    include(cmake/gtest.cmake)
    enable_testing()
    add_subdirectory(test)
endif()

if(BENCH)
    add_subdirectory(benchmark)
endif()

if(CLANG_TIDY)
    include(cmake/clang-tidy.cmake)
endif()

if(ASAN)
    include(cmake/asan.cmake)
endif()

if(TSAN)
    include(cmake/tsan.cmake)
endif()

if(UBSAN)
    include(cmake/ubsan.cmake)
endif()
