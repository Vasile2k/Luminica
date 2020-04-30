#pragma once

#ifdef _DEBUG

#define entry_point int main()

#else

#define entry_point int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)

#endif
