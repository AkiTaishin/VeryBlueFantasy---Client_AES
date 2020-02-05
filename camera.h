#pragma once

class CCamera :public CGameObject
{
private:

	RECT        m_Viewport;
	float       m_MoveSpeed;

	XMFLOAT3    m_WorkPos;
	XMFLOAT3    m_WorkRot;

	XMMATRIX	m_ViewMatrix;
	XMMATRIX	m_InvViewMatrix;
	XMMATRIX	m_ProjectionMatrix;

public:
	CCamera() {};
	~CCamera() {};

	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetVisibility(XMFLOAT3 Position);
};