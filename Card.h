#pragma once
#include <bits/stdc++.h>
using namespace std;
class Card
{
    string _strID;
    string _strPIN;
public:
    Card(string _ID = "", string _PIN = "123456")
    {
        _strID = _ID;
        _strPIN = _PIN;
    };
    string getID()
    {
        return _strID;
    }
    string getPIN()
    {
        return _strPIN;
    }
    void Change_PIN(string s)
    {
        _strPIN = s;
    }
    friend bool operator*(Card a, Card b)
    {
        return (a.getID() == b.getID() && a.getPIN() == b.getPIN());
    }

    friend bool operator==(Card a, Card b)
    {
        return (a.getID() == b.getID());
    }

    friend bool operator!=(Card a, Card b)
    {
        return (a.getID() != b.getID());
    }
    void operator*=(Card a)
    {
        _strPIN = a.getPIN();
    }

    friend ostream& operator<<(ostream& os, Card a)
    {
        os <<a._strID <<" "<< a._strPIN;
        return os;
    }
};
