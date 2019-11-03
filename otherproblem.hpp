//
//  otherproblem.hpp
//  c++
//  各种问题汇集
//  Created by litianfa on 2019/7/11.
//  Copyright © 2019 litianfa. All rights reserved.
//

#ifndef otherproblem_hpp
#define otherproblem_hpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <unordered_set>
using namespace std;

//案例1，占用会议室问题,最多能够安排多少场项目会议
class project{
public:
    int start;
    int end;
public:
    project(int _start,int _end):start(_start),end(_end){ }
};

class projectcompare{
public:
    bool operator()(project const& a,project const& b){
        return a.end<b.end?true:false;
    }
};
int bestArrange(vector<project>& nums);
//案例2，汉诺塔问题
void hanuota(int n);
void hanuoprocess(int n,string from,string mid,string to);
//案例3，IPO，给予一定本金承包项目，每个项目都有一定的前期投资要求，和利润大小，求出最大可以获得的收益
class Node{
public:
    int p; //profit
    int c; //cost
public:
    Node(int _p=0,int _c=0):p(_p),c(_c) { }
    Node(Node const& obj):c(obj.c),p(obj.p){
        
    }
    Node operator=(Node const& obj){
        return Node(obj);
    }
};

class MinCostComparator:public Node{
public:
    int operator()(Node o1,Node o2){
        return o1.c-o2.c;
    }
};

class MaxProfitComparator:public Node{
public:
    int operator()(Node o1,Node o2){
        return o2.p-o1.p;
    }
};
int findMaximizedCapital(int k,int W,vector<int> Profits,vector<int> Capital);
//案例4，母牛问题
int muniu(int n);
//案例5，岛问题
int daoproblem(vector<vector<int> > matrix);
void infect(vector<vector<int> >& matrix,int i,int j);
//案例6，轮廓问题
class buildingnode{
public:
    bool isUp;
    int pos;
    int height;
public:
    buildingnode(){ }
    buildingnode(bool isup,int position,int buildheight):isUp(isup),pos(position),height(buildheight){ }
    buildingnode(const buildingnode& obj){
        isUp = obj.isUp;
        pos = obj.pos;
        height = obj.height;
    }
    buildingnode& operator=(const buildingnode& obj){
        isUp = obj.isUp;
        pos = obj.pos;
        height = obj.height;
        return *this;
    }
};
//声明仿函数
class nodecompare{
public:
    bool operator()(buildingnode a,buildingnode b)
    {
        if(a.pos != b.pos)
            return a.pos<b.pos;
        if(a.isUp != b.isUp)
            return a.isUp ? false : true;
        if(a.height!=b.height)
            return a.height<b.height;
        return false;
    }
};
vector<vector<int> > buildingoutline(vector<vector<int> > buildings);

//案例7，累加和为给定值的最长子数组
int maxlenghtofsum(vector<int> arr,int aim);

//案例8，异或和为0的子数组最多的个数
int maxnumberxorarr(vector<int> arr);

//从此初开始，是剑指offer书中的题目
//案例9，数组中重复的数字
//利用哈希表来找出重复数组成员，时间复杂度为O(N),空间复杂度O(1)
vector<int> getpardonvariable(vector<int>& nums);
//用桶排序试一试
vector<int> tonggetpardonvar(vector<int>& nums);

//案例10，二维数组中的查找,二维数组中从左到右依次递增，从上到下依次递增，思路从右上角开始查找，时间复杂度小于O(N)
bool getvalueofmatrix(vector<vector<int> >& matrix,int val);
//案例11，替换字符串的空格
string changespacestring(string& str);
//相关题目，有两个排序的数组A1和A2，内存在A1的末尾有足够多的空余空间容纳A2.请实现一个函数，把A2中的所有数字插入A1中，并且所有的数字都是排序的。思路类似，还是从后向前复制先比较两数组最后一个成员的大小，将大的放进去，依次向前复制
void copysortarr(vector<int>& a1,vector<int>& a2);
//案例12，从尾到头打印链表，输入一个链表的头节点，从尾到头反过来打印出每个节点的值
struct ListNode{
    int val;
    struct ListNode* next;
    ListNode(int value):val(value),next(NULL){ }
};
void printfromendtostart(ListNode* head);
//案例13，重建二叉树，输入二叉树的前序和中序遍历的结果，请重建二叉树
struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(int value):val(value),left(NULL),right(NULL){ }
};
TreeNode* rebuildTree(vector<int>& pre,vector<int>& In);

#endif /* otherproblem_hpp */
