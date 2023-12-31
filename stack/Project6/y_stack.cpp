#include "y_stack.h"
#include <iostream>
using namespace std;

// 스택 클래스의 생성자
y_stack::y_stack() {
    top = nullptr; // 초기화 시 top은 null
}

// 스택 클래스의 소멸자
y_stack::~y_stack() {
    while (!isEmpty()) {
        pop(); // 스택이 비어있지 않으면 모든 요소 제거
    }
}

// 스택에 데이터를 추가하는 함수
void y_stack::push(int data) {
    NODE* newNODE = new NODE(data); // 새 노드 생성
    newNODE->next = top; // 새 노드의 next를 현재 top으로 설정
    top = newNODE; // 새 노드를 새로운 top으로 설정
}

// 스택에서 데이터를 제거하고 반환하는 함수
int y_stack::pop() {
    if (isEmpty()) {
        cout << "y_stack Underflow" << endl;
        return -1;
    }
    else {
        NODE* temp = top; // 현재 top 노드를 임시 저장
        top = top->next; // top을 다음 노드로 이동
        int PopData = temp->data; // 제거될 데이터 저장
        delete temp; // 노드 메모리 해제
        return PopData; // 제거된 데이터 반환
    }
}

// 스택의 맨 위 데이터를 조회하는 함수
int y_stack::search() {
    if (isEmpty()) {
        cout << "y_stack is Empty" << endl;
        return -1;
    }
    else {
        return top->data; // top 데이터 반환
    }
}

// 스택이 비어 있는지 확인하는 함수
bool y_stack::isEmpty() {
    return top == nullptr; // top이 null이면 스택은 비어 있는 것
}