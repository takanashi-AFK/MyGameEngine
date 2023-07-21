#include "Enemy.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy")
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/odden.fbx");
	transform_.position_.z = 20.0f;

}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	pFbx->Draw(transform_);
}

void Enemy::Release()
{
}
