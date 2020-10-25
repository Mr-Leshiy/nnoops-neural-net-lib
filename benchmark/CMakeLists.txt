find_package(benchmark REQUIRED)

function(addbenchmark name)
    set(THREADS_PREFER_PTHREAD_FLAG TRUE)
    find_package(Threads REQUIRED)
    set(_target benchmark_${name})
    add_executable(${_target} ${ARGN})
    disable_clang_tidy(${_target})
    set_target_properties(${_target} PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED TRUE
    )
    target_link_libraries(${_target}
            benchmark::benchmark
            Threads::Threads
            ${LIB_NAME}
            )
endfunction()

add_subdirectory(long_arithmetic)