// 测试程序
#include<iostream>
#include"addStrings.h"
using namespace std;

int main(){
	string num1;
    string num2;
	cin >> num1 >> num2;
	cout << addFloatStrings(num1, num2) << endl;
	return 0;
}
