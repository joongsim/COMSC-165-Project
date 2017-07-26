//
//  linkl.cpp
//  t2
//
//  Created by Andrey Losev on 7/17/17.
//  Copyright © 2017 Andrey Losev. All rights reserved.
//
#include <iostream>
using namespace std;
#include "linklt.hpp"
#include <string>
linkl::linkl()
{
    head = nullptr;
}

void linkl::insert(listnode* a)
{
    listnode* newnode= new listnode;
    newnode->time = a->time;
    newnode->latitude = a->latitude;
    newnode->longitude = a->longitude;
    newnode->fname = a->fname;
    newnode->next = nullptr;
    listnode* nodeptr;
    listnode* prevnode = nullptr;
    if (!head)
    {
        head = newnode;
    }
    else
    {
        nodeptr = head;
        while (nodeptr != nullptr && (strcmp(nodeptr->time.c_str(), newnode->time.c_str()) < 0))
        {
            prevnode = nodeptr;
            nodeptr = nodeptr->next;
        }
        if (prevnode == nullptr)
        {
            head = newnode;
            newnode->next = nodeptr;
        }
        else
        {
            prevnode->next = newnode;
            newnode->next = nodeptr;
        }
    }
}
void linkl::display()
{
    listnode* nodeptr = head;
    while(nodeptr)
    {
        cout << nodeptr->time << endl;
        nodeptr = nodeptr->next;
    }
    cout << "\n";
}

void linkl::tofile(char* filename)
{
    listnode* nodeptr = head;
    while(nodeptr)
    {
        //kml stuff goes here
        cout << nodeptr->time;
        //kml stuff ends
        nodeptr = nodeptr->next;
    }
}

listnode* linkl::showhead()
{
    return head;
}
