//
//  linked_list.cpp
//  c++
//
//  Created by litianfa on 2019/7/4.
//  Copyright © 2019 litianfa. All rights reserved.
//

#include "linked_list.hpp"

//案例1.给定一个整数num，如何在节点值有序的环形链表中插入一个节点值为num的节点，并且保证这个环形链表依然有序
dounode* insertcyclelinked(int num,dounode* head)
{
    if(head == NULL)
    {
        head = new dounode(num);
        return head;
    }
    dounode* cur = new dounode(num);
    if(num < head->val){
        dounode* help = head->previous;
        head->previous = cur;
        cur->next = head;
        help->next = cur;
        cur->previous = help;
        return cur;
    }
    else
    {
        dounode* ptr = head->next;
        while(ptr != head){
            if(num>ptr->val)
                ptr = ptr->next;
            else{
                dounode* help = ptr->previous;
                ptr->previous = cur;
                cur->next = ptr;
                help->next = cur;
                cur->previous = help;
                break;
            }
        }
        if(ptr == head){
            dounode* help = head->previous;
            head->previous = cur;
            cur->next = head;
            help->next = cur;
            cur->previous = help;
        }
    }
    return head;
}
//2.给定链表中的一个节点node，但不给定整个链表的头节点，如何在链表中删除节点，时间复杂度要求O(1)
void deleteNode(node* cur)
{
    node* ptr = cur->next;
    *cur = *ptr;
    return;
}
//3.给定一个链表的头节点head，在给定一个数num，请把链表调整成节点值小于num的节点放在链表的左边，值等于num的放在链表的中间，大于的放在链表的右边
//方法1，将链表放到一个数组中，进行partition排序就可以了
vector<int> linkedarrpartition(node* head,int num)
{
    vector<int> ret;
    if(head == NULL)
        return ret;
    vector<node*> linkedarr;
    node* ptr = head;
    node* help = NULL;
    while(ptr != NULL){
        if(ptr->val == num)
            help = ptr;
        else
            linkedarr.push_back(ptr);
        ptr = ptr->next;
    }
    linkedarr.push_back(help);
    int less = -1,l = 0;
    int more = (int)linkedarr.size()-1;
    while(l<more){
        if((linkedarr[l])->val<num){
            swap(linkedarr[++less],linkedarr[l++]);
        }
        else if((linkedarr[l])->val == num){
            l++;
        }else if((linkedarr[l])->val>num){
            swap(linkedarr[l],linkedarr[--more]);
        }
    }
    swap(linkedarr[more],linkedarr[(int)linkedarr.size()-1]);
    for(int i = 0;i<linkedarr.size()-1;i++){
        linkedarr[i]->next = linkedarr[i+1];
    }
    linkedarr[linkedarr.size()-1]->next = NULL;
    head = linkedarr[0];
    ret.resize(2);
    ret[0] = less+1;
    ret[1] = more;
    return ret;
}
//方法2，直接在链表上进行排序，分别组成三个链表之后再让它们按次序进行连接
void linkedpartition(node* head,int num)
{
    if(head == NULL)
        return;
    node* less = new node(0);
    node* headless = less;
    node* equal = new node(0);
    node* equalhead = equal;
    node* more = new node(0);
    node* morehead = more;
    node* ptr = head;
    while(ptr != NULL){
        if(ptr->val < num){
            less->next = ptr;
            less = less->next;
        }
        else if(ptr->val == num){
            equal->next = ptr;
            equal = equal->next;
        }else if(ptr->val > num){
            more->next = ptr;
            more = more->next;
        }
        ptr = ptr->next;
    }
    less->next = equalhead->next;
    equal->next = morehead->next;
    head = headless->next;
    more->next = NULL;
    return;
}
//4.给定两个链表的头节点，打印两个有序链表的公共部分
void printcommonlinklist(node* head1,node* head2)
{
    if(head1 == NULL || head2 == NULL){
        return;
    }
    node* ptr1 = head1;
    node* ptr2 = head2;
    while(ptr1 != NULL && ptr2 != NULL){
        if(ptr1->val < ptr2->val){
            ptr1 = ptr1->next;
        }
        else if(ptr1->val == ptr2->val){
            cout<<ptr1->val<<" ";
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        else if(ptr1->val > ptr2->val){
            ptr2 = ptr2->next;
        }
    }
    cout<<endl;
    return;
}
//5.给定单链表的头节点，实现一个调整单链表的函数，使得有k个节点之间逆序，如果不足k个节点的最后几个节点不调整
//方法1，利用栈来实现逆序
node* changefunc1(node* head,int k)
{
    if(head == NULL){
        return NULL;
    }
    node* ptr = head;
    node* help = new node(0);
    node* headhelp = help;
    stack<node*> nodestack;
    while(ptr != NULL){
        while(ptr != NULL && nodestack.size()<k){
            nodestack.push(ptr);
            ptr = ptr->next;
        }
        if(nodestack.size() == k){
            while(!nodestack.empty()){
                help->next = nodestack.top();
                nodestack.pop();
                help = help->next;
            }
            help->next = NULL;
        }
    }
    if(!nodestack.empty()){
        stack<node*> helpstack;
        while(!nodestack.empty()){
            helpstack.push(nodestack.top());
            nodestack.pop();
        }
        while(!helpstack.empty()){
            help->next = helpstack.top();
            helpstack.pop();
            help = help->next;
        }
    }
    help->next = NULL;
    return headhelp->next;
}
//方法2，直接在链表上进行操作
node* optimalcahngefunc2(node* head,int k)
{
    if(head == NULL){
        return NULL;
    }
    node* ret = NULL;
    node* start = NULL;
    node* end = NULL;
    node* ptr = head;
    node* previous = NULL;
    int count = 0;
    int i = 0;
    bool isnotall = false;
    while(ptr != NULL && isnotall == false){
        for(i = 0;i<k;i++){
            if(i == 0){
                start = ptr;
            }
            if(i == k-1){
                end = ptr;
            }
            if(ptr->next == NULL && end == NULL){
                isnotall = true;
                break;
            }
            ptr = ptr->next;
        }
        if(end != NULL){
            node* help = reverselinkedlist(start,end);
            if(count == 0){
                ret = help;
                previous = start;
                end = NULL;
            }else{
                previous->next = help;
                previous = start;
                end = NULL;
            }
            count++;
        }
    }
    if(isnotall){
        previous->next = start;
    }
    return ret;
}
//通用反转链表函数
node* reverselinkedlist(node* start,node* end)
{
    node* help = NULL;
    node* next = NULL;
    node* ptr = start;
    while(ptr != end){
        next = ptr->next;
        ptr->next = help;
        help = ptr;
        ptr = next;
    }
    if(end == NULL)
        return help;
    else{
        ptr->next = help;
        return ptr;
    }
}
//6.给定一个单链表的头节点，链表中每个节点保存一个整数，在给定一个值，把所有等于这个给定值的节点都删掉
node* deleteprovidevalnodelist(node* head,int val)
{
    if(head == NULL){
        return NULL;
    }
    node* start = NULL;
    node* tail = NULL;
    node* cur = head;
    node* help = NULL;
    int count = 0;
    while(cur != NULL){
        if(cur->val == val){
            help = cur;
            cur = cur->next;
            help->next = NULL;
        }
        else{
            if(count == 0){
                start = cur;
                tail = cur;
            }else{
                tail->next = cur;
                tail = tail->next;
            }
            cur = cur->next;
            count++;
        }
    }
    tail->next = NULL;
    return start;
}
//7.判断一个链表是否为回文结构
//方法一，用栈
bool isretwordlist1(node* head)
{
    if(head == NULL || head->next == NULL)
        return true;
    node* ptr = head;
    stack<int> helpstack;
    while(ptr != NULL){
        helpstack.push(ptr->val);
        ptr = ptr->next;
    }
    ptr = head;
    while(ptr != NULL){
        if(ptr->val != helpstack.top()){
            return false;
        }
        else{
            helpstack.pop();
            ptr = ptr->next;
        }
    }
    return true;
}
//方法二，用栈加快慢指针
bool isretwordlist2(node* head)
{
    if(head == NULL || head->next == NULL)
        return true;
    node* fast = head->next->next;
    node* slow = head->next;
    stack<int> helpstack;
    helpstack.push(head->val);
    while(fast != NULL && fast->next != NULL){
        helpstack.push(slow->val);
        slow = slow->next;
        fast = fast->next->next;
    }
    if(fast != NULL)
        helpstack.push(slow->val);
    while(slow != NULL){
        if(slow->val != helpstack.top()){
            return false;
        }
        else{
            slow = slow->next;
            helpstack.pop();
        }
    }
    return true;
}
//方法三，只用快慢指针，链表逆序
bool isretwordlist3(node* head)
{
    if(head == NULL || head->next == NULL)
        return true;
    if(head->next->next == NULL){
        if(head->val == head->next->val)
            return true;
        else
            return false;
    }
    node* fast = head->next->next;
    node* slow = head->next;
    node* temp = NULL;
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    temp = slow;
    node* help = reverselinkedlist(slow,NULL);
    fast = head;
    slow = help;
    while(fast != temp){
        if(fast->val != slow->val)
            return false;
        fast = fast->next;
        slow = slow->next;
    }
    help = reverselinkedlist(help,NULL);
    return true;
}
//8.复制含有rand指针节点的链表
randnode* copyrandnode(randnode* head)
{
    randnode* ptr = head;
    randnode* next = NULL;
    while(ptr != NULL){
        randnode* help = new randnode(ptr->val);
        next = ptr->next;
        ptr->next = help;
        help->next = next;
        ptr = next;
    }
    ptr = head;
    while(ptr != NULL){
        next = ptr->next;
        if(ptr->rand == NULL)
            next->rand = NULL;
        else
            next->rand = ptr->rand->next;
        ptr = next->next;
    }
    //分离拷贝好的链表
    randnode* copyhead = head->next;
    ptr = head;
    randnode* help = copyhead;
    while(ptr != NULL && help != NULL){
        next = ptr->next->next;
        if(next == NULL)
            help->next = NULL;
        else
            help->next = next->next;
        ptr->next = next;
        ptr = next;
        help = help->next;
    }
    return copyhead;
}
//9.如何判断一个链表是否有环，要求时间复杂度为O(N)，额外空间复杂度为O(1)
node* iscyclelist(node* head)
{
    if(head == NULL || head->next == NULL)
        return NULL;
    node* fast = head->next->next;
    node* slow = head->next;
    while(fast != slow){
        if(fast == NULL || fast->next == NULL || fast->next->next == NULL)
            return NULL;
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = head;
    while(fast != slow){
        slow = slow->next;
        fast = fast->next;
    }
    return fast;
}

//10.如何判断两个无环链表是否相交
node* iscommonnocyclelist(node* head1,node* head2)
{
    if(head1 == NULL || head2 == NULL){
        return NULL;
    }
    int len1 = lenghtoflist(head1,NULL);
    int len2 = lenghtoflist(head2,NULL);
    node* ptr1 = head1;
    node* ptr2 = head2;
    if(len1 > len2)
    {
        int len = len1-len2;
        while(len>0){
            ptr1 = ptr1->next;
            len--;
        }
    }
    else
    {
        int len = len2-len1;
        while(len>0){
            ptr2 = ptr2->next;
            len--;
        }
    }
    while(ptr1 != NULL && ptr2 != NULL && ptr1 != ptr2){
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    if(ptr1 == ptr2)
        return ptr1;
    else
        return NULL;
}
//11.如何判断两个有环链表是否相交
node* iscommonnodecyclelist(node* head1,node* head2)
{
    if(head1 == NULL || head2 == NULL){
        return NULL;
    }
    node* help1 = iscyclelist(head1);
    node* help2 = iscyclelist(head2);
    //情况1，两个链表相交于1点
    if(help1 == help2){
        int len1 = lenghtoflist(head1,help1);
        int len2 = lenghtoflist(head2,help2);
        node* ptr1 = head1;
        node* ptr2 = head2;
        if(len1 > len2)
        {
            int len = len1-len2;
            while(len>0){
                ptr1 = ptr1->next;
                len--;
            }
        }
        else
        {
            int len = len2-len1;
            while(len>0){
                ptr2 = ptr2->next;
                len--;
            }
        }
        while(ptr1 != help1 && ptr2 != help2 && ptr1 != ptr2){
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        if(ptr1 == ptr2)
            return ptr1;
        else
            return help1;
    }//情况2，3
    else
    {
        node* temp = help1->next;
        while(temp != help1){
            if(temp == help2)
                break;
            temp = temp->next;
        }
        //情况2，各自为环，不相交
        if(temp == help1){
            cout<<"情况2，各自为环，不相交"<<endl;
            return NULL;
        }
        else//情况3,相交于一个环但是入环点不同
        {
            cout<<"情况3,相交于一个环但是入环点不同"<<endl;
            return help1;
        }
    }
}
//求链表的长度
int lenghtoflist(node* start,node* end)
{
    node* ptr = start;
    int len = 0;
    while(ptr != end){
        ptr = ptr->next;
        ++len;
    }
    return len;
}
//12.给定两个链表，如何判断两个链表是否相交,相交的话返回第一个相交的节点
node* arecommonlist(node* head1,node* head2)
{
    if(head1 == NULL || head2 == NULL){
        return NULL;
    }
    node* help1 = iscyclelist(head1);
    node* help2 = iscyclelist(head2);
    //1.两个都没有环
    if(help1 == NULL && help2 == NULL){
        cout<<"两个都没有环"<<endl;
        return iscommonnocyclelist(head1,head2);
    }
    //2.一个有环，一个没环
    else if((help1 == NULL && help2 != NULL) || (help1 != NULL && help2 == NULL)){
        cout<<"一个有环，一个没环"<<endl;
        return NULL;
    }
    //3.两个都有环
    else{
        cout<<"两个都有环"<<endl;
        return iscommonnodecyclelist(head1,head2);
    }
}
