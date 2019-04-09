#pragma once
#include <map>

struct Animation;

class Blendspace
{
public:
	Blendspace();
	~Blendspace();

	void SetBlendWeight(float* p_blendWeight);
	void SetAnimBlend(float p_weight, Animation& p_anim);

	std::tuple<Animation&, Animation&, float> AnimationRatio();

private:

	float* m_blendWeight;
	std::map<float, Animation&> m_blendtree;

};