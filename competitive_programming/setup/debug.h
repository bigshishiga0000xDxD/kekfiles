#pragma once 

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define debug(x...) std::cout << #x << " = "; _print(x); std::cout << endl;

void _print() {}
template <typename T, typename... V>
void _print(T t, V... v) {
    std::cout << t;
    if (sizeof...(v)) {
        std::cout << ", ";
    }
    _print(v...);
}

template <typename Ostream, typename T>
Ostream& operator<<(Ostream& os, std::queue <T> q) {
    std::vector <T> v;
    while (!q.empty()) {
        v.push_back(q.front());
        q.pop();
    }
    os << v;
    return os;
}

template <typename Ostream, typename T>
Ostream& operator<<(Ostream& os, std::deque <T> q) {
    std::vector <T> v;
    while (!q.empty()) {
        v.push_back(q.front());
        q.pop_front();
    }
    os << v;
    return os;
}

template<typename Ostream, typename Cont>
typename std::enable_if <std::is_same <Ostream, std::ostream>::value, Ostream&>::type 
operator<<(Ostream& os, const Cont& v){
    os << "[";
    bool first = true;
    
    for (auto x : v) {
        if (!first) {
            os << ", ";
        }
        os << x;
        first = false;
    }
    
    return os << "]";

}




template<typename Ostream, typename ...Ts>
Ostream& operator<<(Ostream& os, const std::pair<Ts...>& p){
	return os << "{" << p.first << ", " << p.second << "}";
}

namespace aux {
    template <std::size_t...> struct seq{};

    template <std::size_t N, std::size_t... Is>
    struct gen_seq : gen_seq<N-1, N-1, Is...> {};

    template <std::size_t... Is>
    struct gen_seq<0, Is...> : seq<Is...> {};

    template <class Ch, class Tr, class Tuple, std::size_t... Is>
    void print_tuple(std::basic_ostream<Ch,Tr>& os, Tuple const& t, seq<Is...>){
        using swallow = int[];
        (void)swallow {0, (void(os << (Is == 0 ?  "" : ", ") << std::get<Is>(t)), 0)...};
    }
}

template<class Ch, class Tr, class... Args>
auto operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t) -> std::basic_ostream<Ch, Tr>& {
    os << "(";
    aux::print_tuple(os, t, aux::gen_seq<sizeof...(Args)>());
    return os << ")";
}
