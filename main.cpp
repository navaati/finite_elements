#include<iostream>

#include "finitediff.h"
#include "tests.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "With float :" << endl;
    test_finitediff_error<float>();
    cout << endl << "With double :" << endl;
    test_finitediff_error<double>();
    
    return 0;
}
