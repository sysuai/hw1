/*
  CEC17 Test Function Suite for Single Objective Optimization
  Noor Awad (email: noor0029@ntu.edu.sg) 
  Sep. 10th 2016
*/

// #include <WINDOWS.H>
#include <stdio.h>
#include <math.h>
// #include <cmath>
#include "PSO.h"
#include "DE.h"
#include <stdlib.h>
#include <sys/malloc.h> //mac 无法直接include malloc
#include <iostream>
using namespace std;

void cec17_test_func(double *, double *,int,int,int);
// class PSO;
double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;


int main()
{
    PSO test(10,20,1,2,2,0.5);
    for (int i = 0; i < 150000; i++)
    {
        test.run();
        if (test.gb_value == 100.0)
            break;
        cout << "iteration: " << i << endl;
        cout << "BEST: " << test.gb_value << endl;
        // cout << test.gb_X[0] << " " << test.gb_X[1] << endl;
        for (int j = 0; j < 10; j++)
        {
            //cout << test.x[j*2] << " " << test.x[j*2+1] << " " << test.f[j] << endl;
        }
        // cout << "BEST: " << test.gb_value << endl;
    }
    cout << "BEST: " << test.gb_value << endl;
    cout << test.gb_X[0] << " " << test.gb_X[1] << endl;
    
    DE de(1, 20);
    for (int i = 0; i < 20000; i++) {
        cout << de.run()  << endl;
    }
}

