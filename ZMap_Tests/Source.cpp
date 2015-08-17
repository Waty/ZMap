#include "stdio.h"
#include "ZMap.h"
#include <Windows.h>
#include <fstream>

auto jobMap = 0x197BF54;
auto GetAt = reinterpret_cast<char*&(__thiscall*)(ZMap<uint32_t, char*, uint32_t>*, uint32_t const&, char*&)>(0xEA2910);
auto get_job_name = reinterpret_cast<char*(__cdecl*)(int jobCodem, uint32_t idk)>(0x5D4500);

void InitConsole()
{
	HWND handle = GetConsoleWindow();
	if (handle == nullptr)
	{
		AllocConsole();
		FILE* stream;
		freopen_s(&stream, "CONOUT$", "w", stdout);
		freopen_s(&stream, "CONIN$", "r", stdin);
	}
	else ShowWindow(handle, SW_SHOW);
}

void save_as_csv(ZMap<uint32_t, char*, uint32_t>* s_mJobName)
{
	std::ofstream ostream{ "jobids.csv", std::ofstream::out };
	ostream << "\"Id\",\"JobName\"";
	s_mJobName->for_each([&ostream](uint32_t id, char* msg)
		{
			ostream << "\"" << msg << "\",\"" << id << "\"\n";
		});
}

DWORD WINAPI main(LPVOID /*param*/)
{
	InitConsole();

	printf("Hit any key to start testing");
	getchar();


	printf("maple get_job_name(2210,0) returned %s\n", get_job_name(2210, 0));

	ZMap<uint32_t, char*, uint32_t>* s_mJobName = reinterpret_cast<ZMap<uint32_t, char*, uint32_t>*>(0x197BF54);
	char* result = nullptr;
	printf("maple GetAt(2210) returned %s\n", GetAt(s_mJobName, 2210, result));

	printf("Waty  GetAt(2210) returned %s\n", *s_mJobName->get_at(2210, result));

	printf("time to test for_each...");
	getchar();

	s_mJobName->for_each([](uint32_t id, char* msg)
	{
		printf("id=%i, value='%s'\n", id, msg);
	});

	getchar();

	save_as_csv(s_mJobName);

	TerminateProcess(GetCurrentProcess(), 0x1337);
}


BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		CreateThread(nullptr, 0, main, nullptr, 0, nullptr);;
	}
	return TRUE;
}
