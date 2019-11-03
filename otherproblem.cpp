//
//  otherproblem.cpp
//  c++
//
//  Created by litianfa on 2019/7/11.
//  Copyright © 2019 litianfa. All rights reserved.
//

#include "otherproblem.hpp"

//案例1，占用会议室问题,最多能够安排多少场项目会议
int bestArrange(vector<project>& nums)
{
    if(nums.empty())
        return 0;
    sort(nums.begin(),nums.end(),projectcompare());
    int result = 1;
    int current = nums[0].end;
    for(int i = 1;i<nums.size();i++){
        if(current <= nums[i].start)
        {
            result++;
            current = nums[i].end;
        }
    }
    return result;
}
//案例2，汉诺塔问题
void hanuota(int n)
{
    if(n>0){
        hanuoprocess(n, "source", "middle", "destination");
    }
}
void hanuoprocess(int n,string from,string mid,string to)
{
    if(n==1)
    {
        cout<<"move 1 from "<<from<<" to "<<to<<endl;
        return;
    }
    hanuoprocess(n-1,from,to,mid);
    cout<<"move "<<n<<" from "<<from<<" to "<<to<<endl;
    hanuoprocess(n-1,mid,from,to);
}
//案例3，IPO
int findMaximizedCapital(int k,int W,vector<int> Profits,vector<int> Capital)
{
    vector<Node> nodes(Profits.size());
    for(int i = 0;i<Profits.size();i++){
        nodes[i] = Node(Profits[i],Capital[i]);
    }
    priority_queue<Node,vector<Node>,MinCostComparator> minCostQ;
    priority_queue<Node,vector<Node>,MaxProfitComparator> maxProfitQ;
    for(int i=0;i<nodes.size();i++){
        minCostQ.push(nodes[i]);
    }
    for(int i=0;i<k;i++){
        while(!minCostQ.empty()&& minCostQ.top().c<=W){
            maxProfitQ.push(minCostQ.top());
            minCostQ.pop();
        }
        if(maxProfitQ.empty()){
            return W;
        }
        W += maxProfitQ.top().p;
    }
    return W;
}
//案例4，母牛问题
int muniu(int n){
    if(n == 1 || n == 2 || n == 3 || n == 4){
        return n;
    }
    return muniu(n-1)+muniu(n-3);
}
//案例5，岛问题
int daoproblem(vector<vector<int> > matrix)
{
    int value = 0;
    for(int i = 0;i<matrix.size();i++)
    {
        for(int j = 0;j<matrix[0].size();j++)
        {
            if(matrix[i][j] == 1)
            {
                ++value;
                infect(matrix,i,j);
            }
        }
    }
    return value;
}
void infect(vector<vector<int> >& matrix,int i,int j)
{
    if(i==matrix.size() || i<0 || j<0 || j==matrix[0].size() || matrix[i][j] != 1)
        return;
    else
    {
        matrix[i][j] = 2;
        infect(matrix,i+1,j);
        infect(matrix,i-1,j);
        infect(matrix,i,j+1);
        infect(matrix,i,j-1);
        
    }
}
//案例6，轮廓问题
vector<vector<int> > buildingoutline(vector<vector<int> > buildings)
{
    vector<buildingnode> nodes;//果然是没有默认构造函数惹的祸
    map<int,int> htmap;
    map<int,int> pmmap;
    map<int,int>::iterator it;
    //拆分给定的数组
    for(int i = 0; i <buildings.size() ; i++){
        nodes.push_back(buildingnode(true,buildings[i][0],buildings[i][2]));
        nodes.push_back(buildingnode(false,buildings[i][1],buildings[i][2]));
    }
    sort(nodes.begin(),nodes.end(),nodecompare());
    for(int i = 0;i<nodes.size();i++){
        if(nodes[i].isUp){
            it = htmap.find(nodes[i].height);
            if(it == htmap.end()){
                htmap.insert(make_pair(nodes[i].height,1));
            }
            else{
                htmap[nodes[i].height] = htmap[nodes[i].height]+1;
            }
        }
        else{
            it = htmap.find(nodes[i].height);
            if(it != htmap.end()){
                if(htmap[nodes[i].height] == 1){
                    htmap.erase(nodes[i].height);
                }
                else{
                    htmap[nodes[i].height] = htmap[nodes[i].height]-1;
                }
            }
        }
        if(htmap.empty()){
            if(pmmap.find(nodes[i].pos) != pmmap.end())
                pmmap[nodes[i].pos] = 0;
            else
                pmmap.insert(make_pair(nodes[i].pos,0));
        }
        else{
            auto its = htmap.rbegin();
            if(pmmap.find(nodes[i].pos) != pmmap.end())
                pmmap[nodes[i].pos] = its->first;
            else
                pmmap.insert(make_pair(nodes[i].pos,its->first));
        }
    }
    
    vector<vector<int> > ret;
    int start = 0;
    int height = 0;
    it = pmmap.begin();
    while(it!=pmmap.end()){
        int curposition = it->first;
        int curheight = it->second;
        if(height != curheight){
            if(height!=0){
                vector<int> addret;
                addret.push_back(start);
                addret.push_back(curposition);
                addret.push_back(height);
                ret.push_back(addret);
            }
            start = curposition;
            height = curheight;
        }
        ++it;
    }
    
    return ret;
}

//案例7，累加和为给定值的最长子数组
int maxlenghtofsum(vector<int> arr,int aim)
{
    if(arr.empty() || (arr.size()==1 && arr[0] != aim))
        return 0;
    
    map<int,int> summap;
    map<int,int>::iterator it;
    summap.insert(make_pair(0,-1));
    int len = 0;
    int sum = 0;
    for(int i = 0; i<arr.size();i++){
        sum = sum + arr[i];
        it = summap.find(sum-aim);
        if(it != summap.end()){
            len = max(len,i-(it->second));
        }
        if(summap.find(sum) == summap.end())
        {
            summap.insert(make_pair(sum,i));
        }
    }
    return len;
}

//案例8，异或和为0的子数组最多的个数
int maxnumberxorarr(vector<int> arr)
{
    int ans = 0;
    map<int,int> xormap;
    map<int,int>::iterator it;
    vector<int> dp;
    xormap.insert(make_pair(0,-1));
    int Xor = 0;
    for(int i = 0;i<arr.size();i++){
        Xor ^= arr[i];
        it = xormap.find(Xor);
        if(it!=xormap.end()){
            dp[i]=it->second == -1 ? 1 : dp[it->second]+1;
        }
        if(i>0){
            dp[i] = max(dp[i-1],dp[i]);
        }
        xormap.emplace(Xor,i);
        ans = max(ans,dp[i]);
    }
    return ans;
}
//案例9，数组中重复的数字
vector<int> getpardonvariable(vector<int>& nums)
{
    //个人想法是利用hashmap来看那些数组成员是重复的
    vector<int> ret;
    if(nums.empty())
        return ret;
    unordered_set<int> myset;
    unordered_set<int>::iterator it;
    for(int i = 0;i<nums.size();i++){
        it = myset.find(nums[i]);
        if(it == myset.end()){
            myset.insert(nums[i]);
        }else{
            ret.push_back(nums[i]);
        }
    }
    return ret;
}
//用桶排序试一试
vector<int> tonggetpardonvar(vector<int>& nums)
{
    vector<int> ret;
    if(nums.empty()){
        return ret;
    }
    int maxval = INT_MIN;
    for(int i = 0;i<nums.size();i++){
        maxval = max(maxval,nums[i]);
    }
    vector<int> buket(0,maxval+1);
    buket.resize(maxval+1);
    for(int i = 0;i<nums.size();i++){
        buket[nums[i]]++;
    }
    for(int i = 0;i<=maxval;i++){
        if(buket[i] > 1){
            ret.push_back(i);
        }
    }
    return ret;
}
//案例10，二维数组中的查找,二维数组中从左到右依次递增，从上到下依次递增，思路从右上角开始查找，时间复杂度小于O(N)
bool getvalueofmatrix(vector<vector<int> >& matrix,int val)
{
    if(matrix.empty())
        return false;
    int i = 0;
    int j = (int)matrix[0].size()-1;
    while(i < matrix.size() && j >= 0){
        if(matrix[i][j] > val){
            j--;
        }else if(matrix[i][j] == val){
            return true;
        }else{
            i++;
        }
    }
    return false;
}
//案例11，替换字符串的空格
string changespacestring(string& str)
{
    string ret;
    if(str.empty())
        return ret;
    int countspace = 0;
    for(int i = 0;i<=str.size();i++){
        if(str[i] == ' '){
            countspace++;
        }
    }
    ret.resize(str.size() + countspace*2);
    int i = (int)str.size();
    int j = (int)ret.size();
    while(i>=0){
        if(str[i] != ' '){
            ret[j--] = str[i--];
        }
        else{
            ret[j--] = '0';
            ret[j--] = '2';
            ret[j--] = '%';
            i--;
        }
    }
    return ret;
}
//相关题目，有两个排序的数组A1和A2，内存在A1的末尾有足够多的空余空间容纳A2.请实现一个函数，把A2中的所有数字插入A1中，并且所有的数字都是排序的。思路类似，还是从后向前复制先比较两数组最后一个成员的大小，将大的放进去，依次向前复制
void copysortarr(vector<int>& a1,vector<int>& a2)
{
    int lena1 = (int)a1.size();
    int lena2 = (int)a2.size();
    int len = lena1+lena2;
    a1.resize(len);
    int i = len-1;
    int j = lena1-1;
    int k = lena2-1;
    while(j >=0 && k >= 0){
        if(a1[j] >= a2[k]){
            a1[i--] = a1[j--];
        }else {
            a1[i--] = a2[k--];
        }
    }
    while(k>=0){
        a1[i--] = a2[k--];
    }
    for(auto c:a1){
        cout<<c<<" ";
    }
    cout<<endl;
}
//案例12，从尾到头打印链表，输入一个链表的头节点，从尾到头反过来打印出每个节点的值
void printfromendtostart(ListNode* head)
{
    if(head == NULL)
        return;
    ListNode* ptr = head;
    stack<int> mystack;
    while(ptr != NULL){
        mystack.push(ptr->val);
        ptr = ptr->next;
    }
    while(!mystack.empty()){
        cout<<mystack.top()<<" ";
        mystack.pop();
    }
    return;
}
//案例13，重建二叉树，输入二叉树的前序和后序遍历的结果，请重建二叉树
TreeNode* rebuildTree(vector<int>& pre,vector<int>& In)
{
    if(pre.empty() || In.empty())
        return NULL;
    //用栈试一下
    stack<TreeNode*> mystack;
    TreeNode* head = new TreeNode(pre[0]);
    TreeNode* ptr = head;
    int i = 1;
    int j = 0;
    while(i<pre.size() && j<In.size()){
        if(ptr->val == In[j++])
        {
            ptr = mystack.top();
            mystack.pop();
            ptr->right = new TreeNode(pre[i++]);
            ptr = ptr->right;
            j++;
        }else {
            mystack.push(ptr);
            ptr->left = new TreeNode(pre[i++]);
            ptr = ptr->left;
        }
    }
    return head;
}
