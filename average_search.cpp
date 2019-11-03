//
//  average_search.cpp
//  c++
//
//  Created by litianfa on 2019/7/5.
//  Copyright © 2019 litianfa. All rights reserved.
//

#include "average_search.hpp"
//案例1，给定一个无序数组arr,已知任意相邻的两个元素，值都不重复，请返回任意一个局部最小的位置
int partleastvalue(vector<int>& arr)
{
    if(arr.empty())
        return 0;
    if(arr.size() == 1 || (arr.size() == 2 && arr[0] < arr[1])){
        return arr[0];
    }
    else if(arr.size() == 2 && arr[0] > arr[1])
    {
        return arr[1];
    }
    int l = 0;
    int r = (int)arr.size()-1;
    if(arr[l]<arr[l+1]){
        return arr[l];
    }
    if(arr[r]<arr[r-1]){
        return arr[r];
    }
    while(l<r){
        int mid = l+(r-l)/2;
        if(arr[mid] <arr[mid-1] && arr[mid] < arr[mid+1]){
            return arr[mid];
        }
        else if(arr[mid] >arr[mid-1]){
            r = mid-1;
        }
        else if(arr[mid] > arr[mid+1]){
            l = mid+1;
        }
    }
    return 0;
}
//案例2.给定一个有序数组，在给定一个整数，请在数组中找到给定数出现的最左边的位置
int lessleftpositionnum(vector<int>& arr,int num)
{
    int l = 0;
    int r = (int)arr.size()-1;
    while(l<r){
        int mid = l + (r-l)/2;
        if(arr[mid] == num || arr[mid] > num){
            r = mid-1;
        }
        else if(arr[mid] < num){
            l = mid+1;
        }
    }
    return l;
}
//案例3.给定一个有序循环数组，返回该数组中的最小值，有序循环数组是指有序数组的左边任意长度的部分放到右边去，右边的部分拿到左边来
//有重复值的版本
int getminmumfromsortcyclearr(vector<int>& nums)
{
    if(nums.size() == 1)
        return nums[0];
    int l = 0;
    int r = (int)nums.size()-1;
    if(nums[l]<nums[r]){
        return nums[l];
    }
    while(l<r){
        int mid = l+(r-l)/2;
        if(nums[mid] < nums[l]){
            r = mid;
        }else if(nums[mid] > nums[r]){
            l = mid+1;
        }else if(nums[l]<nums[r]){
            return nums[l];
        }else if(nums[l] == nums[r]){
            break;
        }
    }
    if(l != r){
        int minval = INT_MAX;
        for(int i = l;i<r;i++){
            minval = min(minval,nums[i]);
        }
        return minval;
    }
    return nums[l];
}
//案例4 给定一个有序数组nums，其中不含有重复的元素，请找到满足nums[i] == i条件的最左的位置，如果所有位置上的数都不满足条件，返回-1
int getleftindexofarr(vector<int>& nums)
{
    int l = 0;
    int r = (int)nums.size()-1;
    if(nums[l] >= r || nums[r] <= 0)
        return -1;
    while(l<r){
        int mid = l+(r-l)/2;
        if(nums[mid]>mid){
            r = mid-1;
        }
        else if(nums[mid]<mid){
            l = mid+1;
        }else if(nums[mid] == mid){
            r = mid;
        }
    }
    return l;
}
//案例5 给定一颗完全二叉树的头节点，返回这个树的节点个数，如果完全二叉树的节点个数为N，请实现时间复杂度低于O(N)的解法
returndata getnumbertree(node* head)
{
    if(head == NULL){
        return returndata(0,0);
    }
    returndata leftdata = getnumbertree(head->left);
    returndata rightdata = getnumbertree(head->right);
    //情况1，右子树最左的节点在最深层
    if(leftdata.lefth == rightdata.lefth){
        leftdata.num = calfulltreenumber(leftdata.lefth);
    }
    //情况2，右子树最左的节点不在最深层，在次深层
    if(rightdata.lefth == leftdata.lefth-1){
        rightdata.num = calfulltreenumber(rightdata.lefth);
    }
    return returndata(rightdata.num+leftdata.num+1,leftdata.lefth+1);
}
//满二叉树节点数的计算公式
int calfulltreenumber(int k)
{
    int ret = 1;
    while(k>0){
        ret = ret*2;
        k--;
    }
    ret--;
    return ret;
}
//案例6，如果更快的求一个整数K的N次方，如果两个整数相乘得到结果的时间复杂度为O（1），得到整数K的N次方的过程请实现时间复杂度为O(logN)的方法
long getplusresult(int k,int n)
{
    vector<int> arr;
    long result = 1;
    long temp = k;
    while(n != 0){
        arr.push_back(n%2);
        n = n/2;
    }
    for(int i = 0;i<arr.size();i++){
        if(arr[i] == 1){
            result = result * temp;
        }
        temp = temp*temp;
    }
    return result;
}
//案例7.两有序数组的非公共部分问题,利用二分查找的概念改善时间复杂度O(log(N))
vector<int> getnotcommonvariable(vector<int>& a,vector<int>& b)
{
    vector<int> ret;
    bool contains = false;
    for(int i = 0;i<b.size();i++){
        int l = 0;
        int r = (int)a.size()-1;
        contains = false;
        while(l<r){
            int mid =  l+(r-l)/2;
            if(a[mid] == b[i]){
                contains = true;
                break;
            }else if(a[mid] < b[i]){
                l = mid+1;
            }else{
                r = mid-1;
            }
        }
        if(contains){
            ret.push_back(b[i]);
        }
    }
    return ret;
}
