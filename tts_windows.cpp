// tts_windows.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sapi.h>

wchar_t* convertCharArrayToLPCWSTR(const char* charArray) {
  wchar_t* wString = new wchar_t[4096];
  MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
  return wString;
}

int main(int argc, char* argv[]) {
  if (argc != 2 || argv[1] == NULL) {
    return 1;
  }
  ISpVoice * pVoice = NULL;

  if (FAILED(::CoInitialize(NULL))) {
    return 1;
  }

  HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
  if (SUCCEEDED(hr)) {
    hr = pVoice->Speak(convertCharArrayToLPCWSTR(argv[1]), SPF_IS_XML, NULL);
    pVoice->Release();
    pVoice = NULL;
  }

  ::CoUninitialize();
  return 0;
}