
#include <iostream>
#include <random>
#include <fstream>
#include <unistd.h>
//#include <windows.h>
//#include <conio.h>
#include <string>
#define MAX 5
using namespace std;

struct user {
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
	private:
		user U;
	public:
		void bal_inq(int x); 
		void reg_acc(); 
		void withdraw(int x);
		void deposit(int x); 
		void fund_trans(int x);
		void change_pin();
		void retrieve_acc();
		void add_acc();
		int search_accNum(int x);
		int search_accPin(string x);
		int main_menu();
		void trans_menu(int x);
		void save_Allacc();
        bool check_flash_drive(); 
		void save_card();
		void scan_card();
		void save_c();
};

void ATM::bal_inq(int x){
	cout << "ATM\n\n";
	cout << "Account Balance: " << U.acc_bal[x] << endl;
	sleep(3);
	return;
}

void ATM::reg_acc(){
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

	cout << "Register Pin: "; //temporary input for PIN
	cin >> U.pin[U.MARKER];
	cout << "PIN Succesfully Registered" << endl;

	//Original PIN input yung nasa comment

	/* char pin[5];  // To store the 4-digit PIN, +1 for null terminator
    cout << "Enter your 4-digit PIN: ";

    for (int i = 0; i < 4; ++i) {
        pin[i] = _getch();  // Capture the key press
        cout << '*';   // Print a '' to indicate a key press
    }
    pin[4] = '\0';  // Null terminate the string

   cout << "\nYour PIN is successfully captured.\n"; */

	cout <<"ACOUNT DETAILS\n\n";
	cout << "Acount Name: " << U.acc_name[U.MARKER] << endl;
	cout << "Account Number: " << U.acc_num[U.MARKER] << endl;
	cout << "Account Pin: " << U.pin[U.MARKER] << endl;
	cout << "Birthday: " << U.bday[U.MARKER] << endl;
	cout << "Contact: " << U.contact[U.MARKER] << endl;

	add_acc();
	//trans_menu(U.MARKER);
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

    //cout << "\n";
    cout << "Enter amount to deposit: ";
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
    cout << "\n";
    cout << "WITHDRAW" << endl;
    /*cout << "Enter your account number: ";
    int account_number;
    cin >> account_number;

	int i = search_accNum(account_number);

    if (i == -1) {
        cout << "Account not found!" << endl;
        return;
    }*/

//int i = search_accNum(account_number);
cout << "Enter amount to withdraw: ";
cin >> withdraw_amount;

if (withdraw_amount % 100 == 0){
	if (withdraw_amount <= U.acc_bal[x]){
        cout << "Withdrawal Successful" << endl;
        U.acc_bal[x] -= withdraw_amount;
        cout << "New Account Balance: " << U.acc_bal[x] << endl;
	}
	 else {
        cout << "Insufficient  Balance" << endl;
	}
}
	else {
        cout << "INVALID AMOUNT. IT MUST BE EXACT";
	}
}

void ATM::fund_trans(int x){
    int sender_account_num, recipient_acc_num, fund_transfer_amount;
	string sender_pin;
	char ch;
     cout << "\n";
     cout << "FUND TRANSFER" << endl;
	 
	 /*cout << "Enter your account number: ";
     cin >> sender_account_num;

     int sender_index = search_accNum(sender_account_num);
     if (sender_index == -1) {
        cout << "Account not found!" << endl;
        return;
     }

      cout << "Enter your account PIN: ";
      cin >> sender_pin;
	  for (int i = 0; i < 4; ++i) {
        // temp comment ch = _getch();   
        sender_pin += ch;
        cout << '*';     
    
    cout << "\n";
      if (U.pin[sender_index] != sender_pin){
            cout << "Invalid PIN!" << endl;
            return;
      } 
*/
      cout << "Enter recipient's account number: ";
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

void ATM::change_pin() {
    string current_pin, new_pin, confirm_newPIN;

    cout << "Enter your current PIN number: ";
    char ch;
    for (int i = 0; i < 4; ++i) {
        // temp comment ch = _getch();   
        current_pin += ch;
        cout << '*';     
    }
    cout << "\n";  

    int i = search_accPin(current_pin);
    if (i == -1) {
        cout << "Invalid PIN number!" << endl;
        return;
    }

    cout << "Enter your new PIN code: ";
    for (int i = 0; i < 4; ++i) {
        // temp comment ch = _getch();   // Capture key press
        new_pin += ch;
        cout << '*';     // Print asterisks for each key press
    }
    cout << "\n";  // Move to the next line after input

    cout << "Confirm your new PIN code: ";
    for (int i = 0; i < 4; ++i) {
        // temp comment ch = _getch();   
        confirm_newPIN += ch;
        cout << '*';     
    }
    cout << "\n";  

    if (new_pin == confirm_newPIN) {
        U.pin[i] = new_pin;  
        cout << "Congratulations, you have successfully changed your PIN!" << endl;
    } else {
        cout << "Error: Your PINs do not match!" << endl;
    }
}

void ATM::save_card(){
	string FILE = "D:\\accounts.txt";

	ofstream outFile(FILE);

	if(!outFile){
		cout << "File not found" << endl;
		return;
	}
	outFile << U.acc_name[U.MARKER] << ' ' << U.acc_num[U.MARKER] << ' ' << U.pin[U.MARKER] << ' ' << U.bday[U.MARKER] << ' ' <<  U.contact[U.MARKER] << ' ' << U.acc_bal[U.MARKER] << endl;

	outFile.close();
}

void ATM::scan_card(){
	string acc_n;
	int acc_nm;
	string p;
	string bd;
	string cont;
	int acc_b;

	string FILE = "D:\\accounts.txt";

	ifstream outFile(FILE);

	if(!outFile){
		cout << "Not Registered" << endl;
		reg_acc();
	}

	outFile >> acc_n >> acc_nm >> p >> bd >> cont >> acc_b;

	int i = search_accNum(acc_nm);
	U.acc_name[i] = acc_n;
	U.acc_num[i] = acc_nm;
	U.pin[i] = p;
	U.bday[i] = bd;
	U.contact[i] = cont;
	U.acc_bal[i] = acc_b;
	outFile.close();
}

void ATM::save_c(){
	string FILE = "D:\\accounts.txt";
	ofstream outFile(FILE);

	if(!outFile){
		cout << "Error Opening File" << endl;
		return;
	}

	outFile << U.acc_name[U.MARKER] << ' ' << U.acc_num[U.MARKER] << ' ' << U.pin[U.MARKER] << ' ' << U.bday[U.MARKER] << ' ' << U.contact[U.MARKER] << ' ' << U.acc_bal[U.MARKER] << endl; 
	
	outFile.close();
	cout << "Account Saved Successfully" << endl; //temporary cout
}

void ATM::save_Allacc(){
	ofstream FILE("accounts.txt");

	if(!FILE){
		cout << "Error Opening File" << endl;
		return;
	}

	for(int i = 0; i <= U.MARKER; i++){
	FILE << U.acc_name[i] << ' ' << U.acc_num[i] << ' ' << U.pin[i] << ' ' << U.bday[i] << ' ' << U.contact[i] << ' ' << U.acc_bal[i] << endl; 
	}

	FILE.close();
	cout << "Account Saved Successfully" << endl; //temporary cout
}

void ATM::add_acc(){
	ofstream FILE("accounts.txt", ios::app);

	if(!FILE){
		cout << "Error Opening File" << endl;
		return;
	}

	FILE << U.acc_name[U.MARKER] << ' ' << U.acc_num[U.MARKER] << ' ' << U.pin[U.MARKER] << ' ' << U.bday[U.MARKER] << ' ' << U.contact[U.MARKER] << ' ' << U.acc_bal[U.MARKER] << endl; 
	
	FILE.close();
	cout << "Account Saved Successfully" << endl; //temporary cout
}

void ATM::retrieve_acc(){
	ifstream FILE("accounts.txt");

	if(!FILE){
		cout << "Error Opening File" << endl;
		return;
	}
	int i = 0;
	while (FILE >> U.acc_name[i] >> U.acc_num[i] >> U.pin[i] >> U.bday[i] >> U.contact[i] >> U.acc_bal[i]){
		i++;
	}

	U.MARKER = i - 1;
	
	FILE.close();
	cout << "Accounts Loaded Successfully" << endl; //temporary cout
}

int ATM::main_menu(){
	int op;
	cout << "ATM" << endl;
	cout << "\n[1] Register" << endl;
	cout << "[2] Transaction" << endl;
	cout << "\nSelect: ";
	cin >> op;

	return op;
}

void ATM::trans_menu(int x){
	int op;

	cout << "TRANSACTION" << endl;
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
						bal_inq(x);
						trans_menu(x);
						break;
					case 2:
						withdraw(x);
						sleep(3);
						trans_menu(x);
						break;
					case 3:
						deposit(x);
						sleep(3);
						trans_menu(x);
						break;
					case 4:
						fund_trans(x);
						sleep(3);
						trans_menu(x);
						break;
                    case 5:
                        change_pin();
						sleep(3);
						trans_menu(x);
                        break;
                    case 6:
                        cout<<"Thank you for using our program";
						save_c();
						save_Allacc();
						sleep(3);
                        exit(0);
                    default: 
                        cout<<"Invalid Input!";
                        break;
				}
	//save_Allacc();
}

int main(){
	ATM A;
	A.retrieve_acc();
	string pin;
	char  ch;
	int i;
	switch(A.main_menu()){
		case 1:
			A.reg_acc();
			break;
		case 2:
			A.scan_card();
			cout << "Enter Pin: "; 
			cin >> pin;
			/*for(i=0;i<4;i++){
				//ch = _getch();
				pin += ch;
				cout<<'*';
			}
			cout<<"/n";*/
	}
			if(A.search_accPin(pin)==-1){
				cout << "INVALID PIN" << endl;
				
			}
			else {
				int MARKER = A.search_accPin(pin);
				A.trans_menu(MARKER);
			}
	
	return 0;
}