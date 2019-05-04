include(FetchContent)
FetchContent_Declare(doctest
    GIT_REPOSITORY https://github.com/onqtam/doctest.git
    GIT_TAG 2.3.1
    GIT_SHALLOW ON
    GIT_SUBMODULES ""
)

if(LITEXX_BUILD_TESTS AND NOT TARGET doctest)
    FetchContent_Populate(doctest)
    set(DOCTEST_WITH_TESTS OFF CACHE BOOL "enable doctest tests")
    set(DOCTEST_WITH_MAIN_IN_STATIC_LIB OFF CACHE BOOL "enable doctest static library")
    add_subdirectory(${doctest_SOURCE_DIR} ${doctest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

