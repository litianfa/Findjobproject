//
//  Tree.hpp
//  c++
//  二叉树
//  Created by litianfa on 2019/7/6.
//  Copyright © 2019 litianfa. All rights reserved.
//

#ifndef Tree_hpp
#define Tree_hpp

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
using namespace std;
struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(int value):val(value),left(NULL),right(NULL){ }
};
//案例一，用非递归的方式实现二叉树先序、中序、后序遍历
void treeprintpretra(TreeNode* head);
void treeprintintra(TreeNode* head);
void treeprintafttra(TreeNode* head);
//附加moris遍历
void moris(TreeNode* head);
//moris中序遍历
void morisIn(TreeNode* head);
//moris先序遍历
void morisPre(TreeNode* head);
//moris后序遍历
void morisAft(TreeNode* head);
//打印链表的右边界
void printrightedge(TreeNode* head);
//案例2，给定一颗二叉树的头节点head,请按照层遍历的方式来打印二叉树
void bfstree(TreeNode* head);
//案例3，二叉树的序列化和反序列化
//先序序列化和反序列化
string pretreetostr(TreeNode* root);
TreeNode* prestrtotree(string data);
//案例4，给定一颗二叉树的头节点，判断这棵树是否为平衡二叉树
struct returnAVLdata{
    bool isbalance;
    int height;
    returnAVLdata(bool ib,int h):isbalance(ib),height(h) { }
};
returnAVLdata isavltree(TreeNode* head);
//案例5，给定一颗二叉树，判断这棵二叉树是否是搜索二叉树
bool issearchtree(TreeNode* head);
//案例6，判断一棵树上是否为完全二叉树
bool isfulltree(TreeNode* root);
//案例7，找特殊节点树的后继节点
struct Node{
    int val;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    Node(int value):val(value),left(NULL),right(NULL),parent(NULL){ }
};
Node* follownode(Node* root);
//案例8，折纸问题
void pressit(int N);
void zip(vector<string>& arr,int i,int N,bool isdown);
//案例9，找出搜索二叉树中的两个错误的节点
vector<TreeNode*> searcherrornode(TreeNode* root);
//案例10，从二叉树的节点A出发，可以向上或者向下走，但沿途的节点只能经过一次，当到达节点B时，路径上的节点数叫做A到B的距离，给定一颗二叉树，求整棵树上节点之间的最大距离
struct returnmaxdistance{
    int maxdistance;
    int maxdtoh;
    returnmaxdistance(int maxh,int h):maxdistance(maxh),maxdtoh(h){ }
};
returnmaxdistance maxdistancetree(TreeNode* root);
//案例11，给定一颗二叉树，已知其中所有节点的值都不一样，找到含有节点最多的搜索二叉子树，并返回这棵子树的头节点
struct returnsearchdata{
    TreeNode* root;
    int nodenums;
    int maxval;
    int minval;
    returnsearchdata(TreeNode* head,int nums,int val1,int val2):root(head),nodenums(nums),maxval(val1),minval(val2){ }
};
returnsearchdata getmaxnumssearchtree(TreeNode* head);
//案例12，前缀树
class TrieNode{
public:
    int path;
    int end;
    vector<TrieNode*> map;
public:
    TrieNode():path(0),end(0)
    {
        map.resize(26);
    }
    
};

class Trie{
private:
    TrieNode* root;
public:
    Trie()
    {
        root = new TrieNode();
    }
    void insert(string word)
    {
        char ptr[word.size()];
        strcpy(ptr,word.c_str());
        TrieNode* node = root;
        int index = 0;
        for (int i = 0; i < word.size()-1; i++) {
            index = ptr[i] - 'a';
            if (node->map[index] == NULL) {
                node->map[index] = new TrieNode();
            }
            node = node->map[index];
            node->path++;
        }
        node->end++;
        return;
    }
    
    void Delete(string word) {
        if (search(word)) {
            char chs[word.size()];
            strcpy(chs,word.c_str());
            TrieNode* node = root;
            int index = 0;
            for (int i = 0; i < word.size()-1; i++) {
                index = chs[i] - 'a';
                if ((node->map[index])->path-- == 1) {
                    node->map[index] = NULL;
                    return;
                }
                node = node->map[index];
            }
            node->end--;
        }
    }
    
    bool search(string word) {
        if (word.empty()) {
            return false;
        }
        char chs[word.size()];
        strcpy(chs,word.c_str());
        TrieNode* node = root;
        int index = 0;
        for (int i = 0; i < word.size()-1; i++) {
            index = chs[i] - 'a';
            if (node->map[index] == NULL) {
                return false;
            }
            node = node->map[index];
        }
        return node->end != 0;
    }
    
    int prefixNumber(string pre) {
        if (pre.empty()) {
            return 0;
        }
        char chs[pre.size()];
        strcpy(chs,pre.c_str());
        TrieNode* node = root;
        int index = 0;
        for (int i = 0; i < pre.size()-1; i++) {
            index = chs[i] - 'a';
            if (node->map[index] == NULL) {
                return 0;
            }
            node = node->map[index];
        }
        return node->path;
    }
    
};
//案例12的扩展用前缀树求子数组的最大异或和
class trienode{
public:
    vector<trienode*> nexts;
    
public:
    trienode(){
        nexts.resize(2);
    }
};

class Numtire{
public:
    trienode* head;
    
public:
    Numtire(){
        head = new trienode();
    }
    
    void add(int num){
        trienode* cur = head;
        for(int move = 31;move >= 0;move--){
            int path = ((num >> move) & 1);
            cur->nexts[path] = (cur->nexts[path] == NULL) ? new trienode() : cur->nexts[path];
            cur = cur->nexts[path];//继续往下走
        }
    }
    int maxxor(int num){
        trienode* cur = head;
        int res = 0;
        for(int move = 31; move >= 0; move--){
            int path = (num >> move)&1;
            int best = move == 31 ? path : (path ^ 1);//期待要选的路
            best = cur->nexts[best] != NULL ? best : (best ^ 1);//实际选择的路
            res |= (path ^ best) << move;//设置答案的每一位
            cur = cur->nexts[best];//继续往下走
        }
        return res;
    }
};
//案例13，返回一个树的最大和最小
class returnnodeinfo{
public:
    int max;
    int min;
public:
    returnnodeinfo(int _min_,int _max_):max(_max_),min(_min_){ }
};
returnnodeinfo pro(TreeNode* head);
//案例14，多叉树问题，组织一个晚宴，直接上级来，则直接下级不来，每个成员都有活跃度，求晚宴的最佳活跃度安排
//定义多叉树
class multinode{
public:
    int value;
    int size; //子节点的个数
    multinode* next[];//有多个下级子节点
public:
    multinode(int data):value(data),size(0){
        
    }
};
class ReturnData{
public:
    int lai_huo;
    int bu_lai_huo;
public:
    ReturnData(int a,int b):lai_huo(a),bu_lai_huo(b){ }
};
//主要递归求最大活跃度
ReturnData partyprocess(multinode* head);
//案例15，跳表实现
/*class skiplistnode{
public:
    int value;
    deque<skiplistnode*> nextnodes; //0->NULL,1->value节点第一层下一个节点是谁，2->依此类推
public:
    skiplistnode(int value){
        this->value = value;
    }
};

class skiplist{
private:
    skiplistnode* head; //
    int maxlevel; //最大层数
    int size; //记录一共有多少节点被加入到跳表
    static const double  PROBABILITY;
public:
    skiplist(){
        size = 0;
        maxlevel = 0;
        head = NULL;
    }
    void add(int newvalue){
        if(!contains(newvalue)){
            size++;
            int level = 0;
            while(random()<PROBABILITY)//揉了几层
            {
                level++;
            }
            while(level > maxlevel)//先建立随机出来的层数对应的nextnodes，前提条件是揉出来的层数大于当前的最大层数
            {
                head->nextnodes.push_back(NULL);
                maxlevel++;
            }
            skiplistnode* newnode = new skiplistnode(newvalue); //建立要添加的值的节点
            skiplistnode* current = head;  //将当前头指针给定义的当前指针
            do //思路应该是从最上层往下找，先下到揉出的对应层，然后看此时它对应的下一层是比这个新加入的值大还是小，然后找合适的位置添加新节点，之后就是从上到下不断的更新新节点的nextnodes
            {
                current = findnext(newvalue,current,level);
                newnode->nextnodes.push_front(current->nextnodes[level]);
                current->nextnodes[level] = newnode;
            }while(level-- > 0);
        }
    }
    
    void deletenode(int deletevalue)
    {
        if(contains(deletevalue)){
            skiplistnode* deletenode = find(deletevalue);
            size--;
            int level = maxlevel;
            skiplistnode* current = head;
            do{
                current = findnext(deletenode->value,current,level);
                if(deletenode->nextnodes.size() > level){
                    current->nextnodes[level] = deletenode->nextnodes[level];
                }
            }while(level-- > 0);
        }
    }
    skiplistnode* find(int e){
        return find(e,head,maxlevel);
    }
    
    skiplistnode* find(int e,skiplistnode* current,int level){
        do{
            current = findnext(e,current,level);
        }while(level-- > 0);
        return current;
    }
    
    skiplistnode* findnext(int e,skiplistnode* current,int level){
        skiplistnode* next = current->nextnodes[level];//找到指定层的下一个节点
        while(next!= NULL){
            int value = next->value;
            if(e<value) //若找到，则弹出
            {
                break;
            }
            current = next;
            next = current->nextnodes[level];
        }
        return current;
    }
    
    int listsize(){
        return size;
    }
    
    bool contains(int value){
        skiplistnode* node = find(value);
        return node != NULL && node->value != 0 && node->value == value;
    }
    
};

const double skiplist::PROBABILITY = 0.5;*/

//构造哈夫曼树
struct huffmannode{
    int data;
    struct huffmannode* left;
    struct huffmannode* right;
    huffmannode(int _data):data(_data),left(NULL),right(NULL){ }
};

huffmannode* createhuffman(vector<int>& nums,int n);

#endif /* Tree_hpp */
