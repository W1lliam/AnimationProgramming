#pragma once

class Skeleton;

struct Animation
{
	const char* m_animationName;

	float m_animationSpeed;
	float m_keyframeDuration;
	int m_keyFrameCount;
};

class Animator
{
public:
	Animator(Skeleton& skeleton, const char* baseAnimName, float animationSpeed = 30.0f);

	~Animator();

	void LoadAnimation(const char* animName, float animationSpeed = 30.0f);

	void UpdateAnim(float p_time);

	void SetPlaybackSpeed(float speed);

private:

	Skeleton* m_skeleton;

	Animation m_animation;

	const char* m_animationName;

	float m_keyframeTime;

	int m_currentKeyFrame = 0;


};
