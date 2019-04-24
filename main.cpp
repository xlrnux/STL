#include <stdio.h>
#include "SimpleHashTable.h"


int main(void) {
    Map map1 = Map(193); // 193 is prime number ho!!!

    map1.Set(418,32114);
    map1.Set(9,514);
    map1.Set(27,8917);
    //map1.Set(1031,286);
    map1[1031] = 286;


    printf("Key:%d\t\tValue:%d\n", 418 , map1.Get(418) );
    printf("Key:%d\t\tValue:%d\n", 9 , map1.Get(9) );
    printf("Key:%d\t\tValue:%d\n", 27 , map1.Get(27) );
    printf("Key:%d\tValue:%d\n", 1031 , map1.Get(1031) );


    printf("-----------------------\n");
    printf("Key:%d\t\tValue:%d\n", 418 , map1[418] );
    printf("Key:%d\t\tValue:%d\n", 9 , map1[9] );
    printf("Key:%d\t\tValue:%d\n", 27 , map1[27] );
    printf("Key:%d\tValue:%d\n", 1031 , map1[1031] );


    return 0;
}