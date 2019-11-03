//
//  Tree.cpp
//  c++
//
//  Created by litianfa on 2019/7/6.
//  Copyright © 2019 litianfa. All rights reserved.
//

#include "Tree.hpp"
//案例一，用非递归的方式实现二叉树先序、中序、后序遍历
void treeprintpretra(TreeNode* head)
{
    if(head == NULL)
        return;
    stack<TreeNode*> store;
    store.push(head);
    TreeNode* ptr = NULL;
    while(!store.empty()){
        ptr = store.top();
        store.pop();
        cout<<ptr->val<<" ";
        if(ptr->right != NULL)
            store.push(ptr->right);
        if(ptr->left != NULL)
            store.push(ptr->left);
    }
    return;
}
void treeprintintra(TreeNode* head)
{
    if(head == NULL)
        return;
    stack<TreeNode*> mysta;
    TreeNode* cur = head;
    while(!mysta.empty() || cur != NULL){
        while(cur != NULL){
            mysta.push(cur);
            cur = cur->left;
        }
        TreeNode* node = mysta.top();
        mysta.pop();
        cout<<node->val<<" ";
        cur = node->right;
    }
    return;
}
void treeprintafttra(TreeNode* head)
{
    if(head == NULL)
        return;
    stack<TreeNode*> prestack;
    stack<TreeNode*> aftstack;
    TreeNode* ptr = NULL;
    prestack.push(head);
    while(!prestack.empty()){
        ptr = prestack.top();
        prestack.pop();
        aftstack.push(ptr);
        if(ptr->left != NULL)
            prestack.push(ptr->left);
        if(ptr->right != NULL)
            prestack.push(ptr->right);
    }
    while(!aftstack.empty()){
        ptr = aftstack.top();
        aftstack.pop();
        cout<<ptr->val<<" ";
    }
    return;
}
//moris遍历
//1.此为模版，后边的先序中序后序遍历都是通过这个来改的
void moris(TreeNode* head)
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
        cur = cur->right;
    }
    return;
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
//案例2，给定一颗二叉树的头节点head,请按照层遍历的方式来打印二叉树
void bfstree(TreeNode* head)
{
    if(head == NULL){
        return;
    }
    queue<TreeNode*> tree;
    TreeNode* last = head;
    TreeNode* nlast = NULL;
    TreeNode* help = NULL;
    tree.push(head);
    while(!tree.empty()){
        help = tree.front();
        tree.pop();
        cout<<help->val<<" ";
        if(help->left != NULL){
            tree.push(help->left);
            nlast = help->left;
        }
        if(help->right != NULL){
            tree.push(help->right);
            nlast = help->right;
        }
        if(help == last){
            last = nlast;
            cout<<endl;
        }
    }
    return;
}
//案例3，二叉树的序列化和反序列化
//先序序列化和反序列化
string pretreetostr(TreeNode* root)
{
    string str;
    if(root == NULL)
        return str;
    stack<TreeNode*> store;
    store.push(root);
    TreeNode* ptr = NULL;
    while(!store.empty()){
        ptr = store.top();
        store.pop();
        if(ptr != NULL){
            str+=to_string(ptr->val)+'_';
            if(ptr->left == NULL && ptr->right == NULL){
                str+="#_";
                str+="#_";
                continue;
            }else{
                store.push(ptr->right);
                store.push(ptr->left);
            }
        }
        else
            str+="#_";
    }
    return str;
}
TreeNode* prestrtotree(string data)
{
    if(data.empty())
        return NULL;
    int i = 0;
    int temp = 0;
    bool isnegative = false;
    while(data[i] != '#' && data[i] != '_'){
        if(data[i] == '-')
        {
            i++;
            isnegative = true;
            continue;
        }
        temp = temp*10 + data[i++] - '0';
    }
    if(isnegative)
        temp = -temp;
    TreeNode* head = new TreeNode(temp);
    TreeNode* ptr = head;
    stack<TreeNode*> sta;
    sta.push(ptr);
    while(i<data.size()){
        while(ptr != NULL){
            if(data[i] == '#'){
                ptr->left = NULL;
                ptr = ptr->left;
                i = i+2;
            }else if(data[i] != '_'){
                temp = 0;
                isnegative = false;
                while(data[i] != '_'){
                    if(data[i] == '-')
                    {
                        i++;
                        isnegative = true;
                        continue;
                    }
                    temp = temp*10 + data[i++] - '0';
                }
                if(isnegative)
                    temp = -temp;
                ptr->left = new TreeNode(temp);
                ptr = ptr->left;
                sta.push(ptr);
                i++;
            }else if(data[i] == '_'){
                i++;
            }
        }
        while(!sta.empty() && i<data.size()){
            ptr = sta.top();
            sta.pop();
            if(data[i] == '#'){
                ptr->right = NULL;
                i = i+2;
            }
            else if(data[i] != '_'){
                temp = 0;
                isnegative = false;
                while(data[i] != '_'){
                    if(data[i] == '-')
                    {
                        i++;
                        isnegative = true;
                        continue;
                    }
                    temp = temp*10 + data[i++] - '0';
                }
                if(isnegative)
                    temp = -temp;
                ptr->right = new TreeNode(temp);
                ptr = ptr->right;
                i++;
                sta.push(ptr);
                break;
            }else if(data[i] == '_'){
                i++;
            }
        }
    }
 
    morisPre(head);
    return head;
}
//案例4，给定一颗二叉树的头节点，判断这棵树是否为平衡二叉树
returnAVLdata isavltree(TreeNode* head)
{
    if(head == NULL)
        return returnAVLdata(true,0);
    returnAVLdata leftdata = isavltree(head->left);
    returnAVLdata rightdata = isavltree(head->right);
    int depth = 0;
    bool isbalance = false;
    if(leftdata.isbalance && rightdata.isbalance && abs(leftdata.height-rightdata.height) <= 1) {
        depth = max(leftdata.height,rightdata.height)+1;
        isbalance = true;
    }
    return returnAVLdata(isbalance,depth);
}
//案例5，给定一颗二叉树，判断这棵二叉树是否是搜索二叉树
bool issearchtree(TreeNode* head)
{
    if(head == NULL || (head->left == NULL && head->right == NULL))
        return true;
    stack<TreeNode*> mysta;
    TreeNode* cur = head;
    int last = INT_MIN;
    int count = 0;
    while(!mysta.empty() || cur != NULL){
        while(cur != NULL){
            mysta.push(cur);
            cur = cur->left;
        }
        TreeNode* node = mysta.top();
        mysta.pop();
        if(count > 0){
            if(node->val<=last){
                return false;
            }
        }
        count++;
        last = node->val;
        cur = node->right;
    }
    return true;
}
//案例6，判断一棵树上是否为完全二叉树
bool isfulltree(TreeNode* root)
{
    if(root == NULL)
        return true;
    queue<TreeNode*> que;
    TreeNode* cur = NULL;
    que.push(root);
    bool isnolornor = false;
    while(!que.empty()){
        cur = que.front();
        que.pop();
        if(cur->left != NULL){
            que.push(cur->left);
            if(isnolornor)
                return false;
        }
        if(cur->right != NULL){
            que.push(cur->right);
            if(cur->left == NULL)
                return false;
            if(isnolornor)
                return false;
        }
        if(cur->left == NULL || cur->right == NULL){
            isnolornor = true;
        }
    }
    return true;
}
//案例7，找特殊节点树的后继节点
Node* follownode(Node* root)
{
    if(root == NULL)
        return NULL;
    Node* s = NULL;
    Node* p = NULL;
    if(root->right != NULL){
        s = root->right->left;
        p = root->right;
        while(s != NULL){
            s = s->left;
            p = p->left;
        }
        return p;
    }
    else{
        if(root->parent == NULL)
            return NULL;
        p = root->parent;
        if(p->left == root){
            return p;
        }
        else if(p->right == root){
            s = p;
            p = p->parent;
            while(p!=NULL){
                if(s == p->left)
                    return p;
                else{
                    s = p;
                    p = p->parent;
                }
            }
            return p;
        }
    }
    return p;
}
//案例8，折纸问题
void pressit(int N)
{
    vector<string> res;
    zip(res,1,N,true);
    for(auto c:res){
        cout<<c<<endl;
    }
}
void zip(vector<string>& arr,int i,int N,bool isdown)
{
    if(i>N)
        return;
    zip(arr,i+1,N,true);
    arr.push_back(isdown?"down":"up");
    zip(arr,i+1,N,false);
}
//案例9，找出搜索二叉树中的两个错误的节点
vector<TreeNode*> searcherrornode(TreeNode* root)
{
    vector<TreeNode*> ret;
    if(root == NULL)
        return ret;
    stack<TreeNode*> mysta;
    TreeNode* cur = root;
    TreeNode* last = NULL;
    bool isfirst = true;
    while(!mysta.empty() || cur != NULL){
        while(cur != NULL){
            mysta.push(cur);
            cur = cur->left;
        }
        TreeNode* node = mysta.top();
        mysta.pop();
        if(last != NULL){
            if(last->val > node->val)
            {
                if(isfirst == true){
                    ret.push_back(last);
                    ret.push_back(node);
                    isfirst = false;
                }
                else if(isfirst == false){
                    ret[1] = node;
                }
            }
        }
        last = node;
        cur = node->right;
    }
    if(ret.size() == 2){
        cout<<ret[0]->val<<endl;
        cout<<ret[1]->val<<endl;
    }
    return ret;
}
//案例10，从二叉树的节点A出发，可以向上或者向下走，但沿途的节点只能经过一次，当到达节点B时，路径上的节点数叫做A到B的距离，给定一颗二叉树，求整棵树上节点之间的最大距离
returnmaxdistance maxdistancetree(TreeNode* root)
{
    if(root == NULL)
        return returnmaxdistance(0,0);
    returnmaxdistance leftdata = maxdistancetree(root->left);
    returnmaxdistance rightdata = maxdistancetree(root->right);
    returnmaxdistance data(0,0);
    data.maxdistance = max(leftdata.maxdtoh+rightdata.maxdtoh+1,max(leftdata.maxdistance,rightdata.maxdistance));
    data.maxdtoh = max(leftdata.maxdtoh,rightdata.maxdtoh)+1;
    return data;
}
//案例11，给定一颗二叉树，已知其中所有节点的值都不一样，找到含有节点最多的搜索二叉子树，并返回这棵子树的头节点
returnsearchdata getmaxnumssearchtree(TreeNode* head)
{
    if(head == NULL)
        return returnsearchdata(NULL,0,INT_MIN,INT_MAX);
    returnsearchdata leftdata = getmaxnumssearchtree(head->left);
    returnsearchdata rightdata = getmaxnumssearchtree(head->right);
    int nodenums = 0;
    if(leftdata.root == head->left && rightdata.root == head->right && head->val > leftdata.maxval && head->val < rightdata.minval){
        nodenums = leftdata.nodenums + rightdata.nodenums + 1;
    }
    int leftnums = leftdata.nodenums;
    int rightnums = rightdata.nodenums;
    int maxnums = max(max(leftnums, rightnums),nodenums);
    TreeNode* root = leftnums>rightnums ? leftdata.root : rightdata.root;
    if (maxnums == nodenums)
        root = head;
    return returnsearchdata(root, maxnums, max(max(leftdata.maxval, rightdata.maxval),head->val), min(min(leftdata.minval, rightdata.minval),head->val));
    
}
//案例13，返回一个树的最大和最小
returnnodeinfo pro(TreeNode* head)
{
    if(head == NULL){
        return returnnodeinfo(INT_MAX,INT_MIN);
    }
    returnnodeinfo leftnode = pro(head->left);
    returnnodeinfo rightnode = pro(head->right);
    return returnnodeinfo(min(min(leftnode.min,rightnode.min),head->val),max(max(leftnode.max,rightnode.max),head->val));
}
//案例14，多叉树问题，组织一个晚宴，直接上级来，则直接下级不来，每个成员都有活跃度，求晚宴的最佳活跃度安排
//主要递归求最大活跃度
ReturnData partyprocess(multinode* head)
{
    int lai_huo = head->value;
    int bu_lai_huo = 0;
    for(int i = 0;i<head->size;i++){
        multinode* next = head->next[i];
        ReturnData nextData = partyprocess(next);
        lai_huo += nextData.bu_lai_huo;
        bu_lai_huo += max(nextData.lai_huo,nextData.bu_lai_huo); //动态规划子问题
    }
    return ReturnData(lai_huo,bu_lai_huo);
}
//构造哈夫曼树
huffmannode* createhuffman(vector<int>& nums,int n)
{
    int i,j;
    huffmannode **b,*q;
    b = new huffmannode*[n];
    for(i = 0;i<n;i++){
        b[i] = new huffmannode(nums[i]);
    }
    for(i = 1;i<n;i++){
        int k1 = -1,k2;
        for(j = 0;j<n;j++){
            if(b[j] != NULL && k1 == -1){
                k1 = j;
                continue;
            }
            if(b[j] != NULL){
                k2 = j;
                break;
            }
        }
        for(j = k2;j<n;j++){
            if(b[j] != NULL){
                if(b[j]->data < b[k1]->data){
                    k2 = k1;
                    k1 = j;
                    
                }
                else if(b[j]->data < b[k2]->data){
                    k2 = j;
                }
            }
            q = new huffmannode(b[k1]->data+b[k2]->data);
            q->left = b[k1];
            q->right = b[k2];
            b[k1] = q;
            b[k2]  = NULL;
        }
    }
    for(int i = 0;i<n;i++){
        delete b[i];
    }
    delete[] b;
    return q;
}
