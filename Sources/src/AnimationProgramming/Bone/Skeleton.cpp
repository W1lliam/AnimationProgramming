#include "AnimationProgramming/Bone/Skeleton.h"
#include "AnimationProgramming/Bone/Bone.h"
#include <Engine/Engine.h>

Skeleton::Skeleton()
{

}

Skeleton::~Skeleton()
{

}

void Skeleton::Init()
{
	m_numBones		= GetSkeletonBoneCount();

	if (m_numBones > 0)
	{
		Bones.resize(m_numBones);
		CreateSkeleton();
	}

}

void Skeleton::LoadAnim(const char* animName)
{
	animFrames		= GetAnimKeyCount(animName);
	currentAnimName = animName;
}

void Skeleton::UpdateAnim(const char* animName, int frame, int nextFrame, float keyframeProgress)
{
	std::vector<Matrix4F> vmats;

	for (int i = 0; i < 64/*m_numBones*/; ++i)
	{
		Vector3F tempos;
		Vector4F temprot;
		Matrix4F tempmat	= Matrix4F::Identity;

		GetAnimLocalBoneTransform(animName, i, frame, tempos.x, tempos.y, tempos.z, temprot.w, temprot.x, temprot.y, temprot.z);

		Quaternion tempQuat(temprot.x, temprot.y, temprot.z, temprot.w);

		if (keyframeProgress > 0)
		{
			Vector3F NextTempos;
			Vector4F NextTemprot;

			GetAnimLocalBoneTransform(animName, i, nextFrame, NextTempos.x, NextTempos.y, NextTempos.z, NextTemprot.w, NextTemprot.x, NextTemprot.y, NextTemprot.z);

			Quaternion NextTempQuat(NextTemprot.x, NextTemprot.y, NextTemprot.z, NextTemprot.w);

			tempos		= Vector3F::Lerp(tempos, NextTempos, keyframeProgress);
			tempQuat	= Quaternion::Slerp(tempQuat, NextTempQuat, keyframeProgress);
		}

		Bones[i]->SetPosition(tempos);
		Bones[i]->SetRotation(tempQuat);
		Bones[i]->GenerateMatrix();

		tempmat				= Bones[i]->GetTransform();
		Matrix4F invBind	= Bones[i]->GetBindTransform().Inverse();
		tempmat				= tempmat * invBind;

		vmats.emplace_back(tempmat);

		const float mats[16] = {tempmat.ToArray()[0],	tempmat.ToArray()[1],	tempmat.ToArray()[2],	tempmat.ToArray()[3],
								tempmat.ToArray()[4],	tempmat.ToArray()[5],	tempmat.ToArray()[6],	tempmat.ToArray()[7],
								tempmat.ToArray()[8],	tempmat.ToArray()[9],	tempmat.ToArray()[10],	tempmat.ToArray()[11],
								tempmat.ToArray()[12],  tempmat.ToArray()[13],  tempmat.ToArray()[14],	tempmat.ToArray()[15] };
	}

	float GPUinfo[1024];
	int arrayindex = 0;
	for (int i = 0; i < vmats.size(); ++i)
	{
		for (int j = 0; j < 16; ++j, ++arrayindex)
		{
			GPUinfo[arrayindex] = vmats[i].elements[j];
		}
	}
	SetSkinningPose(GPUinfo, vmats.size());
	vmats.clear();
}

void Skeleton::Draw()
{
	if (Bones.size() > 0)
	{
		for (int i = 0; i < m_numBones; ++i)
		{
			Bones[i]->Draw();
		}
	}
}

void Skeleton::CreateSkeleton()
{ 
	for (int i = 0; i < m_numBones; ++i)
	{
		CreateBone(i);
	}
}

void Skeleton::CreateBone(const int index)
{
	float posX, posY, posZ, quatW, quatX, quatY, quatZ;
	GetSkeletonBoneLocalBindTransform(index, posX, posY, posZ, quatW, quatX, quatY, quatZ);

	std::string		name	= GetSkeletonBoneName(index);
	Vector3F		pos		= Vector3F(posX, posY, posZ);
	Quaternion		rot		= Quaternion(quatX, quatY, quatZ, quatW);

	if (GetSkeletonBoneParentIndex(index) != -1)
	{
		Bones[index]		= std::make_shared<Bone>(index, name, pos, rot);
		
		if (Bones[GetSkeletonBoneParentIndex(index)])
		{
			Bones[index]->SetParent(*Bones[GetSkeletonBoneParentIndex(index)]);
			//std::cout << name << "::" << Bones[GetSkeletonBoneParentIndex(index)]->GetName() << std::endl;
		}
		else
		{
			CreateBone(GetSkeletonBoneParentIndex(index));
			//std::cout << name << "::NoParent" << std::endl;
		}
	}
	else
		Bones[index]		= std::make_shared<Bone>(index, name, pos, rot);
}