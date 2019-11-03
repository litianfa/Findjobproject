//
//  Sort.hpp
//  c++
//
//  Created by litianfa on 2019/7/2.
//  Copyright © 2019 litianfa. All rights reserved.
//

#ifndef Sort_hpp
#define Sort_hpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

//1.冒泡排序
void maopaosort(vector<int>& arr);
//冒泡排序优化,通过记录内排序是否出现交换
void maopaoSortOptimal(vector<int>& arr);
//2.选择排序
void selectsort(vector<int>& arr);
//3.插入排序
void insertsort(vector<int>& arr);
//4.归并排序
void intergesort(vector<int> &arr);
void process(vector<int>& arr,int l,int r);
void merge(vector<int>& arr,int l,int mid,int r);
//4.1求无序数组的每个元素前比他小的所有小和
int minsum(vector<int>& arr);
int minsumprocess(vector<int>& arr,int l,int r);
int minsummerge(vector<int>& arr,int l,int mid,int r);
//5.快速排序
void quicksort(vector<int>& arr,int l,int r);
vector<int> Partition(vector<int>& arr,int l,int r);
//6.堆排序
void heapsort(vector<int>& arr);
//不断的调整维持大根堆结构
void heapfy(vector<int>& arr,int index,int size);
//实现一个大根堆
void heapindex(vector<int>& arr,int index);
//7.桶排序
void buketsort(vector<int>& arr);
//利用桶的思想求排序之后两数之间的最大差值
int maxgap(vector<int>& arr);
int retindex(vector<int>& arr,int index,int max,int min,int len);

/***各种排序附加问题***/
//1.荷兰国旗问题，给定数组中只有0，1，2三种数，要求小于1的放左边，大于1的放右边，等于1的放中间
void helanpartition(vector<int>& arr,int l,int r);
//2.需要排序的最短连续子数组
int findUnsortedSubarray(vector<int>& nums);
//3.两个有序数组的公共子序列,谁小谁先走
vector<int> getcommonsubarr(vector<int>& arr1,vector<int>& arr2);
//4.求最大消费金额，利用小根堆和大根堆的结构来减小时间复杂度O(log(N)),就是用大顶堆和小顶堆的思路来不断弹出金额数最大且在每桌容量允许的范围内
struct customer{
    int total_people;
    int consume;
    bool operator>(struct customer const& a) const{
        return this->total_people>a.total_people;
    }
    bool operator<(struct customer const& a) const{
        return this->consume<a.consume;
    }
};
int maxconsumptionmoney(vector<int>& arr);
//5.阶乘求末尾零的个数
int plusend(int n);
//6.进制转换全功能版
string optimalconvertbit(int m,int n);
//7.BFPRT Algorithm  1)分组 2)组内用插入排序 3)拿出每组的中位数组成N/5d大小的数组 4)递归调用BFPRT 5)Partition
int select(vector<int>& arr, int begin, int end, int i);
int medianOfMedians(vector<int>& arr, int begin, int end);
void insertionSort(vector<int>& arr, int begin, int end);
int getMedian(vector<int>& arr, int begin, int end);
vector<int> bfprtpartition(vector<int>& arr, int begin, int end, int pivotValue);
//8.利用BFPRT进行快速排序,实现时间复杂度为O(N)的排序算法
void quick_bfprt_sort(vector<int>& arr,int left,int right);
//9.在数据流中随时找到中位数
//解题思路：建立一个大根堆和一个小根堆，每次加进来的数先放大根堆，当大根堆的size比小根堆的size大2，那就把大根堆的堆顶弹出加入小根堆，之后再重复以上的步骤
class MedianHolder{
private:
    priority_queue<int,vector<int>,less<int> > bigholder;
    priority_queue<int,vector<int>,greater<int> > smallholder;
    
public:
    //默认构造函数
    //成员函数大都被隐式的声明为内联函数
    void addNum(int num)
    {
        bigholder.push(num);        // Add to max heap
        
        smallholder.push(bigholder.top());    // balancing step
        bigholder.pop();
        
        if (bigholder.size() < smallholder.size()) { // maintain size property
            bigholder.push(smallholder.top());
            smallholder.pop();
        }
    }
    
    // Returns the median of current data stream
    double findMedian()
    {
        return bigholder.size() > smallholder.size() ? (double) bigholder.top() : (bigholder.top() + smallholder.top()) * 0.5;
    }
};

//10,切金条,利用大根堆，本质跟堆排序差不多
int cutGoldSolid(vector<int> vtr);
//11.求最大利润
int getBiggestProfit(vector<int> cost,vector<int> profit,int k,int m);

#endif /* Sort_hpp */
