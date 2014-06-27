#ifndef INTEGRATOR_H
#define INTEGRATOR_H

template<typename E, class unary_op> E integrate(unary_op f, E start, E stop, int steps) {
    const E step = (stop-start)/(E)steps;

    E s = 0;
    for(E x = start+step/2; x < stop; x += step) {
        s += f(x)*step;
    }

    return s;
}

#endif // INTEGRATOR_H
