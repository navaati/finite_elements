#ifndef FINITEDIFF_H
#define FINITEDIFF_H

#include<vector>
#include<iterator>

// Writes the result in reverse order !
template<class InputItA, class InputItB, class OutputIt>
OutputIt resolve_finite_diff(const int n, InputItA c, InputItB f, OutputIt out) {
    typedef typename std::iterator_traits<InputItA>::value_type e;

    const e h = 1/((e)n+1);
    const e h2 = h*h;

    std::vector<std::pair<e,e>> scratch(n+1);

    for(auto it = scratch.begin(); it != scratch.end()-1; ) {
        e common = 1/(2+h2*(*c++)+it->first);
        *++it = std::make_pair(-1*common,(h2*(*f++)+it->second)*common);
    }

    e x_i = 0;
    for (auto it = scratch.rbegin(); it != scratch.rend()-1; it++) {
        x_i = it->second - it->first*x_i;
        *out++ = x_i;
    }

    return out;
}

#endif // FINITEDIFF_H
