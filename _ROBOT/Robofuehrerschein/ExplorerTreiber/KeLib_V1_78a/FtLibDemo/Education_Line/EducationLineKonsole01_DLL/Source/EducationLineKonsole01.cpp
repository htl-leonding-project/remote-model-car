 /**********************************************************
 *(c) by Knobloch GmbH
 *       Weedgasse 14
 *       D-55234 Erbes-Büdesheim                                    
 *
 *  Datei:          EducationLine-Konsole01.cpp:    Implementierungsdatei
 *												    Beispielanwendung zur Verwendung der FtLib.Lib - Datei in MS-VC++ Ver 2005
 *                                  
 *                                                  Es wird das "Erste" USB-Interface verwendet, das gefunden wurde und dessen 
 *                                                  Motor 1 für 3 Sekunden eingeschaltet.
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
#include "stdafx.h"
#include <iostream.h>


#include "FtLibDemo.h"
#include "FtLib\Inc\FtLibDll.h"             // FtLib Header
#include "FtLib\Inc\FtLibDllFunc.h"         // FtLib Header mit DLL Imports



    DWORD       dwStatus,
                dwAnzDev,
                dwInput,
                dwX;
    FT_HANDLE   hUsb;
    FT_TRANSFER_AREA* ftDCB;
    bool        bStop;
    char        cStop;

    struct	    Interface	sIF;	    // Struktur für Interface-Steuerung


int main(int argc, char* argv[])
{
	printf("Testprogramm KeLib / FtLib \n");

	dwStatus = LoadFtLibDll();                                  // DLL laden | load DLL
    if (dwStatus == FTLIB_ERR_SUCCESS)
    {
        printf("Lib-Version:    %2d.%2d \n", (GetLibVersion() >> 8), (GetLibVersion() & 0xFF));
        dwStatus = InitFtLib();                                 // Init Lib
        if (dwStatus == FTLIB_ERR_SUCCESS)
        {
            dwStatus = InitFtUsbDeviceList();                   // Make USB-Device List
            if (dwStatus == FTLIB_ERR_SUCCESS)
            {
                dwAnzDev = GetNumFtUsbDevice();                 // Anzahl gefundener Devices auslesen | Read number of devices
                printf("Devices found: %3d \n", dwAnzDev);

                hUsb = GetFtUsbDeviceHandle(0);                 // Handle auf erstes Device | Get handle of first device
                printf("Devicetyp:     %3d \n", GetFtDeviceTyp(hUsb)); // Ausgeben des Devicetyp (s. FtLibDll.h) | Print devicetyp number (look at FtLibDll.h)

                dwStatus = OpenFtUsbDevice(hUsb);               // Open device


                // Nun 100 Blinker des Ausgangs "0" - Abbruch mit Eingang "1"
                // Now 100 flashes of Output "0" - Stop with Input "1"
                bStop = FALSE;
                for (dwX=0; (dwX < 100) && !bStop; dwX++)
                {   

                    // Usage:                    handle  dwData dwIndex dwOption = sofort ausgeben | write to device
                    //                                   Led ON
                    dwStatus = KE_WriteOutputByte (hUsb,  0x01,  0x00,   0x01);
                    if (dwStatus == FTLIB_ERR_SUCCESS)
                    {
                        Sleep(50);          

                        // Usage:                    handle  dwData dwIndex dwOption = sofort ausgeben | write to device
                        //                                  Led OFF
                        dwStatus = KE_WriteOutputByte (hUsb,  0x00,  0x00,   0x01);
                        if (dwStatus == FTLIB_ERR_SUCCESS)
                        {
                            Sleep(50);

                            dwInput = 0;
                            // Usage                   handle   pData   Index  option = digitale Eingänge neu einlesen | read digital inputs
                            dwStatus = KE_ReadInputByte(hUsb,  &dwInput,   0,   0x01);
                            if (dwStatus == FTLIB_ERR_SUCCESS)
                            {
                                if (dwInput)
                                {
                                    bStop = TRUE;
                                    printf("Key Pressed - STOP    Inputcode: 0x%2X\n", dwInput);
                                }
                            }
                        }
                    }

                    if (dwStatus != FTLIB_ERR_SUCCESS)
                    {
                        bStop = TRUE;
                        printf("ERROR - STOP \n");
                    }
                }   // for...
            }       // InitUsbDeviceList()
        }           // InitFtLib()

        if (dwStatus != FTLIB_ERR_SUCCESS)
        {
            printf("Error: %s - %s - (#%8X)\n", GetFtLibErrorString(dwStatus, 0), GetFtLibErrorString(dwStatus, 1), dwStatus );
        }

        dwStatus = CloseFtLib();
    }
    else
    {
	    printf("Fehler bei LoadFtLib() - Error with LoadFtLib()! \n");
    }

    printf("Ende mit RETURN | End with RETURN \n");
    cin.get(cStop);

	return 0;
}

