#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
{
	childList_.clear();
	pParent_ = nullptr;

}

GameObject::~GameObject()
{
}
