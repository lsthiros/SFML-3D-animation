#pragma once

#include "Bone.h"

struct MatrixKey {
	aiMatrix4x4 matrix;
	float timeStamp;
};

struct QuaternionKey {
	aiQuaternion quaternion;
	float timeStamp;
};

class AnimationChannel
{
private:
	int m_numRotationKeys, m_numScalingKeys, m_numTransformKeys;
	QuaternionKey* m_rotationKeys;
	MatrixKey* m_transformationKey;
	MatrixKey* m_scalingKey;
	//interpolation functions
	aiMatrix4x4* interpolateAnimation(float time);
public:
	AnimationChannel(aiNodeAnim nodeAnimation, int numRotationKeys, int numScalingKeys, int numTransformationKeys);
	~AnimationChannel(void);
};

