// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <windows.h>
#include <fstream>
#include "LocalXInput.h"
#include "XInputProxy.h"

#define EXPORT comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)

struct xinput1_3_dll {
	HMODULE dll;
	LPXIENABLE OrignalXInputEnable;
	LPXIGETBATINFO OrignalXInputGetBatteryInformation;
	LPXIGETCAP OrignalXInputGetCapabilities;
	LPXIGETADGUIDS OrignalXInputGetDSoundAudioDeviceGuids;
	LPXIGETKEY OrignalXInputGetKeystroke;
	LPXIGETSTATE OrignalXInputGetState;
	LPXISETSTATE OrignalXInputSetState;
} xinput1_3;

static XINPUT_DEVICE_CALIBRATION XboxCal = XBOX_CAL;
static XINPUT_DEVICE_CALIBRATION *cals[4];

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	TCHAR path[MAX_PATH*2];
//	std::ofstream log_file;
//	log_file.open("C:\\Users\\craig\\Documents\\XInputProxy.txt", std::ofstream::app);
//	log_file << "Calling XInputProxy: " << ul_reason_for_call << std::endl;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		CopyMemory(path + GetSystemDirectory(path, MAX_PATH - 39), L"\\xinput1_3.org.dll", 40);
//		log_file << "Loading Library: " << path << std::endl;
		xinput1_3.dll = LoadLibrary(path);
		if (xinput1_3.dll == NULL)
		{
			MessageBox(0, path, L"Proxy", MB_ICONERROR);
			ExitProcess(0);
		}
		xinput1_3.OrignalXInputEnable = (LPXIENABLE)GetProcAddress(xinput1_3.dll, "XInputEnable");
		xinput1_3.OrignalXInputGetBatteryInformation = (LPXIGETBATINFO)GetProcAddress(xinput1_3.dll, "XInputGetBatteryInformation");
		xinput1_3.OrignalXInputGetCapabilities = (LPXIGETCAP)GetProcAddress(xinput1_3.dll, "XInputGetCapabilities");
		xinput1_3.OrignalXInputGetDSoundAudioDeviceGuids = (LPXIGETADGUIDS)GetProcAddress(xinput1_3.dll, "XInputGetDSoundAudioDeviceGuids");
		xinput1_3.OrignalXInputGetKeystroke = (LPXIGETKEY)GetProcAddress(xinput1_3.dll, "XInputGetKeystroke");
		xinput1_3.OrignalXInputGetState = (LPXIGETSTATE)GetProcAddress(xinput1_3.dll, "XInputGetState");
		xinput1_3.OrignalXInputSetState = (LPXISETSTATE)GetProcAddress(xinput1_3.dll, "XInputSetState");

		for (int i = 0; i < 4; i++)
		{
			cals[i] = &XboxCal;
		}

//		log_file << cals[3]->axes[XINPUT_AXIS_RX].mid << std::endl;

		break;
	}
	case DLL_PROCESS_DETACH:
	{
		FreeLibrary(xinput1_3.dll);
	}
	break;
	}

//	log_file << "Returning TRUE\n";

//	log_file.close();

	return TRUE;
}

SHORT calibrateAxis(SHORT raw_value, XINPUT_AXIS_CALIBRATION* cal, int deadzone)
{
	int val = (int)raw_value;

	val = raw_value - cal->mid;

	if (val >= -deadzone && val <= deadzone)
		val = 0;
	else
	{
		if (val > 0)
		{
			//val is now between 0 and max-deadzone-mid
			//val needs to be between 0 and 32767
			//so val = val * 32767 / (max-deadzone-mid)
			val -= deadzone;
			val *= 32767;
			val /= (cal->max - deadzone - cal->mid);
		}
		else
		{
			val += deadzone;
			val *= -32768;
			val /= (cal->min + deadzone - cal->mid);
		}

		if (val < -32768)
			val = -32768;
		else if (val > 32767)
			val = 32767;
	}

	return (SHORT)val;
}

DWORD WINAPI XInputGetState(DWORD dwUserIndex, XINPUT_STATE* pState)
{
#pragma EXPORT
	DWORD ret = xinput1_3.OrignalXInputGetState(dwUserIndex, pState);
	pState->Gamepad.sThumbLX = calibrateAxis(pState->Gamepad.sThumbLX, &cals[dwUserIndex]->axes[XINPUT_AXIS_LX], cals[dwUserIndex]->deadzone);
	pState->Gamepad.sThumbLY = calibrateAxis(pState->Gamepad.sThumbLY, &cals[dwUserIndex]->axes[XINPUT_AXIS_LY], cals[dwUserIndex]->deadzone);
	pState->Gamepad.sThumbRX = calibrateAxis(pState->Gamepad.sThumbRX, &cals[dwUserIndex]->axes[XINPUT_AXIS_RX], cals[dwUserIndex]->deadzone);
	pState->Gamepad.sThumbRY = calibrateAxis(pState->Gamepad.sThumbRY, &cals[dwUserIndex]->axes[XINPUT_AXIS_RY], cals[dwUserIndex]->deadzone);
	return ret;
}

DWORD WINAPI XInputSetState(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration)
{
#pragma EXPORT
	return xinput1_3.OrignalXInputSetState(dwUserIndex, pVibration);
}

DWORD WINAPI XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities)
{
#pragma EXPORT
	return xinput1_3.OrignalXInputGetCapabilities(dwUserIndex, dwFlags, pCapabilities);
}

void WINAPI XInputEnable(BOOL enable)
{
#pragma EXPORT
	return xinput1_3.OrignalXInputEnable(enable);
}

DWORD WINAPI XInputGetDSoundAudioDeviceGuids(DWORD dwUserIndex, GUID* pDSoundRenderGuid, GUID* pDSoundCaptureGuid)
{
#pragma EXPORT
	return xinput1_3.OrignalXInputGetDSoundAudioDeviceGuids(dwUserIndex, pDSoundRenderGuid, pDSoundCaptureGuid);
}

DWORD WINAPI XInputGetBatteryInformation(DWORD dwUserIndex, BYTE devType, XINPUT_BATTERY_INFORMATION* pBatteryInformation)
{
#pragma EXPORT
	return xinput1_3.OrignalXInputGetBatteryInformation(dwUserIndex, devType, pBatteryInformation);
}

DWORD WINAPI XInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, PXINPUT_KEYSTROKE pKeystroke)
{
#pragma EXPORT
	return xinput1_3.OrignalXInputGetKeystroke(dwUserIndex, dwReserved, pKeystroke);
}