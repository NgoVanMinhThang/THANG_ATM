#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

void resizeConsole(int _iWidth, int _iHeight)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, _iWidth, _iHeight, TRUE);
}

void textcolor(int _iX)
{
    HANDLE mau;
    mau = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mau, _iX);
}


void gotoxy(int _iX, int _iY)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { _iX - 1,_iY - 1 };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void ToMau(int _iX, int _iY, string _sA, int _iColor)
{
    gotoxy(_iX, _iY);
    textcolor(_iColor);
    cout << _sA;
    textcolor(7);
}
void SizeFont(int _iXX)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = _iXX;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
