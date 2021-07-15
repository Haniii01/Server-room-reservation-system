//
//  manager.hpp
//  test
//
//  Created by cappuccino  on 2021/7/13.
//
#pragma once
#ifndef manager_hpp
#define manager_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
#include "identify.h"
# include "globalFile.h"
# include <vector>
# include "student.hpp"
# include "teacher.hpp"
#include "computerRoom.hpp"

class Manager:public Identify
{
public:
    //默认构造
    Manager();
    //有参构造
    Manager(string n, string p);
    //菜单界面
    virtual void operMenu();
    //添加账号
    void addPerson();
    //查看账号
    void showPerson();
    //查看机房信息
    void showComputer();
    //清空预约记录
    void cleanFile();
    //初始化容器
    void initVector();
    //检测重复 参数1 检测学号/职工号 参数2 检测类型
    bool checkRepeat(int id, int type);
    //学生容器
    vector<Student>vStu;
    //教师容器
    vector<Teacher>vTea;
    //机房信息容器
    vector<ComputerRoom>vCom;
    ~Manager(){};
};

#endif /* manager_hpp */
