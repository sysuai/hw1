#include <iostream>
#include <vector>
#include <ctime>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define URAND ((double)rand() / ((double)RAND_MAX + 1.0))

#define INITRAND srand(time(0))

//double *OShift,*M,*y,*z,*x_bound;
//int ini_flag=0,n_flag,func_flag,*SS;

void cec17_test_func(double *, double *,int,int,int);



class DE {

private:
    int r1, r2, r3; //三个选择出来的个体
    int jrand;
    int numofFE; //调用测试函数的次数
    int D; // 维度
    vector<double> Xl, Xu;
    int NP; //种群大小
    int Gmax; //迭代次数
    int minIndex; //最优个体
    int func_num; //问题编号
    double CR; //交叉概率
    double F; //扰动向量的缩放因子
    double min_value = DBL_MAX; //最优值
    vector<vector<double> > popul, next;
    vector<double> fitness;
    vector<double> U;

public:
    DE(int func_num, int dimension, int NP=80, double CR=0.9, double F=0.9) {
        this->func_num = func_num;
        this->D = dimension;
        Xl.resize(D);
        Xu.resize(D);
        for (int i = 0; i < D; i++) {
            Xl[i] = -100;
            Xu[i] = 100;
        }
        this->NP = NP; //种群大小
        this->Gmax = 300000; //迭代次数
        this->minIndex = -1; //最优个体
        this->CR = CR; //交叉概率
        this->F = CR; //扰动向量的缩放因子
        this->min_value = DBL_MAX; //最优值

        popul.resize(NP);
        next.resize(NP);
        fitness.resize(NP);
        U.resize(D);

        for (int i = 0; i < NP; i++) {
            popul[i].resize(D);
            next[i].resize(D);

            for (int j = 0; j < D; j++) {
                popul[i][j] = Xl[j] + (Xu[j] - Xl[j]) * URAND;
            }

            cec17_test_func(&popul[i][0], &fitness[i], D, 1, func_num);
        }
    }

    double run() {
        for (int i = 0; i < NP; i++) {
            do {
                r1 = (int)(NP*URAND);
            } while (r1 == i);

            do {
                r2 = (int)(NP*URAND);
            } while (r1 == r2 || r2 == i);

            do {
                r3 = (int)(NP*URAND);
            } while (r3 == i || r3 == r1 || r3 == r2);

            jrand = (int)(D*URAND);

            //变异和交叉操作
            for (int j = 0; j < D; j++) {
                if (URAND < CR || j == jrand) {
                    U[j] = popul[r3][j] + F * (popul[r1][j] - popul[r2][j]);
                }
                else {
                    U[j] = popul[i][j];
                }
            }

            //边界条件处理
            for (int j = 0; j < D; j++) {
                if (U[j] > Xu[j]) {
                    U[j] = Xu[j];
                }
                else if (U[j] < Xl[j]) {
                    U[j] = Xl[j];
                }
            }

            double ufitness;
            cec17_test_func(&U[0], &ufitness, D, 1, func_num);

            if (ufitness <= fitness[i]) {
                next[i] = U;
                fitness[i] = ufitness;
            }
            else {
                next[i] = popul[i];
            }
        }
        vector<vector<double> > temp = popul;
        popul = next;
        next = temp;

        for (int i = 0; i < NP; i++) {
            if (fitness[i] < min_value) {
                min_value = fitness[i];
                minIndex = i;
            }
        }
        return min_value;
    }

};

