//
//  computerRoom.hpp
//  test
//
//  Created by cappuccino  on 2021/7/14.
//

#ifndef computerRoom_hpp
#define computerRoom_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
//机房类
class ComputerRoom
{
public:
    int ComId;//机房id号
    int MaxNum; // 机房最大容量
    ComputerRoom(){
        ComId = 0;
        MaxNum = 0;
    }
    ComputerRoom(int comid, int maxnum)
    {
        ComId = comid;
        MaxNum = maxnum;
    }
};


#endif /* computerRoom_hpp */
