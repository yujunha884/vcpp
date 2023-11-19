
#pragma once

// ��� Ŭ���� ����
class NODE {
public:
    int data;     // �����͸� �����ϴ� ����
    NODE* next;   // ���� ��带 ����Ű�� ������

    NODE(int data) : data(data), next(nullptr) {} // ������
};

// ���� Ŭ���� ����
class y_stack {
private:
    NODE* top; // ������ �� ���� ����Ű�� ������
    
public:
    y_stack();    // ������
    ~y_stack();   // �Ҹ���
    void push(int data); // ���ÿ� �����͸� �߰��ϴ� �Լ�
    int pop();  // ���ÿ��� �����͸� �����ϰ� ��ȯ�ϴ� �Լ�
    int search(); // ������ �� �� �����͸� ��ȸ�ϴ� �Լ�
    bool isEmpty(); // ������ ��� �ִ��� Ȯ���ϴ� �Լ�
};