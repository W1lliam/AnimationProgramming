#include <iostream>

#include <GyvrIni/GyvrIni.h>
#include "AnimationProgramming/Simulations/CSimulation.h"
#include <AltMath.h>
#include <chrono>
#include <thread>

using namespace AltMath;

int main()
{
	GyvrIni::Core::IniFile windowINI("config/window.ini");

	AnimationProgramming::Simulations::CSimulation simulation;

	using namespace std::this_thread;
	using namespace std::chrono_literals;
	using std::chrono::system_clock;

	sleep_for(10ns);
	sleep_until(system_clock::now() + 0.5s);

	Run(&simulation, windowINI.Get<unsigned int>("width"), windowINI.Get<unsigned int>("height"));

	return EXIT_SUCCESS;
}