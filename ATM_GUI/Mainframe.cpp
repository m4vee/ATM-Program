#include "Mainframe.h"
#include <wx/wx.h>

wxPanel* home;
wxPanel* transaction;


wxFont titleFont(80, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD);
wxFont brandFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
wxFont textFont(32, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
wxFont createFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
wxFont fieldFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
wxFont pastFont(40, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);


wxPanel* insertPanel;
wxStaticText* inserttxt;
wxStaticText* atminserttxt;

wxStaticText* atm_ntxt; //title page kada panel
wxStaticText* transtxt;
wxStaticText* usertxt;
wxStaticText* baltxt;
wxStaticText* depotxt;
wxStaticText* withrtxt;
wxStaticText* fundtxt;
wxStaticText* chgeptxt;//hanggang dito yung title page panel

//Register Panel
wxPanel* reg;
wxStaticText* regtxt;
wxStaticText* nametxt;
wxTextCtrl* name;
wxStaticText* bdaytxt;
wxStaticText* b_daytxt;
wxChoice* month;
wxChoice* day;
wxChoice* year;
wxStaticText* contacttxt;
wxTextCtrl* contact;
wxStaticText* regpintxt;
wxTextCtrl* regpin;
wxButton* proceedreg;

//Balance Inquiry Panel
wxPanel* balance;
wxStaticText* disp_bal;


//Deposit Panel
wxPanel* depo;
wxStaticText* depo_amnt_entrtxt;//Static txt enter amount for deposit
wxTextCtrl* depo_entr_amnt;//enter amount for deposit
wxButton* proceed_depo_amnt;

//Withdraw Panel
wxPanel* withdraw;
wxStaticText* withr_amnt_entrtxt;
wxTextCtrl* withr_entr_amnt;
wxButton* proceed_withr_amnt;

//Fund Transfer Panel
wxPanel* fund_t;
wxStaticText* recpnt_accntxt;
wxTextCtrl* recpnt_accn;
wxStaticText* trans_entr_amnttxt;
wxTextCtrl* trans_entr_amnt;
wxButton* proceed_trans_amnt;

//Change PIN Panel
wxPanel* chge_p;
wxStaticText* crrnt_pintxt;
wxTextCtrl* crrnt_pin;
wxStaticText* new_pintxt;
wxTextCtrl* new_pin;
wxStaticText* cnfrmnew_pintxt;
wxTextCtrl* cnfrmnew_pin;
wxButton* proceed_chgepin;


wxButton* enter_p; //enter pin button sa simula
wxButton* bal_inq; //button kada transaction
wxButton* deposit;
wxButton* withrbtn;
wxButton* fund_trans;
wxButton* change_p;
wxButton* exits;//hanggang dito yung button of each transaction

wxButton* balinq_b; //back button kada transaction
wxButton* depo_b;
wxButton* withr_b;
wxButton* fndtrns_b;
wxButton* chgep_b;//hanggang dito yung button kada transaction


wxTextCtrl* pin;//for pin input at the start


Mainframe::Mainframe(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    A.retrieve_acc();
    home = new wxPanel(this);
    atm_ntxt = new wxStaticText(home, wxID_ANY, "ATM", wxPoint(330, 100));
    atm_ntxt->SetFont(titleFont);

    enter_p = new wxButton(home, wxID_ANY, "ENTER", wxPoint(520, 350), wxSize(200, 50));
    enter_p->SetFont(fieldFont);
    pin = new wxTextCtrl(home, wxID_ANY, "", wxPoint(200, 350), wxSize(300, 50), wxTE_PASSWORD);
    pin->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    enter_p->Bind(wxEVT_BUTTON, &Mainframe::OnButtonClicked, this);

    reg = new wxPanel(this);
    transaction = new wxPanel(this);
    balance = new wxPanel(this);
    depo = new wxPanel(this);
    withdraw = new wxPanel(this);
    fund_t = new wxPanel(this);
    chge_p = new wxPanel(this);
    insertPanel = new wxPanel(this);

    atminserttxt = new wxStaticText(insertPanel, wxID_ANY, "ATM", wxPoint(330, 100));
    atminserttxt->SetFont(titleFont);

    inserttxt = new wxStaticText(insertPanel, wxID_ANY, "PLEASE INSERT YOUR CARD!", wxPoint(150, 300));
    inserttxt->SetFont(textFont);


    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(home, 1, wxEXPAND);
    mainSizer->Add(reg, 1, wxEXPAND);
    mainSizer->Add(transaction, 1, wxEXPAND);
    mainSizer->Add(balance, 1, wxEXPAND);
    mainSizer->Add(depo, 1, wxEXPAND);
    mainSizer->Add(withdraw, 1, wxEXPAND);
    mainSizer->Add(fund_t, 1, wxEXPAND);
    mainSizer->Add(chge_p, 1, wxEXPAND);
    mainSizer->Add(insertPanel, 1, wxEXPAND);

    SetSizer(mainSizer);

    insertPanel->Show();
    
    home->Hide();
    reg->Hide();
    transaction->Hide();
    balance->Hide();
    depo->Hide();
    withdraw->Hide();
    fund_t->Hide();
    chge_p->Hide();

    insertPanel->Show();

    wxTimer* timer = new wxTimer(this, wxID_ANY);
    Bind(wxEVT_TIMER, [=](wxTimerEvent&) {
        if (A.check_flash_drive() != false) {
            insertPanel->Hide();
            timer->Stop();
            bool check = A.scan_card();
            if (check == false) {
                Register();
                reg->Show();
            }
            else {  
                home->Show();
            }
            Layout();

        }
        });



    timer->Start(1000);
    Layout();
}

void Mainframe::Register() {
    regtxt = new wxStaticText(reg, wxID_ANY, "REGISTER ACCOUNT", wxPoint(170, 50));
    regtxt->SetFont(pastFont);

    nametxt = new wxStaticText(reg, wxID_ANY, "NAME:", wxPoint(190, 150));
    nametxt->SetFont(brandFont);
    name = new wxTextCtrl(reg, wxID_ANY, "", wxPoint(290,150), wxSize(400,25));

    bdaytxt = new wxStaticText(reg, wxID_ANY, "BIRTHDAY:", wxPoint(190, 250));
    bdaytxt->SetFont(brandFont);
    wxArrayString m_choice;
    m_choice.Add("January");
    m_choice.Add("February");
    m_choice.Add("March");
    m_choice.Add("April");
    m_choice.Add("May");
    m_choice.Add("June");
    m_choice.Add("July");
    m_choice.Add("August");
    m_choice.Add("September");
    m_choice.Add("October");
    m_choice.Add("November");
    m_choice.Add("December");

    wxArrayString d_choice;
    d_choice.Add("1");
    d_choice.Add("2");
    d_choice.Add("3");
    d_choice.Add("4");
    d_choice.Add("5");
    d_choice.Add("6");
    d_choice.Add("7");
    d_choice.Add("8");
    d_choice.Add("9");
    d_choice.Add("10");
    d_choice.Add("11");
    d_choice.Add("12");
    d_choice.Add("13");
    d_choice.Add("14");
    d_choice.Add("15");
    d_choice.Add("16");
    d_choice.Add("17");
    d_choice.Add("18");
    d_choice.Add("19");
    d_choice.Add("20");
    d_choice.Add("21");
    d_choice.Add("22");
    d_choice.Add("23");
    d_choice.Add("24");
    d_choice.Add("25");
    d_choice.Add("26");
    d_choice.Add("27");
    d_choice.Add("28");
    d_choice.Add("29");
    d_choice.Add("30");
    d_choice.Add("31");

    wxArrayString y_choice;
    y_choice.Add("2024");
    y_choice.Add("2023");
    y_choice.Add("2022");
    y_choice.Add("2021");
    y_choice.Add("2020");
    y_choice.Add("2019");
    y_choice.Add("2018");
    y_choice.Add("2017");
    y_choice.Add("2016");
    y_choice.Add("2015");
    y_choice.Add("2014");
    y_choice.Add("2013");
    y_choice.Add("2012");
    y_choice.Add("2011");
    y_choice.Add("2010");
    y_choice.Add("2009");
    y_choice.Add("2008");
    y_choice.Add("2007");
    y_choice.Add("2006");
    y_choice.Add("2005");
    y_choice.Add("2004");
    y_choice.Add("2003");
    y_choice.Add("2002");
    y_choice.Add("2001");
    y_choice.Add("2000");
    y_choice.Add("1999");
    y_choice.Add("1998");
    y_choice.Add("1997");
    y_choice.Add("1996");
    y_choice.Add("1995");
    y_choice.Add("1994");
    y_choice.Add("1993");
    y_choice.Add("1992");
    y_choice.Add("1991");
    y_choice.Add("1990");
    y_choice.Add("1989");
    y_choice.Add("1988");
    y_choice.Add("1987");
    y_choice.Add("1986");
    y_choice.Add("1985");
    y_choice.Add("1984");
    y_choice.Add("1983");
    y_choice.Add("1982");
    y_choice.Add("1981");
    y_choice.Add("1980");
    y_choice.Add("1979");
    y_choice.Add("1978");
    y_choice.Add("1977");
    y_choice.Add("1976");
    y_choice.Add("1975");
    y_choice.Add("1974");
    y_choice.Add("1973");
    y_choice.Add("1972");
    y_choice.Add("1971");
    y_choice.Add("1970");
    y_choice.Add("1969");
    y_choice.Add("1968");
    y_choice.Add("1967");
    y_choice.Add("1966");
    y_choice.Add("1965");
    y_choice.Add("1964");
    y_choice.Add("1963");
    y_choice.Add("1962");
    y_choice.Add("1961");
    y_choice.Add("1960");
    y_choice.Add("1959");
    y_choice.Add("1958");
    y_choice.Add("1957");
    y_choice.Add("1956");
    y_choice.Add("1955");
    y_choice.Add("1954");
    y_choice.Add("1953");
    y_choice.Add("1952");
    y_choice.Add("1951");
    y_choice.Add("1950");


    b_daytxt = new wxStaticText(reg, wxID_ANY, "MONTH           DAY             YEAR", wxPoint(320, 250));
    b_daytxt->SetFont(brandFont);
    month = new wxChoice(reg, wxID_ANY, wxPoint(300,275), wxSize(100, 25), m_choice);
    day = new wxChoice(reg, wxID_ANY, wxPoint(420, 275), wxSize(100, 25), d_choice);
    year = new wxChoice(reg, wxID_ANY, wxPoint(540, 275), wxSize(100, 25), y_choice);

    contacttxt = new wxStaticText(reg, wxID_ANY, "CONTACT:", wxPoint(190, 350));
    contacttxt->SetFont(brandFont);
    contact = new wxTextCtrl(reg, wxID_ANY, "", wxPoint(290, 350), wxSize(400, 25));

    regpintxt = new wxStaticText(reg, wxID_ANY, "ENTER 4-DIGIT PIN:", wxPoint(190, 450));
    regpintxt->SetFont(brandFont);
    regpin = new wxTextCtrl(reg, wxID_ANY, "", wxPoint(390, 450), wxSize(300, 25), wxTE_PASSWORD);

    proceedreg = new wxButton(reg, wxID_ANY, "PROCEED", wxPoint(550, 550), wxSize(300, 100));
    proceedreg->SetFont(fieldFont);
    proceedreg->Bind(wxEVT_BUTTON, &Mainframe::RegProceed, this);



}

void Mainframe::Transaction(int x) {
    transtxt = new wxStaticText(transaction, wxID_ANY, "TRANSACTION", wxPoint(260, 50));
    transtxt->SetFont(pastFont);

    usertxt = new wxStaticText(transaction, wxID_ANY, wxString::Format("WELCOME, %s", A.U.acc_name[x]), wxPoint(50, 120));
    usertxt->SetFont(fieldFont);

    bal_inq = new wxButton(transaction, wxID_ANY, "BALANCE INQUIRY", wxPoint(100, 200), wxSize(300, 100));
    bal_inq->SetFont(fieldFont);
    bal_inq->Bind(wxEVT_BUTTON, &Mainframe::BalanceButton, this);

    deposit = new wxButton(transaction, wxID_ANY, "DEPOSIT", wxPoint(100, 330), wxSize(300, 100));
    deposit->SetFont(fieldFont);
    deposit->Bind(wxEVT_BUTTON, &Mainframe::DepositsButton, this);

    withrbtn = new wxButton(transaction, wxID_ANY, "WITHDRAW", wxPoint(100, 460), wxSize(300, 100));
    withrbtn->SetFont(fieldFont);
    withrbtn->Bind(wxEVT_BUTTON, &Mainframe::WithdrawsButton, this);


    fund_trans = new wxButton(transaction, wxID_ANY, "FUND TRANSFER", wxPoint(500, 200), wxSize(300, 100));
    fund_trans->SetFont(fieldFont);
    fund_trans->Bind(wxEVT_BUTTON, &Mainframe::TransferButton, this);


    change_p = new wxButton(transaction, wxID_ANY, "CHANGE PIN", wxPoint(500, 330), wxSize(300, 100));
    change_p->SetFont(fieldFont);
    change_p->Bind(wxEVT_BUTTON, &Mainframe::ChangeButton, this);


    exits = new wxButton(transaction, wxID_ANY, "EXIT", wxPoint(500, 460), wxSize(300, 100));
    exits->SetFont(fieldFont);
    exits->Bind(wxEVT_BUTTON, &Mainframe::ExitButton, this);
}

void Mainframe::Balance(int x) {
    baltxt = new wxStaticText(balance, wxID_ANY, "BALANCE INQUIRY", wxPoint(215, 50));
    baltxt->SetFont(pastFont);

    disp_bal = new wxStaticText(balance, wxID_ANY, "", wxPoint(215,150));
    disp_bal->SetLabel(wxString::Format("BALANCE: %d", A.U.acc_bal[x]));
    disp_bal->SetFont(fieldFont);

    balinq_b = new wxButton(balance, wxID_ANY, "BACK", wxPoint(550, 550), wxSize(300, 100));
    balinq_b->SetFont(fieldFont);
    balinq_b->Bind(wxEVT_BUTTON, &Mainframe::BalanceBack, this);
}

void Mainframe::Deposits() {
    depotxt = new wxStaticText(depo, wxID_ANY, "DEPOSIT", wxPoint(320, 50));
    depotxt->SetFont(pastFont);

    depo_b = new wxButton(depo, wxID_ANY, "CANCEL", wxPoint(550, 550), wxSize(300, 100));
    depo_b->SetFont(fieldFont);
    depo_b->Bind(wxEVT_BUTTON, &Mainframe::DepositBack, this);

    depo_amnt_entrtxt = new wxStaticText(depo, wxID_ANY, "ENTER AMOUNT:", wxPoint(200, 150));
    depo_amnt_entrtxt->SetFont(fieldFont);

    depo_entr_amnt = new wxTextCtrl(depo, wxID_ANY, "", wxPoint(450, 150), wxSize(250,30));
    depo_entr_amnt->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    proceed_depo_amnt = new wxButton(depo, wxID_ANY, "PROCEED", wxPoint(200,200), wxSize(500,100));
    proceed_depo_amnt->SetFont(fieldFont);
    proceed_depo_amnt->Bind(wxEVT_BUTTON, &Mainframe::DepositProceed, this);

}

void Mainframe::Withdraws() {
    withrtxt = new wxStaticText(withdraw, wxID_ANY, "WITHDRAW", wxPoint(320, 50));
    withrtxt->SetFont(pastFont);

    withr_b = new wxButton(withdraw, wxID_ANY, "CANCEL", wxPoint(550, 550), wxSize(300, 100));
    withr_b->SetFont(fieldFont);
    withr_b->Bind(wxEVT_BUTTON, &Mainframe::WithdrawBack, this);

    withr_amnt_entrtxt = new wxStaticText(withdraw, wxID_ANY, "ENTER AMOUNT:", wxPoint(200, 150));
    withr_amnt_entrtxt->SetFont(fieldFont);

    withr_entr_amnt = new wxTextCtrl(withdraw, wxID_ANY, "", wxPoint(450, 150), wxSize(250, 30));
    withr_entr_amnt->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    proceed_withr_amnt = new wxButton(withdraw, wxID_ANY, "PROCEED", wxPoint(200, 200), wxSize(500, 100));
    proceed_withr_amnt->SetFont(fieldFont);
    proceed_withr_amnt->Bind(wxEVT_BUTTON, &Mainframe::WithdrawProceed, this);
}

void Mainframe::Fund_Transfer() {
    fundtxt = new wxStaticText(fund_t, wxID_ANY, "FUND TRANSFER", wxPoint(230, 50));
    fundtxt->SetFont(pastFont);

    fndtrns_b = new wxButton(fund_t, wxID_ANY, "CANCEL", wxPoint(550, 550), wxSize(300, 100));
    fndtrns_b->SetFont(fieldFont);
    fndtrns_b->Bind(wxEVT_BUTTON, &Mainframe::FundTransBack, this);

    recpnt_accntxt = new wxStaticText(fund_t, wxID_ANY, "RECIPIENT ACCOUNT #:", wxPoint(140, 150));
    recpnt_accntxt->SetFont(fieldFont);

    recpnt_accn = new wxTextCtrl(fund_t, wxID_ANY, "", wxPoint(500,150), wxSize(250, 30));
    recpnt_accn->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    trans_entr_amnttxt = new wxStaticText(fund_t, wxID_ANY, "ENTER AMOUNT:", wxPoint(140, 200));
    trans_entr_amnttxt->SetFont(fieldFont);

    trans_entr_amnt = new wxTextCtrl(fund_t, wxID_ANY, "", wxPoint(500,200), wxSize(250, 30));
    trans_entr_amnt->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    proceed_trans_amnt = new wxButton(fund_t, wxID_ANY, "PROCEED", wxPoint(140,250), wxSize(610,60));
    proceed_trans_amnt->SetFont(fieldFont);
    proceed_trans_amnt->Bind(wxEVT_BUTTON, &Mainframe::FundTransProceed, this);
}

void Mainframe::Change() {
    chgeptxt = new wxStaticText(chge_p, wxID_ANY, "CHANGE PIN", wxPoint(275, 50));
    chgeptxt->SetFont(pastFont);

    chgep_b = new wxButton(chge_p, wxID_ANY, "CANCEL", wxPoint(550, 550), wxSize(300, 100));
    chgep_b->SetFont(fieldFont);
    chgep_b->Bind(wxEVT_BUTTON, &Mainframe::ChangePinBack, this);

    crrnt_pintxt = new wxStaticText(chge_p, wxID_ANY, "CURRENT PIN:", wxPoint(220, 150));
    crrnt_pintxt->SetFont(fieldFont);

    crrnt_pin = new wxTextCtrl(chge_p, wxID_ANY, "", wxPoint(420,150), wxSize(250, 30), wxTE_PASSWORD);
    crrnt_pin->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    new_pintxt = new wxStaticText(chge_p, wxID_ANY, "NEW PIN:", wxPoint(220, 220));
    new_pintxt->SetFont(fieldFont);

    new_pin = new wxTextCtrl(chge_p, wxID_ANY, "", wxPoint(420, 220), wxSize(250, 30), wxTE_PASSWORD);
    new_pin->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    cnfrmnew_pintxt = new wxStaticText(chge_p, wxID_ANY, "CONFIRM PIN:", wxPoint(220, 270));
    cnfrmnew_pintxt->SetFont(fieldFont);

    cnfrmnew_pin = new wxTextCtrl(chge_p, wxID_ANY, "", wxPoint(420, 270), wxSize(250, 30), wxTE_PASSWORD);
    cnfrmnew_pin->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    proceed_chgepin = new wxButton(chge_p, wxID_ANY, "PROCEED", wxPoint(220, 320), wxSize(450, 60));
    proceed_chgepin->SetFont(fieldFont);
    proceed_chgepin->Bind(wxEVT_BUTTON, &Mainframe::ChangePinProceed, this);
}


void Mainframe::OnButtonClicked(wxCommandEvent& evt) {
    int MARKER = A.search_accNum(A.U.acc_number);
    wxString getpin = pin->GetValue();
    string getpinstr = getpin.ToStdString();
    if (getpinstr!=A.U.pin[MARKER]) {
        wxLogMessage("INVALID PIN");
        pin->Clear();
        return;
    }
    home->Hide();
    Transaction(MARKER);
    transaction->Show();
    pin->Clear();
    Layout();
}

void Mainframe::BalanceButton(wxCommandEvent& evt) {
    int MARKER = A.search_accNum(A.U.acc_number);
    transaction->Hide();
    Balance(MARKER);
    balance->Show();
    Layout();
}

void Mainframe::DepositsButton(wxCommandEvent& evt) {
    transaction->Hide();
    Deposits();
    depo->Show();
    Layout();
}

void Mainframe::WithdrawsButton(wxCommandEvent& evt) {
    transaction->Hide();
    Withdraws();
    withdraw->Show();
    Layout();
}
		
void Mainframe::TransferButton(wxCommandEvent& evt) {
    transaction->Hide();
    Fund_Transfer();
    fund_t->Show();
    Layout();
}

void Mainframe::ChangeButton(wxCommandEvent& evt) {
    transaction->Hide();
    Change();
    chge_p->Show();
    Layout();
}
			
void Mainframe::ExitButton(wxCommandEvent& evt) {
    int MARKER = A.search_accNum(A.U.acc_number);
    A.save_Allacc();
    A.save_card(MARKER);
    transaction->Hide();
    home->Show();
    Layout();
    Close(true);
}

void Mainframe::BalanceBack(wxCommandEvent& evt) {
    balance->Hide();
    transaction->Show();
    Layout();
}

void Mainframe::DepositBack(wxCommandEvent& evt) {
    depo->Hide();
    transaction->Show();
    Layout();
}

void Mainframe::WithdrawBack(wxCommandEvent& evt) {
    withdraw->Hide();
    transaction->Show();
    Layout();
}

void Mainframe::FundTransBack(wxCommandEvent& evt) {
    fund_t->Hide();
    transaction->Show();
    Layout();
}

void Mainframe::ChangePinBack(wxCommandEvent& evt) {
    chge_p->Hide();
    transaction->Show();
    Layout();
}

void Mainframe::DepositProceed(wxCommandEvent& evt) {
    int MARKER = A.search_accNum(A.U.acc_number);
    wxString dep_amnt = depo_entr_amnt->GetValue(); 
    depo_entr_amnt->Clear();
    A.deposit(MARKER, dep_amnt);
    depo->Hide();
    transaction->Show();
}

void Mainframe::WithdrawProceed(wxCommandEvent& evt) {
    int MARKER = A.search_accNum(A.U.acc_number);
    wxString withr_amnt = withr_entr_amnt->GetValue();
    withr_entr_amnt->Clear();
    A.withdraw(MARKER, withr_amnt);
    withdraw->Hide();
    transaction->Show();
}

void Mainframe::FundTransProceed(wxCommandEvent& evt) {
    int MARKER = A.search_accNum(A.U.acc_number);
    wxString acc_n = recpnt_accn->GetValue();
    wxString amnt = trans_entr_amnt->GetValue();
    recpnt_accn->Clear();
    trans_entr_amnt->Clear();
    A.fund_trans(MARKER, acc_n, amnt);
    fund_t->Hide();
    transaction->Show();
    Layout();
}

void Mainframe::ChangePinProceed(wxCommandEvent& evt) {
    int MARKER = A.search_accNum(A.U.acc_number);
    wxString pin_crrnt = crrnt_pin->GetValue();
    wxString pin_new = new_pin->GetValue();
    wxString pin_cnfrm = cnfrmnew_pin->GetValue();
    crrnt_pin->Clear();
    new_pin->Clear();
    cnfrmnew_pin->Clear();
    A.change_pin(MARKER, pin_crrnt, pin_new, pin_cnfrm);
    chge_p->Hide();
    transaction->Show();
    Layout();
}

void Mainframe::RegProceed(wxCommandEvent& evt) {
    wxString nme = name->GetValue();
    wxString bday_m = month->GetStringSelection();
    wxString bday_d = day->GetStringSelection();
    wxString bday_y = year->GetStringSelection();
    wxString cntact = contact->GetValue();
    wxString pin_reg = regpin->GetValue();
    A.reg_acc(nme, bday_m, bday_d, bday_y, cntact, pin_reg);
    name->Clear();
    month->SetSelection(-1);
    day->SetSelection(-1);
    year->SetSelection(-1);
    contact->Clear();
    regpin->Clear();
    reg->Hide();
    home->Show();
    Layout();
}