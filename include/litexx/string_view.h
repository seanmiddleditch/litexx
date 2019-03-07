// litexx - Liteweight C++ utility library
//
// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non - commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org/>
//
// Authors:
//   Sean Middleditch <sean@middleditch.us>

#if !defined(_guard_LITEXX_STRING_VIEW_H)
#define _guard_LITEXX_STRING_VIEW_H
#pragma once

#include "litexx/char_traits.h"
#include "litexx/type_traits.h"

namespace litexx {
    namespace _detail {
        template <typename, typename = void>
        struct has_string_members { static constexpr bool value = false; };

        template <typename T>
        struct has_string_members<T, void_t<decltype(declval<T>().data()), decltype(declval<T>().size())>> { static constexpr bool value = true; };

        template <typename T>
        constexpr bool is_string_v = has_string_members<T>::value;
    }

    template <typename T>
    class basic_string_view {
    public:
        using value_type = T const;
        using pointer = value_type*;
        using size_type = std::size_t;
        using const_iterator = pointer;

        constexpr basic_string_view() noexcept = default;
        constexpr basic_string_view(const_iterator first, const_iterator last) noexcept : _begin(first), _end(last) {}
        constexpr basic_string_view(pointer nstr, size_type size) noexcept : _begin(nstr), _end(nstr + size) {}
        constexpr basic_string_view(pointer zstr) noexcept : _begin(zstr), _end(zstr != nullptr ? zstr + litexx::char_traits<T>::length(zstr) : zstr) {}

        template <typename S, typename = enable_if_t<_detail::is_string_v<S>>>
        constexpr basic_string_view(S const& str) noexcept : _begin(str.data()), _end(_begin + str.size()) {}

        constexpr pointer data() const noexcept { return _begin; }
        constexpr size_type size() const noexcept { return _end - _begin; }

        [[nodiscard]] constexpr bool empty() const noexcept { return _begin == _end; }
        constexpr explicit operator bool() const noexcept { return _begin != _end; }

        constexpr const_iterator begin() const noexcept { return _begin; }
        constexpr const_iterator end() const noexcept { return _end; }

        constexpr value_type operator[](size_type index) const noexcept { return _begin[index]; }

        constexpr basic_string_view substr(size_type first, size_type length) const noexcept {
            return basic_string_view(_begin + first, _begin + first + length);
        }

        constexpr bool operator==(basic_string_view rhs) const noexcept {
            size_type length = _end - _begin;
            return length == rhs._end - rhs._begin && litexx::char_traits<T>::compare(_begin, rhs._begin, length) == 0;
        }

        constexpr bool operator!=(basic_string_view rhs) const noexcept {
            size_type length = _end - _begin;
            return length != rhs._end - rhs._begin || litexx::char_traits<T>::compare(_begin, rhs._begin, length) != 0;
        }

        constexpr bool operator<(basic_string_view rhs) const noexcept {
            size_type length = _end - _begin;
            size_type other_length = rhs._end - rhs._begin;
            size_type min_length = length < other_length ? length : other_length;
            int rs = litexx::char_traits<T>::compare(_begin, rhs._begin, min_length);
            return rs < 0 || rs == 0 && length < other_length;
        }

    private:
        pointer _begin = nullptr;
        pointer _end = nullptr;
    };

    template <typename T>
    basic_string_view(T const*, T const*)->basic_string_view<T>;
    template <typename T>
    basic_string_view(T const*, std::size_t)->basic_string_view<T>;
    template <typename T>
    basic_string_view(T const*)->basic_string_view<T>;

    using string_view = basic_string_view<char>;
} // namespace litexx

#endif // !defined(_guard_LITEXX_STRING_VIEW_H)
