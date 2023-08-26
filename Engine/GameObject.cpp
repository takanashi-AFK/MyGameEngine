#include "GameObject.h"
#include"SphereCollider.h"

GameObject::GameObject() :isDead_(false),pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name):pParent_(parent), objectName_(name), isDead_(false),pCollider_(nullptr)
{
	if (parent != nullptr)
		this->transform_.pParent_ = &(parent->transform_);
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

	RoundRobin(GetRootJob());
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
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->ReleaseSub();
		delete *itr;
	}
	Release();
}

void GameObject::KillMe()
{
	isDead_ = true;
}

GameObject* GameObject::FindChildObject(std::string _objName)
{
	if (_objName == this->objectName_) {
		return this;
	}
	else {
		for (auto itr:childList_) {
			GameObject* obj  = itr->FindChildObject(_objName);
			if (obj != nullptr)
			{
				return obj;
			}
		}
	}
}

GameObject* GameObject::GetRootJob()
{
	if(pParent_ ==  nullptr)
	return this;

	return pParent_->GetRootJob();
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;

}

float GetVectorLength(const XMVECTOR& vector)
{
	DirectX::XMVECTOR squaredLength = DirectX::XMVector3LengthSq(vector);

	float length;
	DirectX::XMStoreFloat(&length, DirectX::XMVectorSqrt(squaredLength));

	return length;
}

void GameObject::Collision(GameObject* _pTarget)
{
	if (_pTarget == this || _pTarget->pCollider_ == nullptr)
		return;//自分自身、またはターゲットにコライダーがアタッチされていない
	//XMVECTOR v{transform_.position_.x - pTarget->transform_.position_.x,
	//		   transform_.position_.y - pTarget->transform_.position_.y, 
	//		   transform_.position_.z - pTarget->transform_.position_.z, 
	//			0};
	//XMVECTOR dist = XMVector3Dot(v, v);
	float dist = (transform_.position_.x - _pTarget->transform_.position_.x) * (transform_.position_.x - _pTarget->transform_.position_.x)
		+ (transform_.position_.y - _pTarget->transform_.position_.y) * (transform_.position_.y - _pTarget->transform_.position_.y)
		+ (transform_.position_.z - _pTarget->transform_.position_.z) * (transform_.position_.z - _pTarget->transform_.position_.z);
	float rDist = (this->pCollider_->GetRadius() + _pTarget->pCollider_->GetRadius()) * (this->pCollider_->GetRadius() + _pTarget->pCollider_->GetRadius());

	//自分とターゲットの距離　<= R1+R2なら
	//もし、自分のコライダーとターゲットがぶつかっていたら
	//onCollision(pTarget)を呼び出す！
	if (dist <= rDist)
	{
		OnCollision(_pTarget);
		double p = 0;
	}
}

void GameObject::RoundRobin(GameObject* _pTarget)
{
	if (pCollider_ == nullptr)
		return;
	if (_pTarget->pCollider_ != nullptr) //自分とターゲット
		Collision(_pTarget);
	//自分の子供全部とターゲット
	for (auto itr : _pTarget->childList_)
		RoundRobin(itr);
}

void GameObject::SetPosition(XMFLOAT3 _pos)
{
	transform_.position_ = _pos;

}

GameObject* GameObject::FindObject(std::string _objName)
{

	return GetRootJob()->FindChildObject(_objName);
}

void GameObject::SetScale(XMFLOAT3 _scl)
{
	transform_.scale_ = _scl;
}

