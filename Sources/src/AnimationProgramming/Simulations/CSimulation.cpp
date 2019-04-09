#include "AnimationProgramming/Simulations/CSimulation.h"
#include <AltMath.h>
#include <stdio.h>
#include <Windows.h>
#include <WinUser.h>

void AnimationProgramming::Simulations::CSimulation::Init()
{
	press['R'] = false;
	press['Q'] = false;
	press['H'] = false;
	press['G'] = false;

	int spine01 = GetSkeletonBoneIndex("spine_01");
	int spineParent = GetSkeletonBoneParentIndex(spine01);
	const char* spineParentName = GetSkeletonBoneName(spineParent);

	float posX, posY, posZ, quatW, quatX, quatY, quatZ;
	size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
	GetAnimLocalBoneTransform("ThirdPersonWalk.anim", spineParent, keyCount / 2, posX, posY, posZ, quatW, quatX, quatY, quatZ);

	printf("Spine parent bone : %s\n", spineParentName);
	printf("Anim key count : %ld\n", keyCount);
	printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);

	printf("Creting Skeleton\n");
	SkeletalMesh = std::make_unique<Skeleton>();
	SkeletalMesh->Init();
	UAnimator = std::make_unique<Animator>(*SkeletalMesh, "ThirdPersonWalk.anim");
	//PrintConsole();
	ChangeAnim();
}

void AnimationProgramming::Simulations::CSimulation::Update(float p_deltaTime)
{
	ProcessInput();

	UAnimator->UpdateAnim(p_deltaTime);

	Gizmos();
}

void AnimationProgramming::Simulations::CSimulation::DrawGizmo()
{
	DrawLine(0.0f, 0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	DrawLine(0.0f, 0.0f, 0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	DrawLine(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 1.0f);
}

void AnimationProgramming::Simulations::CSimulation::ProcessInput()
{
	if ((GetKeyState('R') & (1<<30)) && !press['R'])
	{
		press['R'] = true;

		running = !running;

		ChangeAnim();
	}
	else if ((GetKeyState('R') & (1 << 30)) == 0 && press['R'])
	{
		press['R'] = false;
	}

	if ((GetKeyState('Q') & (1 << 30)) && !press['Q'])
	{
		press['Q'] = true;
		slowmo = !slowmo;

		Slowmo();

	}
	else if ((GetKeyState('Q') & (1 << 30)) == 0 && press['Q'])
	{
		press['Q'] = false;
	}


	if ((GetKeyState('G') & (1 << 30)) && !press['G'])
	{
		press['G'] = true;

		gizmo = !gizmo;


	}
	else if ((GetKeyState('G') & (1 << 30)) == 0 && press['G'])
	{
		press['G'] = false;
	}

	if ((GetKeyState('H') & (1 << 30)) && !press['H'])
	{
		press['H'] = true;

		skeleton = !skeleton;


	}
	else if ((GetKeyState('H') & (1 << 30)) == 0 && press['H'])
	{
		press['H'] = false;
	}
}

void AnimationProgramming::Simulations::CSimulation::ChangeAnim()
{
	PrintConsole();

	if (running)
	{
		message = "Current State: Running";
		UAnimator->LoadAnimation("ThirdPersonRun.anim");
	}
	else
	{
		message = "Current State: Walking";
		UAnimator->LoadAnimation("ThirdPersonWalk.anim");
	}

	Slowmo();
}

void AnimationProgramming::Simulations::CSimulation::Slowmo()
{
	PrintConsole();

	std::string speed = "";

	if (slowmo)
	{
		speed = " Playback Speed: 50%";
		UAnimator->SetPlaybackSpeed(5.0f);
	}
	else
	{
		speed = " Playback Speed: 100%";
		UAnimator->SetPlaybackSpeed(30.0f);
	}
	std::cout << message<< "," << speed << std::endl;
}

void AnimationProgramming::Simulations::CSimulation::Gizmos()
{
	if (gizmo)
		DrawGizmo();

	if(skeleton)
		SkeletalMesh->Draw();
}

void AnimationProgramming::Simulations::CSimulation::PrintConsole()
{
	system("cls");
	std::cout << "Shaders include specular reflection" << std::endl;
	std::cout << "Created by William Perez" << std::endl;
	std::cout << "______________________________" << std::endl;
	std::cout << "Inputs:\n" << std::endl;
	std::cout << "  R : Toggle Running animation" << std::endl;
	std::cout << "  Q : Toggle Slow motion" << std::endl;
	std::cout << "  G : Toggle Gizmo" << std::endl;
	std::cout << "  H : Toggle Bones" << std::endl;
	std::cout << "______________________________" << std::endl;
}