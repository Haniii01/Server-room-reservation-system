//
//  manager.cpp
//  test
//
//  Created by cappuccino  on 2021/7/13.
//

#include "manager.hpp"
#include <string>
# include <fstream>

//默认构造
Manager::Manager()
{
    
}
//有参构造
Manager::Manager(string n, string p)
{
    Name = n;
    Password = p;
    initVector();
    
    //初始化机房信息
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);
    
    ComputerRoom com;
    while (ifs >> com.ComId && ifs >> com.MaxNum) {
        vCom.push_back(com);
    }
    ifs.close();
    cout << "机房的数量为：" << vCom.size() << endl;
}
//菜单界面
void Manager::operMenu()
{
    cout << "欢迎管理员：" << this->Name << "登录" << endl;
    cout << "\t\t  ---------------------------------\n";
    cout << "\t\t |                                |\n";
    cout << "\t\t |            1.添加账号           |\n";
    cout << "\t\t |                                |\n";
    cout << "\t\t |            2.查看账号           |\n";
    cout << "\t\t |                                |\n";
    cout << "\t\t |            3.查看机房           |\n";
    cout << "\t\t |                                |\n";
    cout << "\t\t |            4.清空预约           |\n";
    cout << "\t\t |                                |\n";
    cout << "\t\t |            0.注销登录           |\n";
    cout << "\t\t |                                |\n";
    cout << "\t\t  ---------------------------------\n";
    cout << "请输入您的操作：";
}
//添加账号
void Manager::addPerson()
{
    cout << "请输入添加账号的类型" << endl;
    cout << "1.添加学生" << endl;
    cout << "2.添加老师" << endl;
    
    string fileName;
    string tip;
    string errorTip;
    
    ofstream ofs;
    
    int select = 0;
    cin >> select;
    
    while (true) {
        if(select == 1)
        {
            //添加的是学生
            fileName = STUDENT_FILE;
            tip = "请输入学号：";
            errorTip = "学号重复，请重新输入";
            break;
        }
        else if(select == 2)
        {
            fileName = TEACHER_FILE;
            tip = "请输入职工编号：";
            errorTip = "职工重复，请重新输入";
            break;
        }
        else
        {
            cout << "请重新选择" << endl;
            cin >> select;
        }
    }
    
    //利用追加的方式写文件
    ofs.open(fileName,ios::out|ios::app);
    
    int id;
    string name;
    string pwd;
    
    cout << tip << endl;
    
    while (true) {
        cin >> id;
        bool ret =  checkRepeat(id, select);
        if(ret)
        {
            cout << errorTip << endl;
        }
        else
        {
            break;
        }
    }
    
//    cin >> id;
    
    cout << "请输入姓名：" << endl;
    cin >> name;
    
    cout << "请输入密码：" << endl;
    cin >> pwd;
    
    //向文件中添加数据
    ofs << id << " " << name << " " << pwd << " " << endl;
    cout << "添加成功" << endl;
    
    printf("press any key to continue......\n");
    getchar();
    
    ofs.close();
    
    //调用初始化容器借口，重新获取文件
    this -> initVector();
}

void printStudent(Student & s)
{
    cout << "学号：" << s.Id << "姓名：" << s.Name << endl;
}
void printTeacher(Teacher & t)
{
    cout << "学号：" << t.EmpId << "姓名：" << t.Name << endl;
}

//查看账号
void Manager::showPerson()
{
    cout << "请选择查看内容：" << endl;
    cout << "1.查看所有学生" << endl;
    cout << "2.查看所有老师" << endl;
    
    int select = 0;
    cin >> select;
    
    if(select == 1)
    {
        //查看学生
        cout << "所有学生信息如下：" << endl;
        for_each(vStu.begin(), vStu.end(), printStudent);
    }
    else if(select == 2)
    {
        //查看老师
        cout << "所有老师信息如下：" << endl;
        for_each(vTea.begin(), vTea.end(), printTeacher);
    }
    else
    {
        cout << "输入错误" << endl;
        return;
    }
    printf("press any key to continue......\n");
    getchar();
    
}
//查看机房信息
void Manager::showComputer()
{
    cout << "机房信息如下：" << endl;
    
    for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++) {
        cout << "机房编号：" << (*it).ComId << "机房最大容量：" << (*it).MaxNum << endl;
    }
    printf("press any key to continue......\n");
    getchar();
}
//清空预约记录
void Manager::cleanFile()
{
    ofstream ofs(ORDER_FILE, ios::trunc);
    ofs.close();
    
    cout << "清空成功" << endl;
    
    printf("press any key to continue......\n");
    getchar();
}
//初始化容器
void Manager::initVector()
{
    //确保容器清空
    vStu.clear();
    vTea.clear();
    
    //读取信息 学生
    ifstream ifs;
    ifs.open(STUDENT_FILE, ios::in);
    if(!ifs.is_open())
    {
        cout << "文件读取失败" << endl;
        return;
    }
    
    Student s;
    while (ifs >> s.Id && ifs >> s.Name && ifs >> s.Password) {
        vStu.push_back(s);
    }
    cout << "当前学生数量为：" << vStu.size() << endl;
    ifs.close();
    
    //读取信息 老师
    ifs.open(TEACHER_FILE, ios::in);
    if(!ifs.is_open())
    {
        cout << "文件读取失败" << endl;
        return;
    }
    
    Teacher t;
    while (ifs >> t.EmpId && ifs >> t.Name && ifs >> t.Password) {
        vTea.push_back(t);
    }
    cout << "当前老师数量为：" << vTea.size() << endl;
    ifs.close();
    
}

//检测重复 参数1 检测学号/职工号 参数2 检测类型
bool Manager::checkRepeat(int id, int type)
{
    if(type == 1)
    {
        //检测学生
        for(vector<Student>::iterator it = vStu.begin();it != vStu.end();it++)
        {
            if(id == it -> Id)
            {
                return true;
            }
        }
    }
    else
    {
        //检测老师
        for(vector<Teacher>::iterator it = vTea.begin();it != vTea.end();it++)
        {
            if(id == it -> EmpId)
            {
                return true;
            }
        }
    }
    return false;
}
