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
static int Prime[] = {10007,20021,40063,80141,160309,320627,641261}; // 현실적인 사이즈
class Map{
public:
    typedef int KeyType; // Template 대신 아쉬운대로
    typedef int ValueType; // Template 대신 아쉬운대로

    typedef struct Node{ // 우리의 주인공님
        KeyType Key; // 진짜 키값
        ValueType Value; // 값
        Node* Next; // 체이닝을 위한 다음노드
        Node(){ // 자동 초기화. 아마 C에서는 못쓸듯
            this->Key = -1;
        }
    }Node;
private:
    int SizeIdx = 0; // TableSize = Prime[SizeIdx]
    int newSizeIdx = SizeIdx + 1; // 리사이징 대비

    int TableSize = Prime[SizeIdx]; // 배열 사이즈 겸, 해싱용 피연산자
    int oldTableSize = 0; // 리사이징 대비
    int newTableSize = Prime[newSizeIdx]; // 리사이징 대비

    Node* Table = new Node[TableSize]; // 해시 테이블 배열
    int UsedSize = 0; // 사용된 공간 카운트

    int ChainLimit = 4; // 클러스터 최대 허용값. 해당 값을 초과하면 리사이징
    bool rehash = false; // 리사이징 필요여부 파라미터
public:
    Map(){

    }
    ~Map(){
        // 해시맵 동적할당 해제
        for(int i = 0; i < this->TableSize; i++){
            if(Table[i].Next == NULL) continue; // 사용되지 않은 원소. 반드시 continue
            Node* Current = Table[i].Next;
            KeyType Key = Current->Key;
            while( Current != NULL ) {
                Node* next = Current->Next;
                Current->Next = NULL;
                delete Current;
                Current = next;
            }
        }
        delete[] Table;
    }

    void Stats(){
        std::cout << "==== start print stats ! \n";
        std::cout << "SizeIdx: " << SizeIdx;
        std::cout << " TableSize: " << TableSize;
        std::cout << " UsedSize: " << UsedSize;
        std::cout << " ChainLimit: " << ChainLimit;

        std::cout << "\n";

        std::cout << "==== end print stats ! \n";
    }
    void FullPrint(){
        Stats();
        std::cout << "-----------start print! \n";
        for(int i = 0; i < TableSize; i++){
            Node* Current = &Table[i];
            while(Current->Key != -1){
                std::cout << "TableSize: " << TableSize << "\t";
                std::cout << "Address: " << Hash(Current->Key);
                std::cout << " Key: " << Current->Key;
                std::cout << " Val: " << Current->Value << "\n";
                Current = Current->Next;
            }
            if(Table[i].Key != -1) std::cout << "\n";
        }
        std::cout << "-----------end print! \n";
    }

    int GetTableSize(){
        return this->TableSize;
    }

    int Hash(KeyType Key){
        // Key 로부터 Address 를 계산
        return Key % TableSize;
    }

    ValueType& operator [](KeyType Key){
        if( (this->UsedSize)*1.0 >= (this->TableSize)*0.75 // 총 용량의 75퍼센트 이상을 사용
        || rehash){ // 체이닝이 너무 커짐
            ReSize();
        }

        int Address = Hash(Key);
        Node* Current = &Table[Address];

        int chain = 0;
        while( Current->Next != NULL
        && ++chain) {
            if (Current->Key == Key) return Current->Value;

            Current = Current->Next;
        }

        // 체이닝이 아닌 최초 노드에 삽입 된 경우에는 UsedSize 를 더해준다
        if(chain == 0) this->UsedSize++;
        if(chain >= ChainLimit) rehash = true;

        Current->Key = Key;
        Current->Next = new Node();
        return Current->Value;
    }

private:
    void Set(KeyType Key, ValueType Value){
        // 재 해싱할 때 옮기는 용도로만 사용함
        int chain = 0;
        int Address = Hash(Key);
        Node* Current = &Table[Address];
        while(Current->Next != NULL && ++chain){
            Current = Current->Next;
        }
        Current->Key = Key;
        Current->Value = Value;
        Current->Next = new Node();
        if(chain == 0) this->UsedSize++;
        if(chain >= this->ChainLimit) rehash = true;
    }

    void ReSize() {
        rehash = false;
        ChainLimit *= 5;
        if(DEBUG) std::cout << "ReSized!!!\n";
        this->SizeIdx = this->newSizeIdx;
        this->newSizeIdx = this->SizeIdx+1;
        this->oldTableSize = this->TableSize;
        this->TableSize = this->newTableSize;
        this->newTableSize = Prime[newSizeIdx];
        this->UsedSize = 0;

        Node* oldTable = Table;
        Table = new Node[TableSize];

        for(int i = 0; i < this->oldTableSize; i++){
            if( oldTable[i].Key == -1) continue;

            Set(oldTable[i].Key, oldTable[i].Value);
            Node* Current = oldTable[i].Next;
            while( Current->Key != -1 ) {
                Set(Current->Key, Current->Value);

                Node* next = Current->Next;
                Current->Next = NULL;
                delete Current;
                Current = next;
            }
            delete Current;
        }

        delete[] oldTable;
    }
};



#endif //STL_SIMPLEHASHTABLE_H
