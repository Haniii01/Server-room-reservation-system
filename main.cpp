#include <iostream>
#include <iomanip>
#include <cstring> // strcpy and strcat prototypes
#include <cstdlib> // exit prototype
#include "identify.h"
#include <fstream>
#include <string>
#include "globalFile.h"
# include "student.hpp"
# include "manager.hpp"
# include "teacher.hpp"

using namespace std;
//进入学生子菜单
void studentMenu(Identify * &student)
{
    //调用学生子菜单
    student -> operMenu();
    
    Student * stu = (Student *)student;
    
    int select = 0;
    cin >> select;
    
    while(true){
        if(select == 1)
        {
            //申请预约
            stu -> applyOrder();
            break;
        }
        else if(select == 2)
        {
            //查看我的预约
            stu -> showMyOrder();
            break;
        }
        else if(select == 3)
        {
            //查看所有人预约
            stu -> showAllOrder();
            break;
        }
        else if(select == 4)
        {
            //取消预约
            stu -> cancelOrder();
            break;
        }
        else if(select == 5)
        {
            //注销登录
            delete stu;
            cout << "注销成功" << endl;
            printf("press any key to continue......\n");
            getchar();
            return;
        }
        else if(select == 0)
        {
            cout << "退出" << endl;
            break;
        }
        else
        {
            cout << "输入错误，请重新输入" << endl;
            cin >> select;
            
        }
    }
}
//进入教师子菜单
void teacherMenu(Identify * &teacher)
{
    while (true) {
        //调用子菜单界面
        teacher -> operMenu();
        
        Teacher * tea = (Teacher*) teacher;
        
        int select = 0;
        while (true) {
            cin >> select;
            if (select == 1) {
                tea -> showAllOrder();
                break;
            }
            else if(select == 2)
            {
                tea -> validOrder();
                break;
            }
            else if(select == 0)
            {
                delete tea;
                cout << "注销成功" << endl;
                printf("press any key to continue......\n");
                getchar();
                return;
            }
            else
            {
                cout << "输入错误，请重新输入：" << endl;
            }
        }

    };
}

//进入管理员子菜单
void managerMenu(Identify * &manager)
{
    while (true)
    {
        //调用管理员子菜单
        manager -> operMenu();
        
        //将父类指针转为子类指针,调用子类里其他接口
        Manager * man = (Manager*)manager;
        
        int select = 0;
        //接收用户选项
        cin >> select;
        
        if(select == 1)
        {
            cout << "添加账号" << endl;
            man -> addPerson();
        }
        else if(select == 2)
        {
            cout << "查看账号" << endl;
            man -> showPerson();
        }
        else if(select == 3)
        {
            cout << "查看机房" << endl;
            man -> showComputer();
        }
        else if(select == 4)
        {
            cout << "清空预约" << endl;
            man -> cleanFile();
        }
        else
        {
            delete man;//销毁堆区对象
            cout << "注销成功" << endl;
            printf("press any key to continue......\n");
            getchar();
            
            
            return;
        }
        
    }
}
void LoginIn(string filename, int type)
{
    Identify * person = NULL;
    
    //读文件
    ifstream ifs;
    ifs.open(filename,ios::in);
    
    //判断文件是否存在
    if(!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }
    
    //准备接收用户信息
    int id = 0;
    string name;
    string passward;
    
    //判断身份
    if (type == 1)//学生身份
    {
        
        cout << "请输入你的学号：" << endl;
        cin >> id;
    }
    else if (type == 2)
    {
        
        cout << "请输入您的职工号：" << endl;
        cin >> id;
    }
    
    cout << "请输入用户名" << endl;
    cin >> name;
    
    cout << "请输入密码" << endl;
    cin >> passward;
    
    if (type == 1)//学生身份验证
    {
        int fId;
        string fName;
        string fPassward;
        while(ifs >> fId && ifs >> fName && ifs >> fPassward)
        {
           if(fId == id && fName == name && fPassward == passward)
           {
               cout << "学生验证登录成功!" << endl;
               //进入学生子菜单
               printf("press any key to continue......\n");
               getchar();
               person = new Student(id, name, passward);
               //进入学生身份子菜单
               studentMenu(person);
               return;
           }
        }
    }
    else if (type == 2)//教师身份验证
    {
        int fId;
        string fName;
        string fPassward;
        while(ifs >> fId && ifs >> fName && ifs >> fPassward)
        {
           if(fId == id && fName == name && fPassward == passward)
           {
               cout << "教师验证登录成功!" << endl;
               //进入老师子菜单
               printf("press any key to continue......\n");
               getchar();
               person = new Teacher(id, name, passward);
               //进入老师身份子菜单
               teacherMenu(person);
               return;
           }
        }
    }
    else if (type == 3)//管理员身份验证
    {
        string fName = "";
        string fPassward = "";
        while(ifs >> fName &&  ifs >> fPassward )
        {
           if(fName == name && fPassward == passward)
           {
               cout << "管理员验证登录成功!" << endl;
               //进入学生子菜单
               printf("press any key to continue......\n");
               person = new Manager(name, passward);
               
               managerMenu(person);
               
               return;
           }
        }
    }
}
int main() {
    int select = 0;
    while(true)
    {
        
        cout << endl << "请输入您的身份" << endl;
        cout << "\t\t  ---------------------------------\n";
        cout << "\t\t |                                |\n";
        cout << "\t\t |            1.学生代表            |\n";
        cout << "\t\t |                                |\n";
        cout << "\t\t |            2.老   师            |\n";
        cout << "\t\t |                                |\n";
        cout << "\t\t |            3.管 理 员           |\n";
        cout << "\t\t |                                |\n";
        cout << "\t\t |            0.退   出            |\n";
        cout << "\t\t |                                |\n";
        cout << "\t\t  ---------------------------------\n";

        cout << "请输入您的选择：";
//                getchar();
        cin >> select;
        switch (select) {
            case 1:
                LoginIn(STUDENT_FILE, 1);
                break;
            case 2:
                LoginIn(TEACHER_FILE, 2);
                break;
            case 3:
                LoginIn(ADMIN_FILE, 3);
                break;
            case 0:
                return 0;;
            default:
                cout << "输入字符有误，请重新输入"<< endl;
                break;
        }
    }
    

    
    return 0;
}


