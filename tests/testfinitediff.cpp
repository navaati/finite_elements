#include<iostream>
#include<iterator>
#include<algorithm>
#include<cmath>
#include <QtTest/QtTest>

#include "const_iterator.h"
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
private slots:
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
