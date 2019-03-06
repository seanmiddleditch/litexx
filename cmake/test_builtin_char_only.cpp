int main(int, char**) { auto l = __builtin_strlen("test") + __builtin_memcmp("abc", "def", 3) + __builtin_char_memchr("abc", 'a', 3); }
