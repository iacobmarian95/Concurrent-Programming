#include"MotorController.h"
#include<thread>
#include<vector>

enum Operation {
	SpeedUp,
	SpeedDown, 
	Stop
};

void speedUp(int value, motor_controller::MotorController& dcMotor) {
	//std::this_thread::sleep_for(std::chrono::seconds(10));
	dcMotor.SpeedUp(value);
}

void speedDown(int value, motor_controller::MotorController& dcMotor) {
	//std::this_thread::sleep_for(std::chrono::seconds(5));
	dcMotor.SpeedDown(value);
}

void stop(motor_controller::MotorController& dcMotor) {
	//std::this_thread::sleep_for(std::chrono::seconds(15));
	dcMotor.Stop();
}

void SpeedManager(Operation operation, int value = 0) {
	static motor_controller::MotorController dcMotor;

	switch (operation)
	{
	case SpeedUp: {
		speedUp(value, dcMotor);

		break;
	}
	case SpeedDown: {
		speedDown(value, dcMotor);

		break;
	}
	case Stop: {
		stop(dcMotor);

		break;
	}
	default:
		break;
	}
}

int main() {
	std::vector<std::thread> threads;

	threads.push_back(std::thread(&SpeedManager, SpeedUp, 10));
	threads.push_back(std::thread(&SpeedManager, SpeedUp, 20));
	threads.push_back(std::thread(&SpeedManager, SpeedUp, 30));
	threads.push_back(std::thread(&SpeedManager, SpeedUp, 40));

	threads.push_back(std::thread(&SpeedManager, SpeedDown, 10));
	threads.push_back(std::thread(&SpeedManager, SpeedDown, 10));
	threads.push_back(std::thread(&SpeedManager, SpeedDown, 10));

	for (auto& it : threads)
		it.join();


	return 0;
}