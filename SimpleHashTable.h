//
// Created by xlrnux on 19. 4. 24.
//

#ifndef STL_SIMPLEHASHTABLE_H
#define STL_SIMPLEHASHTABLE_H

//#include<stdio.h>
#include<iostream>
#include<malloc.h>

static void print_Prime(){
    int* _Prime = (int*)malloc(sizeof(int) * 15000000);
    for(int i = 2; i < 15000000; i++){
        if(_Prime[i] == 0){
            for(int j = 2; i*j < 15000000; j++){
                _Prime[i*j] = 1;
            }
        }
    }

    for(int i = 10000; i < 15000000; i++){
        if(_Prime[i] == 0) {
            printf("%d,", i);
            i = i*2;
        }
    }
    free(_Prime);
}

static int Prime[] = {10007,20021,40063,80141,160309,320627,641261,1282529,2565061,5130143,10260301};
class Map{
public:
    typedef int KeyType;
    typedef int ValueType;
    typedef struct Node{
        KeyType Key;
        ValueType Value;
    }Node;
private:
    Node* Table;
    int SizeIdx; // TableSize = Prime[SizeIdx]
    int TableSize;
    int UsedSize;
public:
    Map(){
        this->UsedSize = 0;
        this->SizeIdx = 0;
        TableSize = Prime[SizeIdx];
        Table = (Node*)malloc(sizeof(Node)*TableSize);
        for(int i = 0; i < TableSize; i++)
            (Table + i)->Key = -1;
    }
    ~Map(){
        free(Table);
    }

    int Hash(KeyType Key, int reHash=0){
        // 재해싱인 경우 reHash 가 0이 아닌 다른 수가
        // 입력되어서 들어옴
        // 원래 상정되어있는 TableSize 가 워낙 크기도 하고
        // 그 큰 수가 0보다 작아질 때 까지 재해싱이
        // 일어나면 그건 이미 해싱이 그냥 망한것.
        // 그러니 예외처리는 안함
        return Key % (TableSize-reHash) + reHash;
    }

    ValueType& operator [](KeyType Key){
        int reHash = 0;
        int Address;
        while(true){
            Address = Hash(Key, reHash);
            if(Table[Address].Key == Key){
                Table[Address].Key = Key;
                return Table[Address].Value;
            }else if(Table[Address].Key == -1 ){
                Table[Address].Key = Key;
                this->UsedSize++;

                if( (this->UsedSize)*1.0 >= TableSize*0.75){
                    // 총 용량의 75퍼센트 이상을 사용했다면?
                    ReSize();
                }

                return Table[Address].Value;
            }else {
                reHash += 2;
                if(Hash(Key, reHash)>= TableSize){
                    // 오버플로우 대비
                    ReSize();
                }

            }

        }
    }

private:
    void ReSize(){
        SizeIdx++;
        TableSize = Prime[SizeIdx];
        realloc(Table,sizeof(Node)*TableSize);
        for(int i = Prime[SizeIdx-1]; i < TableSize; i++)
            (Table + i)->Key = -1;

    }
};



#endif //STL_SIMPLEHASHTABLE_H
