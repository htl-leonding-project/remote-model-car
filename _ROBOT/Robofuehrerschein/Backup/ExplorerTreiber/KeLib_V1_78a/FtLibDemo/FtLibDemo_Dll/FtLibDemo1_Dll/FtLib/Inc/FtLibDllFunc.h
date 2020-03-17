/*******************************************************************************  
 *  (c) by Knobloch GmbH
 *         Weedgasse 14
 *         D-55234 Erbes-Büdesheim                                    
 *
 *  Header:         FtLibDllFunc.h      Headerfile for fischertechnik Library
 *                                      Load DLL-Library 
 *
 *  Version:        0.60
 *  Date:           10. May 2006
 *
 *  Revision:
 *  0.60:   10. May 2006
 *          New Name: GetAnzFtUsbDevice()    --> GetNumFtUsbDevice()
 *                    ClearFtMessagePuffer() --> ClearFtMessageBuffer()
 *  1.74:   12.06.2009
 *          Support for new "education line" Modules from Knobloch GmbH: "CrossRoads / TrafficLights / Signal"
 *          04.10.2009
 *          Correct "SendFtMessage()"
 *          24.06.2010
 *          See Info about the LoadFtLibDll() if the Lib is not loaded
 ********************************************************************************/

    HINSTANCE hFtLibDLL;                // Handle to DLL

    typedef DWORD       (__stdcall *DLL_GetLibVersion) (void);
    typedef DWORD       (__stdcall *DLL_InitFtLib) (void);
    typedef DWORD       (__stdcall *DLL_CloseFtLib) (void);
    typedef DWORD       (__stdcall *DLL_IsFtLibInit) (void);
    typedef DWORD       (__stdcall *DLL_InitFtUsbDeviceList) (void);
    typedef UINT        (__stdcall *DLL_GetNumFtUsbDevice) (void);
    typedef FT_HANDLE   (__stdcall *DLL_GetFtUsbDeviceHandle) (UCHAR ucDevNr);
    typedef FT_HANDLE   (__stdcall *DLL_GetFtUsbDeviceHandleSerialNr) (DWORD dwSN, DWORD dwTyp);
    typedef DWORD       (__stdcall *DLL_OpenFtUsbDevice) (FT_HANDLE hFt);
    typedef FT_HANDLE   (__stdcall *DLL_OpenFtCommDevice) (DWORD dwPort, DWORD dwTyp, DWORD dwZyklus, DWORD *pdwError);
    typedef DWORD       (__stdcall *DLL_SetFtDeviceCommMode) (FT_HANDLE hFt, DWORD dwMode, DWORD dwParameter, USHORT *puiValue);
    typedef DWORD       (__stdcall *DLL_CloseAllFtDevices) (void);
    typedef DWORD       (__stdcall *DLL_CloseFtDevice) (FT_HANDLE hFt);
    typedef DWORD       (__stdcall *DLL_GetFtDeviceTyp) (FT_HANDLE hFt);
    typedef LPCSTR      (__stdcall *DLL_GetFtSerialNrStrg) (FT_HANDLE hFt);
    typedef DWORD       (__stdcall *DLL_GetFtSerialNr) (FT_HANDLE hFt);
    typedef LPCSTR      (__stdcall *DLL_GetFtFirmwareStrg) (FT_HANDLE hFt);
    typedef DWORD       (__stdcall *DLL_GetFtFirmware) (FT_HANDLE hFt);
    typedef LPCSTR      (__stdcall *DLL_GetFtManufacturerStrg) (FT_HANDLE hFt);
    typedef LPCSTR      (__stdcall *DLL_GetFtShortNameStrg) (FT_HANDLE hFt);
    typedef LPCSTR      (__stdcall *DLL_GetFtLongNameStrg) (FT_HANDLE hFt);
    typedef LPCSTR      (__stdcall *DLL_GetFtLibErrorString) (DWORD dwErrorCode, DWORD dwTyp);

    typedef DWORD       (__stdcall *DLL_GetFtDeviceSetting) (FT_HANDLE hFt, FT_SETTING *pSet);
    typedef DWORD       (__stdcall *DLL_SetFtDeviceSetting) (FT_HANDLE hFt, FT_SETTING *pSet);
    typedef DWORD       (__stdcall *DLL_SetFtDistanceSensorMode) (FT_HANDLE hFt, DWORD dwMode, DWORD dwTol1, DWORD dwTol2, 
                                                                  DWORD dwSchwell1, DWORD dwSchwell2, DWORD dwRepeat1, DWORD dwRepeat2);

    typedef DWORD       (__stdcall *DLL_StartFtTransferArea) (FT_HANDLE hFt, NOTIFICATION_EVENTS* sNEvent );
    typedef DWORD       (__stdcall *DLL_StartFtTransferAreaWithCommunication) (FT_HANDLE hFt, NOTIFICATION_EVENTS* sNEvent );
    typedef DWORD       (__stdcall *DLL_StopFtTransferArea) (FT_HANDLE hFt);
    typedef FT_TRANSFER_AREA* (__stdcall *DLL_GetFtTransferAreaAddress) (FT_HANDLE hFt);
    typedef DWORD       (__stdcall *DLL_IsFtTransferActiv) (FT_HANDLE hFt);
    typedef DWORD       (__stdcall *DLL_ResetFtTransfer)  (FT_HANDLE hFt);
    
    typedef DWORD       (__stdcall *DLL_GetFtMemoryLayout) (FT_HANDLE hFt, BYTE * pbArray, DWORD dwSize);
    typedef DWORD       (__stdcall *DLL_DownloadFtProgram) (FT_HANDLE hFt, DWORD dwMemBlock, BYTE* pbArray, DWORD dwSize, DWORD dwParameter, BYTE *pbName, DWORD dwNameLen);
    typedef DWORD       (__stdcall *DLL_StartFtProgram) (FT_HANDLE hFt, DWORD dwMemBlock);
    typedef DWORD       (__stdcall *DLL_StopFtProgram) (FT_HANDLE hFt);
    typedef DWORD       (__stdcall *DLL_DeleteFtProgram) (FT_HANDLE hFt, DWORD dwMemBlock);
    typedef DWORD       (__stdcall *DLL_SetFtProgramActiv) (FT_HANDLE hFt, DWORD dwMemBlock);
    typedef DWORD       (__stdcall *DLL_GetFtProgramName) (FT_HANDLE hFt, DWORD dwMemBlock, DWORD dwSize, LPVOID pName);
    typedef DWORD       (__stdcall *DLL_WriteFtMemoryData) (FT_HANDLE hFt, DWORD dwData, DWORD dwAddress);
    typedef DWORD       (__stdcall *DLL_GetFtMemoryData) (FT_HANDLE hFt, BYTE * pbArray, DWORD dwSize, DWORD dwAddress);

    typedef DWORD       (__stdcall *DLL_SendFtMessage) (FT_HANDLE hFt, BYTE bHwId, BYTE bSubId, DWORD dwMessage, DWORD dwWaitTime, DWORD dwOption); 
    typedef DWORD       (__stdcall *DLL_ClearFtMessageBuffer) (FT_HANDLE hFt);


    // education line
    typedef DWORD       (__stdcall *DLL_KE_WriteOutputByte) (FT_HANDLE hFt, DWORD dwData0, DWORD dwIndex, DWORD dwOption);
    typedef DWORD       (__stdcall *DLL_KE_ReadInputByte) (FT_HANDLE hFt, DWORD *pdwData0, DWORD dwIndex, DWORD dwOption);
    typedef DWORD       (__stdcall *DLL_KE_UpdateStructure) (FT_HANDLE hFt, KE_EL_IO_STRUCT *pStruc, DWORD dwOption);



    DLL_GetLibVersion                           GetLibVersion;
    DLL_InitFtLib                               InitFtLib;
    DLL_CloseFtLib                              CloseFtLib;
    DLL_IsFtLibInit                             IsFtLibInit;
    DLL_InitFtUsbDeviceList                     InitFtUsbDeviceList;
    DLL_GetNumFtUsbDevice                       GetNumFtUsbDevice;
    DLL_GetFtUsbDeviceHandle                    GetFtUsbDeviceHandle;
    DLL_GetFtUsbDeviceHandleSerialNr            GetFtUsbDeviceHandleSerialNr;
    DLL_OpenFtUsbDevice                         OpenFtUsbDevice;
    DLL_OpenFtCommDevice                        OpenFtCommDevice;
    DLL_SetFtDeviceCommMode                     SetFtDeviceCommMode;
    DLL_CloseAllFtDevices                       CloseAllFtDevices;
    DLL_CloseFtDevice                           CloseFtDevice;
    DLL_GetFtDeviceTyp                          GetFtDeviceTyp;
    DLL_GetFtSerialNrStrg                       GetFtSerialNrStrg;
    DLL_GetFtSerialNr                           GetFtSerialNr;
    DLL_GetFtFirmwareStrg                       GetFtFirmwareStrg;
    DLL_GetFtFirmware                           GetFtFirmware;
    DLL_GetFtManufacturerStrg                   GetFtManufacturerStrg;
    DLL_GetFtShortNameStrg                      GetFtShortNameStrg;
    DLL_GetFtLongNameStrg                       GetFtLongNameStrg;
    DLL_GetFtLibErrorString                     GetFtLibErrorString;
        
    DLL_GetFtDeviceSetting                      GetFtDeviceSetting;
    DLL_SetFtDeviceSetting                      SetFtDeviceSetting;
    DLL_SetFtDistanceSensorMode                 SetFtDistanceSensorMode;

    DLL_StartFtTransferArea                     StartFtTransferArea;
    DLL_StartFtTransferAreaWithCommunication    StartFtTransferAreaWithCommunication;
    DLL_StopFtTransferArea                      StopFtTransferArea;
    DLL_GetFtTransferAreaAddress                GetFtTransferAreaAddress;
    DLL_IsFtTransferActiv                       IsFtTransferActiv;
    DLL_ResetFtTransfer                         ResetFtTransfer;
            
    DLL_GetFtMemoryLayout                       GetFtMemoryLayout;
    DLL_DownloadFtProgram                       DownloadFtProgram;
    DLL_StartFtProgram                          StartFtProgram;
    DLL_StopFtProgram                           StopFtProgram;
    DLL_DeleteFtProgram                         DeleteFtProgram;
    DLL_SetFtProgramActiv                       SetFtProgramActiv;
    DLL_GetFtProgramName                        GetFtProgramName;
    DLL_WriteFtMemoryData                       WriteFtMemoryData;
    DLL_GetFtMemoryData                         GetFtMemoryData;

    DLL_SendFtMessage                           SendFtMessage;
    DLL_ClearFtMessageBuffer                    ClearFtMessageBuffer;


    // education line
    DLL_KE_WriteOutputByte                      KE_WriteOutputByte;
    DLL_KE_ReadInputByte                        KE_ReadInputByte;
    DLL_KE_UpdateStructure                      KE_UpdateStructure;



/********************************************************
 *  LoadFtLibDll
 *
 *  This function loads the FtLib-Dll
 *
 *  Calling:    ---
 *  Return:     DWORD 
 *              FTLIB_ERR_DLL_NOT_LOADABLE      Error: DLL not loadable
 *              FTLIB_ERR_SUCCESS               Success: no error
 *          
 ********************************************************/
DWORD LoadFtLibDll(void)
{
    DWORD   dwStatus;

    dwStatus = FTLIB_ERR_SUCCESS;
    hFtLibDLL = LoadLibrary("FtLib.DLL");       // use hFtLibDLL = LoadLibrary(L"FtLib.DLL");  on newer Visual Studio Versions
    if (hFtLibDLL != NULL)
    {
        GetLibVersion =             (DLL_GetLibVersion)            GetProcAddress(hFtLibDLL, "GetLibVersion");
        InitFtLib =                 (DLL_InitFtLib)                GetProcAddress(hFtLibDLL, "InitFtLib");
        CloseFtLib =                (DLL_CloseFtLib)               GetProcAddress(hFtLibDLL, "CloseFtLib");
        IsFtLibInit =               (DLL_IsFtLibInit)              GetProcAddress(hFtLibDLL, "IsFtLibInit");
        InitFtUsbDeviceList =       (DLL_InitFtUsbDeviceList)      GetProcAddress(hFtLibDLL, "InitFtUsbDeviceList");
        GetNumFtUsbDevice =         (DLL_GetNumFtUsbDevice)        GetProcAddress(hFtLibDLL, "GetNumFtUsbDevice");
        GetFtUsbDeviceHandle =      (DLL_GetFtUsbDeviceHandle)     GetProcAddress(hFtLibDLL, "GetFtUsbDeviceHandle");
        GetFtUsbDeviceHandleSerialNr = (DLL_GetFtUsbDeviceHandleSerialNr) GetProcAddress(hFtLibDLL, "GetFtUsbDeviceHandleSerialNr");
        OpenFtUsbDevice =           (DLL_OpenFtUsbDevice)          GetProcAddress(hFtLibDLL, "OpenFtUsbDevice");
        OpenFtCommDevice =          (DLL_OpenFtCommDevice)         GetProcAddress(hFtLibDLL, "OpenFtCommDevice");
        SetFtDeviceCommMode =       (DLL_SetFtDeviceCommMode)      GetProcAddress(hFtLibDLL, "SetFtDeviceCommMode"); 
        CloseAllFtDevices =         (DLL_CloseAllFtDevices)        GetProcAddress(hFtLibDLL, "CloseAllFtDevices");
        CloseFtDevice =             (DLL_CloseFtDevice)            GetProcAddress(hFtLibDLL, "CloseFtDevice");
        GetFtDeviceTyp =            (DLL_GetFtDeviceTyp)           GetProcAddress(hFtLibDLL, "GetFtDeviceTyp");
        GetFtSerialNrStrg =         (DLL_GetFtSerialNrStrg)        GetProcAddress(hFtLibDLL, "GetFtSerialNrStrg");
        GetFtSerialNr =             (DLL_GetFtSerialNr)            GetProcAddress(hFtLibDLL, "GetFtSerialNr");
        GetFtFirmwareStrg =         (DLL_GetFtFirmwareStrg)        GetProcAddress(hFtLibDLL, "GetFtFirmwareStrg");
        GetFtFirmware =             (DLL_GetFtFirmware)            GetProcAddress(hFtLibDLL, "GetFtFirmware");
        GetFtManufacturerStrg =     (DLL_GetFtManufacturerStrg)    GetProcAddress(hFtLibDLL, "GetFtManufacturerStrg");
        GetFtShortNameStrg =        (DLL_GetFtShortNameStrg)       GetProcAddress(hFtLibDLL, "GetFtShortNameStrg");
        GetFtLongNameStrg =         (DLL_GetFtLongNameStrg)        GetProcAddress(hFtLibDLL, "GetFtLongNameStrg");
        GetFtLibErrorString =       (DLL_GetFtLibErrorString)      GetProcAddress(hFtLibDLL, "GetFtLibErrorString");
        GetFtDeviceSetting =        (DLL_GetFtDeviceSetting)       GetProcAddress(hFtLibDLL, "GetFtDeviceSetting");
        SetFtDeviceSetting =        (DLL_SetFtDeviceSetting)       GetProcAddress(hFtLibDLL, "SetFtDeviceSetting");
        SetFtDistanceSensorMode =   (DLL_SetFtDistanceSensorMode)  GetProcAddress(hFtLibDLL, "SetFtDistanceSensorMode");

        StartFtTransferArea =       (DLL_StartFtTransferArea)      GetProcAddress(hFtLibDLL, "StartFtTransferArea");
        StartFtTransferAreaWithCommunication = (DLL_StartFtTransferAreaWithCommunication)     GetProcAddress(hFtLibDLL, "StartFtTransferAreaWithCommunication");
        StopFtTransferArea =        (DLL_StopFtTransferArea)       GetProcAddress(hFtLibDLL, "StopFtTransferArea");
        GetFtTransferAreaAddress =  (DLL_GetFtTransferAreaAddress) GetProcAddress(hFtLibDLL, "GetFtTransferAreaAddress");
        IsFtTransferActiv =         (DLL_IsFtTransferActiv)        GetProcAddress(hFtLibDLL, "IsFtTransferActiv");
        ResetFtTransfer =           (DLL_ResetFtTransfer)          GetProcAddress(hFtLibDLL, "ResetFtTransfer");
    
        GetFtMemoryLayout =         (DLL_GetFtMemoryLayout)        GetProcAddress(hFtLibDLL, "GetFtMemoryLayout");
        DownloadFtProgram =         (DLL_DownloadFtProgram)        GetProcAddress(hFtLibDLL, "DownloadFtProgram");
        StartFtProgram =            (DLL_StartFtProgram)           GetProcAddress(hFtLibDLL, "StartFtProgram");
        StopFtProgram =             (DLL_StopFtProgram)            GetProcAddress(hFtLibDLL, "StopFtProgram");
        DeleteFtProgram =           (DLL_DeleteFtProgram)          GetProcAddress(hFtLibDLL, "DeleteFtProgram");
        SetFtProgramActiv =         (DLL_SetFtProgramActiv)        GetProcAddress(hFtLibDLL, "SetFtProgramActiv");
        GetFtProgramName =          (DLL_GetFtProgramName)         GetProcAddress(hFtLibDLL, "GetFtProgramName");
        WriteFtMemoryData =         (DLL_WriteFtMemoryData)        GetProcAddress(hFtLibDLL, "WriteFtMemoryData");
        GetFtMemoryData =           (DLL_GetFtMemoryData)          GetProcAddress(hFtLibDLL, "GetFtMemoryData");

        SendFtMessage =             (DLL_SendFtMessage)            GetProcAddress(hFtLibDLL, "SendFtMessage");
        ClearFtMessageBuffer =      (DLL_ClearFtMessageBuffer)     GetProcAddress(hFtLibDLL, "ClearFtMessageBuffer");

        // education line
        KE_WriteOutputByte =        (DLL_KE_WriteOutputByte)       GetProcAddress(hFtLibDLL, "KE_WriteOutputByte");
        KE_ReadInputByte =          (DLL_KE_ReadInputByte)         GetProcAddress(hFtLibDLL, "KE_ReadInputByte");
        KE_UpdateStructure =        (DLL_KE_UpdateStructure)       GetProcAddress(hFtLibDLL, "KE_UpdateStructure");
    }
    else
    {
        FreeLibrary(hFtLibDLL);
        dwStatus = FTLIB_ERR_DLL_NOT_LOADABLE;
    }

    return dwStatus;
}



/********************************************************
 *  UnloadFtLibDll
 *
 *  This Function kills the Library
 *
 *  Aufruf: ---
 *  Return: DWORD 
 *          0       Fehler, GetLastError() verwenden für Fehlercode
 *          >0      kein Fehler
 *          
 ********************************************************/
DWORD UnloadFtLibDll(void)
{
    DWORD   dwStatus;

    dwStatus = FreeLibrary(hFtLibDLL);
    hFtLibDLL = NULL;
    return (dwStatus);
}






