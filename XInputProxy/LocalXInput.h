#pragma once

#include <windef.h>

#define XINPUT_GAMEPAD_DPAD_UP          0x0001
#define XINPUT_GAMEPAD_DPAD_DOWN        0x0002
#define XINPUT_GAMEPAD_DPAD_LEFT        0x0004
#define XINPUT_GAMEPAD_DPAD_RIGHT       0x0008
#define XINPUT_GAMEPAD_START            0x0010
#define XINPUT_GAMEPAD_BACK             0x0020
#define XINPUT_GAMEPAD_LEFT_THUMB       0x0040
#define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080
#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
#define XINPUT_GAMEPAD_A                0x1000
#define XINPUT_GAMEPAD_B                0x2000
#define XINPUT_GAMEPAD_X                0x4000
#define XINPUT_GAMEPAD_Y                0x8000

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD    30

#define XUSER_MAX_COUNT                 4

typedef struct _XINPUT_GAMEPAD
{
    WORD                                wButtons;
    BYTE                                bLeftTrigger;
    BYTE                                bRightTrigger;
    SHORT                               sThumbLX;
    SHORT                               sThumbLY;
    SHORT                               sThumbRX;
    SHORT                               sThumbRY;
} XINPUT_GAMEPAD, * PXINPUT_GAMEPAD;

typedef struct _XINPUT_STATE
{
    DWORD                               dwPacketNumber;
    XINPUT_GAMEPAD                      Gamepad;
} XINPUT_STATE, * PXINPUT_STATE;

typedef struct _XINPUT_VIBRATION
{
    WORD                                wLeftMotorSpeed;
    WORD                                wRightMotorSpeed;
} XINPUT_VIBRATION, * PXINPUT_VIBRATION;

typedef struct _XINPUT_CAPABILITIES
{
    BYTE                                Type;
    BYTE                                SubType;
    WORD                                Flags;
    XINPUT_GAMEPAD                      Gamepad;
    XINPUT_VIBRATION                    Vibration;
} XINPUT_CAPABILITIES, * PXINPUT_CAPABILITIES;

typedef struct _XINPUT_BATTERY_INFORMATION
{
    BYTE BatteryType;
    BYTE BatteryLevel;
} XINPUT_BATTERY_INFORMATION, * PXINPUT_BATTERY_INFORMATION;

typedef struct _XINPUT_KEYSTROKE
{
    WORD    VirtualKey;
    WCHAR   Unicode;
    WORD    Flags;
    BYTE    UserIndex;
    BYTE    HidCode;
} XINPUT_KEYSTROKE, * PXINPUT_KEYSTROKE;

typedef DWORD(__stdcall *LPXIGETSTATE)(DWORD, XINPUT_STATE*);
typedef DWORD(__stdcall *LPXISETSTATE)(DWORD, XINPUT_VIBRATION*);
typedef DWORD(__stdcall *LPXIGETCAP)(DWORD, DWORD, XINPUT_CAPABILITIES*);
typedef void(__stdcall *LPXIENABLE)(BOOL);
typedef DWORD(__stdcall* LPXIGETBATINFO)(DWORD, BYTE, XINPUT_BATTERY_INFORMATION*);
typedef DWORD(__stdcall* LPXIGETADGUIDS)(DWORD, GUID*, GUID*);
typedef DWORD(__stdcall* LPXIGETKEY)(DWORD, DWORD, PXINPUT_KEYSTROKE);

/*
DWORD WINAPI XInputGetState
(
    _In_  DWORD         dwUserIndex,  // Index of the gamer associated with the device
    _Out_ XINPUT_STATE* pState        // Receives the current state
);

DWORD WINAPI XInputSetState
(
    _In_ DWORD             dwUserIndex,  // Index of the gamer associated with the device
    _In_ XINPUT_VIBRATION* pVibration    // The vibration information to send to the controller
);

DWORD WINAPI XInputGetCapabilities
(
    _In_  DWORD                dwUserIndex,   // Index of the gamer associated with the device
    _In_  DWORD                dwFlags,       // Input flags that identify the device type
    _Out_ XINPUT_CAPABILITIES* pCapabilities  // Receives the capabilities
);

void WINAPI XInputEnable
(
    _In_ BOOL enable     // [in] Indicates whether xinput is enabled or disabled.
);
*/