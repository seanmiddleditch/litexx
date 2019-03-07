#include "litexx/char_traits.h"
#include <doctest/doctest.h>

#if defined(LITEXX_USE_STRING_BUILTIN_CHAR_ONLY)
static_assert(litexx::char_traits<char>::length("test") == 4, "constexpr char_traits::length failed");
#endif

DOCTEST_TEST_CASE("char_traits<char>") {
    using namespace litexx;

    DOCTEST_SUBCASE("length") {
        char foo[] = "123";
        char const* bar = "1234567";

        DOCTEST_CHECK_EQ(3, char_traits<char>::length(foo));
        DOCTEST_CHECK_EQ(7, char_traits<char>::length(bar));
        DOCTEST_CHECK_EQ(5, char_traits<char>::length("12345"));
    }

    DOCTEST_SUBCASE("compare") {
        char abc[] = "abc";
        char abcdef[] = "abcdef";
        char abcghi[] = "abcghi";

        DOCTEST_CHECK_EQ(0, char_traits<char>::compare(abc, abcdef, 3));
        DOCTEST_CHECK_EQ(0, char_traits<char>::compare(abcdef, abcghi, 3));

        DOCTEST_CHECK_EQ(0, char_traits<char>::compare(abc, abcdef, 3));
        DOCTEST_CHECK_GT(0, char_traits<char>::compare(abcdef, abcghi, 6));
        DOCTEST_CHECK_LT(0, char_traits<char>::compare(abcghi, abcdef, 6));
    }
}
