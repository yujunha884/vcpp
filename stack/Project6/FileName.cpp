#include "y_stack.h"
#include <iostream>
using namespace std;

int main() {
	y_stack s;          // 스택 객체 생성
	s.push(1);       // 스택에 10 추가
	s.push(2);       // 스택에 20 추가
	s.push(3);       // 스택에 30 추가
	s.push(4);       // 스택에 40 추가
	s.push(5);       // 스택에 50 추가
	s.push(6);       // 스택에 60 추가
	s.push(7);       // 스택에 70 추가
	s.push(8);       // 스택에 80 추가


	cout << s.pop() << " 스텍에서 제거됨 \n"; // 스택에서 데이터 제거하고 출력
	cout << "현재 Top은 " << s.search() << "입니다." << endl; // 현재 top 요소 조회
	for (int i = 0; i < 8; i++) {
		int result;
		result = s.pop();
		cout << result << endl;
	}

	return 0;
}