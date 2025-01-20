#include <cstdlib>
#include <string>
#include <iostream>
#include <cstring>
#ifdef _WIN32
#include <windows.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.System.Profile.h>
#endif

bool IsHandheld()
{
	// First test the environment variable
	const char* steamDeckEnv = std::getenv("SteamDeck");
	if (steamDeckEnv && std::strcmp(steamDeckEnv, "1") == 0)
		return true;

	const char* steamDeckEnvAlt = std::getenv("STEAM_DECK");
	if (steamDeckEnvAlt && std::strcmp(steamDeckEnvAlt, "1") == 0)
		return true;

#ifdef _WIN32
	try
	{
		using namespace winrt::Windows::System::Profile;

		// Initialize WinRT
		winrt::init_apartment();

		// Check if the device is in tablet mode
		auto currentMode = AnalyticsInfo::VersionInfo().DeviceFamily();
		if (currentMode == L"Windows.Tablet")
		{
			return true;
		}
	}
	catch (...)
	{
		// If the WinRT API is unavailable or fails, assume not in tablet mode
		return false;
	}
#endif

	return false; // Default to desktop mode for non-Windows platforms
}

void showPopup(const std::string& message, const std::string& title);

int main()
{
	if (IsHandheld())
		showPopup("Yes, we are in handheld mode", "Device Mode");
	else
		showPopup("We are in Desktop mode", "Device Mode");

	return 0;
}
