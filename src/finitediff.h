#ifndef FINITEDIFF_H
#define FINITEDIFF_H

#include<iterator>

#include "thomas_algo.h"
#include "sampler_iterator.h"
#include "const_iterator.h"

template<class FunctorC, class FunctorF, class OutputIt>
OutputIt resolve_finite_diff(const int n, FunctorC c, FunctorF f, OutputIt out) {
    typedef typename std::iterator_traits<OutputIt>::value_type E;

    const E h = 1/((E)n+1);
    const E h2 = h*h;
    const ConstIterator<E> lower_upper(-1/h2);

    auto finite_diff_lambda = [h2, &c](E x){ return 2/h2 + c(x); };

    return thomas_algo(n, lower_upper, SamplerIterator<decltype(finite_diff_lambda), E>(finite_diff_lambda, h), lower_upper, SamplerIterator<FunctorF, E>(f, h), out);
}

#endif // FINITEDIFF_H
