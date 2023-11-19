#include "y_stack.h"
#include <iostream>
using namespace std;

// ���� Ŭ������ ������
y_stack::y_stack() {
    top = nullptr; // �ʱ�ȭ �� top�� null
}

// ���� Ŭ������ �Ҹ���
y_stack::~y_stack() {
    while (!isEmpty()) {
        pop(); // ������ ������� ������ ��� ��� ����
    }
}

// ���ÿ� �����͸� �߰��ϴ� �Լ�
void y_stack::push(int data) {
    NODE* newNODE = new NODE(data); // �� ��� ����
    newNODE->next = top; // �� ����� next�� ���� top���� ����
    top = newNODE; // �� ��带 ���ο� top���� ����
}

// ���ÿ��� �����͸� �����ϰ� ��ȯ�ϴ� �Լ�
int y_stack::pop() {
    if (isEmpty()) {
        cout << "y_stack Underflow" << endl;
        return -1;
    }
    else {
        NODE* temp = top; // ���� top ��带 �ӽ� ����
        top = top->next; // top�� ���� ���� �̵�
        int PopData = temp->data; // ���ŵ� ������ ����
        delete temp; // ��� �޸� ����
        return PopData; // ���ŵ� ������ ��ȯ
    }
}

// ������ �� �� �����͸� ��ȸ�ϴ� �Լ�
int y_stack::search() {
    if (isEmpty()) {
        cout << "y_stack is Empty" << endl;
        return -1;
    }
    else {
        return top->data; // top ������ ��ȯ
    }
}

// ������ ��� �ִ��� Ȯ���ϴ� �Լ�
bool y_stack::isEmpty() {
    return top == nullptr; // top�� null�̸� ������ ��� �ִ� ��
}