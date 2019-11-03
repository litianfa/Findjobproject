//
//  dpexercise.hpp
//  c++
//
//  Created by litianfa on 2019/6/28.
//  Copyright © 2019 litianfa. All rights reserved.
//

#ifndef dpexercise_hpp
#define dpexercise_hpp

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
//最长同值路径
int longestUnivaluePath(TreeNode* root);
int process(TreeNode* root,int value,int len);

//二叉树的节点之间的任意最小值
int minDiffInBST(TreeNode* root);
void processINBST(TreeNode* root,vector<int>& arr);

//二叉搜索树的给定节点之间的和
int rangeSumBST(TreeNode* root, int L, int R);
int processsumBst(TreeNode* root, int aim);


struct node{
    string value;
    node(string data):value(data){ }
    bool operator==(const struct node& obj)const
    {
        return value==obj.value;
    }
    node(const node& obj)
    {
        this->value = obj.value;
    }
    node& operator=(const node& obj)
    {
        this->value = obj.value;
        return *this;
    }
};
namespace sdu{
    template<typename T>
    struct hash_func{
        
    };
    
    template<typename T>
    struct compare{
        
    };
};

//并查集int版
class unionsets{
private:
    unordered_map<int,int> fatherMap; //第一项是节点编号，第二项是节点的父节点
    unordered_map<int,int> sizeMap;  //第一项是节点编号，第二项是节点对应的并查集个数
    int fatherrecord;  //记录最终有几个并查集
public:
    unionsets(int N){
        fatherMap.clear();
        sizeMap.clear();
        for(int i =1;i<=N;i++){
            fatherMap.insert(make_pair(i,i));
            sizeMap.insert(make_pair(i,1));
        }
        fatherrecord = N;
    }
    int sizeunion(int index){
        return sizeMap[findfather(index)];
    }
    int numberfather() const{
        return this->fatherrecord;
    }
    int findfather(int index){
        int father = fatherMap[index];
        if(father != index){
            father = findfather(father);
        }
        fatherMap[index] = father;
        return father;
    }
    int issameset(int a,int b){
        return findfather(a) == findfather(b);
    }
    void unions(int a,int b){
        int afather = findfather(a);
        int bfather = findfather(b);
        if(afather != bfather){
            int afathersize = sizeMap[afather];
            int bfathersize = sizeMap[bfather];
            if(afathersize >= bfathersize){
                fatherMap[bfather] = afather;
                sizeMap[afather] = afathersize+bfathersize;
            }else{
                fatherMap[afather] = bfather;
                sizeMap[bfather] = afathersize+bfathersize;
            }
            fatherrecord--;
        }
    }
};
//畅通工程
struct data{
    int val1;
    int val2;
    data():val1(0),val2(0){ }
    data(int v1,int v2):val1(v1),val2(v2){ }
};
void projectsmooth();

template<typename T> //对并查集进行模版改造
class DisjointSets{
private:
    unordered_map<T,T,sdu::hash_func<T>,sdu::compare<T> > fatherMap;
    unordered_map<T,int,sdu::hash_func<T>,sdu::compare<T> > sizeMap;
    
public:
    DisjointSets(vector<T> nodes)
    {
        fatherMap.clear();
        sizeMap.clear();
        for(auto c : nodes)
        {
            fatherMap.insert(make_pair(c, c));
            sizeMap.insert(make_pair(c,1));
        }
    }
    
    T findFather(T nodes)//通过递归实现查找头节点
    {
        typename unordered_map<T,T,sdu::hash_func<T>,sdu::compare<T> >::iterator it;
        it = fatherMap.find(nodes);
        T father = it->second;
        if (!(father == nodes)){
            father = findFather(father);
        }
        it->second = father;
        return father;
    }
    
    bool issameset(T a,T b)
    {
        return findFather(a) == findFather(b);
    }
    
    void unionset(T a, T b){
        T aFather = findFather(a);
        T bFather = findFather(b);
        typename unordered_map<T,int,sdu::hash_func<T>,sdu::compare<T> >::iterator ita;
        typename unordered_map<T,int,sdu::hash_func<T>,sdu::compare<T> >::iterator itb;
        typename unordered_map<T,T,sdu::hash_func<T>,sdu::compare<T> >::iterator it;
        if (!(aFather == bFather)) {
            ita = sizeMap.find(aFather);
            itb = sizeMap.find(bFather);
            int aFrank = ita->second;
            int bFrank = itb->second;
            if (aFrank <= bFrank) {
                it = fatherMap.find(aFather);
                it->second = bFather;
                itb->second = aFrank + bFrank;
            }
            else
            {
                it = fatherMap.find(bFather);
                it->second = aFather;
                ita->second = aFrank + bFrank;
            }
        }
    }
};
//7.跳跃游戏
int jump(vector<int>& nums);
int processjump(vector<int>& nums,int i);
//7.改动态规划
int jumpdp(vector<int> &nums);
//8.数组中的最长连续序列
int maxlenarr(vector<int> &nums);
int merge(unordered_map<int, int> & arrmap,int less,int more);

//9.龙与地下城游戏问题
int calculateMinimumHP(vector<vector<int>>& dungeon);
int generateMininumHPdigui(vector<vector<int> >& dungen);
int processHP(vector<vector<int> >& dungen,int i,int j);


#endif /* dpexercise_hpp */
