//
//  matrix.hpp
//  c++
//  矩阵问题
//  Created by litianfa on 2019/7/11.
//  Copyright © 2019 litianfa. All rights reserved.
//

#ifndef matrix_hpp
#define matrix_hpp
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
//案例1，在行列都排好序的矩阵中找数
void findfromsortmatrix(vector<vector<int> > const& matrix,int k);
//案例2，之字形打印矩阵
void zprintmatrix(vector<vector<int> > const& vtr);
void printLevel(vector<vector<int> > const& vtr,int tR,int tC,int dR,int dC,bool f);
//案例3，转圈打印矩阵
void cycleprintmatrix(vector<vector<int> > const& vtr,int lrow,int lline,int rrow,int rline);
//案例4，设计RandomPool结构
template<typename T>
class Pool{
private:
    unordered_map<T,int> keyIndexMap;
    unordered_map<int,T> indexKeyMap;
    int size;
public:
    Pool():size(0){
        
    }
    void Insert(T key){
        typename unordered_map<T, int>::const_iterator got;
        got = keyIndexMap.find(key);
        if(got == keyIndexMap.end()){
            keyIndexMap.insert(std::pair<T,int>(key,size));
            indexKeyMap.insert(std::pair<int,T>(size++,key));
        }
    }
    
    void Delete(T key){
        typename unordered_map<T,int>::const_iterator it;
        it = keyIndexMap.find(key);
        if(it != keyIndexMap.end()){
            int deleteIndex = keyIndexMap[key];
            int lastIndex = --size;
            T lastKey = indexKeyMap[lastIndex];
            keyIndexMap[lastKey] = deleteIndex;
            indexKeyMap[deleteIndex] = lastKey;
            keyIndexMap.erase(key);
            indexKeyMap.erase(lastIndex);
        }
    }
    T getRandom(){
        if(size == 0){
            return NULL;
        }
        int randomIndex = rand()%size;
        return indexKeyMap[randomIndex];
    }
    
    void printpool() const{
        for(auto it = indexKeyMap.begin();it != indexKeyMap.end();it++){
            cout<<"[ "<<it->first<<" , "<<it->second<<" ]"<<" ";
        }
        cout<<endl;
    }
};

#endif /* matrix_hpp */
