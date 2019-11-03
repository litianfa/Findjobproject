//
//  coding_guide.hpp
//  c++
//
//  Created by litianfa on 2019/7/24.
//  Copyright © 2019 litianfa. All rights reserved.
//

#ifndef coding_guide_hpp
#define coding_guide_hpp
#include <iostream>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <math.h>
#include <memory>
#include <string>
#include <queue>
#include <deque>
#include <bitset>
#include <algorithm>
#include <list>
#include <map>
#include <cstdio>
#include <cstring>
using namespace std;

//链表问题
struct ListNode{
    int val;
    struct ListNode* next;
    ListNode(int value):val(value),next(NULL){ }
};
//1.删除链表中间节点
ListNode* deletemiddlepoint(ListNode* head);
//进阶，给定链表的头节点head、整数a,b,实现删除位于a/b处节点的函数
ListNode* deleteabnode(ListNode* head,int a,int b);
//2.两个单链表生成相加链表
ListNode* createnewsumList(ListNode* head1,ListNode* head2);
//进阶优化额外空间复杂度,用链表的逆序求解
ListNode* createnewsumlistoptimal(ListNode* head1,ListNode* head2);
//3.删除无序单链表中值重复出现的节点
void deletesamevalnodelist(ListNode* head);
//4.在单链表中删除指定值的节点
ListNode* deletepointnodelist(ListNode* head,int num);
//5.实现智能指针shared_ptr
template<typename T>
class Smart_Ptr{
private:
    T *_ptr;
    int* use_count;
public:
    Smart_Ptr(T *ptr = NULL);
    Smart_Ptr(const Smart_Ptr<T>& s);
    Smart_Ptr<T>& operator=(const Smart_Ptr<T>& s);
    T& operator*();
    T* operator->();
    ~Smart_Ptr();
    T* get();
    bool unique();
    long int usecount();
};
template<typename T>
Smart_Ptr<T>::Smart_Ptr(T *ptr)
{
    _ptr = ptr;
    try{
        use_count = new int(1);
    }
    catch(...){
        delete _ptr;
        _ptr = NULL;
        delete use_count;
        use_count = NULL;
    }
}

template<typename T>
Smart_Ptr<T>::Smart_Ptr(const Smart_Ptr<T>& s):_ptr(s._ptr),use_count(s.use_count)
{
    ++(*use_count);
}

template<typename T>
Smart_Ptr<T>& Smart_Ptr<T>::operator=(const Smart_Ptr<T>& s)
{
    if(this != &s){
        if(--(*(this->use_count)) == 0){
            delete this->_ptr;
            delete this->use_count;
        }
        _ptr = s._ptr;
        use_count = s.use_count;
        ++(*use_count);
    }
    return *this;
}

template<typename T>
T& Smart_Ptr<T>::operator*(){
    return *(this->_ptr);
}

template<typename T>
T* Smart_Ptr<T>::operator->(){
    return (this->_ptr);
}

template<typename T>
Smart_Ptr<T>::~Smart_Ptr(){
    --(*(this->use_count));
    if(this->use_count == 0){
        delete _ptr;
        _ptr = NULL;
        delete use_count;
        use_count = NULL;
    }
}
template<typename T>
T* Smart_Ptr<T>::get(){
    return this->_ptr;
}
template<typename T>
bool Smart_Ptr<T>::unique(){
    if(*use_count == 1)
        return true;
    else
        return false;
}
template<typename T>
long int Smart_Ptr<T>::usecount(){
    return *(this->use_count);
}
//6.将搜索二叉树转换为双向链表
struct Node{
    int val;
    struct Node* left;
    struct Node* right;
    Node(int value):val(value),left(NULL),right(NULL){}
};
//中序遍历
Node* searchtreetodoubledirectionlist(Node* root);
//7.单链表的选择排序
ListNode* selectsortlist(ListNode* head);
//8.一种怪异的节点删除方式
void deletespecialnode(ListNode* spnode);
//9.向有序的环形单链表中插入新节点
ListNode* insertintocuclelist(ListNode* head,int num);
//10.合并两个有序的单链表
ListNode* convergetwolists(ListNode* head1,ListNode* head2);
//11.按照左右半区的方式重新组合单链表
ListNode* leftrightmidareacombinelist(ListNode* head);

//二叉树问题
//1.打印二叉树的边界节点
void printedge1(Node* head);
int getheight(Node* head,int l);
void setedgemap(Node* head,int l,vector<vector<Node*>>& edgemap);
void printleafnotinmap(Node* head,int l,vector<vector<Node*>>& edgemap);

//修改标准2代码
vector<int> boundaryofbinarytree(Node* root);
void getbounds(Node* root,vector<int>& res,bool leftbound,bool rightbound);
//2.较为直观的打印二叉树
void printtree(Node* head);
void printinorder(Node* head,int height,string to,int len);
string getspace(int num);
//3.在二叉树中找到累加和为指定值的最长路径长度
//用哈希表来解决
int getmaxpathlength(Node* root,int sum);
int preorder(Node* root,int sum,int presum,int level,int maxlen,unordered_map<int,int>& summap);
//4.n个整数的无序数组m，找到每个元素后面比它大的第一个数，要求时间复杂度为O(N)
vector<int> findmax(vector<int> num);
//5.找到二叉树中的最大搜索二叉子树
struct searchbinary{
    Node* head;
    int maxval;
    int minval;
    int nums;
    searchbinary(Node* _head,int maxv,int minv,int lev):head(_head),maxval(maxv),minval(minv),nums(lev){ }
};
searchbinary findmaxsearchbinarytree(Node* root);
//6.找到二叉树中符合搜索二叉树条件的最大拓扑结构
int bsttopusize1(Node* root);
int maxtopo(Node* root,Node* n);
bool isbstnode(Node* root,Node* n,int value);
//7.求未排序数组中累加和为规定值的最长子数组长度
int getmalengtharray(vector<int>& nums,int k);
//8.二叉树的按层打印与ZIGZAG打印
void edgeprintbinarytree(Node* root);
void ZigZagprintbinarytree(Node* root);
//9.调整搜索二叉树中两个错误的节点
vector<Node*> gettwoerrsearchnode(Node* root);
//10.判断t1树是否包含t2树的全部的拓扑结构
bool isincludetopo(Node* t1,Node* t2);
bool isincludeprocess(Node* t1,Node* t2);
//11.判断二叉树是否为平衡二叉树
struct balancetree{
    bool isbalance;
    int leveldiff;
    balancetree(bool isb,int leve):isbalance(isb),leveldiff(leve){}
};
bool judgebalancetree(Node* root);
balancetree isbalancetree(Node* root);
//12.根据后续数组重建搜索二叉树
bool isresultforsearchtree(vector<int> nums);
bool isresultprocess(vector<int>& nums,int start,int end);

Node* rebuildsearchbinarytree(vector<int>& nums);
Node* rebuildsearchtreeprocess(vector<int>& nums,int start,int end);
//13.通过有序数组生成平衡搜索二叉树
Node* generatebalancesearchtree(vector<int>& nums);
Node* generateprocesstree(vector<int>& nums,int start,int end);
//14.在二叉树中找到两个节点的最近公共祖先
Node* findminrelationroot(Node* head,Node* h1,Node* h2);
bool findminrelationprocess(Node* root,Node* h);
//
Node* lowestancestor(Node* head,Node* o1,Node* o2);
//进阶：如果查询两个节点的最近公共祖先的操作十分频繁，想法让单条查询的查询时间减少
int reducetimeoffindlowestancestor(Node* head,Node* o1,Node* o2);
//15.Tarjan算法与并查集解决二叉树节点间最近公共祖先的批量查询问题
struct Query{
    Node* o1;
    Node* o2;
    Query(Node* o1,Node* o2):o1(o1),o2(o2){ }
};
vector<int> tarjanandunionforlowestancestor(Node* head,vector<Query> nums);
//16.利用先序和中序遍历重建二叉树
Node* rebuildbinarytree(vector<int> pretra,vector<int> intra);
Node* preintreeprocess(vector<int>& pretra,int pi,int pj,vector<int>& intra,int ni,int nj,unordered_map<int,int>& record);
//17.中序和后续遍历重建二叉树
Node* rebuildbinary2(vector<int> intra,vector<int> postra);
Node* inposprocess(vector<int>& intra,int ni,int nj,vector<int>& postra,int si,int sj,unordered_map<int,int>& map);
//18.先序和后序遍历重建二叉树
Node* rebuildbinary3(vector<int> pre,vector<int> pos);
Node* preposprocess(vector<int> pre,int pi,int pj,vector<int> pos,int si,int sj,unordered_map<int,int>& map);
//19.通过先序和中序数组生成后序数组
vector<int> generateposvectorfromprein(vector<int> pre,vector<int> in);
void generatevalposprocess(vector<int> pre,int pi,int pj,vector<int> in,int ni,int nj,unordered_map<int,int>& record,vector<int>& pos);
//20.统计生成所有不同的二叉树
int numbinarytree(int N);
//动态规划
int numstrees(int n);

//21.统计完全二叉树的节点数
struct returndata{
    int num;
    int lefth;
    returndata(int nums,int left):num(nums),lefth(left){ }
};
returndata recordnumberofnodeforbinarytree(Node* head);
//满二叉树节点数的计算公式
int calculatenumber(int k);
//22.换钱的最少货币数
int minnumsmoney(vector<int> nums,int aim);
//进阶
int minmumnumsmoneypaper(vector<int> nums,int aim);
//23.换钱的方法数
//递归
int numspaybackmoney(vector<int>& nums,int aim);
int numspaybackprocess(vector<int>& nums,int i,int aim);
//动态规划
int dpnumspaybackmoney(vector<int>& nums,int aim);
//24.最长递增子序列
//方法1.
vector<int> getdp1(vector<int> nums);
vector<int> generatelis(vector<int> nums,vector<int> dp);
vector<int> maxlensubindexarray(vector<int> nums);
//25.汉诺塔问题
//递归
void hannuotaproblem(int n,string from,string mid,string to);
//进阶问题，求数组中此时表示的状态是最有轨迹中的哪一个状态
long long getstateofoptimalmove(vector<int> nums);
long long getstateprocess(vector<int>& nums,int i,int from,int mid,int to);
//非递归方式
long long getstateoptimalsolution(vector<int>& nums);
//26.最长公共子序列，经典的动态规划问题
string getmaxlencommonsubarray(string str1,string str2);
//27.最长公共子串
string getmaxlensunstr(string str1,string str2);
//动态规划
string dpgetmaxlensubstr(string str1,string str2);
//改进型动态规划
string improvedpgetmaxlensub(string str1,string str2);
//28.字符串交错组成
bool iscrossstr(string str1,string str2,string aim);
//29.龙与地下城游戏问题
int getintialblood(vector<vector<int>> dungeon);
//30.数字字符串转换成字母组合的种数
//递归版实现
int classesofnumtoword(string number);
int classesnumprocess2(string& str,int i);
//动态规划实现
int dpclassesofnumtoword(string number);
//31.表达式得到期望结果的组成种数
int getnumbersfordesired(string express,bool desired);
bool isvalid(string& str);
int processfordesired(string& str,bool desired,int l,int r);
//动态规划
int dpgetnumbersfordesired(string express,bool desired);
//32.排成一条线的纸牌博弈问题
//递归解决
int first(vector<int>& nums,int l,int r);
int last(vector<int>& nums,int l,int r);
int whowinnumbers(vector<int> nums);
//动态规划
int dpwhowinnumbers(vector<int> nums);
//31.跳跃游戏
//递归
int jumpprocess(vector<int>& nums,int i);
int getminmumjump(vector<int>& nums);
//动态规划
int dpjump(vector<int> nums);
//32.数组中的最长连续序列
//直接用排序的思路，随机快排，时间复杂度O(N)
void quicksortnums(vector<int>& nums,int l,int r);
vector<int> partitionforquick(vector<int>& nums,int start,int end);
int getmaxlencontinueindex(vector<int>& nums);
//用哈希表实现复杂度O(N)
int ntimegetmaxlenindex(vector<int>& nums);
//33.N皇后问题
int nqueenproblem(int n);
int queenprocess(vector<int>& nums,int i);
bool isqueen(vector<int>& nums);
//字符串解法
vector<vector<string>> Nqueenproblemstring(int n);
void queenprocessstr(vector<int>& nums,int i,vector<vector<int>>& queen);
//34.判断两个字符串是否互为变形词
bool isreshapestring(string str1,string str2);
//35.字符串中数字子串的求和
int getsumofnumberstring(string str);
//36.去掉字符串中连续出现的k个0的子串
string deletekzero(string str,int k);
//37.判断两个字符串是否互为旋转词
bool isrotateword(string str1,string str2);
//38.将整数字符串转成整数值
int numberstringconverttoint(string str);
//字符串实现两个整数字符串的大小比较
int isequal(string& str1, string str2);
//39.替换字符串中连续出现的制定字符串
string replacestring(string str,string from,string to);
//40.字符串的统计字符串
string countstring(string str);
//41.判断字符数组中是否所有的字符都只出现过一次
//时间复杂度为O(N)
bool isonlyoncepresent(string str);
//空间复杂度为O(1)
bool onlyoncepresent(string str);
//用快速排序实现
void quicksortforonlyonce(string& str,int l,int r);
vector<int> onlyoncepartition(string& str,int start,int end);
bool onlyoncebyquicksort(string str);
//用堆排序
void strheapinsert(string& str,int index);
void strheapify(string& str,int index,int size);
void strheapsort(string& str);
bool onlyoncebyheapsort(string& str);

//42.在有序但是含有空的数组中查找字符串
int findleftindexstr(vector<string>& nums,string str);
//43.字符串的调整与替换
void findandereplace(char* str);
//44.翻转字符串
void reversestringword(string& str,int l,int r);
void reversestringwordbyindex(string& str);
//附加题
void movelefttoright(string& str,int size);
//45.数组中两个字符串的最小距离
int getmindistance(vector<string> strs,string str1,string str2);
//46.添加最少字符使字符串整体都是回文字符串
string plussharpstringword(string& str);
string manacherstringwordreturnword(string str);
//47.括号字符串的有效性和最长有效长度
bool isvalidstringword(string str);
//补充题目，给定一个括号字符串str,返回最长的有效括号子串
int getmaxlenforvalidinclude(string str);
//48.公式字符串求值
vector<int> value(string& str,int i);
void addnum(deque<string>& record,int num);
int getnum(deque<string>& record);
int getvalue(string& str);
//49.0左边必有1的二进制字符串数量
//递归版
int getlenofcomfortvalue(int n);
int processgetlencom(int n,int i,string str);
bool iscomfort(string& str);
//进阶优化版
long dpgetlenofcomfort(int n);
//50.拼接所有字符串产生字典顺序最小的大写字符串
string getmincombinestringword(vector<string> str);
struct compareword{
    bool operator()(const string& a,const string& b){
        if(a+b<b+a)
            return true;
        else
            return false;
    }
};
//51.找到字符串的最长无重复字符子串
int getunrepeatsubstringword(vector<int>& nums,int len);
//52.找到被指的新类型字符
string getnewtypestringword(string& str,int k);
//53.最小包含子串的长度
int getgivenstringwordsunstring(string str1,string str2);
//54.质数与素数问题
 //质数计数
int countprimenumber(int n);
 //优化版厄尔多塞筛法
int improvecountprimenums(int n);
//报文转换
void baowenconvert(void);
//质数扩展
int minvalueprimebit(int low,int high);
//转发消息
void converttopeople(void);
//55.回文最少分割数
int returnwordmincutnumber(string s);
//56.字符串匹配问题
bool iscomfortstringword(string& str1,string& str2,int i,int j);
//动态规划
bool isvalidstringword(string& str1,string& str2);
void initdpcomfortstring(string& str1,string& str2,int** dp);
bool idmatchdp(string& str1,string& str2);
//57.字典树的实现（前缀树）
class trietreenode{
public:
    int path;
    int end;
    vector<trietreenode*> nexts;
public:
    trietreenode(){
        path = 0;
        end = 0;
        nexts.resize(26);
        for(int i = 0;i<26;i++){
            nexts[i] = NULL;
        }
    }
};

class trietree{
public:
    trietreenode* root;
public:
    trietree()
    {
        root = new trietreenode();
    }
    void inserttree(string word){
        if(word.empty()){
            return;
        }
        trietreenode* node = root;
        node->path++;
        int index = 0;
        int strlen = (int)word.size();
        for(int i = 0;i<strlen;i++){
            index = word[i] - 'a';
            if(node->nexts[index] == NULL){
                node->nexts[index] = new trietreenode();
            }
            node = node->nexts[index];
            node->path++;
        }
        node->end++;
    }
    
    void deleteword(string word){
        if(word.empty()){
            return;
        }
        if(searchword(word)==0)
            return;
        trietreenode* node = root;
        if(--node->path == 0){
            node = NULL;
            return;
        }
        int index = 0;
        int strlen = (int)word.size();
        for(int i = 0;i<strlen;i++){
            index = word[i]-'a';
            if(--node->nexts[index]->path == 0){
                node->nexts[index] = NULL;
                return;
            }
            node = node->nexts[index];
        }
    }
    
    int prefixnumber(string pre){
        if(pre.empty())
            return 0;
        int index = 0;
        int strlen = (int)pre.size();
        trietreenode* node = root;
        for(int i = 0;i<strlen;i++){
            index = pre[i]-'a';
            if(node->nexts[index] == NULL){
                return 0;
            }
            node = node->nexts[index];
        }
        return node->path;
    }
    
    int searchword(string word){
        if(word.empty()){
            return 0;
        }
        int index = 0;
        int strlen  = (int)word.size();
        trietreenode* node = root;
        for(int i = 0;i<strlen;i++){
            index = word[i]-'a';
            if(node->nexts[index] == NULL){
                return 0;
            }
            node = node->nexts[index];
        }
        return node->end;
    }
};
//58.不用额外变量交换两个整数的值
void changethetwoint(int& a,int& b);
//59.不用任何比较判断找出两个数中较大的数
int myflip(int n);
int mysign(int n);
int getmaxvaluebetweentwoint(int& a,int& b);
//60.只用位运算不用算术运算实现整数的加减乘除运算
int summarybitversion(int a,int b);
int subbitversion(int a,int b);
int plusbitversion(int a,int b);
int dividebitversion(int a,int b);
//61.整数的二进制表达式中有多少个1
int getnumsoftheint(int n);
//62.在其他数都出现偶数次的数组中找到出现奇数次的数
//只有一个出现奇数次
int findoddnumberofint(vector<int> nums);
//有两个数出现奇数次
vector<int> findtwooddnumbersofint(vector<int> nums);
//63.在其他数都出现K次的数组中找到只出现一次的数
int findoncepresentnums(vector<int>& nums,int k);
//把单个数转换为K进制的数
vector<int> getchangeknums(int num,int& k);
//64.转圈打印矩阵
void printcyclematrix(vector<vector<int>>& matrix);
void processprintcyclematrix(vector<vector<int>>& matrix,int row0,int col0,int row1,int col1);
//65.将正方形矩阵顺时针转动90度
void transpositionmatrix(vector<vector<int>>& matrix);
void processtranspositionmatrix(vector<vector<int>>& matrix,int row0,int col0,int row1,int col1);
//66.之字形打印矩阵
void printzigzagmatrix(vector<vector<int>>& matrix);
void processprintzigzagmatrix(vector<vector<int>>& matrix,bool istoptobottom,int toprow,int topcol,int botrow,int botcol);
//67.找到无序数组中最小的K个数
vector<int> getlessknumbers(vector<int>& nums,int k);
void improvequicksort(vector<int>& nums,int k,int l,int r);
vector<int> improvepartition(vector<int>& nums,int start,int end);
//68.需要排序的最短子数组长度
int needsortnumbers(vector<int>& nums);
//69.在数组中找到出现次数大于N/K的数
int getnumberofvector(vector<int>& nums);
//进阶，给定一个整形数组，在给定一个整数K，打印所有出现次数大于N/K的数，如果没有输出-1
void printgreaternknumbers(map<int,int>& nums,int n,int k);
//70.在行和列都排好序的矩阵中找数
bool isincludematrix(vector<vector<int>>& matrix,int n,int m,int k);
//71.最长的可整合子数组的长度
int maxlencouldmergearray(vector<int>& nums);
//72.不重复打印排序数组中相加和为给定值的所有二元组和三元组
void doublefactorarray(vector<int>& nums,int k);
//三元组
void printhreeuniquethrid(vector<int>& nums,int k);
void printrestdoublefactor(vector<int>& nums,int f,int l,int r,int k);
//73.未排序的正数数组中累加和为给定值的最长子数组的长度
int getmaxlensubarray(vector<int>& nums,int k);
//74.未排序数组中累加和为给定值的最长子数组系列问题
int getmaxlengthsubarraysolutions(vector<int>& nums,int k);
//75.未排序数组中累加和小于等于给定值的最长子数组长度
int getmaxlengthlessksunarray(vector<int>& nums,int k);
//76.计算数组的小和
int getminsumarray(vector<int>& nums);
int mergersortminsum(vector<int>& nums,int l,int r);
int processmergerminsum(vector<int>& nums,int l,int mid,int r);
//77.自然数数组的排序
void naturenumbersort(vector<int>& nums,int n);
//78.奇数下标都是奇数或者偶数下标都是偶数
void oddarragearray(vector<int>& nums,int n);
//79.子数组的最大累加和问题
int getmaxsumofarray(vector<int>& nums);
//80.子矩阵的最大累加和问题
int getmaxsumofmatrix(vector<vector<int>>& matrix,int m,int n);
//81.在数组中找到一个局部最小的位置
int getpartminindex(vector<int>& nums);
//82.数组中子数组的最大累乘积
double getmaxsummultisubarray(vector<double>& nums,int& n);
//83.打印N个数组整体最大的Top K
void printtopknumbersarray(vector<int>& nums,int k);
void heapsortfortopk(vector<int>& nums,int k);
void rearrangeindexheapsort(vector<int>& nums,int index);
void heapifyfortopk(vector<int>& nums,int index,int r);
//84.边界都是1的最大正方形的大小
int getmaxsquaresize(vector<vector<int>>& grid);
//85.不包含本位置值的累乘数组
vector<int> getsumnultiarray(vector<int>& nums,int n,int k);
//86.数组的partition调整
void arraypartition(vector<int>& nums,int n);
//87.求最短通路径
//递归
int getmindistancepath(vector<vector<int>>& matrix,int m,int n);
void processmindistancepath(int pre,int tor,int toc,vector<vector<int>>& matrix,vector<vector<int>>& map,queue<int>& rq,queue<int>& cq);
//88.数组中未出现的最小正整数
int getminposintnumber(vector<int>& nums,int len);
//89.数组排序后相邻数的最大差值
int getmaxdifferencearraynums(vector<int>& nums,int n);
//90.从5随机到7随机及其扩展
int rand1to7();
//补充题目 给定一个以p概率产生0，以1-p概率产生1的c随机函数rand01p如下:
int rand1to6();
//进阶问题

//91.一行代码求两个数的最大公约数
//如果q和r分别是m除以n的商及余数，即m=nq+r,那么m和n的最大公约数等于n和r的最大公约数
int gcd(int m,int n);

//92.有关阶乘的两个问题
long resultzeronumbers(int n);
long resultzeronumbers2(int n);
//进阶问题
int minlowoneposition(int num);
//93.判断一个点是否在矩形内部
bool isincluderectangle(double x1,double y1,double x4,double y4,double x,double y);
bool isincluderectangle2(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4,double x,double y);
//94.判断一个点是否在三角形内部
//内角比较法，正确率46%
bool isincludetriangle(double x1,double y1,double x2,double y2,double x3,double y3,double x,double y);
bool isincludetriangle2(double x1,double y1,double x2,double y2,double x3,double y3,double x,double y);
//面积法
double getsidelen(double x1,double y1,double x2,double y2);
double getarea(double x1,double y1,double x2,double y2,double x3,double y3);
bool isinside(double x1,double y1,double x2,double y2,double x3,double y3,double x,double y);
//95.折纸问题
void printorigamiproblem(int n);
void ziporigami(int i,int n,vector<string>& nums,bool isdown);
//96.蓄水池算法
vector<int> getknumsrand(int max,int k);
//注意单调栈结构，n个整数的无序数组，找到每个元素后面比它大的第一个数
vector<int> getnextmaxnumbers(vector<int>& nums);
//97.算术表达式转后缀表达式
string topostfix(string str);
int tovalue(string str);
//98.最大的leftMax与rightMax之差的绝对值
int absofleftmaxdiffrightmaxnums(vector<int>& nums);
//99.设计可以变更的缓存结构,双向链表外加哈希表
//100.设计RandomPool结构
template<typename T>
class myrandompool{
private:
    unordered_map<T,int> keymap;
    unordered_map<int,T> indexmap;
    int index;
public:
    void Insert(T key){
        typename unordered_map<T,int>::iterator it;
        it = keymap.find(key);
        if(it == keymap.end()){
            keymap.insert(make_pair(key,index));
            indexmap.insert(make_pair(index++,key));
        }
    }
    void Delete(T key){
        typename unordered_map<T,int>::iterator it;
        it = keymap.find(key);
        if(it != keymap.end()){
            int deleteindex = it->second;
            int realdeleteindex = --index;
            int lastkey = indexmap[realdeleteindex];
            indexmap[deleteindex] = lastkey;
            keymap[lastkey] = deleteindex;
            keymap.erase(key);
            indexmap.erase(realdeleteindex);
        }
    }
    T getRandom(){
        if(index != 0){
            int randomindex = rand()%index;
            return indexmap[randomindex];
        }
        else{
            return T(NULL);
        }
    }
};
//101.调整[0,x)区间上的数出现的概率
double randXPowerK(int k);
//102.路径数组变统计数组
void getcountnumsarray(vector<int>& nums);
void pathstodistans(vector<int>& nums);
void distanstonums(vector<int>& nums);
//103.正数数组的最小不可组成和
//递归版
int getimpossiblesumarray(vector<int>& nums);
void processgetminpossible(vector<int>& nums,int i,unordered_set<int>& record,int sum);
//动态规划版
int dpgetinpossibelsumarray(vector<int>& nums);
//进阶问题
int dpoptimalimpossiblesum(vector<int>& nums);
//104.一种字符串和数字的对应关系
void getrelationshipbetweenwordnum(void);
//105.1到n中1出现的次数
//暴力递归方法
int processgetcountoneoccur(int n);
//找规律方法
int solution2(int num);
int getlenofnum(int num);
int powerbaseof10(int base);
//106.从N个数中等概率打印M个数
void printrandomnums(vector<int>& nums,int n);
//107.判断一个数是否是回文数
bool ispalindromicnumber(int n);
//108.在有序旋转数组中找到最小值
int getminfromrotatearray(vector<int>& nums,int& n);
//109.在有序旋转数组中找到一个数
bool gettargetnumfromrotatearray(vector<int>& nums,int num);
//110.数字的中文表达和英文表达
vector<string> getEnglishandChineseofnum(int num);
//111.分糖果问题
int distributecandysolution(vector<int> nums,int n);
//KMP手撸代码
void isincludekmpmethod(string& str1,string& str2);
vector<int> getnextarrayofkmpmethod(string& str2);
//112.一种消息接收并打印的结构设计
void printsequencenumbers(vector<int>& nums,int n);
//113.随时找到数据流的中位数
class MedianHolder{
private:
    priority_queue<int> bigheap;//大根堆
    priority_queue<int,vector<int>,greater<int>> smallheap;//小根堆
private:
    void resequenceheap(){
        if(bigheap.size() > smallheap.size()+1){
            while(bigheap.size() > smallheap.size()){
                smallheap.push(bigheap.top());
                bigheap.pop();
            }
        }
        else if(smallheap.size() > bigheap.size()+1){
            while(smallheap.size() > bigheap.size()){
                bigheap.push(smallheap.top());
                smallheap.pop();
            }
        }
    }
public:
    void push(int val){
        if(bigheap.empty()){
            bigheap.push(val);
            return;
        }
        else if(bigheap.top() >= val){
            bigheap.push(val);
        }
        else
        {
            if(smallheap.empty()){
                smallheap.push(val);
            }
            else if(smallheap.top()<=val){
                smallheap.push(val);
            }
            else{
                bigheap.push(val);
            }
        }
        resequenceheap();
    }
    double getmedianholder(){
        if(bigheap.empty())
            return -1;
        if(smallheap.empty()){
            return bigheap.top();
        }
        size_t size = bigheap.size()+smallheap.size();
        if(size%2 == 0){
            double res = (bigheap.top() + smallheap.top())/2.0;
            return res;
        }
        else{
            if(bigheap.size()>smallheap.size())
                return bigheap.top();
            else
                return smallheap.top();
        }
    }
};
//114.在两个长度相等的排序数组中找到上中位数
//方法1，谁小谁先走
int getupmediannumber(vector<int>& num1,vector<int>& num2,int n);
//115.在两个排序数组中找到第K小的数
int getminknumbersoftwoarray(vector<int>& num1,vector<int>& num2,int n,int m,int k);
//116.两个有序数组间相加和的TOP K问题
class indexrecord{
public:
    int i1;
    int i2;
public:
    indexrecord(int i1,int i2):i1(i1),i2(i2){ }
    indexrecord(const indexrecord& obj){
        this->i1 = obj.i1;
        this->i2 = obj.i2;
    }
};

struct indexhash{
    int operator()(const indexrecord& index){
        size_t hashcode = 0;
        hashcode = index.i1+index.i2 + (index.i1+index.i2)%2;
        return hashcode;
    }
};

struct indexcompare{
    bool operator()(const indexrecord& index1,const indexrecord& index2){
        if(index1.i1 == index2.i1 && index1.i2 == index2.i2)
            return true;
        else
            return false;
    }
};

vector<int> gettopknumbersofarray(vector<int>& num1,vector<int>& num2,int n,int k);
void processgettopknumbersofarray(vector<int>& num1,vector<int>& num2,int i1,int i2,int& count,priority_queue<int>& bigheap,unordered_set<indexrecord,indexhash,indexcompare>& record);
//117.出现次数的TOP K问题
class stringrecord{
public:
    int count;
    string word;
public:
    stringrecord(int count,string word){
        this->count = count;
        this->word = word;
    }
    bool operator<(const stringrecord& s1) const
    {
        if(this->count < s1.count){
            return true;
        }
        else
            return false;
    }
    bool operator>(const stringrecord& s1) const
    {
        return !(*this<s1);
    }
    
};
void getpresenttopknums(vector<string>& nums,int k);
//118.Manacher算法
string getstringmagic(string& str);
int getmaxlenpalindromeword(string& str);
//119.丢棋子问题
long long getmincountnumbers(long long n,long long k);
//最优解
int log2n(int n);
int optimalsolution(int n,int k);
//120.花匠问题
//先用递归实现
int processmincolor(vector<int>& nums,int i,int num,int maxval,int sum);
int getmindraincolortime(vector<int>& nums,int num);
//二分法实现
int getneednum(vector<int>& nums,int& len,int limit);
int getminbinarysearchmethodcolortime(vector<int>& nums,int num);
//121.邮局选址问题
int mindistances(vector<int>& nums,int num);
//122.马走日问题



#endif /* coding_guide_hpp */
