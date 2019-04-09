#include "AnimationProgramming/Animator/Blendspace.h"
#include "AnimationProgramming/Animator/Animator.h"

Blendspace::Blendspace()
{

}

Blendspace::~Blendspace()
{

}

void Blendspace::SetBlendWeight(float* p_blendWeight)
{
	m_blendWeight = p_blendWeight;
}

void Blendspace::SetAnimBlend(float p_weight, Animation& p_anim)
{
	m_blendtree.emplace(p_weight, p_anim);
}

std::tuple<Animation&, Animation&, float> Blendspace::AnimationRatio()
{
	auto it = m_blendtree.lower_bound(*m_blendWeight);

	if (it == m_blendtree.begin())
		return std::tuple<Animation&, Animation&, float>(it->second, std::next(it, 1)->second, 1.0f);

	if (it == m_blendtree.end())
		return std::tuple<Animation&, Animation&, float>(m_blendtree.rbegin()->second, std::next(m_blendtree.rbegin(), 1)->second, 1.0f);

	auto prev = std::prev(it, 1);
	float range = it->first - prev->first;
	float ratio = (*m_blendWeight - prev->first) / range;

	return std::tuple<Animation&, Animation&, float>(prev->second, it->second, ratio);
}