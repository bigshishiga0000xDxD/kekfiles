#pragma once 

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define debug(x...) std::cout << #x << " = ["; _print(x); std::cout << "]" << std::endl;

template <typename T>
concept Container = std::is_same_v<T, std::vector<typename T::value_type>> ||
                    std::is_same_v<T, std::deque<typename T::value_type>> ||
                    std::is_same_v<T, std::set<typename T::value_type>> ||
                    std::is_same_v<T, std::unordered_set<typename T::value_type>> ||
                    std::is_same_v<T, std::multiset<typename T::value_type>> ||
                    std::is_same_v<T, std::map<typename T::key_type, typename T::mapped_type>> ||
                    std::is_same_v<T, std::unordered_map<typename T::key_type, typename T::mapped_type>>;

template <Container Iterable>
std::ostream& operator<<(std::ostream& out, const Iterable& container);

template <typename T, typename V>
std::ostream& operator<<(std::ostream& out, const std::pair<T, V>& pair);

template <typename... T>
std::ostream& operator<<(std::ostream& out, std::tuple<T...> tuple);

template <typename T>
std::ostream& operator<<(std::ostream& out, std::queue<T> queue);

template <typename T, typename V>
std::ostream& operator<<(std::ostream& out, const std::pair<T, V>& pair) {
    out << "(" << pair.first << ", " << pair.second << ")";
    return out;
}

template <Container Iterable>
std::ostream& operator<<(std::ostream& out, const Iterable& container) {
    out << "(";
    bool first = true;
    for (const auto& elem : container) {
        if (!first) {
            out << ", ";
        }
        out << elem;
        first = false;
    }
    out << ")";
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, std::queue<T> queue) {
    std::vector<T> vector;
    while (!queue.empty()) {
        vector.push_back(queue.front());
        queue.pop();
    }
    out << vector;
    return out;
}

template <typename... T, std::size_t... Ind>
void _print_tuple(std::ostream& out, std::tuple<T...> tuple, std::index_sequence<Ind...>) {
    ((out << (Ind == 0 ? "" : ", ") << std::get<Ind>(tuple)), ...);
}

template <typename... T>
std::ostream& operator<<(std::ostream& out, std::tuple<T...> tuple) {
    out << "(";
    _print_tuple(out, tuple, std::index_sequence_for<T...>{});
    out << ")";
    return out;
}


void _print() {
}

template <typename Head, typename... Tail>
void _print(Head head, Tail... tail) {
    std::cout << head;
    if (sizeof...(Tail)) {
        std::cout << ", ";
        _print(tail...);
    }
}


