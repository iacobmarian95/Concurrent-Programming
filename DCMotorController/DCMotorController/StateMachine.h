#pragma once

#include<mutex>

namespace state_machine {
	class StateMachine;
}

namespace state_machine {
	namespace state {
		enum States{
			IMPOSIBLE = 0xFFFF
		};
	}

	namespace state_action {
		class IStateAction {
		public:
			virtual void Caller(state_machine::StateMachine* sm, int data) = 0;
		};
		
		template<class SM, void (SM::*Func)(int)>
		class StateAction {
		public:
			virtual void Caller(state_machine::StateMachine* sm, int data) {
				SM *derived = static_cast<SM*> (sm);
				(derived->*Func)(data);
			}
		};
	}

	class StateMachine {
	public:
		StateMachine();
	protected:
		int GetCurrentState();
		void SetCurrentState(int state);
		void EventHandler(int state, int data);
	private:
		std::mutex m_mutex;

		int m_currentState;
		virtual state_action::IStateAction* GetFunctionToInvocke(const int&) = 0;
	};
}