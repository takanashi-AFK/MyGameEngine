#include "GameObject.h"

GameObject::GameObject() :isDead_(false)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
{
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->DrawSub();
	}
}

void GameObject::InitializeSub()
{
	Initialize();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->InitializeSub();
	}
}

void GameObject::UpdateSub()
{
	Update();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->UpdateSub();
	}
	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->isDead_) {
			(*itr)->ReleaseSub();
			delete *itr;
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void GameObject::ReleaseSub()
{
	Release();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->ReleaseSub();
	}
}

void GameObject::KillMe()
{
	isDead_ = true;
}
