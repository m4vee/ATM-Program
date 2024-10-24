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
	user () : MARKER(-1) {}
};

class ATM {
	public:
        user U;
		void bal_inq(int x); 
		void reg_acc(); 
		void withdraw(int x);
		void deposit(int x); 
		void fund_trans(int x);
		void change_pin(int x);
		void retrieve_acc();
		void add_acc();
		int search_accNum(int x);
		int search_accPin(string x);
		void trans_menu(int x);
		void save_Allacc();
		void save_card();
		void scan_card();
        char check_flash_drive();
		string encrypt(string x);
		string decrypt(string x);
		string getPin();
};

void ATM::bal_inq(int x){
	cout << "ATM\n\n";
	cout << "Account Balance: " << U.acc_bal[x] << endl;
	return;
}

void ATM::reg_acc(){
    system("cls");
	int acc_n;
	U.MARKER++;
	cout << "ATM REGISTRATION\n\n";
	cout << "Account Name: ";
	cin >> U.acc_name[U.MARKER];
	cout << "Birthday: ";
	cin >> U.bday[U.MARKER];
	cout << "Contact Number: ";
	cin >> U.contact[U.MARKER];

	do {
		random_device rd;
		mt19937 gen(rd());

		uniform_int_distribution<> distr(10000, 99999);
		acc_n = distr(gen);
	} while (search_accNum(acc_n)>-1);

	U.acc_num[U.MARKER] = acc_n;

	U.acc_bal[U.MARKER] = 0;


	cout << "Enter 4-Digit Pin: ";
    U.pin[U.MARKER] = getPin();
    cout << "\nYour PIN is successfully captured.\n"; 
    system("cls");
	cout <<"ACOUNT DETAILS\n\n";
	cout << "Acount Name: " << U.acc_name[U.MARKER] << endl;
	cout << "Account Number: " << U.acc_num[U.MARKER] << endl;
	cout << "Account Pin: " << U.pin[U.MARKER] << endl;
	cout << "Birthday: " << U.bday[U.MARKER] << endl;
	cout << "Contact: " << U.contact[U.MARKER] << endl;

	add_acc();
    save_card();
    system("pause");
    string p;
    char ch;
    cout << "ATM" << endl;
	cout << "Enter Pin: ";
    p = getPin();
    if(search_accPin(p)==-1){
				cout << "\nINVALID PIN" << endl;
                system("pause");
			}
			else {
                scan_card();
				int MARKER = search_accNum(acc_n);
				trans_menu(MARKER);
			}
}

int ATM::search_accNum(int x){
	for(int i=0; i<=U.MARKER; i++){
		if(x==U.acc_num[i]){
			return i;
		}
	}
	return -1;
}

int ATM::search_accPin(string x){
	for(int i=0; i<=U.MARKER; i++){
		if(x==U.pin[i]){
			return i;
		}
	}
	return -1;
}

void ATM::deposit(int x) {
	int deposit_amount;
	string pin;
	char ch;
    cout << "DEPOSIT" << endl;
    cout << "\nEnter amount to deposit: ";
    cin >> deposit_amount;

    if (deposit_amount < 5000) {
        cout << "Invalid deposit amount!" << endl;
        cout << "The minimum deposit is 5000." << endl;
        return;
	}
	
	if (deposit_amount%100 != 0){
		cout << "Invalid deposit amount!" << endl;
		return;
	}
	else {
    		U.acc_bal[x] += deposit_amount;
			cout << "Deposit successful!" << endl;
    		cout << "New Account Balance: " << U.acc_bal[x] << endl;
			
	}
}

void ATM::withdraw(int x){
	int withdraw_amount;
    cout << "WITHDRAW" << endl;
    
cout << "\nEnter amount to withdraw: ";
cin >> withdraw_amount;

if (withdraw_amount % 100 == 0){
	if (withdraw_amount <= U.acc_bal[x]){
        cout << "\nWithdrawal Successful" << endl;
        U.acc_bal[x] -= withdraw_amount;
        cout << "New Account Balance: " << U.acc_bal[x] << endl;
	}
	 else {
        cout << "\nINSUFFICIENT BALANCE" << endl;
	}
}
	else {
        cout << "\nINVALID AMOUNT. IT MUST BE EXACT" << endl;
	}
}

void ATM::fund_trans(int x){
    int sender_account_num, recipient_acc_num, fund_transfer_amount;
	string sender_pin;
	char ch;

     cout << "FUND TRANSFER" << endl;
	 
      cout << "\nEnter recipient's account number: ";
      cin >> recipient_acc_num;

      int recipient_index = search_accNum(recipient_acc_num);
      if (recipient_index == -1){
            cout << "Recipient account is not found." << endl;
            return;
      }

      cout << "Enter amount to transfer: ";
      cin >> fund_transfer_amount;

      if (fund_transfer_amount % 100 != 0){
        cout << "INVALID AMOUNT. It must be divisible by 100." << endl;
        return;
      }

      if (U.acc_bal[x] < fund_transfer_amount){
        cout << "Insufficient balance!" << endl;
        return;
      }

      U.acc_bal[x] -= fund_transfer_amount;
      U.acc_bal[recipient_index] += fund_transfer_amount;

      cout << "Transfer of Funds Successful" << endl;
      cout << "New Account Balance: " << U.acc_bal[x] << endl;
}

void ATM::change_pin(int x) {
    string current_pin, new_pin, confirm_newPIN;
    cout << "CHANGE PIN" << endl;
    cout << "\nEnter your current PIN number: ";
    current_pin = getPin();
    if (x == -1) {
        cout << "\nInvalid PIN number!" << endl;
        return;
    }

    cout << "\nEnter your new PIN code: ";
    new_pin = getPin();
  
    cout << "\nConfirm your new PIN code: ";
    confirm_newPIN = getPin();
    if (new_pin == confirm_newPIN) {
        U.pin[x] = new_pin;  
        cout << "\nCongratulations, you have successfully changed your PIN!" << endl;
    } else {
        cout << "\nError: Your PINs do not match!" << endl;
    }
}

char ATM::check_flash_drive() {
    DWORD drive = GetLogicalDrives(); 

    for (int i = 3; i <= 6; i++) { 
        if (drive & (1 << i)) { 
            char driveLetter = 'D' + (i - 3);
            return driveLetter;
        }
    }
    return false;
}

void ATM::scan_card(){
	string acc_n;
	int acc_nm;
	string p;
	string bd;
	string cont;
	int acc_b;
	string FILE;

    switch(check_flash_drive()){
        case 'D':
        FILE = "D:\\accounts.txt";
        break;
        case 'E':
        FILE = "E:\\accounts.txt";
        break;
        case 'F':
        FILE ="F:\\accounts.txt";
        break;
        case 'G':
        FILE = "G:\\accounts.txt";
        break;
    }

	ifstream outFile(FILE);

	if(!outFile){
		cout << "Card Not Registered" << endl;
        system("pause");
		reg_acc();
	}

	outFile >> acc_n >> acc_nm >> p >> bd >> cont >> acc_b;
	string d_pin = decrypt(p);

	int i = search_accNum(acc_nm);
	U.acc_name[i] = acc_n;
	U.acc_number = U.acc_num[i] = acc_nm;
	U.pin[i] = d_pin;
	U.bday[i] = bd;
	U.contact[i] = cont;
	outFile.close();


	switch(check_flash_drive()){
        case 'D':
        FILE = "D:\\accounts.txt";
        break;
        case 'E':
        FILE = "E:\\accounts.txt";
        break;
        case 'F':
        FILE ="F:\\accounts.txt";
        break;
        case 'G':
        FILE = "G:\\accounts.txt";
        break;
    }

	ofstream outFILE(FILE);

	if(!outFILE){
		cout << "File Error" << endl;
		return;
	}
	string e_pin = encrypt(U.pin[U.MARKER]);
	outFILE << U.acc_name[i] << ' ' << U.acc_num[i] << ' ' << e_pin << ' ' << U.bday[i] << ' ' << U.contact[i] << ' ' << U.acc_bal[i] << endl; 
	outFILE.close();
}

void ATM::save_card(){
	string FILE;

    switch(check_flash_drive()){
        case 'D':
        FILE = "D:\\accounts.txt";
        break;
        case 'E':
        FILE = "E:\\accounts.txt";
        break;
        case 'F':
        FILE ="F:\\accounts.txt";
        break;
        case 'G':
        FILE = "G:\\accounts.txt";
        break;
    }
	ofstream outFile(FILE);

	if(!outFile){
		cout << "Error Opening File" << endl;
		return;
	}
	string e_pin = encrypt(U.pin[U.MARKER]);

	outFile << U.acc_name[U.MARKER] << ' ' << U.acc_num[U.MARKER] << ' ' << e_pin << ' ' << U.bday[U.MARKER] << ' ' << U.contact[U.MARKER] << ' ' << U.acc_bal[U.MARKER] << endl; 
	
	outFile.close();
}

void ATM::save_Allacc(){
	ofstream FILE("accounts.txt");

	if(!FILE){
		cout << "Error Opening File" << endl;
		return;
	}
	string e_pin;
	for(int i = 0; i <= U.MARKER; i++){
	e_pin = encrypt(U.pin[U.MARKER]);
	FILE << U.acc_name[i] << ' ' << U.acc_num[i] << ' ' << e_pin << ' ' << U.bday[i] << ' ' << U.contact[i] << ' ' << U.acc_bal[i] << endl; 
	}

	FILE.close();
}

void ATM::add_acc(){
	ofstream FILE("accounts.txt", ios::app);

	if(!FILE){
		cout << "Error Opening File" << endl;
		return;
	}
	string e_pin = encrypt(U.pin[U.MARKER]);
	FILE << U.acc_name[U.MARKER] << ' ' << U.acc_num[U.MARKER] << ' ' << e_pin << ' ' << U.bday[U.MARKER] << ' ' << U.contact[U.MARKER] << ' ' << U.acc_bal[U.MARKER] << endl; 
	
	FILE.close();
}

void ATM::retrieve_acc(){
	ifstream FILE("accounts.txt");

	if(!FILE){
		cout << "Error Opening File" << endl;
		return;
	}
	int i = 0;
	string d_pin;
	while (FILE >> U.acc_name[i] >> U.acc_num[i] >> U.pin[i] >> U.bday[i] >> U.contact[i] >> U.acc_bal[i]){
		d_pin = decrypt(U.pin[i]);
		U.pin[i] = d_pin;
		i++;
	}

	U.MARKER = i - 1;
	
	FILE.close();
}

void ATM::trans_menu(int x){
	int op;
    system("cls");
    
	cout << "TRANSACTION" << endl;
    cout << "Welcome " << U.acc_name[x] << endl;
	cout << "\n[1] Balance Inquiry" << endl;
	cout << "[2] Withdraw" << endl;
	cout << "[3] Deposit" << endl;
	cout << "[4] Fund Transfer" << endl;
	cout << "[5] Change PIN" << endl;
	cout << "[6] Exit" << endl;
	cout << "\nSelect: ";
	cin >> op;

	switch(op){
					case 1:
                        system("cls");
						bal_inq(x);
                        system("pause");
						trans_menu(x);
						break;
					case 2:
                        system("cls");
						withdraw(x);
						system("pause");
						trans_menu(x);
						break;
					case 3:
                        system("cls");
						deposit(x);
						system("pause");
						trans_menu(x);
						break;
					case 4:
                        system("cls");
						fund_trans(x);
						system("pause");
						trans_menu(x);
						break;
                    case 5:
                        system("cls");
                        change_pin(x);
						system("pause");
						trans_menu(x);
                        break;
                    case 6:
                        system("cls");
                        cout<<"Thank you for using our ATM" << endl;
						save_card();
						save_Allacc();
						system("pause");
                        exit(0);
                    default: 
                        cout<<"Invalid Input!";
                        break;
				}
}

string ATM::encrypt(string x){
	for(int i=0; i < x.size(); i++){
		x[i] = x[i] + 200;
	}
	return x;
}

string ATM::decrypt(string x){
	for(int i=0; i < x.size(); i++){
		x[i] = x[i] - 200;
	}
	return x;
}

string ATM::getPin() {
    string pin;
    char ch;
    int i = 0;

    while (i < 4) {
        ch = _getch(); 
        if (ch == 8) {
            if (!pin.empty()) {
                pin.pop_back();  
                cout << "\b \b"; 
                --i;  
            }
        }
        else if (isdigit(ch)) {
            pin += ch;  
            cout << '*'; 
            ++i;  
        }
    }

    return pin;  
}

int main(){
	ATM A;
	A.retrieve_acc();
	string pin;
	char  ch;
	int i;
    
    while(A.check_flash_drive() == false){
        system("cls");
        cout << "ATM" << endl;
        cout << "Please Insert Your Card" << endl;
    }
    system("cls");
    cout << "ATM" << endl;
    A.scan_card();
	cout << "Enter Pin: ";
    pin = A.getPin();
    if(A.search_accPin(pin)==-1){
				cout << "\nINVALID PIN" << endl;
                system("pause");
			}
			else {
				int MARKER = A.search_accNum(A.U.acc_number);
				A.trans_menu(MARKER);
			}
	return 0;
}