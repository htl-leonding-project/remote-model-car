 /**********************************************************
 *(c) by Knobloch GmbH
 *       Weedgasse 14
 *       D-55234 Erbes-Büdesheim                                    
 *
 *  Datei:          EducationLine-Konsole1.cpp:	Implementierungsdatei
 *												Beispielanwendung zur Verwendung der FtLib.Lib - Datei in MS-VC++ Ver 2005
 *                                  
 *												Es wird das "Erste" USB-Interface verwendet, das gefunden wurde und dessen 
 *												Motor 1 für 3 Sekunden eingeschaltet.
 *										
 *    
 *  Begonnen:       04.06.2010
 *  Letzte Änderung:04.06.2010
 *
 *  Version:        1.89
 *
 *  Revisionen:
 *          1.89:	04.06.2010
 *                  Begonnen
 ********************************************************************************/
#include <windows.h>
#include <iostream>

#include "stdafx.h"


#include "FtLibDemo.h"
#include "..\FtLib\Inc\FtLibDll.h"             // FtLib Header
#include "..\FtLib\Inc\FtLibDllFunc.h"         // FtLib Header mit DLL Imports


    DWORD       dwStatus,
                dwAnzDev;
    FT_HANDLE   hUsb;
    FT_TRANSFER_AREA* ftDCB;
    char        Stop;
    struct	    Interface	sIF;	    // Struktur für Interface-Steuerung



int _tmain(int argc, _TCHAR* argv[])
{

	dwStatus = LoadFtLibDll();      // DLL laden
    if (dwStatus == FTLIB_ERR_SUCCESS)
    {


    cout << "--- Konsole1 gestartet ---" << endl;
    cout << "Version : " << GetLibVersion() << endl;
    dwStatus = InitFtLib();
    cout << "Init : " << dwStatus << endl;
    dwStatus = InitFtUsbDeviceList();
    dwAnzDev = GetNumFtUsbDevice();
    hUsb = GetFtUsbDeviceHandle(0);

    cout << "DeviceTyp " <<GetFtDeviceTyp(hUsb) << endl;
    cout << "SerialNr " << GetFtSerialNrStrg(hUsb) << endl;
    cout << "OpenUSB " << OpenFtUsbDevice(hUsb) << endl;
    dwStatus = StartFtTransferArea(hUsb, NULL);
    if (dwStatus == FTLIB_ERR_SUCCESS)
    {
        ftDCB = GetFtTransferAreaAddress(hUsb);
        ftDCB->M_Main = 0x01;                   // Ausgang 1 einschalten
        ftDCB->MPWM_Main[0] = 0x07;             // mit PWM-Wert "7"
        Sleep(3000);                            // 3 Sek warten
        ftDCB->M_Main = 0x00;                   // Ausgang 1 ausschalten
        cout << "Fertig" << endl;
        Sleep(50);                              // 50ms warten, dass Ausgang auch geschaltet wird
        dwStatus = StopFtTransferArea(hUsb);    // Transfer stoppen
    }
    else
    {
        cout << "Fehler bei StartFtTransfer: " << dwStatus << endl;
    }
    dwStatus = CloseFtLib();
    cout << "Ende mit RETURN" << endl;
    cin.get(Stop);

    }

    return 0;
}




