#include "AnimationProgramming/Animator/Animator.h"
#include "AnimationProgramming/Bone/Skeleton.h"
#include <Engine/Engine.h>

Animator::Animator(Skeleton& skeleton, const char* baseAnimName, float animationSpeed) : 
	m_skeleton(&skeleton),
	m_animation({ baseAnimName , animationSpeed , 1.0f / animationSpeed, (int)GetAnimKeyCount(baseAnimName)})
//	m_animationSpeed(animationSpeed), 
//	m_animationName(baseAnimName),
//	m_keyFrameCount(GetAnimKeyCount(baseAnimName)),
//	m_keyframeDuration(1.0f/animationSpeed)
{

}

Animator::~Animator()
{

}

void Animator::SetPlaybackSpeed(float speed)
{
	m_animation.m_animationSpeed = speed;

	m_animation.m_keyframeDuration = 1.0f / m_animation.m_animationSpeed;
}

void Animator::LoadAnimation(const char* animName, float animationSpeed)
{
	m_currentKeyFrame = 0;
	m_animation.m_keyFrameCount = GetAnimKeyCount(animName);
	m_animation.m_animationName = animName;
	m_animation.m_animationSpeed = animationSpeed;

	m_animation.m_keyframeDuration = 1.0f / m_animation.m_animationSpeed;
}



void Animator::UpdateAnim(float p_deltaTime)
{
	m_keyframeTime += p_deltaTime;
	
	if (m_keyframeTime > m_animation.m_keyframeDuration)
	{
		m_keyframeTime -= m_animation.m_keyframeDuration;
		m_currentKeyFrame++;
		m_currentKeyFrame = m_currentKeyFrame == m_animation.m_keyFrameCount ? 1 : m_currentKeyFrame;
	}
	int nextFrame = m_currentKeyFrame == m_animation.m_keyFrameCount - 1 ? 1 : m_currentKeyFrame + 1;
	m_skeleton->UpdateAnim(m_animation.m_animationName, m_currentKeyFrame, nextFrame, m_keyframeTime / m_animation.m_keyframeDuration);

}