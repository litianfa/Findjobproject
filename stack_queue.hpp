//
//  stack_queue.hpp
//  c++
//
//  Created by litianfa on 2019/7/3.
//  Copyright © 2019 litianfa. All rights reserved.
//

#ifndef stack_queue_hpp
#define stack_queue_hpp
#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_map>
using namespace std;

/***案例***/
//1.实现一个特殊的栈，在实现栈的基本功能的基础上，在实现返回栈的最小元素的操作
class MinStack {
private:
    stack<int> record;
    stack<int> mindata;
    int minval;
public:
    MinStack():minval(INT_MAX){ }
    
    /*
     * @param number: An integer
     * @return: nothing
     */
    void push(int number) {
        // write your code here
        minval = std::min(number,minval);
        record.push(number);
        mindata.push(minval);
    }
    
    /*
     * @return: An integer
     */
    int pop() {
        // write your code here
        if(record.empty()){
            return 0;
        }
        int data = record.top();
        record.pop();
        mindata.pop();
        if(data == minval && !mindata.empty())
            minval = mindata.top();
        else if(mindata.empty()){
            minval = INT_MAX;
        }
        else{
            ;
        }
        return data;
    }
    
    /*
     * @return: An integer
     */
    int min() {
        // write your code here
        if(record.empty()){
            return 0;
        }
        return mindata.top();
    }
};
//2.用栈实现队列结构
class MyQueue {
private:
    stack<int> pushstack;
    stack<int> popstack;
public:
    MyQueue() {
        
    }
    
    void dao(){
        if(popstack.empty()){
            while(!pushstack.empty()){
                popstack.push(pushstack.top());
                pushstack.pop();
            }
        }
    }

    void push(int element) {
        // write your code here
        pushstack.push(element);
    }
    
    int pop() {
        if(pushstack.empty() && popstack.empty()){
            return 0;
        }
        else{
            dao();
            int data = popstack.top();
            popstack.pop();
            return data;
        }
    }
    int top() {
        dao();
        return popstack.top();
    }
};
//3.实现栈的逆序，要求只能用递归函数和这个栈本身的操作来实现，而不能自己申请另外的数据结构
void stackreverse(stack<int>& restack);
int processstack(stack<int>& restack);
//4.栈排序,从栈顶到栈低按从大到小
void sortstack(stack<int>& source);
//5.返回窗口最大值，在一个整形数组和一个大小为w的窗口从数组的最左边滑倒最右边，窗口每滑动一下，返回一个长度为n-w+1的数组res,ress代表每一个窗口状态下的最大值
vector<int> maxSlidingWindow(vector<int> &nums, int k);
//6.给定一个没有重复元素的数组arr,写出生成这个数组的MaxTree的函数，要求如果数组长度为N，则时间复杂度为O(N),额外空间复杂度为O(N)
struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(int value):val(value),left(NULL),right(NULL){ }
};
void getmaxtree(vector<int>& arr);
//7.用队列实现栈结构
class myqueuetostack{
private:
    queue<int> pushsta;
    queue<int> midsta;
private:
    void dao(){
        if(pushsta.size() > 1){
            midsta.push(pushsta.front());
            pushsta.pop();
        }
        else if(pushsta.empty()){
            while(!midsta.empty()){
                pushsta.push(midsta.front());
                midsta.pop();
            }
            while(pushsta.size() > 1){
                midsta.push(pushsta.front());
                pushsta.pop();
            }
        }
    }
public:
    myqueuetostack(){ }
    void push(int val){
        midsta.push(val);
    }
    int front(){
        dao();
        return pushsta.front();
    }
    void pop(){
        dao();
        pushsta.pop();
    }
};
//8.用数组实现队列
template<typename T>
class myqueue{
private:
    int totalsize;
    int length;
    int frontptr;
    int backptr;
    T* ptr;
    
private:
    void ptrdetect(){
        if(frontptr == totalsize)
            frontptr = 0;
        if(backptr == totalsize)
            backptr = 0;
    }
    
public:
    myqueue(int size):totalsize(size){
        ptr = new T[size];
        length = 0;
        frontptr = 0;
        backptr = 0;
    }
    
    void push_back(T value){
        ptrdetect();
        if(length < totalsize){
            ptr[backptr++] = value;
            length++;
        }
        else{
            throw "Full";
        }
    }
    T pop_front(){
        ptrdetect();
        if(length > 0){
            T temp = ptr[frontptr++];
            --length;
            return temp;
        }
        else{
            throw "Empty";
        }
    }
};

//9.用数组实现栈
template<typename T>
class mystack{
private:
    int length;
    T* ptr;
    int this_index; //栈顶指针
public:
    explicit mystack(int size):length(size),this_index(0){
        ptr = new T[length];
    }
    ~mystack(){
        if(ptr != NULL){
            delete[] ptr;
        }
        
    }
    mystack(mystack<T> const& tr){
        if(ptr == tr){
            return;
        }
        length = tr.length;
        delete[] ptr;
        ptr = new T[length];
        for(this_index = 0;this_index<tr.this_index;this_index++){
            ptr[this_index] = tr[this_index];
        }
        
    }
    mystack<T> operator=(mystack<T> const& tr){
        mystack<T> temp(tr);
        delete[] ptr;
        ptr = new T[length];
        for(this_index = 0;this_index<temp.this_index;this_index++){
            ptr[this_index] = temp[this_index];
        }
        delete temp;
        return *this;
    }
    
    int size() const{
        return length;
    }
    
    //栈的特性
    void push(T tr){
        if(this_index < length)
            ptr[this_index++] = tr;
        else{
            throw "beyond the bound";
        }
    }
    
    T pop(){
        if(this_index > 0){
            --this_index;
            T temp = ptr[this_index];
            return temp;
        }
        else
            return 0;
        
    }
};
//10.猫狗队列问题
class Pet{
private:
    string type;
public:
    Pet(string _type):type(_type){ }
    string getPetType() const{
        return this->type;
    }
};

class Dog:public Pet{
public:
    Dog():Pet("dog"){ }
};

class Cat:public Pet{
public:
    Cat():Pet("cat"){ }
};

class DogCatQueue{
private:
    Pet* pet;
    long timecount; //时间戳
public:
    DogCatQueue(Pet* _pet,long count):pet(_pet),timecount(count){ }
    
    string gettype() const{
        return this->pet->getPetType();
    }
    
    Pet* getpet() const{
        return this->pet;
    }
    
    long getCount() const{
        return this->timecount;
    }
};

class Petqueue{
private:
    queue<DogCatQueue> dogqueue;
    queue<DogCatQueue> catqueue;
    long count;
public:
    Petqueue():count(0){
        
    }
    void add(Pet* pet){
        if(pet->getPetType() == "cat"){
            catqueue.push(DogCatQueue(pet,this->count++));
        }
        else if(pet->getPetType() == "dog"){
            dogqueue.push(DogCatQueue(pet,this->count++));
        }
    }
    
    Pet* pollAll(){
        if(isempty()){
            throw "All queue is empty";
        }
        else if(isdogempty()){
            cout<<"The dogqueue is empty"<<endl;
        }
        else if(iscatempty()){
            cout<<"The catqueue is empty"<<endl;
        }
        if((catqueue.front()).getCount() < (dogqueue.front()).getCount()){
            Pet* temp = (catqueue.front()).getpet();
            catqueue.pop();
            return temp;
        }
        else {
            Pet* temp = (dogqueue.front()).getpet();
            dogqueue.pop();
            return temp;
        }
        
    }
    
    Pet* pollDog(){
        if(!dogqueue.empty()){
            Pet* temp = (dogqueue.front()).getpet();
            dogqueue.pop();
            return temp;
        }
        else{
            throw "dogqueue is empty";
        }
    }
    
    Pet* pollCat(){
        if(!catqueue.empty()){
            Pet* temp = (catqueue.front()).getpet();
            catqueue.pop();
            return temp;
        }
        else {
            throw "catqueue is empty";
        }
    }
    
    bool isempty() const{
        return catqueue.empty() && dogqueue.empty();
    }
    
    bool isdogempty() const{
        return dogqueue.empty();
    }
    
    bool iscatempty() const{
        return catqueue.empty();
    }
    
};
//11.子数组的和不大于给定整数的数量
//暴力解法
int subarraylessnum(vector<int> arr,int num);
bool islessnum(vector<int> arr,int start,int end,int num);
//窗口解法
int windowsubarrlessnum(vector<int> arr,int num);
//12.设计单调栈，1.实现求一个数组的每个元素相邻的左边的最大值和最小值
class arr_left_right{
public:
    int index; //防止出现多个相同的值对应不同的序号
    int left_index;
    int right_index;
public:
    arr_left_right(int _index,int _left_index,int _right_index):index(_index),left_index(_left_index),right_index(_right_index){ }
};

vector<arr_left_right> getarrleftright(vector<int> arr);

//13.求最大子矩阵的大小,利用单调栈结构
int maxsizearray(vector<vector<int> > arr);
int maxsubmatrix(int* arr,int length);
//14.山峰对问题（好像是网易原题）
class Tpair{
public:
    int value;
    int times;
public:
    Tpair(int _value):value(_value),times(1){ }
};

int nextindex(int i,int size);
long getInternalSum(int n);
long communication(vector<int> arr);
//15.队列的最大值，定义g一个队列并实现函数max得到队列里的最大值，要求函数max、push_back和pop_front的时间复杂度都是O(1);
template <typename T>
class maxqueue{
private:
    queue<T> data;
    deque<T> maxdata;
public:
    maxqueue(){ }
    
    void pushback(T val){
        data.push(val);
        while(!maxdata.empty() && maxdata.back() <= val){
            maxdata.pop_back();
        }
        maxdata.push_back(val);
    }
    T popfront(){
        if(data.front() == maxdata.front()){
            maxdata.pop_front();
        }
        T temp = data.front();
        data.pop();
        return temp;
    }
    T max(){
        return maxdata.front();
    }
};

#endif /* stack_queue_hpp */
