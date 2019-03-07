#include "litexx/string_view.h"
#include <doctest/doctest.h>
#include <string>
#include <string_view>

DOCTEST_TEST_CASE("string_view") {
    using namespace litexx;

    DOCTEST_SUBCASE("empty") {
        string_view empty;

        DOCTEST_CHECK(empty.empty());
        DOCTEST_CHECK(!empty);
        DOCTEST_CHECK_EQ(0, empty.size());
        DOCTEST_CHECK_EQ(nullptr, empty.data());
        DOCTEST_CHECK_EQ(empty.begin(), empty.end());
    }

    DOCTEST_SUBCASE("literal") {
        string_view literal = "literal";
        DOCTEST_CHECK(!literal.empty());
        DOCTEST_CHECK(literal);
        DOCTEST_CHECK_EQ(7, literal.size());
        DOCTEST_CHECK_NE(nullptr, literal.data());
        DOCTEST_CHECK_NE(literal.begin(), literal.end());
        DOCTEST_CHECK_EQ(literal, "literal");
    }

    DOCTEST_SUBCASE("length") {
        string_view length{"length", 6};

        DOCTEST_CHECK_EQ(6, length.size());
    }

    DOCTEST_SUBCASE("ctad") {
        char strghi[] = "abc";

        basic_string_view abc = "abc";
        basic_string_view def{"def", 3};
        basic_string_view ghi = strghi;
    }

    DOCTEST_SUBCASE("comparison") {
        string_view abc = "abc";
        string_view abcdef = "abcdef";
        string_view abcghi = "abcghi";

        DOCTEST_CHECK_EQ(abc, abc);
        DOCTEST_CHECK_NE(abcdef, abcghi);

        DOCTEST_CHECK_LT(abc, abcdef);
        DOCTEST_CHECK_LT(abcdef, abcghi);
    }

    DOCTEST_SUBCASE("conversion") {
        std::string str = "abc";
        std::string_view sv = str;

        static_assert(_detail::is_string_v<std::string>);
        static_assert(_detail::is_string_v<std::string_view>);

        basic_string_view<char> bv(str);
        basic_string_view<char> bv2(sv);
    }

    DOCTEST_SUBCASE("wide") {
        basic_string_view wide = L"test";
        constexpr basic_string_view cwide{L"test", 4};

        DOCTEST_CHECK_EQ(4, wide.size());
        DOCTEST_CHECK_EQ(4, cwide.size());
        DOCTEST_CHECK_EQ(cwide, wide);
    }
}
