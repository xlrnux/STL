//
// Created by xlrnux on 19. 4. 24.
//

#ifndef STL_SIMPLEHASHTABLE_H
#define STL_SIMPLEHASHTABLE_H

#include<iostream>
static void print_Prime(){
    int* _Prime = new int[20];
    for(int i = 2; i < 15000000; i++){
        if(_Prime[i] == 0){
            for(int j = 2; i*j < 15000000; j++){
                _Prime[i*j] = 1;
            }
        }
    }

    for(int i = 10000; i < 15000000; i++){
        if(_Prime[i] == 0) {
            std::cout << i << ",";
            i = i*2;
        }
    }
    delete[] _Prime;
}

//static int Prime[] = {9,10007,20021,40063,80141,160309,320627,641261,1282529,2565061,5130143,10260301};
static int Prime[] = {9,10007,20021,40063,80141,160309,320627,641261}; // 현실적인 사이즈
class Map{
public:
    typedef int KeyType;
    typedef int ValueType;
    typedef struct Node{
        KeyType Key;
        ValueType Value;
        Node* Next;
        /*
        Node(){
            Key = -1;
            Next = NULL;
        }
         */

    }Node;
private:
    //int SizeIdx; // TableSize = Prime[SizeIdx]
    const int TableSize = 20021;
    Node Table[20021];
    //int UsedSize;
    //int newSizeIdx;
    //int newTableSize;
public:
    Map(){
        //this->SizeIdx = 2; // 무난하게 20021 사이즈 = 2
        //this->TableSize = Prime[SizeIdx];
        //this->UsedSize = 0;
        //this->newSizeIdx = 1;
        //this->newTableSize = Prime[1];


        //Table = new Node[TableSize];
        //Table = (Node*)malloc(sizeof(Node)*TableSize);

        for(int i = 0; i < TableSize; i++) {
            //(Table + i)->Next = (Node*)malloc(sizeof(Node));
            //(Table + i)->Key = -1;
            //(Table + i)->Next = NULL;
            Table[i].Key = -1;
            Table[i].Next = NULL;
            //(Table + i)->Next = new Node();
            //(Table + i)->Next->Key = -1;
        }


    }
    ~Map(){
        for(int i = 0; i < this->TableSize; i++){
            if(Table[i].Key == -1) continue;
            Node* Current = Table[i].Next;
            KeyType Key = Current->Key;
            while( Current->Next != NULL ) {
                Node* next = Current->Next;
                Current->Next = NULL;
                delete Current;
                Current = next;
            }
            if(Current->Key == -1) delete Current;


        }
    }

    int GetTableSize(){
        return this->TableSize;
    }
    int Hash(KeyType Key){
        // Key 로부터 Address 를 계산
        // Key 가 음수일 경우 재할당중이니 newTableSize 기준으로 나머지
        //if(Key < 0) return Key % newTableSize; // 재할당중
        return Key % TableSize;
    }

    ValueType& operator [](KeyType Key){

        /*
        if( (this->UsedSize)*1.0 >= TableSize*0.75){
            // 총 용량의 75퍼센트 이상을 사용했다면?
            // 생각해보니 체이닝해서 리사이즈 딱히 필요없음
            ReSize();
        }
         */

        int Address = Hash(Key);
        //if(Key < 0) Key *= -1;// Key가 음수라면 재할당중 호출

        while(true){
            Node* Current = &Table[Address];
            while(true) {
                if (Current->Key == -1) {
                    //this->UsedSize++;
                    Current->Key = Key;
                    Node* NewNode = new Node;
                    NewNode->Key = -1;
                    NewNode->Next = NULL;
                    Current->Next = NewNode;
                    return Current->Value;
                } else if (Current->Key == Key) {
                    return Current->Value;
                } else {
                    Current = Current->Next;
                }
            }
        }
    }

private:
    void ReSize() {
        /*
        std::cout << "ReSized!!!\n";
        Node* newTable = new Node[newTableSize];

        for(int i = 0; i < TableSize; i++){
            if(Table[i].Key == -1) continue;
            Node* Current = Table[i].Next;
            while(Current->Key != -1) {
                newTable[(Current->Key)*-1] = Current->Value;
                Node* next = Current->Next;
                delete Current;
                Current = next;
            }
        }

        delete[] Table;

        Table = newTable;
        this->SizeIdx = this->newSizeIdx;
        this->TableSize = this->newTableSize;
        this->newSizeIdx = this->SizeIdx+1;
        this->newTableSize = Prime[newSizeIdx];
         */
    }
};



#endif //STL_SIMPLEHASHTABLE_H
