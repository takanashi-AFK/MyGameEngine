#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
#include"Engine/SphereCollider.h"
#include"Engine/Model.h"
class Enemy :public GameObject
{
private:
	int hModel_;
public:
	Enemy(GameObject* parent);
	~Enemy();

	void Initialize()override;
	void Update()	 override;
	void Draw()		 override;
	void Release()	 override;
	void OnCollision(GameObject* _pTarget) override;
};


