#pragma once
#include "Engine/GameObject.h"
class Controller : public GameObject
{
private:
	XMFLOAT3 CamPos = { 0,5,-5 };
	XMFLOAT3 CamTarget = { 0,0,0 };
public:
	//�R���X�g���N�^
	//�����Fparent 
	Controller(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};