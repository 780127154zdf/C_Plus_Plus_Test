#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

// 两个非负整数相加
string addNegStrings(string num1, string num2){
	string ans = "";
	int carry = 0;
	int i = num1.length() - 1, j = num2.length() - 1;
	while(i >= 0 || j >= 0 || carry){
		int a = i >= 0 ? num1[i] - '0' : 0;
		int b = j >= 0 ? num2[j] - '0' : 0;
		int sum = a + b + carry;
		ans += (sum % 10 + '0');
		carry = sum / 10;
		--i;
		--j;
	}
	reverse(ans.begin(), ans.end());

	return ans;
}

// 两个整数相加
string addStrings(string num1, string num2){
	bool isNeg1 = (num1[0] == '-');
	bool isNeg2 = (num2[0] == '-');
	if(isNeg1) num1 = num1.substr(1, num1.length() - 1); // 去掉负号
	if(isNeg2) num2 = num2.substr(1, num2.length() - 1);

	if(isNeg1 && isNeg2){
		return ('-' + addNegStrings(num1, num2));
	}else if(!isNeg1 && !isNeg2){
		return addNegStrings(num1, num2);
	}else{
		// 一正一负，始终保持绝对值大的数在前
		string ans = "";
		if(num2 > num1){
			swap(num1, num2);
			swap(isNeg1, isNeg2);
		}
		int borrow = 0; // 借位
		int i = num1.length() - 1, j = num2.length() - 1;
		while(i >= 0 || j >= 0){
			int a = i >= 0 ? num1[i] - '0' : 0;
			int b = j >= 0 ? num2[j] - '0' : 0;
			int sub = a - b - borrow;
			if(sub < 0){
				// 要从高位借位
				borrow = 1;
				sub += 10;
			}else{
				// 不需要从高位借位
				borrow = 0;
			}
			ans += (sub + '0');
			--i;
			--j;
		}
		reverse(ans.begin(), ans.end());
		// 接下来去除前导0
		int index = 0;
		while(index < ans.length() && ans[index] == '0'){
			++index;
		}
		if(index == ans.length()) return "0";
		ans = ans.substr(index);
		if(isNeg1) ans = '-' + ans;
		return ans;
	}

	return ""; // 失败，实际上到不了这里
}

int main(){
	string num1;
    string num2;
	cin >> num1 >> num2;
	cout << addStrings(num1, num2) << endl;
	return 0;
}
