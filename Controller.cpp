#include "Controller.h"
#include"Engine/SceneManager.h"
#include"Engine/Input.h"
#include"Stage.h"
#include"Engine/Camera.h"
Controller::Controller(GameObject* parent)
	:GameObject(parent, "Controller")
{
}

void Controller::Initialize()
{

}

void Controller::Update()
{
	Camera::SetPosition(CamPos);
	Camera::SetTarget(CamTarget);

	if (Input::IsKey(DIK_W))
	{
		CamPos.z += 0.1;
		CamTarget.z += 0.1;
	}
	if (Input::IsKey(DIK_S))
	{
		CamPos.z -= 0.1;
		CamTarget.z -= 0.1;
	}
	if (Input::IsKey(DIK_A))
	{
		CamPos.x -= 0.1;
		CamTarget.x -= 0.1;
	}
	if (Input::IsKey(DIK_D))
	{
		CamPos.x += 0.1;
		CamTarget.x += 0.1;
	}

	if (Input::IsKey(DIK_UP))
	{
		CamPos.x += 0.1;
	}
	if (Input::IsKey(DIK_DOWN))
	{
		CamPos.x -= 0.1;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		CamPos.x -= 0.1;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		CamPos.x += 0.1;
	}

}

void Controller::Draw()
{
}

void Controller::Release()
{
}