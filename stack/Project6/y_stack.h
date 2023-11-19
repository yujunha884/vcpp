
#pragma once

// 노드 클래스 정의
class NODE {
public:
    int data;     // 데이터를 저장하는 변수
    NODE* next;   // 다음 노드를 가리키는 포인터

    NODE(int data) : data(data), next(nullptr) {} // 생성자
};

// 스택 클래스 정의
class y_stack {
private:
    NODE* top; // 스택의 맨 위를 가리키는 포인터
    
public:
    y_stack();    // 생성자
    ~y_stack();   // 소멸자
    void push(int data); // 스택에 데이터를 추가하는 함수
    int pop();  // 스택에서 데이터를 제거하고 반환하는 함수
    int search(); // 스택의 맨 위 데이터를 조회하는 함수
    bool isEmpty(); // 스택이 비어 있는지 확인하는 함수
};