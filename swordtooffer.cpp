//
//  swordtooffer.cpp
//  c++
//
//  Created by litianfa on 2019/7/14.
//  Copyright © 2019 litianfa. All rights reserved.
//

#include "swordtooffer.hpp"

//剑指offer的面试题练习
//1.青蛙跳台问题
int timesofjumpqingwa(int n){
    if(n == 0)
        return 0;
    int i = n-1;
    int ret = 1;
    while(i>0){
        ret = ret * 2;
        i--;
    }
    return ret;
}
//2.旋转数组的最小数字,怎么感觉直接用二分查找来解非常方便
int minrecyclearr(vector<int>& nums)
{
    if(nums.size() == 1)
        return nums[0];
    int l = 0;
    int r = (int)nums.size()-1;
    if(nums[l]<nums[r]){
        return nums[l];
    }
    while(l<r){
        int mid = l+(r-l)/2;
        if(nums[mid] < nums[l]){
            r = mid;
        }else if(nums[mid] > nums[r]){
            l = mid+1;
        }else if(nums[l]<nums[r]){
            return nums[l];
        }
    }
    return nums[l];
}
//3.矩阵中的路径,有什么回溯法
bool haspath(vector<vector<char> >& matrix,string str)
{
    if(matrix.empty() || str.empty())
        return false;
    int rows = (int)matrix.size();
    int cols = (int)matrix[0].size();
    bool** visited = new bool*[rows];
    for(int i = 0; i<rows;i++){
        visited[i] = new bool[cols];
    }
    for(int i = 0;i<rows;i++){
        for(int j = 0;j<cols;j++){
            visited[i][j] = false;
        }
    }
    int pathlen = 0;
    for(int i = 0;i<rows;i++){
        for(int j = 0;j<cols;j++){
            if(haspathcore(matrix,rows,cols,i,j,str,pathlen,visited)){
                return true;
            }
        }
    }
    
    return false;
}
bool haspathcore(vector<vector<char> >& matrix,int rows,int cols,int i,int j,string str,int& pathlen,bool** visited)
{
    if(str[pathlen] == '\0')
        return true;
    bool hpath = false;
    if(i >= 0 && i< rows && j>= 0 && j < cols && matrix[i][j] == str[pathlen] && !visited[i][j]){
        ++pathlen;
        visited[i][j] = true;
        hpath = haspathcore(matrix,rows,cols,i,j-1,str,pathlen,visited)||  haspathcore(matrix,rows,cols,i-1,j,str,pathlen,visited)|| haspathcore(matrix,rows,cols,i,j+1,str,pathlen,visited)||haspathcore(matrix,rows,cols,i+1,j,str,pathlen,visited);
        if(!hpath){
            --pathlen;
            visited[i][j] = false;
        }
    }
    return hpath;
}
//4.机器人的运动范围
int travelpoint(int m,int n,int k)
{
    if(m<1 || n<1)
        return 0;
    bool** visited = new bool*[m];
    for(int i = 0;i<m;i++){
        visited[i] = new bool[n];
    }
    for(int i = 0;i<m;i++){
        for(int j = 0;j<n;j++){
            visited[i][j] = false;
        }
    }
    int ret = travelprocess(m,n,k,0,0,visited);
    for(int i =  0;i<m;i++){
        delete[] visited[i];
    }
    delete[] visited;
    return ret;
}
int travelprocess(int m,int n,int k,int i,int j,bool** visited)
{
    int pathtravel = 0;
    if(i >= 0 && i<m && j >= 0 && j<n && !visited[i][j]){
        int sum = 0;
        int k = i;
        int h = j;
        while(k >= 10){
            int temp = i%10;
            sum += temp;
            k = k/10;
        }
        sum += k;
        while(h>=10){
            int temp = h%10;
            sum+=temp;
            h = h/10;
        }
        sum += h;
        if(sum <= k){
            visited[i][j] = true;
            pathtravel = 1+ travelprocess(m,n,k,i,j-1,visited) + travelprocess(m,n,k,i,j+1,visited)+travelprocess(m,n,k,i-1,j,visited) + travelprocess(m,n,k,i+1,j,visited);
        }
    }
    return pathtravel;
}
//5.剪绳子
//递归
int getmainmaxplus(int n){
    if(n <= 1)
        return 0;
    if(n == 2)
        return 1;
    if(n == 3)
        return 2;
    if(n == 4)
        return 4;
    return getmaxplussum(n);
}
int getmaxplussum(int n)
{
    if(n == 2){
        return 2;
    }
    if(n == 3){
        return 3;
    }
    return 3*getmaxplussum(n-3);
}
//动态规划
int dpgetmaxplussum(int n)
{
    if(n <= 1){
        return 0;
    }
    if(n == 2){
        return 1;
    }
    if(n == 3){
        return 2;
    }
    if(n == 4){
        return 4;
    }
    vector<int> dp;
    dp.resize(n+1);
    for(int i = 0;i<=4;i++){
        dp[i] = i;
    }
    for(int i = 5;i<=n;i++){
        dp[i] = 3*dp[i-3];
    }
    return dp[n];
}
//6.二进制中1的个数
int numberof1(int n)
{
    int count = 0;
    while(n){
        ++count;
        n = (n-1)&n;
    }
    return count;
}
int mysolution(int n){
    bool isfu = false;
    if(n < 0){
        isfu = true;
        n = n & 0x7fffffff;
    }
    int count = 0;
    while(n){
        if((n & 0x1) == 1){
            count++;
        }
        n = n>>1;
    }
    if(isfu){
        count++;
    }
    return count;
}
//7.数值的整数次方
double Power(double base,int exponent)
{
    if(base == 0){
        return 0;
    }
    stack<int> bitcount;
    bool isfu = false;
    if(exponent < 0){
        exponent = -exponent;
        isfu = true;
    }
    while(exponent){
        if((exponent & 0x1) == 1)
            bitcount.push(1);
        else{
            bitcount.push(0);
        }
        exponent = exponent>>1;
    }
    double plussum = 1;
    double temp = base;
    while(!bitcount.empty()){
        if(bitcount.top() == 1){
            plussum = plussum * temp;
        }
        temp = temp*temp;
        bitcount.pop();
    }
    if(isfu){
        plussum = 1/plussum;
    }
    return plussum;
}
//8.打印从1到最大的n位数
void printmaxbitnumber(int n)
{
    long long maxval = 0;
    while(n>0){
        maxval = maxval*10 + 9;
        n--;
    }
    long long i = 1;
    while(i<=maxval){
        cout<<i++<<" ";
    }
    cout<<endl;
}
void pribnt1tomaxofndigits(int n)
{
    if(n <= 0){
        return;
    }
    char* number  = new char[n+1];
    number[n] = '\0';
    for(int i = 0;i<10;++i){
        number[0] = i+'0';
        print1tomaxofndigitsrecursively(number, n, 0);
    }
    delete[] number;
}
void print1tomaxofndigitsrecursively(char* number,int length,int index)
{
    if(index == length - 1){
        printnumber(number);
        return;
    }
    for(int i = 0;i<10;++i){
        number[index+1] = i+'0';
        print1tomaxofndigitsrecursively(number, length, index+1);
    }
}
void printnumber(char* number)
{
    bool isbeginning0 = true;
    int nlength = (int)strlen(number);
    for(int i = 0;i<nlength;++i){
        if(isbeginning0 && number[i] != '0')
            isbeginning0 = false;
        if(!isbeginning0){
            cout<<number[i];
        }
    }
    cout<<" ";
}
//9.实现任意两个整数的加法
void randomsum(int a,int b)
{
    vector<char> achar;
    vector<char> bchar,sumchar;
    while(a){
        achar.push_back(a%10+'0');
        a = a/10;
    }
    while(b){
        bchar.push_back(b%10+'0');
        b = b/10;
    }
    sumchar.resize(max((int)achar.size(),(int)bchar.size())+1);
    for(int i = 0;i<sumchar.size();i++){
        sumchar[i] = '0';
    }
    int i = 0;
    int j = 0;
    int k = 0;
    while(i<achar.size() && j<bchar.size()){
        if(sumchar[k] - '0' + achar[i] - '0' + bchar[j] - '0' > 9){
            sumchar[k] += achar[i++] - '0'+bchar[j++]- '0' - 10;
            k++;
            sumchar[k]+=1;
        }else{
            sumchar[k] += achar[i++]-'0'+bchar[j++]-'0';
            k++;
        }
    }
    while(i<achar.size()){
        sumchar[k++] += achar[i++] - '0';
    }
    while(j<bchar.size()){
        sumchar[k++] += bchar[j++] - '0';
    }
    int len = (int)sumchar.size()-1;
    if(sumchar[len] == '0')
        --len;
    while(len>=0){
        cout<<sumchar[len--];
    }
    cout<<endl;
}
//10.删除链表节点
void deletenode(ListNode* head,ListNode* ptr)
{
    if(head == NULL)
        return;
    if(ptr == head){
        head = head->next;
        delete ptr;
        return;
    }
    if(ptr == NULL){
        return;
    }
    ptr->val = ptr->next->val;
    ptr->next = ptr->next->next;
    delete ptr->next;
    return;
}
//11.删除重复的节点
void repeatnode(ListNode* head)
{
    if(head == NULL)
        return;
    ListNode* cur = head;
    ListNode* help = NULL;
    while(cur != NULL){
        if(cur->next != NULL && cur->val == cur->next->val){
            help = cur->next;
            cur->next = cur->next->next;
            delete help;
        }else{
            cur = cur->next;
        }
    }
}
//13.表示数值的字符串
//递归版
bool scanunsignedint(const char** str)
{
    const char* before = *str;
    while(**str != '\0' && **str >= '0' && **str <= '9'){
        ++(*str);
    }
    return *str>before;
}
bool isnumber(const char* str)
{
    if(str == NULL)
        return false;
    bool numeric = scanint(&str);
    if(*str == '.'){
        ++str;
        numeric = scanunsignedint(&str) || numeric;
        
    }
    if(*str == 'e' || *str == 'E'){
        ++str;
        numeric = numeric && scanint(&str);
    }
    return numeric && *str == '\0';
}
bool scanint(const char** str)
{
    if(**str == '+' || **str == '-')
        ++(*str);
    return scanunsignedint(str);
}
//14.调整数组顺序使奇数位于偶数前面
void resortoddvector(vector<int>& nums)
{
    if(nums.empty() || nums.size() == 1)
        return;
    int l = 0;
    int more = (int)nums.size()-1;
    int less  = -1;
    while(l<more){
        if(nums[l]%2==1){
            swap(nums[++less],nums[l++]);
        }
        else if(nums[l]%2 == 0){
            swap(nums[more--],nums[l]);
        }
    }
    return;
}
//附加，调整数组的顺序使负数在前，整数在后
void resortzhengfuvector(vector<int>& nums)
{
    if(nums.empty() || nums.size() == 1)
        return;
    int l = 0;
    int more = (int)nums.size()-1;
    int less  = -1;
    while(l<more){
        if(nums[l]<0){
            swap(nums[++less],nums[l++]);
        }
        else if(nums[l]>0){
            swap(nums[more--],nums[l]);
        }
        else{
            l++;
        }
    }
    return;
}
//15.链表中倒数第k个节点
ListNode* kpointoflist(ListNode* head,int k)
{
    if(head == NULL || k == 0)
        return NULL;
    ListNode* cur = head;
    vector<ListNode*> listlinked;
    while(cur != NULL){
        listlinked.push_back(cur);
        cur = cur->next;
    }
    if(k>listlinked.size()){
        return NULL;
    }
    return listlinked[(int)listlinked.size()-k];
}
//双指针法，一个指针先走k-1步，到达k时，第二个指针开始从头走，当第一个指针走到空时，第二个指针走到倒数第k个节点
ListNode* ktwoptrlistlinked(ListNode* head,int k)
{
    if(head == NULL || k ==0 )
        return NULL;
    ListNode* cur = head;
    ListNode* backptr = head;
    for(int i = 0;i<k-1;i++){
        if(cur->next != NULL)
            cur = cur->next;
        else{
            return NULL;
        }
    }
    while(cur->next != NULL){
        cur = cur->next;
        backptr = backptr->next;
    }
    return backptr;
}
//16.链表中环的入口节点
ListNode* incyclelistlinked(ListNode* head)
{
    if(head == NULL || head->next == NULL || head->next->next == NULL)
        return NULL;
    ListNode* fast = head->next->next;
    ListNode* slow = head->next;
    while(slow != fast){
        if(fast->next == NULL || fast->next->next == NULL || slow->next == NULL || fast == NULL || slow == NULL){
            return NULL;
        }
        fast = fast->next->next;
        slow = slow->next;
    }
    fast = head;
    while(slow != fast){
        slow = slow->next;
        fast = fast->next;
    }
    return fast;
}
//17.反转链表
ListNode* reverselistlinked(ListNode* head)
{
    if(head == NULL){
        return NULL;
    }
    ListNode* cur = head;
    ListNode* help = NULL;
    ListNode* next = NULL;
    while(cur != NULL){
        next = cur->next;
        cur->next = help;
        help = cur;
        cur = next;
    }
    return help;
}
//进阶题，反转从位置 m 到 n 的链表。请使用一趟扫描完成反转
ListNode* reverseBetween(ListNode* head, int m, int n)
{
    if(head == NULL){
        return NULL;
    }
    if(m >= n || m <= 0){
        return head;
    }
    ListNode* cur = head;
    ListNode* help = NULL;
    ListNode* tail1 = NULL;
    int j = m-1;
    for(int i = 1;i<=m-1;i++){
        if(cur->next == NULL)
            return head;
        tail1 = cur;
        cur = cur->next;
    }
    ListNode* tail2 = cur;
    ListNode* next = NULL;
    while(cur != NULL && j<n){
        next = cur->next;
        cur->next = help;
        help = cur;
        cur = next;
        j++;
    }
    if(cur == NULL){
        if(tail1 == NULL){
            return help;
        }else{
            tail1->next = help;
            tail2->next = NULL;
        }
    }else{
        if(tail1 == NULL){
            tail2->next = cur;
            return help;
        }else{
            tail1->next = help;
            tail2->next = cur;
        }
    }
    return head;
}
//18.合并两个排序的链表
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
    if(l1 == NULL)
        return l2;
    if(l2 == NULL)
        return l1;
    ListNode* cur1 = l1;
    ListNode* cur2 = l2;
    ListNode* head = NULL;
    if(cur1->val < cur2->val){
        head = l1;
        cur1 = cur1->next;
    }else{
        head = l2;
        cur2 = cur2->next;
    }
    ListNode* ptr = head;
    while(cur1 != NULL && cur2 != NULL){
        if(cur1->val < cur2->val){
            ptr->next = cur1;
            cur1 = cur1->next;
        }
        else{
            ptr->next = cur2;
            cur2 = cur2->next;
        }
        ptr = ptr->next;
    }
    while(cur1 != NULL){
        ptr->next = cur1;
        cur1 = cur1->next;
        ptr = ptr->next;
    }
    while(cur2 != NULL){
        ptr->next = cur2;
        cur2 = cur2->next;
        ptr = ptr->next;
    }
    ptr->next = NULL;
    return head;
}
//19.判断二叉树s中是否有与二叉树t拓扑结构相同的子树
//递归
bool isheadequaltree(TreeNode* s,TreeNode* t)
{
    bool result = false;
    if(s != NULL && t != NULL){
        result = isleftrightequaltree(s,t);
        if(!result){
            result = isheadequaltree(s->left,t);
        }
        if(!result){
            result = isheadequaltree(s->right,t);
        }
    }
    return result;
}
bool isleftrightequaltree(TreeNode* root1,TreeNode* root2)
{
    if(root2 == NULL && root1 == NULL){
        return true;
    }
    else if(root1 == NULL || root2 == NULL){
        return false;
    }
    if(!isequalval(root1,root2)){
        return false;
    }
    return isleftrightequaltree(root1->left,root2->left) && isleftrightequaltree(root1->right,root2->right);
}
bool isequalval(TreeNode* ptr1,TreeNode* ptr2)
{
    if((ptr1->val - ptr2->val > -0.000001) && (ptr1->val - ptr2->val < 0.000001)){
        return true;
    }
    return false;
}
//20.二叉树的镜像
TreeNode* mirrortree(TreeNode* root)
{
    if(root == NULL)
        return NULL;
    queue<TreeNode*> treelevel;
    TreeNode* help = NULL;
    TreeNode* cur = NULL;
    treelevel.push(root);
    while(!treelevel.empty()){
        cur = treelevel.front();
        treelevel.pop();
        help = cur->left;
        cur->left = cur->right;
        cur->right = help;
        if(cur->left != NULL){
            treelevel.push(cur->left);
        }
        if(cur->right != NULL){
            treelevel.push(cur->right);
        }
    }
    return root;
}
void printtreepre(TreeNode* root)
{
    if(root == NULL){
        return;
    }
    printtreepre(root->left);
    cout<<root->val<<" ";
    printtreepre(root->right);
}
//21.对称的二叉树
//一般的递归打印二叉树
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
bool isSymmetricaltree(TreeNode* root)
{
    if(root == NULL)
        return true;
    queue<TreeNode*> treelevel;
    string stroldpre,stroldin;
    string strnewpre,strnewin;
    printPretra(root, stroldpre);
    printIntra(root, stroldin);
    TreeNode* cur = root;
    TreeNode* help = NULL;
    treelevel.push(root);
    while(!treelevel.empty()){
        cur = treelevel.front();
        treelevel.pop();
        help = cur->left;
        cur->left = cur->right;
        cur->right = help;
        if(cur->left != NULL){
            treelevel.push(cur->left);
        }
        if(cur->right != NULL){
            treelevel.push(cur->right);
        }
    }
    printPretra(root, strnewpre);
    printIntra(root, strnewin);
    if(stroldpre == strnewpre && stroldin == strnewin)
        return true;
    return false;
}
//递归版
bool issymmetricaltreenode(TreeNode* root)
{
    if(root == NULL)
        return true;
    return processsymmetricaltree(root, root);
}
bool processsymmetricaltree(TreeNode* root1,TreeNode* root2)
{
    if(root1 == NULL && root2 == NULL)
        return true;
    if(root1 == NULL)
        return false;
    if(root2 == NULL)
        return false;
    if(root1->val != root2->val)
        return false;
    return processsymmetricaltree(root1->left, root2->right) && processsymmetricaltree(root1->right,root2->left);
}
//22.顺时针打印矩阵
void processclockwiseprint(vector<vector<int> >& matrix,int row1,int col1,int row2,int col2)
{
    if(row1 == row2 && col1 == col2){
        cout<<matrix[row1][col1]<<endl;
        return;
    }
    if(row1 > row2)
        return;
    if(col1>col2)
        return;
    if(row1 == row2){
        while(col1 != col2){
            cout<<matrix[row1][col1++]<<" ";
        }
        processclockwiseprint(matrix,row1,col1,row2,col2);
    }
    if(col1 == col2){
        while(row1 != row2){
            cout<<matrix[row1++][col1]<<" ";
        }
        processclockwiseprint(matrix,row1,col1,row2,col2);
    }
    int i = row1;
    int j = col1;
    while(j!=col2){
        cout<<matrix[i][j++]<<" ";
    }
    while(i!=row2){
        cout<<matrix[i++][j]<<" ";
    }
    while(j!=col1){
        cout<<matrix[i][j--]<<" ";
    }
    while(i!=row1){
        cout<<matrix[i--][j]<<" ";
    }
    processclockwiseprint(matrix,row1+1,col1+1,row2-1,col2-1);
}
//24.栈的压入和弹出序列
bool ispushpopindex(vector<int>& pushed,vector<int>& popped)
{
    if(pushed.size() != popped.size()){
        return false;
    }
    if(pushed.empty() && popped.empty())
        return true;
    stack<int> pushstack;
    int i = 0;
    int j = 0;
    while(pushed[i] != popped[j]){
        pushstack.push(pushed[i++]);
    }
    i++;
    j++;
    while(i <= pushed.size() && j < popped.size()){
        if(!pushstack.empty() && pushstack.top() == popped[j]){
            pushstack.pop();
            j++;
        }else{
            if(i < pushed.size() && j < popped.size() && pushed[i] != popped[j]){
                pushstack.push(pushed[i++]);
            }else if(i < pushed.size() && j < popped.size() && pushed[i] == popped[j]){
                i++;
                j++;
            }else{
                return false;
            }
        }
    }
    if(i == j && i == pushed.size() && pushstack.empty())
        return true;
    else
        return false;
}
//25.从上到下打印二叉树
void fromtoptobottomprinttree(TreeNode* root)
{
    queue<TreeNode*> floortree;
    TreeNode* cur = NULL;
    floortree.push(root);
    while(!floortree.empty()){
        cur = floortree.front();
        floortree.pop();
        cout<<cur->val<<" ";
        if(cur->left != NULL){
            floortree.push(cur->left);
        }
        if(cur->right != NULL){
            floortree.push(cur->right);
        }
    }
    return;
}
//26.分行从上到下打印二叉树
void detectfloortoptobottomtreeprint(TreeNode* root)
{
    if(root == NULL)
        return;
    queue<TreeNode*> floortree;
    TreeNode* cur = NULL;
    TreeNode* last = NULL;
    floortree.push(root);
    while(!floortree.empty()){
        cur = floortree.front();
        floortree.pop();
        cout<<cur->val<<" ";
        if(last == NULL || last->right == cur){
            cout<<endl;
            last = cur;
        }
        if(cur->left != NULL){
            floortree.push(cur->left);
        }
        if(cur->right != NULL){
            floortree.push(cur->right);
        }
    }
    return;
}
//27.之字形打印二叉树
void zhiwordprinttree(TreeNode* root)
{
    if(root == NULL)
        return;
    stack<TreeNode*> wstack[2];
    TreeNode* cur = NULL;
    int current = 0;
    int next = 1;
    wstack[current].push(root);
    while(!wstack[0].empty() || !wstack[1].empty()){
        cur = wstack[current].top();
        wstack[current].pop();
        cout<<cur->val<<" ";
        if(current == 0){
            if(cur->left != NULL){
                wstack[next].push(cur->left);
            }
            if(cur->right != NULL){
                wstack[next].push(cur->right);
            }
        }else{
            if(cur->right != NULL){
                wstack[next].push(cur->right);
            }
            if(cur->left != NULL){
                wstack[next].push(cur->left);
            }
        }
        if(wstack[current].empty()){
            cout<<endl;
            current = 1-current;
            next = 1-next;
        }
    }
    
}
//28.二叉树的后序遍历序列
bool isafttraveltree(TreeNode* root,vector<int>& nums)
{
    if(NULL == root && nums.empty()){
        return true;
    }
    if(root == NULL)
        return false;
    if(nums.empty())
        return true;
    vector<int> fullnums;
    afttraveltreeprocess(root,fullnums);
    int i = 0;
    int j = 0;
    while(i < fullnums.size() && fullnums[i] != nums[j]){
        i++;
    }
    while(i<fullnums.size() && j<nums.size()){
        if(fullnums[i] != nums[j])
            return false;
        i++;
        j++;
    }
    return true;
}
void afttraveltreeprocess(TreeNode* root,vector<int>& nums)
{
    if(root == NULL)
        return ;
    afttraveltreeprocess(root->left,nums);
    afttraveltreeprocess(root->right,nums);
    nums.push_back(root->val);
    return;
}
//29.二叉树中和为某一值的路径
void printpathsum(TreeNode* root,int val)
{
    if(root == NULL)
        return;
    vector<int> nums;
    processpathsum(root,val,nums,0);
}
void processpathsum(TreeNode* root,int val,vector<int>& nums,int sum)
{
    if(val == sum){
        for(int i = 0;i<nums.size();i++){
            cout<<nums[i]<<" ";
        }
        cout<<endl;
    }
    if(root == NULL){
        return;
    }
    nums.push_back(root->val);
    processpathsum(root->left,val,nums,sum+root->val);
    processpathsum(root->right,val,nums,sum+root->val);
    nums.pop_back();
    return;
}
//30.二叉搜索树与双向链表,中序遍历
TreeNode* binarysearchtreetolist(TreeNode* root)
{
    if(root == NULL){
        return NULL;
    }
    stack<TreeNode*> Intravel;
    vector<TreeNode*> Innums;
    TreeNode* cur = root->left;
    Intravel.push(root);
    while(!Intravel.empty()){
        while(cur != NULL){
            Intravel.push(cur);
            cur = cur->left;
        }
        TreeNode* help = Intravel.top();
        Intravel.pop();
        Innums.push_back(help);
        cur = help->right;
        if(cur == root->right)
        {
            Intravel.push(cur);
            cur = cur->left;
        }
    }
    if(Innums.size() < 2)
        return Innums[0];
    Innums[0]->right = Innums[1];
    int i = 1;
    for(;i<Innums.size()-1;i++){
        Innums[i]->left = Innums[i-1];
        Innums[i]->right = Innums[i+1];
    }
    Innums[i]->left = Innums[i-1];
    return Innums[0];
}
TreeNode* testconvert(TreeNode* root)
{
    if(root == NULL){
        return NULL;
    }
    stack<TreeNode*> Intravel;
    bool ishead = true;
    TreeNode* head = NULL;
    TreeNode* cur = root->left;
    TreeNode* help = NULL;
    Intravel.push(root);
    while(!Intravel.empty()){
        while(cur != NULL){
            Intravel.push(cur);
            cur = cur->left;
        }
        if(help != NULL){
            help->right = Intravel.top();
        }
        if(Intravel.top() == root){
            root->left = help;
        }
        help = Intravel.top();
        Intravel.pop();
        if(ishead){
            head = help;
            ishead = false;
        }
        cur = help->right;
        if(cur == root->right)
        {
            Intravel.push(cur);
            cur = cur->left;
        }
    }
    return head;
}
//31.数组中出现次数超过一半的数字
int getmaxindexoccurnums(vector<int>& nums)
{
    if(nums.empty())
        return -1;
    unordered_map<int,int> recordtimes;
    unordered_map<int,int>::iterator findit;
    for(int i = 0;i<nums.size();i++){
        findit = recordtimes.find(nums[i]);
        if(findit == recordtimes.end()){
            recordtimes.insert(make_pair(nums[i],1));
        }else{
            findit->second++;
        }
    }
    unordered_map<int,int>::iterator recordbegin = recordtimes.begin();
    int maxval = 0;
    int maxtimes = 0;
    while(recordbegin != recordtimes.end()){
        if(maxtimes < recordbegin->second){
            maxtimes = recordbegin->second;
            maxval = recordbegin->first;
        }
        recordbegin++;
    }
    if(maxtimes > (nums.size() - 1)/2)
        return maxval;
    else
        return -1;
}
//再用桶排序来解决
int getmorethanhalfofnums(vector<int>& nums)
{
    if(nums.empty())
        return -1;
    int maxval = 0;
    for(int i = 0;i<nums.size();i++){
        if(maxval < nums[i]){
            maxval = nums[i];
        }
    }
    vector<int> buket;
    buket.resize(maxval+1);
    for(int i = 0;i<nums.size();i++){
        buket[nums[i]]++;
    }
    maxval = 0;
    int maxtimes = 0;
    for(int i = 0;i<buket.size();i++){
        if(maxtimes < buket[i]){
            maxtimes = buket[i];
            maxval = i;
        }
    }
    if(maxtimes > (nums.size() - 1)/2)
        return maxval;
    else
        return -1;
}
//32.最小的k个数
vector<int> minknumber(vector<int>& nums,int k)
{
    vector<int> knumbers;
    if(nums.empty())
        return knumbers;
    if(k == 0)
        return knumbers;
    int maxval = 0;
    for(int i = 0;i<nums.size();i++){
        if(maxval < nums[i]){
            maxval = nums[i];
        }
    }
    vector<int> buket;
    buket.resize(maxval+1);
    for(int i = 0;i<nums.size();i++){
        buket[nums[i]]++;
    }
    for(int i = 0;i<buket.size();i++){
        if(knumbers.size() == k)
            break;
        if(buket[i] > 0){
            knumbers.push_back(i);
        }
    }
    return knumbers;
}
//partion解法
vector<int> minknumbersofpartition(vector<int>& nums,int k)
{
    vector<int> knumbers;
    if(nums.empty())
        return knumbers;
    int start = 0;
    int end = (int)nums.size()-1;
    int index = mypartition(nums,nums[k-1],start,end);
    while(index != k-1){
        if(index > k-1){
            end = index-1;
            index = mypartition(nums,nums[k-1],start,end);
        }
        else{
            start = index + 1;
            index = mypartition(nums,nums[k-1],start,end);
        }
    }
    for(int i = 0;i<k;i++){
        knumbers.push_back(nums[i]);
    }
    return knumbers;
}
int mypartition(vector<int>& nums,int mid,int start,int end)
{
    int less = start-1;
    int more = end;
    int cur = 0;
    while(cur<more){
        if(nums[cur] < mid){
            swap(nums[++less],nums[cur++]);
        }
        else if(nums[cur] == mid){
            cur++;
        }
        else{
            swap(nums[--more],nums[cur]);
        }
    }
    return less+1;
}
//红黑树解法,适合大数据相关的题
vector<int> getlestnumbers(vector<int>& nums,int k)
{
    vector<int> ret;
    if(k < 1 || nums.size() < k)
        return ret;
    multiset<int,greater<int>> knumbers;
    multiset<int,greater<int>>::iterator kbegin;
    for(int i = 0;i<nums.size();i++){
        if(knumbers.size() < k){
            knumbers.insert(nums[i]);
        }else{
            kbegin = knumbers.begin();
            if(nums[i] < *knumbers.begin()){
                knumbers.erase(kbegin);
                knumbers.insert(nums[i]);
            }
        }
    }
    ret.resize(k);
    k--;
    kbegin = knumbers.begin();
    while(kbegin != knumbers.end() && k >= 0){
        ret[k--] = *kbegin;
        ++kbegin;
    }
    return ret;
}
//33.连续子数组的最大和
//O(n)时间复杂度的解法
int getmaxsumfortimen(vector<int>& nums)
{
    if(nums.empty()){
        return 0;
    }
    int ncursum = 0;
    int ncreatestsum = 0;
    for(int i = 0;i<nums.size();i++){
        if(ncursum <= 0)
            ncursum = nums[i];
        else
            ncursum += nums[i];
        if(ncursum> ncreatestsum){
            ncreatestsum = ncursum;
        }
    }
    return ncreatestsum;
}
//动态规划
int dpgetmaxsumfortimen(vector<int>& nums)
{
    if(nums.empty())
        return 0;
    vector<int> dp;
    dp.resize(nums.size());
    dp[0] = nums[0];
    for(int i = 1;i<nums.size();i++){
        if(dp[i-1] <= 0)
            dp[i] = nums[i];
        else
            dp[i] = dp[i-1]+nums[i];
    }
    return dp[nums.size()-1];
}
//34.1~n整数中1出现的次数
long getcount1(int n)
{
    int i = 1;
    long count = 0;
    while(i <= n){
        count += numberprocess(i);
        i++;
    }
    return count;
}
int numberprocess(int i)
{
    int count1 = 0;
    while(i>0){
        if(i%10 == 1)
            count1++;
        i = i/10;
    }
    return count1;
}
//O(log(N))解法
int countDigitOne(int n) {
    int count = 0;
    for (long long i = 1; i <= n; i *= 10) {
        long long divider = i * 10;
        count += (n / divider) * i + min(max(n % divider - i + 1, 0LL), i);
    }
    return count;
    
    }
//35.数字序列中某一位的数字
int digitindex(int index)
{
    if(index < 0)
        return -1;
    int digits = 1;
    while(true){
        int numbers = countofintergers(digits);
        if(index < numbers*digits)
            return digitatindex(index,digits);
        index -= digits * numbers;
        digits++;
    }
    return -1;
}
int countofintergers(int digits)
{
    if(digits == 1)
        return 10;
    int count = (int)pow(10,digits-1);
    return 9*count;
}
int digitatindex(int index,int digits)
{
    int number = beginnumber(digits) + index/digits;
    int indexfromright = digits - index % digits;
    for(int i = 1;i<indexfromright;i++)
        number /=10;
    return number % 10;
}
int beginnumber(int digits)
{
    if(digits == 1)
        return 0;
    return (int)pow(10, digits-1);
}
//36.把数组排成最小的数
//整一个全排列，然后转成字符串比较大小，找出最小的
string processfullsort(vector<int>& nums,int i)
{
    if(i == nums.size()){
        string ret;
        ret.clear();
        for(int j = 0;j<nums.size();j++){
            ret += to_string(nums[j]);
        }
        return ret;
    }
    string back;
    string minback;
    for(int j = i;j<nums.size();j++){
        swap(nums[i],nums[j]);
        back = processfullsort(nums, i+1);
        if(minback.empty()){
            minback = back;
        }
        else if(minback > back){
            minback = back;
        }
        swap(nums[i],nums[j]);
    }
    return minback;
}
//直接转成字符串然后两两比较排列的大小
string minarrangementarray(vector<int>& nums)
{
    string minarrange;
    if(nums.empty())
        return minarrange;
    minarrange = to_string(nums[0]);
    int i = 1;
    while(i<nums.size()){
        string t1 = to_string(nums[i++]);
        if(t1+minarrange < minarrange+t1){
            minarrange = t1 + minarrange;
        }else{
            minarrange = minarrange+t1;
        }
    }
    return minarrange;
}
//37.把数字翻译成字符串
int GettranslationCount(int number)
{
    if(number == 0){
        return 0;
    }
    if(number < 0)
    {
        number = -number;
    }
    string str = to_string(number);
    return numberstostring(str, 0);
}
int numberstostring(string& str,int i)
{
    if(i >= str.size()){
        return 1;
    }
    int twonumbers = 0,onenumbers = 0;
    onenumbers = numberstostring(str, i+1);
    if(i+1 < str.size() && (str[i]-'0') * 10 + str[i+1]-'0' <= 25){
        twonumbers = numberstostring(str, i+2);
    }
    return twonumbers+onenumbers;
}
//进阶版解法，
int gettranlationcount(int number)
{
    if(number<0)
        return 0;
    string numberinstring = to_string(number);
    return gettranslationprocess(numberinstring);
}
int gettranslationprocess(const string& number)
{
    int length = (int)number.size();
    vector<int> counts(0,length);
    counts.resize(length);
    int count = 0;
    for(int i = length-1;i>=0;i--){
        count = 0;
        if(i<length-1)
            count = counts[i+1];
        else
            count = 1;
        if(i<length-1){
            int digt1 = number[i]-'0';
            int digt2 = number[i+1] - '0';
            int converted = digt1*10 + digt2;
            if(converted >= 10 && converted <= 25){
                if(i<length-2)
                    count += counts[i+2];
                else
                    count += 1;
            }
        }
        counts[i] = count;
    }
    count = counts[0];
    return count;
}
//38.礼物的最大价值,典型的动态规划问题
int getmaxvalueofgifts(vector<vector<int>>& matrix)
{
    if(matrix.empty()){
        return 0;
    }
    int** dp = new int*[matrix.size()];
    for(int i = 0;i<matrix.size();i++){
        dp[i] = new int[matrix[0].size()];
    }
    dp[0][0] = matrix[0][0];
    for(int i = 1;i<matrix.size();i++){
        dp[i][0] = matrix[i][0]+dp[i-1][0];
    }
    for(int j = 1;j<matrix[0].size();j++){
        dp[0][j] = matrix[0][j] + dp[0][j-1];
    }
    for(int i = 1;i<matrix.size();i++){
        for(int j = 1;j<matrix[0].size();j++){
            dp[i][j] = max(dp[i-1][j],dp[i][j-1])+matrix[i][j];
        }
    }
    int ret = dp[matrix.size()-1][matrix[0].size()-1];
    for(int i = 0;i<matrix.size();i++){
        delete[] dp[i];
    }
    delete[] dp;
    return ret;
}
//39.丑数
int getgivenindexuglynumber(int index)
{
    if(index <= 0)
        return 0;
    int number = 0;
    int uglyfind = 0;
    while(uglyfind <index){
        ++number;
        if(isuglynumber(number)){
            ++uglyfind;
        }
    }
    return number;
}
bool isuglynumber(int number)
{
    while(number % 2 == 0)
        number /= 2;
    while(number % 3 == 0)
        number /= 3;
    while(number % 5 == 0)
        number /= 5;
    return (number == 1)?true:false;
}
//以空间换时间
int costspacefortimegetuglynumber(int n)
{
    if(n < 0)
        return 0;
    int *puglynumber = new int[n];
    puglynumber[0] = 1;
    int nextuglyindex = 1;
    int * pmultiply2 = puglynumber;
    int * pmultiply3 = puglynumber;
    int * pmultiply5 = puglynumber;
    while(nextuglyindex < n){
        int minval = min(*pmultiply2*2,min(*pmultiply3*3,*pmultiply5*5));
        puglynumber[nextuglyindex] = minval;
        while(*pmultiply2*2 <= puglynumber[nextuglyindex])
            ++pmultiply2;
        while(*pmultiply3*3 <= puglynumber[nextuglyindex])
            ++pmultiply3;
        while(*pmultiply5*5 <= puglynumber[nextuglyindex])
            ++pmultiply5;
        ++nextuglyindex;
    }
    int ugly = puglynumber[nextuglyindex-1];
    delete[] puglynumber;
    return ugly;
}
//40.第一个只出现一次的字符
char getfirstshowchar(string& str)
{
    if(str.empty())
        return NULL;
    unordered_map<char,int> recordcount;
    unordered_map<char,int>::iterator it;
    for(int i = 0;i<str.size();i++)
    {
        it = recordcount.find(str[i]);
        if(it != recordcount.end()){
            it->second++;
        }
        else {
            recordcount.insert(make_pair(str[i],1));
        }
    }
    for(int i = 0;i<str.size();i++){
        it = recordcount.find(str[i]);
        if(it != recordcount.end() && it->second == 1)
            return str[i];
    }
    return NULL;
}
//附加题1.定义一个函数，输入两个字符，从第一个字符串中删除在第二个字符串中出现过的所有字符串
void deletecharshowinstr2(string& str1,string str2)
{
    if(str1.empty() || str2.empty())
        return;
    unordered_set<char> recordchar;
    unordered_set<char>::iterator it;
    for(int i = 0;i<str2.size();i++){
        it = recordchar.find(str2[i]);
        if(it == recordchar.end()){
            recordchar.insert(str2[i]);
        }
    }
    string::iterator strit = str1.begin();
    while(strit != str1.end()){
        it = recordchar.find(*strit);
        if(it != recordchar.end()){
            strit = str1.erase(strit);
        }else{
            ++strit;
        }
    }
    return;
}
//附加题2.定义一个函数，删除字符串中所有重复出现的字符
void deletereshowchar(string& str)
{
    if(str.empty())
        return;
    unordered_set<char> recordchar;
    unordered_set<char>::iterator it;
    string::iterator strit = str.begin();
    while(strit != str.end()){
        it = recordchar.find(*strit);
        if(it != recordchar.end()){
            strit = str.erase(strit);
        }else{
            recordchar.insert(*strit);
            ++strit;
        }
    }
    return;
}
//附加题3.判断输入的两个字符串是不是互为变位词
bool isuniquebitstring(string& s,string t)
{
    if((s.empty() && !t.empty()) || (t.empty() && ! s.empty()) || (s.size() != t.size()))
        return false;
    if(s.empty() && t.empty())
        return true;
    unordered_map<char,int> recordcount;
    unordered_map<char,int>::iterator it;
    int len = (int)s.size();
    for(int i = 0;i<len;i++){
        it = recordcount.find(s[i]);
        if(it != recordcount.end()){
            it->second++;
        }else{
            recordcount.insert(make_pair(s[i],1));
        }
    }
    for(int i = 0;i<len;i++){
        it = recordcount.find(t[i]);
        if(it != recordcount.end()){
            it->second--;
            if(it->second == 0)
                recordcount.erase(it);
            if(it->second < 0)
                return false;
        }
    }
    if(recordcount.empty())
        return true;
    else
        return false;
}
//41.字符流中第一个只出现一次的字符
char charstreamfirstshowchar()
{
    string temp;
    cin>>temp;
    unordered_map<char,int> recorddata;
    unordered_map<char,int>::iterator it;
    for(int i = 0;i<temp.size();i++){
        it = recorddata.find(temp[i]);
        if(it != recorddata.end()){
            it->second++;
        }else{
            recorddata.insert(make_pair(temp[i],1));
        }
    }
    for(int i = 0;i<temp.size();i++){
        it = recorddata.find(temp[i]);
        if(it != recorddata.end()){
            if(it->second == 1)
                return it->first;
        }
    }
    return NULL;
}
//42.数组中的逆序对
//O(N*N)
int inverseindexqueue(vector<int>& nums)
{
    if(nums.empty() || nums.size() < 2){
        return 0;
    }
    int suminversecount = 0;
    for(int i = 0;i<nums.size();i++){
        for(int j = i+1;j<nums.size();j++){
            if(nums[i]>nums[j])
                ++suminversecount;
        }
    }
    return suminversecount;
}
//利用归并排序的思想
int inverseindexprocess(vector<int>& arr,int l,int r)
{
    if(l == r){
        return 0;
    }
    int mid = l + (r-l-1)/2;
    return inverseindexprocess(arr,l,mid)+inverseindexprocess(arr,mid+1,r)+inverindexmerge(arr,l,mid,r);

}
int inverindexmerge(vector<int>& arr,int l,int mid,int r)
{
    vector<int> help;
    help.resize(r-l+1);
    int p1 = l;
    int p2 = mid+1;
    int i = 0;
    int count = 0;
    while(p1<=mid && p2 <= r){
        count += arr[p1]<=arr[p2] ? 0 : (mid-p1+1);
        help[i++] = arr[p1]<=arr[p2]?arr[p1++]:arr[p2++];
    }
    while(p1<=mid){
        help[i++] = arr[p1++];
    }
    while(p2<=r){
        help[i++] = arr[p2++];
    }
    for(int j = 0;j<help.size();j++){
        arr[l+j] = help[j];
    }
    return count;
}
//43.两个链表的第一个公共节点
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    if(headA == NULL || headB == NULL)
        return NULL;
    int lenA = 0;
    int lenB = 0;
    ListNode* ptrA = headA;
    ListNode* ptrB = headB;
    while(ptrA != NULL){
        ++lenA;
        ptrA = ptrA->next;
    }
    while(ptrB != NULL){
        ++lenB;
        ptrB = ptrB->next;
    }
    ptrA = headA;
    ptrB = headB;
    int len = 0;
    if(lenA > lenB){
        len = lenA - lenB;
        while(len>0){
            ptrA = ptrA->next;
            --len;
        }
    }else{
        len = lenB - lenA;
        while(len>0){
            ptrB = ptrB->next;
            --len;
        }
    }
    while(ptrA != ptrB){
        ptrA = ptrA->next;
        ptrB = ptrB->next;
    }
    return ptrA;
}
//44.在排序数组中查找数字
//44.1数字在排序数组中出现的次数
int getnumberstimes(vector<int>& nums,int k)
{
    if(nums.empty())
        return 0;
    int l = 0;
    int r = (int)nums.size()-1;
    while(l<r){
        int mid = l + (r-l)/2;
        if(nums[mid] > k){
            r = mid-1;
        }else if(nums[mid]<k){
            l = mid+1;
        }else{
            r = mid;
        }
    }
    int count = 0;
    while(nums[l] == k){
        ++count;
        ++l;
    }
    return count;
}
//44.2.0~n-1中缺失的数字
int getlosernumber(vector<int>& nums)
{
    if(nums.empty())
        return -1;
    int l = 0;
    int r = (int)nums.size()-1;
    while(l<r){
        int mid = l+(r-l)/2;
        if(nums[mid]>mid){
            r = mid-1;
        }else if(nums[mid] == mid){
            l = mid+1;
        }else{
            return -1;
        }
    }
    return l;
}
//44.3.数组中数值和下标相等的元素
int findvalueequalindexarray(vector<int>& nums)
{
    if(nums.empty())
        return -1;
    int l = 0;
    int r = (int)nums.size()-1;
    while(l<r){
        int mid = l+(r-l)/2;
        if(nums[mid] > mid){
            r = mid-1;
        }else if(nums[mid] < mid){
            l = mid+1;
        }else{
            r = mid;
            l = mid;
        }
    }
    return l;
}
//54.二叉搜索树的第k个大节点
//递归，简单
TreeNode* findknodebinarytree(TreeNode* root,int k)
{
    if(root == NULL)
        return NULL;
    TreeNode* ptr = root->left;
    stack<TreeNode*> intravel;
    TreeNode* help = NULL;
    vector<TreeNode*> searchtree;
    intravel.push(root);
    while(!intravel.empty()){
        while(ptr != NULL){
            intravel.push(ptr);
            ptr = ptr->left;
        }
        help = intravel.top();
        intravel.pop();
        searchtree.push_back(help);
        ptr = help->right;
    }
    return searchtree[k-1];
}
//46.二叉树的深度
//46.1.二叉树的深度
int getdepthofbinarytree(TreeNode* root)
{
    if(root == NULL)
        return 0;
    int left = 1+getdepthofbinarytree(root->left);
    int right = 1+getdepthofbinarytree(root->right);
    return max(left,right);
}
//46.2.平衡二叉树
rethandisb isbalancetree(TreeNode* root)
{
    if(root == NULL){
        return rethandisb(true,0);
    }
    rethandisb leftdata = isbalancetree(root->left);
    rethandisb rightdata = isbalancetree(root->right);
    if(leftdata.isbalance && rightdata.isbalance && abs(leftdata.height - rightdata.height) <= 1){
        return rethandisb(true,max(leftdata.height,rightdata.height)+1);
    }
    return rethandisb(false,0);
}
//47.数组中数字出现的次数
//47.1.数组中只出现一次的两个数字
vector<int> findtwoonceshownumbers(vector<int>& nums)
{
    int e = 0;
    for(int i = 0;i<nums.size();i++){
        e = e^nums[i];
    }
    bitset<32> etemp(e);
    int k = 0;
    for(;k<32;k++){
        if(etemp.test(k) == 1)
            break;
    }
    int et = 0;
    for(int i = 0;i<nums.size();i++){
        bitset<32> temp(nums[i]);
        if(temp.test(k) == 1)
            et = et^nums[i];
    }
    vector<int> ret;
    ret.push_back(et);
    ret.push_back(et^e);
    return ret;
}
//47.2.数组中唯一只出现一次的数字,如果一个数字出现三次，那么它的二进制表示每一位也出现三次。如果把所有出现三次的数字的二进制表示的每一位都分别加起来，那么每一位的和都能被3整除
int onyonceshownumber(vector<int>& nums)
{
    if(nums.empty())
        throw "invalid input";
    int bitsum[32] = {0};
    for(int i = 0;i<nums.size();i++){
        int bitmask = 1;
        for(int j = 31;j>=0;--j){
            int bit = nums[i]&bitmask;
            if(bit!=0)
                bitsum[j]+=1;
            bitmask = bitmask<<1;
        }
    }
    int result = 0;
    for(int i = 0;i<32;i++){
        result = result<<1;
        result += bitsum[i]%3;
    }
    return result;
}
//48.和为s的数字
//48.1.和为s的两个数字

vector<int> getsumoftwonumbers(vector<int>& nums,int s)
{
    vector<int> twosum;
    if(nums.empty()){
        return twosum;
    }
    int temp = 0;
    int l = 0;
    int r = (int)nums.size()-1;
    for(int i = 0;i<nums.size();i++){
        temp = s-nums[i];
        if(temp<nums[i])
            return twosum;
        else{
            l = i+1;
            while(l<r){
                int mid = l + (r-l)/2;
                if(nums[mid]<temp){
                    r = mid-1;
                }else if(nums[mid] > temp){
                    l = mid+1;
                }else{
                    l = mid;
                    r = mid;
                }
            }
        }
        if(nums[i]+nums[l] == s){
            twosum.push_back(nums[i]);
            twosum.push_back(nums[l]);
            return twosum;
        }
    }
    return twosum;
}
//O(N)的解法
vector<int> optimalgetsumoftwonumbers(vector<int>& nums,int s)
{
    vector<int> twosum;
    if(nums.empty()){
        return twosum;
    }
    int len = (int)nums.size()-1;
    int ahead = len;
    int behind = 0;
    while(ahead>behind){
        long long cursum = nums[ahead]+nums[behind];
        if(cursum == s){
            twosum.push_back(nums[ahead]);
            twosum.push_back(nums[behind]);
            return twosum;
        }
        else if(cursum > s){
            ahead--;
        }else{
            behind++;
        }
    }
    return twosum;
}
//48.2.和为s的连续整数序列,利用窗口的思路解决
void printcontinuousindex(int s)
{
    if(s <= 0)
        return;
    int l = 1;
    int r = 1;
    int sum = 1;
    while(r<s){
        if(sum == s){
            for(int i = l;i<=r;i++){
                cout<<i<<" ";
            }
            cout<<endl;
            r++;
            sum += r;
        }else if(sum < s){
            r++;
            sum += r;
        }else{
            sum -= l;
            l++;
        }
    }
}
//49.n个骰子的点数
unordered_map<int, int>::iterator sumdiceit;
void getsumdice(int n,int i,int sum,unordered_map<int,int>& nums)
{
    if(i == n){
        sumdiceit = nums.find(sum);
        if(sumdiceit != nums.end()){
            sumdiceit->second++;
        }else{
            nums.insert(make_pair(sum,1));
        }
        return ;
    }

    for(int j = 1;j<=6;j++){
        getsumdice(n,i+1,j+sum,nums);
    }
}
void getprobabilitydice(int n)
{
    if(n == 0)
        return;
    unordered_map<int,int> recordpro;
    getsumdice(n,0,0,recordpro);
    unordered_map<int,int>::iterator it = recordpro.begin();
    double total = pow(6,n);
    while(it != recordpro.end()){
        cout<<"The probality of "<<it->first<<" is "<<(it->second/total)<<endl;
        ++it;
    }
}
//优化版
void printprobality(int n)
{
    int gmaxvalue = 6;
    if(n < 1)
        return;
    int* pprobality[2];
    pprobality[0] = new int[gmaxvalue*n + 1];
    pprobality[1] = new int[gmaxvalue*n + 1];
    for(int i = 0;i<gmaxvalue*n+1;i++){
        pprobality[0][i] = 0;
        pprobality[1][i] = 0;
    }
    int flag = 0;
    for(int i = 1;i<=gmaxvalue;i++)
        pprobality[flag][i] = 1;
    for(int k = 2; k<=n;k++){
        for(int i = 0;i<k;i++)
            pprobality[1-flag][i] = 0;
        for(int i = k;i<=gmaxvalue*k;i++)
        {
            pprobality[1-flag][i] = 0;
            for(int j= 1;j<=i && j<=gmaxvalue;j++)
                pprobality[1-flag][i] += pprobality[flag][i-j];
        }
        flag = 1-flag;
    }
    double total = pow((double)gmaxvalue,n);
    for(int i = n;i<=gmaxvalue*n;i++){
        double ratio = (double)pprobality[flag][i]/total;
        cout<<i<<" "<<ratio<<endl;
    }
    delete[] pprobality[0];
    delete[] pprobality[1];
}
//50.扑克牌中的顺子
bool isshunzi(string& str)
{
    if(str.empty())
        return true;
    vector<int> nums;
    for(int i = 0;i<str.size();i++){
        if(str[i] == 'A'){
            nums.push_back(1);
        }
        else if(str[i] == 'J'){
            nums.push_back(11);
        }
        else if(str[i] == 'Q'){
            nums.push_back(12);
        }
        else if(str[i] == 'K'){
            nums.push_back(13);
        }
        else if(str[i] == 'W'){
            nums.push_back(0);
        }
        else{
            nums.push_back(str[i] - '0');
        }
    }
    sort(nums.begin(),nums.end(),[](int a,int b){ return a<b; });
    int zerocount = 0;
    int spacecount = 0;
    int i = 0;
    while(i<nums.size() && nums[i] == 0){
        zerocount++;
        i++;
    }
    if(i == nums.size()){
        return true;
    }
    int last = nums[i++];
    while(i < nums.size()){
        if(nums[i] == last)
            return false;
        spacecount += nums[i] - last -1;
        last = nums[i];
        i++;
    }
    if(zerocount >= spacecount)
        return true;
    else
        return false;
}
//51.圆圈中最后剩下的数字
int getliveswordversion(int i,int m)
{
    if(i == 1){
        return 1;
    }
    return (getliveswordversion(i-1,m)+m-1)%i+1;
}
//
int lastremaining(unsigned int n,unsigned int m)
{
    if(n<1 || m <1)
        return -1;
    int last = 0;
    for(int i = 2;i<= n;i++)
        last = (last+m)%i;
    return last;
}
//52.股票的最大利润
int getmaxprofit(vector<int>& prices)
{
    if(prices.empty())
        return 0;
    int maxprofit = 0;
    int curprofit = 0;
    for(int i = 0;i<prices.size()-1;i++){
        for(int j = i+1;j<prices.size();j++){
            if(prices[i] < prices[j]){
                curprofit = prices[j]-prices[i];
                maxprofit = max(maxprofit,curprofit);
            }
        }
    }
    return maxprofit;
}
//优化版，降低时间复杂度
int bettertimegetmaxprofit(vector<int>& prices)
{
    if(prices.empty())
        return 0;
    vector<int> maxprices;
    maxprices.resize(prices.size());
    int i = (int)maxprices.size()-1;
    maxprices[i] = i;
    i--;
    while(i>=0){
        if(prices[maxprices[i+1]] <= prices[i]){
            maxprices[i] = i;
        }
        else{
            maxprices[i] = maxprices[i+1];
        }
        --i;
    }
    int maxprofits = 0;
    int curprofits = 0;
    for(int j = 0;j<prices.size();j++){
        curprofits = prices[maxprices[j]]-prices[j];
        maxprofits = max(maxprofits,curprofits);
    }
    return maxprofits;
}
//最优版，最优的时间复杂度和额外空间复杂度
int optimalgetmaxprofit(vector<int>& prices)
{
    if(prices.empty())
        return 0;
    int lastmin = prices[0];
    int maxprofits = 0;
    for(int i = 1;i<prices.size();i++){
        maxprofits = max(maxprofits,prices[i]-lastmin);
        lastmin = min(lastmin,prices[i]);
    }
    return maxprofits;
}
//54.不用加减乘除做加法
int addsum(int num1,int num2)
{
    //第一步，求两个数的异或和
    int numxor = num1^num2;
    //第二步，求两个数的进位
    int numyu = (num1&num2) << 1;
    if(numyu != 0){
        return addsum(numxor,numyu);
    }else{
        return numxor;
    }
}
//55.构建乘积数组
void multiply(vector<int>& array1,vector<int>& array2)
{
    int length1 = (int)array1.size();
    int length2 = (int)array2.size();
    if(length1 == length2 && length2 > 1){
        array2[0] = 1;
        for(int i = 1;i<length1;i++){
            array2[i] = array2[i-1]*array1[i-1];
        }
        double temp = 1;
        for(int i = length1-2;i>=0;--i){
            temp *= array1[i+1];
            array2[i] *= temp;
        }
    }
}
