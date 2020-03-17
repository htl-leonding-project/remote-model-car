/*******************************************************************************  
 *  (c) by Knobloch GmbH
 *         Weedgasse 14
 *         D-55234 Erbes-Büdesheim                                    
 *
 *  Header:         FtLib.h          Headerfile for fischertechnik USB-Library
 *
 *  Version:        1.78
 *  Date:           10. August 2010
 *
 *  Revision:
 *  1.60:   10. May 2006
 *          New Name: GetAnzFtUsbDevice()    --> GetNumFtUsbDevice()
 *                    ClearFtMessagePuffer() --> ClearFtMessageBuffer()
 *  1.62:   11. June 2006
 *          New Error-Code: FTLIB_ERR_IF_FW_OLD1
 *          Integration "Robo-Connect-Box" (www.knobloch-gmbh.de) 
 *  1.63:   07.10.2006
 *          Changing FT_SETTING - Structure
 *  1.64:   04.11.2006
 *          Changing Distance-Values
 *  1.65:   01.12.2006
 *          More Robo-Connect-Boc support / changing FT_SETTING
 *  1.66:   18.08.2007
 *          Support for new Sensors: New: IF_DS_INPUT_ULTRASONIC
 *                          and changing: IF_DS_INPUT_DISTANCE from value "1" to "3"
 *  1.74:   12.06.2009
 *          Support for new "education line" Modules from Knobloch GmbH: "CrossRoads / TrafficLights / Signal"
 *  1.75:   23.04.2010
 *          Support for ROBO LT Controller
 *  1.77:   04.06.2010
 *          Support for x32 and x64 Windows Systems
 *  1.78:   10.08.2010
 *          Support for easy pH 
 ********************************************************************************/

#ifndef _FT_LIBRARY_H_
#define _FT_LIBRARY_H_ 


    // Communication Area for ft-Device
typedef struct _FT_TRANSFER_AREA
{
    // Digital Inputs Main Module
    // Base+0x00: | E8 | E7 | E6 | E5 | E4 | E3 | E2 | E1 |
    unsigned char E_Main;

    // Digital Inputs Extension Modules 1..3
    // Base+0x01: | E16| E15| E14| E13| E12| E11| E10| E9 |
    unsigned char E_Sub1;
    // Base+0x02: | E24| E23| E22| E21| E20| E19| E18| E17|
    unsigned char E_Sub2;
    // Base+0x03: | E32| E31| E30| E29| E28| E27| E26| E25|
    unsigned char E_Sub3;

    // Reserved
    // Base+0x04..0x0B
    unsigned char rsvd1[8];

    // Abstandsensoren (1=detektiert)
    // Base+0x0C: |  0 |  0 |  0 |  0 |  0 |  0 | D2 | D1 |
    unsigned char Distance;

    // Base+0x0D: reserved
    unsigned char rsvd2;

    // IR-Receiver input code 
    // Base+0x0E: | 0 | 0 | 0 | C | T | T | T | T
    // C = Code: 0 = Code 1 active, 1 = Code 2 active
    // TTTT = Keycode 0..11
    // Arangement of keys on Transmitter
    //   1        8
    //   2     7
    //   3          10
    //   4      9
    //   5        11
    //   6
    // Taste 1 = M3 right
    // Taste 2 = M3 left
    // Taste 3 = Speed. M1
    // Taste 4 = Speed. M2
    // Taste 5 = Speed. M3
    // Taste 6 = Code 2
    // Taste 7 = M1 backward
    // Taste 8 = M1 forward
    // Taste 9 = M2 left
    // Taste 10 = M2 right
    // Taste 11 = Code 1
    unsigned char IRKeys;

    // Base+0x0F: | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
    unsigned char res_1;

    // Analoginputs of main module
    // 8x 16 Bit, Range 0..1023, L:H Format (intel) )
    // Base+0x10..0x11: AX (Master Modul)
    unsigned short AX;
    // Base+0x12..0x13: AY (Master Modul)
    unsigned short AY;
    // Base+0x14..0x15: A1 (Master Modul)
    unsigned short A1;
    // Base+0x16..0x17: A2 (Master Modul)
    unsigned short A2;
    // Base+0x18..0x19: AZ (Master Modul, vom SLAVE-Modul-BUS)
    unsigned short AZ;
    // Base+0x1A..0x1B: AV (Versorgungsspannung Master Modul)
    unsigned short AV;
    // Base+0x1C..0x1D: D1 (Abstandssensor 1)
    unsigned short D1;
    // Base+0x1E..0x1F: D2 (Abstandssensor 2)
    unsigned short D2;

    // Analoginputs of slave modules 1..3 
    // Base+0x20..0x21: AX (Slave 1 Modul)
    unsigned short AXS1;
    // Base+0x22..0x23: AX (Slave 2 Modul)
    unsigned short AXS2;
    // Base+0x24..0x25: AX (Slave 3 Modul)
    unsigned short AXS3;

    // Detection limit for distance sensors ( to generate digital from analog input )
    // Base+0x26..0x27: DS1
    unsigned short DS1;
    // Base+0x28..0x29: DS2
    unsigned short DS2;

    // Reserved
    // Base+0x2A..0x2B
    unsigned short ZE;

    // Reserved
    // Base+0x2C..0x2F
    unsigned char rsvd3[4];

    // 16-Bit Timers
    // Base+0x30..0x31: Timer 1ms Inkrement
    unsigned short Timer1ms;
    // Base+0x32..0x33: Timer 10ms Inkrement
    unsigned short Timer10ms;
    // Base+0x34..0x35: Timer 100ms Inkrement
    unsigned short Timer100ms;
    // Base+0x36..0x37: Timer 1s Inkrement
    unsigned short Timer1s;
    // Base+0x38..0x39: Timer 10s Inkrement
    unsigned short Timer10s;
    // Base+0x3A..0x3B: Timer 1min Inkrement
    unsigned short Timer1min;

    // Reserved
    // Base+0x3C..0x3D
    unsigned short res_bF;
    // Base+0x3E
    unsigned char res_bT;

    // Reserved
    // Base+0x3F
    unsigned char rsvd4[1];

    // Outputs of the main module ( polarity )
    // Base+0x40: |M4B |M4A |M3B |M3A |M2B |M2A |M1B |M1A |
    // Outputs of extension modules
    unsigned char M_Main;
    // Base+0x41: |M8B |M8A |M7B |M7A |M6B |M6A |M5B |M5A |
    unsigned char M_Sub1;
    // Base+0x42: |M12B|M12A|M11B|M11A|M10B|M10A|M9B |M9A |
    unsigned char M_Sub2;
    // Base+0x43: |M16B|M16A|M15B|M15A|M14B|M14A|M13B|M13A|
    unsigned char M_Sub3;

    // Reserved
    // Base+0x44..0x47
    unsigned char rsvd5[4];

    // Outputs of the main module ( energy saver mode )
    // 1 = energy saver mode, 0 = operational, PowerUp = 1
    // Base+0x48: | 0  | 0  | 0  | 0  | M4 | M3 | M2 | M1 |
    unsigned char MES_Main;
    // Outputs of extension modules 1..3
    // Base+0x49: | 0  | 0  | 0  | 0  | M8 | M7 | M6 | M5 |
    unsigned char MES_Sub1;
    // Base+0x4A: | 0  | 0  | 0  | 0  | M12| M11| M10| M9 |
    unsigned char MES_Sub2;
    // Base+0x4B: | 0  | 0  | 0  | 0  | M16| M15| M14| M13|
    unsigned char MES_Sub3;

    // Reserved
    // Base+0x4C
    unsigned char rsvd6[1];

    // Reserved
    // Base+0x4D:
    unsigned char reserved_l1;
    // Reserved
    // Base+0x4E: 
    unsigned char reserved_l2;
    // Reserved
    // Base+0x4F: 
    unsigned char reserved_l3;

    // Outputs of the main module (PWM values, range =0..7)
    // Base+0x50: M1A
    // Base+0x51: M1B
    // Base+0x52: M2A
    // Base+0x53: M2B
    // Base+0x54: M3A
    // Base+0x55: M3B
    // Base+0x56: M4A
    // Base+0x57: M4B
    unsigned char MPWM_Main[8];

    // Outputs of slave module 1 (PWM values, range =0..7)
    // Base+0x58: M5A
    // Base+0x59: M5B
    // Base+0x5A: M6A
    // Base+0x5B: M6B
    // Base+0x5C: M7A
    // Base+0x5D: M7B
    // Base+0x5E: M8A
    // Base+0x5F: M8B
    unsigned char MPWM_Sub1[8];

    // Outputs of slave module 2 (PWM values, range =0..7)
    // Base+0x60: M9A
    // Base+0x61: M9B
    // Base+0x62: M10A
    // Base+0x63: M10B
    // Base+0x64: M11A
    // Base+0x65: M11B
    // Base+0x66: M12A
    // Base+0x67: M12B
    unsigned char MPWM_Sub2[8];

    // Outputs of slave module 3 (PWM values, range =0..7)
    // Base+0x68: M13A
    // Base+0x69: M13B
    // Base+0x6A: M14A
    // Base+0x6B: M14B
    // Base+0x6C: M15A
    // Base+0x6D: M15B
    // Base+0x6E: M16A
    // Base+0x6F: M16B
    unsigned char MPWM_Sub3[8];

    // Reserved
    // Base+0x70..0x8F
    unsigned char rsvd7[32];


    // Analoginputs of slave modules 1..3 (Update-Time: 20ms)
    // Base+0x90..0x91: A1 (Slave 1 Modul)
    unsigned short A1S1;
    // Base+0x92..0x93: A1 (Slave 2 Modul)
    unsigned short A1S2;
    // Base+0x94..0x95: A1 (Slave 3 Modul)
    unsigned short A1S3;

    // Analoginputs of slave modules 1..3 (Update-Time: 20ms)
    // Base+0x96..0x97: AV (Slave 1 Modul)
    unsigned short AVS1;
    // Base+0x98..0x99: AV (Slave 2 Modul)
    unsigned short AVS2;
    // Base+0x9A..0x9B: AV (Slave 3 Modul)
    unsigned short AVS3;

    // Reserved
    // Base+0x9C..0x9F
    unsigned char rsvd8[4];

    // Reserved
    // Base+0xA0..0xA1: AX (Interface) Resistor-Value (0..5662 Ohm)
    unsigned short AX_R;

    // Base+0xA2..0xA3: AY (Interface) Resistor-Value (0..5662 Ohm)
    unsigned short AY_R;

    // Base+0xA4..0xA5: AX (Slave 1 Modul) Resistor-Value (0..5662 Ohm)
    unsigned short AXS1_R;

    // Base+0xA6..0xA7: AX (Slave 2 Modul) Resistor-Value (0..5662 Ohm)
    unsigned short AXS2_R;

    // Base+0xA8..0xA9: AX (Slave 3 Modul) Resistor-Value (0..5662 Ohm)
    unsigned short AXS3_R;

    // Reserved
    // Base+0xAA..0xDF
    unsigned char rsvd10[54];
 

    // Operation mode 
    // Base+0xE0: 0x00=online, 0x01=binary download
    unsigned char Mode;

    // Output PWM update (0x01=always, 0x02=once)
    // Base+0xE1: | 0  | 0  | 0  | 0  | 0  | 0  |ONCE|ALWA|
    unsigned char MPWM_Update;

    // Base+0xE2
    // 0 = Transfer Area closed
    // 1 = Transfer Area is working (Library Thread is running)
    unsigned char TransferAktiv;

    // Reserved
    // Base+0xE3..0xE5

    unsigned char rsvd11[3];

    // I/O Extension modules connected
    // Base+0xE6: | 0  | 0  | 0  | 0  | 0  | S2 | S1 | S0 |
    // S2..S0 = Number of connected I/O Extension Modules
    unsigned char BusModules;

    // Slot 1 connected extension module type
    // Base+0xE7: ?
    unsigned char SlotModule1;

    // Slot 2 connected extension module type
    // Base+0xE8: ?
    unsigned char SlotModule2;

    // Reserved
    // Base+0xE9..0xEF
    unsigned char rsvd12[7];


    // Change Bytes
    // 1 = EG (Master or Slave 1..3) have changed
    // The Application must read and change this byte to "0"
    // Use the Windows InterlockedExchange() Function for reading and writing at the same time!
    // Base+0xF0: 
    unsigned char ChangeEg;

    // 1 = Analog Inputs (Master AX, AY, A1, A2, AV, AZ or Extension 1..3 AX,AY,AV) 
    // or RfPower, RfError have changed
    // The Application must read and change this byte to "0"
    // Use the Windows InterlockedExchange() Function for reading and writing at the same time!
    // Base+0xF1: 
    unsigned char ChangeAn;

    // 1 = Infrared Input (Robo-IF) or RfStatus have changed
    // The Application must read and change this byte to "0"
    // Use the Windows InterlockedExchange() Function for reading and writing at the same time!
    // Base+0xF2: 
    unsigned char ChangeIr;


    // Reserved
    // Base+0xF3..0xFF
    unsigned char rsvd13[13];


    // Digital inputs as 16 bit values
    // Base+0x100..0x101  Input 1 (Master-Modul)
    // Base+0x102..0x103  Input 2 (Master-Modul)
    // Base+0x104..0x105  Input 3 (Master-Modul)
    // Base+0x106..0x107  Input 4 (Master-Modul)
    // Base+0x108..0x109  Input 5 (Master-Modul)
    // Base+0x10A..0x10B  Input 6 (Master-Modul)
    // Base+0x10C..0x10D  Input 7 (Master-Modul)
    // Base+0x10E..0x10F  Input 8 (Master-Modul)
    unsigned short E16_Main[8];
    // Base+0x110..0x111  Input 9 (Slave1-Modul)
    // Base+0x112..0x113  Input 10 (Slave1-Modul)
    // Base+0x114..0x115  Input 11 (Slave1-Modul)
    // Base+0x116..0x117  Input 12 (Slave1-Modul)
    // Base+0x118..0x119  Input 13 (Slave1-Modul)
    // Base+0x11A..0x11B  Input 14 (Slave1-Modul)
    // Base+0x11C..0x11D  Input 15 (Slave1-Modul)
    // Base+0x11E..0x11F  Input 16 (Slave1-Modul)
    unsigned short E16_Sub1[8];
    // Base+0x120..0x121  Input 17 (Slave2-Modul)
    // Base+0x122..0x123  Input 18 (Slave2-Modul)
    // Base+0x124..0x125  Input 19 (Slave2-Modul)
    // Base+0x126..0x127  Input 20 (Slave2-Modul)
    // Base+0x128..0x129  Input 21 (Slave2-Modul)
    // Base+0x12A..0x12B  Input 22 (Slave2-Modul)
    // Base+0x12C..0x12D  Input 23 (Slave2-Modul)
    // Base+0x12E..0x12F  Input 24 (Slave2-Modul)
    unsigned short E16_Sub2[8];
    // Base+0x130..0x131  Input 25 (Slave3-Modul)
    // Base+0x132..0x133  Input 26 (Slave3-Modul)
    // Base+0x134..0x135  Input 27 (Slave3-Modul)
    // Base+0x136..0x137  Input 28 (Slave3-Modul)
    // Base+0x138..0x139  Input 29 (Slave3-Modul)
    // Base+0x13A..0x13B  Input 30 (Slave3-Modul)
    // Base+0x13C..0x13D  Input 31 (Slave3-Modul)
    // Base+0x13E..0x13F  Input 32 (Slave3-Modul)
    unsigned short E16_Sub3[8];
    // Base+0x140..0x141  Distance sensor D1 (Master-Modul)
    // Base+0x142..0x143  Distance sensor D2 (Master-Modul)
    unsigned short Distance16[2];

    // Reserved
    // Base+0x144..0x14F
    unsigned char rsvd14[12];
 
    // IR-Keys as 16 bit values (independent of code)
    // Base+0x150..0x151  IR Taste  1 (M3R)
    // Base+0x152..0x153  IR Taste  2 (M3L)
    // Base+0x154..0x155  IR Taste  3 (M1)
    // Base+0x156..0x157  IR Taste  4 (M2)
    // Base+0x158..0x159  IR Taste  5 (M3)
    // Base+0x15A..0x15B  IR Taste  6 (Code2)
    // Base+0x15C..0x15D  IR Taste  7 (M1BW)
    // Base+0x15E..0x15F  IR Taste  8 (M1FW)
    // Base+0x160..0x161  IR Taste  9 (M2L)
    // Base+0x162..0x163  IR Taste 10 (M2R)
    // Base+0x164..0x165  IR Taste 11 (Code1)
    unsigned short IRKeys16[11];
    // Reserved
    // Base+0x166..0x16F
    unsigned char rsvd15[10];

    // IR-Keys as 16 bit values (code 1)
    // Base+0x170..0x171  IR Taste  1 (M3R)    Code1
    // Base+0x172..0x173  IR Taste  2 (M3L)    Code1
    // Base+0x174..0x175  IR Taste  3 (M1)     Code1
    // Base+0x176..0x177  IR Taste  4 (M2)     Code1
    // Base+0x178..0x179  IR Taste  5 (M3)     Code1
    // Base+0x17A..0x17B  always 0
    // Base+0x17C..0x17D  IR Taste  7 (M1BW)   Code1
    // Base+0x17E..0x17F  IR Taste  8 (M1FW)   Code1
    // Base+0x180..0x181  IR Taste  9 (M2L)    Code1
    // Base+0x182..0x183  IR Taste 10 (M2R)    Code1
    // Base+0x184..0x185  IR Taste 11 (Code1)  Code1 
    unsigned short IRKeys16Code1[11];

    // Reserved
    // Base+0x186..0x18F
    unsigned char rsvd16[10];
 
    // IR-Keys as 16 bit values (code 2)
    // Base+0x190..0x191  IR Taste  1 (M3R)    Code2
    // Base+0x192..0x193  IR Taste  2 (M3L)    Code2
    // Base+0x194..0x195  IR Taste  3 (M1)     Code2
    // Base+0x196..0x197  IR Taste  4 (M2)     Code2
    // Base+0x198..0x199  IR Taste  5 (M3)     Code2
    // Base+0x19A..0x19B  IR Taste  6 (Code2)  Code2 
    // Base+0x19C..0x19D  IR Taste  7 (M1BW)   Code2
    // Base+0x19E..0x19F  IR Taste  8 (M1FW)   Code2
    // Base+0x1A0..0x1A1  IR Taste  9 (M2LE)   Code2
    // Base+0x1A2..0x1A3  IR Taste 10 (M2RI)   Code2
    // Base+0x1A4..0x1A5  always 0
    unsigned short IRKeys16Code2[11];

    // Reserved
    // Base+0x1A6..0x1AF
    unsigned char rsvd17[10];

    
    // Base+0x1B0..0x1B1
    unsigned short RfStatus;
    // 1 = RfError (0x1B4..0x1B5) is > 25. We think, Rf connection (only Onlinemodus) is lost 

    // Base+0x1B2..0x1B3
    unsigned short RfPower;
    // Signal Power of the RF Signal entering the RF input (only Onlinemodus, 7 bit, 0..127)  


    // Base+0x1B4..0x1B5
    unsigned short RfError;
    // Rf-Error Count (0..250)  


    // Base+0x1B6..0x1B7
    unsigned short MsgNumInBuffer;
    // Number of Messages inside the Buffer


    // Base+0x1B8..0x1B9
    // Number of Interface-RF-Modul if installed or "-1" if not installed
    unsigned short RfModulNr;


    // Reserved
    // Base+0x1BA..0x1BB
    unsigned char rsvd19[2];


    // Reserved for Internal Use
    // Base+0x1BC..0x1BF
    DWORD dwTC;


    // Reserved
    // Base+0x1C0..0x1FF
    unsigned char rsvd20[64];

} FT_TRANSFER_AREA;

                                                // Numbers from GetFtDeviceTyp()
#define     NO_FT_DEVICE                0       // No ft Device connected
#define     FT_AUTO_TYPE                1       // Search for Device
#define     FT_INTELLIGENT_IF           10      // FT-Intelligent Interface connect (serial)
#define     FT_INTELLIGENT_IF_SLAVE     20      // FT-Intelligent Interface with Extension connect (serial)
#define     FT_ROBO_IF_IIM              50      // FT-Robo Interface with Intelligent-Interface-Modus connect (serial)
#define     FT_ROBO_IF_USB              60      // FT-Robo Interface connect with USB-Port
#define     FT_ROBO_IF_COM              70      // FT-Robo Interface connect with COM- (serial-) Port
#define     FT_ROBO_IF_OVER_RF          80      // FT-Robo Interface connect over RF-Data-Link
#define     FT_ROBO_IO_EXTENSION        90      // FT-Robo I/O-Extension
#define     FT_ROBO_LT_CONTROLLER       91      // FT-Robo LT Controller
#define     FT_ROBO_RF_DATA_LINK        110     // FT-Robo RF Data Link
#define     FT_SOUND_AND_LIGHTS         120     // FT-Sound + Lights Module
#define     ROBO_CONNECT_BOX            200     // Robo-Connect-Box (USB-Product for old Interfaces with parallel- or serial- port)
#define     EDU_LINE_MODULE             300     // education line module
#define     EDU_LINE_CROSSROADS         301     // education line - Module: CrossRoads      (www.knobloch-gmbh.de)
#define     EDU_LINE_TRAFFICLIGHTS      302     // education line - Module: Trafic Lights
#define     EDU_LINE_SIGNAL             303     // education line - Module: Signal
#define     EDU_LINE_EASY_PH            304     // education line - Module: easy pH 
#define     EDU_LINE_LIFT_01            305     // education line - Module: Lift (Aufzug)
#define     FT_MAX_TYP_NUMBER           999     // Max Typ Number

                                                // Numbers for dwIfSubType (_FT_SETTING) 
                                                // from the Robo-Connect-Box (RCB)
#define     MULTIFACE_IF_X60            2       // Multiface-Interface (Knobloch GmbH) Type: MF160 / MF260
#define     MULTIFACE_IF_7X             3       // Multiface-Interface (Knobloch GmbH) Txpe: MF7x
#define     MULTIFACE_IF_X50            4       // Multiface-Interface (Knobloch GmbH) Type: MF150 (Box 8) / MF250
#define     HIBS_IF                     8       // Hibs-Interface (Knobloch GmbH)
#define     FT_UNIVERSAL_IF             9       // FT-Universal Interface connect
#define     FT_INTELLIGENT_IF           10      // FT-Intelligent Interface connect (connect on RCB-serial Port)

#define     RCB_IF_SEARCH               0       // Searching for known Interfaces at Power On
#define     RCB_IF_SEARCH_OR_FIX        1       // Searching, if nothig found, than use defined type
#define     RCB_IF_FIX                  2       // Nothing to search, the used Interfacetype is defined



#define     FT_ANALOG_CYCLE             5       // Standard: 5*Read Digital Inputs, then EX, EY
                                                // Only for old Intelligent Interface { for OpenFtCommDevice() }


#define     PORT_NONE                   0
#define     PORT_COM                    1       // Standard: COM1
#define     PORT_COM1                   1
#define     PORT_COM2                   2
#define     PORT_COM3                   3
#define     PORT_COM4                   4
#define     PORT_USB                    50

                                                // Moduletypes for Robo Interface
#define     MODULE_NOT_INSTALLED        0       // Not installed
#define     MODULE_RF1                  1       // RF Data Link Module is installed


#define     LEN_STRG1                   30      // Length of SN / FW Strings
#define     LEN_STRG2                   255     // Length of Name-Strigs
#define     ANZ_DISTANCE_TYPES          2       // Number of supported Distance-Modes
#define     LEN_DIST_TYPE_NAMES         30      // Lenght of Mode-Names
#define     LEN_DIST_VAR_NAMES          20      // Lenght of Variable-Names
#define     NAME_LEN                    85      // Lenght of Prog-Names


#define     MEM_FLASH1                  0       // Use Memory FLASH-1 Block
#define     MEM_FLASH2                  1       // Use Memory FLASH-2 Block
#define     MEM_RAM                     2       // Use Memory RAM Block
#define     MEM_NO_ACCESS               -1      // No Memory Select (for SetFtProgramActiv() )
#define     DOWNLOAD_PROG_NAMELEN       80      // Max. 80 characters/bytes for the programname

                                                // Values for "dwParameter" from DownloadFtProgram() 
#define     PROG_TYP_NORMAL             1       // Program can bei Start with Software and Switch
#define     PROG_TYP_AUTOSTART          2       // Program is startable at Power-On


                                                // COM-Modes for SetFtDeviceCommMode()
#define     IF_COM_ONLINE               1       // Online Mode
#define     IF_COM_MESSAGE              3       // Messagemode
#define     IF_COM_DATA                 4       // Datatransfer
#define     IF_COM_PARAMETER            5       // Get Mode


                                                // Message-System
#define     MSG_HWID_SELF               0       // Message for himself
#define     MSG_HWID_SER                1       // Message for the Robo-Interface serial port
#define     MSG_HWID_RF                 2       // Message for other Interfaces (over RF)
#define     MSG_HWID_RF_SELF            3       // Message for other Interfaces (over RF) and for himself (back over RF)

#define     MSG_BUFF_SER                1       // SER-Messagebuffer (for ClearRfMessage() )
#define     MSG_BUFF_RF                 2       // RF-Messagebuffer (for ClearRfMessage() )
#define     MSG_BUFF_SELF               4       // SELF-Messagebuffer (for ClearRfMessage() )

#define     MSG_SEND_NORMAL             0       // Message send "normal"
#define     MSG_SEND_OTHER_THAN_LAST    1       // Message send "if not the same as the last message"
#define     MSG_SEND_IF_NOT_PRESENT     2       // Message send "if not present in the send buffer"



                                                // Interface Distancesensor-Inputs Type
#define     IF_DS_INPUT_OFF             0       // Disable Inputs (no function)
#define     IF_DS_INPUT_ULTRASONIC      1       // Ultrasonic Distance Sensor (08.2007: New)
#define     IF_DS_INPUT_VOLTAGE         2       // Voltage
#define     IF_DS_INPUT_DISTANCE        3       // Distance (08.2007: New Value, formerly "1")
#define     IF_DS_INPUT_TOL_STD         20      // Toleranz (Standard)
#define     IF_DS_INPUT_REP_STD         3       // Repeat (Standard)



    #pragma pack( push, 1 )
    typedef union
    {
        BYTE    aucMsg[6];

        struct 
        {
            BYTE    ucHwId;       
            BYTE    ucSubId;       
            BYTE    ucB0;
            BYTE    ucB1;
            BYTE    ucB2;
            BYTE    ucB3;
        } B;

        struct 
        {
            BYTE    ucHwId;       
            BYTE    ucSubId;       
            USHORT  uiMsgId;        
            USHORT  uiMsg;
        } W;

        struct 
        {
            BYTE    ucHwId;       
            BYTE    ucSubId;       
            DWORD   dw;
        } L;
    } SMESSAGE;
    #pragma pack( pop )


    typedef void * FT_HANDLE;
    typedef void (*DATA_UPDATE_CALLBACK)(void* Context);
    typedef void (*MSG_UPDATE_CALLBACK)(SMESSAGE *);



    // Important: 
    // Initialise all unused Variables in this Structure with "NULL"
    //
    // Every Time the driver reads new information from the Device
    // the Library checks this structure 
    typedef struct _NOTIFICATION_EVENTS 
    {
        // Callback-Procedure
        DATA_UPDATE_CALLBACK NotificationCallback;  // Pointer to the Callback-Procedure
        void* Context;                              // Pointer to the Context for the Callback-Procedure

        // for SetEvent()
        HANDLE hEvent;

        // for posting a Message (PostMessage() with wParam & lParam = 0)
        HWND    WindowsHandle;                      // handle to the destination window
        DWORD   Message;                            // message ID


        // Callback-Procedure for Messaging
        MSG_UPDATE_CALLBACK     CallbackMessage;    // Pointer to the Callback-Procedure for Receiving Messages

    } 
    NOTIFICATION_EVENTS;




    typedef struct _FT_SERIAL_NUMBER
    {
        DWORD   dwSn;                   // actually Serial Number at Power On
        DWORD   dwSn1;                  // Serial Number-1
        DWORD   dwSn2;                  // Serial Number-2
        DWORD   dwSnAktiv;              // Serial Number Activ (1/2) for next Power On
    } FT_SERIAL_NUMBER; 




    typedef struct _FT_DISTANCE         // Robo Interface Distance Sensor
    {
        unsigned char   aDistModeNames[LEN_DIST_TYPE_NAMES];    // RO   Names for the Modes  

        DWORD           dwEnableDisVal1;                        // RO   1=Ask for Distance Value 1
        unsigned char   aDisVal1Name[LEN_DIST_VAR_NAMES];       // RO   Value 1 Name
        DWORD           dwDisVal1;                              // RW   Value 1

        DWORD           dwEnableDisVal2;                        // RO   1=Ask for Distance Value 2
        unsigned char   aDisVal2Name[LEN_DIST_VAR_NAMES];       // RO   Value 2 Name
        DWORD           dwDisVal2;                              // RW   Value 2

        DWORD           dwEnableDisVal3;                        // RO   1=Ask for Distance Value 3
        unsigned char   aDisVal3Name[LEN_DIST_VAR_NAMES];       // RO   Value 3 Name
        DWORD           dwDisVal3;                              // RW   Value 3

        DWORD           dwEnableDisVal4;                        // RO   1=Ask for Distance Value 4
        unsigned char   aDisVal4Name[LEN_DIST_VAR_NAMES];       // RO   Value 4 Name
        DWORD           dwDisVal4;                              // RW   Value 4

        DWORD           dwEnableDisVal5;                        // RO   1=Ask for Distance Value 5
        unsigned char   aDisVal5Name[LEN_DIST_VAR_NAMES];       // RO   Value 5 Name
        DWORD           dwDisVal5;                              // RW   Value 5

        DWORD           dwEnableDisVal6;                        // RO   1=Ask for Distance Value 6
        unsigned char   aDisVal6Name[LEN_DIST_VAR_NAMES];       // RO   Value 6 Name
        DWORD           dwDisVal6;                              // RW   Value 6

        DWORD           dwEnableDisVal7;                        // RO   1=Ask for Distance Value 7
        unsigned char   aDisVal7Name[LEN_DIST_VAR_NAMES];       // RO   Value 7 Name
        DWORD           dwDisVal7;                              // RW   Value 7

        DWORD           dwEnableDisVal8;                        // RO   1=Ask for Distance Value 8
        unsigned char   aDisVal8Name[LEN_DIST_VAR_NAMES];       // RO   Value 8 Name
        DWORD           dwDisVal8;                              // RW   Value 8
    } FT_DISTANCE;



    #define FT_SETTING_VERSION          4   // Versionnumber of _FT_SETTING
                                            // 01.12.2006: V2 = with Robo-Connect-Support
                                            // 31.12.2008: V3 = with StreetLine-Support (Struct-Length is changed)
                                            // 10.08.2010: V4 = with Robo-LT und Easy pH - Support (Struct-Length not changed)


    typedef union _FT_SETTING
    {
        struct                              // RO = Read Only, RW = Read / Write
        {
            DWORD   dwSettingVersion;       // RO   Versionnumber of this Setting structure as the FtLib / DLL is made. 
                                            //      It´s important for FtLib-DLL users to know, if _FT_SETTUNG is changed
                                            //      See also the CONST "FT_SETTING_VERSION"

            DWORD   dwIfTyp;                // RO   Type of connected Device
                                            //      possible Values:       
                                            //          NO_FT_DEVICE            no answer from the Device - is it gone ?
                                            //          FT_INTELLIGENT_IF       FT-Intelligent Interface connect (serial)
                                            //          FT_ROBO_IF_IIM          FT-Robo Interface with Intelligent-Interface-Modus connect (serial)
                                            //          FT_ROBO_IF_USB          FT-Robo Interface connect with USB-Port
                                            //          FT_ROBO_IF_COM          FT-Robo Interface connect with COM- (serial-) Port
                                            //          FT_ROBO_IO_EXTENSION    FT-Robo I/O-Extension
                                            //          FT_ROBO_RF_DATA_LINK    FT-Robo RF Data Link
                                            //             FT_ROBO_IF_OVER_RF   FT-Robo Interface connect over RF-Data-Link
                                            //          FT_SOUND_AND_LIGHT      FT-Light and Sound Module
                                            //          FT_ROBO_LT_CONTROLLER   FT-Robo LT Controller
                                            //          ROBO_CONNECT_BOX        Robo-Connect-Box (Knobloch Gmbh: for old Interfaces on parallel- or serial- port)
                                            //          EDU_LINE_MODULE         education line module (Knobloch GmbH)
                                            //          EDU_LINE_CROSSROADS     education line - Module: CrossRoads
                                            //          EDU_LINE_TRAFFICLIGHTS  education line - Module: Trafic Lights
                                            //          EDU_LINE_SIGNAL         education line - Module: Signal
                                            //          EDU_LINE_EASY_PH        education line - Module: easy pH


            DWORD   dwIfSubType;            // RO   Robo-Connect-Box: Type of the connected Interface
                                            // MULTIFACE_IF_X60     Multiface-Interface (Knobloch GmbH) Type: MF160 / MF260
                                            // MULTIFACE_IF_7X      Multiface-Interface (Knobloch GmbH) Txpe: MF7x
                                            // MULTIFACE_IF_OTHER   Multiface-Interface (Knobloch GmbH) Txpe: unknown
                                            // HIBS_IF              Hibs-Interface (Knobloch GmbH)
                                            // FT_UNIVERSAL_IF      FT-Universal Interface connect
                                            // FT_INTELLIGENT_IF    FT-Intelligent Interface connect (connect on RCB-serial Port)

            DWORD   dwIfSubTypeSetup;       // RO   Robo-Connect-Box: Setup-parameters
                                            // RCB_IF_SEARCH        Searching for known Interfaces at Power On
                                            // RCB_IF_SEARCH_OR_FIX Searching, if nothig found, than use defined type
                                            // RCB_IF_FIX           Nothing to search, the used Interfacetype is defined

            DWORD   dwIfSubTypeSearchOrFix; // RW   Interfacetype if Setup: "RCB_IF_SEARCH_OR_FIX" or "RCB_IF_FIX"


                                            // Serial numbers section
            DWORD   dwSn;                   // RO   actually Serial Number at Power On
            DWORD   dwSn1;                  // RW   Serial Number-1             (only FT-Robo Products)
            DWORD   dwSn2;                  // RO   Serial Number-2             (only FT-Robo Products)
            DWORD   dwSnAktiv;              // RW   Set Serial Number Activ (1/2) for next Power On

            DWORD   dwFw;                           // RO   Is Firmware Version for this product (only FT-Robo Products)

            unsigned char aSnStrg[LEN_STRG1];       // RO   String with Serialnumber    (only FT-Robo Products)
            unsigned char aSn1Strg[LEN_STRG1];      // RO   String with Serialnumber1   (only FT-Robo Products)
            unsigned char aSn2Strg[LEN_STRG1];      // RO   String with Serialnumber2   (only FT-Robo Products)
            unsigned char aFwStrg[LEN_STRG1];       // RO   String with Firmware        (only FT-Robo Products)
            unsigned char aSNaStrg[LEN_STRG2];      // RO   String with Short-Name      (only FT-Robo Products)
            unsigned char aLNaStrg[LEN_STRG2];      // RO   String with Long-Name       (only FT-Robo Products)

            unsigned char aSubSNaStrg[LEN_STRG2];   // RO   String with Short Sub Type Name (only Robo-Connect-Box)

            DWORD   dwFwRoboIfVerAtLibIsMade;               // RO   Robo-If Firmware Version as this Lib is made
            DWORD   dwFwIoExtVerAtLibIsMade;                // RO   IO-Extension Firmware Version as this Lib is made
            DWORD   dwFwRfDataVerAtLibIsMade;               // RO   RF-DataLink Firmware Version as this Lib is made
            DWORD   dwFwRoboConnectBoxVerAtLibIsMade;       // RO   Robo-Connect-Box Firmware Version as this Lib is made
            DWORD   dwFwSoundAndLightVerAtLibIsMade;        // RO   Sound and Light Firmware Version as this Lib is made
            DWORD   dwFwEduLineCrossRoadsVerAtLibIsMade;    // RO   Education Line: CrossRoads Firmware Version as this Lib is made
            DWORD   dwFwEduLineTrafficLightsVerAtLibIsMade;	// RO   Education Line: TrafficLights Firmware Version as this Lib is made
            DWORD   dwFwEduLineSignalVerAtLibIsMade;		// RO   Education Line: Signal Firmware Version as this Lib is made
            DWORD   dwFwRoboLTVerAtLibIsMade;               // RO   Robo-LT Firmware Version as this Lib is made
            DWORD   dwFwEduLineEasyPHVerAtLibIsMade;		// RO   Education Line: Easy pH Firmware Version as this Lib is made

            DWORD   dwReserved7;                            // RO   Reserved
            DWORD   dwReserved6;                            // RO   Reserved
            DWORD   dwReserved5;                            // RO   Reserved
            DWORD   dwReserved4;                            // RO   Reserved
            DWORD   dwReserved3;                            // RO   Reserved
            DWORD   dwReserved2;                            // RO   Reserved
            DWORD   dwReserved1;                            // RO   Reserved
            DWORD   dwReserved0;                            // RO   Reserved
            unsigned char aFwRoboIfVerAtLibIsMadeStrg[LEN_STRG1];               // RO   String with Robo-If Firmware Version as this Lib is made
            unsigned char aFwIoExtVerAtLibIsMadeStrg[LEN_STRG1];                // RO   String with IO-Extension Firmware Version as this Lib is made
            unsigned char aFwRfDataVerAtLibIsMadeStrg[LEN_STRG1];               // RO   String with Rf-Data-Link Firmware Version as this Lib is made
            unsigned char aFwRoboConnectBoxVerAtLibIsMadeStrg[LEN_STRG1];       // RO   String with Robo-Connect-Box Firmware Version as this Lib is made
            unsigned char aFwSoundAndLightVerAtLibIsMadeStrg[LEN_STRG1];        // RO   String with Sound and Light Firmware Version as this Lib is made
            unsigned char aFwEduLineCrossRoadsVerAtLibIsMadeStrg[LEN_STRG1];    // RO   String with Education Line: CrossRoads Firmware Version as this Lib is made
            unsigned char aFwEduLineTrafficLightsVerAtLibIsMadeStrg[LEN_STRG1]; // RO   String with Education Line: TrafficLights Firmware Version as this Lib is made
            unsigned char aFwEduLineSignalVerAtLibIsMadeStrg[LEN_STRG1];        // RO   String with Education Line: Signal Firmware Version as this Lib is made
            unsigned char aFwRoboLTVerAtLibIsMadeStrg[LEN_STRG1];               // RO   String with Robo-LT Firmware Version as this Lib is made
            unsigned char aFwEduLineEasyPHVerAtLibIsMadeStrg[LEN_STRG1];        // RO   String with Education Line: Easy pH Firmware Version as this Lib is made

            unsigned char aFwReserved7[LEN_STRG1];                          // RO   Reserved-String
            unsigned char aFwReserved6[LEN_STRG1];                          // RO   Reserved-String
            unsigned char aFwReserved5[LEN_STRG1];                          // RO   Reserved-String
            unsigned char aFwReserved4[LEN_STRG1];                          // RO   Reserved-String
            unsigned char aFwReserved3[LEN_STRG1];                          // RO   Reserved-String
            unsigned char aFwReserved2[LEN_STRG1];                          // RO   Reserved-String
            unsigned char aFwReserved1[LEN_STRG1];                          // RO   Reserved-String
            unsigned char aFwReserved0[LEN_STRG1];                          // RO   Reserved-String
                                            
            DWORD   dwReserved;                 // Reserved for later use 


                                                // Output Section
            DWORD   dwOutputAutoOff[4];         // RW   M1=[0]...M4=[3] Energy saver: 
                                                //      "1" = "Power Off" motor driver when both outputs logical "0" (reduces Energy)
                                                //      "0" = do not automatically disable the motor driver
            DWORD   dwOutputPwmType;            // RW   PWM-Type (Today only "0" supported)


                                                // Robo Interface Distance Sensor
            DWORD   dwAnzDistanceModes;         // RO   Number of supported Distance Modes (Array Entries)
            DWORD   dwDistanceMode;             // RW   Type and Mode for Distance-Sensor (Index-Number in the range 0...ANZ_DISTANCE_TYPES)
            FT_DISTANCE     sDistance[ANZ_DISTANCE_TYPES];  // RW   Values for setting
                        

                                                        // Robo Interface Memory Section
            DWORD           dwProg[3];                  // RO   1=Program is saved in the Memory block; [0]=Flash-1 [1]=Flash-2 [2]=Ram
            unsigned char   aProgNames[3][NAME_LEN];    // RO   [0]=Flash-1 Prog Name; [1]=Flash-2 Prog Name; [2]=Ram Prog-Name
            DWORD           dwF1AutoStart;              // RO   1=Autostart Flash-1 programm, 0=no autostart


                                                // Robo Interface Module Section
            DWORD           dwMod1Typ;          // RO   Type of left Module (only Robo-If)
            DWORD           dwMod2Typ;          // RO   Type of right Module (only Robo-If)
                                                //      possible Values:       
                                                //          MODULE_NOT_INSTALLED    No Module is installed
                                                //          MODULE_RF1              RF Data Link is installed

            unsigned char   aMod1Strg[LEN_STRG1];   // RO   String with Module-1 Name   (only FT-Robo Products)
            unsigned char   aMod2Strg[LEN_STRG1];   // RO   String with Module-2 Name   (only FT-Robo Products)


                                                // Robo Interface & RF Data Link Section
            DWORD   dwRfOn;                     // RW   0=disable RF  1=Enable RF
            DWORD   dwRfChannel;                // RW   Channel-Number (2..80) for RF-Communication 
            DWORD   dwRfSubChannel;             // RW   Sub-Channel of Device for the specified Channel (1..3)
            DWORD   dwRfMessage;                // RW   0=Disable Message-Router Function 1=Enable Message-Rounter Function
            DWORD   dwRfWrite;                  // W    0=write values permanent (FLASH); 1=write values temporary (RAM) 
            DWORD   dwRfFw;                     // RO   Firmwareversion of RF-Module
            unsigned char aRfFwStrg[LEN_STRG1]; // RO   String with Firmware of RF-Module 

                                                // Information for the PC-RF Module
            DWORD   dwRfStopTransferOnError;    // RW   1=Stop the RF-Transfer Thread on bad RF Connection

                                                // Information for the Interface RF-Module
            DWORD   dwRfMotorOffOnError;        // RW   1=Motor Off on bad RF Connection
        } sIf;
    } FT_SETTING;






    // *************************************************
    // education line
    // *************************************************
    #define KE_EL_STRUCT_IO_VERSION             1       // Versionnumber of KE_EL_IO_STRUCT
    #define KE_EL_STRUCT_IO_SUB_VERSION         2       // Sub-Versionnumber of KE_EL_IO_STRUCT
                                                        // 10.08.2010: easy pH

    #define KE_EL_ANZ_OUT                       128     // Number of OUTputs
    #define KE_EL_ANZ_IN                        128     // Number of INputs
    #define KE_EL_ANZ_ANA_IN                    128     // Number of Analog-INputs
    #define KE_EL_ANZ_RES                       128     // Number of Reseved Data

    typedef struct                                      // IO-Struct for "education line" Products
    {
        DWORD   dwStructVersion;                        // Versionnumber of this Setting structure as the FtLib / DLL is made. 
                                                        // It´s important for KeLib-DLL users to know, if KE_STRUCT_IO is changed
                                                        // See also the CONST "KE_STRUCT_IO_VERSION"
                                                        // This Number is changed, if the size or the Offset´s changed

        DWORD   dwStructSubVersion;                     // Sub-Versionnumber of this Setting structure 
                                                        // This Number is increment, if a little bit is changed - but not important. 


        DWORD   dwOutTyp;                               // Output typ (today not used)
        union
        {
            struct
            {
                DWORD   dwOut0;                         // Byte 0 Output
                DWORD   dwOut1;                         // Byte 1 Output
                DWORD   dwOut2;                         // Byte 2 Output
                DWORD   dwOut3;                         // Byte 3 Output
                DWORD   dwOut4;                         // Byte 4 Output
                DWORD   dwOut5;                         // Byte 5 Output
                DWORD   dwOut6;                         // Byte 6 Output
                DWORD   dwOut7;                         // Byte 7 Output
                DWORD   dwOut8;                         // Byte 8 Output
                DWORD   dwOut9;                         // Byte 9 Output
                DWORD   dwOut10;                        // Byte 10 Output
                DWORD   dwOut11;                        // Byte 11 Output
                DWORD   dwOut12;                        // Byte 12 Output
                DWORD   dwOut13;                        // Byte 13 Output
                DWORD   dwOut14;                        // Byte 14 Output
                DWORD   dwOut15;                        // Byte 15 Output

                DWORD   dwRes[KE_EL_ANZ_OUT-16];        // reserved
            } s;
            DWORD   adwOut[KE_EL_ANZ_OUT];              // Array
        } Out;                                          // Output - Data


        DWORD   dwReserved1[KE_EL_ANZ_RES+1];           // (today not used)


        DWORD   dwInpTyp;                               // Input typ (today not used)
        union
        {
            struct
            {
                DWORD   dwInp0;                         // Input 0 Data
                DWORD   dwInp1;                         // Input 1 Data
                DWORD   dwInp2;                         // Input 2 Data
                DWORD   dwInp3;                         // Input 3 Data
                DWORD   dwInp4;                         // Input 4 Data
                DWORD   dwInp5;                         // Input 5 Data
                DWORD   dwInp6;                         // Input 6 Data
                DWORD   dwInp7;                         // Input 7 Data
                DWORD   dwInp8;                         // Input 8 Data
                DWORD   dwInp9;                         // Input 9 Data
                DWORD   dwInp10;                        // Input 10 Data
                DWORD   dwInp11;                        // Input 11 Data
                DWORD   dwInp12;                        // Input 12 Data
                DWORD   dwInp13;                        // Input 13 Data
                DWORD   dwInp14;                        // Input 14 Data
                DWORD   dwInp15;                        // Input 15 Data

                DWORD   dwRes[KE_EL_ANZ_IN-16];         // reserved
            } s;
            DWORD   adwInp[KE_EL_ANZ_IN];               // Array
        } Inp;                                          // Input - Data


        DWORD   dwInpAnaTyp;                            // Analog-Input typ (today not used)
        union
        {
            struct
            {
                DWORD   dwAna0;                         // Analog-Input 0 Data
                DWORD   dwAna1;                         // Analog-Input 1 Data
                DWORD   dwAna2;                         // Analog-Input 2 Data
                DWORD   dwAna3;                         // Analog-Input 3 Data
                DWORD   dwAna4;                         // Analog-Input 4 Data
                DWORD   dwAna5;                         // Analog-Input 5 Data
                DWORD   dwAna6;                         // Analog-Input 6 Data
                DWORD   dwAna7;                         // Analog-Input 7 Data
                DWORD   dwAna8;                         // Analog-Input 8 Data
                DWORD   dwAna9;                         // Analog-Input 9 Data
                DWORD   dwAna10;                        // Analog-Input 10 Data
                DWORD   dwAna11;                        // Analog-Input 11 Data
                DWORD   dwAna12;                        // Analog-Input 12 Data
                DWORD   dwAna13;                        // Analog-Input 13 Data
                DWORD   dwAna14;                        // Analog-Input 14 Data
                DWORD   dwAna15;                        // Analog-Input 15 Data

                DWORD   dwRes[KE_EL_ANZ_ANA_IN-16];     // reserved
            } s;
            DWORD   adwAna[KE_EL_ANZ_ANA_IN];           // Array
        } InpAna;                                       // Analog-Input - Data


        DWORD   dwReserved2[4096];                      // reserved Area
    } KE_EL_IO_STRUCT;



    // ****** Function Prototypes  ******
    DWORD __stdcall     GetLibVersion(void);
    DWORD __stdcall     InitFtLib(void);
    DWORD __stdcall     CloseFtLib(void);
    DWORD __stdcall     IsFtLibInit(void);
    DWORD __stdcall     InitFtUsbDeviceList(void);
    UINT  __stdcall     GetNumFtUsbDevice(void);
    FT_HANDLE __stdcall GetFtUsbDeviceHandle(UCHAR ucDevNr);
    FT_HANDLE __stdcall GetFtUsbDeviceHandleSerialNr(DWORD dwSN, DWORD dwTyp);
    DWORD __stdcall     OpenFtUsbDevice(FT_HANDLE hFt);
    FT_HANDLE __stdcall OpenFtCommDevice(DWORD dwPort, DWORD dwTyp, DWORD dwZyklus, DWORD *pdwError);
    DWORD __stdcall     SetFtDeviceCommMode (FT_HANDLE hFt, DWORD dwMode, DWORD dwParameter, USHORT *puiValue);
    DWORD __stdcall     CloseAllFtDevices(void);
    DWORD __stdcall     CloseFtDevice(FT_HANDLE hFt);
    DWORD __stdcall     GetFtDeviceTyp(FT_HANDLE hFt);
    LPCSTR __stdcall    GetFtSerialNrStrg(FT_HANDLE hFt);
    DWORD  __stdcall    GetFtSerialNr(FT_HANDLE hFt);
    LPCSTR __stdcall    GetFtFirmwareStrg(FT_HANDLE hFt);
    DWORD __stdcall     GetFtFirmware(FT_HANDLE hFt);
    LPCSTR __stdcall    GetFtManufacturerStrg(FT_HANDLE hFt);
    LPCSTR __stdcall    GetFtShortNameStrg(FT_HANDLE hFt);
    LPCSTR __stdcall    GetFtLongNameStrg(FT_HANDLE hFt);
    LPCSTR __stdcall    GetFtLibErrorString(DWORD dwErrorCode, DWORD dwTyp);
    DWORD __stdcall     GetFtDeviceSetting(FT_HANDLE hFt, FT_SETTING *pSet);
    DWORD __stdcall     SetFtDeviceSetting(FT_HANDLE hFt, FT_SETTING *pSet);
    DWORD __stdcall     SetFtDistanceSensorMode(FT_HANDLE hFt, DWORD dwMode, DWORD dwTol1, DWORD dwTol2, 
                                                DWORD dwSchwell1, DWORD dwSchwell2, DWORD dwRepeat1, DWORD dwRepeat2);


    DWORD __stdcall     StartFtTransferArea(FT_HANDLE hFt, NOTIFICATION_EVENTS* sNEvent );
    DWORD __stdcall     StartFtTransferAreaWithCommunication(FT_HANDLE hFt, NOTIFICATION_EVENTS* sNEvent );
    DWORD __stdcall     StopFtTransferArea(FT_HANDLE hFt);
    FT_TRANSFER_AREA* __stdcall GetFtTransferAreaAddress(FT_HANDLE hFt);
    DWORD __stdcall     IsFtTransferActiv(FT_HANDLE hFt);
    DWORD __stdcall     ResetFtTransfer (FT_HANDLE hFt);

    
    DWORD __stdcall     GetFtMemoryLayout(FT_HANDLE hFt, BYTE * pbArray, DWORD dwSize);
    DWORD __stdcall     DownloadFtProgram(FT_HANDLE hFt, DWORD dwMemBlock, BYTE* pbArray, DWORD dwSize, DWORD dwParameter, BYTE *pbName, DWORD dwNameLen);
    DWORD __stdcall     StartFtProgram(FT_HANDLE hFt, DWORD dwMemBlock);
    DWORD __stdcall     StopFtProgram(FT_HANDLE hFt);
    DWORD __stdcall     DeleteFtProgram(FT_HANDLE hFt, DWORD dwMemBlock);
    DWORD __stdcall     SetFtProgramActiv(FT_HANDLE hFt, DWORD dwMemBlock);
    DWORD __stdcall     GetFtProgramName(FT_HANDLE hFt, DWORD dwMemBlock, DWORD dwSize, LPVOID pName);
    DWORD __stdcall     WriteFtMemoryData(FT_HANDLE hFt, DWORD dwData, DWORD dwAddress);
    DWORD __stdcall     GetFtMemoryData(FT_HANDLE hFt, BYTE * pbArray, DWORD dwSize, DWORD dwAddress);

    DWORD __stdcall     SendFtMessage(FT_HANDLE hFt, BYTE bHwId, BYTE bSubId, DWORD dwMessage, DWORD dwWaitTime, DWORD dwOption); 
    DWORD __stdcall     ClearFtMessageBuffer(FT_HANDLE hFt);

    // education line

    DWORD __stdcall KE_WriteOutputByte(FT_HANDLE hFt, DWORD dwData0, DWORD dwIndex, DWORD dwOption);
    DWORD __stdcall KE_ReadInputByte(FT_HANDLE hFt, DWORD *pdwData0, DWORD dwIndex, DWORD dwOption);
    DWORD __stdcall KE_UpdateStructure(FT_HANDLE hFt, KE_EL_IO_STRUCT *pStruc, DWORD dwOption);




    



//
// FTLIB Error Codes
//
    #define FTLIB_ERR_SUCCESS                              0x00000000L  
    #define FTLIB_ERR_CRC                                  0xE0000001L  
    #define FTLIB_ERR_BTSTUFF                              0xE0000002L  
    #define FTLIB_ERR_DATA_TOGGLE_MISMATCH                 0xE0000003L  
    #define FTLIB_ERR_STALL_PID                            0xE0000004L  
    #define FTLIB_ERR_DEV_NOT_RESPONDING                   0xE0000005L  
    #define FTLIB_ERR_PID_CHECK_FAILURE                    0xE0000006L  
    #define FTLIB_ERR_UNEXPECTED_PID                       0xE0000007L  
    #define FTLIB_ERR_DATA_OVERRUN                         0xE0000008L  
    #define FTLIB_ERR_DATA_UNDERRUN                        0xE0000009L  
    #define FTLIB_ERR_RESERVED1                            0xE000000AL  
    #define FTLIB_ERR_RESERVED2                            0xE000000BL  
    #define FTLIB_ERR_BUFFER_OVERRUN                       0xE000000CL  
    #define FTLIB_ERR_BUFFER_UNDERRUN                      0xE000000DL  
    #define FTLIB_ERR_NOT_ACCESSED                         0xE000000FL  
    #define FTLIB_ERR_FIFO                                 0xE0000010L  
    #define FTLIB_ERR_XACT_ERROR                           0xE0000011L  
    #define FTLIB_ERR_BABBLE_DETECTED                      0xE0000012L  
    #define FTLIB_ERR_DATA_BUFFER_ERROR                    0xE0000013L  
                                                    
    #define FTLIB_ERR_ENDPOINT_HALTED                      0xE0000030L  
    #define FTLIB_ERR_NO_MEMORY                            0xE0000100L  
    #define FTLIB_ERR_INVALID_URB_FUNCTION                 0xE0000200L  
    #define FTLIB_ERR_INVALID_PARAMETER                    0xE0000300L  
    #define FTLIB_ERR_ERROR_BUSY                           0xE0000400L  
    #define FTLIB_ERR_INVALID_PIPE_HANDLE                  0xE0000600L  
    #define FTLIB_ERR_NO_BANDWIDTH                         0xE0000700L  
    #define FTLIB_ERR_INTERNAL_HC_ERROR                    0xE0000800L  
    #define FTLIB_ERR_ERROR_SHORT_TRANSFER                 0xE0000900L  
    #define FTLIB_ERR_BAD_START_FRAME                      0xE0000A00L  
    #define FTLIB_ERR_ISOCH_REQUEST_FAILED                 0xE0000B00L  
    #define FTLIB_ERR_FRAME_CONTROL_OWNED                  0xE0000C00L  
    #define FTLIB_ERR_FRAME_CONTROL_NOT_OWNED              0xE0000D00L  
    #define FTLIB_ERR_NOT_SUPPORTED                        0xE0000E00L  
    #define FTLIB_ERR_INVALID_CONFIGURATION_DESCRIPTOR     0xE0000F00L  

    #define FTLIB_ERR_INSUFFICIENT_RESOURCES               0xE8001000L  
    #define FTLIB_ERR_SET_CONFIG_FAILED                    0xE0002000L  
    #define FTLIB_ERR_USBD_BUFFER_TOO_SMALL                0xE0003000L  
    #define FTLIB_ERR_USBD_INTERFACE_NOT_FOUND             0xE0004000L  
    #define FTLIB_ERR_INVALID_PIPE_FLAGS                   0xE0005000L  
    #define FTLIB_ERR_USBD_TIMEOUT                         0xE0006000L  
    #define FTLIB_ERR_DEVICE_GONE                          0xE0007000L  
    #define FTLIB_ERR_STATUS_NOT_MAPPED                    0xE0008000L  

    #define FTLIB_ERR_CANCELED                             0xE0010000L  
    #define FTLIB_ERR_ISO_NOT_ACCESSED_BY_HW               0xE0020000L  
    #define FTLIB_ERR_ISO_TD_ERROR                         0xE0030000L  
    #define FTLIB_ERR_ISO_NA_LATE_USBPORT                  0xE0040000L  
    #define FTLIB_ERR_ISO_NOT_ACCESSED_LATE                0xE0050000L  
                                                    
    #define FTLIB_ERR_FAILED                               0xE0001000L  
    #define FTLIB_ERR_INVALID_INBUFFER                     0xE0001001L  
    #define FTLIB_ERR_INVALID_OUTBUFFER                    0xE0001002L  
    #define FTLIB_ERR_OUT_OF_MEMORY                        0xE0001003L  
    #define FTLIB_ERR_PENDING_REQUESTS                     0xE0001004L  
    #define FTLIB_ERR_ALREADY_CONFIGURED                   0xE0001005L  
    #define FTLIB_ERR_NOT_CONFIGURED                       0xE0001006L  
    #define FTLIB_ERR_OPEN_PIPES                           0xE0001007L  
    #define FTLIB_ERR_ALREADY_BOUND                        0xE0001008L  
    #define FTLIB_ERR_NOT_BOUND                            0xE0001009L  
    #define FTLIB_ERR_DEVICE_NOT_PRESENT                   0xE000100AL  
    #define FTLIB_ERR_CONTROL_NOT_SUPPORTED                0xE000100BL  
    #define FTLIB_ERR_TIMEOUT                              0xE000100CL  
    #define FTLIB_ERR_INVALID_RECIPIENT                    0xE000100DL  
    #define FTLIB_ERR_INVALID_TYPE                         0xE000100EL  
    #define FTLIB_ERR_INVALID_IOCTL                        0xE000100FL  
    #define FTLIB_ERR_INVALID_DIRECTION                    0xE0001010L  
    #define FTLIB_ERR_TOO_MUCH_ISO_PACKETS                 0xE0001011L  
    #define FTLIB_ERR_POOL_EMPTY                           0xE0001012L  
    #define FTLIB_ERR_PIPE_NOT_FOUND                       0xE0001013L  
    #define FTLIB_ERR_INVALID_ISO_PACKET                   0xE0001014L  
    #define FTLIB_ERR_OUT_OF_ADDRESS_SPACE                 0xE0001015L  
    #define FTLIB_ERR_INTERFACE_NOT_FOUND                  0xE0001016L  
    #define FTLIB_ERR_INVALID_DEVICE_STATE                 0xE0001017L  
    #define FTLIB_ERR_INVALID_PARAM                        0xE0001018L  
    #define FTLIB_ERR_INVALID_POWER_STATE                  0xE000101AL  
    #define FTLIB_ERR_POWER_DOWN                           0xE000101BL  
    #define FTLIB_ERR_VERSION_MISMATCH                     0xE000101CL  
    #define FTLIB_ERR_SET_CONFIGURATION_FAILED             0xE000101DL  
    #define KEUSB_ERR_ADDITIONAL_EVENT_SIGNALLED           0xE000101EL
    #define KEUSB_ERR_INVALID_PROCESS                      0xE000101FL
    #define KEUSB_ERR_DEVICE_ACQUIRED                      0xE0001020L
    #define KEUSB_ERR_DEVICE_OPENED                        0xE0001021L

    #define FTLIB_ERR_VID_RESTRICTION                      0xE0001080L  
    #define FTLIB_ERR_ISO_RESTRICTION                      0xE0001081L  
    #define FTLIB_ERR_BULK_RESTRICTION                     0xE0001082L  
    #define FTLIB_ERR_EP0_RESTRICTION                      0xE0001083L  
    #define FTLIB_ERR_PIPE_RESTRICTION                     0xE0001084L  
    #define FTLIB_ERR_PIPE_SIZE_RESTRICTION                0xE0001085L  
    #define FTLIB_ERR_CONTROL_RESTRICTION                  0xE0001086L  
    #define FTLIB_ERR_INTERRUPT_RESTRICTION                0xE0001087L  
                                                    
    #define FTLIB_ERR_DEVICE_NOT_FOUND                     0xE0001100L
    #define FTLIB_ERR_SOME_DEVICES_ARE_OPEN                0xE0001101L
    #define FTLIB_ERR_DEVICE_IS_OPEN                       0xE0001102L
    #define FTLIB_ERR_DEVICE_NOT_OPEN                      0xE0001103L
    #define FTLIB_ERR_NO_SUCH_DEVICE_INSTANCE              0xE0001104L
    #define FTLIB_ERR_INVALID_FUNCTION_PARAM               0xE0001105L
    #define FTLIB_ERR_DESTROY_DEVICE_LIST                  0xE0001106L
    #define FTLIB_ERR_USB_NOT_SUPPORTET_FROM_OS            0xE0001107L
    #define FTLIB_ERR_CLOSE_DEVICE                         0xE0001108L

    #define FTLIB_ERR_DEVICE_NOT_SUPPORTET                 0xE0001281L  
    #define FTLIB_ERR_WRONG_DEVICE_NUMBER                  0xE0001282L  
    #define FTLIB_ERR_UNKNOWN_DEVICE_HANDLE                0xE0001283L  
    #define FTLIB_ERR_WRONG_USB_HANDLE                     0xE0001284L  
    #define FTLIB_ERR_WRONG_PATHNAME                       0xE0001285L  
    #define FTLIB_ERR_LIB_IS_INITIALIZED                   0xE0001286L  
    #define FTLIB_ERR_LIB_IS_NOT_INITIALIZED               0xE0001287L  
    #define FTLIB_ERR_SERIAL_NR_UNKNOWN                    0xE0001288L  
    #define FTLIB_ERR_POWER_TOO_LOW                        0xE0001289L  
    #define FTLIB_ERR_WRONG_RETURN_VALUE                   0xE000128AL  
    #define FTLIB_ERR_USB_SUPPORT_IS_NOT_INITIALIZED       0xE000128BL  

    #define FTLIB_ERR_USB_MUT0                             0xE0001290L  
    #define FTLIB_ERR_USB_MUT1                             0xE0001291L  
    #define FTLIB_ERR_USB_MUT2                             0xE0001292L  
    #define FTLIB_ERR_USB_MUT3                             0xE0001293L 
    #define FTLIB_ERR_USB_DEVICE_IS_IN_USE                 0xE0001295L

    #define FTLIB_ERR_THREAD_NOT_STARTABLE                 0xE00012A0L  
    #define FTLIB_ERR_THREAD_NOT_STARTABLE_X1              0xE00012A1L  
    #define FTLIB_ERR_THREAD_NOT_STARTABLE_X2              0xE00012A2L  
    #define FTLIB_ERR_THREAD_NOT_STARTABLE_X3              0xE00012A3L  
    #define FTLIB_ERR_OTHER_THREAD_FOR_SAME_DEVICE_IS_RUN  0xE00012A4L  
    #define FTLIB_ERR_THREAD_IS_RUNNING                    0xE00012A5L  
    #define FTLIB_ERR_THREAD_NOT_RUNNING                   0xE00012A6L  
    #define FTLIB_ERR_THREAD_X1                            0xE00012A7L  
    #define FTLIB_ERR_THREAD_X2                            0xE00012A8L  
    #define FTLIB_ERR_THREAD_WRITE_USB                     0xE00012A9L  
    #define FTLIB_ERR_THREAD_READ_USB                      0xE00012AAL  
    #define FTLIB_ERR_THREAD_IS_NORMAL_STOPPED             0xE00012ABL  
    #define FTLIB_ERR_THREAD_WAIT_TIMEOUT                  0xE00012ACL  
    #define FTLIB_ERR_THREAD_WRITE_COM                     0xE00012ADL  
    #define FTLIB_ERR_THREAD_READ_COM                      0xE00012AEL   

    #define FTLIB_ERR_DOWNLOAD                             0xE00012C0L  
    #define FTLIB_ERR_DOWNLOAD_WRONG_PARAMETER             0xE00012C1L  
    #define FTLIB_ERR_DOWNLOAD_WRONG_MEM_BLOCK             0xE00012C2L  
    #define FTLIB_ERR_DOWNLOAD_DATA_SIZE_IS_NULL           0xE00012C3L  
    #define FTLIB_ERR_DOWNLOAD_DATA_SIZE_TOO_BIG           0xE00012C4L  
    #define FTLIB_ERR_DOWNLOAD_DATA_SIZE                   0xE00012C5L  
    #define FTLIB_ERR_DOWNLOAD_ERASE                       0xE00012C6L  
    #define FTLIB_ERR_DOWNLOAD_F5                          0xE00012C7L  
    #define FTLIB_ERR_DOWNLOAD_PROG_SNF1                   0xE00012C8L  
    #define FTLIB_ERR_DOWNLOAD_PROG_SNF2                   0xE00012C9L  
    #define FTLIB_ERR_DOWNLOAD_BLOCK                       0xE00012CAL  
    #define FTLIB_ERR_DOWNLOAD_BLOCK_NR                    0xE00012CBL  
    #define FTLIB_ERR_DOWNLOAD_CRC                         0xE00012CDL  

    #define FTLIB_ERR_IF_NO_PROGRAM                        0xE00012E0L  
    #define FTLIB_ERR_IF_PROGRAM_IS_RUNNING                0xE00012E1L  
    #define FTLIB_ERR_IF_NO_PROGRAM_IS_RUNNING             0xE00012E2L  
    #define FTLIB_ERR_IF_WRONG_PROG_NUMBER                 0xE00012E3L  
    #define FTLIB_ERR_IF_BUFFER_TOO_SMALL                  0xE00012E4L  
    #define FTLIB_ERR_IF_MEM_ADDRESS                       0xE00012E5L  
    #define FTLIB_ERR_IF_MEM_VERIFY                        0xE00012E6L  
    #define FTLIB_ERR_IF_NOT_SUPPORTET_MODUS               0xE00012E7L  
    #define FTLIB_ERR_IF_FUNCTION_NOT_SUPPORT              0xE00012E8L
    #define FTLIB_ERR_FUNCTION_OVER_RF_NOT_ALLOWED         0xE00012E9L
    #define FTLIB_ERR_IF_FW_OLD1                           0xE00012EAL

    #define FTLIB_INFO_PROGRAM_0_IS_RUNNING                0xE0001600L  
    #define FTLIB_INFO_PROGRAM_1_IS_RUNNING                0xE0001601L  
    #define FTLIB_INFO_PROGRAM_2_IS_RUNNING                0xE0001602L  
    #define FTLIB_INFO_ONLINE_MODUS                        0xE0001620L  

    #define FTLIB_FIRMWARE_UPDATE_FILE_WRONG_0             0xE0001800L  
    #define FTLIB_FIRMWARE_UPDATE_CRC                      0xE0001801L  
    #define FTLIB_FIRMWARE_UPDATE_FILE_OLD                 0xE0001802L
    #define FTLIB_FIRMWARE_UPDATE_FILE_WRONG_1             0xE0001803L


    #define FTLIB_ERR_PORT_NUMBER                          0xE0001900L  
    #define FTLIB_ERR_WRONG_PORT                           0xE0001901L  
    #define FTLIB_ERR_PORT_NUMBER_IS_NULL                  0xE0001902L  
    #define FTLIB_ERR_TYP                                  0xE0001903L  
    #define FTLIB_ERR_PORT_NOT_FOUND                       0xE0001904L  
    #define FTLIB_ERR_ACCESS_DENIED                        0xE0001905L  
    #define FTLIB_ERR_OPEN_COM                             0xE0001906L  
    #define FTLIB_ERR_CLOSE_COM                            0xE0001907L  
    #define FTLIB_ERR_INIT_COM                             0xE0001908L  
    #define FTLIB_ERR_INIT_COM_TIMEOUT                     0xE0001909L  
    #define FTLIB_ERR_WRITE_COM                            0xE000190AL  
    #define FTLIB_ERR_READ_COM                             0xE000190BL  
    #define FTLIB_ERR_READ_COM_NUMBER                      0xE000190CL  
    #define FTLIB_ERR_READ_COM_NOTHING                     0xE000190DL  

    #define FTLIB_ERR_RF_NOT_INSTALLED                     0xE0001A00L
    #define FTLIB_ERR_RF_WRONG_CHANNEL                     0xE0001A01L
    #define FTLIB_ERR_RF_WRONG_SUB_CHANNEL                 0xE0001A02L
    #define FTLIB_ERR_RF_NO_CONNECTION                     0xE0001A03L
    #define FTLIB_ERR_RF_NO_CONNECTION_A                   0xE0001A04L
    #define FTLIB_ERR_RF_NO_CONNECTION_B                   0xE0001A05L
    #define FTLIB_ERR_RF_NO_CONNECTION_C                   0xE0001A06L
    #define FTLIB_ERR_RF_TIMEOUT_1                         0xE0001A08L
    #define FTLIB_ERR_RF_TIMEOUT_2                         0xE0001A09L
    #define FTLIB_ERR_RF_FW_OLD1                           0xE0001A0AL
    #define FTLIB_ERR_RF_INTERNAL_1                        0xE0001A0DL
    #define FTLIB_ERR_RF_NO_INTERFACE_MODULE_FOUND         0xE0001A0EL

    #define FTLIB_ERR_DLL_NOT_LOADABLE                     0xE0001B00L 
    #define FTLIB_ERR_DLL_FUNCTION_ERROR                   0xE0001B01L 

    #define FTLIB_ERR_MSG_HWID_WRONG                       0xE0001C00L 
    #define FTLIB_ERR_MSG_BUFFER_FULL_TIMEOUT              0xE0001C01L

    #define FTLIB_ERR_UNKNOWN_OPTION_VALUE                 0xE0001D00L
    #define FTLIB_ERR_NUMBER_TOO_BIG                       0xE0001D01L 

    #define FTLIB_ERR_INTERFACE_00                         0xE0001F00L  
    #define FTLIB_ERR_INTERFACE_01                         0xE0001F01L  
    #define FTLIB_ERR_INTERFACE_02                         0xE0001F02L  
    #define FTLIB_ERR_INTERFACE_03                         0xE0001F03L  
    #define FTLIB_ERR_INTERFACE_04                         0xE0001F04L  
    #define FTLIB_ERR_INTERFACE_05                         0xE0001F05L  
    #define FTLIB_ERR_INTERFACE_06                         0xE0001F06L  
    #define FTLIB_ERR_INTERFACE_07                         0xE0001F07L  
    #define FTLIB_ERR_INTERFACE_08                         0xE0001F08L  
    #define FTLIB_ERR_INTERFACE_09                         0xE0001F09L  
    #define FTLIB_ERR_INTERFACE_0A                         0xE0001F0AL  
    #define FTLIB_ERR_INTERFACE_0B                         0xE0001F0BL  
    #define FTLIB_ERR_INTERFACE_0C                         0xE0001F0CL  
    #define FTLIB_ERR_INTERFACE_0D                         0xE0001F0DL  
    #define FTLIB_ERR_INTERFACE_0E                         0xE0001F0EL  
    #define FTLIB_ERR_INTERFACE_0F                         0xE0001F0FL  

    #define FTLIB_ERR_INTERFACE_D0                         0xE0001FD0L  
    #define FTLIB_ERR_INTERFACE_D1                         0xE0001FD1L  
    #define FTLIB_ERR_INTERFACE_D2                         0xE0001FD2L  
    #define FTLIB_ERR_INTERFACE_D3                         0xE0001FD3L  
    #define FTLIB_ERR_INTERFACE_D4                         0xE0001FD4L  
    #define FTLIB_ERR_INTERFACE_D5                         0xE0001FD5L  
    #define FTLIB_ERR_INTERFACE_D6                         0xE0001FD6L  
    #define FTLIB_ERR_INTERFACE_D7                         0xE0001FD7L  
    #define FTLIB_ERR_INTERFACE_D8                         0xE0001FD8L  
    #define FTLIB_ERR_INTERFACE_D9                         0xE0001FD9L  
    #define FTLIB_ERR_INTERFACE_DA                         0xE0001FDAL  
    #define FTLIB_ERR_INTERFACE_DB                         0xE0001FDBL  
    #define FTLIB_ERR_INTERFACE_DC                         0xE0001FDCL  
    #define FTLIB_ERR_INTERFACE_DD                         0xE0001FDDL  
    #define FTLIB_ERR_INTERFACE_DE                         0xE0001FDEL  
    #define FTLIB_ERR_INTERFACE_DF                         0xE0001FDFL  

    #define FTLIB_ERR_INTERFACE_E0                         0xE0001FE0L  
    #define FTLIB_ERR_INTERFACE_E1                         0xE0001FE1L  
    #define FTLIB_ERR_INTERFACE_E2                         0xE0001FE2L  
    #define FTLIB_ERR_INTERFACE_E3                         0xE0001FE3L  
    #define FTLIB_ERR_INTERFACE_E4                         0xE0001FE4L  
    #define FTLIB_ERR_INTERFACE_E5                         0xE0001FE5L  
    #define FTLIB_ERR_INTERFACE_E6                         0xE0001FE6L  
    #define FTLIB_ERR_INTERFACE_E7                         0xE0001FE7L  
    #define FTLIB_ERR_INTERFACE_E8                         0xE0001FE8L  
    #define FTLIB_ERR_INTERFACE_E9                         0xE0001FE9L  
    #define FTLIB_ERR_INTERFACE_EA                         0xE0001FEAL  
    #define FTLIB_ERR_INTERFACE_EB                         0xE0001FEBL  
    #define FTLIB_ERR_INTERFACE_EC                         0xE0001FECL  
    #define FTLIB_ERR_INTERFACE_ED                         0xE0001FEDL  
    #define FTLIB_ERR_INTERFACE_EE                         0xE0001FEEL  
    #define FTLIB_ERR_INTERFACE_EF                         0xE0001FEFL  

    #define FTLIB_ERR_INTERFACE_F0                         0xE0001FF0L  
    #define FTLIB_ERR_INTERFACE_F1                         0xE0001FF1L  
    #define FTLIB_ERR_INTERFACE_F2                         0xE0001FF2L  
    #define FTLIB_ERR_INTERFACE_F3                         0xE0001FF3L  
    #define FTLIB_ERR_INTERFACE_F4                         0xE0001FF4L  
    #define FTLIB_ERR_INTERFACE_F5                         0xE0001FF5L  
    #define FTLIB_ERR_INTERFACE_F6                         0xE0001FF6L  
    #define FTLIB_ERR_INTERFACE_F7                         0xE0001FF7L  
    #define FTLIB_ERR_INTERFACE_F8                         0xE0001FF8L  
    #define FTLIB_ERR_INTERFACE_F9                         0xE0001FF9L  
    #define FTLIB_ERR_INTERFACE_FA                         0xE0001FFAL  
    #define FTLIB_ERR_INTERFACE_FB                         0xE0001FFBL  
    #define FTLIB_ERR_INTERFACE_FC                         0xE0001FFCL  
    #define FTLIB_ERR_INTERFACE_FD                         0xE0001FFDL  
    #define FTLIB_ERR_INTERFACE_FE                         0xE0001FFEL  
    #define FTLIB_ERR_INTERFACE_FF                         0xE0001FFFL  

    #define FTLIB_ERR_SOUND_FILE_WRONG_1                   0xE0002001L 
    #define FTLIB_ERR_SOUND_FILE_WRONG_2                   0xE0002002L 
    #define FTLIB_ERR_SOUND_FILE_WRONG_3                   0xE0002003L 
    #define FTLIB_ERR_WRONG_SOUND_INDEX                    0xE0002004L 
    #define FTLIB_ERR_SOUND_DOWNLOAD_1                     0xE0002005L 
    #define FTLIB_ERR_SOUND_DOWNLOAD_2                     0xE0002006L 
    #define FTLIB_ERR_SOUND_MEMORY_1                       0xE0002007L 
    #define FTLIB_ERR_SOUND_MEMORY_2                       0xE0002008L 
    #define FTLIB_ERR_SOUND_MEMORY_3                       0xE0002009L
    #define FTLIB_ERR_SOUND_MEMORY_4                       0xE000200AL

#endif



