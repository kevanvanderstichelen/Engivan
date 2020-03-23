#pragma once
#include "Singleton.h"
#include <string>
#include <Windows.h>
namespace dae
{

	class Devlog final : public Singleton<Devlog>
	{
	public:
		Devlog();
		~Devlog();

		Devlog(const Devlog& other) = delete;
		Devlog(Devlog&& other) noexcept = delete;
		Devlog& operator=(const Devlog& other) = delete;
		Devlog& operator=(Devlog&& other) noexcept = delete;

		static void Print(const std::string& message);
		static void Print(const std::wstring& message);
		static void PrintWarning(const std::string& message);
		static void PrintWarning(const std::wstring& message);
		static void PrintError(const std::string& message);
		static void PrintError(const std::wstring& message);
	protected:
	private:

		enum ConsoleColor : int
		{
			Red = 12,
			DarkRed = 4,
			Gold = 22,
			Yellow = 14,
			LightGray = 7,
			DarkGray = 8,
		};

		static HANDLE m_ConsoleHandle;
	};
}


