#pragma once
#include <bits/stdc++.h>
using namespace std;
class User
{
    string _strID;
    string _strName;
    long long _llWallet;
    string _strType;
public:
    User() {};
    User(const User& a)
    {
        _strID = a._strID;
        _strName = a._strName;
        _llWallet = a._llWallet;
        _strType = a._strType;
    }
    User(string _ID, string _Name, long long  _Wallet, string _Type="VND")
    {
        _strID = _ID;
        _strName = _Name;
        _llWallet = _Wallet;
        _strType = _Type;
    };
    friend ostream& operator<<(ostream& os, User a)
    {
        os << a._strID << endl << a._strName << endl << a._llWallet << endl << a._strType;
        return os;
    }
    string getID()
    {
        return _strID;
    }
    string getName()
    {
        return _strName;
    }
    long long getWallet()
    {
        return _llWallet;
    }
    void Except_Money(long long l)
    {
        _llWallet -= l;
    }
    void Plus_Money(long long l)
    {
        _llWallet += l;
    }
    string getType()
    {
        return _strType;
    }
    friend bool operator*(User a, User b)
    {
        return (a.getID() == b.getID());
    }
    void operator*=(User a)
    {
        _llWallet = a.getWallet();
    }
    friend bool operator==(User a, User b)
    {
        return (a.getID() == b.getID());
    }
    friend bool operator!=(User a, User b)
    {
        return (a.getID() != b.getID());
    }
};

