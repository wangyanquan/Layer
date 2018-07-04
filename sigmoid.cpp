/*************************************************************************
	> File Name: sigmoid.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月28日 星期四 09时27分56秒
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cmath>
#define e 2.71828
#define s(x) (1.0 / (1.0 + pow(e, (-x))))

using namespace std;
int main() {
    double x;
    while(~scanf ("%lf", &x)) {
        printf ("%lf\n", s(x));
    }
    return 0;
}
