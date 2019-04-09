#pragma once
#include <AltMath.h>

using namespace AltMath;

class Bone
{
public:
	Bone();
	~Bone();
	Bone(int p_index, const std::string p_name, Matrix4F p_transform);
	Bone(int p_index, const std::string p_name);
	Bone(int p_index, const std::string p_name, Vector3F p_pos, Quaternion p_rot);
	Bone(int p_index, Vector3F p_pos, Quaternion p_rot);

	//Setters
	void SetPosition	(Vector3F p_pos);
	void SetRotation(Quaternion p_rot);
	void SetDirty	(bool p_dirty);
	void SetName	(std::string p_name);
	void SetParent	(Bone& parent);

	//Helpers
	void DrawSphere	();
	void DrawCross	(Vector3F offset);
	void DrawBone	(Vector3F offset);
	void Draw		();
	void GenerateMatrix();
	void GenerateAnimMatrix();

	inline Bone&		GetParent();

	//Getters
	inline std::string	GetName()			{ return _name;				}
	inline int			GetIndex()			{ return _index;			}
	inline bool			GetIsDirty()		{ return _isDrity;			}
	inline Matrix4f		GetTransform()		{ return _animTransform;	}
	inline Matrix4f		GetBindTransform()  { return _worldTransform;	}
	inline Vector3F     GetPosition()		{ return Vector3F(_animTransform(0, 3), _animTransform(1, 3), _animTransform(2, 3));}

private:

	std::string			_name;
	int					_index;
	bool				_isDrity;
	Matrix4F			_worldTransform;
	Matrix4F			_localTransform;
	Matrix4F			_animTransform;
	Matrix4F			_animRelativeTransform;
	Bone*				_parent;
	

};
