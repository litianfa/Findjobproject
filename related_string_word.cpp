//
//  related_string_word.cpp
//  c++
//
//  Created by litianfa on 2019/7/2.
//  Copyright © 2019 litianfa. All rights reserved.
//

#include "related_string_word.hpp"

/****关于二叉树的一些操作***/
//1.moris遍历
void moristravel(TreeNode* cur)
{
    TreeNode* mostright = NULL;
    while(cur != NULL){
        if(cur->left != NULL){
            mostright = cur->left;
            while(mostright->right != NULL && mostright->right != cur)
            {
                mostright = mostright->right;
            }
            if(mostright->right == NULL){
                mostright->right = cur;
                cout<<cur->val<<" ";
                cur = cur->left;
                continue;
            }
            if(mostright->right == cur){
                mostright->right = NULL;
            }
        }else{
            cout<<cur->val<<" ";
        }
        
        cur = cur->right;
    }
}
//moris中序遍历
void morisIn(TreeNode* head)
{
    if(head == NULL)
        return;
    TreeNode* cur = head;
    TreeNode* mostright = NULL;
    while(cur != NULL){
        mostright = cur->left;
        if(mostright != NULL){
            while(mostright->right != NULL && mostright->right != cur){
                mostright = mostright->right;
            }
            if(mostright->right == NULL){
                mostright->right = cur;
                cur = cur->left;
                continue;
            }
            else{
                mostright->right = NULL;
            }
        }
        cout<<cur->val<<" ";
        cur = cur->right;
    }
    cout<<endl;
    return;
}

void generalPre(TreeNode* head)
{
    if(head == NULL)
        return;
    cout<<head->val<<" ";
    generalPre(head->left);
    generalPre(head->right);
}

//moris先序遍历
void morisPre(TreeNode* head)
{
    if(head == NULL)
        return;
    TreeNode* cur = head;
    TreeNode* mostright = NULL;
    while(cur != NULL){
        mostright = cur->left;
        if(mostright != NULL){
            while(mostright->right != NULL && mostright->right != cur){
                mostright = mostright->right;
            }
            if(mostright->right == NULL){
                mostright->right = cur;
                cout<<cur->val<<" ";
                cur = cur->left;
                continue;
            }
            else{
                mostright->right = NULL;
            }
        }else{
            cout<<cur->val<<" ";
        }
        cur = cur->right;
    }
    cout<<endl;
    return;
}
//moris后序遍历
void morisAft(TreeNode* head)
{
    if(head == NULL)
        return;
    TreeNode* cur = head;
    TreeNode* mostright = NULL;
    while(cur != NULL){
        mostright = cur->left;
        if(mostright != NULL){
            while(mostright->right != NULL && mostright->right != cur){
                mostright = mostright->right;
            }
            if(mostright->right == NULL){
                mostright->right = cur;
                cur = cur->left;
                continue;
            }
            else{
                mostright->right = NULL;
                printrightedge(cur->left);
            }
        }
        cur = cur->right;
    }
    printrightedge(head);
    return;
}
//打印链表的右边界
void printrightedge(TreeNode* head)
{
    if(head == NULL && head->right == NULL){
        return;
    }
    //给的head是头节点,需要翻转链表，然后打印，之后恢复链表
    TreeNode* ptr = head;
    TreeNode* next = NULL;
    TreeNode* help = NULL;
    while(ptr != NULL){
        next = ptr->right;
        ptr->right = help;
        help = ptr;
        ptr = next;
    }
    ptr = help;//记录一下反转后的头节点，位置后恢复原链表做准备
    //打印反转后的链表右边界
    while(ptr != NULL){
        cout<<ptr->val<<" ";
        ptr = ptr->right;
    }
    //恢复原链表
    ptr = help;
    help = NULL;
    next = NULL;
    while(ptr != NULL){
        next = ptr->right;
        ptr->right = help;
        help = ptr;
        ptr = next;
    }
    return;
}

//2.一般的递归打印二叉树
void printIntra(TreeNode* cur,string& str)
{
    if(cur == NULL){
        str = str+"#_";
        return ;
    }
    printIntra(cur->left,str);
    str = str+to_string(cur->val)+"_";
    printIntra(cur->right,str);
    
}
void printPretra(TreeNode* cur,string& str)
{
    if(cur == NULL){
        str = str + "*_";
        return;
    }
    printPretra(cur->left,str);
    printPretra(cur->right,str);
    str+=to_string(cur->val)+"_";
}
//KMP算法
vector<int> getnextarray(string& ptr)
{
    vector<int> next;
    next.resize((int)ptr.size());
    next[0] = -1;
    next[1] = 0;
    int pos = 2;
    int cn = 0;
    while(pos<next.size()){
        if(ptr[pos-1] == ptr[cn]){
            next[pos++] = ++cn;
        }
        else if(cn > 0){
            cn = next[cn];
        } else {
            next[pos++] = 0;
        }
    }
    return next;
}

int kmpalgor(string& str1,string& str2)
{
    if(str1.empty() || str2.empty())
        return -1;
    int i1 = 0;
    int i2 = 0;
    vector<int> next = getnextarray(str2);
    while(i1<str1.size() && i2<str2.size()){
        if(str1[i1] == str2[i2]){
            i1++;
            i2++;
        }else if(next[i2] == -1){
            i1++;
        }else{
            i2 = next[i2];
        }
    }
    return i2 == str2.size() ? i1-i2:-1;
}

//1.判断二叉树s中是否有与二叉树t拓扑结构相同的子树
bool issubtree(TreeNode* s,TreeNode* t)
{
    string str1,str2,str3,str4;
    printIntra(s,str1);
    printIntra(t,str2);
    printPretra(s, str3);
    printPretra(t, str4);
    if(kmpalgor(str1.size() >= str2.size() ? str1:str2,str1.size() < str2.size() ? str1:str2) == -1 || kmpalgor(str3.size() >= str4.size() ? str3:str4,str3.size() < str4.size() ? str3:str4) == -1)
        return false;
    return true;
}

//2.两个字符串是否互为变形词
bool anagram(string s, string t)
{
    int word[52] = {0};
    int index = 0;
    for(int i = 0;i<s.size();i++){
        if(s[i]>='a' && s[i] <='z'){
            index = s[i] - 'a';
            word[index]++;
        }
        else if(s[i]>='A' && s[i] <='Z'){
            index = s[i] - 'A'+26;
            word[index]++;
        }
    }
    for(int i = 0;i<t.size();i++){
        if(t[i]>='a' && t[i] <='z'){
            index = t[i] - 'a';
            word[index]--;
        }
        else if(t[i]>='A' && t[i] <='Z'){
            index = t[i] - 'A'+26;
            word[index]--;
        }
    }
    for(int i = 0;i<52;i++){
        if(word[i] != 0)
            return false;
    }
    return true;
}
//3.两个字符串是否互为旋转词
bool rotateString(string str1, string str2)
{
    if(str1.size() != str2.size())
        return false;
    string str = str1+str1;
    if(kmpalgor(str,str2) == -1)
        return false;
    return true;
}
//4.给定一个字符串，请在单词间做逆序调整
void reverseword(string& str,int start,int end)
{
    while(start<end){
        swap(str[start++],str[end--]);
    }
}
void changeword(string& str)
{
    int start = 0;
    int end = (int)str.size()-1;
    reverseword(str,start,end);
    for(int i = 0;i<str.size();i++){
        if(str[i] == ' '){
            end = i-1;
            reverseword(str,start,end);
            start = i+1;
        }
    }
    if(start != str.size()){
        end = (int)str.size()-1;
        reverseword(str,start,end);
    }
}
//附加题，左旋转字符串，字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部
void leftreversestringword(string& str,int len)
{
    if(len == str.size())
        return;
    int start = 0;
    int end = (int)str.size()-1;
    reverseword(str,start,end);
    reverseword(str,start,end-len);
    if(len>1)
        reverseword(str,end-len+1,end);
}
//5.给定一个字符串str，和一个整数i,i代表str中的位置，将str[0,i]移到右侧，str[i+1,N-1]部分移到左侧
void movepartofword(string& str,int i)
{
    int start = 0;
    int end = (int)str.size()-1;
    reverseword(str,start,i);
    reverseword(str,i+1,end);
    reverseword(str,start,end);
    return;
}
//6.最小字典序的字符串拼接方案
string sumstringword(string& str1,string& str2)
{
    string word;
    if(str1+str2 < str2+str1){
        word = str1+str2;
    }
    return word;
}
//7.给定一个字符串str,将其中所有的空格字符都替换成“%20”，假设str后面有足够的空间
void inserspaceword(string& str)
{
    int num = 0;
    int end = (int)str.size();
    for(int i = 0;i<end;i++){
        if(str[i] == ' '){
            num++;
        }
    }
    int edge = 3*num;
    num = edge+end;
    str.resize(num);
    int i = end-1;
    int j = num - 1;
    while(j>=0){
        if(str[i] == ' '){
            str[j--] = '0';
            str[j--] = '2';
            str[j--] = '%';
            i--;
        }
        else{
            str[j--] = str[i--];
        }
    }
    return;
}
//8.有效的括号序列
bool isValidParentheses(string &s)
{
    //用栈来解决
    stack<char> num;
    for(int i = 0;i<s.size();i++){
        switch(s[i]){
            case '(':
            case '{':
            case '[':
                num.push(s[i]);
                break;
            case ')':
                if(num.empty() || num.top() != '('){
                    return false;
                }
                num.pop();
                break;
            case '}':
                if(num.empty() || num.top() != '{'){
                    return false;
                }
                num.pop();
                break;
            case ']':
                if(num.empty() || num.top() != '['){
                    return false;
                }
                num.pop();
                break;
            default:
                continue;
        }
    }
    if(num.empty())
        return true;
    else
        return false;
}
//9.给定一个字符串，返回其中的最长无重复子串的长度
int lengthOfLongestSubstring(string s)
{
    if(s.empty())
        return 0;
    unordered_map<char,int> recordword; // 其中统计了每种字符之前出现的位置
    unordered_map<char,int>::iterator it;
    int pre = 0;
    int maxlen = 0;
    for(int i =0;i < (int)s.size() ; i++){
        it = recordword.find(s[i]);
        if(it == recordword.end()){
            pre++;
            recordword.insert(make_pair(s[i],i));
        }else{
            if(it->second > i-pre){
                pre = i - it->second;
            }else if(it->second == i-pre){
                ;
            }
            else{
                pre++;
            }
            it->second = i;
        }
        if(maxlen < pre){
            maxlen = pre;
        }
    }
    return maxlen;
}
//10.打印字符串子序列的问题
void stringcharsubarr(string& str,int i,string res)
{
    if(i == str.size()){
        cout<<res<<endl;
        return;
    }
    stringcharsubarr(str, i+1, res);
    stringcharsubarr(str, i+1, res+str[i]);
    return;
}
//11.打印字符串的全排列
void stringcharfullprocess(string str,int i)
{
    if(i == str.size()){
        cout<<str<<endl;
        return;
    }
    for(int j = i;j<str.size();++j){
        swap(str[i],str[j]);
        stringcharfullprocess(str, i+1);
        swap(str[i],str[j]);
    }
}
//扩展，求字符串的所有组合
void stringwordcombineprocess(string& str,int i,string pstr)
{
    if(i == str.size()){
        cout<<pstr<<endl;
        return;
    }
    stringwordcombineprocess(str, i+1, pstr+str[i]);
    stringwordcombineprocess(str, i+1, pstr);
}
//12.公式字符串求值
int getvalue(string str)
{
    int * p = value(str,0);
    return p[0];
}
int* value(string str,int i)
{
    deque<char> deq;
    int pre = 0;
    int* bra = NULL;
    while( i < str.size() && str[i] != ')'){
        if(str[i] >= '0' && str[i] <= '9') // 收集数字
        {
            pre = pre*10+ str[i++] - '0';
        }
        else if(str[i]!='(')//若遇到的是：+-*/
        {
            addNum(deq,pre);
            deq.push_back((str[i++])); // 把符号推进双端队列中去
            pre = 0;
        }
        else //若遇到的是"("
        {
            bra = value(str, i+1);
            pre = bra[0]; //返回的计算值传给bra
            i = bra[1]+1; //位置向后递增
        }
    }
    addNum(deq,pre);//
    int* ret = new int[2];
    ret[0] = getNum(deq);
    ret[1] = i;
    return ret;
}
void addNum(deque<char>& deq,int num)//此函数是用来计算乘除运算符的
{
    if(!deq.empty()){
        int cur = 0;
        char top = deq.back();
        deq.pop_back();
        if(top == '+' || top == '-')
        {
            deq.push_back(top); //若为+-，则不在此函数运算
        }
        else //若队列中的符号是*/则先计算
        {
            cur = (int)deq.back();
            deq.pop_back();
            num = top == '*' ? (cur*num) : (cur/num);
        }
    }
    deq.push_back(char(num));
}

int getNum(deque<char>& deq) //此函数是用来计算加减运算符的
{
    int res = 0;
    bool add = true;
    char cur = NULL;
    int num = 0;
    while(!deq.empty()){
        cur = deq.back();
        deq.pop_back();
        if(cur == '+') //若cur为+号
        {
            add = true;
        }
        else if(cur == '-')//cur为-号
        {
            add=false;
        }
        else //若cur为数字
        {
            num = (int)cur ;
            res+= add ? num : (-num);
        }
    }
    return res;
}

//13.回文字符串manacher算法
string maxLcpsLength(std::string const& str){
    vector<char> charArr = manacherString(str);
    int* arr = new int[charArr.size()]; //Recording the max return number circle
    int index = -1;
    int pR = -1;
//    int max = 0;
    int maxContainer = -1;
    for(int i = 0;i!= charArr.size();i++){
        arr[i] = pR > i ? min(arr[2*index-i],pR-i):1; //式中的2*index-i是为了参照对称点的回文半径
        while(i+arr[i]< charArr.size() && i - arr[i] > -1) //判断条件分别为回文左右边界都不能大于当前数组的左右边界
        {
            if(charArr[i+arr[i]] == charArr[i-arr[i]])//继续往外扩充回文边界
            {
                arr[i]++;
            }
            else{
                break;
            }
        }
        if(i+arr[i]>pR){
            pR = i+arr[i];
            index = i; //index表示回文中心
        }
        if(pR == charArr.size()){
            maxContainer = arr[i];
            break;
        }
        //        max = std::max(max,arr[i]);
    }
    vector<char> res;
    res.resize(str.size()-maxContainer+1);
    for(int i = 0;i<res.size();i++){
        res[(int)(res.size()-1-i)] = charArr[i*2+1];
    }
    //返回处理好的回文字符串
    string ret = str;
    for(auto c : res)
        ret += c;
    return ret; //return the optimal return number
}

vector<char> manacherString(std::string const& str)
{
    unsigned long length = 2*str.size()+1;
    //    boost::shared_array<char> ctr(new char[length]);
    vector<char> arr;
    arr.resize(length);
    int index = 0;
    for(int i = 0;i!=length;i++){
        arr[i] = (i%2) == 0?'#':str[index++]; //& point wether it is an odd number!
    }
    return arr;
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
