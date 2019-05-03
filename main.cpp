#include <stdio.h>
#include "SimpleHashTable.h"
#include<cstring>


int main(void) {
    Map map1;

    map1[418] = 32114;
    map1[9] = 514;
    map1[27] = 8917;
    map1[28] = 86;
    map1[28+map1.GetTableSize()] = 186;
    map1[28+map1.GetTableSize()*2] = 286;
    map1[28+map1.GetTableSize()*3] = 386;
    map1[28+map1.GetTableSize()*4] = 486;
    printf("-----------------------\n");
    printf("Key:%d\t\tValue:%d\n", 418 , map1[418] );
    printf("Key:%d\t\tValue:%d\n", 9 , map1[9] );
    printf("Key:%d\t\tValue:%d\n", 27 , map1[27] );
    printf("Key:%d\tValue:%d\n", 28 , map1[28] );
    printf("Key:%d\tValue:%d\n", 28+map1.GetTableSize() , map1[28+map1.GetTableSize()] );
    printf("Key:%d\tValue:%d\n", 28+map1.GetTableSize()*2 , map1[28+map1.GetTableSize()*2] );
    printf("Key:%d\tValue:%d\n", 28+map1.GetTableSize()*3 , map1[28+map1.GetTableSize()*3] );
    printf("Key:%d\tValue:%d\n", 28+map1.GetTableSize()*4 , map1[28+map1.GetTableSize()*4] );
    map1[28] = 76;
    map1[28+map1.GetTableSize()] = 176;
    map1[28+map1.GetTableSize()*2] = 276;
    map1[28+map1.GetTableSize()*3] = 376;
    map1[28+map1.GetTableSize()*4] = 476;
    printf("Key:%d\tValue:%d\n", 28 , map1[28] );
    printf("Key:%d\tValue:%d\n", 28+map1.GetTableSize() , map1[28+map1.GetTableSize()] );
    printf("Key:%d\tValue:%d\n", 28+map1.GetTableSize()*2 , map1[28+map1.GetTableSize()*2] );
    printf("Key:%d\tValue:%d\n", 28+map1.GetTableSize()*3 , map1[28+map1.GetTableSize()*3] );
    printf("Key:%d\tValue:%d\n", 28+map1.GetTableSize()*4 , map1[28+map1.GetTableSize()*4] );
    printf("Key:%d\tValue:%d\n", 28 , map1[28] );
    printf("Key:%d\tValue:%d\n", 28+map1.GetTableSize() , map1[28+map1.GetTableSize()] );
    printf("Key:%d\tValue:%d\n", 28+map1.GetTableSize()*2 , map1[28+map1.GetTableSize()*2] );
    printf("Key:%d\tValue:%d\n", 28+map1.GetTableSize()*3 , map1[28+map1.GetTableSize()*3] );
    printf("Key:%d\tValue:%d\n", 28+map1.GetTableSize()*4 , map1[28+map1.GetTableSize()*4] );

    //int Prime[1000000] = {0,};

    map1[282] = 76;
    map1[282+map1.GetTableSize()] = 176;
    map1[282+map1.GetTableSize()*2] = 276;
    map1[282+map1.GetTableSize()*3] = 376;
    map1[28+map1.GetTableSize()*4] = 476;

    return 0;
}