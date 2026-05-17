#ifndef LGF_DEBUG_HPP
#define LGF_DEBUG_HPP

#include <bits/stdc++.h>

using namespace std;

namespace lgf_dbg {

// --- Type traits ---

template<typename T, typename = void>
struct is_iterable : false_type {};
template<typename T>
struct is_iterable<T, void_t<decltype(begin(declval<T>())),
                             decltype(end(declval<T>()))>>
    : true_type {};

template<typename T, typename = void>
struct is_tuple_like : false_type {};
template<typename T>
struct is_tuple_like<T, void_t<decltype(tuple_size<T>::value)>>
    : true_type {};

template<typename T>
constexpr bool is_string_like_v =
    is_same_v<decay_t<T>, string> ||
    is_same_v<decay_t<T>, string_view> ||
    is_same_v<decay_t<T>, const char*> ||
    is_same_v<decay_t<T>, char*>;

template<typename T> struct is_stack : false_type {};
template<typename... A> struct is_stack<stack<A...>> : true_type {};

template<typename T> struct is_queue : false_type {};
template<typename... A> struct is_queue<queue<A...>> : true_type {};

template<typename T> struct is_pq : false_type {};
template<typename... A> struct is_pq<priority_queue<A...>> : true_type {};

template<typename T> struct is_bitset : false_type {};
template<size_t N> struct is_bitset<bitset<N>> : true_type {};

template<typename T> struct is_optional : false_type {};
template<typename T> struct is_optional<optional<T>> : true_type {};

// --- Forward declaration ---

template<typename T>
void print(const T& x);

// --- __int128 helper ---

#ifdef __SIZEOF_INT128__
inline void print_128(__int128 x) {
    if (x < 0) { cerr << '-'; x = -x; }
    if (x > 9) print_128(x / 10);
    cerr << static_cast<char>('0' + static_cast<long long>(x % 10));
}
inline void print_128(unsigned __int128 x) {
    if (x > 9) print_128(x / 10);
    cerr << static_cast<char>('0' + static_cast<long long>(x % 10));
}
#endif

// --- Tuple helper (fold expression) ---

template<typename T, size_t... I>
void print_tuple(const T& t, index_sequence<I...>) {
    ((cerr << (I == 0 ? "" : ", "), print(get<I>(t))), ...);
}

// --- Main print function ---

template<typename T>
void print(const T& x) {
    using D = decay_t<T>;

    if constexpr (is_same_v<D, bool>) {
        cerr << (x ? "true" : "false");
    }
    else if constexpr (is_same_v<D, char>) {
        cerr << '\'' << x << '\'';
    }
    else if constexpr (is_string_like_v<T>) {
        cerr << '"' << x << '"';
    }
    else if constexpr (is_arithmetic_v<D>) {
        cerr << x;
    }
#ifdef __SIZEOF_INT128__
    else if constexpr (is_same_v<D, __int128>) {
        print_128(x);
    }
    else if constexpr (is_same_v<D, unsigned __int128>) {
        print_128(x);
    }
#endif
    else if constexpr (is_optional<D>::value) {
        if (x.has_value()) print(*x);
        else cerr << "nullopt";
    }
    else if constexpr (is_bitset<D>::value) {
        cerr << x;
    }
    else if constexpr (is_stack<D>::value) {
        auto cp = x;
        vector<typename D::value_type> v;
        while (!cp.empty()) { v.push_back(cp.top()); cp.pop(); }
        reverse(v.begin(), v.end());
        print(v);
    }
    else if constexpr (is_queue<D>::value) {
        auto cp = x;
        vector<typename D::value_type> v;
        while (!cp.empty()) { v.push_back(cp.front()); cp.pop(); }
        print(v);
    }
    else if constexpr (is_pq<D>::value) {
        auto cp = x;
        vector<typename D::value_type> v;
        while (!cp.empty()) { v.push_back(cp.top()); cp.pop(); }
        print(v);
    }
    else if constexpr (is_iterable<D>::value) {
        cerr << '{';
        bool first = true;
        for (auto&& elem : x) {
            if (!first) cerr << ", ";
            first = false;
            print(elem);
        }
        cerr << '}';
    }
    else if constexpr (is_tuple_like<D>::value) {
        cerr << '(';
        print_tuple(x, make_index_sequence<tuple_size_v<D>>{});
        cerr << ')';
    }
    else {
        cerr << x;
    }
}

// --- Variadic print ---

inline void print_all() {}

template<typename T, typename... Rest>
void print_all(const T& first, const Rest&... rest) {
    print(first);
    if constexpr (sizeof...(rest) > 0) {
        cerr << ", ";
        print_all(rest...);
    }
}

// --- Debug output with formatting ---

template<typename... Args>
void debug_impl(const char* names, long long line, const Args&... args) {
    cerr << "\033[34m" << "[L" << line << "] "
         << "[" << names << "]"
         << "\033[0m" << " = "
         << "\033[33m" << "[";
    print_all(args...);
    cerr << "]" << "\033[0m" << endl;
}

} // namespace lgf_dbg

#ifdef LOCAL
#define debug(...) lgf_dbg::debug_impl(#__VA_ARGS__, __LINE__, __VA_ARGS__)
#else
#define debug(...) ((void)0)
#endif

#endif // LGF_DEBUG_HPP
