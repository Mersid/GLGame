#pragma once
#include <iostream>

#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define DebugInit() \
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE); \
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT); \
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)

#ifdef _DEBUG
	#define Log(message) \
		std::cout << __FILE__ << ":" << __LINE__ << " in function " << __FUNCTION__ << std::endl << (message) << std::endl << std::endl
#else
	#define Log(message)
#endif
