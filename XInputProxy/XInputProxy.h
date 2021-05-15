#pragma once

#include "LocalXInput.h"
/*
#ifdef XINPUTPROXY_EXPORTS
#define XINPUTPROXY_API __declspec(dllexport)
#else
#define XINPUTPROXY_API __declspec(dllimport)
#endif*/

#define XINPUTPROXY_API

/*
Xbox 360 Controller 1
LX
-11600, 2600
LY
-6000, 600
RX
-8000, 4400
RY
-2500, 5500
*/

#define XBOX_X1 {-32768, 32767, -4500}
#define XBOX_Y1 {-32768, 32767, -2700}
#define XBOX_X2 {-32768, 32767, -1800}
#define XBOX_Y2 {-32768, 32767, 1500}
#define XBOX_DEADZONE 7000
#define XBOX_CAL {{XBOX_X1, XBOX_Y1, XBOX_X2, XBOX_Y2}, XBOX_DEADZONE}

#define XINPUT_AXIS_LX 0
#define XINPUT_AXIS_LY 1
#define XINPUT_AXIS_RX 2
#define XINPUT_AXIS_RY 3

typedef struct xinput_axis_calibration {
    int min, max, mid;
} XINPUT_AXIS_CALIBRATION;

typedef struct xinput_device_calibration {
    XINPUT_AXIS_CALIBRATION axes[4];
    int deadzone;
} XINPUT_DEVICE_CALIBRATION;

extern "C" XINPUTPROXY_API DWORD WINAPI XInputGetState
(
    __in  DWORD         dwUserIndex,  // Index of the gamer associated with the device
    __out XINPUT_STATE * pState        // Receives the current state
);

extern "C" XINPUTPROXY_API DWORD WINAPI XInputSetState
(
    __in DWORD             dwUserIndex,  // Index of the gamer associated with the device
    __in XINPUT_VIBRATION* pVibration    // The vibration information to send to the controller
);

extern "C" XINPUTPROXY_API DWORD WINAPI XInputGetCapabilities
(
    __in  DWORD                dwUserIndex,   // Index of the gamer associated with the device
    __in  DWORD                dwFlags,       // Input flags that identify the device type
    __out XINPUT_CAPABILITIES* pCapabilities  // Receives the capabilities
);

extern "C" XINPUTPROXY_API void WINAPI XInputEnable
(
    __in BOOL enable     // [in] Indicates whether xinput is enabled or disabled. 
);

extern "C" XINPUTPROXY_API DWORD WINAPI XInputGetDSoundAudioDeviceGuids
(
    __in  DWORD dwUserIndex,          // Index of the gamer associated with the device
    __out GUID* pDSoundRenderGuid,    // DSound device ID for render
    __out GUID* pDSoundCaptureGuid    // DSound device ID for capture
);

extern "C" XINPUTPROXY_API DWORD WINAPI XInputGetBatteryInformation
(
    __in  DWORD                       dwUserIndex,        // Index of the gamer associated with the device
    __in  BYTE                        devType,            // Which device on this user index
    __out XINPUT_BATTERY_INFORMATION* pBatteryInformation // Contains the level and types of batteries
);

extern "C" XINPUTPROXY_API DWORD WINAPI XInputGetKeystroke
(
    __in       DWORD dwUserIndex,              // Index of the gamer associated with the device
    __reserved DWORD dwReserved,               // Reserved for future use
    __out      PXINPUT_KEYSTROKE pKeystroke    // Pointer to an XINPUT_KEYSTROKE structure that receives an input event.
);

/*
typedef DWORD (__stdcall *LPXIGETSTATE)(DWORD, XINPUT_STATE*);
typedef DWORD(__stdcall *LPXISETSTATE)(DWORD, XINPUT_VIBRATION*);
typedef DWORD(__stdcall *LPXIGETCAP)(DWORD, DWORD, XINPUT_CAPABILITIES);
typedef DWORD(__stdcall *LPXIENABLE)(BOOL);
typedef DWORD(__stdcall* LPXIGETBATINFO)(DWORD, BYTE, XINPUT_BATTERY_INFORMATION*);
typedef DWORD(__stdcall* LPXIGETADGUIDS)(DWORD, GUID*, GUID*);
typedef DWORD(__stdcall* LPXIGETKEY)(DWORD, DWORD, PXINPUT_KEYSTROKE);
*/