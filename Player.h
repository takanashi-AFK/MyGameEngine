#pragma once
#include "Engine/GameObject.h"

class Fbx;

//�v���C�V�[�����Ǘ�����N���X
class Player : public GameObject
{

private:
	Fbx* pFbx;
	int hModel_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
