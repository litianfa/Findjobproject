//
//  Fig.cpp
//  c++
//
//  Created by litianfa on 2019/6/29.
//  Copyright © 2019 litianfa. All rights reserved.
//

#include "Fig.hpp"

//最短路
void minimumpath()
{
    vector<vector<int> > matrix;
    vector<int> temp;
    vector<int> ret;
    int N = 0,M = 0;
    cout<<"please input data:"<<endl;
    cin>>N>>M;
    while(!(N == 0 && M == 0)){
        for(int i = 0;i<M;i++){
            int from,to,time;
            cin>>from>>to>>time;
            temp.push_back(from);
            temp.push_back(to);
            temp.push_back(time);
            matrix.push_back(temp);
            temp.clear();
        }
        ret.push_back(Kminmumpath(creategraph(matrix),N));
        matrix.clear();
        N = 0;
        M = 0;
        cin>>N>>M;
    }
    for(int i = 0;i<ret.size();i++){
        cout<<ret[i]<<endl;
    }
}


//生成图
graph creategraph(const vector<vector<int> >& matrix)
{
    graph graph;
    unordered_map<int,node>::iterator got;
    unordered_map<int,node>::iterator gotto;
    for (int i = 0; i < matrix.size(); i++) {
        int from = matrix[i][0];
        int to = matrix[i][1];
        int weight = matrix[i][2];
        got = graph.nodes.find(from);
        if (got == graph.nodes.end()) {
            graph.nodes.insert(make_pair(from,node(from)));
        }
        gotto = graph.nodes.find(to);
        if (gotto == graph.nodes.end()) {
            graph.nodes.insert(make_pair(to, node(to)));
        }
        got = graph.nodes.find(from);
        gotto = graph.nodes.find(to);
        got->second.out++;
        gotto->second.in++;
        edge newEdge(weight, &(got->second), &(gotto->second));
        got->second.nexts.push_back(&(gotto->second));
        got->second.edges.push_back(newEdge);
        graph.edges.insert(newEdge);
    }
    return graph;
}

//图的宽度优先遍历
void widthgraphBST(node obj)
{
    queue<node> que;
    unordered_set<int> qset;
    unordered_set<int>::iterator it;
    que.push(obj);
    qset.insert(obj.val);
    while(!que.empty()){
        node temp = que.front();
        que.pop();
        cout<<temp.val<<" , "<<temp.in<<" , "<<temp.out<<endl;
        while(!temp.nexts.empty()){
            node next = *(temp.nexts.front());
            temp.nexts.pop_front();
            it = qset.find(next.val);
            if(it == qset.end()){
                que.push(next);
                qset.insert(next.val);
            }
        }
    }
}

//图的深度优先遍历
void dfs(node obj)
{
    stack<node> sta;
    sta.push(obj);
    unordered_set<int> mset;
    unordered_set<int>::iterator it;
    mset.insert(obj.val);
    cout<<obj.val<<" ";
    while(!sta.empty()){
        node cur = sta.top();
        sta.pop();
        while(!cur.nexts.empty()){
            node next = *(cur.nexts.front());
            cur.nexts.pop_front();
            it = mset.find(next.val);
            if(it == mset.end()){
                sta.push(cur);
                sta.push(next);
                mset.insert(next.val);
                cout<<next.val<<" ";
                break;
            }
        }
    }
}

//图的拓扑排序
vector<int> toposort(const graph& gra)
{
    queue<node> zeroqueue;
    unordered_map<node,int,hashnode,hashcompare> inmap;
    unordered_map<int,node>::const_iterator it = gra.nodes.begin();
    while(it!=gra.nodes.end()){
        node cur = it->second;
        inmap.insert(make_pair(cur,cur.in));
        if(cur.in == 0)//入度为0
        {
            zeroqueue.push(cur);
        }
        ++it;
    }
    vector<int> arr;
    while(!zeroqueue.empty()){
        node cur = zeroqueue.front();
        zeroqueue.pop();
        cout<<cur.val<<" ";
        arr.push_back(cur.val);
        while(!cur.nexts.empty()){
            node* next = cur.nexts.front();
            cur.nexts.pop_front();
            inmap.erase(*next);
            --(next->in);
            inmap.insert(make_pair(*next,next->in));
            if(inmap[*next] == 0){
                zeroqueue.push(*next);
            }
        }
    }
    return arr;
}

//最小生成树K算法
unordered_set<edge,hashedge,compareedge> Krulal(graph gra)
{
    vector<node> input;
    priority_queue<edge,vector<edge>,compedge> edgeobj;
    unordered_map<int,node>::const_iterator it = gra.nodes.begin();
    while(it != gra.nodes.end()){
        input.push_back(it->second);
        ++it;
    }
    DisjointSets<node> unigra(input);
    unordered_set<edge,hashedge,compareedge>::iterator start = gra.edges.begin();
    while(start != gra.edges.end()){
        edgeobj.push(*start);
        ++start;
    }
    unordered_set<edge,hashedge,compareedge> result;
    while(!edgeobj.empty()){
        edge cur = edgeobj.top();
        edgeobj.pop();
        if(!unigra.issameset(*(cur.from), *(cur.to))){
            result.insert(cur);
            unigra.unionset(*(cur.from), *(cur.to));
        }
    }
    return result;
}

//最短路径版K算法
int Kminmumpath(graph gra,int n)
{
    vector<node> input;
    int minpath = INT_MAX;
    priority_queue<edge,vector<edge>,compedge> edgeobj;
    unordered_map<int,node>::const_iterator it = gra.nodes.begin();
    while(it != gra.nodes.end()){
        input.push_back(it->second);
        ++it;
    }
    DisjointSets<node> unigra(input);
    unordered_set<edge,hashedge,compareedge>::iterator start = gra.edges.begin();
    while(start != gra.edges.end()){
        edgeobj.push(*start);
        if((start->from->val == 1 && start->to->val == n) || (start->from->val == n && start->to->val == 1)){
            minpath = min(minpath,start->weight);
        }
        ++start;
    }
    int result = 0;
    while(!edgeobj.empty()){
        edge cur = edgeobj.top();
        edgeobj.pop();
        if(!unigra.issameset(*(cur.from), *(cur.to))){
            result += cur.weight;
            unigra.unionset(*(cur.from), *(cur.to));
        }
    }
    return min(minpath,result);
}

//P算法
unordered_set<edge,hashedge,compareedge> Palgraph(graph gra)
{
    priority_queue<edge,vector<edge>,compedge> edgepri;
    unordered_set<node,hashnode,hashcompare> mset;
    unordered_map<int,node>::iterator it = gra.nodes.begin();
    unordered_set<node,hashnode,hashcompare>::iterator setit;
    unordered_set<edge,hashedge,compareedge> result;
    node temp = it->second;
    mset.insert(temp);
    while(!temp.edges.empty()){
        edge cur = temp.edges.front();
        temp.edges.pop_front();
        edgepri.push(cur);
    }
    while(!edgepri.empty()){
        edge cur = edgepri.top();
        edgepri.pop();
        setit = mset.find(*(cur.to));
        if(setit == mset.end()){
            result.insert(cur);
            temp = *cur.to;
            mset.insert(temp);
            while(!temp.edges.empty()){
                edge cur = temp.edges.front();
                temp.edges.pop_front();
                edgepri.push(cur);
            }
        }
    }

    return result;
}
