//
//  Sort.cpp
//  c++
//
//  Created by litianfa on 2019/7/2.
//  Copyright © 2019 litianfa. All rights reserved.
//

#include "Sort.hpp"

//1.冒泡排序
void maopaosort(vector<int>& arr)
{
    int len = (int)arr.size();
    for(int i = 0;i<len;i++){
        for(int j = i+1;j<len;j++){
            if(arr[i]>arr[j]){
                swap(arr[i],arr[j]);
            }
        }
    }
    return;
}
//冒泡排序优化,通过记录内排序是否出现交换
void maopaoSortOptimal(vector<int>& arr){
    if(arr.size()<=1){
        return;
    }
    bool flag = false;
    for(int i = (int)(arr.size()-1);i>0;i--){
        flag = false;
        for(int j = 0;j<i;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
                flag = true;
            }
        }
        if(flag == false){
            break;
        }
    }
    return;
}
//2.选择排序
void selectsort(vector<int>& arr)
{
    int minindex = INT_MAX;
    for(int i = 0;i<arr.size();i++){
        minindex = i;
        for(int j = i+1;j<arr.size();j++){
            minindex = arr[minindex] > arr[j] ? j : minindex;
        }
        swap(arr[minindex],arr[i]);
    }
    return;
}
//3.插入排序,选一个位置然后从这个位置向前出发，两两进行比较排序，每一次都会把选定位置的区段的最小值放到最前边，沿途相邻的两个数一定是小的值在前面，大的值在后面
void insertsort(vector<int>& arr)
{
    for(int i = 1;i<arr.size();i++){
        for(int j = i-1;j>=0 && arr[j]>arr[j+1];j--){
            swap(arr[j],arr[j+1]);
        }
    }
    return;
}
//4.归并排序
void intergesort(vector<int> &arr)
{
    process(arr,0,(int)arr.size()-1);
    return;
}
void process(vector<int>& arr,int l,int r)
{
    if(l == r){
        return;
    }
    int mid = l + (r-l-1)/2;
    process(arr,l,mid);
    process(arr,mid+1,r);
    merge(arr,l,mid,r);
    return;
}
void merge(vector<int>& arr,int l,int mid,int r)
{
    vector<int> help;
    help.resize(r-l+1);
    int p1 = l;
    int p2 = mid+1;
    int i = 0;
    while(p1<=mid && p2 <= r){
        help[i++] = arr[p1]<=arr[p2]?arr[p1++]:arr[p2++];
    }
    while(p1<=mid){
        help[i++] = arr[p1++];
    }
    while(p2<=r){
        help[i++] = arr[p2++];
    }
    for(int j = 0;j<help.size();j++){
        arr[l+j] = help[j];
    }
    return;
}
//4.1求无序数组的每个元素前比他小的所有小和
int minsum(vector<int>& arr)
{
    return minsumprocess(arr,0,(int)arr.size()-1);
}

int minsumprocess(vector<int>& arr,int l,int r){
    if(l == r)
        return 0;
    int mid = l+(r-l-1)/2;
    return minsumprocess(arr,l,mid)+minsumprocess(arr,mid+1,r)+minsummerge(arr,l,mid,r);
    
}

int minsummerge(vector<int>& arr,int l,int mid,int r)
{
    vector<int> help;
    help.resize(r-l+1);
    int p1 = l;
    int p2 = mid+1;
    int i = 0;
    int res = 0;
    while(p1<=mid && p2 <= r){
        res += arr[p1]<arr[p2]?(r-p2+1)*arr[p1]:0;
        help[i++] = arr[p1]<=arr[p2]?arr[p1++]:arr[p2++];
    }
    while(p1<=mid){
        help[i++] = arr[p1++];
    }
    while(p2<=r){
        help[i++] = arr[p2++];
    }
    for(int j = 0;j<help.size();j++){
        arr[l+j] = help[j];
    }
    return res;
}
//5.快速排序
void quicksort(vector<int>& arr,int l,int r)
{
    if(l < r){
        swap(arr[rand() % (r-l) + l],arr[r]);
        vector<int> ret = Partition(arr, l, r);
        quicksort(arr,l,ret[0]-1);
        quicksort(arr,ret[1]+1,r);
    }
    return;
}
vector<int> Partition(vector<int>& arr,int l,int r)
{
    int small = l-1;
    int big = r;
    int cur = l;
    while(cur < big){
        if(arr[cur]<arr[r]){
            swap(arr[++small],arr[cur++]);
        }
        else if(arr[cur] == arr[r]){
            cur++;
        }
        else if(arr[cur]>arr[r]){
            swap(arr[--big],arr[cur]);
        }
    }
    swap(arr[big],arr[r]);
    vector<int> ret;
    ret.resize(2);
    ret[0] = small+1;
    ret[1] = big;
    return ret;
}
//6.堆排序
void heapsort(vector<int>& arr)
{
    int len = (int)arr.size();
    for(int i = 0;i<len;i++){
        heapindex(arr,i);
    }
    swap(arr[0],arr[--len]);
    while(len>0){
        heapfy(arr,0,len);
        swap(arr[0],arr[--len]);
    }
    return;
}
//不断的调整维持大根堆结构
void heapfy(vector<int>& arr,int index,int size)
{
    int left = index*2+1;
    while(left<size){
        int maxindex = left+1<size && arr[left+1]>arr[left]?left+1:left;
        maxindex = arr[index]>arr[maxindex]?index:maxindex;
        if(index == maxindex){
            break;
        }
        swap(arr[index],arr[maxindex]);
        index = maxindex;
        left = index*2+1;
    }
}
//实现一个大根堆
void heapindex(vector<int>& arr,int index)
{
    while(arr[index]>arr[(index-1)/2]){
        swap(arr[index],arr[(index-1)/2]);
        index = (index-1)/2;
    }
    return;
}
//7.桶排序
//7.1计数排序
void buketsort(vector<int>& arr)
{
    int maxindex = 0;
    for(int i = 0;i<arr.size();i++){
        maxindex = max(maxindex,arr[i]);
    }
    vector<int> buket(0,maxindex+1);
    buket.resize(maxindex+1);
    for(int i = 0;i<arr.size();i++){
        buket[arr[i]]++;
    }
    int j = 0;
    for(int i = 0;i<=maxindex;i++){
        while(buket[i]>0){
            arr[j++] = i;
            buket[i]--;
        }
    }
}
//利用桶的思想求排序之后两数之间的最大差值
int maxgap(vector<int>& arr)
{
    if(arr.size()<1){
        return 0;
    }
    int maxval = INT_MIN,minval = INT_MAX;
    for(int i  =0;i<arr.size();i++){
        maxval = max(maxval,arr[i]);
        minval = min(minval,arr[i]);
    }
    int len = (int)arr.size();
    vector<bool> hasval(false,len+1);
    vector<int> maxvalue(0,len+1);
    vector<int> minvalue(0,len+1);
    hasval.resize(len+1);
    maxvalue.resize(len+1);
    minvalue.resize(len+1);
    for(int i = 0;i<len;i++){
        int index = retindex(arr,i,maxval,minval,len);
        maxvalue[index] = hasval[index]?(maxvalue[index]>arr[i]?maxvalue[index]:arr[i]):arr[i];
        minvalue[index] = hasval[index]?(minvalue[index]<arr[i]?minvalue[index]:arr[i]):arr[i];
        hasval[index] = true;
    }
    int mincalvalue = maxvalue[0];
    int maxcalvalue = INT_MIN;
    for(int j = 1;j<len+1;j++){
        if(hasval[j]){
            maxcalvalue = max(maxcalvalue,minvalue[j]-mincalvalue);
            mincalvalue = maxvalue[j];
        }
    }
    return maxcalvalue;
}
int retindex(vector<int>& arr,int index,int max,int min,int len)
{
    return (int)(arr[index]-min)*len/(max-min);
}


/***各种排序附加问题***/
//1.荷兰国旗问题，给定数组中只有0，1，2三种数，要求小于1的放左边，大于1的放右边，等于1的放中间
void helanpartition(vector<int>& arr,int l,int r)
{
    int less = l-1;
    int more = r;
    while(l<more){
        if(arr[l]<arr[r]){
            swap(arr[++less],arr[l++]);
        }
        else if(arr[l] == arr[r]){
            l++;
        }
        else if(arr[l]>arr[r]){
            swap(arr[l],arr[--more]);
        }
    }
    swap(arr[r],arr[more]);
    return;
}
//2.需要排序的最短连续子数组
int findUnsortedSubarray(vector<int>& nums)
{
    //先从左往右遍历数组，找当前数小于当前最大值的数组成员，记录最右边界
    int maxval = INT_MIN;
    int rightedge = 0;
    for(int i = 0;i<nums.size();i++){
        maxval = max(nums[i],maxval);
        if(nums[i]<maxval)
            rightedge = i;
    }
    //从右往左遍历数组，找当前值大于当前最小值的数组成员，记录最左边界
    int minval = INT_MAX;
    int leftedge = (int)nums.size()-1;
    for(int i = (int)nums.size()-1;i>=0;i--){
        minval = min(minval,nums[i]);
        if(nums[i]>minval)
            leftedge = i;
    }
    if(rightedge<=leftedge)
        return 0;
    else
        return rightedge-leftedge+1;
}
//3.两个有序数组的公共子序列,谁小谁先走
vector<int> getcommonsubarr(vector<int>& arr1,vector<int>& arr2)
{
    vector<int> ret;
    if(arr1.empty() || arr2.empty()){
        return ret;
    }
    int l = 0;
    int r = 0;
    while(l<arr1.size() && r< arr2.size()){
        if(arr1[l] < arr2[r]){
            l++;
        }else if(arr1[l] == arr2[r]){
            l++;
            r++;
            ret.push_back(arr1[l]);
        }else{
            r++;
        }
    }
    return ret;
}
//4.求最大消费金额，利用小根堆和大根堆的结构来减小时间复杂度O(log(N)),就是用大顶堆和小顶堆的思路来不断弹出金额数最大且在每桌容量允许的范围内
int maxconsumptionmoney(vector<int>& arr)
{
    int n = arr[0]; //一共有多少张桌子
    int m = arr[1];
    int i = 0;
    int maxconsume = 0;
    vector<int> desk;
    for(i=2;i<2+n;i++){
        desk.push_back(arr[i]);
    }
    sort(desk.begin(),desk.end(),[](int a,int b){ return a<b; });
    priority_queue<customer,vector<customer>,greater<customer> > cuspeople;
    customer temp;
    while(i<2*m+n+2){
        temp.total_people = arr[i++];
        temp.consume = arr[i++];
        cuspeople.push(temp);
    }
    priority_queue<customer,vector<customer>,less<customer> > cusconsume;
    i = 0;
    while(i<n){
        while((cuspeople.top()).total_people<desk[i]){
            cusconsume.push(cuspeople.top());
            cuspeople.pop();
        }
        maxconsume += (cusconsume.top()).consume;
        cusconsume.pop();
        ++i;
    }
    return maxconsume;
}
//5.阶乘求末尾零的个数
int plusend(int n)
{
    if(n < 5){
        return 0;
    }
    return n/5+ plusend(n/5);
}
//6.进制转换全功能版
string optimalconvertbit(int m,int n)
{
    string s = "",table = "0123456789ABCDEF";
    if(m>=0)//m为正整数或者0
    {
        while(m){
            s = table[m%n]+s;
            m/=n;
        }
    }
    else//m为负整数
    {
        unsigned int h = 4294967295 + m + 1;
        if(n == 10){
            return "-"+to_string(m);
        }
        else{
            while(h){
                s = table[h%n]+s;
                h/=n;
            }
        }
    }
    return s;
}
//7.BFPRT Algorithm  1)分组 2)组内用插入排序 3)拿出每组的中位数组成N/5d大小的数组 4)递归调用BFPRT 5)Partition
int select(vector<int>& arr, int begin, int end, int i)
{
    if(begin == end)
        return arr[begin];
    int pivot = medianOfMedians(arr, begin, end);
    vector<int> pivotRange = bfprtpartition(arr,begin,end,pivot);
    if(i>=pivotRange[0] && i<= pivotRange[1]){
        return arr[i];
    }else if(i<pivotRange[0]){
        return select(arr,begin,pivotRange[0]-1,i);
    }else{
        return select(arr,pivotRange[1]+1,end,i);
    }

}
int medianOfMedians(vector<int>& arr, int begin, int end)
{
    int num = end-begin+1;
    int offset = num%5 == 0?0:1;
    vector<int> marr;
    marr.resize(num/5+offset);
    for(int i = 0;i<marr.size();i++){
        int beginI = begin+i*5;
        int endI = beginI+4;
        marr[i] = getMedian(arr, beginI, min(endI,end));
    }
    return select(marr,0,(int)(marr.size()-1),(int)(marr.size()/2));
}
void insertionSort(vector<int>& arr, int begin, int end)//插入排序
{
    for(int i = begin+1;i<=end;i++){
        for(int j = i-1;j>=0 && arr[j]>arr[j+1];j--){
            swap(arr[j],arr[j+1]);
        }
    }
}
int getMedian(vector<int>& arr, int begin, int end)
{
    insertionSort(arr,begin,end);
    int sum = end+begin;
    int mid = (sum/2)+(sum%2);
    return arr[mid];
}
vector<int> bfprtpartition(vector<int>& arr, int begin, int end, int pivotValue)
{
    int less = begin-1;
    int more = end+1;
    while(begin < more){
        if(arr[begin]<pivotValue){
            swap(arr[++less],arr[begin++]);
        }else if(arr[begin] == pivotValue){
            begin++;
        }else {
            swap(arr[--more],arr[begin]);
        }
    }
    vector<int> ret;
    ret.resize(2);
    ret[0] = less+1;
    ret[1] = more-1;
    return ret;
}
//利用BFPRT进行快速排序,实现时间复杂度为O(N)的排序算法
void quick_bfprt_sort(vector<int>& arr,int left,int right)
{
    if(left<right){
        int pivot = medianOfMedians(arr, left, right);
        vector<int> pivotRange = bfprtpartition(arr, left, right, pivot);
        quick_bfprt_sort(arr,left,pivotRange[0]-1);
        quick_bfprt_sort(arr,pivotRange[1]+1,right);
    }
}
//10,切金条,利用大根堆，本质跟堆排序差不多
int cutGoldSolid(vector<int> vtr)
{
    priority_queue<int , vector<int> ,greater<int> > ptr;
    int sum = 0;
    int total = 0;
    for(int i = 0;i<vtr.size();i++){
        ptr.push(vtr[i]);
    }
    while(!ptr.empty()){
        sum = ptr.top();
        ptr.pop();
        sum += ptr.top();
        ptr.pop();
        total += sum;
        if(ptr.empty()){
            return total;
        }
        ptr.push(sum);
    }
    return total;
}
//11.求最大利润
int getBiggestProfit(vector<int> cost,vector<int> profit,int k,int m)
{
    map<int,int,less<int> > costmap;
    map<int,int,greater<int> > profitmap;
    int count = 0;
    for(int i = 0;i<cost.size();i++){
        costmap.insert(pair<int,int>(cost[i],profit[i]));
    }
    map<int,int>::iterator it = costmap.begin();
    map<int,int>::iterator itprofit = profitmap.begin();
    while(count < k){
        while(m >= it->first && it != costmap.end()){
            profitmap.insert(pair<int,int>(it->second,it->first));
            ++it;
        }
        if(!profitmap.empty()){
            itprofit = profitmap.begin();
            m += itprofit->first;
            profitmap.erase(itprofit->first);
            count++;
        }
    }
    return m;
}
