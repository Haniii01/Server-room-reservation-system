//
//  teacher.hpp
//  test
//
//  Created by cappuccino  on 2021/7/13.
//
#pragma once
#ifndef teacher_hpp
#define teacher_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
#include "identify.h"
# include <algorithm>
#include <string>
#include "orderFile.hpp"
#include <vector>

//教师类设计
class Teacher:public Identify
{
public:
    //默认构造
    Teacher();
    //有参构造
    Teacher(int empid, string n, string p);
    //菜单界面
    virtual void operMenu();
    //查看所有预约
    void showAllOrder();
    //审核预约
    void validOrder();
    //职工号
    int EmpId;
    ~Teacher(){};
};

#endif /* teacher_hpp */
