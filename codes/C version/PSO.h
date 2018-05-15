/*
  CEC17 Test Function Suite for Single Objective Optimization
  Noor Awad (email: noor0029@ntu.edu.sg) 
  Sep. 10th 2016
*/

// #include <WINDOWS.H>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/malloc.h>
#define RANDOM ((float)rand() / (float)RAND_MAX)
#define INF 1.0e99



void cec17_test_func(double *, double *,int,int,int);

class PSO{
public:
    int iter; //迭代次数
    double* x; //种群位置
    double* V; //种群速度
    double* f; //最优解
    double c1; //个体学习因子
    double c2; //全局学习因子
    int nx; //维度
    int mx; //种群数量
    double gb_value; //全局最优值
    double* gb_X; //全局最优位置
    double* p_value; //粒子经过的最优值
    double* p_X; //粒子经过的最优位置
    double Vmax; //速度的最大值
    double w; //惯性因子
    int func_num;
    
    PSO(int nx, int mx, int func_num, double c1, double c2, double w)
    {
        // srand(time(NULL));
        this -> Vmax = 200;
        this -> iter = 0;
        this -> nx = nx;
        this -> mx = mx;
        this -> c1 = c1;
        this -> c2 = c2;
        this -> x = new double[mx*nx];
        this -> V = new double[mx*nx];
        this -> f = new double[mx];
        this -> gb_X = new double[nx];
        this -> p_value = new double[mx];
        this -> p_X = new double[mx*nx];
        this -> w = w;
        this -> func_num = func_num;
        this -> gb_value = INF;
        for (int i = 0; i < mx*nx; i++)
        {
            // srand((unsigned)i);
            x[i] = 100*RANDOM;
            // printf("%f\n",x[i]);
            V[i] = 10*RANDOM;
            p_X[i] = x[i];
        }
        for (int i = 0; i < mx; i++)
        {
            p_value[i] = INF;
        }
        for (int i = 0; i < nx; i++)
            gb_X[i] = x[i];
    }
    
    void run()
    {
        updateV();
        updateX();
        iter++;
    }
    
    void updateV()
    {
        for (int i = 0; i < mx*nx; i++)
        {
            // srand((unsigned)i);
            V[i] = w*V[i] + c1*RANDOM*(p_X[i] - x[i]) + c2*RANDOM*(gb_X[i%nx] - x[i]);
            // printf("%f, %f\n",gb_X[i%nx], x[i]);
            if (V[i] > Vmax)
                V[i] = Vmax;
            if (V[i] < -Vmax)
                V[i] = -Vmax;
        }
    }
    
    void updateX()
    {
        //更新粒子位置
        for (int i = 0; i < mx*nx; i++)
        {
            x[i] = x[i] + V[i];
            /*if (x[i] > 100)
                x[i] = 100;
            if (x[i] < -100)
                x[i] = -100;*/
        }
        //更新局部最优
        cec17_test_func(x,f,nx,mx,func_num);
        for (int i = 0; i < mx; i++)
        {
            if (f[i] < p_value[i])
            {
                for (int j = 0; j < nx; j++)
                    p_X[i*nx+j] = x[i*nx+j];
                p_value[i] = f[i];
            }
        }
        // 更新全局最优
        for (int i = 0; i < mx; i++)
        {
            if (p_value[i] < gb_value)
            {
                for (int j = 0; j < nx; j++)
                    gb_X[j] = p_X[i*nx+j];
                gb_value = p_value[i];
            }
        }
    }
    
    ~PSO()
    {
        delete[] x;
        delete[] V;
        delete[] f;
        delete[] gb_X;
        delete[] p_value;
        delete[] p_X;
    }
    
};


