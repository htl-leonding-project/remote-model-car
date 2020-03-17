/**********************************************************
 *(c) by Knobloch GmbH
 *       Weedgasse 14
 *       D-55234 Erbes-Büdesheim                                    
 *
 *  File:           FtLibDemo.h         Header for Demo-Programm
 *										
 *    
 *  Start:          30.04.2005
 *  Last Change:    28.09.2006
 *
 *
 *  Version:        1.62
 *
 *  Revisionen:
 *  0.38:	Start
 *  0.56:   08. Feb. 2006
 *          - New: Interface Voltage
 *  1.61:   15. May 2006
 *          - New Name: 01.61
 *  1.62:   28. September 2006
 *          - Changing SetFtDistanceSensorMode() Function in this Demo
 **********************************************************/

#ifndef     IF3_DIAG_H
#define     IF3_DIAG_H


    #ifndef     _FT_USB_LIB_H_
        #include "FtLib\Inc\FtLibDll.h"     // FtLib Header
    #endif


    #define		DSW_VER1		1			// Versionsnummer der Software X.
    #define		DSW_VER2		62			// Versionsnummer der Software  .Y




    #define     USB_ARRAY_SIZE                  150     // Array Size for some Functions
    #define     GET_MEMORY_LAYOUT_ARRAY_SIZE    30



// eigene Konstanten
#define	SB_VMIN				1			// MIN-Teilungspunkt des Schiebers
#define	SB_VMAX				8			// MAX-Teilungspunkt des Schiebers
#define	SB_VINIT			0			// Stellung des Schiebers beim Starten des Programms (0 in Windows = max bei ft)
#define	SB_PAGE				1			// Scrollbar: Breite des Schiebers
#define	MAX_ANALOGWERT	 1023			// Analoge gehen von 0..1023


#define	SS_NIX				0			// Schnittstelle: nix
#define	SS_USB				1			// Schnittstelle: USB
#define	SS_SER				2			// Schnittstelle: Seriell



#define RADIO_AUS                   0
#define RADIO_ROBO                  1
#define RADIO_IIF                   2



#define	IF_TIMEOUT_WERT		80			// 8sek TimeOut Anzahl "100ms" Timer Ticks warten auf Antwort vom Interface (2sek, da Block löschen lange dauert!)
#define	ANZ_IOPUFFER		250			// Größe des Sende- / Empfangspuffers

#define RB_NIX				0			// Button "keine Schnittstelle gewählt"
#define RB_USB				1			// Button USB
#define RB_SER_COM1			2			// Button COM1 
#define RB_SER_COM2			3			// Button COM2 
#define RB_SER_COM3			4			// Button COM3 
#define RB_SER_COM4			5			// Button COM4 

#define RAB_INTELLIGENT_IF              0   // Button Interface-Typ: Intelligent Interface (nur seriell)
#define RAB_INTELLIGENT_IF_EXTENSION    1   // Button Interface-Typ: Intelligent Interface mit Extension
#define RAB_ROBO_IF                     2   // Button: Robo-IF (bur seriell)

#define RAB_DS_VOLT         0
#define RAB_DS_DISTANZ      1



inline int Max(int a, int b) {return a>b ? a:b;}	// Makro
inline int Min(int a, int b) {return a>b ? b:a;}	// Makro

void BerechneGeschwindigkeit(void);




struct	Interface 
{

    DWORD               dwIfTyp;        // Interface Typ ausgewählt
    DWORD               dwPort;         // Port ausgewählt
    DWORD               dwComTyp;       // Typ des seriellen Device

    UINT	            uiUsbDev;		// Nummer des ausgewählten USB-Device (0..Device)
    FT_HANDLE           hFt;            // Handle des aktiven Device (NULL = kein Device aktiv)
    FT_TRANSFER_AREA*   pTransArea;     // Zeiger auf Transfer Area
    BOOL                bExtTestIsRunning;  // 1 = TimerRoutine vom Hauptfenster aktualisiert nicht, da Extension Test läuft


	ULONG	ulSerialNumber;		// Seriennummer des Interface
	UCHAR	ucSNok;				// TRUE = SN gesetzt

	BYTE	bCTimeOut;			// TimeOut Counter

	BYTE	bVerBLL;	  	    // L-Teil der Bootloader Versionsnummer
	BYTE	bVerBLH;	  	    // H-Teil der Bootloader Versionsnummer
	BYTE	bVerFWL;	  	    // L-Teil der Firmware Versionsnummer
	BYTE	bVerFWH;	  	    // H-Teil der Firmware Versionsnummer

	BYTE	bOut0;				// Zustand Ausgang MASTER
	BYTE	baOut0VS[12+1];		// Array speichert Zustand der "Schieber" für Ausgang 1..8 und M1..M4
								// 0: frei; 1..8 = Ausgänge; 9..12 = M1..M4
	BYTE    baOut0V[3];			// 3 Byte mit Geschwindigkeitsinfos für die Ausgänge: 88877766 65554443 33222111


	BYTE	bIn0;				// Zustand Eingang MASTER
	BYTE	bIn1;				// Zustand Eingang SLAVE1
	BYTE	bIn2;				// Zustand Eingang SLAVE2
	BYTE	bIn3;				// Zustand Eingang SLAVE3
	BYTE	bIn4;				// Zustand Eingang SLAVE4
	BYTE	bIn5;				// Zustand Eingang SLAVE5
	BYTE	bIn6;				// Zustand Eingang SLAVE6
	BYTE	bIn7;				// Zustand Eingang SLAVE7

	UINT	uiA01;				// Zustand Analogeingang 1
	UINT	uiA02;				// Zustand Analogeingang 2
	UINT	uiA0X;				// Zustand Analogeingang AX
	UINT	uiA0Y;				// Zustand Analogeingang AY
	UINT	uiA0Z;				// Zustand Analogeingang Z (auf 26er Steckerleiste)
	UINT	uiD1;				// Zustand Distanzsensor 1
	UINT	uiD2;				// Zustand Distanzsensor 2
	UINT	uiVers;				// Zustand Versorgungsspannung


                                // Variablen für Distanzsensorbetrieb
    DWORD   dwDistanzMode;
    DWORD   dwDsTol1;           // Toleranz 1
    DWORD   dwDsTol2;           // Toleranz 2
    DWORD   dwDsRep1;           // Repeatwert 1
    DWORD   dwDsRep2;           // Repeatwert 2
    DWORD   dwDsSchwelle1;      // Schaltschwelle 1
    DWORD   dwDsSchwelle2;      // Schaltschwelle 2


};



void BerechnePWM(void);

#endif