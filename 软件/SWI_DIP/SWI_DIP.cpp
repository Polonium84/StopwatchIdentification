#include "SWI_DIP.h"
#include "dip_settings.h"

#pragma region GLOBAL
DipSettings settings;
#pragma endregion

int main(int argc, char** argv) {
	InitializeSettings(settings);
	if (AutoMode(argc, argv))
		settings.dipMode = AUTO;
	cout << settings.houghCircle_param2;
	return 0;
}
bool AutoMode(int argc, char** argv) {
	string mode;
	if (argc > 1)
		mode = argv[1];
	if (mode.find("auto") != -1)
		return true;
	else
		return false;
}