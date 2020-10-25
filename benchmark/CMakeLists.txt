find_package(benchmark REQUIRED)

function(addbenchmark name)
    set(_target benchmark_${name})
    add_executable(${_target} ${ARGN})
    disable_clang_tidy(${_target})
    target_link_libraries(${_target}
            benchmark::benchmark
            Threads::Threads
            ${LIB_NAME}
            )
endfunction()