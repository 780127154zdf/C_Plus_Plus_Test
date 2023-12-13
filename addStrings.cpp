#include"addStrings.h"
#include<algorithm>

// 带小数点的两个非负字符串相加，返回它们的和
// 也允许字符串为整数，不必满足非负
// 带小数的部分字符串必须非负，还没有处理负数的带小数字符串相加情况
string addFloatStrings(string num1, string num2){
	int iFloat1 = -1, iFloat2 = -1; // 小数点的下标
	for(int i = 0; i < num1.size(); ++i){
		if(num1[i] == '.'){
			iFloat1 = i;
			break;
		}
	}
	for(int i = 0; i < num2.size(); ++i){
		if(num2[i] == '.'){
			iFloat2 = i;
			break;
		}
	}
	if(iFloat1 == -1 && iFloat2 == -1){
		// 整数字符串相加
		return addStrings(num1, num2);
	}

	if(iFloat1 == -1){
		// 说明num1是整数
		num1 += ".0"; // 构造成带小数
		iFloat1 = num1.size() - 2;
	}
	if(iFloat2 == -1){
		num2 += ".0";
		iFloat2 = num2.size() - 2;
	}
	
	string interStr1 = num1.substr(0, iFloat1), floatStr1 = num1.substr(iFloat1 + 1); // 按小数点将字符串分为整数和小数部分
	string interStr2 = num2.substr(0, iFloat2), floatStr2 = num2.substr(iFloat2 + 1);
	if(floatStr1.size() > floatStr2.size()){
		// 小数部分和整数部分都得交换
		swap(floatStr1, floatStr2);
		swap(interStr1, interStr2);
	}
	if(floatStr1.size() < floatStr2.size()){
		int cnt = floatStr2.size() - floatStr1.size();
		for(int i = 0; i < cnt; ++i){
			floatStr1 += '0';
		}
	}
	// 对较短的小数字符串末尾补零后，两个小数字符串长度一样
	string ans2 = "";
	int carry = 0;
	for(int i = floatStr1.size() - 1; i >= 0; --i){
		int a = floatStr1[i] - '0';
		int b = floatStr2[i] - '0';
		int sum = a + b + carry;
		ans2 += (sum % 10 + '0');
		carry = sum / 10;
	}
	reverse(ans2.begin(), ans2.end());
	string ans1 = "";
	int i = interStr1.size() - 1, j = interStr2.size() - 1;
	while(i >= 0 || j >= 0 || carry){
		int a = i >= 0 ? interStr1[i] - '0' : 0;
		int b = j >= 0 ? interStr2[j] - '0' : 0;
		int sum = a + b + carry;
		ans1 += (sum % 10 + '0');
		carry = sum / 10;
		--i;
		--j; // 如果不加，陷入死循环
	}
	int index = 0; // 去掉小数翻转前的前导0
	while(index < ans2.size() && ans2[index] == '0') ++index;
	if(index == ans2.size()) ans2 = "";
	else ans2 = ans2.substr(index);
	reverse(ans1.begin(), ans1.end());
	if(ans2 != "") ans2 = "." + ans2; // 需要的时候加上小数点
	return ans1 + ans2;
}

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
