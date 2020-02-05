#pragma once

class CInput;
class CPolygon;
class CSlot : public CGameObject
{
private:

	ID3D11Buffer*	            m_VertexBuffer = NULL;
	CPolygon*                   m_Poly;
	CInput*                     m_Input;
	POINT                       m_Pt;
	XMMATRIX                    m_World;
	float                       m_MoveSpeed;
	float	                    m_ImgW;
	float                       m_ImgH;
	bool                        m_IsClick;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};