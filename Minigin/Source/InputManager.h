#pragma once
#include "Mainstructs.h"
#include <XInput.h>
#include "Singleton.h"
#include "MainStructs.h"

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689

namespace dae
{
	enum class XBOXButton
	{
		A, B, X, Y,
		LB, RB, TL, TR,
		Left, Right, Up, Down,
        Back, Start, LT, RT
	};

	enum class XBOXAxis
	{
		TL, TR, LT, RT
	};

	enum class ViberateValue : int
	{
		None = 0, Soft = 1000, Moderate = 5000, Hard = 30000, VeryHard = 65535
	};

	class Command;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		explicit InputManager(const uint& maxControllerPlayers = 0);
		~InputManager();
		bool ProcessInput();

		//XBOX CONTROLLER
		void SetMaxControllerPlayers(const uint& maxPlayers);
		bool IsControllerPressed(const XBOXButton& button);

		bool IsControllerPressed(const XBOXButton& button, const uint& playerNr);
		bool IsControllerPressedDown(const XBOXButton& button, const uint& playerNr);
		void Update(float elapsed);
		Command* GetCommand(const XBOXButton& button) const;
		void AssignCommandToButton(const XBOXButton& button, Command* command);
		void ViberateController(const ViberateValue& leftValue, const ViberateValue& rightValue, const uint controllerNr);
		void ViberateController(const ViberateValue& leftValue, const ViberateValue& rightValue, const uint controllerNr, const float burstTime);
		const FVector2 GetControllerLeftAxis(const uint controllerNr = 0) const;
		const FVector2 GetControllerRightAxis(const uint controllerNr = 0) const;
		const float GetControllerLeftTrigger(const uint controllerNr = 0) const;
		const float GetControllerRightTrigger(const uint controllerNr = 0) const;

		const bool IsControllerConnected(const uint& controllerNr = 0U) const;

		const uint GetMaxControllerPlayers() const { return m_ControllerStates.size(); }

	private:
		//XBOX CONTROlLER STATE
		struct ControllerState
		{
			XINPUT_STATE state;
			bool isConnected = false;
			XINPUT_VIBRATION viberation;
			float viberateTime = 0.f;
			FVector2 joystickLeft;
			FVector2 joystickRight;
			float triggerLeft;
			float triggerRight;
			int previousState;
		};

		std::vector<ControllerState> m_ControllerStates;

		//Controller Command Buttons
		Command* m_Button_A = nullptr;
		Command* m_Button_B = nullptr;
		Command* m_Button_Y = nullptr;
		Command* m_Button_X = nullptr;
		Command* m_Button_LB = nullptr;
		Command* m_Button_RB = nullptr;
		Command* m_Button_Thumb_L = nullptr;
		Command* m_Button_Thumb_R = nullptr;
		Command* m_Button_Left = nullptr;
		Command* m_Button_Right = nullptr;
		Command* m_Button_Up = nullptr;
		Command* m_Button_Down = nullptr;
		Command* m_Button_Back = nullptr;
		Command* m_Button_Start = nullptr;
		Command* m_Button_LT = nullptr;
		Command* m_Button_RT = nullptr;

		bool CheckXBOXButtonDown(const int& button, const uint& playerNr);

	};

}
