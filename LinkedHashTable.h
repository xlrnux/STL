//
// Created by xlrnux on 19. 4. 25.
//

#ifndef STL_LINKEDHASHTABLE_H
#define STL_LINKEDHASHTABLE_H

#include<stdio.h>
#include<malloc.h>

class LMap{
    typedef int KeyType;
    typedef int ValueType;
public:
    typedef struct Node{
        KeyType Key;
        ValueType Value;
        Node* Prev;
        Node* Next;
    }Node;

private:
    Node* Table;



};
#endif //STL_LINKEDHASHTABLE_H
