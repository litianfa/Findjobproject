//
//  average_search.hpp
//  c++
//  二分搜索相关的题
//  Created by litianfa on 2019/7/5.
//  Copyright © 2019 litianfa. All rights reserved.
//

#ifndef average_search_hpp
#define average_search_hpp

#include <iostream>
#include <vector>
#include <stack>
using namespace std;
//案例1，给定一个无序数组arr,已知任意相邻的两个元素，值都不重复，请返回任意一个局部最小的位置
int partleastvalue(vector<int>& arr);
//案例2.给定一个有序数组，在给定一个整数，请在数组中找到给定数出现的最左边的位置
int lessleftpositionnum(vector<int>& arr,int num);
//案例3.给定一个有序循环数组，返回该数组中的最小值，有序循环数组是指有序数组的左边任意长度的部分放到右边去，右边的部分拿到左边来
int getminmumfromsortcyclearr(vector<int>& nums);
//案例4 给定一个有序数组nums，其中不含有重复的元素，请找到满足nums[i] == i条件的最左的位置，如果所有位置上的数都不满足条件，返回-1
int getleftindexofarr(vector<int>& nums);
//案例5 给定一颗完全二叉树的头节点，返回这个树的节点个数，如果完全二叉树的节点个数为N，请实现时间复杂度低于O(N)的解法
struct node{
    int val;
    struct node* left;
    struct node* right;
    node(int value):val(value),left(NULL),right(NULL){ }
};
struct returndata{
    int num;
    int lefth;
    returndata(int nums,int left):num(nums),lefth(left){ }
};
returndata getnumbertree(node* head);
//满二叉树节点数的计算公式
int calfulltreenumber(int k);
//案例6，如果更快的求一个整数K的N次方，如果两个整数相乘得到结果的时间复杂度为O（1），得到整数K的N次方的过程请实现时间复杂度为O(logN)的方法
long getplusresult(int k,int n);
//案例7.两有序数组的非公共部分问题,利用二分查找的概念改善时间复杂度O(log(N))
vector<int> getnotcommonvariable(vector<int>& a,vector<int>& b);

#endif /* average_search_hpp */
