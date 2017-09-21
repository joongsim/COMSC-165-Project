//
//  linklt.h
//  t2
//
//  Created by Andrey Losev on 7/17/17.
//  Copyright © 2017 Andrey Losev. All rights reserved.
//
#ifndef linklt_h
#define linklt_h
struct listnode
{
    std::string time;
    double latitude;
    double longitude;
    std::string fname;
    listnode* next;
};
class linkl
{
private:
    listnode* head;
public:
    linkl();
    void insert(listnode*);
    void display();
    void tofile(char*);
    listnode* showhead();
};
#endif //linklt_h
