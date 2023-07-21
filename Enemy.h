#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
class Enemy :public GameObject
{
private:
	Fbx *pFbx;
public:
	Enemy(GameObject* parent);
	~Enemy();

	void Initialize()override;
	void Update()	 override;
	void Draw()		 override;
	void Release()	 override;
};


