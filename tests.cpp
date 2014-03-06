#include<iostream>
#include<algorithm>
#include<cmath>

#include "finitediff.h"
#include "tests.h"

using namespace std;

template<typename d> d finitediff_error(const int n) {
    const d h = 1/((d)n+1);

    vector<d> c(n, 1);

    vector<d> f(n);
    int i = 1;
    generate(f.begin(), f.end(), [&]{ return (i++)*h; });

    vector<d> out(n);

    resolve_finite_diff(n, c.begin(), f.begin(), out.rbegin());

    i = 1;
    d error = 0;
    for(d uh : out) {
        constexpr d e = exp(1);

        d x = (i++)*h;
        d u = e/(e*e-1)*(exp(-x)-exp(x))+x;
        d new_error = abs(u-uh);
        error = max(error, new_error);
    }

    return error;
}
template double finitediff_error<double>(const int n);
template float finitediff_error<float>(const int n);


template<typename d> int test_finitediff_error() {
    d error = 1;
    for(int n = 1; n < 22; n++) {
        d new_error = finitediff_error<d>((int)pow(2,n));

        if (new_error > error) {
            cout << "Max error for n = 2^" << n-1 << " : " << error << endl;
            cout << "Max error for n = 2^" << n << " : " << new_error << endl;
            cout << "Error not diminishing with h anymore" << endl;
            return n;
        }

        error = new_error;
    }

    return 0;
}
template int test_finitediff_error<float>();
template int test_finitediff_error<double>();
