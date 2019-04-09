#pragma once
#include <vector>
#include <iostream>

class Skeleton
{
public:

	int animFrames;

	Skeleton();
	~Skeleton();
	void Init();
	void LoadAnim(const char* animName);
	void Draw();
	void UpdateAnim(const char* animName, int frame, int nextFrame, float keyframeProgress);
	void Blend(float BlendWeight);

	std::vector<std::shared_ptr<class Bone>> Bones;

private:

	int m_numBones;
	const char* currentAnimName;

	void CreateSkeleton();
	void CreateBone(const int index);
};

