#include <iostream>
#include <random>
#include <fstream>
#define MAX 5
using namespace std;

struct user {
	int MARKER;
	string acc_name[MAX];
	int acc_num[MAX];
	int pin[MAX];
	string bday[MAX];
	string contact[MAX];
	int acc_bal[MAX];
	int deposit_amount;
	int withdraw_amount;
	user () : MARKER(-1) {}
};

class ATM {
	private:
		user U;
	public:
		void bal_inq(int x); //done
		void reg_acc(); //done
		void withdraw();
		void deposit(); //done
		void fund_trans();
		void change_pin();//1111
		void retrieve_acc();
		void save_acc();
		int search_accNum(int x);//11
		int search_accPin(int x);//11

};

void ATM::bal_inq(int x){
	cout << "ATM\n\n";
	cout << "Account Balance: " << U.acc_bal[x] << endl;
}

void ATM::reg_acc(){
	int acc_p;
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
	} while (search_accNum(acc_n)==1);

	U.acc_num[U.MARKER] = acc_n;

	/*do {
		random_device rd;
		mt19937 gen(rd());

		uniform_int_distribution<> distr(1000, 9999);
		acc_p = distr(gen);
	} while (search_accPin(acc_p)==1);*/

	cout <<"ACOUNT DETAILS\n\n";
	cout << "Acount Name: " << U.acc_name[U.MARKER] << endl;
	cout << "Account Number: " << U.acc_num[U.MARKER] << endl;
	cout << "Account Pin: " << U.pin[U.MARKER] << endl;
	cout << "Birthday: " << U.bday[U.MARKER] << endl;
	cout << "Contact: " << U.contact[U.MARKER] << endl;

}

int ATM::search_accNum(int x){
	for(int i=0; i<=U.MARKER; i++){
		if(x==U.acc_num[i]){
			return 1;
		}
	}
	return -1;
}

int ATM::search_accPin(int x){
	for(int i=0; i<=U.MARKER; i++){
		if(x==U.pin[i]){
			return 1;
		}
	}
	return -1;
}

void ATM::deposit() {
    cout << "\n";
    cout << "DEPOSIT" << endl;
    cout << "Enter your account number: ";
    int account_number;
    cin >> account_number;


    int i = search_accNum(account_number);

    if (i == -1) {
        cout << "Account not found!" << endl;
        return;
    }
/*
    cout << "Enter your account pin: ";
    int entered_pin;
    cin >> entered_pin;

    if (U.pin[i] != entered_pin) {
        cout << "Invalid PIN!" << endl;
        return;
    }
*/
    cout << "Enter amount to deposit: ";
    cin >> U.deposit_amount;

    if (U.deposit_amount < 5000) {
        cout << "Invalid deposit amount!" << endl;
        cout << "The minimum deposit is 5000." << endl;
        return;}


else {
    cout << "Deposit successful!" << endl;
    U.acc_bal[i] = 0;
    U.acc_bal[i] += U.deposit_amount;
    cout << "New Account Balance: " << U.acc_bal[i] << endl;
}

}

void ATM::withdraw(){
    cout << "\n";
    cout << "WITHDRAW" << endl;
    cout << "Enter your account number: ";
    int account_number;
    cin >> account_number;

	int i = search_accNum(account_number);

    if (i == -1) {
        cout << "Account not found!" << endl;
        return;
    }

cout << "Enter amount to withdraw: ";
cin >> U.withdraw_amount;

if (U.withdraw_amount % 100 == 0){
	if (U.withdraw_amount <= U.acc_bal[i]){
        cout << "Withdrawal Successful" << endl;
        U.acc_bal[i] -= U.withdraw_amount;
        cout << "New Account Balance: " << U.acc_bal[i] << endl;
	}
	 else {
        cout << "Insufficient  Balance" << endl;
	}
}
	else {
        cout << "INVALID AMOUNT. IT MUST BE EXACT";
	}
}

void ATM::fund_trans(){
    int sender_account_num, recipient_acc_num, fund_transfer_amount, sender_pin;

     cout << "\n";
     cout << "FUND TRANSFER" << endl;
	 
	 cout << "Enter your account number: ";
     cin >> sender_account_num;

     int sender_index = search_accNum(sender_account_num);
     if (sender_index == -1) {
        cout << "Account not found!" << endl;
        return;
     }

      cout << "Enter your account PIN: ";
      cin >> sender_pin;
      if (U.pin[sender_index] != sender_pin){
            cout << "Invalid PIN!" << endl;
            return;
      }

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

      if (U.acc_bal[sender_index] < fund_transfer_amount){
        cout << "Insufficient balance!" << endl;
        return;
      }

      U.acc_bal[sender_index] -= fund_transfer_amount;
      U.acc_bal[recipient_index] += fund_transfer_amount;

      cout << "Transfer of Funds Successful" << endl;
      cout << "New Account Balance: " << U.acc_bal[sender_index] << endl;
}
int main(){
	ATM A;
	//A.reg_acc();
	//A.deposit();
	//A.withdraw();
	cout <<"hello";
	return 0;
}
