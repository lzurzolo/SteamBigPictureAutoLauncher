#include <iostream>
#include <Windows.h>
#include <cassert>
#include "inih/INIReader.h"

struct Device
{
	std::string AudioName;
	int VideoID;

	Device()
	{
		AudioName = " ";
		VideoID = -1;
	}

	Device(std::string aName, int vID)
	{
		AudioName = aName;
		VideoID = vID;
	}
};

std::wstring StringToWideString(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void SetPrimaryDisplay(int ID)
{
	std::string params = "/SetPrimary " + std::to_string(ID);
	ShellExecuteA(NULL, "open", ".\\multimonitortool\\multimonitortool.exe", params.c_str(), NULL, SW_SHOW);
}

void SetPrimaryAudio(std::string name)
{
	std::string params = "setdefaultsounddevice " + name;
	ShellExecuteA(NULL, "open", ".\\nircmd\\nircmd.exe", params.c_str(), NULL, SW_SHOW);
}

void LaunchSteam(std::wstring steamPath)
{
	LPCWSTR SteamExec = steamPath.c_str();
	std::wstring SteamBigPictureArg = L"-start steam://open/bigpicture";

	SHELLEXECUTEINFO SteamExecInfo = { 0 };
	SteamExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	SteamExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	SteamExecInfo.hwnd = NULL;
	SteamExecInfo.lpVerb = NULL;
	SteamExecInfo.lpFile = SteamExec;
	SteamExecInfo.lpParameters = SteamBigPictureArg.c_str();
	SteamExecInfo.lpDirectory = NULL;
	SteamExecInfo.nShow = SW_SHOW;
	SteamExecInfo.hInstApp = NULL;
	ShellExecuteEx(&SteamExecInfo);
	WaitForSingleObject(SteamExecInfo.hProcess, INFINITE);
}

int main()
{
	INIReader INIFile("config.ini");
	if (INIFile.ParseError() != 0)
	{
		std::cerr << "Can't load config.ini" << std::endl;
		return -1;
	}

	Device TV{ INIFile.Get("TV", "AudioName", " "), INIFile.GetInteger("TV", "VideoID", -1) };
	Device Monitor{ INIFile.Get("Monitor", "AudioName", " "), INIFile.GetInteger("Monitor", "VideoID", -1) };
	std::string SteamPath = INIFile.Get("Paths", "SteamExec", ".");

	SetPrimaryDisplay(TV.VideoID);
	SetPrimaryAudio(TV.AudioName);
	LaunchSteam(StringToWideString(SteamPath));
	SetPrimaryDisplay(Monitor.VideoID);
	SetPrimaryAudio(Monitor.AudioName);
}
