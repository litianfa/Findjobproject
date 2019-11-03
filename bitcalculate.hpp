//
//  bitcalculate.hpp
//  c++
//
//  Created by litianfa on 2019/7/8.
//  Copyright © 2019 litianfa. All rights reserved.
//

#ifndef bitcalculate_hpp
#define bitcalculate_hpp
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

//案例2，如何不用任何额外变量交换两个整数的值,用异或操作
void changenum(int& a,int& b);
//案例3，给定两个32位整数a,b,返回这两个数中较大的，但是不能用任何比较判断
int getmax(int a,int b);
//案例4，给定一个整数数组arr，其中只有一个数出现了奇数次，其他的数都出现了偶数次，请打印这个数，要求时间复杂度O（N），额外空间复杂度O（1）
int getoddmemberofarr(vector<int>& arr);
//案例5，给定一个整形数组arr,其中有两个数出现了奇数次，其他的数都出现了偶数次，打印这两个数
vector<int> gettwooddmemberofarr(vector<int>& nums);

#endif /* bitcalculate_hpp */
