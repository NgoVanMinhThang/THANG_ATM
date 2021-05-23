#pragma once
#include <bits/stdc++.h>
using namespace std;
class countLogin
{
    string _strAccount_Number;
    int _d;
public:
    countLogin(string stk = "",int d = 0)
    {
        _strAccount_Number = stk;
        _d = d;
    }
    void operator=(const countLogin& a)
    {
        _strAccount_Number = a._strAccount_Number;
        _d = a._d;
    }
    void loginFail()
    {
        _d++;
    }
    int getD()
    {
        return _d;
    }
    string getID()
    {
        return _strAccount_Number;
    }
    friend bool operator==(countLogin a, countLogin b)
    {
        return (a.getID() == b.getID());
    }
    void operator*=(countLogin a)
    {
        _d = a.getD();
    }
    int operator++(int z)
    {
        loginFail();
        return 0;
    }
    friend ostream& operator<<(ostream& os, countLogin a)
    {
        os << a._strAccount_Number;
        return os;
    }
};
