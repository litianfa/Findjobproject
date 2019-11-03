//
//  dpexercise.cpp
//  c++
//
//  Created by litianfa on 2019/6/28.
//  Copyright © 2019 litianfa. All rights reserved.
//

#include "dpexercise.hpp"

//畅通工程
void projectsmooth()
{
    vector<data> din;
    int N,M;
    cout<<"please input data:"<<endl;
    cin>>N>>M;
    int i,j;
    bool hugeinput = false;
    while(cin>>i && i){
        cin>>j;
        if(i<=N&&j<= N){
            din.push_back(data(i,j));
        }else{
            hugeinput = true;
        }
    }
    unionsets u1(N);
    vector<data>::iterator it = din.begin();
    while(it != din.end()){
        u1.unions(it->val1, it->val2);
        it++;
    }
    cout<<u1.numberfather()-1<<endl;
    if(hugeinput){
        cout<<"Hint Huge input, scanf is recommended"<<endl;
    }
}


//二叉搜索树的给定节点之间的和
int processsumBst(TreeNode* root, int aim)
{
    if(root == NULL){
        return 0;
    }
    else if(root->val == aim){
        return aim;
    }
    else if(root->val>aim){
        return root->val+processsumBst(root->left,aim);
    }else{
        return root->val+processsumBst(root->right,aim);
    }
    
}
int rangeSumBST(TreeNode* root, int L, int R)
{
    if(root == NULL){
        return 0;
    }
    
    return processsumBst(root->left,L)+processsumBst(root->right,R);
}

//二叉树的节点之间的任意最小值
void processINBST(TreeNode* root,vector<int>& arr)
{
    if(root == NULL){
        return;
    }
    arr.push_back(root->val);
    processINBST(root->left,arr);
    processINBST(root->right,arr);
}
int minDiffInBST(TreeNode* root)
{
    
    return 0;
}

//最长同值路径
int longestUnivaluePath(TreeNode* root)
{
    return 0;
}
int process(TreeNode* root,int value,int len)
{
    if(root == NULL)
        return 0;
    if(root->val != value){
        if(root->left != NULL){
            return max(len,process(root->left,root->left->val,0));
        }
        if(root->right != NULL){
            return max(len,process(root->right,root->right->val,0));
        }
        return len;
    }else{
        return max(process(root->left,value,len+1),process(root->right,value,len+1));
    }
}
//9.龙与地下城游戏问题
//递归实现
int generateMininumHPdigui(vector<vector<int> >& dungen)
{
    return processHP(dungen, 0, 0);
}
int processHP(vector<vector<int> >& dungen,int i,int j)
{
    if(i == dungen.size()-1 && j == dungen[0].size()-1){
        return dungen[i][j]>0 ? 1 : (-dungen[i][j]+1);
    }
    else if(i == dungen.size()-1)
        return max(processHP(dungen,i,j+1)-dungen[i][j],1);
    else if(j == dungen[0].size()-1)
        return max(processHP(dungen,i+1,j)-dungen[i][j],1);
    else
        return min(max(processHP(dungen,i,j+1)-dungen[i][j],1),max(processHP(dungen,i+1,j)-dungen[i][j],1));
}
//动态规划实现
int calculateMinimumHP(vector<vector<int>>& dungeon) {
    int **dp = new int*[dungeon.size()];
    int ret = 0;
    for(int i = 0;i<dungeon.size();i++){
        dp[i] = new int[dungeon[0].size()];
    }
    int row = (int)dungeon.size();
    int len = (int)dungeon[0].size();
    dp[row-1][len-1] = dungeon[row-1][len-1]>0?1:-dungeon[row-1][len-1]+1;
    for(int i = row-2;i>=0;i--){
        dp[i][len-1] = max(dp[i+1][len-1]-dungeon[i][len-1],1);
    }
    for(int j = len-2;j>=0;j--){
        dp[row-1][j] = max(dp[row-1][j+1]-dungeon[row-1][j],1);
    }
    for(int i = row-2;i>=0;i--){
        for(int j = len-2;j>=0;j--){
            dp[i][j] = min(max(dp[i+1][j]-dungeon[i][j],1),max(dp[i][j+1]-dungeon[i][j],1));
        }
    }
    ret = dp[0][0];
    for(int i = 0;i<dungeon.size();i++){
        delete[] dp[i];
    }
    delete[] dp;
    return ret;
}

//8.数组中的最长连续序列
int maxlenarr(vector<int> &nums)
{
    if(nums.size() == 0){
        return 0;
    }
    int Max = 1;
    unordered_map<int, int> arrmap;
    for(int i = 0;i<nums.size();i++){
        unordered_map<int, int>::iterator it = arrmap.find(nums[i]);
        if(it == arrmap.end()){
            arrmap.insert(make_pair(nums[i],1));
            unordered_map<int, int>::iterator it1 = arrmap.find(nums[i]-1);
            if(it1 != arrmap.end()){
                Max = max(Max,merge(arrmap,nums[i]-1,nums[i]));
            }
            unordered_map<int, int>::iterator it2 = arrmap.find(nums[i]+1);
            if(it2 != arrmap.end()){
                Max = max(Max,merge(arrmap,nums[i],nums[i]+1));
            }
        }
    }
    return Max;
}
int merge(unordered_map<int, int> & arrmap,int less,int more)
{
    int lesslen = arrmap[less];
    int morelen = arrmap[more];
    int len = arrmap[less] + arrmap[more];
    int i = 0,j =0;
    while(i!=lesslen){
        arrmap[less-i] = len;
        i++;
    }
    while(j!= morelen){
        arrmap[more+j] = len;
        j++;
    }
    return len;
}

//7.跳跃游戏
//7.改动态规划
int jumpdp(vector<int> &nums)
{
    if(nums.size()<=1){
        return 0;
    }
    int jump = 0;
    int cur = 0;
    int next = 0;
    for(int i = 0;i<nums.size();i++)
    {
        if(cur<i){
            jump++;
            cur=next;
        }
        next = max(next,i+nums[i]);
    }
    return jump;
}

int jump(vector<int>& nums)
{
    return processjump(nums,0);
}

int processjump(vector<int>& nums,int i)
{
    if(i >= nums.size() -1 || i+nums[i] >= nums.size() -1)//到达最后位置
    {
        return 1;
    }
    int k = nums[i];
    int maxjump = INT_MIN,index = 0;
    for(int j = i+1;j<=i+k;j++){
        if(maxjump<=nums[j]+j){
            maxjump = nums[j]+j;
            index = j;
        }
    }
    return 1+processjump(nums,index);
}
