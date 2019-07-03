//
//  LinkedQueue.h
//  Project 3
//
//  Created by Mai Pham on 10/28/17.
//  Copyright © 2017 Mai Pham. All rights reserved.
//

#ifndef LinkedQueue_h
#define LinkedQueue_h
#include <iostream>
using namespace std;

template <typename T>
class LinkedQueue
{
private:
    struct Node
    {
        T data;
        Node *next;
    };
    Node *head;
    Node *end;
    int count;
    
public:
    LinkedQueue()
    {
        head = end = NULL;
        count = 0;
    }
    void enqueue(T t)
    {
        Node *temp = new Node;
        temp->data = t;
        temp->next = NULL;
        if (head == NULL || end == NULL)
            head = end = temp;
        else
        {
            end->next = temp;
            end = temp;
        }
        count++;
    }
    void dequeue()
    {
        Node *temp = new Node;
        if (head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
            count--;
        }
    }
    void printList()
    {
        Node *cur = head;
        int i = 1;
        while (cur != NULL)
        {
            cout << i << " " << cur->data << endl;
            cur = cur->next;
            i++;
        }
    }
    T front()
    {
        if(empty())
            cout << "Error!!!" << endl;
        return head->data;
    }
    int size()
    {
        return count;
    }
    bool empty()
    {
        return (count == 0);
    }
};

#endif /* LinkedQueue_h */

