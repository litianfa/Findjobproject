//
//  related_string_word.hpp
//  c++
//
//  Created by litianfa on 2019/7/2.
//  Copyright © 2019 litianfa. All rights reserved.
//

#ifndef related_string_word_hpp
#define related_string_word_hpp

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <deque>
using namespace std;

/****字符串问题****/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/****关于二叉树的一些操作***/
//1.moris遍历
void moristravel(TreeNode* cur);
//moris中序遍历
void morisIn(TreeNode* head);
//moris先序遍历
void morisPre(TreeNode* head);
//moris后序遍历
void morisAft(TreeNode* head);
//打印链表的右边界
void printrightedge(TreeNode* head);
//2.一般的递归打印二叉树
void printIntra(TreeNode* cur,string& str);
void printPretra(TreeNode* cur,string& str);
//KMP算法,是拿str2匹配str1,str2.size() < str1.size()
int kmpalgor(string& str1,string& str2);
vector<int> getnextarray(string& ptr);

//案例
//1.判断二叉树s中是否有与二叉树t拓扑结构相同的子树
bool issubtree(TreeNode* s,TreeNode* t);
//2.两个字符串是否互为变形词
bool anagram(string s, string t);
//3.两个字符串是否互为旋转词
bool rotateString(string str1, string str2);
//4.给定一个字符串，请在单词间做逆序调整
void reverseword(string& str,int start,int end);
void changeword(string& str);
//附加题，左旋转字符串，字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部
void leftreversestringword(string& str,int len);
//5.给定一个字符串str，和一个整数i,i代表str中的位置，将str[0,i]移到右侧，str[i+1,N-1]部分移到左侧
void movepartofword(string& str,int i);
//6.最小字典序的字符串拼接方案
string sumstringword(string& str1,string& str2);
//7.给定一个字符串str,将其中所有的空格字符都替换成“%20”，假设str后面有足够的空间
void inserspaceword(string& str);
//8.有效的括号序列
bool isValidParentheses(string &s);
//9.给定一个字符串，返回其中的最长无重复子串的长度
int lengthOfLongestSubstring(string s);
//10.打印字符串子序列的问题
void stringcharsubarr(string& str,int i,string res);
//11.打印字符串的全排列
void stringcharfullprocess(string str,int i);
//扩展，求字符串的所有组合
void stringwordcombineprocess(string& str,int i,string pstr);
//12.字符串表示公式，返回公式的计算结果
//返回数组的长度一定是2
//arr[0] = 得到的值
//arr[1] = 到达的字符串的位置
int* value(string str,int i);
void addNum(deque<char>& deq,int num);
int getNum(deque<char>& deq);
int getvalue(string str);
//13.回文字符串manacher算法
vector<char> manacherString(std::string const& str);
string maxLcpsLength(std::string const& str);
//案例14，字符串匹配问题，（正则表达式的简版），给定字符串str,其中绝对不包含字符'.'和'*'，在给定字符串exp，其中可以含有'.'和'*','*'字符不能是exp的首字符，并且任意两个'*'字符不能相邻，exp中的'.'代表任何一个字符，expk中的'*'表示'*'的前一个字符可以有0个或者多个，请写出一个函数，判断str是否e能被exp匹配
//递归版
bool process(string str,string exp,int i,int j);
//动态规划版
bool dpstringzhengze(string str,string exp);
bool isvalid(string str,string exp);
bool** initdpmap(string str,string exp);

#endif /* related_string_word_hpp */
