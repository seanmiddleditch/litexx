cmake_minimum_required(VERSION 3.12)

project(litexx
	VERSION 0.0.1
	HOMEPAGE_URL https://github.com/seanmiddleditch/litexx.git
	LANGUAGES CXX
)

get_directory_property(parent_dir PARENT_DIRECTORY)
set(is_root ON)
if(parent_dir)
    set(is_root OFF)
endif()

option(LITEXX_BUILD_VERBOSE "Build litexx verbosely" ${is_root})
option(LITEXX_BUILD_TESTS "Build litexx tests" ${is_root})

if(LITEXX_BUILD_VERBOSE)
    message(STATUS "[litexx] Building version ${litexx_VERSION}")
endif()

add_subdirectory(external)

add_library(litexx INTERFACE)
target_compile_features(litexx INTERFACE cxx_std_17)

try_compile(has_builtin_char_only ${CMAKE_CURRENT_BINARY_DIR}
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/cmake/test_builtin_char_only.cpp
    CXX_STANDARD 17
)

if(has_builtin_char_only)
    if(LITEXX_BUILD_VERBOSE)
        message(STATUS "[litexx] Using string builtins for char only")
    endif()
    target_compile_definitions(litexx INTERFACE
        LITEXX_USE_BUILTIN_STRLEN_CHAR
    )
else()
    if(LITEXX_BUILD_VERBOSE)
        message(STATUS "[litexx] NOT using string builtins")
    endif()
endif()

target_include_directories(litexx INTERFACE
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

install(TARGETS litexx EXPORT litexx-targets
    ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX})
install(EXPORT litexx-targets DESTINATION share/litexx/cmake)

export(TARGETS litexx FILE litexx-exports.cmake)

if(LITEXX_BUILD_TESTS)
    if(LITEXX_BUILD_VERBOSE)
        message(STATUS "[litexx] Building tests")
    endif()

	enable_testing()
	add_executable(litexx_tests)
    target_sources(litexx_tests PRIVATE
        tests/char_traits.cpp
        tests/main.cpp
        tests/string_view.cpp
    )
	target_link_libraries(litexx_tests litexx doctest)
	add_test(litexx_tests litexx_tests)
endif()
