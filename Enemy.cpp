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
	hModel_=Model::Load("Assets/odden.fbx");
	transform_.position_.z = 20.0f;
	SphereCollider* collision = new SphereCollider(1.0f);
	AddCollider(collision);
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* _pTarget)
{
	KillMe();
}
