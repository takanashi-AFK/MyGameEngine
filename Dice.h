#pragma once

#include <DirectXMath.h>
#include "Direct3D.h"
#include"Texture.h"
#include"Quad.h"

using namespace DirectX;


class Dice :public Quad
{

public:
	Dice();
	~Dice();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
};


