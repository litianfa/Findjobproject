//
//  swordtooffer.hpp
//  c++
//
//  Created by litianfa on 2019/7/14.
//  Copyright © 2019 litianfa. All rights reserved.
//

#ifndef swordtooffer_hpp
#define swordtooffer_hpp
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>
using namespace std;

//剑指offer的面试题练习
//1.青蛙跳台问题 2的n-1次方,数学归纳法
int timesofjumpqingwa(int n);
//矩形覆盖问题，斐波那契系列问题，先看一看能不能用f(i-h+1)+f(i-h)来表示几种可能性

//2.旋转数组的最小数字,怎么感觉直接用二分查找来解非常方便
int minrecyclearr(vector<int>& nums);

//3.矩阵中的路径,有什么回溯法
bool haspath(vector<vector<char> >& matrix,string str);
bool haspathcore(vector<vector<char> >& matrix,int rows,int cols,int i,int j,string str,int& pathlen,bool** visited);
//4.机器人的运动范围
int travelpoint(int m,int n,int k);
int travelprocess(int m,int n,int k,int i,int j,bool** visited);
//5.剪绳子
//递归
int getmainmaxplus(int n);
int getmaxplussum(int n);
//动态规划
int dpgetmaxplussum(int n);
//6.二进制中1的个数
int mysolution(int n);
int numberof1(int n);
//7.数值的整数次方
double Power(double base,int exponent);
//8.打印从1到最大的n位数
void printmaxbitnumber(int n);
void pribnt1tomaxofndigits(int n);
void print1tomaxofndigitsrecursively(char* number,int length,int index);
void printnumber(char* number);

//9.实现任意两个整数的加法
void randomsum(int a,int b);
//10.删除链表节点
struct ListNode{
    int val;
    struct ListNode* next;
    ListNode(int value):val(value),next(NULL){ }
};
void deletenode(ListNode* head,ListNode* ptr);
//11.删除重复的节点
void repeatnode(ListNode* head);
//13.表示数值的字符串
//递归版
bool scanint(const char** str);
bool scanunsignedint(const char** str);
bool isnumber(const char* str);
//14.调整数组顺序使奇数位于偶数前面
void resortoddvector(vector<int>& nums);
//附加，调整数组的顺序使负数在前，整数在后
void resortzhengfuvector(vector<int>& nums);
//15.链表中倒数第k个节点
ListNode* kpointoflist(ListNode* head,int k);
//双指针法，一个指针先走k-1步，到达k时，第二个指针开始从头走，当第一个指针d走到空时，第二个指针走到倒数第k个节点
ListNode* ktwoptrlistlinked(ListNode* head,int k);
//16.链表中环的入口节点
ListNode* incyclelistlinked(ListNode* head);
//17.反转链表
ListNode* reverselistlinked(ListNode* head);
//进阶题，反转从位置 m 到 n 的链表。请使用一趟扫描完成反转
ListNode* reverseBetween(ListNode* head, int m, int n);
//18.合并两个排序的链表
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2);
//19.判断二叉树s中是否有与二叉树t拓扑结构相同的子树
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//递归
bool isheadequaltree(TreeNode* s,TreeNode* t);
bool isleftrightequaltree(TreeNode* root1,TreeNode* root2);
bool isequalval(TreeNode* ptr1,TreeNode* ptr2);
//20.二叉树的镜像
TreeNode* mirrortree(TreeNode* root);
void printtreepre(TreeNode* root);
//21.对称的二叉树
//一般的递归打印二叉树
void printIntra(TreeNode* cur,string& str);
void printPretra(TreeNode* cur,string& str);
bool isSymmetricaltree(TreeNode* root);
//递归版
bool issymmetricaltreenode(TreeNode* root);
bool processsymmetricaltree(TreeNode* root1,TreeNode* root2);
//22.顺时针打印矩阵
void processclockwiseprint(vector<vector<int> >& matrix,int row1,int col1,int row2,int col2);
//23.包含min函数的栈
class minstack{
private:
    stack<int> generalstack;
    stack<int> min_stack;
public:
    minstack(){ }
    void push(int val){
        if(min_stack.empty()){
            min_stack.push(val);
        }else{
            if(min_stack.top() > val)
                min_stack.push(val);
            else
                min_stack.push(min_stack.top());
        }
        generalstack.push(val);
    }
    int top(){
        return generalstack.top();
    }
    int min(){
        return min_stack.top();
    }
    void pop(){
        if(generalstack.empty())
            return;
        generalstack.pop();
        min_stack.pop();
    }
};
//24.栈的压入和弹出序列
bool ispushpopindex(vector<int>& pushed,vector<int>& popped);
//25.从上到下打印二叉树
void fromtoptobottomprinttree(TreeNode* root);
//26.分行从上到下打印二叉树
void detectfloortoptobottomtreeprint(TreeNode* root);
//27.之字形打印二叉树
void zhiwordprinttree(TreeNode* root);
//28.二叉树的后序遍历序列
bool isafttraveltree(TreeNode* root,vector<int>& nums);
void afttraveltreeprocess(TreeNode* root,vector<int>& nums);
//29.二叉树中和为某一值的路径
void printpathsum(TreeNode* root,int val);
void processpathsum(TreeNode* root,int val,vector<int>& nums,int sum);
//30.二叉搜索树与双向链表,中序遍历
TreeNode* binarysearchtreetolist(TreeNode* root);
//额外空间复杂度更低，时间复杂度也降低了
TreeNode* testconvert(TreeNode* root);
//31.数组中出现次数超过一半的数字
//先用哈希表来解决
int getmaxindexoccurnums(vector<int>& nums);
//再用桶排序来解决
int getmorethanhalfofnums(vector<int>& nums);
//32.最小的k个数
vector<int> minknumber(vector<int>& nums,int k);
//partion解法
vector<int> minknumbersofpartition(vector<int>& nums,int k);
int mypartition(vector<int>& nums,int mid,int start,int end);
//红黑树解法,适合大数据相关的题
vector<int> getlestnumbers(vector<int>& nums,int k);
//33.连续子数组的最大和
//O(n)时间复杂度的解法
int getmaxsumfortimen(vector<int>& nums);
//动态规划
int dpgetmaxsumfortimen(vector<int>& nums);
//34.1~n整数中1出现的次数
int numberprocess(int i);
long getcount1(int n);
//O(log(N))解法
int countDigitOne(int n);
//35.数字序列中某一位的数字
int digitindex(int index);
int countofintergers(int digits);
int digitatindex(int index,int digits);
int beginnumber(int digits);
//36.把数组排成最小的数
//整一个全排列，然后转成字符串比较大小，找出最小的
string processfullsort(vector<int>& nums,int i);
//直接转成字符串然后两两比较排列的大小
string minarrangementarray(vector<int>& nums);
//37.把数字翻译成字符串
int GettranslationCount(int number);
int numberstostring(string& nums,int i);
//进阶版解法，
int gettranlationcount(int number);
int gettranslationprocess(const string& number);
//38.礼物的最大价值,典型的动态规划问题
int getmaxvalueofgifts(vector<vector<int>>& matrix);
//39.丑数
int getgivenindexuglynumber(int index);
bool isuglynumber(int number);
//以空间换时间
int costspacefortimegetuglynumber(int n);
//40.第一个只出现一次的字符
char getfirstshowchar(string& str);
//附加题1.定义一个函数，输入两个字符，从第一个字符串中删除在第二个字符串中出现过的所有字符串
void deletecharshowinstr2(string& str1,string str2);
//附加题2.定义一个函数，删除字符串中所有重复出现的字符
void deletereshowchar(string& str);
//附加题3.判断输入的两个字符串是不是互为变位词
bool isuniquebitstring(string& str1,string str2);
//41.字符流中第一个只出现一次的字符
char charstreamfirstshowchar();
//42.数组中的逆序对
//O(N*N)
int inverseindexqueue(vector<int>& nums);
//利用归并排序的思想
int inverseindexprocess(vector<int>& arr,int l,int r);
int inverindexmerge(vector<int>& arr,int l,int mid,int r);
//43.两个链表的第一个公共节点
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB);
//44.在排序数组中查找数字
//44.1数字在排序数组中出现的次数
int getnumberstimes(vector<int>& nums,int k);
//44.2.0~n-1中缺失的数字
int getlosernumber(vector<int>& nums);
//44.3.数组中数值和下标相等的元素
int findvalueequalindexarray(vector<int>& nums);
//45.二叉搜索树的第k个大节点
//递归，简单
TreeNode* findknodebinarytree(TreeNode* root,int k);
//46.二叉树的深度
//46.1.二叉树的深度
int getdepthofbinarytree(TreeNode* root);
//46.2.平衡二叉树
struct rethandisb{
    bool isbalance;
    int height;
    rethandisb(bool isb,int h):isbalance(isb),height(h){ }
};
rethandisb isbalancetree(TreeNode* root);
//47.数组中数字出现的次数
//47.1.数组中只出现一次的两个数字
vector<int> findtwoonceshownumbers(vector<int>& nums);
//47.2.数组中唯一只出现一次的数字,如果一个数字出现三次，那么它的二进制表示每一位也出现三次。如果把所有出现三次的数字的二进制表示的每一位都分别加起来，那么每一位的和都能被3整除
int onyonceshownumber(vector<int>& nums);
//48.和为s的数字
//48.1.和为s的两个数字
vector<int> getsumoftwonumbers(vector<int>& nums,int s);
//O(N)的解法
vector<int> optimalgetsumoftwonumbers(vector<int>& nums,int s);
//48.2.和为s的连续整数序列,利用窗口的思路解决
void printcontinuousindex(int s);
//49.n个骰子的点数
void getprobabilitydice(int n);
void getsumdice(int n,int i,int sum,unordered_map<int,int>& nums);
//优化版
void printprobality(int n);
//50.扑克牌中的顺子
bool isshunzi(string& str);
//51.圆圈中最后剩下的数字
int getliveswordversion(int i,int m);
//swordtooffer
int lastremaining(unsigned int n,unsigned int m);
//52.股票的最大利润
int getmaxprofit(vector<int>& prices);
//优化版，降低时间复杂度
int bettertimegetmaxprofit(vector<int>& prices);
//最优版，最优的时间复杂度和额外空间复杂度
int optimalgetmaxprofit(vector<int>& prices);
//53.求1+2+3+...+n
template<unsigned int n>
struct sumsolution4{
    enum value{N = sumsolution4<n-1>::N +n};
};
//特化
template<>
struct sumsolution4<1>
{
    enum value{N = 1};
};
//54.不用加减乘除做加法
int addsum(int num1,int num2);
//55.构建乘积数组
void multiply(vector<int>& array1,vector<int>& array2);

#endif /* swordtooffer_hpp */
