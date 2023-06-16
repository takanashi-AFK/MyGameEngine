#include "Dice.h"
#include"Camera.h"

Dice::Dice() 
{
}

Dice::~Dice()
{
	Release();
}

HRESULT Dice::Initialize()
{
	HRESULT hr;
    //���_���
    VERTEX vertices[] =
    {
        //�ʂP
        {XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},    // �O�ʁi����j0
        {XMVectorSet(1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},    // �O�ʁi�E��j1
        {XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},    // �O�ʁi�E���j2
        {XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},    // �O�ʁi�����j3

        //�ʂS
        {XMVectorSet(-1.0f, 1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(-1.0f,0.0f,0.0f,0.0f)},    // ���ʍ��i����j4
        {XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f,0.0f,0.0f,0.0f) },    // ���ʍ��i�E��j5
        {XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f,0.0f,0.0f,0.0f) },    // ���ʍ��i�E���j6
        {XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(-1.0f,0.0f,0.0f,0.0f)},    // ���ʍ��i�����j7

        //�ʂR
        {XMVectorSet(1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(1.0f,0.0f,0.0f,0.0f)},    // ���ʉE�i����j8
        {XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(1.0f,0.0f,0.0f,0.0f)},    // ���ʉE�i�E��j9
        {XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(1.0f,0.0f,0.0f,0.0f)},    // ���ʉE�i�E���j10
        {XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(1.0f,0.0f,0.0f,0.0f)},    // ���ʉE�i�����j11

        //�ʂU
        {XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,1.0f,0.0f)},    // �w�ʁi����j12
        {XMVectorSet(-1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,1.0f,0.0f)},    // �w�ʁi�E��j13
        {XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,1.0f,0.0f)},    // �w�ʁi�E���j14
        {XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,1.0f,0.0f)},    // �w�ʁi�����j15

        //�ʂT
        {XMVectorSet(-1.0f, 1.0f, 1.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,1.0f,0.0f,0.0f)},    // ��ʁi����j16
        {XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,1.0f,0.0f,0.0f)},    // ��ʁi�E��j17
        {XMVectorSet(1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,1.0f,0.0f,0.0f)},    // ��ʁi�E���j18
        {XMVectorSet(-1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,1.0f,0.0f,0.0f)},    // ��ʁi�����j19

        //�ʂQ
        {XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},    // ��ʁi����j20
        {XMVectorSet(1.0f,  -1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},    // ��ʁi�E��j21
        {XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},    // ��ʁi�E���j22
        {XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},    // ��ʁi�����j23
    };



    //�C���f�b�N�X���
    int index[] = {
         0, 2, 3,  0, 1, 2,        //�ʂP
         4, 6, 7,  4, 5, 6,        //�ʂS
         8,10,11,  8, 9,10,        //�ʂR
        12,14,15, 12,13,14,        //�ʂU
        16,18,19, 16,17,18,        //�ʂT
        20,22,23, 20,21,22,        //�ʂQ
    };

	hr = BufferMaker(vertices,index,24,36);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}
	return S_OK;
}
void Dice::Draw(XMMATRIX& worldMatrix)
{
	BufferSetter(worldMatrix);
}

void Dice::Release()
{
	pTexture_->Release();
	SAFE_RELEASE(pTexture_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}
