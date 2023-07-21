#include "PlayScene.h"
#include"Engine/Fbx.h"
#include"Player.h"
#include"TestObj.h"
#include"Enemy.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),pFbx(nullptr)
{
}

//初期化
void PlayScene::Initialize()
{
	//Player* pPlayer = new Player(this);//Playerの親はthis(PlayScene)
	//pPlayer->Initialize();
	//pPlayer -> Initialize();
	//childList_.push_back(pPlayer);//PlaySceneの子としてPlayerを登録
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
	
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}