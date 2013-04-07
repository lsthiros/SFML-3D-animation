#include "Bone.h"


Bone::Bone(aiMatrix4x4 transform, aiMatrix4x4 global, aiMatrix4x4 offset, std::string name) :
	m_transform(transform),
	m_global(global),
	m_offset(offset)
{
}


Bone::~Bone(void)
{
}
