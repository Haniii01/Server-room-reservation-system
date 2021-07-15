//
//  orderFile.cpp
//  test
//
//  Created by cappuccino  on 2021/7/15.
//

#include "orderFile.hpp"
//构造函数
OrderFile::OrderFile()
{
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);
    
    string date;
    string interval;
    string stuId;
    string stuName;
    string roomId;
    string status;
    
    size = 0;
    
    while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status) {
//        cout << date << endl;
//        cout << interval << endl;
//        cout << stuId << endl;
//        cout << stuName << endl;
//        cout << roomId << endl;
//        cout << status << endl;
//        cout << endl;
        
        string key;
        string value;
        map<string, string> m;
        
        int pos = date.find(":");
        if(pos != -1)
        {
            key = date.substr(0, pos);
            value = date.substr(pos+1, date.size());
            
            m.insert(make_pair(key, value));
        }
        
        pos = interval.find(":");
        if(pos != -1)
        {
            key = interval.substr(0, pos);
            value = interval.substr(pos+1, interval.size());
            
            m.insert(make_pair(key, value));
        }
        
        pos = stuId.find(":");
        if(pos != -1)
        {
            key = stuId.substr(0, pos);
            value = stuId.substr(pos+1, stuId.size());
            
            m.insert(make_pair(key, value));
        }
        
        pos = stuName.find(":");
        if(pos != -1)
        {
            key = stuName.substr(0, pos);
            value = stuName.substr(pos+1, stuName.size());
            
            m.insert(make_pair(key, value));
        }
        
        pos = roomId.find(":");
        if(pos != -1)
        {
            key = roomId.substr(0, pos);
            value = roomId.substr(pos+1, roomId.size());
            
            m.insert(make_pair(key, value));
        }
        
        pos = status.find(":");
        if(pos != -1)
        {
            key = status.substr(0, pos);
            value = status.substr(pos+1, status.size());
            
            m.insert(make_pair(key, value));
        }
        
        //将小map容器放入大map容器中
        orderData.insert(make_pair(size, m));
        size++;
    }
    ifs.close();
    
//    //测试最大map容器
//    for (map<int,map<string,string>>::iterator it = orderData.begin(); it != orderData.end(); it++) {
//        cout << "key = " << (*it).first << "value = " << endl;
//        for (map<string, string>::iterator mit = (*it).second.begin(); mit != (*it).second.end(); mit++) {
//            cout << "key = " << (*mit).first << "value = " <<(*mit).second << " ";
//        }
//        cout << endl;
//    }
}

//更新预约记录
void OrderFile::updateOrder()
{
    if(size == 0)
    {
        return;
    }
    ofstream ofs(ORDER_FILE, ios::out | ios:: trunc);
    for (int i = 0; i < size; i++) {
        ofs << "date:" << orderData[i]["date"] << " ";
        ofs << "interval:" << orderData[i]["interval"] << " ";
        ofs << "stuId:" << orderData[i]["stuId"] << " ";
        ofs << "stuName:" << orderData[i]["stuName"] << " ";
        ofs << "roomId:" << orderData[i]["roomId"] << " ";
        ofs << "status:" << orderData[i]["status"] << endl;
    }
    ofs.close();
}

//记录所有预约信息的容器，key记录条数，value记录具体的键值对信息
map<int, map<string,string>> orderData;
