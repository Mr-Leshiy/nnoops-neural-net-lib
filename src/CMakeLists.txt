include_directories(${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(algorithms)
add_subdirectory(long_arithmetic)

set(SOURCES
        $<TARGET_OBJECTS:algorithms>
        $<TARGET_OBJECTS:long_arithmetic>
        )


if(SHARED)
    set(BUILD SHARED)
else()
    set(BUILD STATIC)
endif()
message(STATUS "BUILD=${BUILD}")

add_library(${LIB_NAME} ${BUILD} ${SOURCES})

install(TARGETS ${LIB_NAME}
        EXPORT ${LIB_NAME}Config
        COMPONENT devel
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FRAMEWORK DESTINATION ${CMAKE_INSTALL_PREFIX}
        )

install(
        DIRECTORY ${CMAKE_SOURCE_DIR}/include/nnoops
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
        EXPORT ${LIB_NAME}Config
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIB_NAME}
        NAMESPACE nnoops::
)

export(
        TARGETS ${LIB_NAME}
        FILE ${LIB_NAME}Config.cmake
)

target_include_directories(${LIB_NAME}
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

set(configured_pc ${CMAKE_BINARY_DIR}/${LIB_NAME}.pc)
configure_file("${CMAKE_SOURCE_DIR}/cmake/lib.pc.in" "${configured_pc}" @ONLY)
install(FILES "${configured_pc}"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")