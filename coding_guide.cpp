//
//  coding_guide.cpp
//  c++
//
//  Created by litianfa on 2019/7/24.
//  Copyright © 2019 litianfa. All rights reserved.
//

#include "coding_guide.hpp"

//1.删除链表中间节点
ListNode* deletemiddlepoint(ListNode* head)
{
    if(head == NULL || head->next == NULL)
        return NULL;
    int len = 0;
    ListNode* ptr = head;
    while(ptr != NULL){
        ++len;
        ptr = ptr->next;
    }
    if(len == 2){
        ptr = head->next;
        return ptr;
    }
    len = (len-1)>>1;
    --len;
    ptr = head;
    while(len > 0){
        --len;
        ptr = ptr->next;
    }
    ListNode* help = ptr->next;
    ptr->next = help->next;
    delete help;
    return head;
}
//进阶，给定链表的头节点head、整数a,b,实现删除位于a/b处节点的函数
ListNode* deleteabnode(ListNode* head,int a,int b)
{
    if(head == NULL)
        return NULL;
    int r = a/b;
    if(r == 0 && r > 1){
        return head;
    }
    int len = 0;
    ListNode* ptr = head;
    while(ptr != NULL){
        ++len;
        ptr = ptr->next;
    }
    int node = 0;
    if(len != b){
        node = (a*len)/b + 1;
    }
    else
        node = a;
    if(a == b)
        node = len;
    if(node == 1){
        ptr = head->next;
        return ptr;
    }
    ptr = head;
    --node;
    while(node > 1){
        --node;
        ptr = ptr->next;
    }
    ListNode* help = ptr->next;
    ptr->next = help->next;
    delete help;
    return head;
}
//2.两个单链表生成相加链表
ListNode* createnewsumList(ListNode* head1,ListNode* head2)
{
    if(head1 == NULL && head2 == NULL)
        return NULL;
    if(head1 == NULL)
        return head2;
    if(head2 == NULL)
        return head1;
    stack<ListNode*> list1,list2;
    ListNode* ptr1 = head1;
    ListNode* ptr2 = head2;
    while(ptr1 != NULL){
        list1.push(ptr1);
        ptr1 = ptr1->next;
    }
    while(ptr2 != NULL){
        list2.push(ptr2);
        ptr2 = ptr2->next;
    }
    int leftbitsum = 0;
    ListNode* ptr = NULL;
    ListNode* last = NULL;
    if(list1.size() > list2.size()){
        while(!list1.empty() && !list2.empty()){
            ptr = list1.top();
            list1.pop();
            ptr2 = list2.top();
            list2.pop();
            ptr->next = last;
            if(ptr->val + ptr2->val + leftbitsum > 9){
                ptr->val = ptr->val + ptr2->val + leftbitsum - 10;
                leftbitsum = 1;
            }else{
                ptr->val = ptr->val + ptr2->val + leftbitsum;
                leftbitsum = 0;
            }
            last = ptr;
        }
        while(!list1.empty()){
            ptr = list1.top();
            list1.pop();
            if(ptr->val + leftbitsum > 9){
                ptr->val = ptr->val + leftbitsum - 10;
                leftbitsum = 1;
            }else{
                ptr->val = ptr->val + leftbitsum;
                leftbitsum = 0;
            }
            last = ptr;
        }
    }
    else{
        while(!list1.empty() && !list2.empty()){
            ptr = list2.top();
            list2.pop();
            ptr1 = list1.top();
            list1.pop();
            ptr->next = last;
            if(ptr->val + ptr1->val + leftbitsum > 9){
                ptr->val = ptr->val + ptr1->val + leftbitsum - 10;
                leftbitsum = 1;
            }else{
                ptr->val = ptr->val + ptr1->val + leftbitsum;
                leftbitsum = 0;
            }
            last = ptr;
        }
        while(!list2.empty()){
            ptr = list2.top();
            list2.pop();
            if(ptr->val + leftbitsum > 9){
                ptr->val = ptr->val + leftbitsum - 10;
                leftbitsum = 1;
            }else{
                ptr->val = ptr->val + leftbitsum;
                leftbitsum = 0;
            }
            last = ptr;
        }
    }
    if(leftbitsum == 1){
        ptr = new ListNode(1);
        ptr->next = last;
    }
    return ptr;
}
//进阶优化额外空间复杂度,用链表的逆序求解
ListNode* createnewsumlistoptimal(ListNode* head1,ListNode* head2)
{
    if(head1 == NULL && head2 == NULL)
        return NULL;
    if(head1 == NULL)
        return head2;
    if(head2 == NULL)
        return head1;
    int len1 = 0;
    int len2 = 0;
    ListNode* ptr1 = head1;
    ListNode* ptr2 = head2;
    ListNode* next = NULL;
    ListNode* help = NULL;
    while(ptr1 != NULL){
        next = ptr1->next;
        ptr1->next = help;
        help = ptr1;
        ptr1 = next;
        ++len1;
    }
    ptr1 = help;
    next = NULL;
    help = NULL;
    while(ptr2 != NULL){
        next = ptr2->next;
        ptr2->next = help;
        help = ptr2;
        ptr2 = next;
        ++len2;
    }
    ptr2 = help;
    int leftbitsum = 0;
    ListNode* ptr = NULL;
    ListNode* head = NULL;
    if(len1 > len2){
        ptr = ptr1;
        head = ptr;
        while(ptr != NULL){
            if(ptr2 != NULL){
                if(ptr->val + ptr2->val + leftbitsum > 9){
                    ptr->val = ptr->val + ptr2->val + leftbitsum - 10;
                    leftbitsum = 1;
                }else{
                    ptr->val = ptr->val + ptr2->val + leftbitsum;
                    leftbitsum = 0;
                }
                ptr2 = ptr2->next;
            }else{
                if(ptr->val + leftbitsum > 9){
                    ptr->val = ptr->val + leftbitsum - 10;
                    leftbitsum = 1;
                }else{
                    ptr->val = ptr->val + leftbitsum;
                    leftbitsum = 0;
                }
            }
            ptr = ptr->next;
        }
    }
    else{
        ptr = ptr2;
        head = ptr;
        while(ptr != NULL){
            if(ptr1 != NULL){
                if(ptr->val + ptr1->val + leftbitsum > 9){
                    ptr->val = ptr->val + ptr1->val + leftbitsum - 10;
                    leftbitsum = 1;
                }else{
                    ptr->val = ptr->val + ptr1->val + leftbitsum;
                    leftbitsum = 0;
                }
                ptr1 = ptr1->next;
            }else{
                if(ptr->val + leftbitsum > 9){
                    ptr->val = ptr->val + leftbitsum - 10;
                    leftbitsum = 1;
                }else{
                    ptr->val = ptr->val + leftbitsum;
                    leftbitsum = 0;
                }
            }
            ptr = ptr->next;
        }
    }
    ptr = head;
    next = NULL;
    help = NULL;
    while(ptr != NULL){
        next = ptr->next;
        ptr->next = help;
        help = ptr;
        ptr = next;
    }
    if(leftbitsum == 1){
        ptr = new ListNode(1);
        ptr->next = help;
    }
    return ptr;
}
//3.删除无序单链表中值重复出现的节点
void deletesamevalnodelist(ListNode* head)
{
    if(head == NULL || head->next == NULL)
        return;
    unordered_set<int> recordval;
    unordered_set<int>::iterator it;
    ListNode* ptr = head;
    ListNode* last = ptr;
    while(ptr != NULL){
        it = recordval.find(ptr->val);
        if(it != recordval.end()){
            last->next = ptr->next;
            ptr = last->next;
        }else{
            recordval.insert(ptr->val);
            last = ptr;
            ptr = ptr->next;
        }
    }
    return;
}
//4.在单链表中删除指定值的节点
ListNode* deletepointnodelist(ListNode* head,int num)
{
    if(head == NULL)
        return NULL;
    ListNode* newhead = head;
    ListNode* ptr = head;
    ListNode* help = NULL;
    while(ptr->val == num){
        help = ptr;
        ptr = ptr->next;
        delete help;
    }
    newhead = ptr;
    help = ptr;
    while(ptr != NULL){
        if(ptr->val == num){
            help->next = ptr->next;
            delete ptr;
            ptr = help->next;
        }else{
            help = ptr;
            ptr = ptr->next;
        }
    }
    return newhead;
}
//6.将搜索二叉树转换为双向链表
//中序遍历
Node* searchtreetodoubledirectionlist(Node* root)
{
    if(root == NULL){
        return NULL;
    }
    stack<Node*> treequeue;
    Node* ptr = root;
    Node* newroot = NULL;
    Node* last = NULL;
    bool isroot = true;
    treequeue.push(root);
    while(!treequeue.empty()){
        while(ptr != NULL){
            ptr = treequeue.top();
            ptr = ptr->left;
            if(ptr != NULL)
                treequeue.push(ptr);
        }
        Node* help = treequeue.top();
        treequeue.pop();
        help->left = last;
        if(last != NULL)
            last->right = help;
        if(isroot){
            newroot = help;
            isroot = false;
        }
        if(help->right != NULL){
            treequeue.push(help->right);
            ptr = help->right;
        }else if(treequeue.empty()){
            break;
        }
        last = help;
    }
    return newroot;
}
//7.单链表的选择排序
ListNode* selectsortlist(ListNode* head)
{
    if(head == NULL || head->next == NULL)
        return NULL;
    ListNode* newhead = NULL;
    ListNode* ptr1 = head;
    ListNode* ptr2 = NULL;
    ListNode* last = NULL;
    ListNode* minptr = NULL;
    ListNode* ptr = NULL;
    while(ptr1 != NULL){
        ptr2 = ptr1;
        minptr = ptr1;
        while(ptr2->next != NULL){
            if(minptr->val > ptr2->next->val){
                minptr = ptr2->next;
                last = ptr2;
            }
            ptr2 = ptr2->next;
        }
        if(ptr1 == minptr){
            ptr1 = minptr->next;
        }else
            last->next = minptr->next;
        if(newhead == NULL){
            newhead = minptr;
            ptr = newhead;
        }else{
            ptr->next = minptr;
            ptr = ptr->next;
        }
    }
    return newhead;
}
//8.一种怪异的节点删除方式
void deletespecialnode(ListNode* spnode)
{
    if(spnode == NULL)
        return;
    ListNode* next = spnode->next;
    if(next == NULL){
        throw "can not remove the last node";
    }
    spnode->val = next->val;
    spnode->next = next->next;
}
//9.向有序的环形单链表中插入新节点
ListNode* insertintocuclelist(ListNode* head,int num)
{
    if(head == NULL)
        return head;
    ListNode* last = head;
    ListNode* ptr = head->next;
    while(ptr != head){
        if(ptr->val > num && last->val <= num){
            break;
        }else{
            last = last->next;
            ptr = ptr->next;
        }
    }
    ListNode* node = new ListNode(num);
    last->next = node;
    node->next = ptr;
    return head->val < num ? head : node;
}
//10.合并两个有序的单链表
ListNode* convergetwolists(ListNode* head1,ListNode* head2)
{
    if(head1 == NULL && head2 == NULL)
        return NULL;
    if(head1 == NULL)
        return head2;
    if(head2 == NULL)
        return head1;
    ListNode* newhead = NULL;
    ListNode* ptr = NULL;
    ListNode* ptr1 = head1;
    ListNode* ptr2 = head2;
    while(ptr1 != NULL && ptr2 != NULL){
        if(ptr1->val <= ptr2->val){
            if(newhead == NULL){
                newhead = ptr1;
                ptr = newhead;
                ptr1 = ptr1->next;
            }else{
                ptr->next = ptr1;
                ptr = ptr->next;
                ptr1 = ptr1->next;
            }
        }else{
            if(newhead == NULL){
                newhead = ptr2;
                ptr = newhead;
                ptr2 = ptr2->next;
            }else{
                ptr->next = ptr2;
                ptr = ptr->next;
                ptr2 = ptr2->next;
            }
        }
    }
    while(ptr1 != NULL){
        ptr->next = ptr1;
        ptr = ptr->next;
        ptr1 = ptr1->next;
    }
    while(ptr2 != NULL){
        ptr->next = ptr2;
        ptr = ptr->next;
        ptr2 = ptr2->next;
    }
    return newhead;
}
//11.按照左右半区的方式重新组合单链表
ListNode* leftrightmidareacombinelist(ListNode* head)
{
    if(head == NULL || head->next == NULL || head->next->next == NULL)
        return head;
    ListNode* slow = head->next;
    ListNode* fast = head->next->next;
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* l = head;
    ListNode* r = slow;
    ListNode* newhead = NULL;
    ListNode* ptr = NULL;
    bool isleft = true;
    while(l != slow && r != NULL){
        if(isleft){
            if(newhead == NULL){
                newhead = l;
                ptr = newhead;
            }else{
                ptr->next = l;
                ptr = ptr->next;
            }
            l = l->next;
            isleft = false;
        }else{
            ptr->next = r;
            r = r->next;
            ptr = ptr->next;
            isleft = true;
        }
    }
    while(l != slow){
        ptr->next = l;
        ptr = ptr->next;
        l = l->next;
    }
    while(r != NULL){
        ptr->next = r;
        ptr = ptr->next;
        r = r->next;
    }
    ptr->next = NULL;
    return newhead;
}


//二叉树问题
//1.打印二叉树的边界节点
void printedge1(Node* head)
{
    if(head == NULL)
        return;
    int height = getheight(head, 0);
    vector<vector<Node*>> edgemap;
    edgemap.resize(height);
    for(int i = 0;i<height;i++){
        edgemap[i].resize(2);
    }
    vector<Node*> temp;
    temp.resize(2);
    temp[0] = NULL;
    temp[1] = NULL;
    for(int i = 0;i<height;i++){
        edgemap[i] = temp;
    }
    setedgemap(head, 0, edgemap);
    for(int i = 0;i != height;i++){
        cout<<edgemap[i][0]->val<<" ";
    }
    printleafnotinmap(head, 0, edgemap);
    for(int i = height-1;i != -1;i--){
        if(edgemap[i][0] != edgemap[i][1]){
            cout<<edgemap[i][1]->val<<" ";
        }
    }
}
int getheight(Node* head,int l)
{
    if(head == NULL)
        return l;
    return max(getheight(head->left, l+1),getheight(head->right, l+1));
}
void setedgemap(Node* head,int l,vector<vector<Node*>>& edgemap)
{
    if(head == NULL){
        return;
    }
    vector<Node*> temp;
    temp.push_back((edgemap[l][0] == NULL) ? head : edgemap[l][0]);
    temp.push_back(head);
    edgemap[l] = temp;
    setedgemap(head->left, l+1, edgemap);
    setedgemap(head->right, l+1, edgemap);
}
void printleafnotinmap(Node* head,int l,vector<vector<Node*>>& edgemap)
{
    if(head == NULL)
        return;
    if(head->left == NULL && head->right == NULL && head != edgemap[l][0] && head != edgemap[l][1])
        cout<<head->val<<" ";
    printleafnotinmap(head->left, l+1, edgemap);
    printleafnotinmap(head->right,l+1,edgemap);
}
//标准2打印边界
//修改标准2代码
vector<int> boundaryofbinarytree(Node* root)
{
    vector<int> res;
    if(root == NULL)
        return res;
    res.push_back(root->val);
    getbounds(root->left,res,true,false);
    getbounds(root->right,res,false,true);
    return res;
}
void getbounds(Node* root,vector<int>& res,bool leftbound,bool rightbound)
{
    if(root == NULL)
        return;
    if(leftbound){
        res.push_back(root->val);
    }
    if(!leftbound && !rightbound && root->left == NULL && root->right == NULL){
        res.push_back(root->val);
    }
    getbounds(root->left,res,leftbound,rightbound && root->right == NULL);
    getbounds(root->right,res,leftbound && root->left == NULL,rightbound);
    if(rightbound){
        res.push_back(root->val);
    }
}
//2.较为直观的打印二叉树
void printtree(Node* head)
{
    printinorder(head, 0, "H", 17);
    cout<<endl;
}
void printinorder(Node* head,int height,string to,int len)
{
    if(head == NULL)
        return;
    printinorder(head->right, height+1, "v", len);
    //
    string val = to+to_string(head->val)+to;
    //计算前后需要补齐的空格数
    int lenm = (int)val.length();
    int lenl = (len-lenm)/2;
    int lenr = len-lenm-lenl;
    //生成一个合格的打印字符串
    val = getspace(lenl)+val+getspace(lenr);
    //打印字符串
    cout<<(getspace(height*len)+val)<<endl;
    //
    printinorder(head->left, height+1, "^", len);
}
string getspace(int num)
{
    string space = " ";
    string buf;
    for(int i = 0;i<num;i++)
        buf += space;
    return buf;
}
//3.在二叉树中找到累加和为指定值的最长路径长度
//用哈希表来解决
int getmaxpathlength(Node* root,int sum)
{
    if(root == NULL)
        return 0;
    unordered_map<int, int> summap;
    summap.insert(make_pair(0,0));
    return preorder(root, sum, 0, 1, 0, summap);
}
int preorder(Node* root,int sum,int presum,int level,int maxlen,unordered_map<int,int>& summap)
{
    if(root == NULL)
        return maxlen;
    int cursum = presum + root->val;
    unordered_map<int,int>::iterator it = summap.find(cursum);
    if(it == summap.end()){
        summap.insert(make_pair(cursum,level));
    }
    it = summap.find(cursum - sum);
    if(it != summap.end()){
        maxlen = max(level - it->second,maxlen);
    }
    maxlen = max(maxlen,preorder(root->left,sum,cursum,level+1,maxlen,summap));
    maxlen = max(maxlen,preorder(root->right,sum,cursum,level+1,maxlen,summap));
    it = summap.find(cursum);
    if(level == it->second)
        summap.erase(it);
    return maxlen;
}
//4.n个整数的无序数组m，找到每个元素后面比它大的第一个数，要求时间复杂度为O(N)
vector<int> findmax(vector<int> num)
{
    vector<int> res;
    if(num.empty() || num.size() <2)
        return res;
    stack<int> maxstack;
    maxstack.push(0);
    res.resize(num.size());
    int i = 1;
    while(i<num.size()){
        while(!maxstack.empty() && num[maxstack.top()] < num[i]){
            int index = maxstack.top();
            maxstack.pop();
            res[index] = num[i];
        }
        maxstack.push(i++);
    }
    while(!maxstack.empty()){
        int index = maxstack.top();
        maxstack.pop();
        res[index] = INT_MAX;
    }
    return res;
}
//5.找到二叉树中的最大搜索二叉子树
searchbinary findmaxsearchbinarytree(Node* root)
{
    if(root == NULL)
        return searchbinary(NULL,INT_MIN,INT_MAX,0);
    searchbinary left = findmaxsearchbinarytree(root->left);
    searchbinary right = findmaxsearchbinarytree(root->right);
    int curnums = 0;
    if(left.head == root->left && right.head == root->right && root->val > left.maxval && root->val < right.minval){
        curnums = left.nums + right.nums + 1;
    }
    int maxnums = max(curnums,max(left.nums,right.nums));
    Node* maxhead = left.nums>right.nums ? left.head : right.head;
    if(maxnums == curnums)
        maxhead = root;
    return searchbinary(maxhead,max(root->val,max(left.maxval,right.maxval)),min(root->val,min(left.minval,right.minval)),maxnums);
}
//6.找到二叉树中符合搜索二叉树条件的最大拓扑结构
int bsttopusize1(Node* root)
{
    if(root == NULL)
        return 0;
    int maxval = maxtopo(root,root);
    maxval = max(bsttopusize1(root->left),maxval);
    maxval = max(bsttopusize1(root->right),maxval);
    return maxval;
}
int maxtopo(Node* root,Node* n)
{
    if(root != NULL && n != NULL && isbstnode(root, n, n->val)){
        return maxtopo(root,n->left)+ maxtopo(root,n->right)+1;
    }
    return 0;
}
bool isbstnode(Node* root,Node* n,int value)
{
    if(root == NULL)
        return false;
    if(root == n){
        return true;
    }
    return isbstnode(root->val > value?root->left:root->right, n, value);
}
//7.求未排序数组中累加和为规定值的最长子数组长度
int getmalengtharray(vector<int>& nums,int k)
{
    if(nums.empty())
        return 0;
    unordered_map<int, int> record;
    int cursum = 0,maxlen = 0;
    for(int i = 0;i<nums.size();i++){
        unordered_map<int, int>::iterator it = record.find(cursum);
        if(it == record.end()){
            record.insert(make_pair(cursum,i));
        }
        cursum += nums[i];
        it = record.find(cursum - k);
        if(it != record.end()){
            maxlen = max(maxlen,i - it->second);
        }
    }
    return maxlen;
}
//8.二叉树的按层打印与ZIGZAG打印
void edgeprintbinarytree(Node* root)
{
    if(root == NULL)
        return;
    Node* ptr = root;
    Node* last = root;
    queue<Node*> record;
    record.push(root);
    while(!record.empty()){
        ptr = record.front();
        record.pop();
        cout<<ptr->val<<" ";
        if(ptr->left != NULL){
            record.push(ptr->left);
        }
        if(ptr->right != NULL){
            record.push(ptr->right);
        }
        if(ptr == last){
            last = record.back();
            cout<<endl;
        }
    }
    return;
}
void ZigZagprintbinarytree(Node* root)
{
    if(root == NULL){
        return;
    }
    Node* ptr = NULL;
    Node* last = root;
    bool ispositive = true;
    deque<Node*> record;
    record.push_back(root);
    while(!record.empty()){
        if(ispositive){
            ptr = record.front();
            record.pop_front();
            if(ptr->left != NULL){
                record.push_back(ptr->left);
            }
            if(ptr->right != NULL){
                record.push_back(ptr->right);
            }
        }else{
            ptr = record.back();
            record.pop_back();
            if(ptr->right != NULL){
                record.push_front(ptr->right);
            }
            if(ptr->left != NULL){
                record.push_front(ptr->left);
            }
        }
        cout<<ptr->val<<" ";
        if(ptr == last){
            if(ispositive){
                ispositive = false;
                last = record.front();
            }
            else{
                ispositive = true;
                last = record.back();
            }
            cout<<endl;
        }
    }
}
//9.调整搜索二叉树中两个错误的节点
vector<Node*> gettwoerrsearchnode(Node* root)
{
    vector<Node*> err;
    if(root == NULL)
        return err;
    //中序遍历搜索二叉树
    stack<Node*> searchtree;
    Node* last = NULL;
    Node* ptr = root->left;
    bool isfirst = true;
    Node* curerr = NULL;
    Node* help = NULL;
    searchtree.push(root);
    while(!searchtree.empty()){
        while(ptr != NULL){
            searchtree.push(ptr);
            ptr = ptr->left;
        }
        help = searchtree.top();
        searchtree.pop();
        if(last != NULL && isfirst && last->val > help->val){
            err.push_back(last);
            isfirst = false;
            curerr = last;
        }
        if(!isfirst && curerr->val < help->val){
            err.push_back(last);
            break;
        }
        if(help->right != NULL){
            searchtree.push(help->right);
            ptr = help->right->left;
        }
        last = help;
    }
    if(err.size()<2){
        err.push_back(help);
    }
    return err;
}
//10.判断t1树是否包含t2树的全部的拓扑结构
bool isincludetopo(Node* t1,Node* t2)
{
    if(t2 == NULL)
        return true;
    if(t1 == NULL)
        return false;
    return isincludeprocess(t1,t2) || isincludetopo(t1->left,t2) || isincludetopo(t1->right,t2);
}
bool isincludeprocess(Node* t1,Node* t2)
{
    if(t2 == NULL)
        return true;
    if(t1 == NULL || t1->val != t2->val)
        return false;
    return isincludeprocess(t1->left,t2->left) && isincludeprocess(t1->right,t2->right);
}
//11.判断二叉树是否为平衡二叉树
bool judgebalancetree(Node* root)
{
    if(root == NULL)
        return true;
    balancetree data = isbalancetree(root);
    return data.isbalance;
}
balancetree isbalancetree(Node* root)
{
    if(root == NULL)
        return balancetree(true,0);
    balancetree left = isbalancetree(root->left);
    balancetree right = isbalancetree(root->right);
    if(left.isbalance && right.isbalance && abs(left.leveldiff - right.leveldiff) <= 1){
        return balancetree(true,max(left.leveldiff,right.leveldiff)+1);
    }else{
        return balancetree(false,0);
    }
}
//12.根据后续数组重建搜索二叉树
bool isresultforsearchtree(vector<int> nums)
{
    if(nums.size()<2)
        return true;
    return isresultprocess(nums,0,(int)nums.size()-1);
}
bool isresultprocess(vector<int>& nums,int start,int end)
{
    if(start == end)
        return true;
    int less =  -1;
    int more = end;
    for(int i = 0;i<end;i++){
        if(nums[i] < nums[end])
            less = i;
        else
            more = more == end ? i : more;
    }
    if(less == -1 || more == end)
        return isresultprocess(nums,start,end-1);
    if(less != more-1){
        return false;
    }
    return isresultprocess(nums,start,less) && isresultprocess(nums,more,end-1);
}
//重建搜索二叉树
Node* rebuildsearchbinarytree(vector<int>& nums)
{
    if(nums.empty())
        return NULL;
    int end = (int)nums.size()-1;
    return rebuildsearchtreeprocess(nums,0,end);
}
Node* rebuildsearchtreeprocess(vector<int>& nums,int start,int end)
{
    if(start > end)
        return NULL;
    Node* ptr = new Node(nums[end]);
    int less = -1;
    int more = end;
    for(int i = start;i<end;i++){
        if(nums[i] < nums[end])
            less = i;
        else
            more = more == end ? i : more;
    }
    ptr->left = rebuildsearchtreeprocess(nums, start, less);
    ptr->right = rebuildsearchtreeprocess(nums, more, end-1);
    return ptr;
}
//13.通过有序数组生成平衡搜索二叉树
Node* generatebalancesearchtree(vector<int>& nums)
{
    if(nums.empty())
        return NULL;
    return generateprocesstree(nums,0,(int)nums.size()-1);
}
Node* generateprocesstree(vector<int>& nums,int start,int end)
{
    if(start > end)
        return NULL;
    int mid = start + (end-start)/2;
    Node* head = new Node(nums[mid]);
    head->left = generateprocesstree(nums,start,mid-1);
    head->right = generateprocesstree(nums,mid+1,end);
    return head;
}
//14.在二叉树中找到两个节点的最近公共祖先
Node* findminrelationroot(Node* head,Node* h1,Node* h2)
{
    if(head == NULL)
        return NULL;
    Node* root = NULL;
    if(findminrelationprocess(head, h1) && findminrelationprocess(head,h2))
    {
        root = head;
    }
    if(head->left != NULL){
        Node* ptr = findminrelationroot(head->left,h1,h2);
        root = ptr != NULL ? ptr : root;
    }
    if(head->right != NULL){
        Node* ptr = findminrelationroot(head->right,h1,h2);
        root = ptr != NULL ? ptr : root;
    }
    return root;
}
bool findminrelationprocess(Node* root,Node* h)
{
    if(root == NULL)
        return false;
    if(root == h)
        return true;
    return findminrelationprocess(root->left,h) || findminrelationprocess(root->right,h);
}
//
Node* lowestancestor(Node* head,Node* o1,Node* o2)
{
    if(head == NULL || head == o1 || head == o2)
        return head;
    Node* left = lowestancestor(head->left, o1, o2);
    Node* right = lowestancestor(head->right, o1, o2);
    if(left != NULL && right != NULL)
        return head;
    return left != NULL ? left : right;
}
//进阶：如果查询两个节点的最近公共祖先的操作十分频繁，想法让单条查询的查询时间减少
int reducetimeoffindlowestancestor(Node* head,Node* o1,Node* o2)
{
    if(head == NULL)
        return NULL;
    unordered_map<int,int> record;
    unordered_map<int,int>::iterator it;
    stack<Node*> nodest;
    Node* ptr = head;
    nodest.push(ptr);
    while(ptr != NULL && !nodest.empty()){
        ptr = nodest.top();
        nodest.pop();
        it = record.find(ptr->val);
        if(it == record.end()){
            record.insert(make_pair(ptr->val,INT_MAX));
        }
        if(ptr->left != NULL){
            nodest.push(ptr->left);
            record.insert(make_pair(ptr->left->val,ptr->val));
        }
        if(ptr->right != NULL){
            nodest.push(ptr->right);
            record.insert(make_pair(ptr->right->val,ptr->val));
        }
    }
    unordered_map<int,int> recordA;
    it = record.find(o1->val);
    while(it->first != head->val){
        it = record.find(it->second);
        recordA.insert(make_pair(it->first,it->second));
    }
    recordA.insert(make_pair(head->val,NULL));
    it = record.find(o2->val);
    unordered_map<int,int>::iterator it1;
    while(it->first != head->val){
        it1 = recordA.find(it->second);
        if(it1 != recordA.end()){
            return it->second;
        }
        it = record.find(it->second);
    }
    return head->val;
}
//15.Tarjan算法与并查集解决二叉树节点间最近公共祖先的批量查询问题
class UnionFind{
private:
    unordered_map<int,int> fathermap;
    unordered_map<int,int> sizemap;
public:
    UnionFind(vector<int>& nums)
    {
        fathermap.clear();
        sizemap.clear();
        for(auto c:nums){
            fathermap.insert(make_pair(c,c));
            sizemap.insert(make_pair(c,1));
        }
    }
    int findfather(int val){
        unordered_map<int,int>::iterator it = fathermap.find(val);
        int father = it->second;
        if(father != val){
            father = findfather(father);
        }
        it->second = father;
        return father;
    }
    bool issameunion(int node1,int node2){
        return findfather(node1) == findfather(node2);
    }
    void unionset(int node1,int node2){
        int node1father = findfather(node1);
        int node2father = findfather(node2);
        if(node1father != node2father){
            unordered_map<int,int>::iterator itnode1 = sizemap.find(node1father);
            unordered_map<int, int>::iterator itnode2 = sizemap.find(node2father);
            if(itnode1->second <= itnode2->second){
                unordered_map<int,int>::iterator it = fathermap.find(itnode1->first);
                it->second = itnode2->first;
                itnode2->second = itnode1->second + itnode2->second;
            }else{
                unordered_map<int, int>::iterator it = fathermap.find(itnode2->first);
                it->second = itnode1->first;
                itnode1->second = itnode1->second+itnode2->second;
            }
        }
    }
};
vector<int> tarjanandunionforlowestancestor(Node* head,vector<Query> nums)
{
    vector<int> res;
    if(head == NULL)
        return res;
    stack<Node*> pretravel;
    vector<int> sets;
    pretravel.push(head);
    Node* ptr = head;
    while(!pretravel.empty()){
        ptr = pretravel.top();
        pretravel.pop();
        sets.push_back(ptr->val);
        if(ptr->left != NULL)
            pretravel.push(ptr->left);
        if(ptr->right != NULL)
            pretravel.push(ptr->right);
    }
    UnionFind unionsets(sets);
    
    return res;
}
//16.利用先序和中序遍历重建二叉树
Node* rebuildbinarytree(vector<int> pretra,vector<int> intra)
{
    if(pretra.empty())
        return NULL;
    unordered_map<int,int> record;
    for(int i = 0;i<intra.size();i++){
        record.insert(make_pair(intra[i],i));
    }
    return preintreeprocess(pretra,0,(int)pretra.size()-1,intra,0,(int)intra.size()-1,record);
}
Node* preintreeprocess(vector<int>& pretra,int pi,int pj,vector<int>& intra,int ni,int nj,unordered_map<int,int>& record)
{
    if(pi>pj)
        return NULL;
    Node* head = new Node(pretra[pi]);
    int index = record[pretra[pi]];
    head->left = preintreeprocess(pretra, pi+1, pi+index-ni, intra, ni, index-1, record);
    head->right = preintreeprocess(pretra, pi + index - ni+1, pj, intra, index+1, nj, record);
    return head;
}
//17.中序和后续遍历重建二叉树
Node* rebuildbinary2(vector<int> intra,vector<int> postra)
{
    if(intra.empty())
        return NULL;
    unordered_map<int,int> map;
    for(int i = 0;i<intra.size();i++){
        map.insert(make_pair(intra[i],i));
    }
    return inposprocess(intra, 0, (int)intra.size()-1, postra, 0, (int)postra.size()-1, map);
}
Node* inposprocess(vector<int>& intra,int ni,int nj,vector<int>& postra,int si,int sj,unordered_map<int,int>& map)
{
    if(si>sj)
        return NULL;
    Node* head = new Node(postra[sj]);
    int index = map[postra[sj]];
    head->left = inposprocess(intra, ni, index-1, postra, si, si+index-ni-1, map);
    head->right = inposprocess(intra, index+1, nj, postra, si+index-ni, sj-1, map);
    return head;
}
//18.先序和后序遍历重建二叉树
Node* rebuildbinary3(vector<int> pre,vector<int> pos)
{
    if(pre.empty())
        return NULL;
    unordered_map<int,int> record;
    for(int i = 0;i<pre.size();i++){
        record.insert(make_pair(pre[i],i));
    }
    return preposprocess(pre, 0, (int)pre.size()-1, pos, 0, (int)pos.size()-1, record);
}
Node* preposprocess(vector<int> pre,int pi,int pj,vector<int> pos,int si,int sj,unordered_map<int,int>& map)
{
    Node* head = new Node(pos[sj--]);
    if(pi == pj)
        return head;
    int index = map[pre[++pi]];
    head->left = preposprocess(pre,pi, pi+index-si , pos, si, index, map);
    head->right = preposprocess(pre, pi+index-si+1, pj, pos, index+1, sj, map);
    return head;
}
//19.通过先序和中序数组生成后序数组
vector<int> generateposvectorfromprein(vector<int> pre,vector<int> in)
{
    vector<int> pos;
    if(pre.empty())
    {
        return pos;
    }
    unordered_map<int,int> record;
    for(int i = 0;i<in.size();i++){
        record.insert(make_pair(in[i],i));
    }
    generatevalposprocess(pre, 0, (int)pre.size()-1, in, 0, (int)in.size()-1, record, pos);
    return pos;
}
void generatevalposprocess(vector<int> pre,int pi,int pj,vector<int> in,int ni,int nj,unordered_map<int,int>& record,vector<int>& pos)
{
    if(pi>pj)
        return;
    int head = pre[pi];
    int index = record[pre[pi]];
    generatevalposprocess(pre, pi+1, pi+index-ni, in, ni, index-1, record, pos);
    generatevalposprocess(pre, pi+index-ni+1, pj, in, index+1, nj, record, pos);
    pos.push_back(head);
    return;
}
//20.统计生成所有不同的二叉树
int numbinarytree(int N)
{
    if(N < 2)
        return 1;
    int nums = 0;
    for(int i = 2;i<N;i++)
        nums += numbinarytree(i-1)*numbinarytree(N-i);
    return nums + 2*numbinarytree(N-1);
}
//动态规划
int numstrees(int n)
{
    if(n < 2)
        return 1;
    vector<int> num;
    num.resize(n+1);
    num[0] = 1;
    for(int i = 1;i<n+1;i++){
        for(int j = 1;j<i+1;j++){
            num[i] += num[j-1]*num[i-j];
        }
    }
    return num[n];
}

//21.统计完全二叉树的节点数
returndata recordnumberofnodeforbinarytree(Node* head)
{
    if(head == NULL){
        return returndata(0,0);
    }
    returndata leftdata = recordnumberofnodeforbinarytree(head->left);
    returndata rightdata = recordnumberofnodeforbinarytree(head->right);
    //情况1，右子树最左的节点在最深层
    if(leftdata.lefth == rightdata.lefth){
        leftdata.num = calculatenumber(leftdata.lefth);
    }
    //情况2，右子树最左的节点不在最深层，在次深层
    if(rightdata.lefth == leftdata.lefth-1){
        rightdata.num = calculatenumber(rightdata.lefth);
    }
    return returndata(rightdata.num+leftdata.num+1,leftdata.lefth+1);
}
//满二叉树节点数的计算公式
int calculatenumber(int k)
{
    int ret = 1;
    while(k>0){
        ret = ret*2;
        k--;
    }
    ret--;
    return ret;
}
//22.换钱的最少货币数
int minnumsmoney(vector<int> nums,int aim)
{
    if(aim == 0){
        return 0;
    }
    if(nums.empty()){
        return -1;
    }
    sort(nums.begin(),nums.end(),[](int a,int b){return a > b;});
    int numsmoney = 0;
    for(int i = 0;i<nums.size();i++){
        while(aim >= nums[i]){
            aim -= nums[i];
            ++numsmoney;
        }
        if(aim == 0){
            return numsmoney;
        }
    }
    if(aim != 0){
        return -1;
    }
    return numsmoney;
}
//进阶
int minmumnumsmoneypaper(vector<int> nums,int aim)
{
    if(aim == 0){
        return 0;
    }
    if(nums.empty()){
        return -1;
    }
    sort(nums.begin(),nums.end(),[](int a,int b){return a > b;});
    int numsmoney = 0;
    for(int i = 0;i<nums.size();i++){
        if(aim >= nums[i]){
            aim -= nums[i];
            ++numsmoney;
        }
    }
    if(aim == 0){
        return numsmoney;
    }else{
        return -1;
    }
}
//23.换钱的方法数
//递归
int numspaybackmoney(vector<int>& nums,int aim)
{
    if(aim == 0)
        return 0;
    return numspaybackprocess(nums,0,aim);
}
int numspaybackprocess(vector<int>& nums,int i,int aim)
{
    if(i == nums.size())
        return aim == 0 ? 1 : 0;
    int numbers = 0;
    for(int j = 0;j*nums[i] <= aim;j++){
        numbers += numspaybackprocess(nums,i+1,aim-j*nums[i]);
    }
    return numbers;
}
//动态规划
int dpnumspaybackmoney(vector<int>& nums,int aim)
{
    int** dp = new int*[nums.size()];
    for(int i = 0;i<nums.size();i++){
        dp[i] = new int[aim+1];
    }
    for(int i = 1;i<nums.size();i++){
        dp[i][0] = 1;
    }
    for(int j = 0;j<aim+1;j++){
        dp[0][j] = 0;
    }
    for(int j = 0;j*nums[0]<=aim;j++){
        dp[0][j*nums[0]] = 1;
    }
    for(int i = 1;i<nums.size();i++){
        for(int j = 1;j<aim+1;j++){
            dp[i][j] = dp[i-1][j];
            dp[i][j] += j-nums[i]>= 0? dp[i][j-nums[i]] : 0;
        }
    }
    int res = dp[nums.size()-1][aim];
    for(int i = 0;i<nums.size();i++){
        delete[] dp[i];
    }
    delete[] dp;
    return res;
}
//24.最长递增子序列
//方法1.
vector<int> getdp1(vector<int> nums)
{
    vector<int> dp;
    dp.resize(nums.size());
    for(int i = 0;i<nums.size();i++){
        dp[i] = 1;
        for(int j = 0;j<i;j++){
            if(nums[i] > nums[j]){
                dp[i] = max(dp[i],dp[j]+1);
            }
        }
    }
    return dp;
}
vector<int> generatelis(vector<int> nums,vector<int> dp)
{
    int len = 0;
    int index = 0;
    for(int i = 0;i<dp.size();i++){
        if(dp[i]>len){
            len = dp[i];
            index = i;
        }
    }
    vector<int> lis;
    lis.resize(len);
    lis[--len] = nums[index];
    for(int i = index;i>=0;i--){
        if(nums[i]<nums[index]&&dp[i] == dp[index]-1){
            lis[--len] = nums[i];
            index=i;
        }
    }
    return lis;
}
vector<int> maxlensubindexarray(vector<int> nums)
{
    vector<int> dp = getdp1(nums);
    return generatelis(nums,dp);
}
//25.汉诺塔问题
//递归
void hannuotaproblem(int n,string from,string mid,string to)
{
    if(n == 1){
        cout<<n<<" from "<<from<<" to "<<to<<endl;
        return;
    }
    hannuotaproblem(n-1,from,to,mid);
    cout<<n<<" from "<<from<<" to "<<to<<endl;
    hannuotaproblem(n-1,mid,from,to);
    return;
}
//进阶问题，求数组中此时表示的状态是最有轨迹中的哪一个状态
long long getstateofoptimalmove(vector<int> nums)
{
    if(nums.empty())
        return 0;
    return getstateprocess(nums,(int)nums.size()-1,1,2,3);
}
long long getstateprocess(vector<int>& nums,int i,int from,int mid,int to)
{
    if(i == -1)
        return 0;
    if(nums[i] != from && nums[i] != to){
        return -1;
    }
    if(nums[i] == from){
        return getstateprocess(nums, i-1, from, to, mid);
    }else{
        long long res = getstateprocess(nums, i-1, mid, from, to);
        if(res == -1)
            return -1;
        return (1<<i)+res;
    }
}
//非递归方式
long long getstateoptimalsolution(vector<int>& nums)
{
    if(nums.empty())
        return 0;
    int from = 1;
    int mid = 2;
    int to = 3;
    int i = (int)nums.size()-1;
    int res = 0;
    while(i>=0){
        if(nums[i] == mid)
            return -1;
        if(nums[i] == to){
            res += 1<<i;
            int tmp = from;
            from = mid;
            mid = tmp;
        }else{
            int tmp = to;
            to = mid;
            mid = tmp;
        }
        --i;
    }
    return res;
}
//26.最长公共子序列，经典的动态规划问题
string getmaxlencommonsubarray(string str1,string str2)
{
    int len1 = (int)str1.size();
    int len2 = (int)str2.size();
    int** dp = new int*[len1];
    for(int i = 0;i<len1;i++){
        dp[i] = new int[len2];
    }
    dp[0][0] = str1[0] == str2[0] ? 1 : 0;
    for(int i = 1;i<len1;i++){
        dp[i][0] = str1[i] == str2[0] ? 1 : dp[i-1][0];
    }
    for(int j = 1;j<len2;j++){
        dp[0][j] = str1[0] == str2[j] ? 1 : dp[0][j-1];
    }
    for(int i = 1;i<len1;i++){
        for(int j = 1;j<len2;j++){
            dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            if(str1[i] == str2[j]){
                dp[i][j] = max(dp[i][j],dp[i-1][j-1]+1);
            }
        }
    }
    int i = len1-1;
    int j = len2-1;
    string res;
    while(i>=0 && j>=0){
        if(i>0 && dp[i][j] == dp[i-1][j]){
            --i;
        }else if(j>0 && dp[i][j] == dp[i][j-1]){
            --j;
        }else{
            res += str1[i];
            --i;
            --j;
        }
    }
    reverse(res.begin(),res.end());
    for(int i = 0;i<len2;i++){
        delete[] dp[i];
    }
    delete[] dp;
    return res;
}
//27.最长公共子串
string getmaxlensunstr(string str1,string str2)
{
    int len1 = (int)str1.size();
    int len2 = (int)str2.size();
    int i = len1-1;
    int j = len2-1;
    int curend = 0;
    int curstart = 0;
    int maxend = 0;
    int maxstart = 0;
    while(i>=0){
        if(str1[i] == str2[j]){
            curend = i;
            while(i>=0 && j>=0 && str1[i] == str2[j]){
                --i;
                --j;
            }
            curstart = i+1;
        }else{
            if(maxend - maxstart < curend - curstart){
                maxend = curend;
                maxstart = curstart;
            }
            j = len2-1;
            while(i>=0 && j>=0 && str1[i] != str2[j]){
                --j;
            }
            if(j < 0){
                --i;
                j = len2-1;
            }
        }
    }
    string res;
    i = maxstart;
    while(i<=maxend){
        res += str1[i++];
    }
    return res;
}
//动态规划
string dpgetmaxlensubstr(string str1,string str2)
{
    int len1 = (int)str1.size();
    int len2 = (int)str2.size();
    int** dp = new int*[len1];
    for(int i = 0;i<len1;i++){
        dp[i] = new int[len2];
    }
    dp[0][0] = str1[0] == str2[0] ? 1 : 0;
    int maxindex = dp[0][0];
    int end = 0;
    for(int i = 1;i<len1;i++){
        dp[i][0] = str1[i] == str2[0] ? 1 : 0;
    }
    for(int j = 1;j<len2;j++){
        dp[0][j] = str1[0] == str2[j] ? 1:0;
    }
    for(int i = 1;i<len1;i++){
        for(int j = 1;j<len2;j++){
            if(str1[i] == str2[j]){
                dp[i][j] = dp[i-1][j-1]+1;
            }else{
                dp[i][j] = 0;
            }
            if(maxindex < dp[i][j]){
                maxindex = dp[i][j];
                end = i;
            }
        }
    }
    for(int i = 0;i<len1;i++){
        delete[] dp[i];
    }
    delete[] dp;
    string res;
    int i = end - maxindex + 1;
    while(i <= end){
        res += str1[i++];
    }
    return res;
}
//改进型动态规划
string improvedpgetmaxlensub(string s1,string s2)
{
    int row = 0;
    int col = 0;
    int max = 0;
    int end = 0;
    while(row<s1.size()){
        int i = row;
        int j = col;
        int len = 0;
        while(i<s1.size()&&j<s2.size()){
            if(s1[i] != s2[j]){
                len =0;
            }else{
                len++;
            }
            if(len>max){
                end = i;
                max=len;
            }
            i++;
            j++;
        }
        if(col>0){
            col--;
        }else{
            row++;
        }
    }
    int i = end-max+1;
    string res;
    while(i<=end){
        res+=s1[i++];
    }
    return res;
}
//28.字符串交错组成
bool iscrossstr(string s1,string s2,string s3)
{
    int m = (int)s1.size();
    int n = (int)s2.size();
    int k = (int)s3.size();
    if(k != m+n)
        return false;
    bool dp[m+1][n+1];
    dp[0][0] = true;
    for(int i = 1;i<=m;i++){
        if(dp[i-1][0] && s1[i-1] == s3[i-1]){
            dp[i][0] = true;
        }else{
            dp[i][0] = false;
        }
    }
    for(int j = 1;j<=n;j++){
        if(dp[0][j-1] && s2[j-1] == s3[j-1]){
            dp[0][j] = true;
        }else{
            dp[0][j] = false;
        }
    }
    for(int i = 1;i<=m;i++){
        for(int j = 1;j<=n;j++){
            if(dp[i-1][j] && s1[i-1] == s3[i+j-1]){
                dp[i][j] = true;
            }else if(dp[i][j-1] && s2[j-1] == s3[i+j-1]){
                dp[i][j] = true;
            }else{
                dp[i][j] = false;
            }
        }
    }
    
    return dp[m][n];
}
//29.龙与地下城游戏问题
int getintialblood(vector<vector<int>> dungeon)
{
    if(dungeon.empty()){
        return -1;
    }
    int row = (int)dungeon.size();
    int col = (int)dungeon[0].size();
    if(row == 0 && col == 0){
        return dungeon[row][col]>=0 ? 1:1-dungeon[row][col];
    }
    int dp[row--][col--];
    dp[row][col] = dungeon[row][col]>=1 ? 1 : 1-dungeon[row][col];
    for(int j = col-1;j>=0;j--){
        dp[row][j] = max(dp[row][j+1]-dungeon[row][j],1);
    }
    for(int i = row-1;i>=0;i--){
        dp[i][col] = max(dp[i+1][col]-dungeon[i][col],1);
    }
    int right = 0;
    int left = 0;
    for(int i = row-1;i>=0;i--){
        for(int j = col-1;j>=0;j--){
            right = max(dp[i][j+1]-dungeon[i][j],1);
            left = max(dp[i+1][j]-dungeon[i][j],1);
            dp[i][j] = min(right,left);
        }
    }
    return dp[0][0];
}
//30.数字字符串转换成字母组合的种数
int classesofnumtoword(string number)
{
    if(number[0] == '0'){
        return 0;
    }
    return classesnumprocess2(number,0);
}
int classesnumprocess2(string& str,int i)
{
    if(i==str.size())
        return 1;
    int res = 0;
    if(str[i] >= '1' && str[i] <= '9'){
        res += classesnumprocess2(str,i+1);
    }
    if(i+1 < str.size()){
        int tmp = (str[i]-'0')*10+str[i+1]-'0';
        if(tmp > 0 && tmp <= 26){
            res += classesnumprocess2(str,i+2);
        }
    }
    return res;
}
//动态规划实现
int dpclassesofnumtoword(string number)
{
    if(number[0] == '0')
        return 0;
    int size = (int)number.size();
    int dp[size+1];
    int i = size;
    dp[i--] = 1;
    if(number[i] > '0' && number[i] <= '9'){
        dp[i] = dp[i+1];
    }else{
        dp[i] = 0;
    }
    --i;
    while(i>=0){
        if(number[i] > '0' && number[i] <= '9'){
            dp[i] = dp[i+1];
        }
        if(i+2 <= size && (number[i]-'0')*10+number[i+1]-'0' > 0 && (number[i]-'0')*10+number[i+1]-'0' < 27){
            dp[i] += dp[i+2];
        }
        --i;
    }
    return dp[0];
}
//31.表达式得到期望结果的组成种数
int getnumbersfordesired(string express,bool desired)
{
    if(!isvalid(express))
        return 0;
    return processfordesired(express,desired,0,(int)express.size()-1);
}
bool isvalid(string& str)
{
    if(str.size() % 2 == 0){
        return false;
    }
    for(int i = 0;i<str.size();i++){
        if(i % 2 == 0 && str[i] != '0' && str[i] != '1'){
            return false;
        }
        if(i % 2 == 1 && str[i] != '&' && str[i] != '^' && str[i] != '|'){
            return false;
        }
    }
    return true;
}
int processfordesired(string& str,bool desired,int l,int r)
{
    if(l == r){
        if(str[l] == '1')
            return desired ? 1:0;
        else
            return desired ? 0:1;
    }
    int res = 0;
    if(desired){
        for(int i = l+1;i<=r;i = i+2){
            switch(str[i]){
                case '^':
                    res += processfordesired(str, true, l, i-1)*processfordesired(str, false, i+1, r);
                    res += processfordesired(str, false, l, i-1)*processfordesired(str, true, i+1, r);
                    break;
                case '|':
                    res += processfordesired(str, true, l, i-1)*processfordesired(str, false, i+1, r);
                    res += processfordesired(str, false, l, i-1)*processfordesired(str, true, i+1, r);
                    res += processfordesired(str, true, l, i-1)*processfordesired(str, true, i+1, r);
                    break;
                case '&':
                    res += processfordesired(str, true, l, i-1)*processfordesired(str, true, i+1, r);
                    break;
                default:
                    break;
            }
        }
    }
    else{
        for(int i = l+1;i<=r;i = i+2){
            switch(str[i]){
                case '^':
                    res += processfordesired(str, true, l, i-1)*processfordesired(str, true, i+1, r);
                    res += processfordesired(str, false, l, i-1)*processfordesired(str, false, i+1, r);
                    break;
                case '|':
                    res += processfordesired(str, false, l, i-1)*processfordesired(str, false, i+1, r);
                    break;
                case '&':
                    res += processfordesired(str, true, l, i-1)*processfordesired(str, false, i+1, r);
                    res += processfordesired(str, false, l, i-1)*processfordesired(str, true, i+1, r);
                    res += processfordesired(str, false, l, i-1)*processfordesired(str, false, i+1, r);
                    break;
                default:
                    break;
            }
        }
    }
    return res;
}
//动态规划
int dpgetnumbersfordesired(string express,bool desired)
{
    if(!isvalid(express))
        return 0;
    int size = (int)express.size();
    int t[size][size],f[size][size];
    for(int i = 0;i<size;i++){
        for(int j = 0;j<size;j++){
            t[i][j] = 0;
            f[i][j] = 0;
        }
    }
    t[0][0] = express[0] == '1' ? 1 : 0;
    f[0][0] = express[0] == '0' ? 1 : 0;
    for(int i = 2;i<size;i = i+2){
        t[i][i] = express[i] == '1' ? 1 : 0;
        f[i][i] = express[i] == '0' ? 1 : 0;
        for(int j = i-2;j>=0;j-=2){
            for(int k = j;k<i;k+=2){
                if(express[k+1] == '&'){
                    t[j][i] += t[j][k]*t[k+2][i];
                    f[j][i] += (f[j][k] + t[j][k])*f[k+2][i]+f[j][k]*t[k+2][i];
                }
                else if(express[k+1] == '|'){
                    t[j][i]+=(t[j][k] + f[j][k])*t[k+2][i]+t[j][k]*f[k+2][i];
                    f[j][i]+=f[j][k]*f[k+2][i];
                }
                else{
                    t[j][i]+=t[j][k]*f[k+2][i]+f[j][k]*t[k+2][i];
                    f[j][i]+=f[j][k]*f[k+2][i]+t[j][k]*t[k+2][i];
                }
            }
        }
    }
    return desired ? t[0][size-1] : f[0][size-1];
}
//32.排成一条线的纸牌博弈问题
//递归解决
int first(vector<int>& nums,int l,int r)
{
    if(l == r)
        return nums[l];
    return max(nums[l]+last(nums,l+1,r),nums[r]+last(nums,l,r-1));
}
int last(vector<int>& nums,int l,int r)
{
    if(l == r)
        return 0;
    return min(first(nums, l+1, r),first(nums, l, r-1));
}
int whowinnumbers(vector<int> nums)
{
    if(nums.empty())
        return 0;
    return max(first(nums,0,(int)nums.size()-1),last(nums,0,(int)nums.size()-1));
}
//动态规划
int dpwhowinnumbers(vector<int> nums)
{
    if(nums.empty())
        return 0;
    int size = (int)nums.size();
    int f[size][size],t[size][size];
    for(int j = 0;j<size;j++){
        f[j][j] = nums[j];
        t[j][j] = 0;
        for(int i = j-1;i>=0;--i){
            f[i][j] = max(nums[i]+t[i+1][j],nums[j]+t[i][j-1]);
            t[i][j] = min(f[i+1][j],f[i][j-1]);
        }
    }
    return max(f[0][size-1],t[0][size-1]);
}
//31.跳跃游戏
//递归
int jumpprocess(vector<int>& nums,int i)
{
    if(i >= nums.size()-1)
        return 0;
    int maxval = 0;
    int maxindex = 0;
    for(int j = 1;j <= nums[i];j++){
        if(i+j < nums.size() && maxval <= j+nums[i+j]){
            maxval = nums[i+j];
            maxindex = i+j;
        }
        if(i+j == nums.size()-1){
            return 1;
        }
    }
    return 1+jumpprocess(nums, maxindex);
}
int getminmumjump(vector<int>& nums)
{
    if(nums.empty())
        return 0;
    return jumpprocess(nums,0);
}
//动态规划
int dpjump(vector<int> nums)
{
    if(nums.empty())
        return 0;
    int size = (int)nums.size();
    int dp[size];
    dp[0] = 0;
    int i = 0;
    int maxval = 0;
    int maxindex = 0;
    while(i<size-1){
        maxval = 0;
        for(int j = 1;j<=nums[i];j++){
            if(i+j<size&&maxval<=j+nums[i+j]){
                maxval = j+nums[i+j];
                maxindex = i+j;
            }
            if(i+j == size-1){
                return dp[i]+1;
            }
        }
        dp[maxindex] = dp[i]+1;
        i = maxindex;
    }
    return dp[size-1];
}
//32.数组中的最长连续序列
//直接用排序的思路，随机快排
void quicksortnums(vector<int>& nums,int l,int r)
{
    if(l >= r)
        return;
    swap(nums[rand()%(r-l)+l],nums[r]);
    vector<int>&& res = partitionforquick(nums,l,r);
    quicksortnums(nums,l,res[0]-1);
    quicksortnums(nums, res[1]+1, r);
}
vector<int> partitionforquick(vector<int>& nums,int start,int end)
{
    int less = start-1;
    int more = end;
    while(start<more){
        if(nums[start]<nums[end]){
            swap(nums[++less],nums[start++]);
        }
        else if(nums[start] == nums[end]){
            start++;
        }
        else{
            swap(nums[--more],nums[start]);
        }
    }
    swap(nums[more],nums[end]);
    vector<int> res;
    res.resize(2);
    res[0] = ++less;
    res[1] = more;
    return res;
}
int getmaxlencontinueindex(vector<int>& nums)
{
    if(nums.empty())
        return 0;
    int size = (int)nums.size();
    if(size == 1)
        return 1;
    quicksortnums(nums,0,size-1);
    int dp[size];
    dp[size-1] = 1;
    int maxlen = 1;
    for(int i = size-2;i>=0;i--){
        if(nums[i+1]==nums[i]+1){
            dp[i] = dp[i+1]+1;
        }else{
            dp[i] = 1;
        }
        maxlen = max(maxlen,dp[i]);
    }
    return maxlen;
}
//用哈希表实现复杂度O(N)
int ntimegetmaxlenindex(vector<int>& nums)
{
    if(nums.empty())
        return 0;
    int size = (int)nums.size();
    unordered_set<int> record;
    for(int i = 0;i<size;i++){
        record.insert(nums[i]);
    }
    int maxlen = 0;
    int curlen = 0;
    int curnum = 0;
    unordered_set<int>::iterator rd = record.begin();
    unordered_set<int>::iterator rd1;
    while(rd != record.end()){
        curnum = *rd;
        rd1 = record.find(curnum-1);
        if(rd1 == record.end())
        {
            curlen = 1;
            rd1 = record.find(curnum+1);
            while(rd1 != record.end()){
                curlen++;
                curnum++;
                rd1 = record.find(curnum+1);
            }
            maxlen = max(maxlen,curlen);
        }
        ++rd;
    }
    return maxlen;
}
//33.N皇后问题
int nqueenproblem(int n)
{
    vector<int> queen;
    queen.resize(n);
    for(int i = 0;i<n;i++){
        queen[i] = i;
    }
    return queenprocess(queen,0);
}
int queenprocess(vector<int>& nums,int i)
{
    if(i == nums.size()){
        return isqueen(nums) ? 1 : 0;
    }
    int res = 0;
    for(int j = i; j < nums.size();j++)//是用i与其后面的变量换
    {
        swap(nums[i],nums[j]);
        res += queenprocess(nums,i+1);
        swap(nums[i],nums[j]);
    }
    return res;
}
bool isqueen(vector<int>& nums)
{
    int n = (int)nums.size();
    for(int i =0;i<n;i++){
        for(int j = 0;j<n;j++){
            if(i != j){
                if(i - j == nums[i] - nums[j] || j - i == nums[i] - nums[j])
                    return false;
            }
        }
    }
    return true;
}
//字符串解法
vector<vector<string>> Nqueenproblemstring(int n)
{
    vector<vector<string>> queenstr;
    vector<int> queen;
    vector<vector<int>> queenvec;
    queen.resize(n);
    for(int i = 0;i<n;i++){
        queen[i] = i;
    }
    queenprocessstr(queen,0,queenvec);
    for(int i = 0;i<n;i++){
        vector<string> qv;
        qv.resize(n);
        for(int j = 0;j<n;j++){
            string q(n,'.');
            q[j] = 'Q';
            qv[queenvec[i][j]] = q;
        }
        queenstr.push_back(qv);
    }
    return queenstr;
}
void queenprocessstr(vector<int>& nums,int i,vector<vector<int>>& queen)
{
    if(i == nums.size()){
        if(isqueen(nums)){
            queen.push_back(nums);
        }
        return;
    }
    for(int j=  i;j<nums.size();j++){
        swap(nums[i],nums[j]);
        queenprocessstr(nums,i+1,queen);
        swap(nums[i],nums[j]);
    }
    return;
}
//34.判断两个字符串是否互为变形词
bool isreshapestring(string str1,string str2)
{
    if(str1.size() != str2.size())
        return false;
    unordered_map<char,int> record;
    unordered_map<char,int>::iterator it;
    for(int i = 0;i<str1.size();i++){
        it = record.find(str1[i]);
        if(it == record.end()){
            record.insert(make_pair(str1[i],1));
        }else{
            it->second++;
        }
    }
    for(int i = 0;i<str2.size();i++){
        it = record.find(str2[i]);
        if(it == record.end()){
            return false;
        }else{
            if(it->second <= 0){
                return false;
            }
            it->second--;
            if(it->second == 0){
                record.erase(it);
            }
        }
    }
    if(!record.empty()){
        return false;
    }
    return true;
}
//35.字符串中数字子串的求和
int getsumofnumberstring(string str)
{
    if(str.empty())
        return 0;
    int sum = 0;
    int i = 0;
    int strlen = (int)str.size();
    while(i < strlen){
        if(str[i] == '-'){
            int count = 0;
            while(i < strlen && str[i] == '-'){
                ++count;
                ++i;
            }
            if(count % 2 == 1 && str[i] >= '0' && str[i] <= '9'){
                int temp = 0;
                while(i < strlen && str[i] >= '0' && str[i] <= '9'){
                    temp = temp*10 + str[i++]-'0';
                }
                sum -= temp;
            }
        }
        else if(str[i] > '0' && str[i] <= '9'){
            int temp = 0;
            while(i < strlen && str[i] >= '0' && str[i] <= '9'){
                temp = temp*10 + str[i++]-'0';
            }
            sum += temp;
        }
        else{
            ++i;
        }
    }
    return sum;
}
//36.去掉字符串中连续出现的k个0的子串
string deletekzero(string str,int k)
{
    if(str.empty())
        return str;
    string res;
    int i = 0;
    int strlen = (int)str.size();
    while(i < strlen){
        if(str[i] != '0'){
            res += str[i];
            ++i;
        }
        else{
            int count = 0;
            while(i < strlen && str[i] == '0'){
                ++count;
                ++i;
            }
            if(count == k){
                continue;
            }
            else{
                for(int j = 0;j<count;j++)
                    res += to_string(0);
            }
        }
    }
    return res;
}
//37.判断两个字符串是否互为旋转词
bool isrotateword(string str1,string str2)
{
    if(str1.size() != str2.size())
        return false;
    int strlen = (int)str1.size();
    int i = 0;
    int j = 0;
    int rotateindex = 0;
    while(i < strlen){
        if(str1[i] != str2[j]){
            while(i < strlen && str1[i] != str2[j]){
                i++;
            }
            if(str1[i] == str2[j]){
                rotateindex = i;
                break;
            }
            else{
                return false;
            }
        }
        else{
            while(i<strlen && j<strlen && str1[i] == str2[j]){
                ++i;
                ++j;
            }
            if(i == strlen && j == strlen){
                return true;
            }
            else {
                return false;
            }
        }
    }
    i = rotateindex;
    j = 0;
    while(i<strlen){
        if(str1[i] != str2[j]){
            return false;
        }else{
            ++i;
            ++j;
        }
    }
    i = 0;
    while(i<rotateindex && j < strlen){
        if(str1[i] != str2[j]){
            return false;
        }else{
            ++i;
            ++j;
        }
    }
    
    return true;
}
//38.将整数字符串转成整数值
int numberstringconverttoint(string str)
{
    if(str.empty())
        return 0;
    bool isnegative = false;
    if(str[0] == '-'){
        isnegative = true;
    }
    else if(str[0] > '9' || str[0] <= '0'){
        return 0;
    }
    int strlen = (int)str.size();
    for(int i = 1;i<strlen;i++){
        if(str[i] < '0' || str[i] > '9'){
            return 0;
        }
    }
    string strmin = to_string(INT_MIN);
    string strmax = to_string(INT_MAX);
    if(isnegative && isequal(str,strmin) == 1){
        return 0;
    }
    if(!isnegative && isequal(str,strmax) == 1){
        return 0;
    }
    int i = 0;
    int sum = 0;
    if(isnegative)
        ++i;
    while(i < strlen){
        sum = sum * 10 + str[i] - '0';
        i++;
    }
    if(isnegative)
        sum = -sum;
    return sum;
}
//字符串实现两个整数字符串的大小比较
int isequal(string& str1, string str2)
{
    int str1len = (int)str1.size();
    int str2len = (int)str2.size();
    if(str1len > str2len){
        return 1;
    }
    else if(str1len == str2len){
        for(int i = 0;i<str1len;i++){
            if(str1[i] > str2[i])
                return 1;
            if(str1[i] < str2[i])
                return -1;
        }
        return 0;
    }else{
        return -1;
    }
}
//39.替换字符串中连续出现的制定字符串
string replacestring(string str,string from,string to)
{
    if(str.empty())
        return str;
    string res;
    int strlen = (int)str.size();
    int fromlen = (int)from.size();
    bool iscomfort = false;
    int i = 0;
    int j = 0;
    while(i < strlen){
        j = 0;
        if(str[i] != from[j]){
            if(iscomfort)
            {
                res += to;
                iscomfort = false;
            }
            res += str[i];
            i++;
        }else{
            string temp;
            int k = 0;
            while(i < strlen && k < fromlen){
                temp += str[i];
                k++;
                i++;
            }
            if(temp == from){
                iscomfort = true;
            }
            else{
                res += temp;
            }
        }
    }
    if(iscomfort)
    {
        res += to;
        iscomfort = false;
    }
    return res;
}
//字符串的统计字符串
string countstring(string str)
{
    if(str.empty())
        return str;
    int strlen = (int)str.size();
    string res;
    int i = 0;
    int curcount = 1;
    char curstr = str[i++];
    while(i < strlen){
        if(curstr == str[i]){
            ++curcount;
            ++i;
        }
        else{
            res = res + curstr + '_' + to_string(curcount) + '_';
            curstr = str[i++];
            curcount  = 1;
        }
    }
    res = res + curstr + '_' + to_string(curcount);
    return res;
}
//41.判断字符数组中是否所有的字符都只出现过一次
bool isonlyoncepresent(string str)
{
    if(str.empty())
        return false;
    unordered_map<char, int> record;
    unordered_map<char, int>::iterator it;
    int strlen = (int)str.size();
    int maxlen = 1;
    for(int i = 0 ; i< strlen ; i++){
        it = record.find(str[i]);
        if(it == record.end()){
            record.insert(make_pair(str[i],1));
        }else{
            it->second++;
            maxlen = max(maxlen,it->second);
        }
    }
    if(maxlen > 1){
        return false;
    }else{
        return true;
    }
}
//空间复杂度为O(1)
bool onlyoncepresent(string str)
{
    if(str.empty())
        return false;
    int strlen = (int)str.size();
    for(int i = 0;i<strlen;i++){
        for(int j = i+1;j<strlen;j++){
            if(str[i] == str[j]){
                return false;
            }
        }
    }
    return true;
}
//用快速排序实现
void quicksortforonlyonce(string& str,int l,int r)
{
    if(l<r){
        swap(str[r],str[rand()%(r-l)+l]);
        vector<int>&& res = onlyoncepartition(str, l, r);
        quicksortforonlyonce(str,l,res[0]-1);
        quicksortforonlyonce(str,res[1]+1,r);
    }
}
vector<int> onlyoncepartition(string& str,int start,int end)
{
    int less = start - 1;
    int more = end;
    while(start<more){
        if(str[start] < str[end]){
            swap(str[++less],str[start++]);
        }
        else if(str[start] == str[end]){
            start++;
        }else{
            swap(str[--more],str[start]);
        }
    }
    swap(str[more],str[end]);
    vector<int> res;
    res.resize(2);
    res[0] = less+1;
    res[1] = more;
    return res;
}
bool onlyoncebyquicksort(string str)
{
    if(str.empty())
        return false;
    int strlen = (int)str.size();
    quicksortforonlyonce(str,0,strlen-1);
    char lastchar = str[0];
    for(int i = 1;i<strlen;i++){
        if(str[i] == lastchar){
            return false;
        }
        lastchar = str[i];
    }
    return true;
}
//用堆排序
void strheapinsert(string& str,int index)
{
    while(str[index] > str[(index-1)/2]){
        swap(str[index],str[(index-1)/2]);
        index = (index-1)/2;
    }
}
void strheapify(string& str,int index,int size)
{
    int left = index*2+1;
    while(left < size){
        int maxindex = left+1<size && str[left+1]>str[left] ? left+1 : left;
        maxindex = str[index]>str[maxindex]?index:maxindex;
        if(index == maxindex){
            break;
        }
        swap(str[index],str[maxindex]);
        index = maxindex;
        left = index*2 + 1;
    }
}
void strheapsort(string& str)
{
    int strlen = (int)str.size();
    for(int i = 0;i<strlen;i++){
        strheapinsert(str, i);
    }
    swap(str[0],str[--strlen]);
    while(strlen>0){
        strheapify(str, 0, strlen);
        swap(str[0],str[--strlen]);
    }
    return;
}
bool onlyoncebyheapsort(string& str)
{
    if(str.empty())
        return false;
    strheapsort(str);
    char lastchar = str[0];
    for(int i = 1;i<str.size();i++){
        if(str[i] == lastchar){
            return false;
        }
        lastchar = str[i];
    }
    return true;
}
//42.在有序但是含有空的数组中查找字符串
int findleftindexstr(vector<string>& nums,string str)
{
    if(nums.empty())
        return -1;
    if(str == "0")
        return -1;
    int l = 0;
    int r = (int)nums.size()-1;
    int res = -1;
    while(l<r){
        int mid = l+(r-l)/2;
        if(nums[mid] != "0" && nums[mid] == str){
            res = mid;
            r = mid-1;
        }
        else if(nums[mid] != "0"){
            if(nums[mid] > str){
                r = mid-1;
            }
            else if(nums[mid] < str){
                l = mid+1;
            }
        }
        else{
            int i = mid;
            while(i>=l && nums[i] == "0"){
                --i;
            }
            if(i < l || nums[i] < str){
                l = mid+1;
            }
            else{
                res = nums[i] == str ? i : res;
                r = i-1;
            }
        }
        
    }
    return res;
}
//43.字符串的调整与替换
void findandereplace(char* str)
{
    int strlen = 0;
    int spacecount = 0;
    while(str[strlen] != '\0'){
        if(str[strlen] == ' ')
            ++spacecount;
        ++strlen;
    }
    int strsize = strlen;
    strlen = strlen + spacecount*2;
    while(strsize >= 0){
        if(str[strsize] != ' '){
            str[strlen] = str[strsize];
            strlen--;
        }else{
            str[strlen--] = '0';
            str[strlen--] = '2';
            str[strlen--] = '%';
        }
        strsize--;
    }
    return;
}
//44.翻转字符串
void reversestringword(string& str,int l,int r)
{
    while(l<r){
        swap(str[l],str[r]);
        l++;
        r--;
    }
    return;
}
void reversestringwordbyindex(string& str)
{
    if(str.empty())
        return ;
    int strlen = (int)str.size()-1;
    int l = 0;
    int r = 0;
    for(int i = 0;i<=strlen;i++){
        if(str[i] == ' '){
            reversestringword(str,l,r);
            l = i+1;
        }
        else{
            r = i;
        }
    }
    reversestringword(str,l,r);
    reversestringword(str,0,strlen);
}
//附加题
void movelefttoright(string& str,int size)
{
    if(str.empty())
        return;
    int strlen = (int)str.size()-1;
    reversestringword(str,0,size-1);
    reversestringword(str,size,strlen);
    reversestringword(str,0,strlen);
}
//45.数组中两个字符串的最小距离
int getmindistance(vector<string> strs,string str1,string str2)
{
    if(strs.empty())
        return -1;
    unordered_map<string,int> record;
    unordered_map<string,int>::iterator it1;
    unordered_map<string,int>::iterator it2;
    int strlen = (int)strs.size();
    int minlen = -1;
    for(int i = 0;i<strlen;i++){
        if(strs[i] == str1){
            it1 = record.find(str1);
            if(it1 == record.end()){
                record.insert(make_pair(str1,i));
            }else{
                it1->second = i;
            }
        }
        if(strs[i] == str2){
            it2 = record.find(str2);
            if(it2 == record.end()){
                record.insert(make_pair(str2,i));
            }else{
                it2->second = i;
            }
        }
        it1 = record.find(str1);
        it2 = record.find(str2);
        if(it1 != record.end() && it2 != record.end()){
            if(minlen == -1){
                minlen = abs(it1->second - it2->second);
            }
            else{
                minlen = min(minlen,abs(it1->second - it2->second));
            }
        }
    }
    return minlen;
}
//46.添加最少字符使字符串整体都是回文字符串
string plussharpstringword(string& str)
{
    if(str.empty())
        return str;
    string res;
    int strlen = (int)str.size();
    res += '#';
    for(int i = 0;i<strlen;i++){
        res = res + str[i] + '#';
    }
    return res;
}
string manacherstringwordreturnword(string str)
{
    string&& res = plussharpstringword(str);
    int strlen = (int)res.size();
    int record[strlen];
    int center = -1;
    int right = -1;
    int endlen = 0;
    for(int i = 0;i<strlen;i++){
        record[i] = right > i ? min(record[2*center-i],right-i) : 1;
        while(i+record[i]<strlen && i-record[i]>-1){
            if(res[i+record[i]] == res[i-record[i]]){
                record[i]++;
            }else{
                break;
            }
        }
        if(right < i+record[i]){
            right = i+record[i];
            center = i;
        }
        if(right == strlen){
            endlen = record[i];
            break;
        }
    }
    int size = (int)str.size()-endlen+1;
    if(size <= 0)
        return str;
    else{
        string temp;
        temp.resize(size);
        int len = (int)temp.size();
        for(int i = 0;i<len;i++){
            temp[(len-1-i)] = res[i*2+1];
        }
        return str+temp;
    }
}
//47.括号字符串的有效性和最长有效长度
bool isvalidstringword(string str)
{
    if(str.empty()){
        return true;
    }
    int record = 0;
    int strlen = (int)str.size();
    for(int i = 0;i<strlen;i++){
        switch(str[i]){
            case '(':
                record++;
                break;
            case ')':
                if(record <= 0)
                    return false;
                record--;
                break;
            default:
                if(i < strlen && record == 0){
                    return false;
                }
        }
    }
    if(record == 0)
        return true;
    else
        return false;
}
//补充题目，给定一个括号字符串str,返回最长的有效括号子串
int getmaxlenforvalidinclude(string s)
{
    if(s.empty())
        return 0;
    int strlen = (int)s.size();
    vector<int> dp;
    dp.resize(strlen);
    for(int i = 0;i<strlen;i++){
        dp[i] = 0;
    }
    int pre = 0;
    int maxlen = 0;
    for(int i = 0;i<strlen;i++){
        if(s[i] == ')'){
            pre = i - dp[i-1]-1;
            if(pre>=0 && s[pre] == '('){
                dp[i] = dp[i-1]+2+(pre>0?dp[pre-1]:0);
                maxlen = max(maxlen,dp[i]);
            }
        }
    }
    return maxlen;
}
//48.公式字符串求值
void addnum(deque<string>& record,int num)
{
    if(!record.empty()){
        string top = record.back();
        if(top == "+" || top == "-"){
            ;
        }else{
            record.pop_back();
            string temp = record.back();
            record.pop_back();
            int cur = 0;
            int i = 0;
            bool isneg = false;
            if(temp[i] == '-'){
                isneg = true;
                i++;
            }
            for(;i<temp.size();i++){
                cur = cur*10 + temp[i]-'0';
            }
            if(isneg){
                cur = -cur;
            }
            num = top == "*" ? (cur*num) : (cur/num);
        }
    }
    record.push_back(to_string(num));
}
int getnum(deque<string>& record)
{
    bool positive = true;
    int num = 0;
    while(!record.empty()){
        string tmp = record.front();
        record.pop_front();
        if(tmp == "+"){
            positive = true;
        }else if(tmp == "-"){
            positive = false;
        }else{
            int cur = 0;
            int i = 0;
            bool isneg = false;
            if(tmp[i] == '-'){
                isneg = true;
                i++;
            }
            for(;i<tmp.size();i++){
                cur = cur*10 + tmp[i]-'0';
            }
            if(isneg){
                cur = -cur;
            }
            num += positive ? cur : (-cur);
        }
    }
    return num;
}
vector<int> value(string& str,int i)
{
    deque<string> record;
    int pre = 0;
    while(i < str.size() && str[i] != ')'){
        if(str[i] >= '0' && str[i] <= '9'){
            while(i < str.size() && str[i] >= '0' && str[i] <= '9'){
                pre = pre*10 + str[i++] - '0';
            }
        }
        else if(str[i] != '('){
            addnum(record,pre);
            string s(1,str[i]);
            record.push_back(s);
            i++;
            pre = 0;
        }
        else{
            vector<int> res = value(str,i+1);
            pre = res[0];
            i = res[1]+1;
        }
    }
    addnum(record,pre);
    vector<int> ret;
    ret.resize(2);
    ret[0] = getnum(record);
    ret[1] = i;
    return ret;
}
int getvalue(string& str)
{
    if(str.empty())
        return 0;
    return value(str,0)[0];
}
//49.0左边必有1的二进制字符串数量
int getlenofcomfortvalue(int n)
{
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
    return processgetlencom(n, 0, "");
}
int processgetlencom(int n,int i,string str)
{
    if(i == n){
        return iscomfort(str)?1:0;
    }
    int left = processgetlencom(n,i+1,str+'0');
    int right = processgetlencom(n,i+1,str+'1');
    return left+right;
}
bool iscomfort(string& str)
{
    int count_one = 0;
    for(int i = 0;i<str.size();i++){
        if(str[i] == '0' && count_one == 0){
            return false;
        }
        else if(str[i] == '1'){
            count_one++;
        }else{
            count_one = 0;
        }
    }
    return true;
}
//进阶优化版
long dpgetlenofcomfort(int n)
{
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
    long long pre = 1;
    long long cur = 1;
    long long tmp = 0;
    for(int i = 2;i<=n;i++){
        tmp = cur;
        cur+= pre;
        pre = tmp;
        if(cur > 536870912){
            cur = cur % 536870912;
        }
    }
    return cur;
}
//50.拼接所有字符串产生字典顺序最小的大写字符串
string getmincombinestringword(vector<string> str)
{
    if(str.empty()){
        return NULL;
    }
    if(str.size() == 1){
        return str[0];
    }
    sort(str.begin(),str.end(),compareword());
    string res;
    for(int i = 0;i<str.size();i++){
        res += str[i];
    }
    return res;
}
//51.找到字符串的最长无重复字符子串
int getunrepeatsubstringword(vector<int>& nums,int len)
{
    if(len == 1)
        return 1;
    unordered_map<int,int> record;
    unordered_map<int,int>::iterator it;
    int maxlen = 0;
    int pre = 0;
    for(int i = 0;i<len;i++){
        it = record.find(nums[i]);
        if(it == record.end()){
            record.insert(make_pair(nums[i],i));
            pre++;
        }
        else{
            if(i-pre>it->second){
                pre++;
            }
            else if(i - pre == it->second){
                ;
            }
            else{
                pre = i-it->second;
            }
            it->second = i;
            maxlen = max(maxlen,pre);
        }
    }
    maxlen = max(pre,maxlen);
    return maxlen;
}
//52.找到被指的新类型字符
string getnewtypestringword(string& str,int k)
{
    string res;
    if(str[k-1] >= 'a' && str[k-1] <= 'z'){
        return string(1,str[k-1]);
    }
    else if(str[k-1] >= 'A' && str[k-1] <= 'Z'){
        res += str[k-1];
        res += str[k];
    }
    else{
        return NULL;
    }
    return res;
}
//53.最小包含子串的长度
int getgivenstringwordsunstring(string source,string target)
{
    int strlen1 = (int)source.size();
    int strlen2 = (int)target.size();
    unordered_map<char,int> record;
    unordered_map<char,int>::iterator it;
    int match = 0;
    for(int i = 0;i<strlen2;i++){
        it = record.find(target[i]);
        if(it == record.end()){
            record.insert(make_pair(target[i],1));
        }
        else {
            it->second++;
        }
        match++;
    }
    int l = 0;
    int r = 0;
    int minlen = 2147483647;
    while(r < strlen1 && l<=r){
        if(match > 0){
            it = record.find(source[r]);
            if(it == record.end()){
                record.insert(make_pair(source[r],-1));
            }
            else{
                it->second--;
                match--;
            }
            r++;
        }
        else if(match == 0){
            it = record.find(source[l]);
            if(it->second < 0){
                it->second++;
                l++;
            }
            else if(it->second == 0){
                it->second++;
                minlen = min(minlen,r-l);
                l++;
                match++;
            }
        }
    }
    if(match == 0)
        minlen = min(minlen,r-l);
    if(minlen == 2147483647){
        return 0;
    }
    return minlen;
}
//54.质数与素数问题
//质数计数
int countprimenumber(int n)
{
    if(n < 2)
        return 0;
    int count = 0;
    int i = 2,j = 2;
    for(i = 2;i<n;i++){
        for(j = 2;j<i;j++){
            if(i%j == 0)
                break;
        }
        if(i == j){
            cout<<i<<" ";
            count++;
        }
    }
    cout<<endl;
    return count;
}
//优化版厄尔多塞筛法
int improvecountprimenums(int n)
{
    bitset<1000000> nums;
    nums.set();
    nums[0] = 0;
    nums[1] = 0;
    int count = 0;
    for(int i = 2;i<n;i++){
        if(nums[i]){
            count++;
            for(int j = i+i;j<n;j = j+i){
                nums[j] = 0;
            }
        }
    }
    return count;
}
//报文转换
void baowenconvert(void)
{
    string str;
    getline(cin,str);
    int n = 0;
    int i = 0;
    int strlen = (int)str.size();
    while(i<strlen && str[i] != ' '){
        n = n*10 + str[i++] - '0';
    }
    i++;
    string res;
    while(i<strlen){
        if(str[i] == 'A')//12 34
        {
            n++;
            res = res + "12 34";
        }
        else if(str[i] == 'B')//AB CD
        {
            n++;
            res = res + "AB CD";
        }
        else{
            res += str[i];
        }
        i++;
    }
    cout<<n<<" "<<res<<endl;
}
//质数扩展
int minvalueprimebit(int low,int high)
{
    if(low < 2){
        return 0;
    }
    bitset<1000000> nums;
    nums.set();
    nums[0] = 0;
    nums[1] = 0;
    for(int i = 2;i<high;i++){
        if(nums[i]){
            for(int j = i+i;j<high;j = j+i){
                nums[j] = 0;
            }
        }
    }
    int firstcount = 0;
    int secondcount = 0;
    int temp = 0;
    while(low < high){
        if(nums[low]){
            temp = low;
            if(temp > 0){
                firstcount = firstcount + (temp%10);
                temp = temp/10;
                secondcount = secondcount + (temp%10);
            }
        }
        low++;
    }
    return min(firstcount,secondcount);
}
//转发消息
void converttopeople(void)
{
    string source,size;
    getline(cin,source);
    getline(cin,size);
    int n = 0;
    for(int i = 0;i<size.size();i++){
        n = n*10 + size[i] - '0';
        i++;
    }
    unordered_set<string> record;
    unordered_set<string>::iterator it;
    vector<string> num;
    int count = 1;
    record.insert(source);
    bool isinclude = false;
    for(int i = 0;i<n;i++){
        string temp;
        getline(cin,temp);
        num.push_back(temp);
    }
    vector<string> num1;
    vector<vector<string>> nums;
    for(int i = 0;i<n;i++){
        num.clear();
        isinclude = false;
        string tmp;
        for(int j = 0;j<num[i].size();j++){
            if(num[i][j] == ','){
                num1.push_back(tmp);
                it = record.find(tmp);
                if(it != record.end())
                    isinclude = true;
                tmp.clear();
            }
            else{
                tmp += num[i][j];
            }
        }
        num1.push_back(tmp);
        if(isinclude){
            for(int k = 0;k<num1.size();k++){
                it = record.find(num1[k]);
                if(it == record.end()){
                    record.insert(num1[k]);
                    count++;
                }
            }
        }else{
            nums.push_back(num);
        }
    }
    for(int i = 0;i<nums.size();i++){
        int j = 0;
        for(;j<nums[i].size();j++){
            it = record.find(nums[i][j]);
            if(it != record.end()){
                break;
            }
        }
        if(j != nums[i].size()){
            for(int k = 0;k<nums[i].size();k++){
                it = record.find(nums[i][j]);
                if(it == record.end()){
                    record.insert(nums[i][j]);
                    count++;
                }
            }
        }
    }
    cout<<count<<endl;
}
//55.回文最少分割数
int returnwordmincutnumber(string s)
{
    if(s.size() < 1){
        return 0;
    }
    int strlen = (int)s.size();
    int dp[strlen+1];
    dp[strlen] = -1;
    bool p[strlen][strlen];
    for(int i = 0;i<strlen;i++){
        for(int j = 0;j<strlen;j++){
            p[i][j] = false;
        }
    }
    for(int i = strlen -1 ;i>=0;i--){
        dp[i] = INT_MAX;
        for(int j = i;j<strlen;j++){
            if(s[i] == s[j] && (j-i < 2 || p[i+1][j-1])){
                p[i][j] = true;
                dp[i] = min(dp[i],dp[j+1]+1);
            }
        }
    }
    return dp[0];
}
//56.字符串匹配问题
bool iscomfortstringword(string& str1,string& str2,int i,int j)
{
    if(j == str2.size()){
        return i == str1.size();
    }
    if(j+1 == str2.size() || str2[j+1] != '*'){
        return i != str1.size() && (str2[j] == str1[i] || str2[j] == '.') && iscomfortstringword(str1, str2, i+1, j+1);
    }
    while(i != str1.size() && (str1[i] == str2[j] || str2[j] == '.')){
        if(iscomfortstringword(str1, str2, i, j+2)){
            return true;
        }
        i++;
    }
    return iscomfortstringword(str1, str2, i, j+2);
}
//动态规划
bool isvalidstringword(string& str1,string& str2)
{
    if(str1.empty() && str2.empty()){
        return true;
    }
    for(int i = 0;i<str1.size();i++){
        if(str1[i] == '.' || str1[i] == '*'){
            return false;
        }
    }
    for(int i = 0;i<str2.size();i++){
        if(str2[i] == '*' && (i == 0 || str2[i-1] == '*')){
            return false;
        }
    }
    return true;
}
void initdpcomfortstring(string& str1,string& str2,int** dp)
{
    int strlen1 = (int)str1.size();
    int strlen2 = (int)str2.size();
    dp[strlen1][strlen2] = true;
    for(int i = strlen1-1;i>-1;i--){
        dp[i][strlen2] = false;
        dp[i][strlen2-1] = false;
    }
    for(int j = strlen2-2;j>-1;j = j-2){
        if(str2[j] != '*' && str2[j+1] == '*'){
            dp[strlen1][j] = true;
        }else{
            dp[strlen1][j] = false;
        }
    }
    if(strlen1 > 0 && strlen2 > 0){
        if(str2[strlen2-1] == '.' || str1[strlen1-1] == str2[strlen2-1]){
            dp[strlen1-1][strlen2-1] = true;
        }
    }
}
bool idmatchdp(string& str1,string& str2)
{
    if(str1.empty() && str2.empty())
        return true;
    if(!isvalidstringword(str1,str2)){
        return false;
    }
    int strlen1 = (int)str1.size();
    int strlen2 = (int)str2.size();
    int** dp = new int*[strlen1+1];
    for(int i  = 0;i<=strlen1;i++){
        dp[i] = new int[strlen2+1];
    }
    initdpcomfortstring(str1,str2,dp);
    for(int i = strlen1-1;i>-1;i--){
        for(int j = strlen2-2;j>-1;j--){
            if(str2[j] != '*'){
                dp[i][j] = (str1[i] == str2[j] || str2[j] == '.')&&dp[i+1][j+1];
            }else{
                int k = i;
                while(k != strlen1 && (str1[i] == str2[j] || str2[j] == '.')){
                    if(dp[i][j+2]){
                        dp[i][j] = true;
                        break;
                    }
                    k++;
                }
                if(!dp[i][j]){
                    dp[i][j] = dp[i][j-2];
                }
            }
        }
    }
    return true;
}
//58.不用额外变量交换两个整数的值
void changethetwoint(int& a,int& b)
{
    a = a^b;
    b = a^b;
    a = a^b;
    return;
}
//59.不用任何比较判断找出两个数中较大的数
int myflip(int n)
{
    return n^1;
}
int mysign(int n)
{
    return myflip((n>>31)&1);
}
int getmaxvaluebetweentwoint(int& a,int& b)
{
    int c = a-b;
    int sca = mysign(c);
    int scb = myflip(sca);
    return a*sca+b*scb;
}
//60.只用位运算不用算术运算实现整数的加减乘除运算
int summarybitversion(int a,int b)
{
    int sum = a;
    while(b != 0){
        sum = a^b;
        b=  (a&b)<<1;
        a = sum;
    }
    return sum;
}
int subbitversion(int a,int b)
{
    int tmp = summarybitversion(~b, 1);
    return summarybitversion(a, tmp);
}
int plusbitversion(int a,int b)
{
    int res = 0;
    int two = 1;
    bitset<32> bbit(b);
    for(int i = 0;i<32;i++){
        if(bbit.test(i)){
            res += a*two;
        }
        two = two*2;
    }
    return res;
}
int dividebitversion(int a,int b)
{
    bool isapos = (a<0);
    bool isbpos = (b<0);
    int x = isapos ? -a:a;
    int y = isbpos ? -b:b;
    int res = 0;
    for(int i = 31;i>-1;i = plusbitversion(i, 1)){
        if((x>>i) >= y){
            res |= (1<<i);
            x = plusbitversion(x, y<<i);
        }
    }
    return isapos^isbpos ? -res : res;
}
//61.整数的二进制表达式中有多少个1
int getnumsoftheint(int n)
{
    bitset<32> nbit(n);
    int res = (int)(nbit.count());
    return res;
}
//62.a在其他数都出现偶数次的数组中找到出现奇数次的数
//只有一个出现奇数次
int findoddnumberofint(vector<int> nums)
{
    int res = nums[0];
    for(int i = 1;i<nums.size();i++){
        res = res^nums[i];
    }
    return res;
}
//有两个数出现奇数次
vector<int> findtwooddnumbersofint(vector<int> nums)
{
    int res = nums[0];
    for(int i = 1;i<nums.size();i++){
        res = res^nums[i];
    }
    bitset<32> resbit(res);
    int i = 0;
    int tmp = 1;
    for(;i<32;i++){
        if(resbit.test(i)){
            break;
        }
        tmp = tmp<<1;
    }
    int firstnum = 0;
    for(int j = 0;j<nums.size();j++){
        if((nums[j] & tmp) == 1){
            firstnum = nums[j];
            break;
        }
    }
    int secondnum = res^firstnum;
    vector<int> resvec;
    resvec.resize(2);
    resvec[0] = firstnum;
    resvec[1] = secondnum;
    return resvec;
}
//63.在其他数都出现K次的数组中找到只出现一次的数
//把单个数转换为K进制的数
vector<int> getchangeknums(int num,int& k)
{
    vector<int> res;
    while(k != 0){
        res.push_back(num%k);
        num = num/k;
    }
    return res;
}
int findoncepresentnums(vector<int>& nums,int k)
{
    if(k == 1){
        return nums[0];
    }
    if(k%2 == 0){
        int res = nums[0];
        for(int i = 1;i<nums.size();i++){
            res = res^nums[i];
        }
        return res;
    }
    else{
        int len = (int)nums.size();
        vector<int> res(len,0);
        for(int i = 0;i<nums.size();i++){
            vector<int> temp = getchangeknums(nums[i],k);
            for(int j = 0;j<temp.size();j++){
                res[j]  = res[j] + temp[j];
            }
        }
        int ret = 0;
        for(int i = 0;i<len;i++){
            res[i] = res[i]%k;
            ret = ret*k + res[i];
        }
        return ret;
    }
}
//64.转圈打印矩阵
void printcyclematrix(vector<vector<int>>& matrix)
{
    int row0 = 0;
    int col0 = 0;
    int row1 = (int)matrix.size()-1;
    int col1 = (int)matrix[0].size()-1;
    while(row0 <= row1 && col0 <= col1){
        processprintcyclematrix(matrix,row0++,col0++,row1--,col1--);
    }
    cout<<endl;
    return;
}
void processprintcyclematrix(vector<vector<int>>& matrix,int row0,int col0,int row1,int col1)
{
    if(row0 == row1){
        for(int j = col0;j<col1;j++){
            cout<<matrix[row0][j]<<" ";
        }
    }
    else if(col0 == col1){
        for(int i = row0;i<row1;i++){
            cout<<matrix[i][col0]<<" ";
        }
    }
    else{
        int i = row0;
        int j = col0;
        while(j < col1){
            cout<<matrix[i][j++]<<" ";
        }
        while(i<row1){
            cout<<matrix[i++][j]<<" ";
        }
        while(j>col0){
            cout<<matrix[i][j--]<<" ";
        }
        while(i>row0){
            cout<<matrix[i--][j]<<" ";
        }
    }
    
}
//65.将正方形矩阵顺时针转动90度
void transpositionmatrix(vector<vector<int>>& matrix)
{
    int row = (int)matrix.size()-1;
    int col = (int)matrix[0].size()-1;
    int row0 = 0;
    int col0 = 0;
    while(row0 < row){
        processtranspositionmatrix(matrix,row0++,col0++,row--,col--);
    }
    return;
}
void processtranspositionmatrix(vector<vector<int>>& matrix,int row0,int col0,int row1,int col1)
{
    int times = col1 - col0;
    for(int i  =0;i<times;i++){
        int temp = matrix[row0][col0+i];
        matrix[row0][col0+i] = matrix[row1-i][col0];
        matrix[row1-i][col0] = matrix[row1][col1-i];
        matrix[row1][col1-i] = matrix[row0+i][col1];
        matrix[row0+i][col1] = temp;
    }
    return;
}
//66.之字形打印矩阵
void printzigzagmatrix(vector<vector<int>>& matrix)
{
    bool istoptobottom = true;
    int toprow = 0;
    int topcol = 0;
    int maxrow = (int)matrix.size()-1;
    int maxcol = (int)matrix[0].size()-1;
    int botrow = 0;
    int botcol = 0;
    while(toprow<=maxrow && topcol <= maxcol && botrow <= maxrow && botcol <= maxcol){
        processprintzigzagmatrix(matrix,istoptobottom,toprow,topcol,botrow,botcol);
        toprow = topcol == maxcol ? toprow+1:toprow;
        topcol = topcol == maxcol ? topcol:topcol+1;
        botcol = botrow == maxrow ? botcol+1:botcol;
        botrow = botrow == maxrow ? botrow:botrow+1;
        istoptobottom = !istoptobottom;
    }
}
void processprintzigzagmatrix(vector<vector<int>>& matrix,bool istoptobottom,int toprow,int topcol,int botrow,int botcol)
{
    if(istoptobottom){
        while(toprow <= botrow && topcol >= botcol){
            cout<<matrix[toprow++][topcol--]<<" ";
        }
    }
    else{
        while(toprow <= botrow && topcol >= botcol){
            cout<<matrix[botrow--][botcol++]<<" ";
        }
    }
}
//67.找到无序数组中最小的K个数
vector<int> getlessknumbers(vector<int>& nums,int k)
{
    vector<int> res;
    res.resize(k);
    improvequicksort(nums,k-1,0,(int)nums.size()-1);
    for(int i = 0;i<k;i++){
        res[i] = nums[i];
    }
    return res;
}
void improvequicksort(vector<int>& nums,int k,int l,int r)
{
    if(l<r){
        int mid = rand()%(r-l) + l;
        swap(nums[mid],nums[r]);
        vector<int>&& res = improvepartition(nums,l,r);
        if(res[0]>k){
            improvequicksort(nums,k,l,res[0]-1);
        }
        else if(res[1]<k){
            improvequicksort(nums,k,res[0]+1,r);
        }
        else{
            return;
        }
    }
               return;
}
vector<int> improvepartition(vector<int>& nums,int start,int end)
{
    int less = start-1;
    int more = end;
    while(start<more){
        if(nums[start] < nums[end]){
            swap(nums[++less],nums[start++]);
        }
        else if(nums[start] == nums[end]){
            start++;
        }
        else {
            swap(nums[--more],nums[start]);
        }
    }
    swap(nums[more],nums[end]);
    vector<int> res;
    res.resize(2);
    res[0] = less+1;
    res[1] = more;
    return res;
}
//68.需要排序的最短子数组长度
int needsortnumbers(vector<int>& nums)
{
    int nominindex = -1;
    int numslen = (int)nums.size();
    int minval = nums[numslen-1];
    for(int i = numslen-2;i>-1;i--){
        if(nums[i]>minval){
            nominindex = i;
        }
        minval = min(minval,nums[i]);
    }
    if(nominindex == -1){
        return 0;
    }
    int nomaxindex = -1;
    int maxval = nums[0];
    for(int i = 1;i<numslen;i++){
        if(nums[i]<maxval){
            nomaxindex = i;
        }
        maxval = max(maxval,nums[i]);
    }
    return nomaxindex-nominindex+1;
}
//69.在数组中找到出现次数大于N/K的数
int getnumberofvector(vector<int>& nums)
{
    if(nums.empty())
        return -1;
    int numslen = (int)nums.size();
    int last = nums[0];
    int continuenum = 0;
    int count = 1;
    int maxcount = 0;
    int maxnum = 0;
    for(int i =1;i<numslen;i++){
        if(last == nums[i]){
            continuenum = last;
            count++;
        }
        else {
            if(maxcount < count){
                maxcount = count;
                maxnum = continuenum;
            }
            count = 1;
        }
        last = nums[i];
    }
    if(maxcount < count){
        maxcount = count;
        maxnum = continuenum;
    }
    count = 0;
    for(int i = 0;i<numslen;i++){
        if(nums[i] == maxnum){
            count++;
        }
    }
    if(count > numslen/2){
        return maxnum;
    }
    return -1;
}
//进阶，给定一个整形数组，在给定一个整数K，打印所有出现次数大于N/K的数，如果没有输出-1
void printgreaternknumbers(map<int,int>& nums,int n,int k)
{
    int p = n/k;
    bool hasprint = false;
    for(auto c = nums.begin();c != nums.end();c++){
        if(c->second > p){
            hasprint = true;
            cout<<c->first<<" ";
        }
    }
    if(!hasprint){
        cout<<-1<<endl;
    }
    else{
        cout<<endl;
    }
    return;
}
//70.在行列都排好序的矩阵中找数
bool isincludematrix(vector<vector<int>>& matrix,int n,int m,int k)
{
    if(matrix.empty())
        return false;
    int row = n-1;
    int col = m-1;
    int i = 0;
    int j = col;
    while(i>=0&&i<=row&&j>=0&&j<=col){
        if(matrix[i][j] == k){
            return true;
        }
        else if(matrix[i][j] > k){
            j--;
        }
        else if(matrix[i][j] < k){
            i++;
        }
    }
    return false;
}
//71.最长的可整合子数组的长度
int maxlencouldmergearray(vector<int>& nums)
{
    sort(nums.begin(),nums.end());
    int numslen = (int)nums.size();
    int maxlen = 0;
    int curlen = 1;
    int last = nums[0];
    for(int i = 1;i<numslen;i++){
        if(nums[i]-last == 1){
            curlen++;
        }
        else if(nums[i] == last){
            ;
        }
        else {
            maxlen = max(maxlen,curlen);
            curlen = 1;
        }
        last = nums[i];
    }
    maxlen = max(maxlen,curlen);
    return maxlen;
}
//72.不重复打印排序数组中相加和为给定值的所有二元组和三元组
void doublefactorarray(vector<int>& nums,int k)
{
    int l = 0;
    int r = (int)nums.size()-1;
    while(l<r){
        if(nums[l]+nums[r] == k){
            if(l == 0 || nums[l-1] != nums[l]){
                cout<<nums[l]<<" "<<nums[r]<<endl;
            }
            l++;
            r--;
        }
        else if(nums[l]+nums[r] < k){
            l++;
        }
        else{
            r--;
        }
    }
}
//三元组
void printhreeuniquethrid(vector<int>& nums,int k)
{
    if(nums.empty())
        return;
    int numslen = (int)nums.size();
    for(int i = 0;i<numslen;i++){
        if(i == 0 || nums[i] != nums[i-1]){
            printrestdoublefactor(nums,i,i+1,numslen-1,k-nums[i]);
        }
    }
}
void printrestdoublefactor(vector<int>& nums,int f,int l,int r,int k)
{
    while(l<r){
        if(nums[l]+nums[r] > k){
            r--;
        }
        else if(nums[l]+nums[r] < k){
            l++;
        }
        else{
            if(l == f+1 || nums[l] != nums[l-1]){
                cout<<nums[f]<<" "<<nums[l]<<" "<<nums[r]<<endl;
            }
            l++;
            r--;
        }
    }
}
//73.未排序的正数数组中累加和为给定值的最长子数组的长度
int getmaxlensubarray(vector<int>& nums,int k)
{
    int numslen = (int)nums.size();
    int maxlen = 0;
    int l = 0;
    int r = 0;
    int cursum = nums[0];
    while(r < numslen){
        if(cursum < k){
            r++;
            if(r == numslen){
                break;
            }
            cursum += nums[r];
        }
        else if(cursum > k){
            cursum -= nums[l];
            l++;
        }
        else {
            maxlen = max(maxlen,r-l+1);
            cursum -= nums[l];
            l++;
        }
    }
    return maxlen;
}
//74.未排序数组中累加和为给定值的最长子数组系列问题
int getmaxlengthsubarraysolutions(vector<int>& nums,int k)
{
    unordered_map<int,int> record;
    unordered_map<int,int>::iterator it;
    unordered_map<int,int>::iterator it1;
    int cursum = 0;
    int maxlen = 0;
    int numslen = (int)nums.size();
    record.insert(make_pair(0,-1));
    for(int i =0;i<numslen;i++){
        cursum += nums[i];
        it = record.find(cursum);
        if(it == record.end()){
            record.insert(make_pair(cursum,i));
        }
        it1 = record.find(cursum - k);
        if(it1 != record.end()){
            maxlen = max(maxlen,i - it1->second);
        }
    }
    return maxlen;
}
//75.未排序数组中累加和小于等于给定值的最长子数组长度
int getmaxlengthlessksunarray(vector<int>& nums,int k)
{
    int maxlen = 0;
    int cursum = 0;
    int maxsum = 0;
    int numslen = (int)nums.size();
    vector<int> sum,leftmax;
    sum.push_back(0);
    leftmax.push_back(0);
    for(int i = 0;i<numslen;i++){
        cursum += nums[i];
        sum.push_back(cursum);
        maxsum = max(maxsum,cursum);
        leftmax.push_back(maxsum);
        int diff = cursum - k;
        int l = 0;
        int r = i;
        while(l<r){
            int mid = l+(r-l)/2;
            if(leftmax[mid] < diff){
                l = mid+1;
            }
            else if(leftmax[mid] > diff){
                r = mid-1;
            }
            else{
                r = mid;
            }
        }
        maxlen = max(maxlen,i-l+1);
    }
    
    return maxlen;
}
//76.计算数组的小和
int getminsumarray(vector<int>& nums)
{
    int numslen = (int)nums.size()-1;
    return mergersortminsum(nums,0,numslen);
}
int mergersortminsum(vector<int>& nums,int l,int r)
{
    if(l==r)
        return 0;
    int mid = l+(r-l)/2;
    return mergersortminsum(nums,l,mid)+mergersortminsum(nums,mid+1,r)+processmergerminsum(nums,l,mid,r);
}
int processmergerminsum(vector<int>& nums,int l,int mid,int r)
{
    int res = 0;
    int p1 = l;
    int p2 = mid+1;
    vector<int> help;
    while(p1<=mid && p2<=r){
        res+=nums[p1]<=nums[p2]?(r-p2+1)*nums[p1]:0;
        help.push_back(nums[p1]<=nums[p2]?nums[p1++]:nums[p2++]);
    }
    while(p1<=mid){
        help.push_back(nums[p1++]);
    }
    while(p2<=r){
        help.push_back(nums[p2++]);
    }
    for(int i = 0;i<help.size();i++){
        nums[l+i] = help[i];
    }
    return res;
}
//77.自然数数组的排序
void naturenumbersort(vector<int>& nums,int n)
{
    if(n <= 1)
        return;
    int index = 0;
    for(int i = 0;i<n;i++){
        if(nums[i] != i+1){
            index = nums[i]-1;
            swap(nums[i],nums[index]);
        }
    }
    for(int i = 0;i<n;i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;
    return;
}
//78.奇数下标都是奇数或者偶数下标都是偶数
void oddarragearray(vector<int>& nums,int n)
{
    int oddcount = 0;
    for(int i = 0;i<n;i++){
        if(nums[i]%2 == 0)
            oddcount++;
    }
    if(oddcount > n/2){
        int i = 0;
        int j = 1;
        while(i<n && j<n){
            if(nums[i]%2 != 0){
                while(j<n && nums[j]%2 != 0){
                    j = j+2;
                }
                swap(nums[i],nums[j]);
            }
            i = i+2;
        }
    }
    else{
        int i = 0;
        int j = 1;
        while(i<n && j<n){
            if(nums[j]%2 == 0){
                while(i<n && nums[i]%2 == 0){
                    i = i+2;
                }
                swap(nums[j],nums[i]);
            }
            j = j+2;
        }
    }
    for(int i = 0;i<n;i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;
}
//79.子数组的最大累加和问题
int getmaxsumofarray(vector<int>& nums)
{
    if(nums.empty())
        return 0;
    int maxsum = 0;
    int lastsum = 0;
    int numslen = (int)nums.size();
    for(int i = 0;i<numslen;i++){
        if(lastsum + nums[i] > nums[i]){
            lastsum += nums[i];
        }
        else{
            lastsum = nums[i];
        }
        maxsum = max(maxsum,lastsum);
    }
    maxsum = max(maxsum,lastsum);
    return maxsum;
}
//80.子矩阵的最大累加和问题
int getmaxsumofmatrix(vector<vector<int>>& matrix,int m,int n)
{
    int row = m;
    int col = n;
    vector<int> result;
    result.resize(col);
    int maxsum = 0;
    int cursum = 0;
    for(int i = 0;i<row;i++){
        result.clear();
        result.resize(col);
        for(int k = 0;k<col;k++){
            result[k] = 0;
        }
        for(int j = i;j<row;j++){
            for(int k = 0;k<col;k++){
                result[k] += matrix[j][k];
            }
            cursum = 0;
            for(int k = 0;k<col;k++){
                if(cursum>=0){
                    cursum += result[k];
                }
                else{
                    cursum = result[k];
                }
                maxsum = max(maxsum,cursum);
            }
        }
    }
    return maxsum;
}
//81.在数组中找到一个局部最小的位置
int getpartminindex(vector<int>& nums)
{
    if(nums.empty())
        return -1;
    int numslen = (int)nums.size();
    if(numslen == 1 || nums[0]<nums[1])
        return 0;
    if(nums[numslen-1]<nums[numslen-2])
        return numslen-1;
    int index = -1;
    int l = 0;
    int r = numslen-1;
    while(l<r){
        int mid = l+(r-l)/2;
        if(nums[mid] > nums[mid-1]){
            r = mid-1;
        }
        else if(nums[mid]>nums[mid+1]){
            l = mid+1;
        }
        else{
            index = mid;
            break;
        }
    }
    return index;
}

//82.数组中子数组的最大累乘积
double getmaxsummultisubarray(vector<double>& nums,int& n)
{
    if(n == 0)
        return 0;
    double mincur = nums[0];
    double maxcur = nums[0];
    double maxmulti = 0;
    double curmax = 0;
    double curmin = 0;
    for(int i = 1;i<n;i++){
        curmax = maxcur*nums[i];
        curmin = mincur*nums[i];
        maxcur = max(max(curmax,curmin),nums[i]);
        mincur = min(min(curmin,curmax),nums[i]);
        maxmulti = max(maxmulti,maxcur);
    }
    printf("%.2lf\n", maxmulti);
    return maxmulti;
}
//83.打印N个数组整体最大的Top K
void printtopknumbersarray(vector<int>& nums,int k)
{
    heapsortfortopk(nums,k);
}
void heapsortfortopk(vector<int>& nums,int k)
{
    int numslen = (int)nums.size();
    for(int i = 1;i<numslen;i++){
        rearrangeindexheapsort(nums,i);
    }
    if(numslen < k){
        k = numslen;
    }
    cout<<nums[0]<<" ";
    swap(nums[0],nums[numslen-1]);
    for(int i = 1;i<k;i++){
        heapifyfortopk(nums,0,numslen-i);
        cout<<nums[0]<<" ";
        swap(nums[0],nums[numslen-i-1]);
    }
    cout<<endl;
}
void rearrangeindexheapsort(vector<int>& nums,int index)
{
    while(index>-1 && nums[index] > nums[(index-1)/2]){
        swap(nums[index] , nums[(index-1)/2]);
        index = (index-1)/2;
    }
}
void heapifyfortopk(vector<int>& nums,int index,int r)
{
    int left = 2*index+1;
    while(left<r){
        int maxindex = left+1<r && nums[left+1]>nums[left]?left+1:left;
        maxindex = nums[maxindex]>nums[index]?maxindex:index;
        if(maxindex == index){
            return;
        }
        swap(nums[maxindex],nums[index]);
        index = maxindex;
        left = 2*index+1;
    }
}
//84.边界都是1的最大正方形的大小
int getmaxsquaresize(vector<vector<int>>& grid)
{
    int r = (int)grid.size();
    int c = (int)grid[0].size();
    int ans = 0;
    int edgs[100][100][4];
    
    /*left*/
    for(int i = 0;i < r; ++i){
        int left = 0;
        for(int j = 0;j < c; ++j){
            if(grid[i][j] == 1){
                left++;
            }else{
                left = 0;
            }
            edgs[i][j][0] = left;
        }
    }
    /*right*/
    for(int i = 0;i < r; ++i){
        int right = 0;
        for(int j = c-1;j >= 0; --j){
            if(grid[i][j] == 1){
                right++;
            }else{
                right = 0;
            }
            edgs[i][j][1] = right;
        }
    }
    /*up*/
    for(int j = 0;j < c; ++j){
        int up = 0;
        for(int i = 0;i < r; ++i){
            if(grid[i][j] == 1){
                up++;
            }else{
                up = 0;
            }
            edgs[i][j][2] = up;
        }
    }
    /*down*/
    for(int j = 0;j < c; ++j){
        int down = 0;
        for(int i = r-1;i >= 0; --i){
            if(grid[i][j] == 1){
                down++;
            }else{
                down = 0;
            }
            edgs[i][j][3] = down;
        }
    }
    
    for(int i = 0;i < r; ++i){
        for(int j = 0;j < c; ++j){
            for(int k = edgs[i][j][3] - 1; k >= 0 ; --k){
                if((i+k) < r && (j+k) < c){
                    if(edgs[i][j][1] > k &&
                       edgs[i+k][j+k][2] > k &&
                       edgs[i+k][j+k][0] > k){
                        ans = max(ans,(k+1)*(k+1));
                        break;
                    }
                }
            }
        }
    }
    
    return ans;
}
//85.不包含本位置值的累乘数组
vector<int> getsumnultiarray(vector<int>& nums,int n,int k)
{
    vector<int> res;
    res.resize(n);
    int totalmulti = 1;
    for(int i = 0;i<n;i++){
        totalmulti = totalmulti*nums[i];
    }
    for(int i = 0;i<n;i++){
        res[i] = (totalmulti/nums[i])%k;
    }
    return res;
}
//86.数组的partition调整
void arraypartition(vector<int>& nums,int n)
{
    int i = 0;
    int j = 1;
    while(j<n && i<=(n+1)/2){
        if(nums[j] != nums[i]){
            swap(nums[++i],nums[j]);
        }
        j++;
    }
}
//87.求最短通路径
int getmindistancepath(vector<vector<int>>& matrix,int m,int n)
{
    if(m < 1 || n< 1){
        return 0;
    }
    int res = 0;
    vector<vector<int>> map;
    vector<int> temp;
    for(int i = 0;i<m;i++){
        temp.clear();
        temp.resize(n);
        for(int j = 0;j<n;j++){
            temp[j] = 0;
        }
        map.push_back(temp);
    }
    map[0][0] = 1;
    queue<int> rq,cq;
    rq.push(0);
    cq.push(0);
    int r = 0;
    int c = 0;
    while(!rq.empty()){
        r = rq.front();
        rq.pop();
        c = cq.front();
        cq.pop();
        if(r == m-1 && c == n-1){
            res = map[r][c];
            break;
        }
        processmindistancepath(map[r][c],r-1,c,matrix,map,rq,cq);
        processmindistancepath(map[r][c],r+1,c,matrix,map,rq,cq);
        processmindistancepath(map[r][c],r,c-1,matrix,map,rq,cq);
        processmindistancepath(map[r][c],r,c+1,matrix,map,rq,cq);
    }
    return res;
}
void processmindistancepath(int pre,int tor,int toc,vector<vector<int>>& matrix,vector<vector<int>>& map,queue<int>& rq,queue<int>& cq){
    if(tor < 0 || tor == matrix.size() || toc < 0 || toc == matrix[0].size() || matrix[tor][toc] != 1 || map[tor][toc] != 0){
        return;
    }
    map[tor][toc] = pre+1;
    rq.push(tor);
    cq.push(toc);
}
//88.数组中未出现的最小正整数
int getminposintnumber(vector<int>& nums,int len)
{
    int poscount = 0;
    int minpos = INT_MAX;
    int maxpos = INT_MIN;
    for(int i = 0;i<len;i++){
        if(nums[i]>0){
            minpos = min(minpos,nums[i]);
            maxpos = max(maxpos,nums[i]);
            poscount++;
        }
    }
    if(minpos > 1)
        return 1;
    int i = 0;
    while(i<len){
        if(nums[i]>0 && nums[i]<len && nums[i] != i+1){
            swap(nums[i],nums[nums[i]-1]);
        }
        i++;
    }
    int res = INT_MAX;
    for(int j = 0;j<len;j++){
        if(nums[j]>0 && nums[j] != j+1){
            res = min(res,j+1);
        }
    }
    if(res == INT_MAX){
        return len+1;
    }
    return res;
}
//89.数组排序后相邻数的最大差值,桶排序思想
int getmaxdifferencearraynums(vector<int>& nums,int n)
{
    if(n <= 1)
        return 0;
    int maxval = INT_MIN;
    int minval = INT_MAX;
    for(int i = 0;i<n;i++){
        maxval = max(maxval,nums[i]);
        minval = min(minval,nums[i]);
    }
    if(maxval == minval){
        return 0;
    }
    vector<int> maxbucket,minbucket;
    vector<bool> isinbucket;
    maxbucket.resize(n+1);
    minbucket.resize(n+1);
    isinbucket.resize(n+1);
    for(int i = 0;i<n+1;i++){
        isinbucket[i] = false;
    }
    for(int i = 0;i<n;i++){
        int index = (int)((nums[i]-minval)*n)/(maxval-minval);
        maxbucket[index] = isinbucket[index]? max(maxbucket[index],nums[i]) : nums[i];
        minbucket[index] = isinbucket[index]? min(minbucket[index],nums[i]) : nums[i];
        isinbucket[index] = true;
    }
    int maxdiff = 0;
    int lastval = minval;
    for(int i = 0;i<n+1;i++){
        if(isinbucket[i]){
            maxdiff = max(maxdiff,minbucket[i]-lastval);
            maxdiff = max(maxdiff,maxbucket[i]-minbucket[i]);
            lastval = maxbucket[i];
        }
    }
    return maxdiff;
}
//
ListNode* mergeprocess(vector<ListNode*>& lists,int begin,int end) {
    if (end < begin) return NULL;
    if (end == begin) return lists[begin];
    
    int mid = (begin + end) / 2;
    auto p1 = mergeprocess(lists, begin, mid);
    auto p2 = mergeprocess(lists, mid + 1, end);
    
    ListNode head(0);
    ListNode* cur = &head;
    while (p1 && p2) {
        if (p1->val < p2->val) {
            cur->next = p1;
            p1 = p1->next;
        } else {
            cur->next = p2;
            p2 = p2->next;
        }
        cur = cur->next;
    }
    
    if (p1) cur->next = p1;
    else if (p2) cur->next = p2;
    return head.next;
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    return mergeprocess(lists, 0, (int)lists.size() - 1);
}

//90.从5随机到7随机及其扩展
int rand1to5()
{
    return (int)(rand()%5)+1;
}
int rand1to7()
{
    int res = (rand1to5()-1)*5 + (rand1to5()-1);
    while(res > 20){
        res = (rand1to5()-1)*5 + (rand1to5()-1);
    }
    res = res%7;
    res = res+1;
    return res;
}
//补充题目 给定一个以p概率产生0，以1-p概率产生1的c随机函数rand01p如下:
int rand01p(double p = 0.83){
    return rand()%2 < p ? 0:1;
}
int rand0to3()
{
    return rand01p(0.5)*2+rand01p(0.5);
}
int rand1to6()
{
    int res = rand0to3()*4+rand0to3();
    while(res>11){
        res = rand0to3()*4+rand0to3();
    }
    return res%6+1;
}
//91.一行代码求两个数的最大公约数
//如果q和r分别是m除以n的商及余数，即m=nq+r,那么m和n的最大公约数等于n和r的最大公约数
int gcd(int m,int n)
{
    return n == 0 ? m : gcd(n,(m%n));
}
//92.有关阶乘的两个问题
long resultzeronumbers(int n)
{
    int sum = 0;
    for(int i = 1;i<=n;i++){
        int temp = i;
        while(temp%5 == 0){
            sum++;
            temp = temp/5;
        }
    }
    return sum;
}
long resultzeronumbers2(int n)
{
    int sum = 0;
    while(n != 0){
        sum += n/5;
        n = n/5;
    }
    return sum;
}
//进阶问题
int minlowoneposition(int num)
{
    if(num < 1){
        return -1;
    }
    int res = 0;
    while(num != 0){
        num = num >> 1;
        res += num;
    }
    return res;
}
//93.判断一个点是否在矩形内部
bool isincluderectangle(double x1,double y1,double x4,double y4,double x,double y)
{
    if(x <= x1)
        return false;
    if(x >= x4)
        return false;
    if(y >= y1)
        return false;
    if(y <= y4)
        return false;
    return true;
}
bool isincluderectangle2(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4,double x,double y)
{
    if(y1 == y2)
        return isincluderectangle(x1, y1, x4, y4, x, y);
    double l = abs(y4-y3);
    double k = abs(x4-x3);
    double s = sqrt(k*k+l*l);
    double sin = l/s;
    double cos = k/s;
    double x1r = cos*x1+sin*y1;
    double y1r = -x1*sin + y1*cos;
    double x4r = cos*x4+sin*y4;
    double y4r = -x4*sin + y4*cos;
    double xr = cos*x+sin*y;
    double yr = -x*sin + y*cos;
    return isincluderectangle(x1r, y1r, x4r, y4r, xr, yr);
}
//94.判断一个点是否在三角形内部
bool isincludetriangle(double x1,double y1,double x2,double y2,double x3,double y3,double x,double y)
{
    bool isup = true;
    if(y3 < y1)
        isup = false;
    if(isup && y<y1)
        return false;
    if(!isup && y>y1)
        return false;
    if(x >= x2)
        return false;
    if(x <= x1)
        return false;
    double l1 = abs(y-y1);
    double k1 = abs(x-x1);
    double k2 = abs(x2-x);
    double l = abs(y3-y1);
    double k = abs(x3-x1);
    double _k = abs(x2-x3);
    double a1 = atan(l/k);
    double a2 = atan(l/_k);
    double a_1 = atan(l1/k1);
    double a_2 = atan(l1/k2);
    if(a_1 >= a1)
        return false;
    if(a_2 >= a2)
        return false;
    return true;
}
bool isincludetriangle2(double x1,double y1,double x2,double y2,double x3,double y3,double x,double y)
{
    if(y1 == y2)
        return isincludetriangle(x1, y1, x2, y2, x3, y3, x, y);
    double l = abs(y2-y1);
    double k = abs(x2-x1);
    double s = sqrt(k*k+l*l);
    double sin = l/s;
    double cos = k/s;
    double x1r = cos*x1+sin*y1;
    double y1r = -x1*sin + y1*cos;
    double x2r = cos*x2+sin*y2;
    double y2r = -x2*sin + y2*cos;
    double x3r = cos*x3+sin*y3;
    double y3r = -x3*sin + y3*cos;
    double xr = cos*x+sin*y;
    double yr = -x*sin + y*cos;
    return isincludetriangle(x1r, y1r, x2r, y2r, x3r, y3r, xr, yr);
}
//面积法
double getsidelen(double x1,double y1,double x2,double y2)
{
    double l = abs(y2-y1);
    double k = abs(x2-x1);
    return sqrt(l*l+k*k);
}
double getarea(double x1,double y1,double x2,double y2,double x3,double y3)
{
    double side1len = getsidelen(x1,y1,x2,y2);
    double side2len = getsidelen(x1,y1,x3,y3);
    double side3len = getsidelen(x2,y2,x3,y3);
    double p = (side1len+side2len+side3len)/2;
    return sqrt((p-side1len)*(p-side2len)*(p-side3len) * p);
}
bool isinside(double x1,double y1,double x2,double y2,double x3,double y3,double x,double y)
{
    double area1 = getarea(x1, y1, x2, y2, x, y);
    double area2 = getarea(x1, y1, x3, y3, x, y);
    double area3 = getarea(x2, y2, x3, y3, x, y);
    double area = getarea(x1, y1, x2, y2, x3, y3);
    return area1+area2+area3 <= area;
}
//95.折纸问题
void printorigamiproblem(int n)
{
    vector<string> nums;
    ziporigami(0, n, nums, true);
    for(auto c : nums)
        cout<<c<<endl;
}
void ziporigami(int i,int n,vector<string>& nums,bool isdown)
{
    if(i == n){
        return;
    }
    ziporigami(i+1,n,nums,true);
    nums.push_back(isdown?"down":"up");
    ziporigami(i+1,n,nums,false);
}
//96.蓄水池算法
int randfunc(int max){
    return rand()%max+1;
}
vector<int> getknumsrand(int max,int k)
{
    vector<int> res;
    if(k < 1 || max < 1)
        return res;
    res.resize(min(k,max));
    for(int i = 1;i<=max;i++){
        if(i<=k){
            res[i-1] = i;
        }
        else if(randfunc(i) <= k){
            res[randfunc(i)-1] = i;
        }
    }
    return res;
}
//注意单调栈结构，n个整数的无序数组，找到每个元素后面比它大的第一个数
vector<int> getnextmaxnumbers(vector<int>& nums)
{
    vector<int> res;
    if(nums.empty())
        return res;
    int len = (int)nums.size();
    res.resize(len);
    stack<int> record;
    int i = 1;
    record.push(nums[0]);
    while(!record.empty() && i<len){
        while(i<len  && record.top() <= nums[i]){
            record.push(i++);
        }
        while(i < len && !record.empty()){
            res[record.top()] = nums[i];
            record.pop();
        }
    }
    while(!record.empty()){
        res[record.top()] = -1;
        record.pop();
    }
    return res;
}
//97.算术表达式转后缀表达式
string topostfix(string str)
{
    stack<string> m_stack;
    string postfix;
    int i = 0;
    while(i<str.size()){
        char ch = str[i];
        switch(ch)
        {
            case '+':
            case '-':
                while(!m_stack.empty() && m_stack.top() != "("){
                    postfix.append(m_stack.top());
                    m_stack.pop();
                }
                m_stack.push(to_string(ch));
                i++;
                break;
            case '*':
            case '/':
                while(!m_stack.empty() && (m_stack.top() == "*" || m_stack.top() == "/")){
                    postfix.append(m_stack.top());
                    m_stack.pop();
                }
                m_stack.push(to_string(ch));
                i++;
                break;
            case '(':
                m_stack.push(to_string(ch));
                i++;
                break;
            case ')':
            {
                string out = m_stack.top();
                m_stack.pop();
                while(!out.empty() && out != "("){
                    postfix.append(out);
                    out = m_stack.top();
                    m_stack.pop();
                }
                i++;
                break;
            }
            default:
                while(i<str.size() && ch >= '0' && ch <= '9'){
                    postfix.append(to_string(ch));
                    i++;
                    if(i<str.size()){
                        ch = str[i];
                    }
                }
                postfix.append(" ");
        }
    }
    while(!m_stack.empty()){
        postfix.append(m_stack.top());
        m_stack.pop();
    }
    return postfix;
}
int tovalue(string str)
{
    stack<int> m_stack;
    int value = 0;
    for(int i = 0;i<str.size();i++){
        char ch = str[i];
        if(ch >= '0' && ch <= '9'){
            value = 0;
            while(ch != ' '){
                value = value * 10 +ch-'0';
                ch = str[++i];
            }
            m_stack.push(value);
        }
        else if(ch != ' '){
            int y = m_stack.top();
            m_stack.pop();
            int x = m_stack.top();
            m_stack.pop();
            switch (ch) {
                case '+':
                    value = x+y;
                    break;
                case '-':
                    value = x-y;
                    break;
                case '*':
                    value = x*y;
                    break;
                case '/':
                    value = x/y;
                    break;
                default:
                    break;
            }
            cout<<x<<ch<<y<<"="<<value<<endl;
            m_stack.push(value);
        }
    }
    return m_stack.top();
}
//98.最大的leftMax与rightMax之差的绝对值
int absofleftmaxdiffrightmaxnums(vector<int>& nums)
{
    vector<int> leftmax,rightmax;
    int len = (int)nums.size();
    leftmax.resize(len);
    rightmax.resize(len);
    int curmax = nums[0];
    leftmax[0] = curmax;
    for(int i = 1;i<len;i++){
        curmax = max(curmax,nums[i]);
        leftmax[i] = curmax;
    }
    curmax = nums[len-1];
    rightmax[len-1] = curmax;
    for(int i = len-2;i>-1;i--){
        curmax = max(curmax,nums[i]);
        rightmax[i] = curmax;
    }
    int k = 1;
    int maxdiff = 0;
    for(;k<len-1;k++){
        curmax = abs(leftmax[k-1]-rightmax[k+1]);
        maxdiff = max(maxdiff,curmax);
    }
    return maxdiff;
}
//101.调整[0,x)区间上的数出现的概率
double randXPowerK(int k)
{
    if(k<1)
        return 0;
    double res = -1;
    for(int i = 0;i != k;i++){
        double randindex = rand()%1;
        res = max(res,randindex);
    }
    return res;
}
//102.路径数组变统计数组
void getcountnumsarray(vector<int>& nums)
{
    if(nums.empty())
        return;
    pathstodistans(nums);
    distanstonums(nums);
}
void pathstodistans(vector<int>& nums){
    int cap = 0;
    for(int i = 0;i != nums.size();i++){
        if(nums[i] == i){
            cap = i;
        }else if(nums[i] > -1){
            int curi = nums[i];
            nums[i] = -1;
            int prei = i;
            while(nums[curi] > -1){
                if(nums[curi]>-1){
                    int nexti = nums[curi];
                    nums[curi] = prei;
                    prei = curi;
                    curi = nexti;
                }else{
                    break;
                }
            }
            int value = nums[curi] == curi ? 0 : nums[curi];
            while(nums[prei] != -1){
                int lastprei = nums[prei];
                nums[prei] = --value;
                curi = prei;
                prei = lastprei;
            }
            nums[prei] = --value;
        }
    }
    nums[cap] = 0;
}
void distanstonums(vector<int>& nums){
    for(int i = 0;i != nums.size();i++){
        int index = nums[i];
        if(index < 0){
            nums[i] = 0;
            while(true){
                index = -index;
                if(nums[index] > -1){
                    nums[index]++;
                    break;
                }else{
                    int nextindex = nums[index];
                    nums[index] = 1;
                    index = nextindex;
                }
            }
        }
    }
    nums[0] = 1;
}
//103.正数数组的最小不可组成和
int getimpossiblesumarray(vector<int>& nums)
{
    int maxval = 0;
    int minval = INT_MAX;
    int len = (int)nums.size();
    for(int i = 0;i<len;i++){
        minval = min(minval,nums[i]);
        maxval += nums[i];
    }
    unordered_set<int> record;
    unordered_set<int>::iterator it;
    processgetminpossible(nums,0,record,0);
    for(int i = minval+1;i < maxval;i++){
        it = record.find(i);
        if(it == record.end()){
            return i;
        }
    }
    return maxval+1;
}
void processgetminpossible(vector<int>& nums,int i,unordered_set<int>& record,int sum){
    if(i == nums.size()){
        if(sum != 0){
            unordered_set<int>::iterator it = record.find(sum);
            if(it == record.end()){
                record.insert(sum);
            }
        }
        return;
    }
    if(sum != 0){
        unordered_set<int>::iterator it = record.find(sum);
        if(it == record.end()){
            record.insert(sum);
        }
    }
    processgetminpossible(nums,i+1,record,sum);
    processgetminpossible(nums,i+1,record,sum+nums[i]);
}
//动态规划版
int dpgetinpossibelsumarray(vector<int>& nums)
{
    if(nums.empty())
        return -1;
    int maxval = 0;
    int minval = INT_MAX;
    int len = (int)nums.size();
    for(int i = 0;i<len;i++){
        minval = min(minval,nums[i]);
        maxval += nums[i];
    }
    vector<bool> dp(maxval+1,false);
    dp[0] = true;
    for(int i = 0;i<len;i++){
        for(int j = maxval;j>=nums[i];j--){
            dp[j] = dp[j-nums[i]] ? true : dp[j];
        }
    }
    for(int i = minval+1;i<maxval;i++){
        if(dp[i] == false)
            return i;
    }
    return maxval+1;
}
//进阶问题
int dpoptimalimpossiblesum(vector<int>& nums)
{
    if(nums.empty())
        return -1;
    sort(nums.begin(),nums.end());
    int cursum = nums[0];
    int len = (int)nums.size();
    for(int i = 1;i<len;i++){
        if(nums[i] > cursum + 1)
            return cursum+1;
        else{
            cursum += nums[i];
        }
    }
    return cursum+1;
}
//104.一种字符串和数字的对应关系
void getrelationshipbetweenwordnum(void)
{
    string str1,str2,str3;
    getline(cin,str1);
    getline(cin,str2);
    getline(cin,str3);
    int i = 0;
    int opt = 0,n = 0;
    while(i<str1.size()&& str1[i] != ' '){
        opt = opt*10 + str1[i++]-'0';
    }
    i++;
    while(i<str1.size()&& str1[i] != ' '){
        n = n*10 + str1[i++]-'0';
    }
    if(opt == 1)
    {
        int target = 0;
        i = 0;
        while(i<str3.size()){
            target = target*10 + str3[i++]-'0';
        }
        vector<int> record;
        while(target != 0){
            record.push_back(target%n);
            target /= n;
        }
        string res;
        bool bitcal = false;
        int index = 0;
        for(int i = 0;i<record.size();i++){
            index = bitcal ? record[i]-2 : record[i]-1;
            if(index < 0){
                if(i == record.size()-1)
                    break;
                index = index+n;
                bitcal = true;
            }
            else{
                bitcal = false;
            }
            res = res + str2[index];
        }
        for(int i = (int)res.size()-1;i>-1;i--){
            cout<<res[i];
        }
        cout<<endl;
    }
    else if(opt == 2)
    {
        i = (int)str3.size()-1;
        int curn = 1;
        int res = 0;
        int j = 0;
        while(i > -1){
            for(j = 0;j<n;j++){
                if(str2[j] == str3[i])
                    break;
            }
            res = res + (j+1)*curn;
            curn = curn*n;
            i--;
        }
        cout<<res<<endl;
    }
}
//105.1到n中1出现的次数
//暴力递归方法
int processgetcountoneoccur(int n)
{
    int count = 0;
    int temp = 0;
    for(int i = 1;i<=n;i++){
        temp = i;
        while(temp != 0){
            if(temp %10 == 1)
                count++;
            temp /= 10;
        }
    }
    return count;
}
//找规律方法
int solution2(int num)
{
    if(num < 1){
        return 0;
    }
    int len = getlenofnum(num);
    if(len == 1)
        return 1;
    int tmp1 = powerbaseof10(len-1);
    int first = num/tmp1;
    int firstonenum = first == 1 ? num % tmp1 + 1:tmp1;
    int othernum = first * (len-1)*(tmp1/10);
    return firstonenum + othernum + solution2(num%tmp1);
}
int getlenofnum(int num)
{
    int len = 0;
    while(num != 0){
        len++;
        num /= 10;
    }
    return len;
}
int powerbaseof10(int base)
{
    return (int)pow(10,base);
}
//106.从N个数中等概率打印M个数
void printrandomnums(vector<int>& nums,int n)
{
    int len = (int)nums.size();
    int index = 0;
    int i = 0;
    while(i<n){
        index = rand()%len;
        cout<<nums[index]<<" ";
        swap(nums[index],nums[len-1]);
        len--;
        i++;
    }
    cout<<endl;
}
//107.判断一个数是否是回文数
bool ispalindromicnumber(int n)
{
    n = abs(n);
    vector<int> nums;
    while(n){
        nums.push_back(n%10);
        n /= 10;
    }
    int len = (int)nums.size()-1;
    int i = 0;
    while(i < len){
        if(nums[i] != nums[len]){
            return false;
        }
        i++;
        len--;
    }
    return true;
}
//108.在有序旋转数组中找到最小值
int getminfromrotatearray(vector<int>& nums,int& n)
{
    if(n <= 0){
        return INT_MAX;
    }
    if(n == 1)
        return nums[0];
    if(nums[0] < nums[n-1])//没有旋转
        return nums[0];
    int l = 0;
    int r = n-1;
    while(l<r){
        if(l+1 == r){
            return nums[l]<nums[r]?nums[l]:nums[r];
        }
        if(nums[l] < nums[r])
            return nums[l];
        int mid = l+ (r-l)/2;
        if(nums[mid] > nums[l]){
            l = mid+1;
        }
        else if(nums[mid] < nums[l]){
            r = mid;
        }
        else{
            l = mid;
        }
    }
    return 0;
}
//109.在有序旋转数组中找到一个数
bool gettargetnumfromrotatearray(vector<int>& nums,int num)
{
    int n = (int)nums.size();
    if(n == 1)
        return nums[0];
    int l = 0;
    int r = n-1;
    while(l<r){
        int mid = l + (r-l)/2;
        if(nums[mid] == num){
            return true;
        }
        if(nums[l] == nums[mid] && nums[mid] == nums[r]){
            while(l<mid && nums[l] == nums[mid]){
                l++;
            }
            if(nums[l] == nums[mid]){
                l = mid+1;
                continue;
            }
        }
        if(nums[mid] != nums[l]){
            if(nums[mid] > nums[l]){
                if(num >= nums[l] && num < nums[mid]){
                    r = mid-1;
                }else{
                    l = mid+1;
                }
            }
        }else{
            if(num > nums[mid] && num <= nums[r]){
                l = mid+1;
            }else{
                r = mid-1;
            }
        }
    }
    return false;
}
//110.数字的中文表达和英文表达
vector<string> getEnglishandChineseofnum(int num)
{
    vector<string> res;
    res.resize(2);
    //0～19
    vector<string> Engvec = {"zero","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
    vector<string> Chnvec = {"零","一","二","三","四","五","六","七","八","九","十","十一","十二","十三","十四","十五","十六","十七","十八","十九"};
    vector<string> Engtwobit = {"","","twenty","thirty","fourty","fifty","sixty","seventy","eighty","ninety"};
    vector<string> Chntwobit = {"","","二十","三十","四十","五十","六十","七十","八十","九十"};
    vector<string> Engbit = {"","","hundred","Thousand","Million","Billion"};
    vector<string> Chnbit = {"","","百","千","万","亿"};
    stack<int> record;//高位先出
    int highbit = 0;
    while(num){
        record.push(num%10);
        num /= 10;
        highbit++;
    }
    
    
    return res;
}
//111.分糖果问题
int distributecandysolution(vector<int> nums,int n)
{
    int candycount = 1;
    int lastcandy = nums[0];
    int curcandy = 1;
    for(int i = 1;i<n;i++){
        if(nums[i] > lastcandy){
            curcandy++;
        }
        else{
            curcandy = 1;
        }
        candycount = candycount + curcandy;
        lastcandy = nums[i];
    }
    return candycount;
}
//KMP手撸代码
void isincludekmpmethod(string& str1,string& str2)
{
    vector<int>&& next = getnextarrayofkmpmethod(str2);
    int len1 = (int)str1.size();
    int len2 = (int)str2.size();
    int i1 = 0;
    int i2 = 0;
    bool isinclude = false;
    while(i1 < len1){
        if(i2 == len2){
            cout<<i1-len2<<" ";
            isinclude = true;
            i2 = 0;
        }
        if(str1[i1] == str2[i2]){
            i1++;
            i2++;
        }
        else if(i2 == 0){
            i1++;
        }
        else{
            i2 = next[i2];
        }
    }
    if(i2 == len2){
        cout<<i1-len2<<endl;
        isinclude = true;
    }
    if(!isinclude){
        cout<<-1<<endl;
    }
    return;
}
vector<int> getnextarrayofkmpmethod(string& str2)
{
    vector<int> next;
    int len = (int)str2.size();
    next.resize(len);
    next[0] = -1;
    next[1] = 0;
    int cn = 0;
    int i = 2;
    while(i<len){
        if(str2[i-1] == str2[cn]){
            next[i++] = ++cn;
        }
        else if(cn > 0){
            cn = next[cn];
        }
        else{
            next[i++] = 0;
        }
    }
    return next;
}
//112.一种消息接收并打印的结构设计
void printsequencenumbers(vector<int>& nums,int n)
{
    //思路：桶排序，再判断一下上一次输出的是那个lastval
    int lastval = 1;
    unordered_set<int> record;
    unordered_set<int>::iterator it;
    for(int i = 0;i<n;i++){
        cout<<i+1<<" "<<lastval<<endl;
        record.insert(nums[i]);
        if(nums[i] == lastval){
            it = record.find(lastval);
            while(it != record.end()){
                record.erase(it);
                it = record.find(++lastval);
            }
        }
    }
    return;
}
//114.在两个长度相等的排序数组中找到上中位数
int getupmediannumber(vector<int>& num1,vector<int>& num2,int n)
{
    //第一种方法：谁小谁先走
    int i1 = 0,i2 = 0;
    int count = 0;
    int res = -1;
    while(i1 < n && i2 < n && count < n){
        if(num1[i1] < num2[i2]){
            res = num1[i1];
            i1++;
        }
        else{
            res = num2[i2];
            i2++;
        }
        count++;
    }
    return res;
}
//115.在两个排序数组中找到第K小的数
int getminknumbersoftwoarray(vector<int>& num1,vector<int>& num2,int n,int m,int k)
{
    int i1 = 0;
    int i2 = 0;
    int count = 0;
    int res = 0;
    while(i1 < n && i2 < m && count < k){
        if(num1[i1] < num2[i2]){
            res = num1[i1];
            i1++;
        }
        else{
            res = num2[i2];
            i2++;
        }
        count++;
    }
    if(count == k)
        return res;
    while(i1 < n && count < k){
        res = num1[i1];
        i1++;
        count++;
    }
    while(i2 < m&& count < k){
        res = num2[i2];
        i2++;
        count++;
    }
    return res;
}
//116.两个有序数组间相加和的TOP K问题
vector<int> gettopknumbersofarray(vector<int>& num1,vector<int>& num2,int n,int k)
{
    vector<int> res;
    priority_queue<int> bigheap;
    unordered_set<indexrecord,indexhash,indexcompare> record;
    unordered_set<indexrecord,indexhash,indexcompare>::iterator it;
    int i1 = n-1;
    int i2 = n-1;
    int count = 0;
    processgettopknumbersofarray(num1,num2,i1,i2,count,bigheap,record);
    for(int i = 0;i<k;i++){
        res.push_back(bigheap.top());
        bigheap.pop();
    }
    return res;
}
void processgettopknumbersofarray(vector<int>& num1,vector<int>& num2,int i1,int i2,int& count,priority_queue<int>& bigheap,unordered_set<indexrecord,indexhash,indexcompare>& record)
{
    if(i1 < 0 || i2 < 0){
        return;
    }
    indexrecord tmp(i1,i2);
    if(record.find(tmp) == record.end()){
        record.insert(tmp);
        bigheap.push(num1[i1]+num2[i2]);
        count++;
    }
    processgettopknumbersofarray(num1,num2,i1-1,i2,count,bigheap,record);
    processgettopknumbersofarray(num1,num2,i1,i2-1,count,bigheap,record);
}
//117.出现次数的TOP K问题
void getpresenttopknums(vector<string>& nums,int k)
{
    priority_queue<stringrecord> bigheap;
    unordered_map<string,int> record;
    int len = (int)nums.size();
    for(int i = 0;i<len;i++){
        if(record.find(nums[i]) != record.end()){
            record[nums[i]]++;
        }
        else{
            record.insert(make_pair(nums[i],1));
        }
    }
    unordered_set<string> isinclude;
    for(int i = 0;i<len;i++){
        if(isinclude.find(nums[i]) == isinclude.end()){
            isinclude.insert(nums[i]);
            bigheap.push(stringrecord(record[nums[i]],nums[i]));
        }
    }
    for(int i = 0;i<k;i++){
        cout<<(bigheap.top()).word<<" "<<(bigheap.top()).count<<endl;
        bigheap.pop();
    }
}
//118.Manacher算法
string getstringmagic(string& str)
{
    string res;
    res += "#";
    for(int i = 0;i<str.size();i++){
        res = res + str[i] + "#";
    }
    return res;
}
int getmaxlenpalindromeword(string& str)
{
    string&& res = getstringmagic(str);
    int len = (int)res.size();
    int center = 0;
    int right = 0;
    int curright = 0;
    vector<int> palindromearray(len,0);
    int maxlen = 0;
    int i = 0;
    while(i<len)
    {
        curright = right > i?min(right,palindromearray[2*center-i]+i):1+i;
        while(2*i-curright > -1 && curright < len && res[curright] == res[2*i-curright]){
            curright++;
        }
        palindromearray[i] = curright-i-1;
        if(right < curright){
            center = i;
            right = curright;
        }
        maxlen = max(palindromearray[i],maxlen);
        i++;
    }
    return maxlen;
}
//119.丢棋子问题
long long getmincountnumbers(long long n,long long k)
{
    long long dp[n+1][k+1];
    dp[0][0] = 0;
    for(int i = 1;i<=n;i++){
        dp[i][1] = i;
    }
    for(int j = 0;j<=k;j++){
        dp[0][j] = 0;
    }
    for(int i = 1;i<=n;i++){
        for(int j = 2;j<=k;j++){
            long long minval = INT_MAX;
            for(int k = 1;k <= i;k++){
                minval = min(minval,max(dp[k-1][j-1],dp[i-k][j]));
            }
            dp[i][j] = minval + 1;
        }
    }
    return dp[n][k];
}
//最优解
int log2n(int n)
{
    int res = -1;
    while(n != 0){
        res++;
        n = n>>1;
    }
    return res;
}
int optimalsolution(int n,int k)
{
    if(n < 1 || k < 1)
        return 0;
    int nstime = log2n(n)+1;
    if(k >= nstime)
        return nstime;
    vector<int> dp(k,0);
    int res = 0;
    while(true){
        res++;
        int previous = 0;
        for(int i = 0;i<k;i++){
            int tmp = dp[i];
            dp[i] = dp[i]+previous+1;
            previous = tmp;
            if(dp[i] >= n){
                return res;
            }
        }
    }
    return 0;
}
//120.花匠问题
int processmincolor(vector<int>& nums,int i,int num,int maxval,int sum)
{
    if(i >= nums.size()){
        int temp = max(sum,maxval);
        sum = 0;
        maxval = 0;
        return temp;
    }
    if(num == 1){
        maxval = max(maxval,sum);
        sum = 0;
        while(i<nums.size()){
            sum += nums[i];
            i++;
        }
        int temp = max(maxval,sum);
        sum = 0;
        maxval = 0;
        return temp;
    }
    return min(processmincolor(nums,i+1,num,maxval,sum+nums[i]),processmincolor(nums,i+1,num-1,max(maxval,sum+nums[i]),0));
}
int getmindraincolortime(vector<int>& nums,int num)
{
    return processmincolor(nums,0,num,0,0);
}
//二分法实现
int getneednum(vector<int>& nums,int& len,int limit)
{
    int res = 0;
    int sum = 0;
    for(int i = 0;i<len;i++){
        if(nums[i] > limit)
            return INT_MAX;
        sum += nums[i];
        if(sum > limit){
            res++;
            sum = nums[i];
        }
    }
    return res;
}
int getminbinarysearchmethodcolortime(vector<int>& nums,int num)
{
    int len = (int)nums.size();
    if(len < num){
        int maxres = 0;
        for(int i = 0;i<len;i++){
            maxres = max(maxres,nums[i]);
        }
        return maxres;
    }
    int l = 0;
    int r = 0;
    for(int i = l;i<len;i++){
        r += nums[i];
    }
    while(l != r-1){
        int mid = (r+l)/2;
        if(getneednum(nums,len,mid) > num){
            l = mid;
        }
        else{
            r = mid;
        }
    }
    return r;
}
//121.邮局选址问题
int mindistances(vector<int>& nums,int num)
{
    int len = (int)nums.size();
    if(len < 1 || len < num)
        return 0;
    int w[len+1][len+1];
    for(int i = 0;i<=len;i++){
        for(int j = 0;j<=len;j++){
            w[i][j] = 0;
        }
    }
    for(int i = 0;i<len;i++){
        for(int j = i+1;j<len;j++){
            w[i][j] = w[i][j-1] + nums[j]-nums[(i+j)/2];
        }
    }
    int dp[num][len];
    for(int i = 0;i<num;i++){
        for(int j = 0;j<=len;j++){
            dp[i][j] = 0;
        }
    }
    for(int j = 0;j != len;j++){
        dp[0][j] = w[0][j];
    }
    for(int i = 1;i<num;i++){
        for(int j = i+1;j<len;j++){
            dp[i][j] = INT_MAX;
            for(int k = 0;k<=j;k++){
                dp[i][j] = min(dp[i][j],dp[i-1][k] + w[k+1][j]);
            }
        }
    }
    return dp[num-1][len-1];
}
