#pragma once
#include <bits/stdc++.h>
using namespace std;
class BlockUser
{
    string _strID;
    string _strStatus;
public:
    BlockUser(string _ID="", string _Status="")
    {
        _strID = _ID;
        _strStatus = _Status;
    };
    friend ostream& operator<<(ostream& os, BlockUser a)
    {
        os << a._strID << endl << a._strStatus;
        return os;
    }
    string getID()
    {
        return _strID;
    }
    string getStatus()
    {
        return _strStatus;
    }
    friend bool operator==(BlockUser a, BlockUser b)
    {
        return (a.getID() == b.getID());
    }
    friend bool operator!=(BlockUser a, BlockUser b)
    {
        return (a.getID() != b.getID());
    }
    void operator*=(BlockUser a)
    {
        _strStatus = a.getStatus();
    }
};

