//
//  student.cpp
//  test
//
//  Created by cappuccino  on 2021/7/13.
//

#include "student.hpp"
using namespace std;
Student::Student()
{
    
}
//有参构造 学号、姓名、密码
Student::Student(int id,string n,string pa)
{
    Id = id;
    Name = n;
    Password = pa;
    
    //初始化机房信息
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);
    
    ComputerRoom com;
    while (ifs >> com.ComId && ifs >> com.MaxNum) {
        //将读取信息放入容器中
        vCom.push_back(com);
    }
    ifs.close();
}
//菜单界面
void Student::operMenu()
{
    cout << "欢迎学生代表：" << Name << "登录" << endl;
    cout << "\t\t  ---------------------------------\n";
    cout << "\t\t |                                |\n";
    cout << "\t\t |            1.申请预约            |\n";
    cout << "\t\t |                                |\n";
    cout << "\t\t |            2.查看我的预约        |\n";
    cout << "\t\t |                                |\n";
    cout << "\t\t |            3.查看所有预约        |\n";
    cout << "\t\t |                                |\n";
    cout << "\t\t |            4.取消预约            |\n";
    cout << "\t\t |                                |\n";
    cout << "\t\t |            0.注销登录            |\n";
    cout << "\t\t |                                |\n";
    cout << "\t\t  ---------------------------------\n";
    cout << "请输入您的操作：";
}

//申请预约
void Student::applyOrder()
{
    cout << "机房开放的时间为周一至周五" << endl;
    cout << "请输入申请预约的时间" << endl;
    cout << "1.周一" << endl;
    cout << "2.周二" << endl;
    cout << "3.周三" << endl;
    cout << "4.周四" << endl;
    cout << "5.周五" << endl;
    
    int date = 0;//日期
    int interval = 0;//时间段
    int room = 0; //机房编号
    
    while (true) {
        cin >> date;
        if (date >= 1 && date <= 5) {
            break;
        }
        else
            cout << "输入有误，请重新输入" << endl;
        
    };
    cout << "请输入申请预约的时间段：" << endl;
    cout << "1.上午" << endl;
    cout << "2.下午" << endl;
    
    while(true)
    {
        cin >> interval;
        if(interval == 1 || interval == 2)
        {
            break;
        }
        cout << "输入有误，请重新输入"  << endl;
    }
    
    cout << "请选择机房：" << endl;
    for (int i = 0; i < 3; i++) {
        cout << vCom[i].ComId << "号机房容量为：" << vCom[i].MaxNum << endl;
    }
    
    while (true) {
        cin >> room;
        if (room >= 1 && room <= 3) {
            break;
        }
        cout << "输入有误，请重新输入" << endl;
    }
    cout << "预约成功，审核中" << endl;
    
    ofstream ofs;
    ofs.open(ORDER_FILE, ios::app);
    
    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stuId:" << Id << " ";
    ofs << "stuName:" << Name << " ";
    ofs << "roomId:" << room << " ";
    ofs << "status:" << 1 << endl;
    
    ofs.close();
    
    printf("press any key to continue......\n");
    getchar();
}
//查看自身预约
void Student::showMyOrder()
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
        //string 转 int
        //string 利用 .c_str() 转 const char*
        //利用atoi(const char *)转 int
        if(Id == atoi(of.orderData[i]["stuId"].c_str()))
        {
            cout << "预约日期：周" << of.orderData[i]["date"] << endl;
            cout << "时间段：" << (of.orderData[i]["interval"] == "1" ? "上午" : "下午") << endl;
            cout << "机房号：" << of.orderData[i]["roomId"] << endl;
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
    }
    printf("press any key to continue......\n");
    getchar();
}
//查看所有预约
void Student::showAllOrder()
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
    getchar();
}
//取消预约
void Student::cancelOrder()
{
    OrderFile of;
    if (of.size == 0) {
        cout << "无预约记录！" << endl;
        printf("press any key to continue......\n");
        getchar();
        return;
    }
    
    cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;
    vector<int> v;//存放在最大容器中的下标编号
    int index = 1;
    for (int i = 0; i < of.size; i++) {
        //先是判断自身学号
        if(Id == atoi(of.orderData[i]["stuId"].c_str()))
        {
            //先审核状态，审核中或预约成功
            if(of.orderData[i]["status"] == "1" || of.orderData[i]["status"] == "2")
            {
                v.push_back(i);
                cout << index++ << "、" << endl;
                cout << "预约日期：周" << of.orderData[i]["date"] << " ";
                cout << "时间段：" << (of.orderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
                cout << "机房号：" << of.orderData[i]["roomId"] << " ";
                string status = "状态：";
                if(of.orderData[i]["status"] == "1")
                {
                    status += "审核中";
                }
                else if(of.orderData[i]["status"] == "2")
                {
                    status += "预约成功";
                }
                cout << status << endl;
            }
        }
    }
    
    cout << "请输入预约的记录,0代表返回" << endl;
    int select = 0;
    
    while (true) {
        cin >> select;
        
        if(select >= 0 && select <= v.size())
        {
            if (select == 0) {
                break;
            }
            else
            {
                of.orderData[v[select-1]]["status"] = "0";
                
                of.updateOrder();
                
                cout << "已取消预约" << endl;
            }
        }
        else
        {
            cout << "输入有误，请重新输入" << endl;
        }
    }
    printf("press any key to continue......\n");
    getchar();
}
