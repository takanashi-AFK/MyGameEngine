#include "Dice.h"
#include"Camera.h"
Dice::Dice() :
	pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pTexture_(nullptr)
{
}

Dice::~Dice()
{
	Release();
}

HRESULT Dice::Initialize()
{
	HRESULT hr;
	//頂点設定
	VERTEX vertices[] =
	{
		//面１
		{XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) },  // 前面（左上）0
		{XMVectorSet(1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) },  // 前面（右上）1
		{XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },  // 前面（右下）2
		{XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) },  // 前面（左下）3

		//面４
		{XMVectorSet(-1.0f, 1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) },   // 測面左（左上）4
		{XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },  // 測面左（右上）5
		{XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f) },  // 測面左（右下）6
		{XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) },  // 測面左（左下）7

		//面３
		{XMVectorSet(1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) },    // 測面右（左上）8
		{XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) },   // 測面右（右上）9
		{XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) },   // 測面右（右下）10
		{XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },   // 測面右（左下）11

		//面６
		{XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },    // 背面（左上）12
		{XMVectorSet(-1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },   // 背面（右上）13
		{XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f) },   // 背面（右下）14
		{XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) },   // 背面（左下）15

		//面５
		{XMVectorSet(-1.0f, 1.0f, 1.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) },    // 上面（左上）16
		{XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },   // 上面（右上）17
		{XMVectorSet(1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) },   // 上面（右下）18
		{XMVectorSet(-1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },   // 上面（左下）19

		//面２
		{XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) }, // 上面（左上）20
		{XMVectorSet(1.0f,  -1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) },  // 上面（右上）21
		{XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },    // 上面（右下）22
		{XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },  // 上面（左下）23
	};
	//インデックス情報の設定
	int index[] = {
		 0, 2, 3,  0, 1, 2,     //面１
		 4, 6, 7,  4, 5, 6,     //面４
		 8,10,11,  8, 9,10,     //面３
		12,14,15, 12,13,14,     //面６
		16,18,19, 16,17,18,     //面５
		20,22,23, 20,21,22,     //面２
	};

	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "頂点バッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}


	////インデックス情報
	//int index[] = { 0,1,2,//手前
	//				0,2,3,

	//				1,0,4,//上
	//				1,4,5,

	//				5,4,7,//奥
	//				5,6,7,

	//				3,6,7,//下
	//				3,6,2,

	//				6,1,2,//右
	//				6,1,5,

	//				4,3,0,//左
	//				4,3,7
	//				};

	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{

		MessageBox(nullptr, "インデックスバッファの作成に失敗しました", "エラー", MB_OK);

		return hr;

	}

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}
	pTexture_ = new Texture;
	pTexture_->Load("Assets/Dice.png");
	return S_OK;
}

void Dice::Draw(XMMATRIX& worldMatrix)
{
	////コンスタントバッファに渡す情報
	//XMVECTOR position = { 0, 3, -10, 0 };	//カメラの位置
	//XMVECTOR target = { 0, 0, 0, 0 };	//カメラの焦点
	//XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//ビュー行列 カメラから見た座標に変換
	//XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);//射影行列 遠近感をつける

	////引数: 視野角 アス比 NearClippingSurface FarClipSurface(近くはどこから、遠くはどこまで映すか)
	////NearClippingSurfaceとFarClipSurfaceの差はできるだけ小さくしていけ

//プロジェクション座標は、遠いものは引き伸ばし、近いものは圧縮．遠近を圧縮した幅1m.横高さ2m2mの四角い箱に収める
	//ズームと接近
	//視野角を狭めてズームすると、遠近感がなくなる
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	ID3D11SamplerState* pSampler = pTexture_->GetSampler();

	//テクスチャとサンプラーをシェーダーへ
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);
	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開

	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	Direct3D::pContext_->DrawIndexed(45, 0, 0);
}

void Dice::Release()
{
	pTexture_->Release();
	SAFE_RELEASE(pTexture_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}

//a
