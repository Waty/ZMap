#include "stdio.h"
#include "ZMap.h"
#include <Windows.h>


uint32_t CMobPoolPtr = 0x1813928;
auto GetAt = reinterpret_cast<__POSITION*&(__thiscall*)(ZMap<unsigned long, __POSITION*, unsigned long>, const unsigned long&, __POSITION*&)>(0xC8D1A0);

class CMobPool
{
public:
	virtual ~CMobPool() { };

	ZMap<unsigned long, __POSITION *, unsigned long> m_mMob;

	// we don't care about the other ones atm

	/*	ZList<ZRef<CMob>> m_lMob;
	ZList<ZRef<CMob>> m_lMobDelayedDead;
	ZList<ZRef<CMob>> m_lMobDeadProcess;
	ZRef<CMob> m_pMobDamagedByMob;
	int m_tLastHitMobDamagedByMob;
	ZRef<CMob> m_pGuidedMob;
	unsigned int m_dwMobCrcKey;

	static CMobPool* GetInstance();
	static int GetCount();
	CMob* GetMob(unsigned int dwMobId);

	static std::list<CMob*> ValidMobs;*/
};

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

DWORD WINAPI main(LPVOID param)
{
	InitConsole();

	auto pool = *reinterpret_cast<CMobPool**>(CMobPoolPtr);

	printf("waiting for CMobPool to initialize...");
	while (!pool) {}
	printf("CMobPool has initialized, hit any key to start testing");
	getchar();

	__POSITION* pos = nullptr;
	printf("maple GetAt(0) returned %p", GetAt(pool->m_mMob, 0, pos));
	printf("Waty  GetAt(0) returned %p", pool->m_mMob.get_at(0, pos));
}


BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		CreateThread(nullptr, 0, main, nullptr, 0, nullptr);;
	}
	return TRUE;
}
