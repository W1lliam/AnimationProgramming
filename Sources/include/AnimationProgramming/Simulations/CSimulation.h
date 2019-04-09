

#pragma once
#ifndef _CSIMULATION_H
#define _CSIMULATION_H

#include <Engine/Engine.h>
#include <Engine/Simulation.h>
#include <map>
#include <AnimationProgramming/Bone/Skeleton.h>
#include "AnimationProgramming/Animator/Animator.h"

namespace AnimationProgramming::Simulations
{
	/**
	* The CSimulation class is the simulation that is used in this project
	*/
	class CSimulation final : public ISimulation
	{
		std::unique_ptr<Skeleton> SkeletalMesh;
		std::unique_ptr<Animator> UAnimator;

		
		std::map<char, bool> press;
		bool slowmo = false;
		bool running = false;
		bool gizmo = true;
		bool skeleton = false;

		std::string message = "";

		/**
		* Init the Simulation
		*/
		virtual void Init() override;

		/**
		* Update the simulation
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

		/**
		* Simply render a gizmo on the screen
		*/
		void DrawGizmo();

		float currentKeyframe = 0;

		void ProcessInput();
		void ChangeAnim();
		void Slowmo();
		void Gizmos();
		void PrintConsole();
	};
}

#endif // _CSIMULATION_H

