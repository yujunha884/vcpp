#include "y_stack.h"
#include <iostream>
using namespace std;

int main() {
	y_stack s;          // ���� ��ü ����
	s.push(1);       // ���ÿ� 10 �߰�
	s.push(2);       // ���ÿ� 20 �߰�
	s.push(3);       // ���ÿ� 30 �߰�
	s.push(4);       // ���ÿ� 40 �߰�
	s.push(5);       // ���ÿ� 50 �߰�
	s.push(6);       // ���ÿ� 60 �߰�
	s.push(7);       // ���ÿ� 70 �߰�
	s.push(8);       // ���ÿ� 80 �߰�


	cout << s.pop() << " ���ؿ��� ���ŵ� \n"; // ���ÿ��� ������ �����ϰ� ���
	cout << "���� Top�� " << s.search() << "�Դϴ�." << endl; // ���� top ��� ��ȸ
	for (int i = 0; i < 8; i++) {
		int result;
		result = s.pop();
		cout << result << endl;
	}

	return 0;
}