#include "litexx/string_view.h"
#include <doctest/doctest.h>

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
        basic_string_view abc = "abc";
        basic_string_view def{"def", 3};
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
}
