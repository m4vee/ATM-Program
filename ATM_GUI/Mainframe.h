#pragma once
#include <wx/wx.h>
#include "atmfunctions.h"
#define MAX 5
class Mainframe : public wxFrame
{
public:
	Mainframe(const wxString& title);
	void Register();
	void Transaction(int x);
	void Balance(int x);
	void Deposits();
	void Withdraws();
	void Fund_Transfer();
	void Change();
	atmfunctions A;
private:
	void OnButtonClicked(wxCommandEvent& evt);//button for each transaction
	void BalanceButton(wxCommandEvent& evt);
	void DepositsButton(wxCommandEvent& evt);
	void WithdrawsButton(wxCommandEvent& evt);
	void TransferButton(wxCommandEvent& evt);
	void ChangeButton(wxCommandEvent& evt);
	void ExitButton(wxCommandEvent& evt);//hanggang dito yung button for each transaction

	void BalanceBack(wxCommandEvent& evt);//back button for each transaction
	void DepositBack(wxCommandEvent& evt);
	void WithdrawBack(wxCommandEvent& evt);
	void FundTransBack(wxCommandEvent& evt);
	void ChangePinBack(wxCommandEvent& evt);//back button for each transaction
	void DepositProceed(wxCommandEvent& evt);
	void WithdrawProceed(wxCommandEvent& evt);
	void FundTransProceed(wxCommandEvent& evt);
	void ChangePinProceed(wxCommandEvent& evt);
	void RegProceed(wxCommandEvent& evt);
};

