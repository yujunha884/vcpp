#include<stdio.h>
#include <conio.h>
#include <iostream>
#include <windows.h> 

int main()
{
    int befkey = 0; //  이전 입력한 키를 저장
    int aftkey = 0; //  현재 입력되어진 키를 저장
    char command;

    while (1) {
        Sleep(300); // 0.3초 지연시간
        command = _getch();
        if (command == 75) {

            befkey = command; // 입력한 키에 좌측 화살표의 아스키코드값을 넣어준다
            aftkey = 0; // 이전 입력이 무엇이었던, 해당 커맨드 이후 a를 눌러서 기술 발동은 불가능
            printf("←");
        }
        else if (command == 77) {
            if (befkey == 75) {
                aftkey = 1; // 집가고 싶다 기술 발현이 가능해진 상태
            }
            else if (befkey == 80) {
                aftkey = 2; // 아도겐 =o 기술 발동이 가능
            }
            else {
                befkey = command; // 기술 발동이 불가능하다면, 입력한 키 초기화
                aftkey = 0; // 또한 기술 발현이 불가능한 상태로 변경
            }
            printf("→");
        }
        else if (command == 72) {
            if (befkey == 77) {
                aftkey = 3; // 아아아아아기술 발동이 가능
            }
            else {
                befkey = command; // 기술 발동이 불가능하다면, 입력한 키 초기화
                aftkey = 0; // 또한 기술 발현이 불가능한 상태로 변경
            }
            printf("↑");
        }
        else if (command == 80) {
            befkey = command; // 발동 가능한 기술이 없으므로 입력한 키만 초기화
            aftkey = 0; // 또한 기술 발현이 불가능한 상태로 변경
            printf("↓");
        }
        else if (command == 97) {
            if (aftkey == 1) {
                printf("a \t [집가고 싶다!] \n"); // 첫 번째 기술 발동 
            }
            else if (aftkey == 2) {
                printf("a \t [아도겐 =o] \n"); // 두 번째 기술 발동 
            }
            else if (aftkey == 3) {
                printf("a \t [아아아아아\n!]  \n"); // 세 번째 기술 발동
            }
            else if (befkey == 80) {
                printf("a \t [포효!] \n"); // 방어기
            }
            else {
                printf("a \t[때잉 쯧!] \n"); // 위의 상황 모두와 안맞을 경우 기본 평타가 나감
            }
            aftkey = 0;
            befkey = 0; // 이후 사용된 모든 전 입력 키들은 초기화
        }
        else {
            if (command == -32) {
                continue;
            }
            else if (command == 27) {
                break; // ESC키 입력시 종료됨
            }
            else {
                putchar(command);
                aftkey = 0;
                befkey = 0;
                continue;
            }
        }
    }
}