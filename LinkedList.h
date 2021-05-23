#pragma once
#include <bits/stdc++.h>
#include "Admin.h"
#include "Card.h"
#include "User.h"
#include "BlockUser.h"
#include "History.h"
#include "countLogin.h"
using namespace std;
template <class DataType>
class Node
{
public:
    DataType _data;

    Node* _pNext;


    Node(DataType data)
    {
        _data = data;
        _pNext = NULL;
    }

    void display()
    {
        cout << _data<<endl;
    }
};
template <class DataType>
class LinkedList
{
    Node<DataType>* _pHead;
    Node<DataType>* _pTail;
    int _iSize;
public:
    LinkedList()
    {
        _pHead = NULL;
        _pTail = NULL;
        _iSize = 0;
    };

    void addHead(DataType data)
    {
        Node<DataType>* pAdd = new Node<DataType>(data);
        if (_pHead == NULL) _pHead = _pTail = pAdd;
        else
        {
            pAdd->_pNext = _pHead;
            _pHead = pAdd;
        }
        _iSize++;
    }

    void addTail(DataType data)
    {
        Node<DataType>* pAdd = new Node<DataType>(data);
        if (_pHead == NULL) _pHead = _pTail = pAdd;
        else
        {
            _pTail->_pNext = pAdd;
            _pTail = pAdd;
        }
        _iSize++;
    }

    void display()
    {
        Node<DataType>* pWalker = _pHead;
        while (pWalker != NULL)
        {
            pWalker->display();
            pWalker = pWalker->_pNext;
        }
    }

    void displayID()
    {
        ofstream f("Info.txt");
        Node<DataType>* pWalker = _pHead;
        while (pWalker != NULL)
        {
            if (pWalker == _pTail)
                f << pWalker->_data;
            else f << pWalker->_data << endl;
            pWalker = pWalker->_pNext;
        }
    }

    void displayHistory()
    {
        ofstream f("History.txt");
        Node<DataType>* pWalker = _pHead;
        while (pWalker != NULL)
        {
            if (pWalker == _pTail)
                f << pWalker->_data;
            else f << pWalker->_data << endl;
            pWalker = pWalker->_pNext;
        }
    }

    void displayCard()
    {
        ofstream f("Card.txt");
        Node<DataType>* pWalker = _pHead;
        while (pWalker != NULL)
        {
            if (pWalker == _pTail)
                f << pWalker->_data;
            else f << pWalker->_data << endl;
            pWalker = pWalker->_pNext;
        }
    }

    void displayBlockList()
    {
        ofstream f("ListBlockUser.txt");
        Node<DataType>* pWalker = _pHead;
        while (pWalker != NULL)
        {
            if (pWalker == _pTail)
                f << pWalker->_data;
            else f << pWalker->_data << endl;
            pWalker = pWalker->_pNext;
        }
    }

    void displayLogin()
    {
        ofstream f("countLogin.txt");
        Node<DataType>* pWalker = _pHead;
        while (pWalker != NULL)
        {
            if (pWalker == _pTail)
                f << pWalker->_data;
            else f << pWalker->_data << endl;
            pWalker = pWalker->_pNext;
        }
    }

    void remove(DataType data)
    {
        Node<DataType>* pWalker = _pHead, * pTemp = NULL;
        while ((pWalker != NULL) && (pWalker->_data != data))
        {
            pTemp = pWalker;
            pWalker = pWalker->_pNext;
        }
        if (pWalker == NULL) return;
        if (pTemp != NULL)
        {
            if (pWalker == _pTail)
            {
                _pTail = pTemp;
                _pTail->_pNext = NULL;
            }
            pTemp->_pNext = pWalker->_pNext;
            delete pWalker;
            _iSize--;
        }
    }

    bool checkAdmin(DataType data)
    {
        Node<DataType>* pWalker = _pHead;
        Node<DataType>* tmp = new Node<DataType>(data);
        while (pWalker != NULL)
        {
            if (pWalker->_data == tmp->_data) return true;
            pWalker = pWalker->_pNext;
        }
        return false;
    }

    bool checkUser(DataType data)
    {
        Node<DataType>* pWalker = _pHead;
        Node<DataType>* tmp = new Node<DataType>(data);
        while (pWalker != NULL)
        {
            if (pWalker->_data * tmp->_data) return true;
            pWalker = pWalker->_pNext;
        }
        return false;
    }

    bool search(DataType data)
    {
        Node<DataType>* pWalker = _pHead;
        while (pWalker != NULL)
        {
            if (pWalker->_data ==data) return true;
            pWalker = pWalker->_pNext;
        }
        return false;
    }


    bool search1(DataType data)
    {
        Node<DataType>* pWalker = _pHead;
        while (pWalker != NULL)
        {
            if (pWalker->_data * data) return true;
            pWalker = pWalker->_pNext;
        }
        return false;
    }

    bool search11(DataType data)
    {
        Node<DataType>* pWalker = _pHead;
        while (pWalker != NULL)
        {
            if (pWalker->_data == data) return true;
            pWalker = pWalker->_pNext;
        }
        return false;
    }

    DataType search2(DataType data)
    {
        Node<DataType>* pWalker = _pHead;
        while (pWalker != NULL)
        {
            if (pWalker->_data * data) return pWalker->_data;
            pWalker = pWalker->_pNext;
        }
    }


    void search3(DataType data, LinkedList& l)
    {
        Node<DataType>* pWalker = _pHead;
        while (pWalker != NULL)
        {
            if (pWalker->_data != data)
            {
                l.addTail(pWalker->_data);
            }
            pWalker = pWalker->_pNext;
        }
    }


    DataType search4(DataType data)
    {
        Node<DataType>* pWalker = _pHead;
        while (pWalker != NULL)
        {
            if (pWalker->_data == data) return pWalker->_data;
            pWalker = pWalker->_pNext;
        }
    }


    bool search5(DataType data)
    {
        Node<DataType>* pWalker = _pHead;
        while (pWalker != NULL)
        {
            if (pWalker->_data == data) return true;
            pWalker = pWalker->_pNext;
        }
        return false;
    }


    void changeValue(DataType data)
    {
        for (Node<DataType>* pWalker = _pHead; pWalker; pWalker = pWalker->_pNext)
        {
            if (pWalker->_data * data)
            {
                pWalker->_data *= data;
                return;
            }
        }
    }

    void changeValue1(DataType data)
    {
        for (Node<DataType>* pWalker = _pHead; pWalker; pWalker = pWalker->_pNext)
        {
            if (pWalker->_data == data)
            {
                pWalker->_data *= data;
                return;
            }
        }
    }


    DataType loginFailUp(DataType& data)
    {
        for (Node<DataType>* pWalker = _pHead; pWalker; pWalker = pWalker->_pNext)
        {
            if (pWalker->_data == data)
            {
                pWalker->_data++;
                return pWalker->_data;
            }
        }
    }


    DataType operator[](int i)
    {
        Node<DataType>* pWalker = _pHead;
        int ii = 0;
        for (Node<DataType>* pWalker = _pHead; pWalker; pWalker = pWalker->_pNext)
        {
            if (ii == i)
                return pWalker->_data;
            else ii++;
        }
    }

    int getSize()
    {
        return _iSize;
    }
};

