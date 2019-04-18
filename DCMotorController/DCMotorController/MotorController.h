#pragma once
#include"StateMachine.h"
#include<iostream>

namespace motor_controller {

	namespace state {
		enum States {
			IDLE,
			START,
			CHANGE_SPEED,
			STOP,
			MAX_STATE
		};
	}

	class MotorController : public state_machine::StateMachine {
	public:
		MotorController();

		void SpeedUp(int howMuch);
		void SpeedDown(int howMuch);
		void Stop();

	private:

	private:
		int m_currentSpeed;
		// ON SPEED_UP/SPEED_DOWN EVENTS WE DEFINE OUR TRANSITIONS
		const static int ON_CHANGE_SPEED_TRANSITIONS[];
		const static int ON_STOP_TRANSITIONS[];

		state_machine::state_action::IStateAction* MappedStatesToAction[4];
		virtual state_machine::state_action::IStateAction* GetFunctionToInvocke(const int& state);

		//we will create functions and some handlers for our functions for each state
		void idle(int);
		state_machine::state_action::StateAction<MotorController, &idle> _idle;

		void start(int);
		state_machine::state_action::StateAction<MotorController, &start> _start;

		void changeSpeed(int);
		state_machine::state_action::StateAction<MotorController, &changeSpeed> _changeSpeed;

		void stop(int);
		state_machine::state_action::StateAction<MotorController, &stop> _stop;
	};
}