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
    //頂点情報
    VERTEX vertices[] =
    {
        //面１
        {XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},    // 前面（左上）0
        {XMVectorSet(1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},    // 前面（右上）1
        {XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},    // 前面（右下）2
        {XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},    // 前面（左下）3

        //面４
        {XMVectorSet(-1.0f, 1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(-1.0f,0.0f,0.0f,0.0f)},    // 測面左（左上）4
        {XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f,0.0f,0.0f,0.0f) },    // 測面左（右上）5
        {XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f,0.0f,0.0f,0.0f) },    // 測面左（右下）6
        {XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(-1.0f,0.0f,0.0f,0.0f)},    // 測面左（左下）7

        //面３
        {XMVectorSet(1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(1.0f,0.0f,0.0f,0.0f)},    // 測面右（左上）8
        {XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(1.0f,0.0f,0.0f,0.0f)},    // 測面右（右上）9
        {XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(1.0f,0.0f,0.0f,0.0f)},    // 測面右（右下）10
        {XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(1.0f,0.0f,0.0f,0.0f)},    // 測面右（左下）11

        //面６
        {XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,1.0f,0.0f)},    // 背面（左上）12
        {XMVectorSet(-1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,1.0f,0.0f)},    // 背面（右上）13
        {XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,1.0f,0.0f)},    // 背面（右下）14
        {XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,1.0f,0.0f)},    // 背面（左下）15

        //面５
        {XMVectorSet(-1.0f, 1.0f, 1.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,1.0f,0.0f,0.0f)},    // 上面（左上）16
        {XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,1.0f,0.0f,0.0f)},    // 上面（右上）17
        {XMVectorSet(1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,1.0f,0.0f,0.0f)},    // 上面（右下）18
        {XMVectorSet(-1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,1.0f,0.0f,0.0f)},    // 上面（左下）19

        //面２
        {XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},    // 上面（左上）20
        {XMVectorSet(1.0f,  -1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},    // 上面（右上）21
        {XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},    // 上面（右下）22
        {XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},    // 上面（左下）23
    };



    //インデックス情報
    int index[] = {
         0, 2, 3,  0, 1, 2,        //面１
         4, 6, 7,  4, 5, 6,        //面４
         8,10,11,  8, 9,10,        //面３
        12,14,15, 12,13,14,        //面６
        16,18,19, 16,17,18,        //面５
        20,22,23, 20,21,22,        //面２
    };

	hr = BufferMaker(vertices,index,24,36);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "バッファの作成に失敗しました", "エラー", MB_OK);
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
