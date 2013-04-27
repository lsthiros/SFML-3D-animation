#include "AnimationChannel.h"

AnimationChannel::AnimationChannel(aiNodeAnim nodeAnimation, int numRotationKeys, int numScalingKeys, int numTransformationKeys) :
	m_numRotationKeys(numRotationKeys),
	m_numScalingKeys(numScalingKeys),
	m_numTransformKeys(numTransformationKeys)
{
};

AnimationChannel::~AnimationChannel(void)
{
};

