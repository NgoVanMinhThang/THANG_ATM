#pragma once
#include <bits/stdc++.h>
using namespace std;
class History
{
    string _strNoti;
    string _strUserSend;
    string _strUserReceive;
public:
    History() {};
    History(const History& a)
    {
        _strNoti = a._strNoti;
        _strUserSend = a._strUserSend;
        _strUserReceive = a._strUserReceive;
    }
    History(string _strnoti,string _struserSend,string _struserReceive)
    {
        _strNoti = _strnoti;
        _strUserSend = _struserSend;
        _strUserReceive = _struserReceive;
    }
    friend bool operator!=(History a, History b)
    {
        return (a._strUserSend == b._strUserSend || a._strUserReceive == b._strUserReceive);
    }
    string getNoti()
    {
        return _strNoti;
    }
    string getSend()
    {
        return _strUserSend;
    }
    string getReceive()
    {
        return _strUserReceive;
    }
    friend ostream& operator<<(ostream& os, History a)
    {
        os << a._strNoti <<endl<<a._strUserSend <<endl<< a._strUserReceive;
        return os;
    }
};

