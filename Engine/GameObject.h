#pragma once

#include <list>
#include <string>
#include "Transform.h"

class GameObject
{
private:


protected:
	std::list<GameObject*>	childList_;
	Transform				transform_;
	GameObject*				pParent_;
	std::string				objectName_;
	bool					isDead_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() = 0;
	virtual void Update()	  = 0;
	virtual void Draw()		  = 0;
	virtual void Release()	  = 0;

	template <class T>
	GameObject* Instantiate(GameObject* parent)
	{
		T* p;

		p = new T(parent);
		p->Initialize();
		childList_.push_back(p);
		return p;
	}

	void InitializeSub();
	void UpdateSub();
	void DrawSub();
	void ReleaseSub();
	void KillMe();
};