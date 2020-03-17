 /**********************************************************
 *(c) by Knobloch GmbH
 *       Weedgasse 14
 *       D-55234 Erbes-Büdesheim                                    
 *
 *  Datei:          Konsole1.cpp :  Implementierungsdatei
 *                                  Beispielanwendung zur Verwendung der FtLib.Lib - Datei in MS-VC++ Ver. 6.0
 *                                  
 *                                  Es wird das "Erste" USB-Interface verwendet, das gefunden wurde und dessen 
 *                                  Motor 1 für 3 Sekunden eingeschaltet.
 *										
 *    
 *  Begonnen:       02.05.2005
 *  Letzte Änderung:15.05.2005
 *
 *  Version:        1.61
 *
 *  Revisionen:
 *          0.38:	Beginn (Version identisch zur Library-Version)
 *          0.60:   10. May 2006
 *                  Neuer Name: GetAnzFtUsbDevice()    --> GetNumFtUsbDevice()
 *                              ClearFtMessagePuffer() --> ClearFtMessageBuffer()
 *          0.61:   15. May 2006
 *                  Neuer Name: 1.61
 ********************************************************************************/


#include <windows.h>
#include <iostream.h>
#include "FtLib\Inc\FtLib.h"
 

    DWORD       dwStatus,
                dwAnzDev;
    FT_HANDLE   hUsb;
    FT_TRANSFER_AREA* ftDCB;
    char        Stop;



void main()
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