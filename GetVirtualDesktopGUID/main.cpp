#include <cstddef>
#include <cstdio>
#include <ostream>
#include <windows.h>
#include <shobjidl.h>
#include <winerror.h>
#include <winnt.h>
#include <winscard.h>
#include <iostream>
#include <objbase.h>
int main(){

	HWND hwnd = GetForegroundWindow();
	if (!hwnd){
		std::cerr << "Foreground window failed capture";
	}
	IVirtualDesktopManager *pVirtualDesktopManager;
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr)){
		hr = CoCreateInstance(CLSID_VirtualDesktopManager, NULL, CLSCTX_ALL, IID_IVirtualDesktopManager, reinterpret_cast<void**>(&pVirtualDesktopManager));
		
		if (SUCCEEDED(hr)){

			//HWND hwnd = FindWindowW(L"Notepad", nullptr);	
			GUID deskID;

			HRESULT hr = pVirtualDesktopManager->GetWindowDesktopId(hwnd, &deskID);

			if (SUCCEEDED(hr)){

				OLECHAR buf[64];
				StringFromGUID2(deskID, buf, 64);
				std::wcout << buf << std::endl;
			}

			pVirtualDesktopManager->Release();
		}
		CoUninitialize();
	}
	if(hwnd) DestroyWindow(hwnd);

}
