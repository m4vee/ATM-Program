#pragma once
#include <wx/wx.h>
#include <iostream>
#include <random>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <string>
#define MAX 5
using namespace std;

struct user {
	int acc_number;
	int MARKER;
	string acc_name[MAX];
	int acc_num[MAX];
	string pin[MAX];
	string bday[MAX];
	string contact[MAX];
	int acc_bal[MAX];
	user() : MARKER(-1) {}
};

class atmfunctions
{
public:
	user U;
	void reg_acc(wxString nme, wxString bday_m, wxString bday_d, wxString bday_y, wxString cntact, wxString pinreg);
	void withdraw(int x, wxString amnt);
	void deposit(int x, wxString amnt);
	void fund_trans(int x, wxString accn, wxString amnt);
	void change_pin(int x, wxString pin_crrnt, wxString pin_new, wxString pin_cnfrm);
	void retrieve_acc();
	void add_acc();
	int search_accNum(int x);
	int search_accPin(string x);
	void save_Allacc();
	void save_card(int x);
	bool scan_card();
	char check_flash_drive();
	string encrypt(string x);
	string decrypt(string x);
};

