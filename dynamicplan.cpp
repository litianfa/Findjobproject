//
//  dynamicplan.cpp
//  c++
//
//  Created by litianfa on 2019/7/8.
//  Copyright © 2019 litianfa. All rights reserved.
//

#include "dynamicplan.hpp"
//换钱的方法数
//先递归实现
int changemoney(vector<int>& arr,int aim,int i)
{
    if(aim == 0)
        return 1;
    if(i == arr.size() || aim<0)
        return 0;
    int ret = 0;
    for(int j = 0;j*arr[i]<=aim;j++){
        ret += changemoney(arr, aim-j*arr[i], i+1);
    }
    return ret;
}
//动态规划版本
int dpchangemoney(vector<int>& arr,int aim)
{
    int** dp = new int*[arr.size()];
    for(int i = 0;i<arr.size();i++){
        dp[i] = new int[aim+1];
    }
    for(int i = 0;i<arr.size();i++){
        dp[i][0] = 1;
    }
    for(int j = 1;j<aim+1;j++){
        dp[0][j] = 0;
    }
    for(int j = 0;j*arr[0]<=aim;j++){
            dp[0][j*arr[0]] = 1;
    }
    for(int i = 1;i<arr.size();i++){
        for(int j = 1;j<aim+1;j++){
            dp[i][j] = dp[i-1][j];
            dp[i][j] += j-arr[i]>=0 ? dp[i][j-arr[i]]:0;
        }
    }
    int ret = dp[arr.size()-1][aim];
    for(int i = 0;i<arr.size();i++){
        delete[] dp[i];
    }
    delete[] dp;
    return ret;
}
//案例1，有N级台阶，一个人每次上一级或者两级，问有多少种方法走完N级台阶的方法
//递归版
int taijie(int n)
{
    if(n == 0)
        return 1;
    if(n < 0)
        return 0;
    return taijie(n-1)+taijie(n-2);
}
//动态规划版
int dptaijie(int n)
{
    int* dp = new int[n+1];
    dp[0] = 1;
    dp[1] = 1;
    for(int i = 2;i<=n;i++)
    {
        dp[i] = dp[i-1]+dp[i-2];
    }
    int ret = dp[n];
    delete[] dp;
    return ret;
}
//案例2，矩阵的最小路径和
//递归版
int matrixminpathsum(vector<vector<int> >& matrix,int i,int j)
{
    if(i == matrix.size()-1 && j == matrix[0].size()-1)
        return matrix[i][j];
    else if(i == matrix.size()-1)
        return matrixminpathsum(matrix,i,j+1);
    else if(j == matrix[0].size()-1)
        return matrixminpathsum(matrix,i+1,j);
    else
        return min(matrixminpathsum(matrix,i+1,j),matrixminpathsum(matrix,i,j+1));
}
//动态规划版
int dpmatrixminpathsum(vector<vector<int> >& matrix)
{
    int** dp = new int*[matrix.size()];
    for(int i = 0;i<matrix.size();i++){
        dp[i] = new int[matrix[0].size()];
    }
    dp[0][0] = matrix[0][0];
    for(int i = 1;i<matrix.size();i++){
        dp[i][0] = dp[i-1][0]+matrix[i][0];
    }
    for(int j = 1;j<matrix[0].size();j++){
        dp[0][j] = dp[0][j-1]+matrix[0][j];
    }
    for(int i = 1;i<matrix.size();i++){
        for(int j = 1;j<matrix[0].size();j++){
            dp[i][j] = min(dp[i-1][j],dp[i][j-1])+matrix[i][j];
        }
    }
    int ret = dp[matrix.size()-1][matrix[0].size()-1];
    for(int i = 0;i<matrix.size();i++){
        delete[] dp[i];
    }
    delete[] dp;
    return ret;
}
//案例3最长递增子序列
//递归版
int lengthofLIS(vector<int>& nums)
{
    return getlengthoflis(nums, INT_MIN, 0);
}
int getlengthoflis(vector<int>& nums,int preval,int curpos)
{
    if(curpos == nums.size())
        return 0;
    int takein = 0,takeout = 0;
    if(nums[curpos] > preval){
        takein = 1+getlengthoflis(nums,nums[curpos],curpos+1);
    }
    takeout = getlengthoflis(nums,preval,curpos+1);
    return max(takein,takeout);
}
//动态规划版
int dplengthofLIS(vector<int>& nums)
{
    if(nums.empty()){
        return 0;
    }
    vector<int> dp;
    dp.resize((int)nums.size());
    for(int i = 0;i<nums.size();i++){
        dp[i] = 1;
    }
    int ret = 1;
    for(int i = 1;i<nums.size();i++){
        for(int j = 0;j<i;j++){
            if(nums[j]<nums[i]){
                dp[i] = max(dp[i],dp[j]+1);
            }
        }
        ret = max(ret,dp[i]);
    }
    return ret;
}
//案例4，返回两个字符串的最长公共子序列
//递归版
string maxlengthcommonsubarr(string str1,string str2)
{
    return processmaxlensubstring(str1,str2,0,0);
}
string processmaxlensubstring(string str1,string str2,int i,int j)
{
    if(i == str1.size() || j == str2.size())
        return "";
    if(str1[i] == str2[j]){
        return str1[i] + processmaxlensubstring(str1,str2,i+1,j+1);
    }
    else{
        string ret1 = processmaxlensubstring(str1,str2,i+1,j);
        string ret2 = processmaxlensubstring(str1,str2,i,j+1);
        return ret1.size()>ret2.size()?ret1:ret2;
    }
}
//动态规划版
string dpmaxlensubstring(string& str1,string& str2)
{
    if(str1.empty() || str2.empty())
        return "";
    string** dp = new string*[str1.size()];
    for(int i = 0;i<str1.size();i++){
        dp[i] = new string[str2.size()];
    }
    if(str1[0] == str2[0])
        dp[0][0] = str1[0];
    for(int i = 1;i<str1.size();i++){
        if(str1[i] == str2[0])
            dp[i][0] = str2[0];
        else{
            dp[i][0] = "";
        }
    }
    for(int j = 1;j<str2.size();j++){
        if(str1[0] == str2[j]){
            dp[0][j] = str1[0];
        }else{
            dp[0][j] = "";
        }
    }
    for(int i = 1;i<str1.size();i++){
        for(int j = 1;j<str2.size();j++){
            if(str1[i] == str2[j])
                dp[i][j] += str1[i] + dp[i-1][j-1];
            else{
                dp[i][j] += dp[i-1][j].size()>dp[i][j-1].size()?dp[i-1][j]:dp[i][j-1];
            }
        }
    }
    string ret = dp[str1.size()-1][str2.size()-1];
    ret.reserve();
    for(int i = 0;i<str1.size();i++){
        delete[] dp[i];
    }
    delete[] dp;
    return ret;
}
//案例5，一个背包有一定的承重W，有N件物品，每件都有自己的价值，记录在数组v中，也都有自己的重量，记录在数组w中，每件物品只能选择要装入背包还是不装入背包，要求在不超过背包承重的前提下，选出物品总价最大
//递归版
int backpacksolution(vector<int>& w,vector<int>& v,int W)
{
    if(W == 0)
        return 0;
    return processbackpacksolution(w, v, W, 0);
}
int processbackpacksolution(vector<int>& w,vector<int>& v,int W,int i)
{
    if(i == w.size() || W <= 0)
        return 0;
    int yao = 0,buyao = 0;
    if(W-w[i] >= 0){
        yao = v[i]+processbackpacksolution(w,v,W-w[i],i+1);
    }
    buyao = processbackpacksolution(w, v, W, i+1);
    return max(yao,buyao);
}
//动态规划版
int dpbackpacksolution(vector<int>& w,vector<int>& v,int W)
{
    if(W == 0)
        return 0;
    int** dp = new int*[w.size()];
    for(int i = 0;i<w.size();i++){
        dp[i] = new int[W+1];
    }
    for(int i = 0;i<w.size();i++){
        dp[i][0] = 0;
    }
    for(int j=1;j<W+1;j++){
        if(w[0]<=j)
            dp[0][j] = v[0];
        else
            dp[0][j] = 0;
    }
    for(int i =1;i<w.size();i++){
        for(int j = 1;j<W+1;j++){
            dp[i][j] = j-w[i]>=0?max(dp[i-1][j-w[i]]+v[i],dp[i-1][j]):dp[i-1][j];
        }
    }
    int ret = dp[w.size()-1][W];
    for(int i = 0;i<w.size();i++){
        delete[] dp[i];
    }
    delete[] dp;
    return ret;
}
//案例6，给定两个字符串str1和str2，在给定3个整数ic、dc、rc，分别代表插入、删除、替换一个字符的代价。返回将str1编辑成str2的最小代价
//递归版
int mincostofmakesamestring(string str1,string str2,int ic,int dc,int rc)
{
    if(str1 == str2)
        return 0;
    return processmincostchangestring(str1,str2,ic,dc,rc,0,0);
}
int processmincostchangestring(string str1,string str2,int ic,int dc,int rc,int i,int j)
{
    if(i == str1.size() && j == str2.size())
        return 0;
    if(i == str1.size() && j <str2.size()){
        return ic*((int)str2.size()-j);
    }
    if(i < str1.size() && j == str2.size()){
        return dc*((int)str1.size()-i);
    }
    if(str1[i] == str2[j]){
        return processmincostchangestring(str1,str2,ic,dc,rc,i+1,j+1);
    }
    else{
        int case1 = dc+processmincostchangestring(str1,str2,ic,dc,rc,i+1,j);//删除
        int case2 = ic+processmincostchangestring(str1,str2,ic,dc,rc,i,j+1);//插入
        int case3 = rc+processmincostchangestring(str1,str2,ic,dc,rc,i+1,j+1);//替换
        return min(min(case1,case2),case3);
    }
}
//动态规划版
int dpmincostchangestring(string word1,string word2,int ic,int dc,int rc)
{
    if(word1 == word2)
        return 0;
    int** dp = new int*[word2.size()+1];
    for(int i = 0;i<=word2.size();i++){
        dp[i] = new int[word1.size()+1];
    }
    dp[0][0] = 0;
    for(int i = 1;i<=word2.size();i++){
        dp[i][0] = i*ic;
    }
    for(int j = 1;j<=word1.size();j++){
        dp[0][j] = j*dc;
    }
    for(int i = 1;i<=word2.size();i++){
        for(int j = 1;j<=word1.size();j++){
            if(word2[i-1] == word1[j-1]){
                dp[i][j] = dp[i-1][j-1];
            }else{
                dp[i][j] = min(min(ic+dp[i-1][j],dc+dp[i][j-1]),rc+dp[i-1][j-1]);
            }
        }
    }
    int ret = dp[word2.size()][word1.size()];
    for(int i = 0;i<word2.size()+1;i++){
        delete[] dp[i];
    }
    delete[] dp;
    return ret;
}
//案例7，给定一个数组和一个整数，求数组中任意组合的和等于给定的整数
bool isequalsum(vector<int> nums,int aim,int sum,int i)
{
    if(i == nums.size())
        return aim == sum ? true : false;
    return isequalsum(nums, aim, sum, i+1) || isequalsum(nums, aim, sum+nums[i], i+1);
}
//案例8，排成一条线的纸牌博弈问题
//递归版
int win1(vector<int> arr)
{
    if(arr.empty()){
        return 0;
    }
    return max(f(arr,0,arr.size()-1),s(arr,0,arr.size()-1));
}
int f(vector<int> arr,int i,int j)
{
    if(i == j){
        return arr[i];
    }
    return max(arr[i]+s(arr,i+1,j),arr[j]+s(arr,i,j-1));
}
int s(vector<int> arr,int i,int j)
{
    if(i == j){
        return 0;
    }
    return min(f(arr,i+1,j),f(arr,i,j-1));
}
//动态规划版
int win2(vector<int> arr)
{
    int **f = new int*[arr.size()];
    for(int i = 0;i<arr.size();i++){
        f[i] = new int[arr.size()];
    }
    int **s = new int*[arr.size()];
    for(int i = 0;i<arr.size();i++){
        s[i] = new int[arr.size()];
    }
    //不依赖项赋值
    for(int i = 0;i<arr.size();i++){
        f[i][i] = arr[i];
        s[i][i] = 0;
    }
    for(int j = 0;j<arr.size();j++){
        for(int i = j-1;i>=0;i--){
            f[i][j] = max(arr[i]+s[i+1][j],arr[j]+s[i][j-1]);
            s[i][j] = min(f[i+1][j],f[i][j-1]);
        }
    }
    int ret = max(f[0][arr.size()-1],s[0][arr.size()-1]);
    for(int i = 0;i<arr.size();i++){
        delete[] f[i];
    }
    delete[] f;
    for(int i = 0;i<arr.size();i++){
        delete[] s[i];
    }
    delete[] s;
    return ret;
}
//案例9，换钱的最小货币数
//递归版
int minchangemoney(vector<int> arr,int aim)
{
    return processminmoney1(arr,aim,0);
}
int processminmoney1(vector<int> arr,int aim,int index)
{
    if(aim == 0)
        return 0;
    if(index == arr.size()){
        return aim == 0?0:-1;
    }
    int minnum = INT_MAX;
    int ret = 0;
    for(int i = 1;i*arr[index]<=aim;i++){
        ret = processminmoney1(arr,aim-i*arr[index],index+1);
        if(ret >= 0){
            minnum = min(minnum,i+ret);
        }
    }
    return minnum == INT_MAX ? -1 : minnum;
}

//案例10，最少费用的爬台阶方法
//递归版
int minCostClimbingStairs(vector<int> &cost)
{
    return min(processcoststairs(cost,0),processcoststairs(cost,1));
}
int processcoststairs(vector<int> &cost,int index)
{
    if(index >= cost.size()){
        return index == cost.size() ? 0 : INT_MAX;
    }
    else
        return cost[index]+min(processcoststairs(cost,index+1),processcoststairs(cost,index+2));
}
//改动态规划
int minCostClimbingStairsdp(vector<int> &cost)
{
    if(cost.empty()){
        return 0;
    }
    if(cost.size() == 1){
        return cost[0];
    }
    int *dp = new int[cost.size()+1];
    dp[0] = cost[0];
    dp[1] = cost[1];
    for(int i = 2;i<cost.size();i++){
        dp[i] = cost[i]+min(dp[i-1],dp[i-2]);
    }
    dp[cost.size()] = min(dp[cost.size()-1],dp[cost.size()-2]);
    int ret = dp[cost.size()];
    delete[] dp;
    return ret;
}
//案例11，给定一个数组，全是正数，和一个整数aim,求累加和等于aim的最长子数组,时间复杂度为O(N)，额外空间复杂度为O(1),思路为用双指针组成一个窗口不断移动窗口求其和
int getmaxlengtharr(vector<int>& arr,int aim)
{
    if(arr.empty())
        return 0;
    int l = 0;
    int r = 0;
    int sum = arr[0];
    int maxlen = 1;
    while(r<arr.size()){
        if(sum < aim){
            r++;
            sum += arr[r];
        }
        else if(sum == aim){
            maxlen = max(maxlen,r-l+1);
            r++;
            sum += arr[r];
        }
        else {
            sum -= arr[l];
            l++;
        }
    }
    return maxlen;
}
//案例12，给定一个数组，值可正可负可0，z一个整数aim,求累加和小于等于aim的最长子数组，要求时间复杂度为O(N)
int getmaxlensubvariablearr(vector<int>& nums,int aim)
{
    if(nums.empty())
        return 0;
    vector<int> min_sum;
    vector<int> min_sum_index;
    min_sum.resize((int)nums.size());
    min_sum_index.resize((int)nums.size());
    int len = (int)nums.size()-1;
    min_sum[len] = nums[len];
    min_sum_index[len] = len;
    for(int i = len-1;i>=0;i--){
        if(min_sum[i+1]<=0)
        {
            min_sum[i] = nums[i]+min_sum[i+1];
            min_sum_index[i] = min_sum_index[i+1];
        }
        else{
            min_sum[i] = nums[i];
            min_sum_index[i] = i;
        }
    }
    int end = 0;
    int sum = 0;
    int res = 0;
    for(int i = 0;i<=len;i++){
        while(end <= len && sum+min_sum[end]<aim){
            sum += min_sum[end];
            end = min_sum_index[end]+1;
        }
        sum -= end>i ? nums[i] : 0;
        res = max(res,end-i);
        end = max(end,i+1);
    }
    return res;
}
//案例13，环形单链表的约瑟夫问题
circlenode* josephusKill2(circlenode* head,int m)
{
    if(head == NULL || head->next == head || m < 1){
        return head;
    }
    circlenode* cur = head->next;
    int tmp = 1;
    while(cur != head){
        tmp++;
        cur = cur->next;
    }
    tmp = getlive(tmp,m);
    while(--tmp != 0){
        head = head->next;
    }
    head->next = head;
    return head;
}
int getlive(int i,int m)
{
    if(i == 1){
        return 1;
    }
    return (getlive(i-1,m)+m-1)%i+1;
}
//案例14，字符串匹配问题，（正则表达式的简版），给定字符串str,其中绝对不包含字符'.'和'*'，在给定字符串exp，其中可以含有'.'和'*','*'字符不能是exp的首字符，并且任意两个'*'字符不能相邻，exp中的'.'代表任何一个字符，expk中的'*'表示'*'的前一个字符可以有0个或者多个，请写出一个函数，判断str是否e能被exp匹配
//递归版
bool process(string str,string exp,int i,int j)
{
    //
    if(j == exp.size()){
        return i == str.size();
    }
    //j上面还有字符，考察j+1情况
    if(j+1 == exp.size() || exp[j+1] != '*'){
        return i != str.size() && (exp[j] == str[i] || exp[j] == '.')&&process(str,exp,i+1,j+1);
    }
    //exp的j+1位置不仅有字符而且是'*'
    while(i != str.size() && (exp[j] == str[i] || exp[j] == '.')){
        if(process(str,exp,i,j+2)){
            return true;
        }
        i++;
    }
    //默认0个
    return process(str,exp,i,j+2);
}
//动态规划版
bool dpstringzhengze(string str,string exp)
{
    if(str.empty() || exp.empty())
        return false;
    if(!isvalid(str, exp))
        return false;
    bool** dp = initdpmap(str, exp);
    for(int i = (int)str.size()-1;i>-1;i--){
        for(int j = (int)exp.size()-2;j>-1;j--){
            if(exp[j+1] != '*'){
                dp[i][j] = (str[i] == exp[j] || exp[j] == '.')&& dp[i+1][j+1];
            }
            else{
                int si = i;
                while(si != str.size() && (str[si] == exp[j] || exp[j] == '.')){
                    if(dp[si][j+2]){
                        dp[i][j] = true;
                        break;
                    }
                    si++;
                }
                if(dp[i][j] != true){
                    dp[i][j] = dp[si][j+2];
                }
            }
        }
    }
    bool ret = dp[0][0];
    for(int i = 0;i<str.size()+1;i++){
        delete[] dp[i];
    }
    delete[] dp;
    return ret;
}
bool isvalid(string str,string exp)
{
    for(int i = 0;i<str.size();i++){
        if(str[i] == '.' || str[i] == '*'){
            return false;
        }
    }
    for(int i = 0;i<exp.size();i++){
        if(exp[i] == '*' && (i == 0 || exp[i-1] == '*')){
            return false;
        }
    }
    return true;
}
bool** initdpmap(string str,string exp)
{
    bool** dp = new bool*[str.size()+1];
    for(int i = 0;i<str.size()+1;i++){
        dp[i] = new bool[exp.size()+1];
    }
    dp[str.size()][exp.size()] = true;
    for(int j = (int)exp.size()-2;j>-1;j=j-2){
        if(exp[j] != '*' && exp[j+1] == '*'){
            dp[str.size()][j] = true;
        }else{
            break;
        }
    }
    if(str.size()>0 && exp.size() >0){
        if((exp[exp.size()-1] == '.' || str[str.size()-1] == exp[exp.size()-1])){
            dp[str.size()-1][exp.size()-1] = true;
        }
    }
    return dp;
}
//案例15.最长回文子串
//动态规划
string getmaxlenlongeststringword(string s)
{
    if(s.empty() || s.size() == 1){
        return s;
    }
    string res;
    int strlen = (int)s.size();
    bool islongestword[strlen][strlen];
    for(int i = 0;i<strlen;i++){
        for(int j = 0;j<strlen;j++){
            islongestword[i][j] = false;
        }
    }
    int curlen = 0;
    int maxlen = 0;
    int maxstart = 0;
    int maxend = 0;
    for(int i = strlen-1;i>=0;i--){
        for(int j = i;j<strlen;j++){
            if(s[i] == s[j] && (j - i <= 1 || islongestword[i+1][j-1])){
                islongestword[i][j] = true;
                curlen = j-i+1;
                if(maxlen < curlen){
                    maxlen = curlen;
                    maxstart = i;
                    maxend = j;
                }
            }
        }
    }
    while(maxstart<=maxend){
        res += s[maxstart];
        maxstart++;
    }
    return res;
}
//案例16.通配符匹配
//递归
bool ismatchstringword(string& s,string& p,int i,int j)
{
    if(j == p.size()){
        return i == s.size();
    }
    if(p[j] != '*'){
        return i != s.size() && (s[i] == p[j] || p[j] == '?') && ismatchstringword(s, p, i+1, j+1);
    }
    while(i<s.size() && p[j] == '*'){
        if(ismatchstringword(s, p, i, j+1)){
            return true;
        }
        i++;
    }
    return ismatchstringword(s, p, i, j+1);
}

bool isMatch(string s, string p) {
    if(s.empty() && p.empty()){
        return true;
    }
    else if(!s.empty() && p.empty()){
        return false;
    }
    else{
        return ismatchstringword(s,p,0,0);
    }
}
//动态规划
bool ismatchdpstringword(string s,string p)
{
    int strlen = (int)s.size();
    int ptrlen = (int)p.size();
    bool dp[strlen+1][ptrlen+1];
    for(int i = 0;i<=strlen;i++){
        for(int j = 0;j<=ptrlen;j++){
            dp[i][j] = false;
        }
    }
    dp[strlen][ptrlen] = true;
    for(int i = strlen-1;i>=0;i--){
        dp[i][ptrlen] = false;
    }
    for(int j = ptrlen-1;j>=0;j--){
        if(p[j] == '*' && dp[strlen][j+1])
            dp[strlen][j] = true;
    }
    for(int i = strlen-1;i>=0;i--){
        for(int j = ptrlen-1;j>=0;j--){
            if(p[j] != '*'){
                dp[i][j] = (s[i] == p[j] || p[j] == '?') && dp[i+1][j+1];
            }
            else{
                int k = i;
                while(k<=strlen && (s[k] == p[j] || p[j] == '*')){
                    if(dp[k][j+1]){
                        dp[i][j] = true;
                        break;
                    }
                    k++;
                }
                if(dp[i][j] != true){
                    dp[i][j] = dp[i][j+1];
                }
            }
        }
    }
    return dp[0][0];
}
//案例17.最大子序和
int maxSubArray(vector<int>& nums)
{
    int numslen = (int)nums.size();
    int dp[numslen];
    dp[0] = nums[0];
    int maxsum = dp[0];
    for(int i = 1;i<numslen;i++){
        if(nums[i]+dp[i-1]>nums[i]){
            dp[i] = dp[i-1]+nums[i];
        }else{
            dp[i] = nums[i];
        }
        maxsum = max(maxsum,dp[i]);
    }
    return maxsum;
}
//案例18.不同路径
int uniquePaths(int m, int n)
{
    if(m == 0 && n == 0){
        return 0;
    }
    return processuniquepaths(m-1,n-1,0,0);
}
int processuniquepaths(int m,int n,int i,int j)
{
    if(i == m && j == n)
        return 1;
    if(i == m)
        return processuniquepaths(m,n,i,j+1);
    if(j == n)
        return processuniquepaths(m,n,i+1,j);
    return processuniquepaths(m,n,i+1,j)+processuniquepaths(m,n,i,j+1);
}
//动态规划版
int dpuniquepaths(int m,int n)
{
    if(m == 0 && n == 0){
        return 0;
    }
    int dp[m][n];
    dp[m-1][n-1] = 1;
    for(int i = 0;i<m-1;i++){
        dp[i][n-1] = 1;
    }
    for(int j = 0;j<n-1;j++){
        dp[m-1][j] = 1;
    }
    for(int i = m-2;i>-1;i--){
        for(int j = n-2;j>-1;j--){
            dp[i][j] = dp[i+1][j]+dp[i][j+1];
        }
    }
    return dp[0][0];
}
//案例19.不同路径2（加障碍物）
//递归版
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
{
    if(obstacleGrid.empty())
        return 0;
    int m = (int)obstacleGrid.size();
    int n = (int)obstacleGrid[0].size();
    if(obstacleGrid[m-1][n-1] == 1){
        return 0;
    }
    return processuniquepathswithobstacles(obstacleGrid,m-1,n-1,0,0);
}
int processuniquepathswithobstacles(vector<vector<int>>& obstacle,int m,int n,int i,int j)
{
    if(i == m && j == n)
        return 1;
    if(obstacle[i][j] == 1){
        return 0;
    }
    if(i == m){
        return processuniquepathswithobstacles(obstacle,m,n,i,j+1);
    }
    if(j == n){
        return processuniquepathswithobstacles(obstacle,m,n,i+1,j);
    }
    return processuniquepathswithobstacles(obstacle,m,n,i,j+1)+processuniquepathswithobstacles(obstacle,m,n,i+1,j);
}
//动态规划版
int dpuniquepathswithobstacles(vector<vector<int>>& obstacleGrid)
{
    int m = (int)obstacleGrid.size();
    int n = (int)obstacleGrid[0].size();
    if(m == 0 && n == 0){
        return 0;
    }
    if(obstacleGrid[m-1][n-1] == 1){
        return 0;
    }
    long dp[m][n];
    dp[m-1][n-1] = 1;
    for(int i = m-2;i>-1;i--){
        if(obstacleGrid[i][n-1] == 1 || dp[i+1][n-1] == 0){
            dp[i][n-1] = 0;
        }
        else
            dp[i][n-1] = 1;
    }
    for(int j = n-2;j>-1;j--){
        if(obstacleGrid[m-1][j] == 1 || dp[m-1][j+1] == 0)
            dp[m-1][j] = 0;
        else
            dp[m-1][j] = 1;
    }
    for(int i = m-2;i>-1;i--){
        for(int j = n-2;j>-1;j--){
            if(obstacleGrid[i][j] == 1)
                dp[i][j] = 0;
            else
                dp[i][j] = dp[i+1][j]+dp[i][j+1];
        }
    }
    return (int)dp[0][0];
}
