// Regular Expression Matching.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct match
{
	char key;
	char value;
};

class Solution {
public:
	bool isLetterMatch(char s, char p)
	{
		if (s == p || p == '.')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool isMatch(string s, string p) {
		vector<match> new_p;

		//把匹配模式p转换成比较容易理解的结构
		for (int i = 0; i < p.length(); )
		{
			match data;
			data.key = p[i];
			if (i + 1 < p.length() && p[i + 1] == '*')
			{
				data.value = '*';
				i += 2;
			}
			else
			{
				data.value = 1;
				i++;
			}
			new_p.push_back(data);
		}

		//初始化二维数组
		vector<vector<bool>> record;
		for (int i = 0; i <= new_p.size(); i++)
		{
			record.push_back(vector<bool>(s.length() + 1, false));
		}

		//初始化最开始的情况
		record[0][0] = true;
		for (int i = 1; i <= s.length(); i++)
		{
			record[0][i] = false;
		}
		for (int i = 1; i <= new_p.size(); i++)
		{
			record[i][0] = record[i - 1][0] && new_p[i - 1].value == '*';
		}

		//从子问题推导出最终需要解决的问题
		for (int i = 1; i <= new_p.size(); i++)
		{
			for (int j = 1; j <= s.length(); j++)
			{
				if (new_p[i - 1].value == 1)
				{
					record[i][j] = record[i - 1][j - 1] && isLetterMatch(s[j - 1], new_p[i - 1].key);
				}
				else
				{
					record[i][j] = (record[i - 1][j]) ||
						(record[i - 1][j - 1] && isLetterMatch(s[j - 1], new_p[i - 1].key)) ||
						(record[i][j - 1] && isLetterMatch(s[j - 1], new_p[i - 1].key));
				}
			}
		}
		return record[new_p.size()][s.length()];
	}
};

int main()
{
	Solution s;
	
    std::cout << s.isMatch("aa", "a") << endl;
	std::cout << s.isMatch("aa", "a*") << endl;
	std::cout << s.isMatch("ab", ".*") << endl;
	std::cout << s.isMatch("aab", "c*a*b") << endl;
	std::cout << s.isMatch("mississippi", "mis*is*p*.") << endl;

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
