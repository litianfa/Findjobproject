//
//  matrix.cpp
//  c++
//
//  Created by litianfa on 2019/7/11.
//  Copyright © 2019 litianfa. All rights reserved.
//

#include "matrix.hpp"

//案例1，在行列都排好序的矩阵中找数
void findfromsortmatrix(vector<vector<int> > const& matrix,int k)
{
    //必须从矩阵画右上角或者左下角开始查找，这样才能实现时间复杂度为O(N+M),额外空间复杂度为O(1)
    //从右上角
    int strow = 0;
    int stline = (int)matrix[0].size()-1;
    while(strow >= 0&& strow < matrix.size()&&stline >= 0&& stline < matrix.size()){
        if(matrix[strow][stline] > k){
            stline--;
        }
        else if(matrix[strow][stline] < k){
            strow++;
        }
        else if(matrix[strow][stline] == k){
            cout<<" k is belong to the matrix["<<strow<<"]["<<stline<<"]"<<endl;
            break;
        }
    }
}
//案例2，之字形打印矩阵
void zprintmatrix(vector<vector<int> > const& vtr)
{
    int tR = 0;
    int tC = 0;
    int dR = 0;
    int dC = 0;
    unsigned long endR = vtr.size()-1;
    unsigned long endC = vtr[0].size() - 1;
    bool fromUp = false;
    while(tR != endR + 1){
        printLevel(vtr,tR,tC,dR,dC,fromUp);
        tR = tC == endC ? tR + 1: tR;
        tC = tC == endC ? tC : tC + 1;
        dC = dR == endR ? dC + 1 : dC;
        dR = dR == endR ? dR : dR + 1;
        fromUp = !fromUp;
    }
    cout<<endl;
    
}

void printLevel(vector<vector<int> > const& vtr,int tR,int tC,int dR,int dC,bool f)
{
    if(f){
        while(tR != dR + 1){
            cout<<vtr[tR++][tC--]<<" ";
        }
    }
    else{
        while(dR != tR - 1){
            cout<<vtr[dR--][dC++]<<" ";
        }
    }
}

//案例3，转圈打印矩阵
void cycleprintmatrix(vector<vector<int> > const& vtr,int lrow,int lline,int rrow,int rline)
{
    if(lrow == rrow && lline == rline){
        cout<<vtr[lrow][lline]<<endl;
        return;
    }
    if(lrow>rrow)
        return;
    if(lline>rline)
        return;
    if(rrow == lrow){
        while(lline != rline){
            cout<<vtr[lrow][lline++]<<" ";
        }
        cycleprintmatrix(vtr,lrow,lline,rrow,rline);
    }
    if(lline == rline){
        while(lrow != rrow){
            cout<<vtr[lrow++][lline]<<" ";
        }
        cycleprintmatrix(vtr,lrow,lline,rrow,rline);
    }
    int l = lline;
    int r = lrow;
    while(l != rline){
        cout<<vtr[lrow][l++]<<" ";
    }
    while(r != rrow){
        cout<<vtr[r++][rline]<<" ";
    }
    while(l != lline){
        cout<<vtr[rrow][l--]<<" ";
    }
    while(r != lrow){
        cout<<vtr[r--][lline]<<" ";
    }
    cycleprintmatrix(vtr,lrow+1,lline+1,rrow-1,rline-1);
}
