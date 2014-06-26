#ifndef SAMPLER_ITERATOR_H
#define SAMPLER_ITERATOR_H

#include<iterator>

template<class unary_op, typename E> class SamplerIterator : public std::iterator<std::input_iterator_tag, E> {
private:
    const unary_op m_f;
    const E m_h;

    E m_x;
public:
    SamplerIterator(unary_op f, E h) : m_f(f), m_h(h), m_x(h) {}

    E operator*() {
        return m_f(m_x);
    }

    SamplerIterator<unary_op, E>& operator++() {
        m_x += m_h;
        return *this;
    }
};

#endif // SAMPLER_ITERATOR_H
