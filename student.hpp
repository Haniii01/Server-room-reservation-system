//
//  student.hpp
//  test
//
//  Created by cappuccino  on 2021/7/13.
//
#pragma once
#ifndef student_hpp
#define student_hpp

#include <stdio.h>
#include "identify.h"
#include <iostream>
#include <string>
# include <vector>
#include "computerRoom.hpp"
#include <fstream>
#include "globalFile.h"
#include "orderFile.hpp"
using namespace std;
//学生类
class Student:public Identify
{
public:
    //默认构造
    Student();
    //有参构造 学号、姓名、密码
    Student(int i,string n,string p);
    //菜单界面
    virtual void operMenu();
    //申请预约
    void applyOrder();
    //查看自身预约
    void showMyOrder();
    //查看所有预约
    void showAllOrder();
    //取消预约
    void cancelOrder();
    //学生学号
    int Id;
    ~Student(){}
    //机房容器
    vector<ComputerRoom> vCom;
};

#endif /* student_hpp */
