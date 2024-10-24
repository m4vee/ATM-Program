#include "App.h"
#include "Mainframe.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	Mainframe* mainframe = new Mainframe("ATM");
	mainframe->SetMinClientSize(wxSize(900,700));
	mainframe->SetMaxClientSize(wxSize(900, 700));
	mainframe->SetClientSize(wxSize(900, 700));
	mainframe->Center();
	mainframe->Show();

	return true;
}
