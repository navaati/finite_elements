#ifndef THOMAS_ALGO_H
#define THOMAS_ALGO_H

#include<vector>
#include<utility>

template<typename E> std::pair<E,E> make_thomas_pair(E lower_i, E diag_i, E upper_i, E right_i, std::pair<E,E> pair_im1) {
    E denominator = diag_i-lower_i*pair_im1.first;

    return std::make_pair(upper_i/denominator, (right_i-lower_i*pair_im1.second)/denominator);
}

// Writes the result in reverse order !
template<class LowerIt, class DiagIt, class UpperIt, class RightIt, class OutputIt>
OutputIt thomas_algo(const int n, LowerIt lower, DiagIt diag, UpperIt upper, RightIt right, OutputIt out) {
    typedef typename std::iterator_traits<UpperIt>::value_type E;

    auto scratch = std::vector<std::pair<E,E>>(n-1);

    auto it = scratch.begin();

    *it = make_thomas_pair((E)0, *diag, *upper, *right, std::make_pair((E)0,(E)0));
    ++upper; ++diag; ++right;

    while(it != scratch.end()-1) {
        std::pair<E,E> pair_im1 = *it;
        ++it;

        *it = make_thomas_pair(*lower, *diag, *upper, *right, pair_im1);
        ++lower; ++diag; ++upper; ++right;
    }
    // from now on upper is past-the-end, illegal to dereference

    E x_ip1 = make_thomas_pair(*lower, *diag, (E)0, *right, *it).second; // this is x_n = b_n
    *out = x_ip1;
    ++out;

    while(it != scratch.begin()-1) {
        E x_i = it->second - it->first*x_ip1;
        *out = x_i;
        x_ip1 = x_i;
        ++out;
        --it;
    }

    return out;
}

#endif // THOMAS_ALGO_H
