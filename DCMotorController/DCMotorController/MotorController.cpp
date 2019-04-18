#include"MotorController.h"

/*						ON_CHANGE_SPEED EVENT
	*	1. If we are in idle state => can go in Start state
	*	2. If we are in start state => we can go in Change_Speed state
	*	3. If we are in Change_Speed state => we can go in Change_Speed state (will not change current state)
	*	4. In case if we are in Stop state => is imposibile to go in Change_Speed state
*/
const int motor_controller::MotorController::ON_CHANGE_SPEED_TRANSITIONS[] = {
	state::START,
	state::CHANGE_SPEED,
	state::CHANGE_SPEED,
	state_machine::state::IMPOSIBLE
};

/*							ON_STOP_EVENT
	*	1. If we are in idle state => is impsible to go in Stop state
	*	2. If we are in start state => we can go in Stop state
	*	3. If we are in Change_Speed => we can in in Stop state
	*	4. If we already are in Stop state => we cannot go in Stop action
*/
const int motor_controller::MotorController::ON_STOP_TRANSITIONS[] = {
	state_machine::state::IMPOSIBLE,
	state::STOP,
	state::STOP,
	state_machine::state::IMPOSIBLE
};

motor_controller::MotorController::MotorController(): m_currentSpeed(0) {
	MappedStatesToAction[0] = (state_machine::state_action::IStateAction*) (&_idle);
	MappedStatesToAction[1] = (state_machine::state_action::IStateAction*) (&_start);
	MappedStatesToAction[2] = (state_machine::state_action::IStateAction*) (&_changeSpeed);
	MappedStatesToAction[3] = (state_machine::state_action::IStateAction*) (&_stop);
}
/* ************** we provide three functions for our consumer **************/
void motor_controller::MotorController::SpeedUp(int howMuch) {
	EventHandler(ON_CHANGE_SPEED_TRANSITIONS[GetCurrentState()], howMuch);
}

void motor_controller::MotorController::SpeedDown(int howMuch) {
	howMuch = -howMuch;	//we will substract from current spped 
	EventHandler(ON_CHANGE_SPEED_TRANSITIONS[GetCurrentState()], howMuch);
}

void motor_controller::MotorController::Stop() {
	EventHandler(ON_STOP_TRANSITIONS[GetCurrentState()], 0);
	//Once I'm stopped - I will go in idle state
	SetCurrentState(motor_controller::state::IDLE);
}

/******************** which function must be called *************************/
state_machine::state_action::IStateAction* motor_controller::MotorController::GetFunctionToInvocke(const int& state) {
	return MappedStatesToAction[state];
}

/* ********* through those functions we will handle our transitions *********/
void motor_controller::MotorController::idle(int alhpa = 0) {
	std::cout << "Idle state does nothing" << std::endl;
}

void motor_controller::MotorController::start(int alpha) {
	std::cout << "I just started with an initial speed: " << alpha << std::endl;
	m_currentSpeed = alpha;
}

void motor_controller::MotorController::changeSpeed(int alpha) {
	std::cout << "The speed will be changed with " << alpha << " units" << std::endl;
	m_currentSpeed += alpha;
}

void motor_controller::MotorController::stop(int alpha = 0) {
	std::cout << "I'm stopped now and I will go in idle state" << std::endl;
	m_currentSpeed = 0;
}