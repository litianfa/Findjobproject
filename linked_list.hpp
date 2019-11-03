//
//  linked_list.hpp
//  c++
//
//  Created by litianfa on 2019/7/4.
//  Copyright © 2019 litianfa. All rights reserved.
//

#ifndef linked_list_hpp
#define linked_list_hpp
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;
//单链表节点
struct node{
    int val;
    struct node* next;
    node(int value):val(value),next(NULL){ }
};
//双链表节点
struct dounode{
    int val;
    struct dounode* previous;
    struct dounode* next;
    dounode(int value):val(value),previous(NULL),next(NULL) { }
};

//案例1.给定一个整数num，如何在节点值有序的环形链表中插入一个节点值为num的节点，并且保证这个环形链表依然有序
dounode* insertcyclelinked(int num,dounode* head);
//2.给定链表中的一个节点node，但不给定整个链表的头节点，如何在链表中删除节点，时间复杂度要求O(1)
void deleteNode(node* cur);
//3.给定一个链表的头节点head，在给定一个数num，请把链表调整成节点值小于num的节点放在链表的左边，值等于num的放在链表的中间，大于的放在链表的右边
//方法1，将链表放到一个数组中，进行partition排序就可以了
vector<int> linkedarrpartition(node* head,int num);
//方法2，直接在链表上进行排序，分别组成三个链表之后再让它们按次序进行连接
void linkedpartition(node* head,int num);
//4.给定两个链表的头节点，打印两个有序链表的公共部分
void printcommonlinklist(node* head1,node* head2);
//5.给定单链表的头节点，实现一个调整单链表的函数，使得有k个节点之间逆序，如果不足k个节点的最后几个节点不调整
//方法1，利用栈来实现逆序
node* changefunc1(node* head,int k);
//方法2，直接在链表上进行操作
node* optimalcahngefunc2(node* head,int k);
//通用反转链表函数
node* reverselinkedlist(node* start,node* end);
//6.给定一个单链表的头节点，链表中每个节点保存一个整数，在给定一个值，把所有等于这个给定值的节点都删掉
node* deleteprovidevalnodelist(node* head,int val);
//7.判断一个链表是否为回文结构
//方法一，用栈
bool isretwordlist1(node* head);
//方法二，用栈加快慢指针
bool isretwordlist2(node* head);
//方法三，只用快慢指针，链表逆序
bool isretwordlist3(node* head);
//8.复制含有rand指针节点的链表
struct randnode{
    int val;
    struct randnode* next;
    struct randnode* rand;
    randnode(int value):val(value),next(NULL),rand(NULL){ }
};
randnode* copyrandnode(randnode* head);
//9.如何判断一个链表是否有环，要求时间复杂度为O(N)，额外空间复杂度为O(1)
node* iscyclelist(node* head);
//10.如何判断两个无环链表是否相交
node* iscommonnocyclelist(node* head1,node* head2);
//11.如何判断两个有环链表是否相交
node* iscommonnodecyclelist(node* head1,node* head2);
//求链表的长度
int lenghtoflist(node* start,node* end);
//12.给定两个链表，如何判断两个链表是否相交,相交的话返回第一个相交的节点
node* arecommonlist(node* head1,node* head2);
//13,设计可以改变的缓存结构
//应用泛型编程
//定义双向链表的节点
template<typename T,typename V>
class Node{
public:
    T key;
    V value;
    Node<T,V>* last;
    Node<T,V>* next;
public:
    Node(T a,V b):key(a),value(b) { }
};

//实现自定义的双向链表
template<typename T,typename V>
class nodedoublelinkedlist{
private:
    Node<T,V>* head;
    Node<T,V>* tail;
public:
    nodedoublelinkedlist():head(NULL),tail(NULL){ }
    void addNode(Node<T,V>* newnode){
        if(newnode == NULL){
            return;
        }
        if(head == NULL){
            head = newnode;
            tail = newnode;
        }
        else{
            //这时至少有一个节点，必然是新的节点往双向链表的末尾加
            tail->next = newnode;
            newnode->last = tail;
            tail = newnode;
        }
    }
    
    void movenodetotail(Node<T,V>* node){
        if(tail == node)//如果末尾就是要移动的节点那就不用在费力气了
        {
            return;
        }
        if(head == node)//如果要移动的节点在双向链表的头部
        {
            head = node->next;
            head->last = NULL;
        }else{
            node->next->last = node->last;
            node->last->next = node->next;
        }
        tail->next = node;
        node->last = tail;
        tail = node;
        tail->next = NULL;
    }
    Node<T,V> removeHead(){
        if(head == NULL){
            return NULL;
        }
        Node<T,V> res = head;
        if(head == tail){
            head = NULL;
            tail = NULL;
        }else{
            head = res->next;
            head->last = NULL;
            res->next = NULL;
        }
        return res;
    }
    
};

template<typename T,typename V>
class MyCache{
private:
    //缓存结构可以由双端链表和哈希表相结合的方式实现
    unordered_map<T,Node<T,V> > nodemap;
    nodedoublelinkedlist<T,V> nodelist;
    int capacity;
public:
    MyCache(int cap):capacity(cap) { }
    V get(T key){
        typename unordered_map<T,Node<T,V> >::iterator it;
        it = nodemap.find(key);
        if(it != nodemap.end()){
            Node<T,V> res = it->second;
            nodelist.movenodetotail(res);
            return res.value;
        }
    }
    void set(T key,V value){
        typename unordered_map<T,Node<T,V> >::iterator it;
        it = nodemap.find(key);
        if(it != nodemap.end()){
            Node<T,V> node = it->second;
            node.value = value;
            nodelist.movenodetotail(node);
        }else{
            Node<T,V> newnode = new Node<T,V>(key,value);
            nodemap.insert(make_pair(key,newnode));
            if(nodemap.size() == capacity+1){
                removemostunusedcache();
            }
        }
    }
    
    void removemostunusedcache(){
        Node<T,V> removenode = nodelist.removeHead();
        T removekey = removenode.key;
        nodemap.erase(removekey);
    }
    
};

//14,LFU
class lfunode{
public:
    int key;
    int value;
    int times;
    lfunode* up;
    lfunode* down;
public:
    lfunode(int _key,int _value,int _times):key(_key),value(_value),times(_times),up(NULL),down(NULL){ }
    
};

class lfulist{
public:
    lfunode* head;
    lfunode* tail;
    lfulist* last;
    lfulist* next;
public:
    lfulist(lfunode* node){
        head = node;
        tail = node;
        last = NULL;
        next = NULL;
    }
    void addnodefromhead(lfunode* node){
        node->down = head;
        head->up = node;
        head = node;
    }
    bool isempty(){
        return head == NULL;
    }
    void deletenode(lfunode* node){
        if(head == tail){
            head = NULL;
            tail = NULL;
        }else{
            if(node == head)//要删的是头部
            {
                head = node->down;
                head->up = NULL;
            }
            else if(node == tail)//要删的是尾部
            {
                tail = node->up;
                tail->down = NULL;
            }
            else//要删的既不是头部也不是尾部
            {
                node->up->down = node->down;
                node->down->up = node->up;
            }
        }
        node->up = NULL;
        node->down = NULL;
    }
};

class lfucache{
private:
    int capacity;
    int size;//实际大小
    unordered_map<int, lfunode*> records; //这里需要把类型声明为指针，好处就是占内存不多,仅占8个字节的指针内存
    unordered_map<lfunode*,lfulist*> heads; //这里需要把类型声明为指针，好处就是占内存不多,仅占8个字节的指针内存
    lfulist* headlist;
    
public:
    lfucache(int capacity_):capacity(capacity_),size(0) {
        headlist = NULL;
    }
    
    void set(int key,int value){
        unordered_map<int, lfunode*>::iterator it = records.find(key);
        if(it != records.end()){
            lfunode* node = it->second;
            node->value = value;
            node->times++;
            unordered_map<lfunode*,lfulist*>::iterator itlfu = heads.find(node);
            lfulist* curnodelist = itlfu->second;
            move(node,curnodelist);
        }
        else{
            if(size == capacity)//若不为空，则删掉链表的最后一个节点
            {
                lfunode* node = headlist->tail;
                headlist->deletenode(node);
                modifyheadlist(headlist);
                records.erase(node->key);
                heads.erase(node);
                size--;
            }
            lfunode* node = new lfunode(key,value,1);
            if(headlist == NULL){
                headlist = new lfulist(node);
            }
            else{
                if(headlist->head->times == node->times){
                    headlist->addnodefromhead(node);
                }
                else{
                    lfulist* newlist = new lfulist(node);
                    newlist->next = headlist;
                    headlist->last = newlist;
                    headlist = newlist;
                }
                records.insert(make_pair(key,node));
                heads.insert(make_pair(node,headlist));
                size++;
            }
        }
    }
    
    bool modifyheadlist(lfulist* nodelist){
        if(nodelist->isempty()){
            if(headlist == nodelist){
                headlist = nodelist->next;
                if(headlist != NULL){
                    headlist->last = NULL;
                }
            }
            else{
                nodelist->last->next = nodelist->next;
                if(nodelist->next != NULL){
                    nodelist->next->last = nodelist->last;
                }
            }
            return true;
        }
        return true;
    }
    
    void move(lfunode* node,lfulist* oldnodelist){
        oldnodelist->deletenode(node);
        lfulist* prelist = modifyheadlist(oldnodelist) ? oldnodelist->last : oldnodelist;
        lfulist* nextlist = oldnodelist->next;
        if(nextlist == NULL){
            lfulist* newlist = new lfulist(node);
            if(prelist != NULL){
                prelist->next = newlist;
            }
            newlist->last = prelist;
            if(headlist == NULL){
                headlist = newlist;
            }
            heads.insert(make_pair(node,newlist));
        }else{
            if(nextlist->head->times == node->times){
                nextlist->addnodefromhead(node);
                heads.insert(make_pair(node,nextlist));
            }else{
                lfulist* newlist = new lfulist(node);
                if(prelist != NULL){
                    prelist->next = newlist;
                }
                newlist->last = prelist;
                newlist->next = nextlist;
                nextlist->last = newlist;
                if(headlist == nextlist){
                    headlist = newlist;
                }
                heads.insert(make_pair(node,newlist));
            }
        }
    }
    
    int get(int key){
        unordered_map<int, lfunode*>::iterator it = records.find(key);
        if(it == records.end()){
            return -1;
        }
        lfunode* node = it->second;
        node->times++;
        unordered_map<lfunode*,lfulist*>::iterator ith = heads.find(node);
        lfulist* curnodelist = ith->second;
        move(node, curnodelist);
        return node->value;
    }
    
};

#endif /* linked_list_hpp */
