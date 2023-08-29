#include "Controller.h"
#include"Engine/SceneManager.h"
#include"Engine/Input.h"
#include"Stage.h"
#include"Engine/Camera.h"
#include <directxmath.h>
Controller::Controller(GameObject* parent)
	:GameObject(parent, "Controller")
{
}

void Controller::Initialize()
{

    transform_.position_ = XMFLOAT3{ 7,0,7 };
}

void Controller::Update()
{
    //����]
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 1.0f;
    }

    //�E��]
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += 1.0f;
    }


    //transform_.rotate_.y�̒l�ɍ��킹�Ăx����]������s��
    XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    //���݈ʒu���x�N�g���ɂ��Ă���
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //�O��ړ��x�N�g��
    XMFLOAT3 frontMove = { 0, 0, 0.1f };                //��������XMFLOAT3�\���̂�p�ӂ�
    XMVECTOR vMove = XMLoadFloat3(&frontMove);               //������x�N�g���ɂ���
    vMove = XMVector3TransformCoord(vMove, mRotateY);    //��Ԃ̌����ɍ��킹�ĉ�]
    if (Input::IsKey(DIK_UP)&& transform_.rotate_.x <= 43)
    {
        transform_.rotate_.x += 1;
    }
    if (Input::IsKey(DIK_DOWN)&& transform_.rotate_.x >= -45)
    {     
        transform_.rotate_.x -= 1;
    }

    if (Input::IsKey(DIK_W))
    {
        vPos += vMove;
    }
    if (Input::IsKey(DIK_S))
    {
        vPos -= vMove;
    }

    //���E�ړ��x�N�g��
    XMFLOAT3 rightMove = { 0.1f, 0, 0 };                //�E������XMFLOAT3�\���̂�p�ӂ�
    vMove = XMLoadFloat3(&rightMove);               //������x�N�g���ɂ���
    vMove = XMVector3TransformCoord(vMove, mRotateY);    //��Ԃ̌����ɍ��킹�ĉ�]


    if (Input::IsKey(DIK_D))
    {
        vPos += vMove;
    }
    if (Input::IsKey(DIK_A))
    {
        vPos -= vMove;
    }

        XMStoreFloat3(&transform_.position_, vPos);

    //�J����
    XMVECTOR vCam = XMVectorSet(0, 13,-13, 0);
    vCam = XMVector3TransformCoord(vCam, mRotateX * mRotateY);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    Camera::SetPosition(XMLoadFloat3(&camPos));
    Camera::SetTarget(XMLoadFloat3(&transform_.position_));      //�J�����̏œ_�̓v���C���[�̈ʒu

}

void Controller::Draw()
{
}

void Controller::Release()
{
}