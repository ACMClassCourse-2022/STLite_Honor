#ifndef SJTU_ALGORITHM_HPP
#define SJTU_ALGORITHM_HPP

#include <functional>

namespace sjtu{

template<typename T>
void sort(T *begin, T *end, std::function<bool(const T&, const T&)> cmp){
    int len = end - begin;
    if (len <= 1) return ;
    T *i = begin, *j = end - 1;
    T pivot = *(begin + (len + 1) / 2 - 1);
    while (j - i >= 0){
        while (cmp(*i, pivot)) i++;
        while (cmp(pivot, *j)) j--;
        if (j - i >= 0){
            std::swap(*i, *j);
            i++, j--;
        }
    }
    if (j - begin > 0) sort(begin, i, cmp);
    if (end - i > 1) sort(i, end, cmp);
}

template<class T>
T *upper_bound(const T *begin, const T *end, const T &num){
    int l = -1, r = end - begin;
    while (l + 1 < r){
        int mid = (l + r) >> 1;
        if (num < *(begin + mid)) r = mid; else l = mid;
    }
    return const_cast<T *>(begin + r);
}

template<class T>
T *lower_bound(const T *begin, const T *end, const T &num){
    int l = -1, r = end - begin;
    while (l + 1 < r){
        int mid = (l + r) >> 1;
        if (num <= *(begin + mid)) r = mid; else l = mid;
    }
    return const_cast<T *>(begin + r);
}

};

#endif //SJTU_ALGORITHM_HPP
