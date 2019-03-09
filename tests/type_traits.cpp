#include "litexx/string_view.h"
#include <doctest/doctest.h>

struct sfinae {
    template <typename T>
    static constexpr litexx::enable_if_t<litexx::is_same_v<T, int>, bool> is_int(T);

    template <typename T>
    static constexpr litexx::enable_if_t<!litexx::is_same_v<T, int>> is_int(T);
};


DOCTEST_TEST_CASE("type_traits") {
    using namespace litexx;

    // NOTE: many of these tests are compile-time tests
    // and there will be no assertions for this test case

    DOCTEST_SUBCASE("is_same_v") {
        static_assert(is_same_v<void, void>);
        static_assert(is_same_v<int&, int&>);
        static_assert(!is_same_v<char, int>);
        static_assert(!is_same_v<int&, int>);
    }

    DOCTEST_SUBCASE("void_t") {
        static_assert(is_same_v<void, void_t<int>>);
        static_assert(is_same_v<void, void_t<char, float>>);
    }

    DOCTEST_SUBCASE("enable_if_t") {
        static_assert(is_same_v<void, enable_if_t<true>>);
        static_assert(is_same_v<int, enable_if_t<true, int>>);

        static_assert(is_same_v<bool, decltype(sfinae::is_int(1))>);
        static_assert(is_same_v<void, decltype(sfinae::is_int(1.f))>);
    }

    DOCTEST_SUBCASE("remove_cv_t") {
        static_assert(is_same_v<int, remove_cv_t<int>>);
        static_assert(is_same_v<int, remove_cv_t<const int>>);
        static_assert(is_same_v<int, remove_cv_t<volatile int>>);
        static_assert(is_same_v<int, remove_cv_t<const volatile int>>);
    }

    DOCTEST_SUBCASE("remove_reference_t") {
        static_assert(is_same_v<int, remove_reference_t<int>>);
        static_assert(is_same_v<int, remove_reference_t<int&>>);
        static_assert(is_same_v<int const, remove_reference_t<int const&>>);
    }

    DOCTEST_SUBCASE("remove_cvref_t") {
        static_assert(is_same_v<int, remove_cvref_t<int>>);
        static_assert(is_same_v<int, remove_cvref_t<int&>>);
        static_assert(is_same_v<int, remove_cvref_t<int const>>);
        static_assert(is_same_v<int, remove_cvref_t<int const&>>);
    }
}
