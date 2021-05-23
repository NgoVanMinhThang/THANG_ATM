#include "LinkedList.h"
#include "Graphic.h"
#include<string.h>
#include<iostream>
#pragma warning(disable:4996)
#define YELLOW textcolor(14);
#define BLUE textcolor(9);
#define GREEN textcolor(10);
#define MAUXANH textcolor(2);
#define WHITE textcolor(15);
#define RED textcolor(4);
#define LISTADMIN LinkedList<Admin> listAdmin, LinkedList<User> listUser, LinkedList<Card> listCard,LinkedList<History> listLog,LinkedList<BlockUser> listBlockUser,LinkedList<countLogin> listLogin
#define CALLLIST listAdmin,listUser,listCard,listLog,listBlockUser,listLogin
#define ClearSceen system("cls");
using namespace std;
void loadAdmin(LinkedList<Admin>& lListAdmin);
void loadID(LinkedList<User>& listUser);
void loadCard(LinkedList<Card>& listCard);
void loadLog(LinkedList<History>& listLog);
void loadBlockList(LinkedList<BlockUser>& listBlockUser);
void loadlistLogin(LinkedList<countLogin>& listLogin);
void showMain(LISTADMIN);
void showAccessAdmin(LISTADMIN);
void showAccessUser(LISTADMIN,string sUserNow);
void showLoginUser(LISTADMIN);
void showLoginAdmin(LISTADMIN);
void adminAddUser(LISTADMIN);
void adminDeleteUser(LISTADMIN);
void adminUnlockUser(LISTADMIN);
void adminShowUser(LISTADMIN);

void userXemSoDu(LISTADMIN,string sUserNow);
void userRutTien(LISTADMIN, string sUserNow);
void userChuyenTien(LISTADMIN, string sUserNow);
void userNoiDungGD(LISTADMIN, string sUserNow);
void userChangePin(LISTADMIN, string sUserNow);

void updateHistory(LISTADMIN);
void updateID(LISTADMIN);
void updateCard(LISTADMIN);
void updateListBlock(LISTADMIN);
void updateListLogin(LISTADMIN);

void setKhung(LISTADMIN);

const string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), " %X ngày %d tháng %m năm %Y", &tstruct);
	return buf;
}

void inputPass(string& pw);
bool checkLoginAdmin(string _strUser, string _strPass, LinkedList<Admin> listAdmin);
bool checkLoginUser(string _strUser, string _strPass, LISTADMIN);
void checkRutTien(LISTADMIN, long long _llWallet, User tmp);

BOOL WINAPI SetConsoleOutputCP(_In_ UINT wCodePageID);

int main() {
	SetConsoleOutputCP(65001);
	resizeConsole(800, 600);
	LinkedList<Admin> listAdmin;LinkedList<User> listUser;LinkedList<Card> listCard;LinkedList<History> listLog;LinkedList<BlockUser> listBlockUser;LinkedList<countLogin> listLogin;
	loadAdmin(listAdmin);loadCard(listCard);loadLog(listLog);loadID(listUser);loadBlockList(listBlockUser);loadlistLogin(listLogin);
	showMain(CALLLIST);
	system("pause >nul");
}

void loadlistLogin(LinkedList<countLogin>& listLogin) {
	ifstream f;
	f.open("countLogin.txt");
	string _strAccountNumber;
	while (!f.eof()) {
		f >> _strAccountNumber;
		countLogin tmp(_strAccountNumber, 0);
		listLogin.addTail(tmp);
	}
	f.close();
}
void loadAdmin(LinkedList<Admin>& lListAdmin) {
	ifstream f;
	f.open("Admin.txt");
	while (!f.eof()) {
		bool _bA = false;
		string sU, sP, stmp;
		getline(f, stmp);
		for (int i = 0; i < stmp.size(); i++) {
			if (stmp[i] == ' ') _bA = true;
			else if (_bA == false) sU.push_back(stmp[i]);
			else sP.push_back(stmp[i]);
		}
		Admin ttmp(sU, sP);
		lListAdmin.addTail(ttmp);
	}
	f.close();
}
void loadID(LinkedList<User>& listUser) {
	ifstream f;
	f.open("Info.txt");
	string sNumber, sName, sType;
	long lWallet;
	while (!f.eof()) {
		sNumber = "";
		sName = "";
		lWallet = 0;
		sType = "";
		f >> sNumber;
		f.ignore();
		getline(f, sName);
		f >> lWallet;
		f >> sType;
		User ttmp(sNumber, sName, lWallet, sType);
		listUser.addTail(ttmp);
		f.ignore();
	}
	f.close();
}
void loadCard(LinkedList<Card>& listCard) {
	ifstream f;
	f.open("Card.txt");
	string sU, sP, sTmp;
	while (!f.eof()) {
		sU = "";
		sP = "";
		bool a = false;
		getline(f, sTmp);
		for (int i = 0; i < sTmp.size(); i++) {
			if (sTmp[i] == ' ') a = true;
			else if (a == false) sU.push_back(sTmp[i]);
			else sP.push_back(sTmp[i]);
		}
		Card ttmp(sU, sP);
		listCard.addTail(ttmp);
	}
	f.close();
}
void loadLog(LinkedList<History>& listLog) {
	ifstream f;
	f.open("History.txt");
	string sTmp;
	string sNoti, sSend, sReceive;
	while (!f.eof()) {
		sSend = "";
		sReceive = "";
		sNoti = "";
		getline(f, sNoti);
		f >> sSend;
		f >> sReceive;
		f.ignore();
		History h(sNoti,sSend,sReceive);
		listLog.addTail(h);
	}
	f.close();
}
void loadBlockList(LinkedList<BlockUser>& listBlockUser) {
	ifstream f;
	f.open("ListBlockUser.txt");
	string _sID;
	string _sStatus;
	while (!f.eof()) {
		f >> _sID;
		f >> _sStatus;
		BlockUser user(_sID,_sStatus);
		listBlockUser.addTail(user);
	}
	f.close();
}
void updateHistory(LISTADMIN) {
	listLog.displayHistory();
}
void updateID(LISTADMIN) {
	listUser.displayID();
}
void updateCard(LISTADMIN) {
	listCard.displayCard();
}
void updateListBlock(LISTADMIN) {
	listBlockUser.displayBlockList();
}
void updateListLogin(LISTADMIN) {
	listLogin.displayLogin();
}

void showLoginAdmin(LISTADMIN) {
	setKhung(CALLLIST);
	bool _bA = false;
	while (!_bA) {
		YELLOW
			gotoxy(42, 15); cout << "* ** ** ** ** ** ** *";
		gotoxy(42, 16); cout << "*  "; GREEN cout << "ĐĂNG NHẬP ADMIN"; YELLOW cout << "  *" << endl;
		gotoxy(42, 17);  cout << "* ** ** ** ** ** ** *";
		gotoxy(42, 18); BLUE cout << "User :";
		gotoxy(42, 19); BLUE cout << "Pass :";
		gotoxy(53, 18); WHITE string user = ""; cin >> user;
		gotoxy(53, 19); WHITE string Pass; inputPass(Pass);
		gotoxy(41, 20);
		if (checkLoginAdmin(user, Pass, listAdmin)) {
			MAUXANH cout << "Bạn đã đăng nhập thành công"; _bA = true;
			Sleep(200);
			ClearSceen
				setKhung(CALLLIST);
			showAccessAdmin(CALLLIST);
		}
		else {
			RED
				cout << "Bạn đã nhập sai, vui lòng thử lại";
			Sleep(200);
			ClearSceen
				setKhung(CALLLIST);
		}
	}
}
void showAccessAdmin(LISTADMIN) {
	setKhung(CALLLIST);
	ToMau(32, 13, "* * * * * * * * * *MENU* * * * * * * * * *", 14);
	ToMau(40, 14, "1. Xem danh sách tài khoản", 202);
	ToMau(40, 15, "2. Thêm tài khoản", 14);
	ToMau(40, 16, "3. Xóa tài khoản", 14);
	ToMau(40, 17, "4. Mở khóa tài khoản", 14);
	ToMau(40, 18, "5. Thoát", 14);
	ToMau(30, 19, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	int _iChoose = 0;
	int _iToaDo = 14;
	do {
		char _cA = _getch();
		if (_cA == 80) _iChoose = 1;
		else if (_cA == 72) _iChoose = 2;
		else if (_cA == 13) _iChoose = 3;
		else _iChoose = 0;
		if (_iChoose == 1 && _iToaDo < 19) _iToaDo++;
		else if (_iChoose == 2 && _iToaDo > 13) _iToaDo--;
		if (_iToaDo == 14) {
			ToMau(40, 14, "1. Xem danh sách tài khoản", 202);
			ToMau(40, 15, "2. Thêm tài khoản", 14);
			ToMau(40, 16, "3. Xóa tài khoản", 14);
			ToMau(40, 17, "4. Mở khóa tài khoản", 14);
			ToMau(40, 18, "5. Thoát", 14);
		}
		if (_iToaDo == 15) {
			ToMau(40, 14, "1. Xem danh sách tài khoản", 14);
			ToMau(40, 15, "2. Thêm tài khoản", 202);
			ToMau(40, 16, "3. Xóa tài khoản", 14);
			ToMau(40, 17, "4. Mở khóa tài khoản", 14);
			ToMau(40, 18, "5. Thoát", 14);
		}
		if (_iToaDo == 16) {
			ToMau(40, 14, "1. Xem danh sách tài khoản", 14);
			ToMau(40, 15, "2. Thêm tài khoản", 14);
			ToMau(40, 16, "3. Xóa tài khoản", 202);
			ToMau(40, 17, "4. Mở khóa tài khoản", 14);
			ToMau(40, 18, "5. Thoát", 14);
		}
		if (_iToaDo == 17) {
			ToMau(40, 14, "1. Xem danh sách tài khoản", 14);
			ToMau(40, 15, "2. Thêm tài khoản", 14);
			ToMau(40, 16, "3. Xóa tài khoản", 14);
			ToMau(40, 17, "4. Mở khóa tài khoản", 202);
			ToMau(40, 18, "5. Thoát", 14);
		}
		if (_iToaDo == 18) {
			ToMau(40, 14, "1. Xem danh sách tài khoản", 14);
			ToMau(40, 15, "2. Thêm tài khoản", 14);
			ToMau(40, 16, "3. Xóa tài khoản", 14);
			ToMau(40, 17, "4. Mở khóa tài khoản", 14);
			ToMau(40, 18, "5. Thoát", 202);
		}
	} while (_iChoose != 3);
	ClearSceen
		if (_iToaDo == 14) {
			ClearSceen
				adminShowUser(CALLLIST);
			char a = _getch();
			if (a != '+') { ClearSceen showAccessAdmin(CALLLIST); }
		}
		else if (_iToaDo == 15) {
			ClearSceen
				adminAddUser(CALLLIST);
		}
		else if (_iToaDo == 16) { ClearSceen adminDeleteUser(CALLLIST); }
		else if (_iToaDo == 17) { ClearSceen adminUnlockUser(CALLLIST); }
		else if (_iToaDo == 18) { showLoginAdmin(CALLLIST); }
}
void adminAddUser(LISTADMIN) {
	setKhung(CALLLIST);
	string sName;
	string sNumberAccount;
	string sType;
	cin.ignore();
	long long llWallet = 0;
	string sWallet = "";
	ToMau(31, 13, "* ** ** ** ** ** **THÊM TÀI KHOẢN* ** ** ** ** ** **", 4);
	ToMau(36, 14, "Họ và tên    : ", 10);
	ToMau(36, 15, "Số tài khoản : ", 10);
	ToMau(36, 16, "Số dư        : ", 10);
	ToMau(36, 17, "Loại tiền    : ", 10);
	ToMau(31, 19, "* ** ** ** ** ** **THÊM TÀI KHOẢN* ** ** ** ** ** **", 4);
	gotoxy(55, 14); getline(cin, sName);
	gotoxy(55, 15); cin >> sNumberAccount;
	gotoxy(55, 16);	cin >> sWallet;
	for (int i = 0; i < sWallet.size(); i++) {
		if (sWallet[i] < 48 || sWallet[i]>57) {
			llWallet = 50000;
		}
		else {
			llWallet = stol(sWallet);
		}
	}
	gotoxy(55, 17); cout<<"VND";
	cin.ignore();
	if (sName.length() == 0) sName = "TESTER";
	if (llWallet < 50000) llWallet = 50000;
	Card tmp(sNumberAccount,"123456");
	if (listCard.search11(tmp.getID())) {
		gotoxy(40, 20); cout << "Trùng với ID đã tồn tại!";
		Sleep(1000);
		ClearSceen
			showAccessAdmin(CALLLIST);
	}
	else if (sNumberAccount.length()!=8) {
		gotoxy(40, 20); cout << "STK bạn nhập chưa đủ 8 số!";
		Sleep(1000);
		ClearSceen
			showAccessAdmin(CALLLIST);
	}
	else {
		BlockUser tmp11(sNumberAccount, "Active");
		listBlockUser.addTail(tmp11);
		updateListBlock(CALLLIST);
		User tmp1(sNumberAccount, sName, llWallet, sType);
		listUser.addTail(tmp1);
		listCard.addTail(tmp);
		string noti = "[" + sNumberAccount + "]-[" + sName + "]" + "-[" + to_string(llWallet) + sType + "] được tạo bởi ADMIN vào lúc" + currentDateTime();
		History notii(noti,"Admin","NewUser");
		listLog.addTail(notii);
		countLogin z(sNumberAccount, 0);
		listLogin.addTail(z);
		updateHistory(CALLLIST);
		updateID(CALLLIST);
		updateCard(CALLLIST);
		updateListLogin(CALLLIST);
		ToMau(40, 20, "Bạn đã tạo thành công!", 10);
		Sleep(2000);
		ClearSceen;
		showAccessAdmin(CALLLIST);
		cin.ignore();
	}

}
void adminDeleteUser(LISTADMIN) {
	ToMau(31, 13, "* ** ** ** ** ** **XÓA TÀI KHOẢN* ** ** ** ** ** **", 14);
	ToMau(36, 14, "Số tài khoản cần xóa  : ", 10);
	ToMau(36, 15, "Lí do xóa tài khoản    : ", 10);
	ToMau(31, 19, "* ** ** ** ** ** **XÓA TÀI KHOẢN* ** ** ** ** ** **", 14);
	string _sAccountNumber;
	gotoxy(51, 14); cin >> _sAccountNumber;
	User tmp1(_sAccountNumber,"",0,"");
	Card tmp2(_sAccountNumber, "");
	BlockUser tmp3(_sAccountNumber, "");
	if (listCard.search5(tmp2)) {
		listUser.remove(tmp1);
		listCard.remove(tmp2);
		listBlockUser.remove(tmp3);
		updateCard(CALLLIST);
		updateID(CALLLIST);
		updateListBlock(CALLLIST);
		string _sReason, _sNoti;
		gotoxy(51, 15); cin.ignore(); getline(cin, _sReason);
		_sNoti = "Admin vừa xóa tài khoản " + _sAccountNumber + " với lí do: " + _sReason + " vào lúc" + currentDateTime();
		History noti1(_sNoti, "Admin", _sAccountNumber);
		listLog.addTail(noti1);
		updateHistory(CALLLIST);
		Sleep(2000);
		ToMau(32, 16, "Bạn đã xóa "+ _sAccountNumber +" thành công!", 10);
		Sleep(1000);
		ClearSceen
			showAccessAdmin(CALLLIST);
	}
	else {
		ToMau(32, 16, "Số tài khoản này không tồn tại trong database!", 4);
		Sleep(1000);
		ClearSceen
			showAccessAdmin(CALLLIST);
	}
	cin.ignore();
}
void adminUnlockUser(LISTADMIN){
	cin.ignore();
	ToMau(31, 13, "* ** ** ** ** ** **MỞ TÀI KHOẢN* ** ** ** ** ** **", 14);
	ToMau(36, 14, "STK cần mở  : ", 9);
	ToMau(36, 15, "Trạng thái  : ", 9);
	ToMau(31, 16, "* ** ** ** ** ** **MỞ TÀI KHOẢN* ** ** ** ** ** **", 14);
	string _sAccountNumber;
	gotoxy(51, 14); cin >> _sAccountNumber;
	BlockUser ttmp(_sAccountNumber, "");
	if (listBlockUser.search(ttmp)) {
		BlockUser tmp = listBlockUser.search4(ttmp);
		if (tmp.getStatus() == "Active") {
			ToMau(51, 15, "Active", 10);
			Sleep(1000);
			ClearSceen
				showAccessAdmin(CALLLIST);
		}
		else {
			ToMau(51, 15, "Block", 4);
			Sleep(1000);
			ToMau(36, 15, "Mở khóa thành công!", 2);
			BlockUser tmp1(_sAccountNumber, "Active");
			listBlockUser.changeValue1(tmp1);
			updateListBlock(CALLLIST);
			Sleep(2000);
			ClearSceen
				showAccessAdmin(CALLLIST);
		}
	}
	else {
		ToMau(36, 15, "Số tài khoản bạn nhập không tồn tại!", 15);
		Sleep(2000);
		ClearSceen
			showAccessAdmin(CALLLIST);
	}
}
void adminShowUser(LISTADMIN) {
	ClearSceen
	int iNumberLines = 4;
	int iColorTitle = 11;
	int iQuantity = listUser.getSize();
	int sColorInformations = 15;
	ToMau(1, 1, "╔══════════════════════════╦══════════════════════════╦══════════════════════════╦═══════════════════════╗", 9);
	ToMau(1, 2, "║                          ║                          ║                          ║                       ║",9);
	ToMau(9, 2, "SỐ TÀI KHOẢN", iColorTitle);
	ToMau(38, 2, "HỌ VÀ TÊN", iColorTitle);
	ToMau(66, 2, "SỐ DƯ", iColorTitle);
	ToMau(92, 2, "MÃ PIN", iColorTitle);
	ToMau(1, 3, "╠══════════════════════════╬══════════════════════════╬══════════════════════════╬═══════════════════════╣", 9);
	for (int i = 0; i < iQuantity; i++) {
		User tmp;
		tmp = listUser[i];
		Card tmp1 = listCard[i];
		ToMau(8, iNumberLines,tmp.getID(), sColorInformations);
		ToMau(33, iNumberLines,tmp.getName(), sColorInformations);
		ToMau(62, iNumberLines,to_string(tmp.getWallet())+ " "+tmp.getType(), sColorInformations);
		ToMau(92, iNumberLines,tmp1.getPIN(), sColorInformations);
		ToMau(1, iNumberLines, "║", 9);
		ToMau(28, iNumberLines, "║", 9);
		ToMau(55, iNumberLines, "║", 9);
		ToMau(82, iNumberLines, "║", 9);
		ToMau(106, iNumberLines, "║", 9);
		if(i<iQuantity-1) ToMau(1, iNumberLines +=1, "╠══════════════════════════╬══════════════════════════╬══════════════════════════╬═══════════════════════╣", 9);
		iNumberLines++;
	}
	ToMau(1, iNumberLines, "╚══════════════════════════╩══════════════════════════╩══════════════════════════╩═══════════════════════╝", 9);
	char _cA = _getch();
	if (_cA != '+') { ClearSceen showAccessAdmin(CALLLIST); }
}
void showLoginUser(LISTADMIN) {
	setKhung(CALLLIST);
	bool _bA = false;
	while (!_bA) {
		string sUser = "";
		string sPass = "";
		YELLOW
			gotoxy(42, 15); cout << "* ** ** ** ** ** ** *";
		gotoxy(42, 16); cout << "*  "; BLUE cout << " ĐĂNG NHẬP USER"; YELLOW cout << "  *" << endl;
		gotoxy(42, 17);  cout << "* ** ** ** ** ** ** *";
		gotoxy(42, 18); BLUE cout << "ID :";
		gotoxy(42, 19); BLUE cout << "PIN:";
		gotoxy(52, 18); WHITE cin >> sUser;
		gotoxy(52, 19); WHITE inputPass(sPass);
		gotoxy(41, 20);
		if (checkLoginUser(sUser, sPass, CALLLIST)) {
			MAUXANH cout << "Bạn đã đăng nhập thành công"; _bA = true;
			Sleep(200);
			ClearSceen
			setKhung(CALLLIST);
			string sUserNow = sUser;
			showAccessUser(CALLLIST, sUserNow);
		}
		else {
			BlockUser z(sUser, "");
			if (listBlockUser.search5(z)) {
				BlockUser zz = listBlockUser.search4(z);
				if (zz.getStatus() == "Block") {
					RED
						cout << "Tài khoản này đã bị Block";
					Sleep(1500);
					ClearSceen
						setKhung(CALLLIST);
				}
				else {
					countLogin t(sUser, 0);
					countLogin tmp = listLogin.search4(t);
					tmp = listLogin.loginFailUp(tmp);
					if (tmp.getD() == 5) {
						BlockUser tmp1(sUser, "Block");
						listBlockUser.changeValue1(tmp1);
						updateListBlock(CALLLIST);
					}
					RED
						cout << "Bạn đã nhập sai, vui lòng thử lại";
					Sleep(1500);
					ClearSceen
						setKhung(CALLLIST);
				}
			}
			else {
				RED
					cout << "Bạn đã nhập sai, vui lòng thử lại";
				Sleep(1000);
				ClearSceen
					setKhung(CALLLIST);
			}
		}
	}
}
void showAccessUser(LISTADMIN,string sUserNow) {
	setKhung(CALLLIST);
	ToMau(32, 13, "* * * * * * * * * *MENU* * * * * * * * * *", 14);
	ToMau(40, 14, "1. Xem thông tin tài khoản", 202);
	ToMau(40, 15, "2. Rút tiền", 14);
	ToMau(40, 16, "3. Chuyển tiền", 14);
	ToMau(40, 17, "4. Xem nội dung giao dịch", 14);
	ToMau(40, 18, "5. Đổi mã pin", 14);
	ToMau(40, 19, "6. Thoát", 14);
	ToMau(30, 20, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	int iChoose = 0;
	int iToaDo = 14;
	do {
		char a = _getch();
		if (a == 80) iChoose = 1;
		else if (a == 72) iChoose = 2;
		else if (a == 13) iChoose = 3;
		else iChoose = 0;
		if (iChoose == 1 && iToaDo < 20) iToaDo++;
		else if (iChoose == 2 && iToaDo > 13) iToaDo--;
		if (iToaDo == 14){
			ToMau(40, 14, "1. Xem thông tin tài khoản", 202);
			ToMau(40, 15, "2. Rút tiền", 14);
			ToMau(40, 16, "3. Chuyển tiền", 14);
			ToMau(40, 17, "4. Xem nội dung giao dịch", 14);
			ToMau(40, 18, "5. Đổi mã pin", 14);
			ToMau(40, 19, "6. Thoát", 14);
		}
		if (iToaDo == 15){
			ToMau(40, 14, "1. Xem thông tin tài khoản", 14);
			ToMau(40, 15, "2. Rút tiền", 202);
			ToMau(40, 16, "3. Chuyển tiền", 14);
			ToMau(40, 17, "4. Xem nội dung giao dịch", 14);
			ToMau(40, 18, "5. Đổi mã pin", 14);
			ToMau(40, 19, "6. Thoát", 14);
		}
		if (iToaDo == 16){
			ToMau(40, 14, "1. Xem thông tin tài khoản", 14);
			ToMau(40, 15, "2. Rút tiền", 14);
			ToMau(40, 16, "3. Chuyển tiền", 202);
			ToMau(40, 17, "4. Xem nội dung giao dịch", 14);
			ToMau(40, 18, "5. Đổi mã pin", 14);
			ToMau(40, 19, "6. Thoát", 14);
		}
		if (iToaDo == 17){
			ToMau(40, 14, "1. Xem thông tin tài khoản", 14);
			ToMau(40, 15, "2. Rút tiền", 14);
			ToMau(40, 16, "3. Chuyển tiền", 14);
			ToMau(40, 17, "4. Xem nội dung giao dịch", 202);
			ToMau(40, 18, "5. Đổi mã pin", 14);
			ToMau(40, 19, "6. Thoát", 14);
		}
		if (iToaDo == 18){
			ToMau(40, 14, "1. Xem thông tin tài khoản", 14);
			ToMau(40, 15, "2. Rút tiền", 14);
			ToMau(40, 16, "3. Chuyển tiền", 14);
			ToMau(40, 17, "4. Xem nội dung giao dịch", 14);
			ToMau(40, 18, "5. Đổi mã pin", 202);
			ToMau(40, 19, "6. Thoát", 14);
		}
		if (iToaDo == 19){
			ToMau(40, 14, "1. Xem thông tin tài khoản", 14);
			ToMau(40, 15, "2. Rút tiền", 14);
			ToMau(40, 16, "3. Chuyển tiền", 14);
			ToMau(40, 17, "4. Xem nội dung giao dịch", 14);
			ToMau(40, 18, "5. Đổi mã pin", 14);
			ToMau(40, 19, "6. Thoát", 202);
		}
	} while (iChoose != 3);
	ClearSceen
		if (iToaDo == 14) userXemSoDu(CALLLIST, sUserNow);
		else if (iToaDo == 15) userRutTien(CALLLIST, sUserNow);
		else if (iToaDo == 16) userChuyenTien(CALLLIST, sUserNow);
		else if (iToaDo == 17) userNoiDungGD(CALLLIST, sUserNow);
		else if (iToaDo == 18) userChangePin(CALLLIST, sUserNow);
	else if (iToaDo == 19) showLoginUser(CALLLIST);
}
void userXemSoDu(LISTADMIN,string sUserNow) {
	setKhung(CALLLIST);
	string sAccountNumber, sName, sWallet, sType;
	User ttmp(sUserNow,"",0,"");
	User tmp = listUser.search2(ttmp);
	ToMau(32, 13, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	ToMau(38, 14, "1.Số tài khoản: ", 14);
	ToMau(38, 15, "2.Họ và tên   : ", 14);
	ToMau(38, 16, "3.Số dư       : ", 14);
	ToMau(38, 17, "4.Đơn vị tiền : ", 14);
	ToMau(38, 18, "5.Trạng thái  : ", 14);
	ToMau(30, 19, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	Sleep(200); gotoxy(54, 14); BLUE cout << tmp.getID();
	Sleep(200); gotoxy(54, 15); WHITE cout<< tmp.getName();
	Sleep(200); gotoxy(54, 16); WHITE cout<< tmp.getWallet();
	Sleep(200); gotoxy(54, 17); RED cout<<tmp.getType();
	Sleep(200); gotoxy(54, 18); GREEN cout << "Online";
	char _cA = _getch();
	if (_cA != '+') {
		ClearSceen
			setKhung(CALLLIST);
		showAccessUser(CALLLIST, sUserNow);
	}
}
void userRutTien(LISTADMIN, string sUserNow) {
	setKhung(CALLLIST);
	string sAccountNumber, sName, sWallet, sType;
	User ttmp(sUserNow, "", 0, "");
	User tmp = listUser.search2(ttmp);
	ToMau(32, 13, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	ToMau(34, 14, "[50000] ", 32);
	ToMau(34, 16, "[100000]", 91);
	ToMau(34, 18, "[200000]", 91);
	ToMau(65, 14, "[400000]", 91);
	ToMau(65, 16, "[500000]", 91);
	ToMau(64, 18, " SỐ KHÁC ", 91);
	ToMau(50, 16, "THOÁT", 91);
	ToMau(30, 19, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	int iChoose = 0;
	int iToaDo = 14;
	do {
		char _cA = _getch();
		if (_cA == 80) iChoose = 1;
		else if (_cA == 72) iChoose = 2;
		else if (_cA == 13) iChoose = 3;
		else iChoose = 0;
		if (iChoose == 1 && iToaDo < 21) iToaDo++;
		else if (iChoose == 2 && iToaDo > 13) iToaDo--;
		if (iToaDo == 14) {
			ToMau(34, 14, "[50000] ", 32);
			ToMau(34, 16, "[100000]", 91);
			ToMau(34, 18, "[200000]", 91);
			ToMau(65, 14, "[400000]", 91);
			ToMau(65, 16, "[500000]", 91);
			ToMau(64, 18, " SỐ KHÁC ", 91);
			ToMau(50, 16, "THOÁT", 91);
		}
		if (iToaDo == 15) {
			ToMau(34, 14, "[50000] ", 91);
			ToMau(34, 16, "[100000]", 32);
			ToMau(34, 18, "[200000]", 91);
			ToMau(65, 14, "[400000]", 91);
			ToMau(65, 16, "[500000]", 91);
			ToMau(64, 18, " SỐ KHÁC ", 91);
			ToMau(50, 16, "THOÁT", 91);
		}
		if (iToaDo == 16) {
			ToMau(34, 14, "[50000] ", 91);
			ToMau(34, 16, "[100000]", 91);
			ToMau(34, 18, "[200000]", 32);
			ToMau(65, 14, "[400000]", 91);
			ToMau(65, 16, "[500000]", 91);
			ToMau(64, 18, " SỐ KHÁC ", 91);
			ToMau(50, 16, "THOÁT", 91);
		}
		if (iToaDo == 17) {
			ToMau(34, 14, "[50000] ", 91);
			ToMau(34, 16, "[100000]", 91);
			ToMau(34, 18, "[200000]", 91);
			ToMau(65, 14, "[400000]", 32);
			ToMau(65, 16, "[500000]", 91);
			ToMau(64, 18, " SỐ KHÁC ", 91);
			ToMau(50, 16, "THOÁT", 91);
		}
		if (iToaDo == 18) {
			ToMau(34, 14, "[50000] ", 91);
			ToMau(34, 16, "[100000]", 91);
			ToMau(34, 18, "[200000]", 91);
			ToMau(65, 14, "[400000]", 91);
			ToMau(65, 16, "[500000]", 32);
			ToMau(64, 18, " SỐ KHÁC ", 91);
			ToMau(50, 16, "THOÁT", 91);
		}
		if (iToaDo == 19) {
			ToMau(34, 14, "[50000] ", 91);
			ToMau(34, 16, "[100000]", 91);
			ToMau(34, 18, "[200000]", 91);
			ToMau(65, 14, "[400000]", 91);
			ToMau(65, 16, "[500000]", 91);
			ToMau(64, 18, " SỐ KHÁC ", 32);
			ToMau(50, 16, "THOÁT", 91);
		}
		if (iToaDo == 20) {
			ToMau(34, 14, "[50000] ", 91);
			ToMau(34, 16, "[100000]", 91);
			ToMau(34, 18, "[200000]", 91);
			ToMau(65, 14, "[400000]", 91);
			ToMau(65, 16, "[500000]", 91);
			ToMau(64, 18, " SỐ KHÁC ", 91);
			ToMau(50, 16, "THOÁT", 32);
		}
	} while (iChoose != 3);
	if (iToaDo == 14)checkRutTien(CALLLIST, 50000, tmp);
	else if (iToaDo == 15)  checkRutTien(CALLLIST, 100000, tmp);
	else if (iToaDo == 16) checkRutTien(CALLLIST, 200000, tmp);
	else if (iToaDo == 17) checkRutTien(CALLLIST, 400000, tmp);
	else if (iToaDo == 18) checkRutTien(CALLLIST, 500000, tmp);
	else if (iToaDo == 20) { ClearSceen showAccessUser(CALLLIST, sUserNow); }
	else if (iToaDo == 19) {
		gotoxy(73, 18); int iwall=0; cin >> iwall;
		checkRutTien(CALLLIST, iwall, tmp);
	}
}
void userChuyenTien(LISTADMIN, string sUserNow) {
	User tmp1(sUserNow, "", 0, "");
	User tmp11 = listUser.search2(tmp1);
	string sUserReceive = "";
	long long llNumberMoneyTranferred;
	setKhung(CALLLIST);
	ToMau(32, 13, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	ToMau(34, 14, "STK người nhận:", 3);
	ToMau(34, 15, "Số dư hiện tại:", 5);
	gotoxy(50, 15);  cout << tmp11.getWallet() <<" "<< tmp11.getType();
	ToMau(34, 16, "Người nhận:", 6);
	ToMau(34, 17, "Số tiền:", 2);
	ToMau(30, 19, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	gotoxy(50, 14); cin >> sUserReceive;
	User tmp2(sUserReceive, "", 0, "");
	if (listUser.search1(tmp2) && sUserNow!=sUserReceive) {
		User tmp22 = listUser.search2(tmp2);
		gotoxy(50, 16); cout << tmp22.getName();
		gotoxy(50, 17); cin >> llNumberMoneyTranferred;
		if (llNumberMoneyTranferred >= 50000 && llNumberMoneyTranferred <= tmp11.getWallet() - 50000 && llNumberMoneyTranferred % 50000 == 0) {
			string sNoti = tmp11.getName() + " vừa chuyển " + to_string(llNumberMoneyTranferred) + " đến "+ tmp22.getName() + " vào lúc" + currentDateTime();
			History noti1(sNoti, tmp11.getID(), tmp22.getID());
			listLog.addTail(noti1);
			tmp11.Except_Money(llNumberMoneyTranferred);
			tmp22.Plus_Money(llNumberMoneyTranferred);
			updateHistory(CALLLIST);
			listUser.changeValue(tmp11);
			listUser.changeValue(tmp22);
			updateID(CALLLIST);
			Sleep(1000);
			ToMau(34, 18, "Bạn đã chuyển thành công!", 4);
			Sleep(2000);
			ClearSceen
				setKhung(CALLLIST);
			showAccessUser(CALLLIST, tmp11.getID());
		}
		else {
			ToMau(34, 18, "Vui lòng nhập lại! Tiền bạn chưa đủ hoặc không phải bội 50000", 4);
			Sleep(2000);
			ClearSceen
				showAccessUser(CALLLIST, sUserNow);
		}
	}
	else {
		ToMau(34, 18, "Sai định dạng hoặc sai số tài khoản!", 4);
		Sleep(2000);
		ClearSceen
			showAccessUser(CALLLIST, sUserNow);

	}
}
void userNoiDungGD(LISTADMIN, string sUserNow) {
	resizeConsole(1027, 600);
	History noti1("", sUserNow, sUserNow);
	LinkedList<History> tmp;
	listLog.search3(noti1, tmp);
	int iNumberLines = 4;
	int iColorTitle = 11;
	int iQuantity = tmp.getSize();
	int iColorInformations = 15;
	ToMau(1, 1, "╔════════════════╦════════════════╦══════════════════════════════════════════════════════════════════════════════════════════════════════╗", 9);
	ToMau(1, 2, "║                ║                ║                                                                                                      ║", 9);
	ToMau(8, 2, "FROM", iColorTitle);
	ToMau(26, 2, "TO", iColorTitle);
	ToMau(85, 2, "NỘI DUNG", iColorTitle);
	ToMau(1, 3, "╠════════════════╬════════════════╬══════════════════════════════════════════════════════════════════════════════════════════════════════╣", 9);
	for (int i = 0; i < iQuantity; i++) {

		ToMau(3, iNumberLines, tmp[i].getSend(), iColorInformations);
		if (tmp[i].getReceive() == "0") {
			ToMau(20, iNumberLines, tmp[i].getSend(), iColorInformations);
		}
		else ToMau(20, iNumberLines, tmp[i].getReceive(), iColorInformations);
		ToMau(37, iNumberLines, tmp[i].getNoti(), iColorInformations);
		ToMau(1, iNumberLines, "║", 9);
		ToMau(18, iNumberLines, "║", 9);
		ToMau(35, iNumberLines, "║", 9);
		ToMau(138, iNumberLines, "║", 9);
		if (i < iQuantity - 1) ToMau(1, iNumberLines += 1, "╠════════════════╬════════════════╬══════════════════════════════════════════════════════════════════════════════════════════════════════╣", 9);
		iNumberLines++;
	}
	ToMau(1, iNumberLines, "╚════════════════╩════════════════╩══════════════════════════════════════════════════════════════════════════════════════════════════════╝", 9);
	char _cA = _getch();
	if (_cA != '+') {
		resizeConsole(800, 600);
		ClearSceen
			setKhung(CALLLIST);
		showAccessUser(CALLLIST, sUserNow);
	}
}
void userChangePin(LISTADMIN, string sUserNow) {
	Card a(sUserNow, "");
	a=listCard.search4(a);
	setKhung(CALLLIST);
	string sPinNow = a.getPIN();
	Card ttmp(sUserNow, a.getPIN());
	Card tmp = listCard.search2(ttmp);
	string sPinInput;
	string sNewPin, sNewPin1;
	ToMau(32, 13, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	ToMau(34, 14, "Mã pin hiên tại    :", 3);
	ToMau(30, 19, "	* * * * * * * * * * * * * * * * * * * * *", 14);
	gotoxy(55, 14);  cin >> sPinInput;
	if (sPinInput == sPinNow) {
		ToMau(34, 15, "Mã pin mới:", 5);
		gotoxy(55, 15); cin >> sNewPin;
		if (sNewPin.size() != 6) {
			ToMau(40, 20, "Mã pin mới có 6 ký tự!", 4);
			Sleep(1000);
			ClearSceen
				showAccessUser(CALLLIST, sUserNow);
		}
		ToMau(34, 16, "Nhập lại mã pin mới:", 6);
		gotoxy(55, 16); cin >> sNewPin1;
		if (sNewPin != sNewPin1) {
			ToMau(40, 20, "2 mã pin bạn nhập vào khác nhau!", 4);
			Sleep(1000);
			ClearSceen
			showAccessUser(CALLLIST, sUserNow);
		}
		else {
			ToMau(40, 20, "Bạn đã đổi mã pin thành công!", 4);
			tmp.Change_PIN(sNewPin);
			listCard.changeValue1(tmp);
			updateCard(CALLLIST);
			Sleep(2000);
			ClearSceen
			showAccessUser(CALLLIST, sUserNow);
		}
	}
	else {
		ToMau(40, 20, "Mã pin hiện tại bạn nhập sai!", 4);
		Sleep(1000);
		ClearSceen
		showAccessUser(CALLLIST, sUserNow);
	}
}


void setKhung(LISTADMIN) {
	int iSampleFrame = 14;
	ToMau(1, 1, "╔════════════════════════════════════════════════════════════════════════════════════════════════════════╗", iSampleFrame);
	int _iX = 2;
	for (int i = 0; i < 34; i++) {
		ToMau(1, _iX, "║", iSampleFrame);
		ToMau(106, _iX, "║", iSampleFrame);
		_iX++;
	}
	ToMau(1, 35, "╚════════════════════════════════════════════════════════════════════════════════════════════════════════╝", iSampleFrame);
	gotoxy(1, 1);
}
bool checkLoginAdmin(string user, string Pass, LinkedList<Admin> listAdmin) {
	Admin z(user, Pass);
	return (listAdmin.checkAdmin(z));
}
bool checkLoginUser(string user, string Pass, LISTADMIN) {
	Card z(user, Pass);
	return (listCard.checkUser(z));
}
void checkRutTien(LISTADMIN,long long wallet, User tmp) {
	long long soDu = tmp.getWallet();
	if (wallet >= 50 && wallet <= soDu - 50000 && wallet % 50000 == 0) {
		gotoxy(40, 20); cout << "Vui lòng đợi một lát...";
		tmp.Except_Money(wallet);
		string sNoti = tmp.getName() + " vừa rút "+ to_string(wallet)+" vào lúc" + currentDateTime();
		History noti1(sNoti,tmp.getID(), "0");
		listLog.addTail(noti1);
		updateHistory(CALLLIST);
		listUser.changeValue(tmp);
		updateID(CALLLIST);
		Sleep(1000);
		ToMau(38, 21, "BẠN ĐÃ RÚT TIỀN THÀNH CÔNG " + to_string(wallet), 4);
		Sleep(2000);
		ClearSceen
			setKhung(CALLLIST);
		showAccessUser(CALLLIST, tmp.getID());
	}
	else {
		gotoxy(20, 20); cout << "Vui lòng nhập lại! Tiền bạn chưa đủ hoặc không phải bội 50000";
		Sleep(3000);
		ClearSceen
			setKhung(CALLLIST);
		showAccessUser(CALLLIST, tmp.getID());
	}
}
void inputPass(string& pw) {
	char cPass[32];
	int i = 0;
	char _cA;
	for (i = 0;;) {
		_cA = _getch();
		if ((_cA >= 'a' && _cA <= 'z') || (_cA >= 'A' && _cA <= 'Z') || (_cA >= '0' && _cA <= '9')) {
			cPass[i] = _cA;
			++i;
			cout << "*";
		}
		if (_cA == '\b' && i >= 1) {
			cout << "\b \b";
			--i;
		}
		if (_cA == '\r') {
			cPass[i] = '\0';
			break;
		}
	}
	for (int z = 0; z < i; z++) {
		pw.push_back(cPass[z]);
	}
}

void showMain(LISTADMIN) {
	setKhung(CALLLIST);
	int iLeft = 38;
	ToMau(iLeft - 17, 15, " ██╗       ██╗███████╗██╗      █████╗  █████╗ ███╗   ███╗███████╗", 15);
	ToMau(iLeft - 17, 16, " ██║  ██╗  ██║██╔════╝██║     ██╔══██╗██╔══██╗████╗ ████║██╔════╝", 15);
	ToMau(iLeft - 17, 17, " ╚██╗████╗██╔╝█████╗  ██║     ██║  ╚═╝██║  ██║██╔████╔██║█████╗  ", 15);
	ToMau(iLeft - 17, 18, "  ████╔═████║ ██╔══╝  ██║     ██║  ██╗██║  ██║██║╚██╔╝██║██╔══╝  ", 15);
	ToMau(iLeft - 17, 19, "  ╚██╔╝ ╚██╔╝ ███████╗███████╗╚█████╔╝╚█████╔╝██║ ╚═╝ ██║███████╗", 15);
	ToMau(iLeft - 17, 20, "   ╚═╝   ╚═╝  ╚══════╝╚══════╝ ╚════╝  ╚════╝ ╚═╝     ╚═╝╚══════╝", 15);
	Sleep(600);
	ToMau(iLeft - 17, 15, "                                                                 ", 0);
	ToMau(iLeft - 17, 16, "                                                                 ", 0);
	ToMau(iLeft - 17, 17, "                                                                 ", 0);
	ToMau(iLeft - 17, 18, "                                                                 ", 0);
	ToMau(iLeft - 17, 19, "                                                                 ", 0);
	ToMau(iLeft - 17, 20, "                                                                 ", 0);
	ToMau(iLeft + 8, 15, "████████╗ █████╗ ", 12);
	ToMau(iLeft + 8, 16, "╚══██╔══╝██╔══██╗", 12);
	ToMau(iLeft + 8, 17, "   ██║   ██║  ██║", 12);
	ToMau(iLeft + 8, 18, "   ██║   ██║  ██║", 12);
	ToMau(iLeft + 8, 19, "   ██║   ╚█████╔╝", 12);
	ToMau(iLeft + 8, 20, "   ╚═╝    ╚════╝ ", 12);
	Sleep(600);
	ToMau(iLeft - 17, 15, "                                                                 ", 0);
	ToMau(iLeft - 17, 16, "                                                                 ", 0);
	ToMau(iLeft - 17, 17, "                                                                 ", 0);
	ToMau(iLeft - 17, 18, "                                                                 ", 0);
	ToMau(iLeft - 17, 19, "                                                                 ", 0);
	ToMau(iLeft - 17, 20, "                                                                 ", 0);
	ToMau(iLeft, 13, "█░█ █▄░█", 15);
	ToMau(iLeft, 14, "▀▄▀ █░▀█", 15);
	ToMau(iLeft, 15, "██████╗  █████╗ ███╗  ██╗██╗  ██╗", 11);
	ToMau(iLeft, 16, "██╔══██╗██╔══██╗████╗ ██║██║ ██╔╝", 11);
	ToMau(iLeft, 17, "██████╦╝███████║██╔██╗██║█████═╝ ", 11);
	ToMau(iLeft, 18, "██╔══██╗██╔══██║██║╚████║██╔═██╗ ", 11);
	ToMau(iLeft, 19, "██████╦╝██║  ██║██║ ╚███║██║ ╚██╗", 11);
	ToMau(iLeft, 20, "╚═════╝ ╚═╝  ╚═╝╚═╝  ╚══╝╚═╝  ╚═╝", 9);
	Sleep(200);
	ToMau(65, 33, "Press A to open the Admin login", 15);
	ToMau(65, 34, "Press U to open the User login", 15);
	char _cA = _getch();
	if (_cA == 'A') { ClearSceen showLoginAdmin(CALLLIST);}
	if (_cA == 'U') { ClearSceen showLoginUser(CALLLIST);}
}
