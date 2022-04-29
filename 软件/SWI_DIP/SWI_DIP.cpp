#include "SWI_DIP.h"
#include "dip_settings.h"

#pragma region GLOBAL
DipSettings settings;
#pragma endregion

int main() {
	InitializeSettings(settings);
	cout << settings.houghCircle_param2;
	return 0;
}
