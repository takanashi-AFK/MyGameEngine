#include "PlayScene.h"
#include"Engine/Fbx.h"
#include"Player.h"
#include"TestObj.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),pFbx(nullptr)
{
}

//������
void PlayScene::Initialize()
{
	//Player* pPlayer = new Player(this);//Player�̐e��this(PlayScene)
	//pPlayer->Initialize();
	//pPlayer -> Initialize();
	//childList_.push_back(pPlayer);//PlayScene�̎q�Ƃ���Player��o�^
	Instantiate<Player>(this);

	
}

//�X�V
void PlayScene::Update()
{
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}