#include<iostream>

#include "finitediff.h"

using namespace std;

int main(int argc, char *argv[])
{
    int n = 4;
    double c[] = {3, 5, 1, 8};
    double f[] = {1, 9, 6, 2};
    auto out = ostream_iterator<double>(cout, " ");
    resolve_finite_diff(n, c, f, out);
    
    return 0;
}
