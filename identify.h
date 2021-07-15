//
//  Header.h
//  c++_exercise
//
//  Created by cappuccino  on 2021/7/13.
//
#pragma once
#ifndef Header_h
#define Header_h
#include <iostream>
using namespace std;

//身份抽象基类
class Identify
{
public:
    virtual void operMenu() = 0;
    
    string Name;
    string Password;
    
};


#endif /* Header_h */
