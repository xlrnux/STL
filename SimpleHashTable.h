//
// Created by xlrnux on 19. 4. 24.
//

#ifndef STL_SIMPLEHASHTABLE_H
#define STL_SIMPLEHASHTABLE_H

#include<iostream>
#define DEBUG 1
// 그냥 Prime 배열을 만들기 위해 덤으로 만든 함수
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
// TableSize (겸 해싱에서 나머지 연산의 피연산자로 사용될 목록)
static int Prime[] = {9,10007,20021,40063,80141,160309,320627,641261}; // 현실적인 사이즈
class Map{
public:
    typedef int KeyType; // Template 대신 아쉬운대로
    typedef int ValueType; // Template 대신 아쉬운대로
    typedef struct Node{ // 우리의 주인공님
        KeyType Key;
        ValueType Value;
        Node* Next;
    }Node;
private:
    int SizeIdx = 0; // TableSize = Prime[SizeIdx]
    int TableSize = Prime[SizeIdx];
    Node* Table = new Node[TableSize];
    int UsedSize = 0;
    int newSizeIdx = 1;
    int newTableSize = Prime[newSizeIdx];
    int oldTableSize = 0;
    int ChainLimit = 5;
    bool rehash = false;
public:
    Map(){
        for(int i = 0; i < TableSize; i++) {
            Table[i] = (Node){-1,-1,NULL};
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
        delete[] Table;
    }

    int GetTableSize(){
        return this->TableSize;
    }
    int Hash(KeyType Key){
        // Key 로부터 Address 를 계산
        // Key 가 음수일 경우 재할당중이니 newTableSize 기준으로 나머지
        // 키의 기본값이 -1인만큼 이것도 신경써야할듯
        // 통상시에 키에 음수가 안들어 가도록 각별히 주의를 해야할듯
        if(Key < 0) return (Key*-1) % newTableSize; // 재할당중
        return Key % TableSize;
    }

    ValueType& operator [](KeyType Key){
        if( (this->UsedSize)*1.0 >= TableSize*0.75 // 총 용량의 75퍼센트 이상을 사용
        || rehash){ // 체이닝이 너무 커짐
            rehash = false;
            ChainLimit *= 5;
            if(DEBUG) std::cout << "ReSized!!!\n";
            this->oldTableSize = this->TableSize;
            this->SizeIdx = this->newSizeIdx;
            this->TableSize = this->newTableSize;
            this->newSizeIdx = this->SizeIdx+1;
            this->newTableSize = Prime[newSizeIdx];
            ReSize();
        }


        int Address = Hash(Key);
        if(Key < 0) Key *= -1;// Key가 음수라면 재할당중 호출
        // 키의 기본값이 -1인만큼 이것도 신경써야할듯
        // 통상시에 키에 음수가 안들어 가도록 각별히 주의를 해야할듯


        while(true){
            Node* Current = &Table[Address];
            int turn = 0;
            while(++turn) {
                if (Current->Key == Key) {
                    return Current->Value;
                } else if (Current->Next == NULL) {
                    if(turn > 1) {
                        // 체이닝이 아닌 최초 노드에 삽입 된 경우에는 UsedSize 를 더해준다                        //
                        this->UsedSize++;
                        if(turn > ChainLimit) {
                            rehash = true;
                        }
                    }
                    Current->Key = Key;
                    Node* NewNode = new Node;
                    NewNode->Key = -1;
                    NewNode->Next = NULL;
                    Current->Next = NewNode;
                    if(DEBUG) std::cout << turn << "\n";
                    return Current->Value;
                }  else {
                    Current = Current->Next;
                }
            }
        }
    }

private:
    int minus(int num){
        return num*-1;
    }
    void ReSize() {

        Node* oldTable = Table;
        Table = new Node[TableSize];

        for(int i = 0; i < TableSize; i++) {
            Table[i].Key = -1;
            Table[i].Next = NULL;
        }

        int Address;
        for(int i = 0; i < this->oldTableSize; i++){
            if((oldTable[i]).Key == -1) continue;
            Address = Hash( minus(oldTable[i].Key) );
            Table[Address].Value = (oldTable[i]).Value;

            Node* Current = (oldTable[i]).Next;
            KeyType Key = Current->Key;
            while( Current->Next != NULL ) {
                Address = Hash( minus(Current->Key) );
                Table[Address].Value = Current->Value;

                Node* next = Current->Next;
                Current->Next = NULL;
                delete Current;
                Current = next;
            }
            if(Current->Key == -1) delete Current;
        }
        delete[] (oldTable);
    }
};



#endif //STL_SIMPLEHASHTABLE_H
