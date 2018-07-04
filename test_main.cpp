/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年05月12日 星期六 14时24分10秒
 ************************************************************************/

#include<iostream>
#include "hanshu.h"
#include<cstdio>
#include<cmath>
void set_0(float*p, int n) {
    for (int i = 0; i < n; i++) {
        if (i < n / 2) {
            p[i] = 0;
        }
        else {
            p[i] = 1;
        }
    }
}
void set_1(float*p, int n) {
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            p[i] = 1;
        }
        else {
            p[i] = 0;
        }
    }
}
int main() {
    float y_zhan[2] = {1, 0};
    float y_wo[2] = {0, 1};
    
    Layer l1(500);
    Layer l2(100, 500);
    Layer l3(2, 100);
    l2.init();
//    l3.init();
    for (int i = 0; i < 10000; i++) {
        set_0(l1.a, l1.row);
        l1 >> l2 > l3;
      //  l3.output_a();
        count_layer3(l3, l2, y_zhan);
        count_layer2(l2, l3, l1);
        update(l2);
        update(l3);
      //  l3.output_a();

        set_1(l1.a, l1.row);
        l1 >> l2 > l3;
     //   l3.output_a();
        count_layer3(l3, l2, y_wo);
        count_layer2(l2, l3, l1);
        update(l2);
        update(l3);
      //  l3.output_a();
    }
    printf("ok\n");

    set_0(l1.a, l1.row);
    l1 >> l2 > l3;
    l3.output_a();

    set_1(l1.a, l1.row);
    l1 >> l2 > l3;
    l3.output_a();
    return 0;
}
