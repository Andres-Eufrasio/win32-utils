#include <iostream>
#include <libloaderapi.h>
#include <minwinbase.h>
#include <minwindef.h>
#include <windows.h>
#include <winnt.h>
#include <thread>
#include <atomic>

std::atomic<bool> autoOn = false;
void SimulateClick(){
	while (1){
		Sleep(100);
		while (autoOn){
			INPUT inputs[2] ={0};
			ZeroMemory(inputs, sizeof(inputs));

			inputs[0].type = INPUT_MOUSE;
			inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

			inputs[1].type = INPUT_MOUSE;
			inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

			UINT uClick = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
			if ((uClick) != ARRAYSIZE(inputs)){
				std::cerr << "SendInput failed mouse";
			}
		}
	}
}

LRESULT CALLBACK keyboard(int code, WPARAM wParam, LPARAM lParam){
	tagKBDLLHOOKSTRUCT* hookptr = (tagKBDLLHOOKSTRUCT*)lParam;
	auto hookKey = hookptr-> vkCode;
	if (code >= 0){
		if (wParam == WM_KEYDOWN && hookKey == VK_HOME){
			if (autoOn) std::cout << "off \n";
			else std::cout << "on \n";
			autoOn = !autoOn;
			return 1;
		}
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}

int main(){
	HHOOK hHook = SetWindowsHookExA(
		WH_KEYBOARD_LL,
		keyboard,
		GetModuleHandle(nullptr),
		0
	);

	std::thread clickLoop(SimulateClick);
	clickLoop.detach();
	if (hHook){
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0) > 0){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		UnhookWindowsHookEx(hHook);
	}
	else{
		std::cerr << "hook failed";
	}
}
