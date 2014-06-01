#ifndef FINITEDIFF_H
#define FINITEDIFF_H

#include<iterator>
#include<type_traits>

#include "thomas_algo.h"
#include "const_iterator.h"

template<class It> class FiniteDiffIterator {
private:
    typedef typename std::iterator_traits<It>::value_type E;
    It m_it;
    const E m_h2;
public:
    typedef std::input_iterator_tag iterator_category;
    typedef E value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    FiniteDiffIterator(It it, E h2) : m_it(it), m_h2(h2) {}

    E operator*() {
        return 2/m_h2 + *m_it;
    }

    FiniteDiffIterator<It>& operator++() {
        ++m_it;
        return *this;
    }
};

template<class InputItA, class InputItB, class OutputIt>
OutputIt resolve_finite_diff(const int n, InputItA c, InputItB f, OutputIt out) {
    typedef typename std::iterator_traits<InputItA>::value_type E;

    const E h = 1/((E)n+1);
    const E h2 = h*h;
    const ConstIterator<E> lower_upper(-1/h2);

    return thomas_algo(n, lower_upper, FiniteDiffIterator<InputItA>(c, h2), lower_upper, f, out);
}

#endif // FINITEDIFF_H
