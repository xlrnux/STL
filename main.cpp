#include <stdio.h>
#include "SimpleHashTable.h"
#include<cstring>

int main(void) {
    Map map1 = Map(); // 10007 is prime number ho!!!

    map1[418] = 32114;
    map1[9] = 514;
    map1[27] = 8917;
    map1[1031] = 86;
    map1[1031+10007] = 186;
    map1[1031+10007*2] = 286;
    map1[1031+10007*3] = 386;
    map1[1031+10007*4] = 486;
    printf("-----------------------\n");
    printf("Key:%d\t\tValue:%d\n", 418 , map1[418] );
    printf("Key:%d\t\tValue:%d\n", 9 , map1[9] );
    printf("Key:%d\t\tValue:%d\n", 27 , map1[27] );
    printf("Key:%d\tValue:%d\n", 1031 , map1[1031] );
    printf("Key:%d\tValue:%d\n", 1031+10007 , map1[1031+10007] );
    printf("Key:%d\tValue:%d\n", 1031+10007*2 , map1[1031+10007*2] );
    printf("Key:%d\tValue:%d\n", 1031+10007*3 , map1[1031+10007*3] );
    printf("Key:%d\tValue:%d\n", 1031+10007*4 , map1[1031+10007*4] );
    map1[1031] = 76;
    map1[1031+10007] = 176;
    map1[1031+10007*2] = 276;
    map1[1031+10007*3] = 376;
    map1[1031+10007*4] = 476;
    printf("Key:%d\tValue:%d\n", 1031 , map1[1031] );
    printf("Key:%d\tValue:%d\n", 1031+10007 , map1[1031+10007] );
    printf("Key:%d\tValue:%d\n", 1031+10007*2 , map1[1031+10007*2] );
    printf("Key:%d\tValue:%d\n", 1031+10007*3 , map1[1031+10007*3] );
    printf("Key:%d\tValue:%d\n", 1031+10007*4 , map1[1031+10007*4] );
    printf("Key:%d\tValue:%d\n", 1031 , map1[1031] );
    printf("Key:%d\tValue:%d\n", 1031+10007 , map1[1031+10007] );
    printf("Key:%d\tValue:%d\n", 1031+10007*2 , map1[1031+10007*2] );
    printf("Key:%d\tValue:%d\n", 1031+10007*3 , map1[1031+10007*3] );
    printf("Key:%d\tValue:%d\n", 1031+10007*4 , map1[1031+10007*4] );

    //int Prime[1000000] = {0,};



    return 0;
}