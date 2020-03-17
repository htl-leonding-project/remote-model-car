// FtLibDemo1.cpp : Legt das Klassenverhalten für die Anwendung fest.
//

#include "stdafx.h"
#include "FtLibDemo1.h"
#include "FtLibDemo1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFtLibDemo1App

BEGIN_MESSAGE_MAP(CFtLibDemo1App, CWinApp)
	//{{AFX_MSG_MAP(CFtLibDemo1App)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFtLibDemo1App Konstruktion

CFtLibDemo1App::CFtLibDemo1App()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CFtLibDemo1App-Objekt

CFtLibDemo1App theApp;

/////////////////////////////////////////////////////////////////////////////
// CFtLibDemo1App Initialisierung

BOOL CFtLibDemo1App::InitInstance()
{
	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Größe Ihrer fertigen 
	//  ausführbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht benötigen, entfernen.

	CFtLibDemo1Dlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// ZU ERLEDIGEN: Fügen Sie hier Code ein, um ein Schließen des
		//  Dialogfelds über OK zu steuern
	}
	else if (nResponse == IDCANCEL)
	{
		// ZU ERLEDIGEN: Fügen Sie hier Code ein, um ein Schließen des
		//  Dialogfelds über "Abbrechen" zu steuern
	}

	// Da das Dialogfeld geschlossen wurde, FALSE zurückliefern, so dass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.
	return FALSE;
}
