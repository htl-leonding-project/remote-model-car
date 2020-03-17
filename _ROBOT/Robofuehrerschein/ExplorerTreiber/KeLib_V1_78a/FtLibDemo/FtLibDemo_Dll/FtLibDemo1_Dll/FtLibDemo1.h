// FtLibDemo1.h : Haupt-Header-Datei für die Anwendung FTLIBDEMO1
//

#if !defined(AFX_FTLIBDEMO1_H__D7EEB736_BDA7_47C9_84BA_1D39BCB0AD4B__INCLUDED_)
#define AFX_FTLIBDEMO1_H__D7EEB736_BDA7_47C9_84BA_1D39BCB0AD4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CFtLibDemo1App:
// Siehe FtLibDemo1.cpp für die Implementierung dieser Klasse
//

class CFtLibDemo1App : public CWinApp
{
public:
	CFtLibDemo1App();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CFtLibDemo1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CFtLibDemo1App)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_FTLIBDEMO1_H__D7EEB736_BDA7_47C9_84BA_1D39BCB0AD4B__INCLUDED_)
