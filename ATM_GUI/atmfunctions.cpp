#include "atmfunctions.h"
#include <wx/wx.h>

void atmfunctions::reg_acc(wxString nme, wxString bday_m, wxString bday_d, wxString bday_y, wxString cntact, wxString pinreg) {
	int acc_n;
	string name = nme.ToStdString();
	string m_bday = bday_m.ToStdString();
	string d_bday = bday_d.ToStdString();
	string y_bday = bday_y.ToStdString();
	string contact_ = cntact.ToStdString();
	string pin_ = pinreg.ToStdString();
	string b_day;
	b_day += m_bday;
	b_day += d_bday;
	b_day += ',';
	b_day += y_bday;


	U.MARKER++;

	U.acc_name[U.MARKER] = name;
	U.bday[U.MARKER] = b_day;
	U.contact[U.MARKER] = contact_;
	U.pin[U.MARKER] = pin_;

	do {
		random_device rd;
		mt19937 gen(rd());

		uniform_int_distribution<> distr(10000, 99999);
		acc_n = distr(gen);
	} while (search_accNum(acc_n) > -1);

	U.acc_num[U.MARKER] = acc_n;

	U.acc_bal[U.MARKER] = 0;

	wxMessageBox(wxString::Format("ACOUNT DETAILS\nNAME: %s\nBIRTHDAY: %s\nCONTACT: %s\nACCOUNT NUMBER: %d\nPIN: %s", U.acc_name[U.MARKER], U.bday[U.MARKER], U.contact[U.MARKER], U.acc_num[U.MARKER], U.pin[U.MARKER]));

	add_acc();
	save_card(U.MARKER);
}

int atmfunctions::search_accNum(int x) {
	for (int i = 0; i <= U.MARKER; i++) {
		if (x == U.acc_num[i]) {
			return i;
		}
	}
	return -1;
}

int atmfunctions::search_accPin(string x) {
	for (int i = 0; i <= U.MARKER; i++) {
		if (x == U.pin[i]) {
			return i;
		}
	}
	return -1;
}

void atmfunctions::deposit(int x, wxString amnt) {
	long deposit_amount;
	string pin;
	char ch;
	
	if (amnt.ToLong(&deposit_amount)) {
		if (deposit_amount < 5000) {
			wxMessageBox("INVALID! THE MINIMUM DEPOSIT IS 5000");
			return;
		}
		else if (deposit_amount % 100 != 0) {
			wxMessageBox("INVALID DEPOSIT AMOUNT");
			return;
		}
		else {
			int value = static_cast<int>(deposit_amount);
			U.acc_bal[x] += value;
			wxMessageBox(wxString::Format("DEPOSIT SUCCESSFUL!\nNEW BALANCE: %d", U.acc_bal[x]));
		}
	}
}

void atmfunctions::withdraw(int x, wxString amnt) {
	long withdraw_amount;
	
	
	if(amnt.ToLong(&withdraw_amount))
	if (withdraw_amount % 100 == 0) {
		if (withdraw_amount <= U.acc_bal[x]) {
			U.acc_bal[x] -= withdraw_amount;
			wxMessageBox(wxString::Format("WITHDRAWAL SUCCESSFUL!\nNEW BALANCE: %d", U.acc_bal[x]));
		}
		else {
			wxMessageBox("INSUFFICIENT BALLANCE");
		}
	}
	else {
		wxMessageBox("INVALID AMOUNT! IT MUST BE EXACT");
	}
}

void atmfunctions::fund_trans(int x, wxString accn, wxString amnt) {
	long recipient_acc_num, fund_transfer_amount;

	if (!accn.ToLong(&recipient_acc_num) || !amnt.ToLong(&fund_transfer_amount)) {
		wxMessageBox("Invalid input! Please enter valid numbers");
		return;
	}
	
	int recipient_index = search_accNum(recipient_acc_num);
	if (recipient_index == -1) {
		wxMessageBox("RECIPIENT ACCOUNT NOT FOUND");
		return;
	}

	if (fund_transfer_amount % 100 != 0) {
		wxMessageBox("INVALID AMOUNT. IT MUST BE DIVISIBLE BY 100");
		return;
	}

	if (U.acc_bal[x] < fund_transfer_amount) {
		wxMessageBox("INSUFFICIENT BALANCE");
		return;
	}

	U.acc_bal[x] -= fund_transfer_amount; 
	U.acc_bal[recipient_index] += fund_transfer_amount; 
	wxMessageBox(wxString::Format("FUND TRANSFER SUCCESSFUL!\n%ld SENT TO %s\nNEW BALANCE: %d", fund_transfer_amount, U.acc_name[recipient_index],U.acc_bal[x]));
}

void atmfunctions::change_pin(int x, wxString pin_crrnt, wxString pin_new, wxString pin_cnfrm) {
	string current_pin = pin_crrnt.ToStdString();
	string new_pin = pin_new.ToStdString();
	string confirm_newPIN = pin_cnfrm.ToStdString();
	
		if (search_accPin(current_pin)==-1) {
			wxMessageBox("INVALID PIN");
			return;
		}
		if (new_pin != confirm_newPIN) {
			wxMessageBox("PINS DO NOT MATCH");
			return;
		}
		else {
			U.pin[x] = new_pin;
			wxMessageBox("PIN CHANGED SUCCESSFULLY");
			save_Allacc();
		}
}

char atmfunctions::check_flash_drive() {
	DWORD drive = GetLogicalDrives();

	for (int i = 3; i <= 6; i++) {
		if (drive & (1 << i)) {
			char driveLetter = 'D' + (i - 3);
			return driveLetter;
		}
	}
	return false;
}

bool atmfunctions::scan_card() {
	string acc_n, p, bd, cont;
	int acc_nm, acc_b;
	string FILE;

	char drive = check_flash_drive();
	switch (drive) {
	case 'D': FILE = "D:\\accounts.txt"; break;
	case 'E': FILE = "E:\\accounts.txt"; break;
	case 'F': FILE = "F:\\accounts.txt"; break;
	case 'G': FILE = "G:\\accounts.txt"; break;
	default:
		return false;
	}

	ifstream outFile(FILE);
	if (!outFile) {
		return false;
	}

	if (!(outFile >> acc_n >> acc_nm >> p >> bd >> cont >> acc_b)) {
		return false;
	}

	int i = search_accNum(acc_nm);
	if (i < 0 || i >= MAX) {
		wxMessageBox("Account number not found.");
		return false;
	}

	string d_pin = decrypt(p);
	U.acc_name[i] = acc_n;
	U.acc_number = U.acc_num[i] = acc_nm;
	U.pin[i] = d_pin;
	U.bday[i] = bd;
	U.contact[i] = cont;

	outFile.close();

	ofstream outFILE(FILE);
	if (!outFILE) {
		return false;
	}

	string e_pin = encrypt(U.pin[i]);
	outFILE << U.acc_name[i] << ' ' << U.acc_num[i] << ' ' << e_pin << ' ' << U.bday[i] << ' ' << U.contact[i] << ' ' << U.acc_bal[i] << endl;

	return true;
}





void atmfunctions::save_card(int x) {
	string FILE;

	switch (check_flash_drive()) {
	case 'D':
		FILE = "D:\\accounts.txt";
		break;
	case 'E':
		FILE = "E:\\accounts.txt";
		break;
	case 'F':
		FILE = "F:\\accounts.txt";
		break;
	case 'G':
		FILE = "G:\\accounts.txt";
		break;
	}
	ofstream outFile(FILE);

	if (!outFile) {
		cout << "Error Opening File" << endl;
		return;
	}
	string e_pin = encrypt(U.pin[U.MARKER]);

	outFile << U.acc_name[x] << ' ' << U.acc_num[x] << ' ' << e_pin << ' ' << U.bday[x] << ' ' << U.contact[x] << ' ' << U.acc_bal[x] << endl;
	outFile.close();
}

void atmfunctions::save_Allacc() {
	ofstream FILE("accounts.txt");

	if (!FILE) {
		return;
	}
	string e_pin;
	for (int i = 0; i <= U.MARKER; i++) {
		e_pin = encrypt(U.pin[i]);
		FILE << U.acc_name[i] << ' ' << U.acc_num[i] << ' ' << e_pin << ' ' << U.bday[i] << ' ' << U.contact[i] << ' ' << U.acc_bal[i] << endl;
	}

	FILE.close();
}

void atmfunctions::add_acc() {
	ofstream FILE("accounts.txt", ios::app);

	if (!FILE) {
		cout << "Error Opening File" << endl;
		return;
	}
	string e_pin = encrypt(U.pin[U.MARKER]);
	FILE << U.acc_name[U.MARKER] << ' ' << U.acc_num[U.MARKER] << ' ' << e_pin << ' ' << U.bday[U.MARKER] << ' ' << U.contact[U.MARKER] << ' ' << U.acc_bal[U.MARKER] << endl;

	FILE.close();
}

void atmfunctions::retrieve_acc() {
	ifstream FILE("accounts.txt");

	if (!FILE) {
		return;
	}
	int i = 0;
	string d_pin;
	string e_pin;

	while (FILE >> U.acc_name[i] >> U.acc_num[i] >> e_pin >> U.bday[i] >> U.contact[i] >> U.acc_bal[i]) {
		d_pin = decrypt(e_pin);
		U.pin[i] = d_pin;
		i++;
	}

	U.MARKER = i - 1;

	FILE.close();
}

string atmfunctions::encrypt(string x) {
	for (int i = 0; i < x.size(); i++) {
		x[i] = x[i] + 50;
	}
	return x;
}

string atmfunctions::decrypt(string x) {
	for (int i = 0; i < x.size(); i++) {
		x[i] = x[i] - 50;
	}
	return x;
}
