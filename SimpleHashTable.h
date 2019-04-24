//
// Created by xlrnux on 19. 4. 24.
//

#ifndef STL_SIMPLEHASHTABLE_H
#define STL_SIMPLEHASHTABLE_H

#include<stdio.h>
#include<malloc.h>

typedef int KeyType;
typedef int ValueType;
class Map {
public:
    typedef struct Node {
        KeyType Key;
        ValueType Value;
    }Node;
private:
    Node *Table;
    int TableSize;

public:
    Map(int TableSize){
        this->TableSize = TableSize;
        Table = (Node*)malloc(sizeof(Node)*TableSize);
    }

    ~Map(){
        free(Table);
    }

    int Hash(KeyType Key){
        return Key % TableSize;
    }

    void Set(KeyType Key, ValueType Value){
        int Address = Hash(Key);
        Table[Address].Key = Key;
        Table[Address].Value = Value;
    }
    ValueType Get(KeyType Key){
        int Address = Hash(Key);
        return Table[Address].Value;
    }
    ValueType operator[](KeyType Key){
        return Get(Key);
    }
};


#endif //STL_SIMPLEHASHTABLE_H
