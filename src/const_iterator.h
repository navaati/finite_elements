#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include<type_traits>

template<typename E> class ConstIterator {
private:
    const E m_val;
public:
    typedef std::input_iterator_tag iterator_category;
    typedef E value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    ConstIterator(E val) : m_val(val) {}

    const E operator*() const {
        return m_val;
    }

    const ConstIterator<E>& operator++() const {
        return *this;
    }
};

#endif // CONST_ITERATOR_H
