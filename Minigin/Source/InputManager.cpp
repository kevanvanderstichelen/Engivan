#include "MiniginPCH.h"
#include "InputManager.h"
#include "Devlog.h"
#include "Utilities.h"
#include <SDL.h>
#include "Command.h"

//Max controller players default = 0
//For every controller player will check
dae::InputManager::InputManager(const uint& maxControllerPlayers)
{
	m_ControllerStates.resize(maxControllerPlayers);
	AssignCommandToButton(XBOXButton::Left, new TestCommand);
}

dae::InputManager::~InputManager()
{
	SAFE_DELETE(m_Button_A);
	SAFE_DELETE(m_Button_B);
	SAFE_DELETE(m_Button_Y);
	SAFE_DELETE(m_Button_X);
	SAFE_DELETE(m_Button_LB);
	SAFE_DELETE(m_Button_RB);
	SAFE_DELETE(m_Button_Thumb_L);
	SAFE_DELETE(m_Button_Thumb_R);
	SAFE_DELETE(m_Button_Left);
	SAFE_DELETE(m_Button_Right);
	SAFE_DELETE(m_Button_Up);
	SAFE_DELETE(m_Button_Down);
	SAFE_DELETE(m_Button_Back);
	SAFE_DELETE(m_Button_Start);
}

//Used for update checks connected controllers & Poll Events (such as QUIT button...)
bool dae::InputManager::ProcessInput()
{
	for (uint i = 0; i < m_ControllerStates.size(); i++)
	{
		//Get all input buttons states and register them here
		ZeroMemory(&m_ControllerStates[i].state, sizeof(XINPUT_STATE));
		DWORD Result = XInputGetState(i, &m_ControllerStates[i].state);
		m_ControllerStates[i].isConnected = (Result == ERROR_SUCCESS) ? true : false;
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			
		}
	}

	return true;
}

void dae::InputManager::SetMaxControllerPlayers(const uint& maxPlayers)
{
	m_ControllerStates.resize(maxPlayers);
}

//Player[0] Button will be checked, returns true when pressed button.
//DEBUG: Prints warning when Controller[0] is not connected and returns false.
bool dae::InputManager::IsControllerPressed(const XBOXButton& button)
{
	if (m_ControllerStates.size() <= 0)
	{
		Devlog::PrintWarning("InputManager::IsPressed() Max Player size Not Registered At initialize of InputManager");
		Devlog::PrintWarning("InputManager::IsPressed() MAX PLAYER SIZE: AUTOMATIC - RESIZED TO" + std::to_string(1));
		m_ControllerStates.resize(1);
		return false;
	}

#ifdef _DEBUG
	if (!m_ControllerStates[0].isConnected)
	{
		Devlog::PrintWarning("InputManager::IsPressed() Controller 1 Not Connected");
		return false;
	}
#endif

	switch (button)
	{
	case XBOXButton::A:
		return m_ControllerStates[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case XBOXButton::B:
		return m_ControllerStates[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case XBOXButton::X:
		return m_ControllerStates[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case XBOXButton::Y:
		return m_ControllerStates[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case XBOXButton::RB:
		return m_ControllerStates[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
	case XBOXButton::LB:
		return m_ControllerStates[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
	case XBOXButton::TL:
		return m_ControllerStates[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
	case XBOXButton::TR:
		return m_ControllerStates[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
	case XBOXButton::Left:
		return m_ControllerStates[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case XBOXButton::Right:
		return m_ControllerStates[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case XBOXButton::Up:
		return m_ControllerStates[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case XBOXButton::Down:
		return m_ControllerStates[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case XBOXButton::Start:
		return m_ControllerStates[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_START;
	case XBOXButton::Back:
		return m_ControllerStates[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
	case XBOXButton::RT:
		return m_ControllerStates[0].triggerRight > 0 ? true : false;
	case XBOXButton::LT:
		return m_ControllerStates[0].triggerLeft > 0 ? true : false;
	default: return false;
	}
}

//Player[playerNr] Button will be checked, returns true when pressed button.
//DEBUG: Prints warning when Controller[playerNr] is not connected and returns false.
bool dae::InputManager::IsControllerPressed(const XBOXButton& button, const uint& playerNr)
{

	if (m_ControllerStates.size() <= playerNr)
	{
		Devlog::PrintWarning("InputManager::IsPressed() Max Player size Not Registered At initialize of InputManager");
		Devlog::PrintWarning("InputManager::IsPressed() MAX PLAYER SIZE: AUTOMATIC - RESIZED TO " + std::to_string(playerNr + 1U));
		m_ControllerStates.resize(playerNr + 1U);
		return false;
	}

#ifdef _DEBUG

	if (!m_ControllerStates[playerNr].isConnected)
	{
		Devlog::PrintWarning("InputManager::IsPressed() Controller " + std::to_string(playerNr + 1U) + " Not Connected ");
		return false;
	}
#endif

	switch (button)
	{
	case XBOXButton::A:
		return m_ControllerStates[playerNr].state.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case XBOXButton::B:
		return m_ControllerStates[playerNr].state.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case XBOXButton::X:
		return m_ControllerStates[playerNr].state.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case XBOXButton::Y:
		return m_ControllerStates[playerNr].state.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case XBOXButton::RB:
		return m_ControllerStates[playerNr].state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
	case XBOXButton::LB:
		return m_ControllerStates[playerNr].state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
	case XBOXButton::TL: 
		return m_ControllerStates[playerNr].state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
	case XBOXButton::TR:  
		return m_ControllerStates[playerNr].state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
	case XBOXButton::Left:	  
		return m_ControllerStates[playerNr].state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case XBOXButton::Right:	 
		return m_ControllerStates[playerNr].state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case XBOXButton::Up:
		return m_ControllerStates[playerNr].state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case XBOXButton::Down:	
		return m_ControllerStates[playerNr].state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case XBOXButton::Start:
		return m_ControllerStates[playerNr].state.Gamepad.wButtons & XINPUT_GAMEPAD_START;
	case XBOXButton::Back:
		return m_ControllerStates[playerNr].state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
	case XBOXButton::RT:
		return m_ControllerStates[playerNr].triggerRight > 0 ? true : false;
	case XBOXButton::LT:
		return m_ControllerStates[playerNr].triggerLeft > 0 ? true : false;
	default: return false;
	}
}

void dae::InputManager::Update(float elapsed)
{
	for (uint i = 0; i < m_ControllerStates.size(); i++)
	{
		//Stop viberating when timer is set and when timer runs out stops viberating
		if (m_ControllerStates[i].viberateTime >= 0.f)
		{
			m_ControllerStates[i].viberateTime -= elapsed;
			if (m_ControllerStates[i].viberateTime <= 0.001f)
			{
				ViberateController(ViberateValue::None, ViberateValue::None, i);
			}
		}

		//Trigger returns value 0 - 255
		m_ControllerStates[i].triggerLeft = m_ControllerStates[i].state.Gamepad.bLeftTrigger;
		m_ControllerStates[i].triggerRight = m_ControllerStates[i].state.Gamepad.bRightTrigger;

		//Calculate Joystick positions ( LEFT )
		const float LX = m_ControllerStates[i].state.Gamepad.sThumbLX;
		const float LY = m_ControllerStates[i].state.Gamepad.sThumbLY;

		float magnitude = sqrt(LX * LX + LY * LY);

		float normLX = LX / magnitude;
		float normLY = LY / magnitude;

		float normalizedMagnitude = 0;

		if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			if (magnitude > 32767) magnitude = 32767;

			magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
			normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		}
		else normalizedMagnitude = 0.0;
		

		if (normLX != normLX) normLX = 0;
		if (normLY != normLY) normLY = 0;
		if (normalizedMagnitude == 0) normLX = normLY = 0;

		m_ControllerStates[i].joystickLeft.x = normLX;
		m_ControllerStates[i].joystickLeft.y = normLY;

		//Calculate Joystick positions ( RIGHT )
		const float RX = m_ControllerStates[i].state.Gamepad.sThumbRX;
		const float RY = m_ControllerStates[i].state.Gamepad.sThumbRY;

		magnitude = sqrt(RX * RX + RY * RY);

		if (magnitude > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			if (magnitude > 32767) magnitude = 32767;

			magnitude -= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
			normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		}
		else normalizedMagnitude = 0.0;

		float normRX = RX / magnitude;
		float normRY = RY / magnitude;

		if (normRX != normRX) normRX = 0;
		if (normRY != normRY) normRY = 0;
		if (normalizedMagnitude == 0) normRX = normRY = 0;

		m_ControllerStates[i].joystickLeft.x = normLX;
		m_ControllerStates[i].joystickLeft.y = normLY;

		m_ControllerStates[i].joystickRight.x = normRX;
		m_ControllerStates[i].joystickRight.y = normRY;

	}

}

//Retunrs NULL when no command is assigned
dae::Command* dae::InputManager::GetCommand(const XBOXButton& button) const
{
	switch (button)
	{
	case XBOXButton::A:
		if (!m_Button_A) Devlog::PrintError("InputManager::GetCommand() No Command Assigned to Button A");
		return m_Button_A;
	case XBOXButton::B:
		if (!m_Button_B) Devlog::PrintError("InputManager::GetCommand() No Command Assigned to Button B");
		return m_Button_B;
	case XBOXButton::X:
		if (!m_Button_X) Devlog::PrintError("InputManager::GetCommand() No Command Assigned to Button X");
		return m_Button_X;
	case XBOXButton::Y:
		if (!m_Button_Y) Devlog::PrintError("InputManager::GetCommand() No Command Assigned to Button Y");
		return m_Button_Y;
	case XBOXButton::RB:
		if (!m_Button_RB) Devlog::PrintError("InputManager::GetCommand() No Command Assigned to Button RB");
		return m_Button_RB;
	case XBOXButton::LB:
		if (!m_Button_LB) Devlog::PrintError("InputManager::GetCommand() No Command Assigned to Button LB");
		return m_Button_LB;
	case XBOXButton::TL:
		if (!m_Button_Thumb_L) Devlog::PrintError("InputManager::GetCommand() No Command Assigned to Button thumb left");
		return m_Button_Thumb_L;
	case XBOXButton::TR:
		if (!m_Button_Thumb_R) Devlog::PrintError("InputManager::GetCommand() No Command Assigned to Button thumb right");
		return m_Button_Thumb_R;
	case XBOXButton::Left:
		if (!m_Button_Left) Devlog::PrintError("InputManager::GetCommand() No Command Assigned to Button left");
		return m_Button_Left;
	case XBOXButton::Right:
		if (!m_Button_Right) Devlog::PrintError("InputManager::GetCommand() No Command Assigned to Button Right");
		return m_Button_Right;
	case XBOXButton::Up:
		if (!m_Button_Up) Devlog::PrintError("InputManager::GetCommand() No Command Assigned to Button up");
		return m_Button_Up;
	case XBOXButton::Down:
		if (!m_Button_Down) Devlog::PrintError("InputManager::GetCommand() No Command Assigned to Button Down");
		return m_Button_Down;
	case XBOXButton::Start:
		if (!m_Button_Start) Devlog::PrintError("InputManager::GetCommand() No Command Assigned to Button Start");
		return m_Button_Start;
	case XBOXButton::Back:
		if (!m_Button_Back) Devlog::PrintError("InputManager::GetCommand() No Command Assigned to Button back");
		return m_Button_Back;
	case XBOXButton::LT:
		if (!m_Button_LT) Devlog::PrintError("InputManager::GetCommand() No Command Assigned to LT Button");
		return m_Button_LT;
	case XBOXButton::RT:
		if (!m_Button_RT) Devlog::PrintError("InputManager::GetCommand() No Command Assigned to RT Button");
		return m_Button_RT;
	default: return nullptr;
	}
}

void dae::InputManager::AssignCommandToButton(const XBOXButton& button, Command* command)
{
	switch (button)
	{
	case XBOXButton::A:
		SAFE_DELETE(m_Button_A);
		m_Button_A = command;
		break;
	case XBOXButton::B:
		SAFE_DELETE(m_Button_B);
		m_Button_B = command;
		break;
	case XBOXButton::X:
		SAFE_DELETE(m_Button_X);
		m_Button_X = command;
		break;
	case XBOXButton::Y:
		SAFE_DELETE(m_Button_Y);
		m_Button_Y = command;
		break;
	case XBOXButton::RB:
		SAFE_DELETE(m_Button_RB);
		m_Button_RB = command;
		break;
	case XBOXButton::LB:
		SAFE_DELETE(m_Button_LB);
		m_Button_RB = command;
		break;
	case XBOXButton::TL:
		SAFE_DELETE(m_Button_Thumb_L);
		m_Button_Thumb_L = command;
		break;
	case XBOXButton::TR:
		SAFE_DELETE(m_Button_Thumb_R);
		m_Button_Thumb_R = command;
		break;
	case XBOXButton::Left:
		SAFE_DELETE(m_Button_Left);
		m_Button_Left = command;
		break;
	case XBOXButton::Right:
		SAFE_DELETE(m_Button_Right);
		m_Button_Right = command;
		break;
	case XBOXButton::Up:
		SAFE_DELETE(m_Button_Up);
		m_Button_Up = command;
		break;
	case XBOXButton::Down:
		SAFE_DELETE(m_Button_Down);
		m_Button_Down = command;
		break;
	case XBOXButton::Start:
		SAFE_DELETE(m_Button_Start);
		m_Button_Start = command;
		break;
	case XBOXButton::Back:
		SAFE_DELETE(m_Button_Back);
		m_Button_Back = command;
		break;
	case XBOXButton::LT:
		SAFE_DELETE(m_Button_LT);
		m_Button_Back = command;
		break;
	case XBOXButton::RT:
		SAFE_DELETE(m_Button_RT);
		m_Button_Back = command;
		break;
	}
}

//Permanent viberate, stops only when ViberateValue::None is called again
void dae::InputManager::ViberateController(const ViberateValue& leftValue, const ViberateValue& rightValue, const uint controllerNr)
{
	
	ZeroMemory(&m_ControllerStates[controllerNr].viberation, sizeof(XINPUT_VIBRATION));

	m_ControllerStates[controllerNr].viberation.wLeftMotorSpeed = static_cast<WORD>(leftValue);
	m_ControllerStates[controllerNr].viberation.wRightMotorSpeed = static_cast<WORD>(rightValue);

	XInputSetState(controllerNr, &m_ControllerStates[controllerNr].viberation);

}

//Viberate controller with time ( in seconds )
void dae::InputManager::ViberateController(const ViberateValue& leftValue, const ViberateValue& rightValue, const uint controllerNr, const float burstTime)
{
	ViberateController(leftValue, rightValue, controllerNr);
	m_ControllerStates[controllerNr].viberateTime = burstTime;
}

const FVector2 dae::InputManager::GetControllerLeftAxis(const uint controllerNr) const
{
	if (m_ControllerStates.size() <= controllerNr)
	{
		Devlog::PrintWarning("InputManager::GetControllerLeftAxis Controller Nr out of bound! returning nothing.");
		return{};
	}
	return m_ControllerStates[controllerNr].joystickLeft;
}

const FVector2 dae::InputManager::GetControllerRightAxis(const uint controllerNr) const
{
	if (m_ControllerStates.size() <= controllerNr)
	{
		Devlog::PrintWarning("InputManager::GetControllerRightAxis Controller Nr out of bound! returning nothing.");
		return{};
	}
	return m_ControllerStates[controllerNr].joystickRight;
}

const float dae::InputManager::GetControllerLeftTrigger(const uint controllerNr) const
{
	if (m_ControllerStates.size() <= controllerNr)
	{
		Devlog::PrintWarning("InputManager::GetControllerLeftTrigger Controller Nr out of bound! returning nothing.");
		return{};
	}
	return m_ControllerStates[controllerNr].triggerLeft;
}

const float dae::InputManager::GetControllerRightTrigger(const uint controllerNr) const
{
	if (m_ControllerStates.size() <= controllerNr)
	{
		Devlog::PrintWarning("InputManager::GetControllerRightTrigger Controller Nr out of bound! returning nothing.");
		return{};
	}
	return m_ControllerStates[controllerNr].triggerRight;
}

