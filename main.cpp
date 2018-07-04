/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年05月12日 星期六 14时24分10秒
 ************************************************************************/

#include<iostream>
#include "hanshu.h"
#include<cstdio>
int main() {
    float y_zhan[3] = {1, 0, 0};
    float y_wo[3] = {0, 1, 0};
    float y_zhi[3] = {0, 0, 1};
    Conlayer l1(1, 50, 50);
    Conlayer l2(5, 48, 48, 1, 3, 3);
    l2.init();
    Poollayer l3(5, 24, 24, 2, 2);
    Conlayer l4(5, 22, 22, 5, 3, 3);
    l4.init();
    Poollayer l5(5, 11, 11, 2, 2);
    Layer l6(100, 605);
    Layer l7(3, 100);
    l6.init();
    l7.init();
    for (int i = 0; i < 50; i++) {
        FILE *f_zhan = fopen("./zhan.txt", "r");
        FILE *f_wo = fopen("./wo.txt", "r");
        FILE *f_zhi = fopen("./zhi.txt", "r");
        for (int j = 0; j < 100; j++) {
            read_con(f_zhan, l1);
            (l1 > l2 > l3 > l4 > l5 > l6) > l7;
            //  l5.output_out();
            //  l6.output_a();
            printf ("1------------\n");
            l7.output_a();
            count_layer3(l7, l6, y_zhan);
            count_layer2(l6, l7, l5);
            count_pool_layer(l5, l6);
            count_conlayer_pool(l4, l5);
            count_wb(l4, l3);
            count_pool_con(l3, l4);
            count_conlayer_pool(l2, l3);
            count_wb(l2, l1);
    
            read_con(f_wo, l1);
            (l1 > l2 > l3 > l4 > l5 > l6) > l7;
            //  l5.output_out();
            //  l6.output_a();
            printf ("2------------\n");
            l7.output_a();
            count_layer3(l7, l6, y_wo);
            count_layer2(l6, l7, l5);
            count_pool_layer(l5, l6);
            count_conlayer_pool(l4, l5);
            count_wb(l4, l3);
            count_pool_con(l3, l4);
            count_conlayer_pool(l2, l3);
            count_wb(l2, l1);
        
            read_con(f_zhi, l1);
            (l1 > l2 > l3 > l4 > l5 > l6) > l7;
            //  l5.output_out();
            //  l6.output_a();
            printf ("3------------\n");
            l7.output_a();
            count_layer3(l7, l6, y_zhi);
            count_layer2(l6, l7, l5);
            count_pool_layer(l5, l6);
            count_conlayer_pool(l4, l5);
            count_wb(l4, l3);
            count_pool_con(l3, l4);
            count_conlayer_pool(l2, l3);
            count_wb(l2, l1);
        
            update_wb(l2);
            update_wb(l4);
            update(l6);
            update(l7);
        }
        fclose(f_zhan);
        fclose(f_wo);
        fclose(f_zhi);

    }
    return 0;
}
