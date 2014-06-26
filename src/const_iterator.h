#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include<iterator>

template<typename E> class ConstIterator : public std::iterator<std::input_iterator_tag, E> {
private:
    const E m_val;

public:
    ConstIterator(E val) : m_val(val) {}

    const E operator*() const {
        return m_val;
    }

    const ConstIterator<E>& operator++() const {
        return *this;
    }
};

#endif // CONST_ITERATOR_H
