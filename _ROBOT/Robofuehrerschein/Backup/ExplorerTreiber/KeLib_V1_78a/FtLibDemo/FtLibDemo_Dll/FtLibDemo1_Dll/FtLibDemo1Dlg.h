// FtLibDemo1Dlg.h : Header-Datei
//

#if !defined(AFX_FTLIBDEMO1DLG_H__6FD220B0_BBA4_466A_A5BF_34DB72FB5F00__INCLUDED_)
#define AFX_FTLIBDEMO1DLG_H__6FD220B0_BBA4_466A_A5BF_34DB72FB5F00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFtLibDemo1Dlg Dialogfeld

class CFtLibDemo1Dlg : public CDialog
{
// Konstruktion
public:
	CFtLibDemo1Dlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CFtLibDemo1Dlg)
	enum { IDD = IDD_FTLIBDEMO1_DIALOG };
	CListBox	m_List_USB;
	int		m_RAB_SS;
	int		m_RAB_Com_Mode;
	int		m_RAB_DsWert;
	CString	m_DS_Tol1;
	CString	m_DS_Tol2;
	CString	m_DS_Rep1;
	CString	m_DS_Rep2;
	CString	m_DS_Schwell1;
	CString	m_DS_Schwell2;
	CString	m_sTime;
	BOOL	m_O01;
	BOOL	m_O02;
	BOOL	m_O03;
	BOOL	m_O04;
	BOOL	m_O05;
	BOOL	m_O06;
	BOOL	m_O07;
	BOOL	m_O08;
	BOOL	m_I01;
	BOOL	m_I02;
	BOOL	m_I03;
	BOOL	m_I04;
	BOOL	m_I05;
	BOOL	m_I06;
	BOOL	m_I07;
	BOOL	m_I08;
	//}}AFX_DATA

    void UpdateAgData(); 
    void ClearVariablenUndAnzeige(void);
    void WriteIfData(void);
    void SetupCommPort(DWORD dwComPort);

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CFtLibDemo1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CFtLibDemo1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonExit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnO01();
	afx_msg void OnO02();
	afx_msg void OnO03();
	afx_msg void OnO04();
	afx_msg void OnO05();
	afx_msg void OnO06();
	afx_msg void OnO07();
	afx_msg void OnO08();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);


	afx_msg void OnRaSer();
	afx_msg void OnRaUsb();
	afx_msg void OnRaSerc1();
	afx_msg void OnRaSerc2();
	afx_msg void OnRaSerc3();
	afx_msg void OnRaSerc4();
	afx_msg void OnStInitCom();
	afx_msg void OnRaOff();
	afx_msg void OnButtonScanUsb();
	afx_msg void OnCheckUsb();
	afx_msg void OnRabIif();
	afx_msg void OnRabIifExtension();
	afx_msg void OnRabRif();

	afx_msg void OnSelchangeListUsb();


	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_FTLIBDEMO1DLG_H__6FD220B0_BBA4_466A_A5BF_34DB72FB5F00__INCLUDED_)
