//
//  dynamicplan.hpp
//  c++
//
//  Created by litianfa on 2019/7/8.
//  Copyright © 2019 litianfa. All rights reserved.
//

#ifndef dynamicplan_hpp
#define dynamicplan_hpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//换钱的方法数
//先递归实现
int changemoney(vector<int>& arr,int aim,int i);
//动态规划版本
int dpchangemoney(vector<int>& arr,int aim);
//案例1，有N级台阶，一个人每次上一级或者两级，问有多少种方法走完N级台阶的方法
//递归版
int taijie(int n);
//动态规划版
int dptaijie(int n);
//案例2，矩阵的最小路径和
//递归版
int matrixminpathsum(vector<vector<int> >& matrix,int i,int j);
//动态规划版
int dpmatrixminpathsum(vector<vector<int> >& matrix);
//案例3最长递增子序列
//递归版
int lengthofLIS(vector<int>& nums);
int getlengthoflis(vector<int>& nums,int preval,int curpos);
//动态规划版
int dplengthofLIS(vector<int>& nums);
//案例4，返回两个字符串的最长公共子序列
//递归版
string maxlengthcommonsubarr(string str1,string str2);
string processmaxlensubstring(string str1,string str2,int i,int j);
//动态规划版
string dpmaxlensubstring(string& str1,string& str2);
//案例5，一个背包有一定的承重W，有N件物品，每件都有自己的价值，记录在数组v中，也都有自己的重量，记录在数组w中，每件物品只能选择要装入背包还是不装入背包，要求在不超过背包承重的前提下，选出物品总价最大
//递归版
int backpacksolution(vector<int>& w,vector<int>& v,int W);
int processbackpacksolution(vector<int>& w,vector<int>& v,int W,int i);
//动态规划版
int dpbackpacksolution(vector<int>& w,vector<int>& v,int W);
//案例6，给定两个字符串str1和str2，在给定3个整数ic、dc、rc，分别代表插入、删除、替换一个字符的代价。返回将str1编辑成str2的最小代价
//递归版
int mincostofmakesamestring(string str1,string str2,int ic,int dc,int rc);
int processmincostchangestring(string str1,string str2,int ic,int dc,int rc,int i,int j);
//动态规划版
int dpmincostchangestring(string str1,string str2,int ic,int dc,int rc);
//案例7，给定一个数组和一个整数，求数组中任意组合的和等于给定的整数
bool isequalsum(vector<int> nums,int aim,int sum,int i);

//案例8，排成一条线的纸牌博弈问题
//递归版
int win1(vector<int> arr);
int f(vector<int> arr,int i,int j);
int s(vector<int> arr,int i,int j);
//动态规划版
int win2(vector<int> arr);
//案例9，换钱的最小货币数
//递归版
int minchangemoney(vector<int> arr,int aim);
int processminmoney1(vector<int> arr,int aim,int index);
//改动态规划
int minchangemoneydp(vector<int> arr,int aim);
//案例10，最少费用的爬台阶方法
//递归版
int minCostClimbingStairs(vector<int> &cost);
int processcoststairs(vector<int> &cost,int index);
//改动态规划
int minCostClimbingStairsdp(vector<int> &cost);
//案例11，给定一个数组，全是正数，和一个整数aim,求累加和等于aim的最长子数组,时间复杂度为O(N)，额外空间复杂度为O(1),思路为用双指针组成一个窗口不断移动窗口求其和
int getmaxlengtharr(vector<int>& arr,int aim);
//案例12，给定一个数组，值可正可负可0，z一个整数aim,求累加和小于等于aim的最长子数组，要求时间复杂度为O(N)
int getmaxlensubvariablearr(vector<int>& nums,int aim);
//案例13，环形单链表的约瑟夫问题
struct circlenode{
    int val;
    struct circlenode* next;
    circlenode(int value):val(value),next(NULL){ }
};
circlenode* josephusKill2(circlenode* head,int m);
int getlive(int i,int m);
//案例14，字符串匹配问题，（正则表达式的简版），给定字符串str,其中绝对不包含字符'.'和'*'，在给定字符串exp，其中可以含有'.'和'*','*'字符不能是exp的首字符，并且任意两个'*'字符不能相邻，exp中的'.'代表任何一个字符，expk中的'*'表示'*'的前一个字符可以有0个或者多个，请写出一个函数，判断str是否e能被exp匹配
//递归版
bool process(string str,string exp,int i,int j);
//动态规划版
bool dpstringzhengze(string str,string exp);
bool isvalid(string str,string exp);
bool** initdpmap(string str,string exp);
//案例15.最长回文子串
//动态规划
string getmaxlenlongeststringword(string s);
//案例16.通配符匹配
//递归
bool ismatchstringword(string& s,string& p,int i,int j);
bool isMatch(string s, string p);
//动态规划
bool ismatchdpstringword(string s,string p);
//案例17.最大子序和
int maxSubArray(vector<int>& nums);
//案例18.不同路径
//递归版
int uniquePaths(int m, int n);
int processuniquepaths(int m,int n,int i,int j);
//动态规划版
int dpuniquepaths(int m,int n);
//案例19.不同路径2（加障碍物）
//递归版
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid);
int processuniquepathswithobstacles(vector<vector<int>>& obstacle,int m,int n,int i,int j);
//动态规划版
int dpuniquepathswithobstacles(vector<vector<int>>& obstacleGrid);

#endif /* dynamicplan_hpp */
