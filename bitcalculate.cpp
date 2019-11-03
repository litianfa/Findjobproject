//
//  bitcalculate.cpp
//  c++
//
//  Created by litianfa on 2019/7/8.
//  Copyright © 2019 litianfa. All rights reserved.
//

#include "bitcalculate.hpp"

//案例2，如何不用任何额外变量交换两个整数的值,用异或操作
void changenum(int& a,int& b)
{
    a = a^b;
    b = a^b;
    a = a^b;
    return;
}
//案例3，给定两个32位整数a,b,返回这两个数中较大的，但是不能用任何比较判断
int flip(int n)
{
    return n ^ 1;
}

int sign(int n)
{
    return flip(n>>31 & 1);
}
int getmax(int a,int b)
{
    int c = a-b;
    int as = sign(a);
    int bs = sign(b);
    int cs = sign(c);
    int difab = as^bs;
    int sameab = flip(difab);
    int returnA = difab*as+sameab*cs;
    int returnB = flip(returnA);
    return a*returnA + b*returnB;
}
//案例4，给定一个整数数组arr，其中只有一个数出现了奇数次，其他的数都出现了偶数次，请打印这个数，要求时间复杂度O（N），额外空间复杂度O（1）
int getoddmemberofarr(vector<int>& arr)
{
    int e = 0;
    for(int i = 0;i<arr.size();i++){
        e = e^arr[i];
    }
    return e;
}
//案例5，给定一个整形数组arr,其中有两个数出现了奇数次，其他的数都出现了偶数次，打印这两个数
vector<int> gettwooddmemberofarr(vector<int>& nums)
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
