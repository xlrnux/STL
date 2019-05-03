#include <stdio.h>
#include "SimpleHashTable.h"

void MapExp(){
    Map map1;
    map1.Stats();


    map1[418] = 32114;
    map1[9] = 514;
    map1[27] = 8917;
    map1[28] = 86;
    map1[28+map1.GetTableSize()] = 186;
    map1[28+map1.GetTableSize()*2] = 286;
    map1[28+map1.GetTableSize()*3] = 386;
    map1[28+map1.GetTableSize()*4] = 486;
    map1.FullPrint();

    map1[28] = 76;
    map1[28+map1.GetTableSize()] = 176;
    map1[28+map1.GetTableSize()*2] = 276;
    map1[28+map1.GetTableSize()*3] = 376;
    map1[28+map1.GetTableSize()*4] = 476;
    map1.FullPrint();

    map1[282] = 76;
    map1[282+map1.GetTableSize()*2] = 266;
    map1[282+map1.GetTableSize()*3] = 366;
    map1[282+map1.GetTableSize()] = 166;
    map1[28+map1.GetTableSize()*4] = 466;
    map1.FullPrint();
}
int main(void) {

    return 0;
}