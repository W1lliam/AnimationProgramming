#include "AnimationProgramming/Bone/Bone.h"
#include <Engine/Engine.h>

Bone::Bone()
{
	_name					= "";
	_index					= 0;
	_parent					= nullptr;
	_isDrity				= true;
	_localTransform			= Matrix4F::Identity;
	_worldTransform			= Matrix4F::Identity;
	_animTransform			= Matrix4F::Identity;
	_animRelativeTransform	= Matrix4F::Identity;
}
Bone::Bone(int p_index, const std::string p_name, Matrix4F p_transform) : Bone()
{

	_index			= p_index;
	_name			= p_name;
	_localTransform = p_transform;

}
Bone::Bone(int p_index, const std::string p_name) : Bone()
{
	_name		= p_name;
	_index		= p_index;
}

Bone::Bone(int p_index, const std::string p_name, Vector3F p_pos, Quaternion p_rot) : Bone()
{

	_name		= p_name;
	_index		= p_index;

	_localTransform.Translate(p_pos);
	_localTransform.Multiply(p_rot.ToMatrix4());
}

Bone::Bone(int p_index, Vector3F p_pos, Quaternion p_rot) : Bone()
{
	_index		= p_index;


	_localTransform.Translate(p_pos);
	_localTransform.Multiply(p_rot.ToMatrix4());
}

Bone::~Bone()
{

}

Bone& Bone::GetParent()
{
	if (!_parent)
	{
		throw std::invalid_argument("No parent found");
	}

	return *_parent;
}

void Bone::SetPosition(Vector3F p_pos)
{
	_animRelativeTransform	= Matrix4F::Identity;
	Vector3F TPosePos		= Vector3F(_localTransform(0, 3), _localTransform(1, 3), _localTransform(2, 3));
	Vector3F resultPos		= TPosePos + p_pos;

	_animRelativeTransform.Translate(resultPos);
}

void Bone::SetRotation(Quaternion p_rot)
{
		Matrix3F TPoseRotMat	= Matrix3F(_localTransform(0, 0), _localTransform(0, 1), _localTransform(0, 2),
										   _localTransform(1, 0), _localTransform(1, 1), _localTransform(1, 2),
										   _localTransform(2, 0), _localTransform(2, 1), _localTransform(2, 2));

		Quaternion TPoseRot		= Quaternion(TPoseRotMat);
		Quaternion resultRot	= TPoseRot * p_rot;

		_animRelativeTransform.Multiply(resultRot.ToMatrix4());
}

void Bone::SetDirty(bool p_dirty)
{
	_isDrity	= p_dirty;
}

void Bone::SetName(std::string p_name)
{
	_name		= p_name;
}

void Bone::SetParent(Bone& parent)
{
	_parent		= &parent;
	GenerateMatrix();
}

void Bone::GenerateMatrix()
{
	if (_parent)
	{
		_worldTransform = _parent->_worldTransform * _localTransform;
	}
	else
		_worldTransform = _localTransform;

	GenerateAnimMatrix();
}

void Bone::GenerateAnimMatrix()
{
	if (_parent)
	{
		_animRelativeTransform	= _parent->_animRelativeTransform * _animRelativeTransform;
	}

	_animTransform	= _animRelativeTransform;
}

void Bone::Draw()
{
	if (_parent && _name.find("ik") == std::string::npos) //don't want to show the ik bones
	{
		DrawCross(Vector3F(0.0f, -20.0f, 0.0f));
		DrawBone(Vector3F(0.0f, -20.0f, 0.0f));
	}
}

void Bone::DrawCross(Vector3F offset)
{
	DrawLine(GetPosition().x + offset.x, GetPosition().y - 2 + offset.y, GetPosition().z + offset.z,
			 GetPosition().x + offset.x, GetPosition().y + 2 + offset.y, GetPosition().z + offset.z,
					0.0f,			21.0f / 255.0f,			1.0f);
	DrawLine(GetPosition().x + offset.x, GetPosition().y + offset.y, GetPosition().z - 2 + offset.z,
			 GetPosition().x + offset.x, GetPosition().y + offset.y, GetPosition().z + 2 + offset.z,
					0.0f,			21.0f / 255.0f,			1.0f);
	DrawLine(GetPosition().x - 2 + offset.x, GetPosition().y + offset.y, GetPosition().z + offset.z,
			 GetPosition().x + 2 + offset.x, GetPosition().y + offset.y, GetPosition().z + offset.z,
					0.0f,			21.0f / 255.0f,			1.0f);
}

void Bone::DrawBone(Vector3F offset)
{
	DrawLine(GetPosition().x + offset.x,			GetPosition().y + offset.y,				GetPosition().z + offset.z,
			 _parent->GetPosition().x + offset.x,	_parent->GetPosition().y + offset.y,	_parent->GetPosition().z + offset.z,
			 38.0f / 255.0f,						46.0f / 255.0f,							127.0f / 255.0f);
}

void Bone::DrawSphere()
{
	for (int i = 0; i < 360; ++i)
	{
		DrawLine( std::cos(i * 180.0f) + GetPosition().x,		GetPosition().y, std::sin(i * 180.0f) + GetPosition().z,
				  std::cos((i + 0.1f) * 180.0f) + GetPosition().x, GetPosition().y, std::sin((i + 0.1f) * 180.0f) +GetPosition().z,
							0.0f,								21.0f/255.0f,				1.0f);
	}
}