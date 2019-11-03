//
//  stack_queue.cpp
//  c++
//
//  Created by litianfa on 2019/7/3.
//  Copyright © 2019 litianfa. All rights reserved.
//

#include "stack_queue.hpp"


//3.实现栈的逆序，要求只能用递归函数和这个栈本身的操作来实现，而不能自己申请另外的数据结构
void stackreverse(stack<int>& restack)
{
    if(restack.empty()){
        return ;
    }
    else{
        int last = processstack(restack);
        stackreverse(restack);
        restack.push(last);
    }
}
int processstack(stack<int>& restack)
{
    int ret = restack.top();
    restack.pop();
    if(restack.empty())
        return ret;
    else{
        int last = processstack(restack);
        restack.push(ret);
        return last;
    }
}
//4.栈排序,从栈顶到栈低按从大到小
void sortstack(stack<int>& source)
{
    stack<int> help;
    help.push(source.top());
    source.pop();
    int cur = 0;
    while(!source.empty()){
        cur = source.top();
        source.pop();
        while(!help.empty() && cur > help.top()){
            source.push(help.top());
            help.pop();
        }
        if(help.empty() || cur <= help.top()){
            help.push(cur);
        }
    }
    if(cur != help.top())
        help.push(cur);
    while(!help.empty()){
        source.push(help.top());
        help.pop();
    }
    return;
}
//5.返回窗口最大值，在一个整形数组和一个大小为w的窗口从数组的最左边滑倒最右边，窗口每滑动一下，返回一个长度为n-w+1的数组res,ress代表每一个窗口状态下的最大值
vector<int> maxSlidingWindow(vector<int> &nums, int k)
{
    vector<int> res;
    if(nums.empty()){
        return res;
    }
    if(nums.size()<k){
        int maxval = INT_MIN;
        for(int i = 0;i<nums.size();i++){
            maxval = max(maxval,nums[i]);
        }
        res.push_back(maxval);
        return res;
    }
    int n = (int)nums.size();
    deque<int> maxque;
    int index = 0;
    res.resize(n-k+1);
    for(int i = 0;i<n;i++){
        while(!maxque.empty() && nums[maxque.back()] <= nums[i]){
            maxque.pop_back();
        }
        maxque.push_back(i);
        if(maxque.front() == i-k){
            maxque.pop_front();
        }
        if(i>=k-1){
            res[index++] = nums[maxque.front()];
        }
    }
    return res;
}
//6.给定一个没有重复元素的数组arr,写出生成这个数组的MaxTree的函数，要求如果数组长度为N，则时间复杂度为O(N),额外空间复杂度为O(N)
void getmaxtree(vector<int>& arr)
{
    if(arr.empty()){
        return;
    }
    stack<int> gstack;
    unordered_map<int,int> recordnode;
    unordered_map<int,int>::iterator it;
    for(int i = 0;i<(int)arr.size();i++){
        while(!gstack.empty() && arr[i]>gstack.top()){
            it = recordnode.find(gstack.top());
            if(it != recordnode.end() && it->second > arr[i]){
                it->second = arr[i];
            }else if(it == recordnode.end()){
                recordnode.insert(make_pair(gstack.top(),arr[i]));
            }
            gstack.pop();
        }
        if(gstack.empty()){
            gstack.push(arr[i]);
            recordnode.insert(make_pair(arr[i],INT_MAX));
        }else{
            it = recordnode.find(arr[i]);
            if(it != recordnode.end() && it->second > gstack.top()){
                it->second = gstack.top();
            }else if(it == recordnode.end()){
                recordnode.insert(make_pair(arr[i],gstack.top()));
            }
            gstack.push(arr[i]);
        }
    }
    it = recordnode.begin();
    while(it != recordnode.end()){
        cout<<it->first<<" "<<it->second<<endl;
        ++it;
    }
    
    return ;
}
//11.子数组不大于给定整数的数量
//暴力解法
int subarraylessnum(vector<int> arr,int num)
{
    int res = 0;
    if(arr.empty())
        return 0;
    else
    {
        for(int start = 0;start<arr.size();start++){
            for(int end = start;end<arr.size();end++){
                if(islessnum(arr,start, end, num)){
                    ++res;
                }
            }
        }
    }
    return res;
}
bool islessnum(vector<int> arr,int start,int end,int num)
{
    int Max = INT_MIN;
    int Min = INT_MAX;
    for(int i = start;i<=end;i++){
        Max = max(Max,arr[i]);
        Min = min(Min,arr[i]);
    }
    return (Max-Min) <= num ? true : false;
}
//窗口解法
int windowsubarrlessnum(vector<int> arr,int num)
{
    int ret = 0;
    int L = 0;
    int R = 0;
    deque<int> lessdeque;
    deque<int> greaterdeque;
    while(L < arr.size()){
        while(R < arr.size()){
            while(!lessdeque.empty() && arr[lessdeque.back()] >= arr[R]){
                lessdeque.pop_back();
            }
            lessdeque.push_back(R);
            while(!greaterdeque.empty() && arr[greaterdeque.back()] <= arr[R]){
                greaterdeque.pop_back();
            }
            greaterdeque.push_back(R);
            if(arr[greaterdeque.front()] - arr[lessdeque.front()] > num){
                break;
            }
            ++R;
        }
        if(lessdeque.front() == L){
            lessdeque.pop_front();
        }
        if(greaterdeque.front() == L){
            greaterdeque.pop_front();
        }
        ret += R - L;
        ++L;
    }
    return ret;
}
//12.单调栈 用-1表示空
vector<arr_left_right> getarrleftright(vector<int> arr)
{
    vector<arr_left_right> ret;
    stack<int> recindex;
    int i = 0;
    while(i<arr.size()){
        while(!recindex.empty() && arr[recindex.top()] < arr[i]){
            int temp = recindex.top();
            recindex.pop();
            if(recindex.empty()){
                ret.push_back(arr_left_right(arr[temp],-1,arr[i]));
                break;
            }
            else
                ret.push_back(arr_left_right(arr[temp],arr[recindex.top()],arr[i]));
        }
        recindex.push(i);
        ++i;
    }
    if(!recindex.empty()){
        int temp = recindex.top();
        recindex.pop();
        if(recindex.empty()){
            ret.push_back(arr_left_right(arr[temp],-1,-1));
            return ret;
        }
        else
            ret.push_back(arr_left_right(arr[temp],arr[recindex.top()],-1));
        while(!recindex.empty()){
            int index = recindex.top();
            recindex.pop();
            if(recindex.empty()){
                ret.push_back(arr_left_right(arr[index],-1,arr[temp]));
                return ret;
            }
            else
                ret.push_back(arr_left_right(arr[index],arr[recindex.top()],arr[temp]));
            temp = index;
        }
    }
    return ret;
}

//13.求最大子矩阵的大小,利用单调栈结构
int maxsizearray(vector<vector<int> > arr)
{
    int maxsize = 0;
    int* help = new int[arr[0].size()];
    for(int i = 0;i<arr[0].size();i++){
        help[i] = 0;
    }
    for(int i = 0;i<arr.size();i++){
        for(int j = 0; j<arr[0].size();j++){
            help[j] = arr[i][j]== 0 ? 0 : help[j]+1;
        }
        maxsize = max(maxsize,maxsubmatrix(help,arr[0].size()));
    }
    return maxsize;
}
int maxsubmatrix(int* arr,int length)
{
    int maxarea = 0;
    stack<int> lessdeque;
    int i = 0;
    while(i < length){
        while(!lessdeque.empty() && arr[lessdeque.top()] >= arr[i]){
            int temp = lessdeque.top();
            lessdeque.pop();
            int k = lessdeque.empty() ? -1 : lessdeque.top();
            maxarea = max(maxarea,(i-k-1)*arr[temp]);
        }
        lessdeque.push(i);
        ++i;
    }
    while(!lessdeque.empty()){
        int temp = lessdeque.top();
        lessdeque.pop();
        int k = lessdeque.empty() ? -1 : lessdeque.top();
        maxarea = max(maxarea,(length-k-1)*arr[temp]);
    }
    return maxarea;
}
//14.山峰对问题
int nextindex(int i,int size)
{
    return i < size - 1 ? i+1 : 0;//因为是一个环形结构，所以在i = size-1时将其下一个位置置为0
}
long getInternalSum(int n)
{
    return n > 1 ? (long)(n*(n-1)/2L):0L;
}
long communication(vector<int> arr)
{
    if(arr.size()==1)
        return 1L;
    if(arr.empty())
        return 0L;
    int maxIndex = 0;
    int size = (int)arr.size();
    for(int i = 1;i<size;i++){
        maxIndex = arr[maxIndex]>arr[i]?maxIndex:i;
    }
    int value = arr[maxIndex];
    int index = nextindex(maxIndex,size);
    stack<Tpair> dullstack;
    dullstack.push(value);
    long res = 0L;
    while(index != maxIndex){
        value = arr[index];
        while(!dullstack.empty() && value > dullstack.top().value){
            int times = dullstack.top().times;
            dullstack.pop();
            res += getInternalSum(times) + 2*times;
        }
        if(!dullstack.empty() && value == dullstack.top().value){
            dullstack.top().times++;
        }
        else{
            dullstack.push(value);
        }
        index = nextindex(index,size);
    }
    while(!dullstack.empty()){
        int times = dullstack.top().times;
        dullstack.pop();
        res += getInternalSum(times);
        if(!dullstack.empty()){
            res += times;
            if(dullstack.size() > 1){
                res += times;
            }
            else{
                res += dullstack.top().times > 1 ? times : 0;
            }
        }
    }
    return res;
}
