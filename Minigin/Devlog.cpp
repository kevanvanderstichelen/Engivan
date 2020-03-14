#include "MiniginPCH.h"
#include <Windows.h>
#include "Devlog.h"

HANDLE dae::Devlog::m_ConsoleHandle = nullptr;

dae::Devlog::Devlog()
{
#ifdef _DEBUG
	AllocConsole();
	FILE* fDummy;
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
	m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	Print("Devlog activated. ");
#endif
}

dae::Devlog::~Devlog()
{
#ifdef _DEBUG
	FreeConsole();
#endif
}

void dae::Devlog::Print(const std::wstring& message)
{
	
#ifdef _DEBUG
	SetConsoleTextAttribute(m_ConsoleHandle, ConsoleColor::LightGray);
	std::wcout << "[DEVLOG] [LOG] : " << message << std::endl;
#else
	UNREFERENCED_PARAMETER(message);
#endif
}

void dae::Devlog::Print(const std::string& message)
{
#ifdef _DEBUG
	SetConsoleTextAttribute(m_ConsoleHandle, ConsoleColor::LightGray);
	std::cout << "[DEVLOG] [LOG] : " << message << std::endl;
#else
	UNREFERENCED_PARAMETER(message);
#endif
}

void dae::Devlog::PrintWarning(const std::wstring& message)
{
#ifdef _DEBUG
	SetConsoleTextAttribute(m_ConsoleHandle, ConsoleColor::Yellow);
	std::wcout << "[DEVLOG] [WARNING] : " << message << std::endl;
#else
	UNREFERENCED_PARAMETER(message);
#endif
}

void dae::Devlog::PrintWarning(const std::string& message)
{
#ifdef _DEBUG
	SetConsoleTextAttribute(m_ConsoleHandle, ConsoleColor::Yellow);
	std::cout << "[DEVLOG] [WARNING] : " << message << std::endl;
#else
	UNREFERENCED_PARAMETER(message);
#endif
}

void dae::Devlog::PrintError(const std::wstring& message)
{
#ifdef _DEBUG
	SetConsoleTextAttribute(m_ConsoleHandle, ConsoleColor::Red);
	std::wcout << "[DEVLOG] [ERROR] : " << message << std::endl;
#else
	UNREFERENCED_PARAMETER(message);
#endif
}

void dae::Devlog::PrintError(const std::string& message)
{
#ifdef _DEBUG
	SetConsoleTextAttribute(m_ConsoleHandle, ConsoleColor::Red);
	std::cout << "[DEVLOG] [ERROR] : " << message << std::endl;
#else
	UNREFERENCED_PARAMETER(message);
#endif
}
