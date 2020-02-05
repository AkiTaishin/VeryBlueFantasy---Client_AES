#pragma once
#include "main.h"
#include "renderer.h"

class CMouse
{
private:

	POINT                       m_pt;

public:
	XMFLOAT3					m_Position;
	bool                        m_IsSelect;
	void Init();
	void Update();
};