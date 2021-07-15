//
//  teacher.cpp
//  test
//
//  Created by cappuccino  on 2021/7/13.
//

#include "teacher.hpp"
//默认构造
Teacher::Teacher()
{
    
}
//有参构造
Teacher::Teacher(int empid, string n, string p)
{
    EmpId = empid;
    Name = n;
    Password = p;
}
//菜单界面
void Teacher::operMenu()
{
    cout << "欢迎教师：" << Name << "登录！" << endl;
    cout << "\t\t  ---------------------------------\n";
    cout << "\t\t |                                |\n";
    cout << "\t\t |            1.查看所有预约      |\n";
    cout << "\t\t |                                |\n";
    cout << "\t\t |            2.审核预约          |\n";
    cout << "\t\t |                                |\n";
    cout << "\t\t |            0.注销登录          |\n";
    cout << "\t\t |                                |\n";
    cout << "\t\t  ---------------------------------\n";
    cout << "请选择您的操作：";
}

//查看所有预约
void Teacher::showAllOrder()
{
    OrderFile of;
    if(of.size == 0)
    {
        cout << "无预约记录！" << endl;
        printf("press any key to continue......\n");
        getchar();
        return;
    }
    for (int i = 0; i < of.size; i ++) {
        cout << i+1 <<":" << endl;
        cout << "预约日期：周" << of.orderData[i]["date"] << " ";
        cout << "时间段：" << (of.orderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
        cout << "学号：" << of.orderData[i]["stuName"] << " ";
        cout << "姓名" << of.orderData[i]["roomId"] << " ";
        cout << "机房号：" << of.orderData[i]["roomId"] << " ";
        string status = "状态：";
        //1 审核中 2 已预约 -1 预约失败 0 取消预约
        if(of.orderData[i]["status"] == "1")
        {
            status += "审核中";
        }
        else if(of.orderData[i]["status"] == "2")
        {
            status += "预约成功";
        }
        else if(of.orderData[i]["status"] == "-1")
        {
            status += "预约失败，审核未通过";
        }
        else
        {
            status += "预约已取消";
        }
        cout << status << endl;
    }
    printf("press any key to continue......\n");
    getchar();}
//审核预约
void Teacher::validOrder()
{
    OrderFile of;
    if(of.size == 0)
    {
        cout << "无预约记录！" << endl;
        printf("press any key to continue......\n");
        getchar();
        return;
    }
    
    vector<int>v;
    int index = 0;
    
    cout << "待审核的预约记录如下：" << endl;
    for (int i = 0; i < of.size; i++) {
        if(of.orderData[i]["status"] == "1")
        {
            v.push_back(i);
            cout << ++index << "：";
            cout << "预约日期：周" << of.orderData[i]["date"] << " ";
            cout << "时间段：" << (of.orderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
            cout << "学号：" << of.orderData[i]["stuName"] << " ";
            cout << "姓名" << of.orderData[i]["roomId"] << " ";
            cout << "机房号：" << of.orderData[i]["roomId"] << " ";
            string status = "状态：审核中";
            cout << status << endl;
        }
    }
    cout << "请输入审核的预约记录，0代表返回" << endl;
    int select = 0;//接收用户选择的预约记录
    int ret = 0;//接收预约结果记录
    
    while (true) {
        cin >> select;
        if(select >= 0 && select <= v.size())
        {
            if (select == 0) {
                break;
            }
            else
            {
                cout << "请输入审核结果1.通过2.不通过" << endl;
                cin >> ret;
                if(ret == 1)
                {
                    of.orderData[v[select - 1]]["status"] = "2";
                }
                else
                {
                    of.orderData[v[select - 1]]["status"] = "-1";
                }
                of.updateOrder();
                cout << "审核完毕" << endl;
                break;
            }
        }
        else
        {
            cout << "输入有误，请重新输入" << endl;
        }
    }
    printf("press any key to continue......\n");
    getchar();
    return;
}
