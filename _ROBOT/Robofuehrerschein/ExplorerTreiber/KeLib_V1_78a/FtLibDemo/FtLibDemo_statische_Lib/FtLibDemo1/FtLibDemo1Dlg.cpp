/**********************************************************
 *(c) by Knobloch GmbH
 *       Weedgasse 14
 *       D-55234 Erbes-Büdesheim                                    
 *
 *  File:           FtLibDemo1Dlg.cpp : Sample for FtLib.DLL - File with MS-VC++ Ver. 6.0
 *										
 *    
 *  Start:          30.04.2005
 *  Last Change:    15.05.2006
 *                  05.05.2008
 *
 *
 *  Version:        1.82
 *  Date:           5. May 2008
 *
 *  Revision:
 *  0.60:   10. May 2006
 *        - New Name: GetAnzFtUsbDevice()    --> GetNumFtUsbDevice()
 *                    ClearFtMessagePuffer() --> ClearFtMessageBuffer()
 *  1.61:   15. May 2006
 *        - New Name: 01.61
 *  1.82:   05.05.2008
 *          Support for new Sensors: New: IF_DS_INPUT_ULTRASONIC
 ********************************************************************************/

#include "stdafx.h"
#include "FtLibDemo1.h"
#include "FtLibDemo1Dlg.h"

#include "FtLibDemo.h"
#include "FtLib\Inc\FtLib.h"                // FtLib Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct	Interface	sIF;	                // Struktur für Interface-Steuerung
static  char	FILENAME[] = "FtLibDemo1Dlg";	

/////////////////////////////////////////////////////////////////////////////
// CFtLibDemo1Dlg Dialogfeld

CFtLibDemo1Dlg::CFtLibDemo1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFtLibDemo1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFtLibDemo1Dlg)
	m_RAB_SS = -1;
	m_RAB_Com_Mode = -1;
	m_RAB_DsWert = -1;
	m_DS_Tol1 = _T("");
	m_DS_Tol2 = _T("");
	m_DS_Rep1 = _T("");
	m_DS_Rep2 = _T("");
	m_DS_Schwell1 = _T("");
	m_DS_Schwell2 = _T("");
	m_sTime = _T("");
	m_O01 = FALSE;
	m_O02 = FALSE;
	m_O03 = FALSE;
	m_O04 = FALSE;
	m_O05 = FALSE;
	m_O06 = FALSE;
	m_O07 = FALSE;
	m_O08 = FALSE;
	m_I01 = FALSE;
	m_I02 = FALSE;
	m_I03 = FALSE;
	m_I04 = FALSE;
	m_I05 = FALSE;
	m_I06 = FALSE;
	m_I07 = FALSE;
	m_I08 = FALSE;
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFtLibDemo1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFtLibDemo1Dlg)
	DDX_Control(pDX, IDC_LIST_USB, m_List_USB);
	DDX_Radio(pDX, IDC_RA_OFF, m_RAB_SS);
	DDX_Radio(pDX, IDC_RAB_IIF, m_RAB_Com_Mode);
	DDX_Radio(pDX, IDC_RAB_DS_VOLT, m_RAB_DsWert);
	DDX_Text(pDX, IDC_EDIT_DS_TOL1, m_DS_Tol1);
	DDX_Text(pDX, IDC_EDIT_DS_TOL2, m_DS_Tol2);
	DDX_Text(pDX, IDC_EDIT_DS_REP1, m_DS_Rep1);
	DDX_Text(pDX, IDC_EDIT_DS_REP2, m_DS_Rep2);
	DDX_Text(pDX, IDC_EDIT_DS_SCHWELLE1, m_DS_Schwell1);
	DDX_Text(pDX, IDC_EDIT_DS_SCHWELLE2, m_DS_Schwell2);
	DDX_Text(pDX, IDC_STATIC_Time, m_sTime);
	DDX_Check(pDX, IDC_O01, m_O01);
	DDX_Check(pDX, IDC_O02, m_O02);
	DDX_Check(pDX, IDC_O03, m_O03);
	DDX_Check(pDX, IDC_O04, m_O04);
	DDX_Check(pDX, IDC_O05, m_O05);
	DDX_Check(pDX, IDC_O06, m_O06);
	DDX_Check(pDX, IDC_O07, m_O07);
	DDX_Check(pDX, IDC_O08, m_O08);
	DDX_Check(pDX, IDC_I01, m_I01);
	DDX_Check(pDX, IDC_I02, m_I02);
	DDX_Check(pDX, IDC_I03, m_I03);
	DDX_Check(pDX, IDC_I04, m_I04);
	DDX_Check(pDX, IDC_I05, m_I05);
	DDX_Check(pDX, IDC_I06, m_I06);
	DDX_Check(pDX, IDC_I07, m_I07);
	DDX_Check(pDX, IDC_I08, m_I08);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFtLibDemo1Dlg, CDialog)
	//{{AFX_MSG_MAP(CFtLibDemo1Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_O01, OnO01)
	ON_BN_CLICKED(IDC_O02, OnO02)
	ON_BN_CLICKED(IDC_O03, OnO03)
	ON_BN_CLICKED(IDC_O04, OnO04)
	ON_BN_CLICKED(IDC_O05, OnO05)
	ON_BN_CLICKED(IDC_O06, OnO06)
	ON_BN_CLICKED(IDC_O07, OnO07)
	ON_BN_CLICKED(IDC_O08, OnO08)
	ON_BN_CLICKED(IDC_RA_USB, OnRaUsb)
	ON_BN_CLICKED(IDC_RA_SERC1, OnRaSerc1)
	ON_BN_CLICKED(IDC_RA_SERC2, OnRaSerc2)
	ON_BN_CLICKED(IDC_RA_SERC3, OnRaSerc3)
	ON_BN_CLICKED(IDC_RA_SERC4, OnRaSerc4)
	ON_BN_CLICKED(IDC_RA_OFF, OnRaOff)
	ON_BN_CLICKED(IDC_BUTTON_SCANUSB, OnButtonScanUsb)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)

	ON_BN_CLICKED(IDC_RAB_IIF, OnRabIif)
	ON_BN_CLICKED(IDC_RAB_IIF_EXTENSION, OnRabIifExtension)
	ON_BN_CLICKED(IDC_RAB_RIF, OnRabRif)

	ON_LBN_SELCHANGE(IDC_LIST_USB, OnSelchangeListUsb)


	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFtLibDemo1Dlg Nachrichten-Handler


// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CFtLibDemo1Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CFtLibDemo1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



/////////////////////////////////////////////////////////////////////////////
// CIf3_Diag_V1Dlg Nachrichten-Handler


/********************************************************
 *  Programm starten, INIT der Variablen
 *
 *
 *  Je nachdem ob entsprechende Konstanten definiert sind,
 *  schaltet die Initialisierung im Menü verschiedene
 *  Einträge aus (USB-Check, SN-setzen)
 *  um "Kundenspezifische" Versionen zu erhalten
 *
 *  Menü-Tipps im Buch: Visual C++ 6 /Leinecker, Archer) ab S. 107
 ********************************************************/
BOOL CFtLibDemo1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString	sText;						// für Textausgaben in ein Fenster
    DWORD   dwStatus;


	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	
	// Timer für Uhr starten
	SetTimer(ID_CLOCK_TIMER,1000,NULL);

	// Timer für Aktualisierung der Anzeige / des Interface (alle 100ms)
	SetTimer(ID_TICK_TIMER,100,NULL);


	// Softwareversion dieser (Diagnose) anzeigen
    sText.Format("FT Robo - Demo Software  Ver.:%d.%d", DSW_VER1, DSW_VER2);
    SetDlgItemText(IDC_STATIC_DIAG_VER, sText);

    GetDlgItem(IDC_RADIO_DS_DS)->ShowWindow(SW_SHOW);       // Distanzsensor: Auswahlbutton "Distanzsensor"
    GetDlgItem(IDC_RADIO_DS_VOLT)->ShowWindow(SW_SHOW);     // Distanzsensor: Auswahlbutton "Voltmesser"


	// Schnitstelle einstellen
	m_RAB_SS = RB_NIX;						// Mit "NIX" - Schnittstelle beginnen
    m_RAB_Com_Mode = RAB_ROBO_IF;           // "Robo-Interface" auswählen
    m_RAB_DsWert = RAB_DS_DISTANZ;


    sIF.dwIfTyp = NO_FT_DEVICE;             // Interface Typ ausgewählt
    sIF.dwPort = PORT_NONE;                 // kein Port ausgewählt
    sIF.dwComTyp = FT_ROBO_IF_COM;

    sIF.uiUsbDev = -1;		                // Nummer des ausgewählten USB-Device (0..Device), -1 = nix
    sIF.hFt = NULL;                         // Handle des aktiven Device (NULL = kein Device aktiv)
    sIF.pTransArea = NULL;                  // Zeiger auf Transfer Area


	// Variablen initialisieren
	sIF.bCTimeOut = 0;					// TimeOut löschen
	sIF.bOut0 = 0;						// Ausgänge setzen
	sIF.bIn0 = 0;						// Eingang
	sIF.uiA01 = 0;						// Analog 1
	sIF.uiA02 = 0;						// Analog 2
	sIF.uiA0X = 0;						// Analog EX
	sIF.uiA0Y = 0;						// Analog EY
	sIF.uiA0Z = 0;						// Analog Z (auf 26er Steckerleiste)
	sIF.uiD1 = 0;						// Analog Distanzsensor 1
	sIF.uiD2 = 0;						// Analog Distanzsensor 2
	sIF.uiVers = 0;						// Analog Versorgungsspannung
//	sIF.bUSBConnect = FALSE;			// 1=USB aktiv

	sIF.ulSerialNumber = 0;				// Seriennummer löschen
	sIF.ucSNok = FALSE;					// noch keine SN vorhanden


    sIF.dwDistanzMode = IF_DS_INPUT_ULTRASONIC; // Ultrasonic Distance Sensor (08.2007: New)
    sIF.dwDsTol1 = 20;                  // Toleranz 1
    sIF.dwDsTol2 = 20;                  // Toleranz 2
    sIF.dwDsRep1 = 3;                   // Repeatwert 1
    sIF.dwDsRep2 = 3;                   // Repeatwert 2
    sIF.dwDsSchwelle1 = 100;            // Schaltschwelle 1
    sIF.dwDsSchwelle2 = 100;            // Schaltschwelle 2


    m_DS_Tol1 = "20";
    m_DS_Tol2 = "20";
    m_DS_Rep1 = "3";
    m_DS_Rep2 = "3";
    m_DS_Schwell1 = "100";
    m_DS_Schwell2 = "100";



	// Fenster mit Werten vorbelegen

	sText.Format("%d", sIF.bOut0);			// Output Wert (dezimal) anzeigen
	SetDlgItemText(IDC_OWert, sText);
	sText.Format("%.2Xh", sIF.bOut0);		// Output Wert (hexadezimal) anzeigen
	SetDlgItemText(IDC_OWertHex, sText);

	sText.Format("%d", sIF.bIn0);			// Input Wert (dezimal) anzeigen
	SetDlgItemText(IDC_IWert, sText);
	sText.Format("%.2Xh", sIF.bIn0);			// Input Wert (hexadezimal) anzeigen
	SetDlgItemText(IDC_IWertHex, sText);



    dwStatus = GetLibVersion();             // FtUsbLib - Version anzeigen
	sText.Format("%d.%02d", (dwStatus>>8)&0xFF, dwStatus & 0xFF);    // Input Wert (dezimal) anzeigen
	SetDlgItemText(IDC_ST_LIB_VER, sText);


	// Scrollbars / Schieberegler einstellen
	SCROLLINFO* sLaufleistenInfo;			// Initialisierung der Schieber Out1 über Struct
	sLaufleistenInfo=new SCROLLINFO;
	sLaufleistenInfo->fMask = SIF_ALL;		// alles erlaubt
	sLaufleistenInfo->nMin = SB_VMIN;		// Min-Wert
	sLaufleistenInfo->nMax = SB_VMAX;		// Max-Wert
	sLaufleistenInfo->nPos = SB_VINIT;		// Start-Position
	sLaufleistenInfo->nPage = SB_PAGE;		// Größe des Schiebers


	CScrollBar* pSB_O01 = (CScrollBar*) GetDlgItem(IDC_SB_O01);				// Out 1 Schieber
	pSB_O01->SetScrollInfo(sLaufleistenInfo);								// Zugriff über Temp.Zeiger
	sIF.baOut0VS[1] = abs((sLaufleistenInfo->nPos) - ((SB_VMAX - SB_VMIN)+1));	// Geschwindigkeit setzen
    sText.Format("%d", sIF.baOut0VS[1]);										// Wert in Fenster schreiben
    SetDlgItemText(IDC_SB_O01Wert, sText);

	CScrollBar* pSB_O02 = (CScrollBar*) GetDlgItem(IDC_SB_O02);				// Out 2 Schieber
	pSB_O02->SetScrollInfo(sLaufleistenInfo);								// Zugriff über Temp.Zeiger
	sIF.baOut0VS[2] = abs((sLaufleistenInfo->nPos) - ((SB_VMAX - SB_VMIN)+1));	// Geschwindigkeit setzen
    sText.Format("%d", sIF.baOut0VS[2]);										// Wert in Fenster schreiben
    SetDlgItemText(IDC_SB_O02Wert, sText);
	
	CScrollBar* pSB_O03 = (CScrollBar*) GetDlgItem(IDC_SB_O03);				// Out 3 Schieber
	pSB_O03->SetScrollInfo(sLaufleistenInfo);								// Zugriff über Temp.Zeiger
	sIF.baOut0VS[3] = abs((sLaufleistenInfo->nPos) - ((SB_VMAX - SB_VMIN)+1));	// Geschwindigkeit setzen
    sText.Format("%d", sIF.baOut0VS[3]);										// Wert in Fenster schreiben
    SetDlgItemText(IDC_SB_O03Wert, sText);
	
	CScrollBar* pSB_O04 = (CScrollBar*) GetDlgItem(IDC_SB_O04);				// Out 4 Schieber
	pSB_O04->SetScrollInfo(sLaufleistenInfo);								// Zugriff über Temp.Zeiger
	sIF.baOut0VS[4] = abs((sLaufleistenInfo->nPos) - ((SB_VMAX - SB_VMIN)+1));	// Geschwindigkeit setzen
    sText.Format("%d", sIF.baOut0VS[4]);										// Wert in Fenster schreiben
    SetDlgItemText(IDC_SB_O04Wert, sText);

	CScrollBar* pSB_O05 = (CScrollBar*) GetDlgItem(IDC_SB_O05);				// Out 5 Schieber
	pSB_O05->SetScrollInfo(sLaufleistenInfo);								// Zugriff über Temp.Zeiger
	sIF.baOut0VS[5] = abs((sLaufleistenInfo->nPos) - ((SB_VMAX - SB_VMIN)+1));	// Geschwindigkeit setzen
    sText.Format("%d", sIF.baOut0VS[5]);										// Wert in Fenster schreiben
    SetDlgItemText(IDC_SB_O05Wert, sText);

	CScrollBar* pSB_O06 = (CScrollBar*) GetDlgItem(IDC_SB_O06);				// Out 6 Schieber
	pSB_O06->SetScrollInfo(sLaufleistenInfo);								// Zugriff über Temp.Zeiger
	sIF.baOut0VS[6] = abs((sLaufleistenInfo->nPos) - ((SB_VMAX - SB_VMIN)+1));	// Geschwindigkeit setzen
    sText.Format("%d", sIF.baOut0VS[6]);										// Wert in Fenster schreiben
    SetDlgItemText(IDC_SB_O06Wert, sText);

	CScrollBar* pSB_O07 = (CScrollBar*) GetDlgItem(IDC_SB_O07);				// Out 7 Schieber
	pSB_O07->SetScrollInfo(sLaufleistenInfo);								// Zugriff über Temp.Zeiger
	sIF.baOut0VS[7] = abs((sLaufleistenInfo->nPos) - ((SB_VMAX - SB_VMIN)+1));	// Geschwindigkeit setzen
    sText.Format("%d", sIF.baOut0VS[7]);										// Wert in Fenster schreiben
    SetDlgItemText(IDC_SB_O07Wert, sText);
	
	CScrollBar* pSB_O08 = (CScrollBar*) GetDlgItem(IDC_SB_O08);				// Out 8 Schieber
	pSB_O08->SetScrollInfo(sLaufleistenInfo);								// Zugriff über Temp.Zeiger
	sIF.baOut0VS[8] = abs((sLaufleistenInfo->nPos) - ((SB_VMAX - SB_VMIN)+1));	// Geschwindigkeit setzen
    sText.Format("%d", sIF.baOut0VS[8]);										// Wert in Fenster schreiben
    SetDlgItemText(IDC_SB_O08Wert, sText);

	delete sLaufleistenInfo;

	CSliderCtrl* pSC_A01 = (CSliderCtrl*) GetDlgItem(IDC_SL_A01);			// Analog 1 Schieber
	pSC_A01->SetRange(0,MAX_ANALOGWERT);									// Min / Max festlegen
	pSC_A01->SetTic(20);													// Anzahl Rastmarken festlegen
	pSC_A01->SetTicFreq(128);												// Rastmarken Periode
	pSC_A01->SetPos(abs(sIF.uiA01-MAX_ANALOGWERT));							// aktuellen Position
	pSC_A01->SetLineSize(1);												// 
	pSC_A01->EnableWindow(FALSE);											// Slider deaktivieren (keine Reaktion auf Maus)
    sText.Format("%d", sIF.uiA01); 											// Wert in Fenster schreiben
    SetDlgItemText(IDC_SL_A01Wert, sText);

	CSliderCtrl* pSC_A02 = (CSliderCtrl*) GetDlgItem(IDC_SL_A02);			// Analog 2 Schieber
	pSC_A02->SetRange(0,MAX_ANALOGWERT);									// Min / Max festlegen
	pSC_A02->SetTic(20);													// Anzahl Rastmarken festlegen
	pSC_A02->SetTicFreq(128);												// Rastmarken Periode
	pSC_A02->SetPos(abs(sIF.uiA02-MAX_ANALOGWERT));							// aktuellen Position
	pSC_A02->SetLineSize(1);												// 
	pSC_A02->EnableWindow(FALSE);											// Slider deaktivieren (keine Reaktion auf Maus)
    sText.Format("%d", sIF.uiA02); 											// Wert in Fenster schreiben
    SetDlgItemText(IDC_SL_A02Wert, sText);
	
	CSliderCtrl* pSC_A0X = (CSliderCtrl*) GetDlgItem(IDC_SL_A0X);			// Analog X Schieber
	pSC_A0X->SetRange(0,MAX_ANALOGWERT);									// Min / Max festlegen
	pSC_A0X->SetTic(20);													// Anzahl Rastmarken festlegen
	pSC_A0X->SetTicFreq(128);												// Rastmarken Periode
	pSC_A0X->SetPos(abs(sIF.uiA0X-MAX_ANALOGWERT));							// aktuellen Position
	pSC_A0X->SetLineSize(1);												// 
	pSC_A0X->EnableWindow(FALSE);											// Slider deaktivieren (keine Reaktion auf Maus)
    sText.Format("%d", sIF.uiA0X); 											// Wert in Fenster schreiben
    SetDlgItemText(IDC_SL_A0XWert, sText);

	CSliderCtrl* pSC_A0Y = (CSliderCtrl*) GetDlgItem(IDC_SL_A0Y);			// Analog Y Schieber
	pSC_A0Y->SetRange(0,MAX_ANALOGWERT);									// Min / Max festlegen
	pSC_A0Y->SetTic(20);													// Anzahl Rastmarken festlegen
	pSC_A0Y->SetTicFreq(128);												// Rastmarken Periode
	pSC_A0Y->SetPos(abs(sIF.uiA0Y-MAX_ANALOGWERT));							// aktuellen Position
	pSC_A0Y->SetLineSize(1);												// 
	pSC_A0Y->EnableWindow(FALSE);											// Slider deaktivieren (keine Reaktion auf Maus)
    sText.Format("%d", sIF.uiA0Y); 											// Wert in Fenster schreiben
    SetDlgItemText(IDC_SL_A0YWert, sText);
	
	CSliderCtrl* pSC_A0Z = (CSliderCtrl*) GetDlgItem(IDC_SL_A0Z);			// Analog Z Schieber
	pSC_A0Z->SetRange(0,MAX_ANALOGWERT);									// Min / Max festlegen
	pSC_A0Z->SetTic(20);													// Anzahl Rastmarken festlegen
	pSC_A0Z->SetTicFreq(128);												// Rastmarken Periode
	pSC_A0Z->SetPos(abs(sIF.uiA0Z-MAX_ANALOGWERT));							// aktuellen Position
	pSC_A0Z->SetLineSize(1);												// 
	pSC_A0Z->EnableWindow(FALSE);											// Slider deaktivieren (keine Reaktion auf Maus)
    sText.Format("%d", sIF.uiA0Z); 											// Wert in Fenster schreiben
    SetDlgItemText(IDC_SL_A0ZWert, sText);
	
	CSliderCtrl* pSC_DS1 = (CSliderCtrl*) GetDlgItem(IDC_SL_DS1);			// Analog DS1 Schieber (Distanzsensor)
	pSC_DS1->SetRange(0,MAX_ANALOGWERT);									// Min / Max festlegen
	pSC_DS1->SetTic(20);													// Anzahl Rastmarken festlegen
	pSC_DS1->SetTicFreq(128);												// Rastmarken Periode
	pSC_DS1->SetPos(abs(sIF.uiD1-MAX_ANALOGWERT));							// aktuellen Position
	pSC_DS1->SetLineSize(1);												// 
	pSC_DS1->EnableWindow(FALSE);											// Slider deaktivieren (keine Reaktion auf Maus)
    sText.Format("%d", sIF.uiD1); 											// Wert in Fenster schreiben
    SetDlgItemText(IDC_SL_DS1Wert, sText);
	
	CSliderCtrl* pSC_DS2 = (CSliderCtrl*) GetDlgItem(IDC_SL_DS2);			// Analog DS2 Schieber (Distanzsensor)
	pSC_DS2->SetRange(0,MAX_ANALOGWERT);									// Min / Max festlegen
	pSC_DS2->SetTic(20);													// Anzahl Rastmarken festlegen
	pSC_DS2->SetTicFreq(128);												// Rastmarken Periode
	pSC_DS2->SetPos(abs(sIF.uiD2-MAX_ANALOGWERT));							// aktuellen Position
	pSC_DS2->SetLineSize(1);												// 
	pSC_DS2->EnableWindow(FALSE);											// Slider deaktivieren (keine Reaktion auf Maus)
    sText.Format("%d", sIF.uiD2); 											// Wert in Fenster schreiben
    SetDlgItemText(IDC_SL_DS2Wert, sText);
	
	CSliderCtrl* pSC_VERS = (CSliderCtrl*) GetDlgItem(IDC_SL_Vers);			// Analog Versorgungsspannung Schieber
	pSC_VERS->SetRange(0,MAX_ANALOGWERT);									// Min / Max festlegen
	pSC_VERS->SetTic(20);													// Anzahl Rastmarken festlegen
	pSC_VERS->SetTicFreq(128);												// Rastmarken Periode
	pSC_VERS->SetPos(abs(sIF.uiVers-MAX_ANALOGWERT));						// aktuellen Position
	pSC_VERS->SetLineSize(1);												// 
	pSC_VERS->EnableWindow(FALSE);											// Slider deaktivieren (keine Reaktion auf Maus)
    sText.Format("%d V", sIF.uiVers); 										// Wert in Fenster schreiben
    SetDlgItemText(IDC_SL_VersWert, sText);

	BerechnePWM();			            // Geschwindigkeitsvariablen (3 Byte pro Interface) einstellen

	UpdateData(FALSE);					// Werte setzen (zurückschreiben)


    GetDlgItem(IDC_RA_USB)->EnableWindow(FALSE);        // deaktiviert USB-Button aus

    dwStatus = InitFtLib();

    if (dwStatus == FTLIB_ERR_USB_NOT_SUPPORTET_FROM_OS)
    {                                                           // USB-Fehler, dann kein USB "anbieten"
        GetDlgItem(IDC_LIST_USB)->ShowWindow(SW_HIDE);          // "USB-Listenfenster" verstecken
        GetDlgItem(IDC_BUTTON_SCANUSB)->ShowWindow(SW_HIDE);    // Button "Scan USB" verstecken
        GetDlgItem(IDC_RA_USB)->EnableWindow(FALSE);            // schaltet USB-Button ab

        SetDlgItemText(IDC_STATIC_USB_DEV, "Sorry, Your Operating System doesn´t support USB");
        GetDlgItem(IDC_STATIC_USB_DEV)->EnableWindow(FALSE);
    }
    else
    {
        if (dwStatus != FTLIB_ERR_SUCCESS)
        {
            sText.Format("FEHLER bei InitFtLib(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		    MessageBox(sText, MB_OK);
        }
    }

	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}




/********************************************************
 * Programm beenden
 ********************************************************/
void CFtLibDemo1Dlg::OnButtonExit() 
{
    DWORD       dwStatus;
    CString     sText;

    KillTimer(ID_CLOCK_TIMER);  // Timer abschalten
    KillTimer(ID_TICK_TIMER);

    if (IsFtLibInit() == FTLIB_ERR_LIB_IS_INITIALIZED)  // Nur wenn USB-Bereich verfügbar ist
    {                                                   // wird er gelöscht
        dwStatus = CloseFtLib();                        // FT-Bibliothek wieder entfernen
        if (dwStatus != FTLIB_ERR_SUCCESS)
        {                                   // Fehler bei CloseFtLib()
            sText.Format("FEHLER bei CloseFtLib(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		    MessageBox(sText, MB_OK);
        }
    }


	CDialog::OnOK();
}



/********************************************************
 *	Diese Prozedur erzeugt die drei Bytes pro Modul mit den 
 *  Geschwindigkeitsbits (PWM-Wert) für die acht Ausgänge.
 ********************************************************/
void BerechnePWM()
{
    union {                                 // Union um die Geschwindigkeitsbits über L/H oder als DWORD anzusprechen    
        struct {
            UCHAR   ucB0;                   // Byte 0
            UCHAR   ucB1;                   // Byte 1
            UCHAR   ucB2;                   // Byte 2
            UCHAR   ucB3;                   // Byte 3
        } byte;
        ULONG   ulB;                        
    }og;                                    // Output Geschwindigkeit
	
	og.ulB = (sIF.baOut0VS[1]-1) & 0x07;					// Ausgang 1 einstellen
	og.ulB = og.ulB | (((sIF.baOut0VS[2]-1) & 0x07) << 3);	// Ausgang 2 einblenden
	og.ulB = og.ulB | (((sIF.baOut0VS[3]-1) & 0x07) << 6);	// Ausgang 3 einblenden
	og.ulB = og.ulB | (((sIF.baOut0VS[4]-1) & 0x07) << 9);	// Ausgang 4 einblenden
	og.ulB = og.ulB | (((sIF.baOut0VS[5]-1) & 0x07) << 12);	// Ausgang 5 einblenden
	og.ulB = og.ulB | (((sIF.baOut0VS[6]-1) & 0x07) << 15);	// Ausgang 6 einblenden
	og.ulB = og.ulB | (((sIF.baOut0VS[7]-1) & 0x07) << 18);	// Ausgang 7 einblenden
	og.ulB = og.ulB | (((sIF.baOut0VS[8]-1) & 0x07) << 21);	// Ausgang 8 einblenden
	sIF.baOut0V[0] = og.byte.ucB0;							// Byte 0 kopieren
	sIF.baOut0V[1] = og.byte.ucB1;							// Byte 1 kopieren
	sIF.baOut0V[2] = og.byte.ucB2;							// Byte 2 kopieren
}




/********************************************************
 *	Diese Timer-Routine wird alle 100ms und alle 1s aufgerufen.
 *	Alle 1s wird die Uhrzeit im Fenster aktualisiert
 *
 *	Alle 100ms werden die Analogen Scroll-Bars aktualisiert und das Interface abgefragt
 *	Hinweis: 
 *	  -	Da die Schieber in Windows "oben" = 0 haben und unten ihr Maximum wird der
 *		Zahlenwert entsprechend umgerechnet. Wenn der Analogwert 0 hat, wird an den 
 *		Schieber ein 1023 gesendet um diesen an den unteren Rand zu bewegen!
 *	  -	Der Timer in Windows erzeugt eine normale "Nachricht", es wird somit keine
 *		andere Routine in Abarbeitung gerade unterbrochen.
 ********************************************************/
void CFtLibDemo1Dlg::OnTimer(UINT nIDEvent) 
{
    DWORD   dwStatus;
	CString	text;
	double	rdWert = 0;
	
	CDialog::OnTimer(nIDEvent);

	// Aktuelle Zeit holen
	CTime curTime = CTime::GetCurrentTime();
	UpdateData(TRUE);				// Werte einlesen
    dwStatus = 0;
	
	switch (nIDEvent)				// Welcher Timer hat das Ereignis ausgelöst ?
	{
	    case ID_CLOCK_TIMER:			// aktuelle Zeit anzeigen
		    m_sTime.Format("%d:%.2d:%.2d", curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond());
		    break;


        case ID_TICK_TIMER:				// Anzeige alle 100ms aktualisieren und Interface abfragen
            if (IsFtTransferActiv(sIF.hFt) == FTLIB_ERR_THREAD_IS_RUNNING)
            {
                if (sIF.pTransArea != NULL)
                {
                    if (sIF.bExtTestIsRunning == FALSE) 
                    {
                        if (m_O01)
		                    sIF.bOut0 = sIF.bOut0 | 0x01;
	                    else
		                    sIF.bOut0 = sIF.bOut0 & (~0x01);


	                    if (m_O02)
		                    sIF.bOut0 = sIF.bOut0 | 0x02;
	                    else
		                    sIF.bOut0 = sIF.bOut0 & (~0x02);


                        if (m_O03)
		                    sIF.bOut0 = sIF.bOut0 | 0x04;
	                    else
		                    sIF.bOut0 = sIF.bOut0 & (~0x04);


                        if (m_O04)
		                    sIF.bOut0 = sIF.bOut0 | 0x08;
	                    else
		                    sIF.bOut0 = sIF.bOut0 & (~0x08);


                        if (m_O05)
		                    sIF.bOut0 = sIF.bOut0 | 0x10;
	                    else
		                    sIF.bOut0 = sIF.bOut0 & (~0x10);


                        if (m_O06)
		                    sIF.bOut0 = sIF.bOut0 | 0x20;
	                    else
		                    sIF.bOut0 = sIF.bOut0 & (~0x20);


                        if (m_O07)
		                    sIF.bOut0 = sIF.bOut0 | 0x40;
	                    else
		                    sIF.bOut0 = sIF.bOut0 & (~0x40);

	                    if (m_O08)
		                    sIF.bOut0 = sIF.bOut0 | 0x80;
	                    else
		                    sIF.bOut0 = sIF.bOut0 & (~0x80);

	                    text.Format("%d", sIF.bOut0);
	                    SetDlgItemText(IDC_OWert, text);

	                    text.Format("%.2Xh", sIF.bOut0);
	                    SetDlgItemText(IDC_OWertHex, text);


			            sIF.pTransArea->M_Main= sIF.bOut0;			// 2. Byte Master Ausgänge
			            sIF.pTransArea->MPWM_Main[0] = sIF.baOut0VS[1]-1;   // Geschwindigkeit Ausgang 1 
			            sIF.pTransArea->MPWM_Main[1] = sIF.baOut0VS[2]-1;   // Geschwindigkeit Ausgang 2 
			            sIF.pTransArea->MPWM_Main[2] = sIF.baOut0VS[3]-1;   // Geschwindigkeit Ausgang 3 
			            sIF.pTransArea->MPWM_Main[3] = sIF.baOut0VS[4]-1;   // Geschwindigkeit Ausgang 4 
			            sIF.pTransArea->MPWM_Main[4] = sIF.baOut0VS[5]-1;   // Geschwindigkeit Ausgang 5 
			            sIF.pTransArea->MPWM_Main[5] = sIF.baOut0VS[6]-1;   // Geschwindigkeit Ausgang 6 
			            sIF.pTransArea->MPWM_Main[6] = sIF.baOut0VS[7]-1;   // Geschwindigkeit Ausgang 7 
			            sIF.pTransArea->MPWM_Main[7] = sIF.baOut0VS[8]-1;   // Geschwindigkeit Ausgang 8 

                        sIF.bIn0 = sIF.pTransArea->E_Main;          // Eingänge Master zuordnen
					    sIF.uiA0X = sIF.pTransArea->AX;	            // Analog AX zuordnen
					    sIF.uiA0Y = sIF.pTransArea->AY;	            // Analog AY zuordnen
					    sIF.uiA01 = sIF.pTransArea->A1;	            // Analog A1 zuordnen
					    sIF.uiA02 = sIF.pTransArea->A2;	            // Analog A2 zuordnen

					    sIF.uiA0Z = sIF.pTransArea->AZ;	            // Analog AZ zuordnen
					    sIF.uiD1 = sIF.pTransArea->D1;             // Analog DS1 zuordnen (DS1 ist Schwellwert für 0/1 Erkennung)
					    sIF.uiD2 = sIF.pTransArea->D2;             // Analog DS2 zuordnen 
					    sIF.uiVers= sIF.pTransArea->AV;             // Analog Versorgung zuordnen



    //					        sIF.ucIRCodeH = (((sIF.pTransArea->IRKeys & 0xF0) >> 4) & 0x01);    // IR-Code "H" einblenden, AS-Bits ausblenden
    //					        sIF.ucIRCodeL = sIF.pTransArea->IRKeys & 0x0F;					    // IR-Code "L" einblenden


                        // Testweise durch Addition der Arrays überprüfen, daß immer nur eine Taste gedrückt ist
                        DWORD   dwX;
                        DWORD   dwAnzCode;
                        DWORD   dwAnzKey;

                        dwAnzCode = 0;
                        dwAnzKey = 0;
                        for (dwX = 0; dwX < 11; dwX++)
                        {              
                            if (sIF.pTransArea->IRKeys16[dwX] == 1)
                            {                                               // Taste gedrückt
                                dwAnzKey = dwAnzKey + dwX+1;
                            }

                            if (sIF.pTransArea->IRKeys16Code1[dwX] == 1)
                            {                                               // Taste Code 1 gedrückt
                                dwAnzCode = dwAnzCode + 1;
                            }

                            if (sIF.pTransArea->IRKeys16Code2[dwX] == 1)
                            {                                               // Taste Code 2 gedrückt
                                dwAnzCode = dwAnzCode + 2;
                            }
                        }

		                if (sIF.bIn0 & 0x01)											// I1 gesetzt ?
			                m_I01 = TRUE;
		                else
			                m_I01 = FALSE;
		                
		                if (sIF.bIn0 & 0x02)											// I1 gesetzt ?
			                m_I02 = TRUE;
		                else
			                m_I02 = FALSE;
		                
		                if (sIF.bIn0 & 0x04)											// I3 gesetzt ?
			                m_I03 = TRUE;
		                else
			                m_I03 = FALSE;
		                
		                if (sIF.bIn0 & 0x08)											// I4 gesetzt ?
			                m_I04 = TRUE;
		                else
			                m_I04 = FALSE;
		                
		                if (sIF.bIn0 & 0x10)											// I5 gesetzt ?
			                m_I05 = TRUE;
		                else
			                m_I05 = FALSE;
		                
		                if (sIF.bIn0 & 0x20)											// I6 gesetzt ?
			                m_I06 = TRUE;
		                else
			                m_I06 = FALSE;
		                
		                if (sIF.bIn0 & 0x40)											// I7 gesetzt ?
			                m_I07 = TRUE;
		                else
			                m_I07 = FALSE;
		                
		                if (sIF.bIn0 & 0x80)											// I8 gesetzt ?
			                m_I08 = TRUE;
		                else
			                m_I08 = FALSE;
		                
		                
		                text.Format("%d", sIF.bIn0);									// Input Wert (dezimal) anzeigen
		                SetDlgItemText(IDC_IWert, text);
		                text.Format("%.2Xh", sIF.bIn0);									// Input Wert (hexadezimal) anzeigen
		                SetDlgItemText(IDC_IWertHex, text);

		                CSliderCtrl* pSC_A01 = (CSliderCtrl*) GetDlgItem(IDC_SL_A01);	// Slider A01 
		                pSC_A01->SetPos(abs(sIF.uiA01 - MAX_ANALOGWERT));				// Schieber oben=0, unten=MAX, daher "umdrehen"
		                text.Format("%4d", sIF.uiA01);									// und anzeigen
		                SetDlgItemText(IDC_SL_A01Wert, text);

		                rdWert = sIF.uiA01;												// in Volt umrechnen1
		                rdWert = rdWert / 100;											// in Volt umrechnen1
		                text.Format("%2.2f V", rdWert);									// und anzeigen ("V" angehängt)
		                SetDlgItemText(IDC_SL_A01Volt, text);


		                CSliderCtrl* pSC_A02 = (CSliderCtrl*) GetDlgItem(IDC_SL_A02);	// Slider A02 
		                pSC_A02->SetPos(abs(sIF.uiA02 - MAX_ANALOGWERT));				// Schieber oben=0, unten=MAX, daher "umdrehen"
		                text.Format("%4d", sIF.uiA02);									// und anzeigen
		                SetDlgItemText(IDC_SL_A02Wert, text);

		                rdWert = sIF.uiA02;												// in Volt umrechnen1
		                rdWert = rdWert / 100;											// in Volt umrechnen1
		                text.Format("%2.2f V", rdWert);									// und anzeigen ("V" angehängt)
		                SetDlgItemText(IDC_SL_A02Volt, text);


		                CSliderCtrl* pSC_A0X = (CSliderCtrl*) GetDlgItem(IDC_SL_A0X);	// Slider A0X
		                pSC_A0X->SetPos(abs(sIF.uiA0X - MAX_ANALOGWERT));				// Schieber oben=0, unten=MAX, daher "umdrehen"
		                text.Format("%4d", sIF.uiA0X);									// und anzeigen
		                SetDlgItemText(IDC_SL_A0XWert, text);

		                CSliderCtrl* pSC_A0Y = (CSliderCtrl*) GetDlgItem(IDC_SL_A0Y);	// Slider A0Y
		                pSC_A0Y->SetPos(abs(sIF.uiA0Y - MAX_ANALOGWERT));				// Schieber oben=0, unten=MAX, daher "umdrehen"
		                text.Format("%4d", sIF.uiA0Y);									// und anzeigen
		                SetDlgItemText(IDC_SL_A0YWert, text);

		                CSliderCtrl* pSC_A0Z = (CSliderCtrl*) GetDlgItem(IDC_SL_A0Z);	// Slider A0Z
		                pSC_A0Z->SetPos(abs(sIF.uiA0Z - MAX_ANALOGWERT));				// Schieber oben=0, unten=MAX, daher "umdrehen"
		                text.Format("%4d", sIF.uiA0Z);									// und anzeigen
		                SetDlgItemText(IDC_SL_A0ZWert, text);

		                rdWert = sIF.uiA0Z;												// in Volt umrechnen1
		                rdWert = rdWert / 100;											// in Volt umrechnen1
		                text.Format("%2.2f V", rdWert);									// und anzeigen ("V" angehängt)
		                SetDlgItemText(IDC_SL_A0ZVolt, text);


		                CSliderCtrl* pSC_DS1 = (CSliderCtrl*) GetDlgItem(IDC_SL_DS1);	// Slider DS1
		                pSC_DS1->SetPos(abs(sIF.uiD1 - MAX_ANALOGWERT));				// Schieber oben=0, unten=MAX, daher "umdrehen"
		                text.Format("%4d", sIF.uiD1);									// und anzeigen
		                SetDlgItemText(IDC_SL_DS1Wert, text);

		                CSliderCtrl* pSC_DS2 = (CSliderCtrl*) GetDlgItem(IDC_SL_DS2);	// Slider DS2
		                pSC_DS2->SetPos(abs(sIF.uiD2 - MAX_ANALOGWERT));				// Schieber oben=0, unten=MAX, daher "umdrehen"
		                text.Format("%4d", sIF.uiD2);									// und anzeigen
		                SetDlgItemText(IDC_SL_DS2Wert, text);

		                CSliderCtrl* pSC_VERS = (CSliderCtrl*) GetDlgItem(IDC_SL_Vers);	// Slider Versorgungsspannung
		                pSC_VERS->SetPos(abs(sIF.uiVers - MAX_ANALOGWERT));				// Schieber oben=0, unten=MAX, daher "umdrehen"
		                text.Format("%4d", sIF.uiVers);							        // und anzeigen 
		                SetDlgItemText(IDC_SL_VersWert, text);
		                rdWert = sIF.uiVers * 0.01;									    // in Volt umrechnen1
		                text.Format("%2.2f Volt", rdWert);								// und anzeigen ("V" angehängt)
		                SetDlgItemText(IDC_SL_VersVolt, text);

                    }
                    dwStatus = 1;   // also "Online", auch wenn Zugriff z.Zt. durch Extension-Test
                }       // Zeiger auf TransferArea hat unerlaubte Adresse
            }


            if (dwStatus == 1)
            {                                                               // Interface ist ONLINE (Transfer läuft)
			    text.Format("%s", "IF ist ONLINE");							// Wert in Fenster schreiben
			    SetDlgItemText(IDC_Online, text);
            }
            else
            {																// Interface ist OFFLINE
	            text.Format("%s", "** OFFLINE ** ");						// Wert in Fenster schreiben
	            SetDlgItemText(IDC_Online, text);
	            sIF.bOut0 = 0;												// Ausgänge setzen
	            sIF.bIn0 = 0;												// Eingang
	            sIF.uiA01 = 0;												// Analog 1
	            sIF.uiA02 = 0;												// Analog 2
	            sIF.uiA0X = 0;												// Analog EX
	            sIF.uiA0Y = 0;												// Analog EY
	            sIF.uiA0Z = 0;												// Analog Z (auf 26er Steckerleiste)
	            sIF.uiD1 = 0;												// Analog Distanzsensor 1
	            sIF.uiD2 = 0;												// Analog Distanzsensor 2
	            sIF.uiVers = 0;												// Analog Versorgungsspannung
            } 
		    break;

        default:
            break;

	}
	// Dialogfeld aktualisieren
	UpdateData(FALSE);
}



// --------------------------------------------------------
//	Einer der Ausgänge wurde angeklickt
//
// --------------------------------------------------------
void CFtLibDemo1Dlg::OnO01() 
{
	CString	text;

	UpdateData(TRUE);					// Zustand einlesen
	if (m_O01)
		sIF.bOut0 = sIF.bOut0 | 0x01;
	else
		sIF.bOut0 = sIF.bOut0 & (~0x01);

	text.Format("%d", sIF.bOut0);
	SetDlgItemText(IDC_OWert, text);

	text.Format("%.2Xh", sIF.bOut0);
	SetDlgItemText(IDC_OWertHex, text);
	
}



void CFtLibDemo1Dlg::OnO02() 
{
	CString	text;

	UpdateData(TRUE);					// Zustand einlesen
	if (m_O02)
		sIF.bOut0 = sIF.bOut0 | 0x02;
	else
		sIF.bOut0 = sIF.bOut0 & (~0x02);

	text.Format("%d", sIF.bOut0);
	SetDlgItemText(IDC_OWert, text);

	text.Format("%.2Xh", sIF.bOut0);
	SetDlgItemText(IDC_OWertHex, text);
}

void CFtLibDemo1Dlg::OnO03() 
{
	CString	text;

	UpdateData(TRUE);					// Zustand einlesen
	if (m_O03)
		sIF.bOut0 = sIF.bOut0 | 0x04;
	else
		sIF.bOut0 = sIF.bOut0 & (~0x04);

	text.Format("%d", sIF.bOut0);
	SetDlgItemText(IDC_OWert, text);

	text.Format("%.2Xh", sIF.bOut0);
	SetDlgItemText(IDC_OWertHex, text);
}

void CFtLibDemo1Dlg::OnO04() 
{
	CString	text;

	UpdateData(TRUE);					// Zustand einlesen
	if (m_O04)
		sIF.bOut0 = sIF.bOut0 | 0x08;
	else
		sIF.bOut0 = sIF.bOut0 & (~0x08);

	text.Format("%d", sIF.bOut0);
	SetDlgItemText(IDC_OWert, text);

	text.Format("%.2Xh", sIF.bOut0);
	SetDlgItemText(IDC_OWertHex, text);
}

void CFtLibDemo1Dlg::OnO05() 
{
	CString	text;

	UpdateData(TRUE);					// Zustand einlesen
	if (m_O05)
		sIF.bOut0 = sIF.bOut0 | 0x10;
	else
		sIF.bOut0 = sIF.bOut0 & (~0x10);

	text.Format("%d", sIF.bOut0);
	SetDlgItemText(IDC_OWert, text);

	text.Format("%.2Xh", sIF.bOut0);
	SetDlgItemText(IDC_OWertHex, text);
}

void CFtLibDemo1Dlg::OnO06() 
{
	CString	text;

	UpdateData(TRUE);					// Zustand einlesen
	if (m_O06)
		sIF.bOut0 = sIF.bOut0 | 0x20;
	else
		sIF.bOut0 = sIF.bOut0 & (~0x20);

	text.Format("%d", sIF.bOut0);
	SetDlgItemText(IDC_OWert, text);

	text.Format("%.2Xh", sIF.bOut0);
	SetDlgItemText(IDC_OWertHex, text);
}

void CFtLibDemo1Dlg::OnO07() 
{
	CString	text;

	UpdateData(TRUE);					// Zustand einlesen
	if (m_O07)
		sIF.bOut0 = sIF.bOut0 | 0x40;
	else
		sIF.bOut0 = sIF.bOut0 & (~0x40);

	text.Format("%d", sIF.bOut0);
	SetDlgItemText(IDC_OWert, text);

	text.Format("%.2Xh", sIF.bOut0);
	SetDlgItemText(IDC_OWertHex, text);
}

void CFtLibDemo1Dlg::OnO08() 
{
	CString	text;

	UpdateData(TRUE);					// Zustand einlesen
	if (m_O08)
		sIF.bOut0 = sIF.bOut0 | 0x80;
	else
		sIF.bOut0 = sIF.bOut0 & (~0x80);

	text.Format("%d", sIF.bOut0);
	SetDlgItemText(IDC_OWert, text);

	text.Format("%.2Xh", sIF.bOut0);
	SetDlgItemText(IDC_OWertHex, text);
}





/********************************************************
 *  UpdateAgData()
 *
 *  Diese Routine überträgt die Bildschirmeinstallungen
 *  auf die in der Struktur gespeicherten Variablen
 *
 *  Diese Routine hat kein dazugehörendes Steuerelement 
 *  sondern wurde in der Headerdatei als Klassenelement 
 *  aufgenommen wie ClearVariablenUndAnzeige()
 ********************************************************/
void CFtLibDemo1Dlg::UpdateAgData() 
{
	CString	text;

	UpdateData(TRUE);					// Zustand einlesen

    if (m_O01)
		sIF.bOut0 = sIF.bOut0 | 0x01;
	else
		sIF.bOut0 = sIF.bOut0 & (~0x01);


	if (m_O02)
		sIF.bOut0 = sIF.bOut0 | 0x02;
	else
		sIF.bOut0 = sIF.bOut0 & (~0x02);


    if (m_O03)
		sIF.bOut0 = sIF.bOut0 | 0x04;
	else
		sIF.bOut0 = sIF.bOut0 & (~0x04);


    if (m_O04)
		sIF.bOut0 = sIF.bOut0 | 0x08;
	else
		sIF.bOut0 = sIF.bOut0 & (~0x08);


    if (m_O05)
		sIF.bOut0 = sIF.bOut0 | 0x10;
	else
		sIF.bOut0 = sIF.bOut0 & (~0x10);


    if (m_O06)
		sIF.bOut0 = sIF.bOut0 | 0x20;
	else
		sIF.bOut0 = sIF.bOut0 & (~0x20);


    if (m_O07)
		sIF.bOut0 = sIF.bOut0 | 0x40;
	else
		sIF.bOut0 = sIF.bOut0 & (~0x40);

	if (m_O08)
		sIF.bOut0 = sIF.bOut0 | 0x80;
	else
		sIF.bOut0 = sIF.bOut0 & (~0x80);

	text.Format("%d", sIF.bOut0);
	SetDlgItemText(IDC_OWert, text);

	text.Format("%.2Xh", sIF.bOut0);
	SetDlgItemText(IDC_OWertHex, text);
}



/********************************************************
 *  ClearVariablenUndAnzeige() 
 *
 *  Diese Routine löscht alle angezeigten Eingänge / Ausgänge
 *  auf dem Bildschirm
 ********************************************************/
void CFtLibDemo1Dlg::ClearVariablenUndAnzeige(void)
{
	CString	text;
	double	rdWert = 0;

    
    UpdateData(TRUE);				// Werte einlesen

	m_I01 = FALSE;
	m_I02 = FALSE;
	m_I03 = FALSE;
	m_I04 = FALSE;
	m_I05 = FALSE;
	m_I06 = FALSE;
	m_I07 = FALSE;
	m_I08 = FALSE;

    m_O01 = FALSE;              // Ausgänge abschalten
    m_O02 = FALSE;  
    m_O03 = FALSE;
    m_O04 = FALSE;
    m_O05 = FALSE;
    m_O06 = FALSE;
    m_O07 = FALSE;
    m_O08 = FALSE;


    sIF.bIn0 = 0;
    sIF.uiA01 = 0;
    sIF.uiA02 = 0;
    sIF.uiA0X = 0;
    sIF.uiA0Y = 0;
    sIF.uiA0Z = 0;
    sIF.uiD1 = 0;
    sIF.uiD2 = 0;
    sIF.uiVers = 0;

	text.Format("%d", sIF.bIn0);									// Input Wert (dezimal) anzeigen
	SetDlgItemText(IDC_IWert, text);
	text.Format("%.2Xh", sIF.bIn0);									// Input Wert (hexadezimal) anzeigen
	SetDlgItemText(IDC_IWertHex, text);

	CSliderCtrl* pSC_A01 = (CSliderCtrl*) GetDlgItem(IDC_SL_A01);	// Slider A01 
	pSC_A01->SetPos(abs(sIF.uiA01 - MAX_ANALOGWERT));				// Schieber oben=0, unten=MAX, daher "umdrehen"
	text.Format("%4d", sIF.uiA01);									// und anzeigen
	SetDlgItemText(IDC_SL_A01Wert, text);

	rdWert = sIF.uiA01;												// in Volt umrechnen1
	rdWert = rdWert / 100;											// in Volt umrechnen1
	text.Format("%2.2f V", rdWert);									// und anzeigen ("V" angehängt)
	SetDlgItemText(IDC_SL_A01Volt, text);


	CSliderCtrl* pSC_A02 = (CSliderCtrl*) GetDlgItem(IDC_SL_A02);	// Slider A02 
	pSC_A02->SetPos(abs(sIF.uiA02 - MAX_ANALOGWERT));				// Schieber oben=0, unten=MAX, daher "umdrehen"
	text.Format("%4d", sIF.uiA02);									// und anzeigen
	SetDlgItemText(IDC_SL_A02Wert, text);

	rdWert = sIF.uiA02;												// in Volt umrechnen1
	rdWert = rdWert / 100;											// in Volt umrechnen1
	text.Format("%2.2f V", rdWert);									// und anzeigen ("V" angehängt)
	SetDlgItemText(IDC_SL_A02Volt, text);


	CSliderCtrl* pSC_A0X = (CSliderCtrl*) GetDlgItem(IDC_SL_A0X);	// Slider A0X
	pSC_A0X->SetPos(abs(sIF.uiA0X - MAX_ANALOGWERT));				// Schieber oben=0, unten=MAX, daher "umdrehen"
	text.Format("%4d", sIF.uiA0X);									// und anzeigen
    SetDlgItemText(IDC_SL_A0XWert, text);


	CSliderCtrl* pSC_A0Y = (CSliderCtrl*) GetDlgItem(IDC_SL_A0Y);	// Slider A0Y
	pSC_A0Y->SetPos(abs(sIF.uiA0Y - MAX_ANALOGWERT));				// Schieber oben=0, unten=MAX, daher "umdrehen"
	text.Format("%4d", sIF.uiA0Y);									// und anzeigen
	SetDlgItemText(IDC_SL_A0YWert, text);

	CSliderCtrl* pSC_A0Z = (CSliderCtrl*) GetDlgItem(IDC_SL_A0Z);	// Slider A0Z
	pSC_A0Z->SetPos(abs(sIF.uiA0Z - MAX_ANALOGWERT));				// Schieber oben=0, unten=MAX, daher "umdrehen"
	text.Format("%4d", sIF.uiA0Z);									// und anzeigen
	SetDlgItemText(IDC_SL_A0ZWert, text);

	rdWert = sIF.uiA0Z;												// in Volt umrechnen1
	rdWert = rdWert / 100;											// in Volt umrechnen1
	text.Format("%2.2f V", rdWert);									// und anzeigen ("V" angehängt)
	SetDlgItemText(IDC_SL_A0ZVolt, text);


	CSliderCtrl* pSC_DS1 = (CSliderCtrl*) GetDlgItem(IDC_SL_DS1);	// Slider DS1
	pSC_DS1->SetPos(abs(sIF.uiD1 - MAX_ANALOGWERT));				// Schieber oben=0, unten=MAX, daher "umdrehen"
	text.Format("%4d", sIF.uiD1);									// und anzeigen
	SetDlgItemText(IDC_SL_DS1Wert, text);

	CSliderCtrl* pSC_DS2 = (CSliderCtrl*) GetDlgItem(IDC_SL_DS2);	// Slider DS2
	pSC_DS2->SetPos(abs(sIF.uiD2 - MAX_ANALOGWERT));				// Schieber oben=0, unten=MAX, daher "umdrehen"
	text.Format("%4d", sIF.uiD2);									// und anzeigen
	SetDlgItemText(IDC_SL_DS2Wert, text);

	CSliderCtrl* pSC_VERS = (CSliderCtrl*) GetDlgItem(IDC_SL_Vers);	// Slider Versorgungsspannung
	pSC_VERS->SetPos(abs(sIF.uiVers - MAX_ANALOGWERT));				// Schieber oben=0, unten=MAX, daher "umdrehen"
	text.Format("%4d", sIF.uiVers);							        // und anzeigen 
	SetDlgItemText(IDC_SL_VersWert, text);
	rdWert = sIF.uiVers * 0.0269;									// in Volt umrechnen1
	text.Format("%2.2f Volt", rdWert);								// und anzeigen ("V" angehängt)
	SetDlgItemText(IDC_SL_VersVolt, text);

	text.Format(" ---  ");										// Kein Interface, dann keine Firmware Versionsnummer anzeigen
	SetDlgItemText(IDC_ST_IF_Firmware, text);
	sIF.ucSNok = FALSE;											// kein Interface, dann Anzeige der SN löschen

	text.Format(" ---  ");										// Kein Interface, dann keine SN anzeigen
	SetDlgItemText(IDC_ST_IF_AKT_SN, text);
	SetDlgItemText(IDC_ST_IF_TYP, text);
    
    UpdateData(FALSE);                                          // und schreiben
}



/********************************************************
 *  WriteIfData() 
 *
 *  Diese Routine zeigt die Interface Daten an
 *  (Sn, Fw)
 ********************************************************/
void CFtLibDemo1Dlg::WriteIfData(void)
{
    CString sText;

	if ((sIF.bVerFWH == 0) && (sIF.bVerFWL == 0))				// FIRMWARE Version anzeigen
		sText.Format(" ---  ");									// Kein Interface, dann keine Firmware Versionsnummer anzeigen
	else
	{
		if (sIF.bVerFWL < 10)									// Wenn Versionsnummer x.0y, dann "0" einfügen
        {
            if (sIF.bVerBLL < 10)
            {
				sText.Format("%2d.0%d.%d.0%d", sIF.bVerFWH,sIF.bVerFWL,sIF.bVerBLH,sIF.bVerBLL);    // Firmware Versionsnummer F.0W.B.0L anzeigen
            }
            else
            {
				sText.Format("%2d.0%d.%d.%2d", sIF.bVerFWH,sIF.bVerFWL,sIF.bVerBLH,sIF.bVerBLL);    // Firmware Versionsnummer F.0W.B.0L anzeigen
            }
        }
		else
        {
            if (sIF.bVerBLL < 10)
            {
				sText.Format("%2d.%2d.%d.0%d", sIF.bVerFWH,sIF.bVerFWL,sIF.bVerBLH,sIF.bVerBLL);    // Firmware Versionsnummer F.0W.B.0L anzeigen
            }
            else
            {
				sText.Format("%2d.%2d.%d.%2d", sIF.bVerFWH,sIF.bVerFWL,sIF.bVerBLH,sIF.bVerBLL);    // Firmware Versionsnummer F.0W.B.0L anzeigen
            }
        }
		SetDlgItemText(IDC_ST_IF_Firmware, sText);				// und ausgeben
	}

    if (sIF.ucSNok)
    {
        sText.Format("%d (dez) / %.X (hex) ", sIF.ulSerialNumber, sIF.ulSerialNumber);	// Seriennummer dezimal / hexadezimal anzeigen
    }
    else
    {
        sText.Format("---");
    }
	SetDlgItemText(IDC_ST_IF_AKT_SN, sText);											// Format: .8X für 8-stellen breites Feld


    switch (sIF.dwIfTyp)
    {
        case FT_INTELLIGENT_IF:
			sText.Format("%s", "FT Intelligent Interface");						
            break;

        case FT_INTELLIGENT_IF_SLAVE:
			sText.Format("%s", "FT Intelligent Interface with Slave");						
            break;

        case FT_ROBO_IF_IIM:
			sText.Format("%s", "FT Robo Interface (Intelligent Interface Modus)");
            break;

        case FT_ROBO_IF_USB:
			sText.Format("%s", "FT Robo Interface (USB connected)");
            break;

        case FT_ROBO_IF_OVER_RF:
			sText.Format("%s", "FT Robo Interface (over RF Data Link)");
            break;

        case FT_ROBO_IF_COM:
			sText.Format("%s", "FT Robo Interface (COM connected)");
            break;

        case FT_ROBO_IO_EXTENSION:
			sText.Format("%s", "FT Robo I/O Extension");
            break;

        case FT_ROBO_RF_DATA_LINK:
			sText.Format("%s", "FT Robo RF Data Link");
            break;

        case NO_FT_DEVICE:
        default:
			sText.Format("%s", "--- ");						
            break;
    }
	SetDlgItemText(IDC_ST_IF_TYP, sText);                        // typ des Interface ausgeben
}


	




/********************************************************
 *  OnVScroll() 
 *
 *	Hinweis:
 *	- Der obere Rand des Schiebers entspricht dem MIN-Wert, der untere dem MAX-Wert.
 ********************************************************/
void CFtLibDemo1Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    UINT	uiAusgabe,					// welches Fenster soll beschrieben werden
			uiPos,						// Position des Reglers
			uiSchrittK;                 // Kleiner Schritt
	INT		iMin, iMax,			    	// Bereiche abfragen
		    iFtPos;						// Wert des ft-Reglers
	BYTE	bArray;						// Zeiger in das "Geschwindigkeits" Array der Ausgänge

	CString	text;
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);

	uiAusgabe = NULL;							// nur zur Sicherheit
	if (pScrollBar==GetDlgItem(IDC_SB_O01))		// Ausgang 1 gewünscht
	{
		uiAusgabe = IDC_SB_O01Wert;
		bArray = 1;						
	}
	else if (pScrollBar==GetDlgItem(IDC_SB_O02)) 
	{
		uiAusgabe = IDC_SB_O02Wert;
		bArray = 2;
	}
	else if (pScrollBar==GetDlgItem(IDC_SB_O03)) 
	{
		uiAusgabe = IDC_SB_O03Wert;
		bArray = 3;
	}
	else if (pScrollBar==GetDlgItem(IDC_SB_O04)) 
	{
		uiAusgabe = IDC_SB_O04Wert;
		bArray = 4;
	}
	else if (pScrollBar==GetDlgItem(IDC_SB_O05)) 
	{
		uiAusgabe = IDC_SB_O05Wert;
		bArray = 5;
	}
	else if (pScrollBar==GetDlgItem(IDC_SB_O06)) 
	{
		uiAusgabe = IDC_SB_O06Wert;
		bArray = 6;
	}
	else if (pScrollBar==GetDlgItem(IDC_SB_O07)) 
	{
		uiAusgabe = IDC_SB_O07Wert;
		bArray = 7;
	}
	else if (pScrollBar==GetDlgItem(IDC_SB_O08)) 
	{
		uiAusgabe = IDC_SB_O08Wert;
		bArray = 8;
	}

	uiPos = pScrollBar->GetScrollPos();
	pScrollBar->GetScrollRange(&iMin, &iMax);
	uiSchrittK = 1;
	switch(nSBCode)
	{
		case SB_THUMBPOSITION:			// Regler verschoben
			pScrollBar->SetScrollPos(nPos);
			iFtPos = abs(nPos - (SB_VMAX + SB_VMIN));
			sIF.baOut0VS[bArray] = iFtPos;				// neue Geschwindigkeit setzen
			text.Format("%d", sIF.baOut0VS[bArray]);	// und anzeigen
			SetDlgItemText(uiAusgabe, text);
			break;

		case SB_LINEDOWN:				// Pfeiltaste nach unten (Achtung: oben ist min, unten ist MAX bei Windows!!!)
			uiPos=Min(iMax, uiPos+uiSchrittK);
			pScrollBar->SetScrollPos(uiPos);
			iFtPos = abs(uiPos - (SB_VMAX + SB_VMIN));
			sIF.baOut0VS[bArray] = iFtPos;				// neue Geschwindigkeit setzen
			text.Format("%d", sIF.baOut0VS[bArray]);	// und anzeigen
			SetDlgItemText(uiAusgabe, text);
			break;
	
		case SB_LINEUP:					// Pfeiltaste nach oben (Achtung: oben ist min, unten ist MAX! bei Windows!!)
			uiPos=Max(iMin, uiPos-uiSchrittK);
			pScrollBar->SetScrollPos(uiPos);
			iFtPos = abs(uiPos - (SB_VMAX + SB_VMIN));
			sIF.baOut0VS[bArray] = iFtPos;				// neue Geschwindigkeit setzen
			text.Format("%d", sIF.baOut0VS[bArray]);	// und anzeigen
			SetDlgItemText(uiAusgabe, text);
			break;
	
		case SB_PAGEUP:					// Pfeiltaste nach oben (Achtung: oben ist min, unten ist MAX!!!)
			uiPos=SB_VMIN;				// auf (Windows) MIN-Wert setzen
			pScrollBar->SetScrollPos(uiPos);
			iFtPos = abs(uiPos - (SB_VMAX + SB_VMIN));
			sIF.baOut0VS[bArray] = iFtPos;				// neue Geschwindigkeit setzen
			text.Format("%d", sIF.baOut0VS[bArray]);	// und anzeigen
			SetDlgItemText(uiAusgabe, text);
			break;

		case SB_PAGEDOWN:				// Bildtaste nach unten (Achtung: oben ist min, unten ist MAX!!!)
			uiPos=SB_VMAX;				// auf (Windows) MAX-Wert setzen
			pScrollBar->SetScrollPos(uiPos);
			iFtPos = abs(uiPos - (SB_VMAX + SB_VMIN));
			sIF.baOut0VS[bArray] = iFtPos;				// neue Geschwindigkeit setzen
			text.Format("%d", sIF.baOut0VS[bArray]);	// und anzeigen
			SetDlgItemText(uiAusgabe, text);
			break;
	}
	BerechnePWM();
}


/********************************************************
 * OnButtonScan()
 * Aktualisiert die Device-Liste
 * Öffnet jede Instanz und holt den Device String (Seriennummer des Gerätes)   
 ********************************************************/
void CFtLibDemo1Dlg::OnButtonScanUsb() 
{
    FT_HANDLE   hFt;                            // Handle des Device
    DWORD       dwStatus;
    CString     strDescSProdS;
	CString     strDescSSN;
	CString     strDescSFW;
	CString     str;
    CString     sText;

    UINT        uiI;                            // Zähler


    UpdateData(TRUE);				            // Werte holen
    if (RB_USB == m_RAB_SS)			            // Button USB ist aktiviert, daher alles zurücksetzen
    {
        dwStatus = CloseAllFtDevices();         // alle offenen USB Verbindungen schließen
        if (dwStatus != FTLIB_ERR_SUCCESS)
        {
            sText.Format("FEHLER bei CloseAllFtDevices(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		    MessageBox(sText, MB_OK);
        }
		m_RAB_SS = RB_NIX;						// Schnitstelle zurücksetzen
        sIF.dwIfTyp = NO_FT_DEVICE;
        sIF.dwPort = PORT_NONE;
    }

 	m_List_USB.ResetContent();                          // Liste löschen
    GetDlgItem(IDC_RA_USB)->EnableWindow(FALSE);        // Deaktiviert USB-RadioButton
	sIF.uiUsbDev = -1;									// kein USB-Device ausgewählt

    str = "  ";											// Ausgewähltes USB-Device löschen
    SetDlgItemText(IDC_STATIC_USB_DEV, str);

    UpdateData(FALSE);				            // Werte schreiben

    if (IsFtLibInit() == FTLIB_ERR_LIB_IS_INITIALIZED)      // Nur wenn USB-Bereich verfügbar ist
    {
        dwStatus = InitFtUsbDeviceList();                   // Initialisieren
        switch (dwStatus)
        {
            case FTLIB_ERR_SUCCESS:
            case FTLIB_ERR_DEVICE_NOT_FOUND:
                for (uiI=0; uiI < GetNumFtUsbDevice(); uiI++)
                {
                    strDescSProdS = "";
			        strDescSSN = "";
			        strDescSFW = "";
                                                            
                    hFt = GetFtUsbDeviceHandle(uiI);    // Zeiger auf Device-Struktur holen			
   			        strDescSProdS.Format("  %s", GetFtShortNameStrg(hFt) );
   			        strDescSSN.Format("   SN: %s", GetFtSerialNrStrg(hFt));
       		        strDescSFW.Format("  FW: %s", GetFtFirmwareStrg(hFt));

                                                                    // zur Liste hinzufügen
			        str.Format("%d: %s %s %s ", uiI, strDescSProdS, strDescSSN, strDescSFW );   
			        int index = m_List_USB.AddString(str);
			        if ( index >= 0 ) 
                    {
				        m_List_USB.SetItemData(index, uiI);
			        }
                }   // for(...)

                if (uiI == 0)   
                {                               // keine Devices gefunden
			        str = "No ft-devices found / keine ft-Geräte gefunden";   
		            m_List_USB.AddString(str);
		            m_List_USB.EnableWindow(FALSE);
                }
                else
                {
		            m_List_USB.EnableWindow(TRUE);
                }
                break;

            default:            // Fehler bei InitFtUsbDeviceList()
                sText.Format("FEHLER bei InitFtUsbDeviceList(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		        MessageBox(sText, MB_OK);
                break;
        }                   // switch()
    }                       // if (pMem..)
    else
    {                       // USB nicht initialisiert, also vermutlich nicht verfügbar
        sText.Format("Dieser Rechner unterstützt kein USB");
	    MessageBox(sText, MB_OK);
    }


                                                           // Distanssensor auswählen
    GetDlgItem(IDC_STATIC_DS_TOL)->EnableWindow(TRUE);     // Distanzsensor: Toleranztext
    GetDlgItem(IDC_EDIT_DS_TOL1)->EnableWindow(TRUE);      // Distanzsensor: Toleranz 1
    GetDlgItem(IDC_EDIT_DS_TOL2)->EnableWindow(TRUE);      // Distanzsensor: Toleranz 2

    GetDlgItem(IDC_STATIC_DS_REP)->EnableWindow(TRUE);     // Distanzsensor: Repeat
    GetDlgItem(IDC_EDIT_DS_REP1)->EnableWindow(TRUE);      // Distanzsensor: Repeatwert 1
    GetDlgItem(IDC_EDIT_DS_REP2)->EnableWindow(TRUE);      // Distanzsensor: Repeatwert 2

    GetDlgItem(IDC_STATIC_DS_SCHWELL)->EnableWindow(TRUE); // Distanzsensor: Schwellwerttext
    GetDlgItem(IDC_EDIT_DS_SCHWELLE1)->EnableWindow(TRUE); // Distanzsensor: Schwellwert 1
    GetDlgItem(IDC_EDIT_DS_SCHWELLE2)->EnableWindow(TRUE); // Distanzsensor: Schwellwert 2


    GetDlgItem(IDC_RADIO_DS_DS)->EnableWindow(TRUE);       // Distanzsensor: Auswahlbutton "Distanzsensor"
    GetDlgItem(IDC_RADIO_DS_VOLT)->EnableWindow(TRUE);     // Distanzsensor: Auswahlbutton "Voltmesser"


    UpdateData(FALSE);				        // Werte schreiben
}
    




/********************************************************
 * OnSelchangeListUsb()
 * Es wurde auf einen Eintrag in der Liste der
 * Devices geklickt. Nun diesen Eintrag auswählen
 * und im Fenster nach dem USB-Button anzeigen.          
 ********************************************************/
void CFtLibDemo1Dlg::OnSelchangeListUsb() 
{
    FT_HANDLE   hFt;                            // Handle des Device
    DWORD       dwStatus;
    int         iListBox;                       // Zeiger / Zähler für ft-Devices

    CString     strDescSProdS;                  // Strings für die Texte der Devices
	CString     strDescSSN;
	CString     strDescSFW;
	CString     sText;


	UpdateData(TRUE);				            // Werte holen
    if (RB_USB == m_RAB_SS)			            // Button USB ist aktiviert, daher alles zurücksetzen
    {
        dwStatus = CloseAllFtDevices();         // alle offenen USB Verbindungen schließen
        if (dwStatus != FTLIB_ERR_SUCCESS)
        {
            sText.Format("FEHLER bei CloseAllFtDevices(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		    MessageBox(sText, MB_OK);
        }

		m_RAB_SS = RB_NIX;						// Schnitstelle zurücksetzen
        sIF.dwIfTyp = NO_FT_DEVICE;
        sIF.dwPort = PORT_NONE;
    }

    iListBox = m_List_USB.GetCurSel();          // aktuell ausgewähles USB-Gerät

    GetDlgItem(IDC_RA_USB)->EnableWindow(TRUE); // zeigt USB-Button wieder an
//    GetDlgItem(IDC_RA_FUNK)->EnableWindow(TRUE);// zeigt Funk-Button wieder an

    
    hFt = GetFtUsbDeviceHandle(iListBox);    // Zeiger auf Device-Struktur holen			
   	strDescSProdS.Format("  %s", GetFtShortNameStrg(hFt) );
   	strDescSSN.Format("   SN: %s", GetFtSerialNrStrg(hFt));
    strDescSFW.Format("  FW: %s", GetFtFirmwareStrg(hFt));

                                                          // zur Liste hinzufügen
	sText.Format("%d: %s %s %s ", iListBox, strDescSProdS, strDescSSN, strDescSFW );   
    SetDlgItemText(IDC_STATIC_USB_DEV, sText);

	sIF.uiUsbDev = iListBox;					// ausgewähltes USB-Device setzen


                                                           // Distanssensor auswählen
    GetDlgItem(IDC_STATIC_DS_TOL)->EnableWindow(TRUE);     // Distanzsensor: Toleranztext
    GetDlgItem(IDC_EDIT_DS_TOL1)->EnableWindow(TRUE);      // Distanzsensor: Toleranz 1
    GetDlgItem(IDC_EDIT_DS_TOL2)->EnableWindow(TRUE);      // Distanzsensor: Toleranz 2

    GetDlgItem(IDC_STATIC_DS_REP)->EnableWindow(TRUE);     // Distanzsensor: Repeat
    GetDlgItem(IDC_EDIT_DS_REP1)->EnableWindow(TRUE);      // Distanzsensor: Repeatwert 1
    GetDlgItem(IDC_EDIT_DS_REP2)->EnableWindow(TRUE);      // Distanzsensor: Repeatwert 2

    GetDlgItem(IDC_STATIC_DS_SCHWELL)->EnableWindow(TRUE); // Distanzsensor: Schwellwerttext
    GetDlgItem(IDC_EDIT_DS_SCHWELLE1)->EnableWindow(TRUE); // Distanzsensor: Schwellwert 1
    GetDlgItem(IDC_EDIT_DS_SCHWELLE2)->EnableWindow(TRUE); // Distanzsensor: Schwellwert 2


    GetDlgItem(IDC_RADIO_DS_DS)->EnableWindow(TRUE);       // Distanzsensor: Auswahlbutton "Distanzsensor"
    GetDlgItem(IDC_RADIO_DS_VOLT)->EnableWindow(TRUE);     // Distanzsensor: Auswahlbutton "Voltmesser"



    UpdateData(FALSE);				        // Werte schreiben
}



/********************************************************
 * OnRabIif() 
 *
 * "Intelligent Interface" ausgewählt
 ********************************************************/
void CFtLibDemo1Dlg::OnRabIif() 
{
    sIF.dwComTyp = FT_INTELLIGENT_IF;
}


/********************************************************
 * OnRabIifExtension() 
 *
 * "Intelligent Interface mit Extension" ausgewählt
 ********************************************************/
void CFtLibDemo1Dlg::OnRabIifExtension() 
{
    sIF.dwComTyp = FT_INTELLIGENT_IF_SLAVE;
}


/********************************************************
 * OnRabRif() 
 *
 * "Robo Interface" ausgewählt
 ********************************************************/
void CFtLibDemo1Dlg::OnRabRif() 
{
    sIF.dwComTyp = FT_ROBO_IF_COM;
}


/********************************************************
 * SetupCommPOrt(DWORD dwComPort)
 *
 ********************************************************/
void CFtLibDemo1Dlg::SetupCommPort(DWORD dwComPort)
{
    NOTIFICATION_EVENTS     sNotification;
	CString		sText;
	DWORD		dwStatus;


    ClearVariablenUndAnzeige();         // Anzeigevariablen auf "0" setzen (muß vor UpdateData() stehen, da die 
                                        // Routine auch einließt und schreibt!
	UpdateData(TRUE);				    // Werte holen

    dwStatus = FTLIB_ERR_SUCCESS;

    if (sIF.dwPort == PORT_USB)                             // USB-Auswahl zurücksetzen
    {
        GetDlgItem(IDC_RA_USB)->EnableWindow(FALSE);        // Deaktiviert USB-RadioButton
//        GetDlgItem(IDC_RA_FUNK)->EnableWindow(FALSE);       // Deaktiviert Funk-RadioButton
	    sIF.uiUsbDev = -1;									// kein USB-Device ausgewählt

        sText = "  ";									    // Ausgewähltes USB-Device löschen
        SetDlgItemText(IDC_STATIC_USB_DEV, sText);
    }

    if (sIF.dwPort != PORT_NONE)        
    {
        dwStatus = CloseAllFtDevices();
        if (dwStatus != FTLIB_ERR_SUCCESS)
        {
            sText.Format("FEHLER bei CloseAllFtDevice(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		    MessageBox(sText, MB_OK);
        }
        sIF.hFt = NULL;
    }


    if (dwStatus == FTLIB_ERR_SUCCESS)
    {
        sIF.dwPort = PORT_COM;
        sIF.hFt = OpenFtCommDevice(dwComPort, sIF.dwComTyp, FT_ANALOG_CYCLE, &dwStatus);
        if (sIF.hFt == NULL)
        {
            sText.Format("FEHLER bei OpenFtCommDevice(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		    MessageBox(sText, MB_OK);
            m_RAB_SS = SS_NIX;
            sIF.dwIfTyp = NO_FT_DEVICE;
        }

        if (dwStatus == FTLIB_ERR_SUCCESS)              // Seriennummer holen und setzen
        {                                               // Intelligent Interface liefert keine Seriennummer!
            dwStatus = GetFtSerialNr(sIF.hFt);
			sIF.ulSerialNumber = dwStatus;              
			sIF.ucSNok = TRUE;
            dwStatus = FTLIB_ERR_SUCCESS;              
        }
        
        if (dwStatus == FTLIB_ERR_SUCCESS)              // Firmware holen und setzen
        {                                               // Intelligent Interface liefert keine Firmware!
            dwStatus = GetFtFirmware(sIF.hFt);         
            sIF.bVerBLL = (UCHAR) dwStatus & 0x00FF;
			sIF.bVerBLH = (UCHAR) (dwStatus >> 8) & 0x00FF;     
			sIF.bVerFWL = (UCHAR) (dwStatus >> 16) & 0x00FF;    
			sIF.bVerFWH = (UCHAR) (dwStatus >> 24) & 0x00FF;    
            dwStatus = FTLIB_ERR_SUCCESS;              
        }
        
        if (dwStatus == FTLIB_ERR_SUCCESS)              // Nun Transfer der Daten starten
        {                                               // Nicht vergessen die Notification Struktur zu löschen, wenn nicht genutzt!!!
            sNotification.Context = NULL;               // ZeroMemory() ist der einfachere Weg,
            sNotification.Context = NULL;               // aber in diesem Beispiel fällt diese
            sNotification.Message = NULL;               // schrittweise Initialisierung besser AUF !!!
            sNotification.NotificationCallback = NULL;
            sNotification.WindowsHandle = NULL;


            sIF.dwDsTol1 = strtoul (m_DS_Tol1, NULL, 10);       // Toleranz 1
            sIF.dwDsTol2 = strtoul (m_DS_Tol2, NULL, 10);       // Toleranz 2
            sIF.dwDsRep1 = strtoul (m_DS_Rep1, NULL, 10);       // Repeatwert 1
            sIF.dwDsRep2 = strtoul (m_DS_Rep2, NULL, 10);       // Repeatwert 2
            sIF.dwDsSchwelle1 = strtoul (m_DS_Schwell1, NULL, 10);  // Schaltschwelle 1
            sIF.dwDsSchwelle2 = strtoul (m_DS_Schwell2, NULL, 10);  // Schaltschwelle 2


            if ((sIF.bVerFWL + (sIF.bVerFWH *256)) >= 25)   // ab Version 0.25 wird DS unterstützt
            {
                switch (sIF.dwIfTyp)
                {
                    case FT_INTELLIGENT_IF:                  // keine Unterstützung für DS
                    case FT_INTELLIGENT_IF_SLAVE:    
                    case FT_ROBO_IF_IIM:   
                        break;

                    case FT_ROBO_IF_USB:
                    case FT_ROBO_IF_COM:
                    case FT_ROBO_IF_OVER_RF: 
                    case FT_ROBO_IO_EXTENSION:       
                    case FT_ROBO_RF_DATA_LINK:       
                        dwStatus = SetFtDistanceSensorMode(sIF.hFt, sIF.dwDistanzMode, sIF.dwDsTol1, sIF.dwDsTol2,
                                                         sIF.dwDsSchwelle1, sIF.dwDsSchwelle2, sIF.dwDsRep1, sIF.dwDsRep2);
                        if (dwStatus != FTLIB_ERR_SUCCESS)
                        {
                            sText.Format("FEHLER bei SetFtDistanceSensorMode(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		                    MessageBox(sText, MB_OK);
                        }
                        break;
                }
            }


            UpdateAgData();                         // Ausgänge setzen
            dwStatus = StartFtTransferArea(sIF.hFt, &sNotification);
            if (dwStatus != FTLIB_ERR_SUCCESS)
            {
                sText.Format("FEHLER bei StartFtTransferArea(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		        MessageBox(sText, MB_OK);
            }
        }


    	if (dwStatus == FTLIB_ERR_SUCCESS)              // Nun Transfer Adresse holen
	    {
            sIF.pTransArea = GetFtTransferAreaAddress(sIF.hFt);
            if (sIF.pTransArea == NULL)
            {
                sText.Format("FEHLER bei GetFtTransferAreaAddress(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		        MessageBox(sText, MB_OK);
                dwStatus = !FTLIB_ERR_SUCCESS;
            }
        }


    	if (dwStatus == FTLIB_ERR_SUCCESS)
	    {
            dwStatus = GetFtDeviceTyp(sIF.hFt);
            if (dwStatus > FT_MAX_TYP_NUMBER)
            {                               // Fehler
                sText.Format("FEHLER bei GetFtDeviceTyp(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		        MessageBox(sText, MB_OK);
                dwStatus = !FTLIB_ERR_SUCCESS;
                sIF.dwIfTyp = NO_FT_DEVICE;
            }
            else
            {                               // Typ ist korrekt
                sIF.dwIfTyp = dwStatus;
                dwStatus = FTLIB_ERR_SUCCESS;
                UpdateAgData();             // gewünschter Zustand der Ausgänge einlesen und OUT-Varaible setzen
            }

            GetDlgItem(IDC_RAB_RIF)->EnableWindow(FALSE);   // Auswahlbutton für IF deaktivieren
            GetDlgItem(IDC_RAB_IIF)->EnableWindow(FALSE);   // Auswahlbutton für IF deaktivieren
            GetDlgItem(IDC_RAB_IIF_EXTENSION)->EnableWindow(FALSE);
            GetDlgItem(IDC_STATIC_IF_RAHMEN)->EnableWindow(FALSE);


                                                                    // Distanzsensor
            GetDlgItem(IDC_STATIC_DS_TOL)->EnableWindow(FALSE);     // Distanzsensor: Toleranztext
            GetDlgItem(IDC_EDIT_DS_TOL1)->EnableWindow(FALSE);      // Distanzsensor: Toleranz 1
            GetDlgItem(IDC_EDIT_DS_TOL2)->EnableWindow(FALSE);      // Distanzsensor: Toleranz 2

            GetDlgItem(IDC_STATIC_DS_REP)->EnableWindow(FALSE);     // Distanzsensor: Repeat
            GetDlgItem(IDC_EDIT_DS_REP1)->EnableWindow(FALSE);      // Distanzsensor: Repeatwert 1
            GetDlgItem(IDC_EDIT_DS_REP2)->EnableWindow(FALSE);      // Distanzsensor: Repeatwert 2

            GetDlgItem(IDC_STATIC_DS_SCHWELL)->EnableWindow(FALSE); // Distanzsensor: Schwellwerttext
            GetDlgItem(IDC_EDIT_DS_SCHWELLE1)->EnableWindow(FALSE); // Distanzsensor: Schwellwert 1
            GetDlgItem(IDC_EDIT_DS_SCHWELLE2)->EnableWindow(FALSE); // Distanzsensor: Schwellwert 2

            GetDlgItem(IDC_RADIO_DS_DS)->EnableWindow(FALSE);       // Distanzsensor: Auswahlbutton "Distanzsensor"
            GetDlgItem(IDC_RADIO_DS_VOLT)->EnableWindow(FALSE);     // Distanzsensor: Auswahlbutton "Voltmesser"
        }
    }

    WriteIfData();                              // SN / FW ausgeben
    UpdateData(FALSE);				        // Werte schreiben
}


/********************************************************
 * OnRaOff() 
 *
 * Button "Offline" wurde angeklickt
 ********************************************************/
void CFtLibDemo1Dlg::OnRaOff() 
{
	CString		sText;
    DWORD       dwStatus;


    UpdateData(TRUE);				        // Werte holen

    if (sIF.dwPort == PORT_USB)                             // USB-Auswahl zurücksetzen
    {
        GetDlgItem(IDC_RA_USB)->EnableWindow(FALSE);        // Deaktiviert USB-RadioButton
//        GetDlgItem(IDC_RA_FUNK)->EnableWindow(FALSE);       // Deaktiviert Funk-RadioButton
	    sIF.uiUsbDev = -1;									// kein USB-Device ausgewählt

        sText = "  ";									    // Ausgewähltes USB-Device löschen
        SetDlgItemText(IDC_STATIC_USB_DEV, sText);
    }

    if (sIF.hFt)
    {
        dwStatus = StopFtTransferArea(sIF.hFt); // Stoppen
        if (dwStatus != FTLIB_ERR_SUCCESS)
        {
            sText.Format("FEHLER bei StopFtTransferArea(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		    MessageBox(sText, MB_OK);
        }
    }


    if (sIF.hFt)
    {
        dwStatus = ResetFtTransfer(sIF.hFt);        // Ausgänge abschalten
        if ( (dwStatus != FTLIB_ERR_SUCCESS) && (dwStatus != FTLIB_ERR_READ_COM_NOTHING) )
        {
            sText.Format("FEHLER bei ResetFtTransfer(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		    MessageBox(sText, MB_OK);
        }
    }

    
    if (sIF.dwPort != PORT_NONE)            // Falls eine Schnittstelle aktiv ist, alles zurücksetzen
    {
        dwStatus = CloseAllFtDevices();
        if (dwStatus != FTLIB_ERR_SUCCESS)
        {
            sText.Format("FEHLER bei CloseAllFtDevices(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		    MessageBox(sText, MB_OK);
        }
        sIF.hFt = NULL;
        sIF.dwPort = PORT_NONE;
    }
    

    sIF.pTransArea = NULL;
    sIF.dwIfTyp = NO_FT_DEVICE;
    sIF.ulSerialNumber = 0;
    sIF.ucSNok = FALSE;
    sIF.bVerFWH = 0;
    sIF.bVerFWL = 0;
    sIF.bVerBLH = 0;
    sIF.bVerBLL = 0;

    UpdateData(FALSE);                              // Werte schreiben

    ClearVariablenUndAnzeige();         // Anzeigevariablen auf "0" setzen (muß hinter UpdateData(FALSE) stehen, da die 
                                        // Routine auch einließt und schreibt!
    WriteIfData();                                  // SN / FW löschen

    GetDlgItem(IDC_RAB_RIF)->EnableWindow(TRUE);    // Auswahlbutton für IF aktivieren
    GetDlgItem(IDC_RAB_IIF)->EnableWindow(TRUE);    // Auswahlbutton für IF aktivieren
    GetDlgItem(IDC_RAB_IIF_EXTENSION)->EnableWindow(TRUE);
    GetDlgItem(IDC_STATIC_IF_RAHMEN)->EnableWindow(TRUE);

                                                           // Distanssensor auswählen
    GetDlgItem(IDC_STATIC_DS_TOL)->EnableWindow(TRUE);     // Distanzsensor: Toleranztext
    GetDlgItem(IDC_EDIT_DS_TOL1)->EnableWindow(TRUE);      // Distanzsensor: Toleranz 1
    GetDlgItem(IDC_EDIT_DS_TOL2)->EnableWindow(TRUE);      // Distanzsensor: Toleranz 2

    GetDlgItem(IDC_STATIC_DS_REP)->EnableWindow(TRUE);     // Distanzsensor: Repeat
    GetDlgItem(IDC_EDIT_DS_REP1)->EnableWindow(TRUE);      // Distanzsensor: Repeatwert 1
    GetDlgItem(IDC_EDIT_DS_REP2)->EnableWindow(TRUE);      // Distanzsensor: Repeatwert 2

    GetDlgItem(IDC_STATIC_DS_SCHWELL)->EnableWindow(TRUE); // Distanzsensor: Schwellwerttext
    GetDlgItem(IDC_EDIT_DS_SCHWELLE1)->EnableWindow(TRUE); // Distanzsensor: Schwellwert 1
    GetDlgItem(IDC_EDIT_DS_SCHWELLE2)->EnableWindow(TRUE); // Distanzsensor: Schwellwert 2

    GetDlgItem(IDC_RADIO_DS_DS)->EnableWindow(TRUE);       // Distanzsensor: Auswahlbutton "Distanzsensor"
    GetDlgItem(IDC_RADIO_DS_VOLT)->EnableWindow(TRUE);     // Distanzsensor: Auswahlbutton "Voltmesser"
}



/********************************************************
 * OnRaUsb() 
 *
 * Button "Usb" wurde angeklickt
 ********************************************************/
void CFtLibDemo1Dlg::OnRaUsb()
{
    NOTIFICATION_EVENTS     sNotification;
	CString		sText;
	DWORD		dwStatus,
                dwStatus2;

    ClearVariablenUndAnzeige();     // Anzeigevariablen auf "0" setzen (muß vor UpdateData(TRUE) stehen, da die 
                                    // Routine auch einließt und schreibt!
	UpdateData(TRUE);				// Werte holen


    if (sIF.uiUsbDev != -1)			// Nummer des ausgewählten USB-Device (0..Device), -1=Nix ausgewählt
    {                               // Ein Device ist ausgewählt worden
        dwStatus = CloseAllFtDevices();
        sIF.hFt = NULL;
        if (dwStatus != FTLIB_ERR_SUCCESS)
        {
            sText.Format("FEHLER bei CloseAllFtDevices(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		    MessageBox(sText, MB_OK);
        }
        
        if (dwStatus == FTLIB_ERR_SUCCESS)
        {
            sIF.hFt = GetFtUsbDeviceHandle(sIF.uiUsbDev);   // Handle holen
            if (sIF.hFt == NULL)
            {
                sText.Format("FEHLER bei GetFtUsbDeviceHandle(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		        MessageBox(sText, MB_OK);
                dwStatus = !FTLIB_ERR_SUCCESS;              // Fehlercode zum Abbruch setzen!
            }
        }


        if (dwStatus == FTLIB_ERR_SUCCESS)
        {
            dwStatus = OpenFtUsbDevice(sIF.hFt);
            if (dwStatus != FTLIB_ERR_SUCCESS)
            {
                sText.Format("FEHLER bei OpenFtUsbDevice(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		        MessageBox(sText, MB_OK);

                dwStatus2 = CloseAllFtDevices();
                if (dwStatus2 != FTLIB_ERR_SUCCESS)
                {
                    sText.Format("FEHLER bei CloseAllFtDevice(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		            MessageBox(sText, MB_OK);
                }

                GetDlgItem(IDC_RA_USB)->EnableWindow(FALSE);        // Deaktiviert USB-RadioButton
	            sIF.uiUsbDev = -1;									// kein USB-Device ausgewählt
                sText = "  ";									    // Ausgewähltes USB-Device löschen
                SetDlgItemText(IDC_STATIC_USB_DEV, sText);

                sIF.hFt = NULL;
                m_RAB_SS = SS_NIX;      
            }
        }


        if (dwStatus == FTLIB_ERR_SUCCESS)              // Seriennummer holen und setzen
        {
            dwStatus = GetFtSerialNr(sIF.hFt);
            if (dwStatus == NULL)
            {
                sText.Format("FEHLER bei GetFtSerialNr(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		        MessageBox(sText, MB_OK);
                dwStatus = !FTLIB_ERR_SUCCESS;          // Fehlercode zum Abbruch setzen!
            }
            else
            {
			    sIF.ulSerialNumber = dwStatus;
			    sIF.ucSNok = TRUE;
                dwStatus = FTLIB_ERR_SUCCESS;              
            }
        }


        if (dwStatus == FTLIB_ERR_SUCCESS)              // Firmware holen und setzen
        {
            dwStatus = GetFtFirmware(sIF.hFt);
            if (dwStatus == NULL)
            {
                sText.Format("FEHLER bei GetFtFirmware(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		        MessageBox(sText, MB_OK);
                dwStatus = !FTLIB_ERR_SUCCESS;          // Fehlercode zum Abbruch setzen!
            }
            else
            {
                sIF.bVerBLL = (UCHAR) dwStatus & 0x00FF;
				sIF.bVerBLH = (UCHAR) (dwStatus >> 8) & 0x00FF;     // H-Teil kopieren der Bootloader Versionsnummer
				sIF.bVerFWL = (UCHAR) (dwStatus >> 16) & 0x00FF;    // L-Teil kopieren der Firmware Versionsnummer
				sIF.bVerFWH = (UCHAR) (dwStatus >> 24) & 0x00FF;    // H-Teil kopieren der Firmware Versionsnummer
                dwStatus = FTLIB_ERR_SUCCESS;              
            }
        }


        if (dwStatus == FTLIB_ERR_SUCCESS)      // Interfacetyp holen und speichern, wird anschließend benötigt
        {                                       // um festzustellen, ob Distanzsensor gestartet werden kann
            dwStatus = GetFtDeviceTyp(sIF.hFt);
            if (dwStatus > FT_MAX_TYP_NUMBER)
            {                                   // Fehler
                sText.Format("FEHLER bei GetFtDeviceTyp(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		        MessageBox(sText, MB_OK);
                dwStatus = !FTLIB_ERR_SUCCESS;
            }
            else
            {                                   // Typ ist korrekt
                sIF.dwIfTyp = dwStatus;
                dwStatus = FTLIB_ERR_SUCCESS;
            }
        }


        if (m_RAB_DsWert == RAB_DS_VOLT)   
        {                                               // Spannungen messen
            sIF.dwDistanzMode = IF_DS_INPUT_VOLTAGE;
        }
        else
        {
            sIF.dwDistanzMode = IF_DS_INPUT_ULTRASONIC; // Distanzsensor gewünscht
        }

        sIF.dwDsTol1 = strtoul (m_DS_Tol1, NULL, 10);       // Toleranz 1
        sIF.dwDsTol2 = strtoul (m_DS_Tol2, NULL, 10);       // Toleranz 2
        sIF.dwDsRep1 = strtoul (m_DS_Rep1, NULL, 10);       // Repeatwert 1
        sIF.dwDsRep2 = strtoul (m_DS_Rep2, NULL, 10);       // Repeatwert 2
        sIF.dwDsSchwelle1 = strtoul (m_DS_Schwell1, NULL, 10);  // Schaltschwelle 1
        sIF.dwDsSchwelle2 = strtoul (m_DS_Schwell2, NULL, 10);  // Schaltschwelle 2


        if (dwStatus == FTLIB_ERR_SUCCESS)              // Nun Transfer der Daten starten
        {                                               // Nicht vergessen die Notification Struktur zu löschen, wenn nicht genutzt!!!
            sNotification.Context = NULL;               // ZeroMemory() ist der einfachere Weg,
            sNotification.Context = NULL;               // aber in diesem Beispiel fällt diese
            sNotification.Message = NULL;               // schrittweise Initialisierung besser AUF !!!
            sNotification.NotificationCallback = NULL;
            sNotification.WindowsHandle = NULL;

            if ((sIF.bVerFWL + (sIF.bVerFWH *256)) >= 25)   // ab Version 0.25 wird DS unterstützt
            {
                switch (sIF.dwIfTyp)
                {
                    case FT_INTELLIGENT_IF:                  // keine Unterstützung für DS
                    case FT_INTELLIGENT_IF_SLAVE:    
                    case FT_ROBO_IF_IIM:   
                        break;

                    case FT_ROBO_IF_USB:
                    case FT_ROBO_IF_COM:
                    case FT_ROBO_IF_OVER_RF: 
                    case FT_ROBO_IO_EXTENSION:       
                    case FT_ROBO_RF_DATA_LINK:       
                        dwStatus = SetFtDistanceSensorMode(sIF.hFt, sIF.dwDistanzMode, sIF.dwDsTol1, sIF.dwDsTol2,
                                                         sIF.dwDsSchwelle1, sIF.dwDsSchwelle2, sIF.dwDsRep1, sIF.dwDsRep2);
                        if (dwStatus != FTLIB_ERR_SUCCESS)
                        {
                            sText.Format("FEHLER bei SetFtDistanceSensorMode(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		                    MessageBox(sText, MB_OK);
                        }
                        break;
                }
            }

            UpdateAgData();                         // Ausgänge setzen
            dwStatus = StartFtTransferArea(sIF.hFt, &sNotification);
            if (dwStatus != FTLIB_ERR_SUCCESS)
            {
                sText.Format("FEHLER bei StartFtTransferArea(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		        MessageBox(sText, MB_OK);
            }
        }


    	if (dwStatus == FTLIB_ERR_SUCCESS)              // Nun Transfer Adresse holen
	    {
            sIF.pTransArea = GetFtTransferAreaAddress(sIF.hFt);
            if (sIF.pTransArea == NULL)
            {
                sText.Format("FEHLER bei GetFtTransferAreaAddress(): %s \n%s\n(#%8X)", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
		        MessageBox(sText, MB_OK);
                dwStatus = !FTLIB_ERR_SUCCESS;
            }
        }


    	if (dwStatus == FTLIB_ERR_SUCCESS)
	    {
            sIF.dwPort = PORT_USB;
    	    m_RAB_SS = RB_USB;          // Button USB aktiviert
            UpdateAgData();             // gewünschter Zustand der Ausgänge einlesen und OUT-Varaible setzen
        }
        else                                        // Transfer starten ist fehlgeschlagen
        {                                           // nun testen, ob es sich um ein RF-Data-Link handelt!
            if (sIF.dwIfTyp == (DWORD) FT_ROBO_RF_DATA_LINK)
            {                                       // wenn es ein Rf-Data-Link ist, dann das "interne" Setup freischalten
                sIF.dwPort = PORT_USB;
    	        m_RAB_SS = RB_USB;                  // Button USB aktiviert
            }
        }
    }
    
    GetDlgItem(IDC_RAB_RIF)->EnableWindow(TRUE);    // Auswahlbutton für IF-Typ aktivieren
    GetDlgItem(IDC_RAB_IIF)->EnableWindow(TRUE);    // Auswahlbutton für IF-Typ aktivieren
    GetDlgItem(IDC_RAB_IIF_EXTENSION)->EnableWindow(TRUE);
    GetDlgItem(IDC_STATIC_IF_RAHMEN)->EnableWindow(TRUE);

                                                            // Distanzsensor
    GetDlgItem(IDC_STATIC_DS_TOL)->EnableWindow(FALSE);     // Distanzsensor: Toleranztext
    GetDlgItem(IDC_EDIT_DS_TOL1)->EnableWindow(FALSE);      // Distanzsensor: Toleranz 1
    GetDlgItem(IDC_EDIT_DS_TOL2)->EnableWindow(FALSE);      // Distanzsensor: Toleranz 2

    GetDlgItem(IDC_STATIC_DS_REP)->EnableWindow(FALSE);     // Distanzsensor: Repeat
    GetDlgItem(IDC_EDIT_DS_REP1)->EnableWindow(FALSE);      // Distanzsensor: Repeatwert 1
    GetDlgItem(IDC_EDIT_DS_REP2)->EnableWindow(FALSE);      // Distanzsensor: Repeatwert 2

    GetDlgItem(IDC_STATIC_DS_SCHWELL)->EnableWindow(FALSE); // Distanzsensor: Schwellwerttext
    GetDlgItem(IDC_EDIT_DS_SCHWELLE1)->EnableWindow(FALSE); // Distanzsensor: Schwellwert 1
    GetDlgItem(IDC_EDIT_DS_SCHWELLE2)->EnableWindow(FALSE); // Distanzsensor: Schwellwert 2

    GetDlgItem(IDC_RADIO_DS_DS)->EnableWindow(FALSE);       // Distanzsensor: Auswahlbutton "Distanzsensor"
    GetDlgItem(IDC_RADIO_DS_VOLT)->EnableWindow(FALSE);     // Distanzsensor: Auswahlbutton "Voltmesser"



    UpdateData(FALSE);				            // Werte schreiben

    WriteIfData();                              // SN / FW ausgeben
}



/********************************************************
 * OnRaSerc1() 
 *
 * Button "COM 1" wurde angeklickt
 ********************************************************/
void CFtLibDemo1Dlg::OnRaSerc1()
{
    UpdateData(TRUE);				// Werte holen
    if (m_RAB_SS == RB_SER_COM1)
    {
        SetupCommPort(PORT_COM1);
    }
}


/********************************************************
 * OnRaSerc2() 
 *
 * Button "COM 2" wurde angeklickt
 ********************************************************/
 void CFtLibDemo1Dlg::OnRaSerc2() 
{
    UpdateData(TRUE);				// Werte holen
    if (m_RAB_SS == RB_SER_COM2)
    {
        SetupCommPort(PORT_COM2);
    }
}


/********************************************************
 * OnRaSerc3() 
 *
 * Button "COM 3" wurde angeklickt
 ********************************************************/
void CFtLibDemo1Dlg::OnRaSerc3() 
{
    SetupCommPort(PORT_COM3);
}


/********************************************************
 * OnRaSerc4() 
 *
 * Button "COM 4" wurde angeklickt
 ********************************************************/
void CFtLibDemo1Dlg::OnRaSerc4() 
{
    SetupCommPort(PORT_COM4);
}




