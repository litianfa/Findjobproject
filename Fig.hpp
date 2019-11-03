//
//  Fig.hpp
//  c++
//
//  Created by litianfa on 2019/6/29.
//  Copyright © 2019 litianfa. All rights reserved.
//

#ifndef Fig_hpp
#define Fig_hpp
#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <set>
using namespace std;

//图的架构定义，C++实现
struct edge;
struct node{
    int val;
    int in;
    int out;
    list<node*> nexts;//这样定义的话需要默认构造函数
    list<edge> edges;
    node(){
        val = 0;
        in = 0;
        out = 0;
    }
    node(int val):val(val),in(0),out(0){ }
    node(int val,int in,int out):val(val),in(in),out(out){ }
    bool operator==(const node& obj){
        return (this->val == obj.val)&&(this->in == obj.in);
    }
};

struct hashnode{
    size_t operator()(const node& obj) const
    {
        return obj.in * obj.val + obj.out;
    }
};

struct hashcompare{
    bool operator()(const node& a,const node& b)const
    {
        if(a.val == b.val && a.in == b.in && a.out == b.out)
            return true;
        else
            return false;
    }
};

struct edge{
    int weight;
    node* from;
    node* to;
    edge(){
        weight = 0;
        from = NULL;
        to = NULL;
    }
    edge(int weight,node* fnode,node* tnode){
        this->weight = weight;
        from = fnode;
        to = tnode;
    }
};

class compedge{
public:
    bool operator()(const edge& a,const edge& b)
    {
        return a.weight>b.weight;
    }
};

struct hashedge{
    size_t operator()(const edge& obj) const
    {
        return obj.from->in * obj.weight + obj.to->out;
    }
};

struct compareedge{
    bool operator()(const edge& a,const edge& b)const
    {
        if(a.weight == b.weight && a.from->val == b.from->val)
            return true;
        else
            return false;
    }
};

struct graph{
    unordered_map<int,node> nodes;
    unordered_set<edge,hashedge,compareedge> edges;
};

//生成图
graph creategraph(const vector<vector<int> >& matrix);

//图的宽度优先遍历
void widthgraphBST(node obj);
//图的深度优先遍历
void dfs(node obj);

//图的拓扑排序
vector<int> toposort(const graph& gra);
//最小生成树K算法
unordered_set<edge,hashedge,compareedge> Krulal(graph gra);
//最短路径版K算法
int Kminmumpath(graph gra,int n);

//最短路
void minimumpath();

//P算法
unordered_set<edge,hashedge,compareedge> Palgraph(graph gra);

namespace sdu{
    //模版泛化
    template<typename T>
    struct hash_func{
        
    };
    
    template<typename T>
    struct compare{
        
    };
    //模版特化
    template<>
    struct hash_func<node>{
        size_t operator()(const node& obj) const
        {
            return obj.in * obj.val + obj.out;
        }
    };
    template<>
    struct compare<node>{
        bool operator()(const node& a,const node& b)const
        {
            if(a.val == b.val && a.in == b.in && a.out == b.out)
                return true;
            else
                return false;
        }
    };
    
};
//并查集进行泛型化
template<typename T>
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

#endif /* Fig_hpp */
