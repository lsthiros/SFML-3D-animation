#include "Bone.h"


Bone::Bone(aiMatrix4x4 transform, aiMatrix4x4 global, Bone* parent) :
	m_transform(transform),
	m_global(global),
	m_parent(parent)
{
	m_numChildren=0;
	m_offset = 
}

void Bone::addChild(Bone* child) {
	m_children.push_back(child);
	m_numChildren++;
}

Bone::~Bone(void)
{
}
