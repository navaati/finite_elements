#include<iostream>
#include<iterator>
#include<algorithm>
#include<cmath>
#include <QtTest/QtTest>

#include "const_iterator.h"
#include "thomas_algo.h"
#include "finitediff.h"

using namespace std;

template<typename d> d finitediff_error(const int n) {
    const d h = 1/((d)n+1);

    const ConstIterator<d> c(1);

    vector<d> f(n);
    int i = 1;
    generate(f.begin(), f.end(), [&]{ return (i++)*h; });

    vector<d> out(n);

    resolve_finite_diff(n, c, f.begin(), out.rbegin());

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


template<typename d> unsigned finitediffPrecisionLossRank() {
    d old_error;
    d error = 1;
    unsigned n = 0;

    do {
        n++;
        old_error = error;
        error = finitediff_error<d>((int)pow(2,n));
    } while(error < old_error);

    cout << "Max error for n = 2^" << n-1 << " : " << old_error << endl;
    cout << "Max error for n = 2^" << n << " : " << error << endl;
    cout << "Error not diminishing with h anymore" << endl;

    return n;
}
template unsigned finitediffPrecisionLossRank<float>();
template unsigned finitediffPrecisionLossRank<double>();

class TestFiniteDiff: public QObject
{
    Q_OBJECT
private:
    void eqn_error(double& max_error, double a, double b, double c, double x_im1, double x_i, double x_ip1, double r) {
        double new_error = abs(a*x_im1 + b*x_i + c*x_ip1 - r);
        max_error = max(max_error, new_error);
    }

private slots:
    void maxThomasAlgoError() {
        constexpr int n = 4;
        const double lower[n-1] = {4, 8, 12};
        const double diag[n] = {1, 5, 9, 13};
        const double upper[n-1] = {2, 6, 10};
        const double right[n] = {300, 700, 1100, 1400};

        vector<double> x(n);
        thomas_algo(n, lower, diag, upper, right, x.begin());

        double max_error = 0;
        const double* lower_it = lower;
        const double* diag_it = diag;
        const double* upper_it = upper;
        const double* right_it = right;
        auto x_it = x.rbegin(); // was written in reverse !

        eqn_error(max_error, 0, *diag_it, *upper_it, 0, *x_it, *(x_it+1), *right_it);
        ++diag_it; ++upper_it; ++right_it;
        ++x_it;

        while(x_it != x.rend()-1) {
            eqn_error(max_error, *lower_it, *diag_it, *upper_it, *(x_it-1), *x_it, *(x_it+1), *right_it);
            ++lower_it, ++diag_it; ++upper_it; ++right_it;
            ++x_it;
        }

        eqn_error(max_error, *lower_it, *diag_it, 0, *(x_it-1), *x_it, 0, *right_it);

        cout << "Thomas algo max error : " << max_error << endl;

        QVERIFY(max_error < 5e-13);
    }

    void maxRankFloat() {
        QVERIFY(finitediffPrecisionLossRank<float>() > 7);
    }
    void maxRankDouble() {
        QVERIFY(finitediffPrecisionLossRank<double>() > 13);
    }
};
QTEST_MAIN(TestFiniteDiff)
#include "testfinitediff.moc"

void showSimpleFiniteDiff() {
    int n = 4;
    double c[] = {3, 5, 1, 8};
    double f[] = {1, 9, 6, 2};
    auto out = ostream_iterator<double>(cout, " ");
    resolve_finite_diff(n, c, f, out);
}
