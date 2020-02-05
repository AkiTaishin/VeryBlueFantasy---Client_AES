#pragma once

class CPolygon;
class CInput;
class CSummonButton : public CGameObject
{
private:

	ID3D11Buffer*	            m_VertexBuffer = NULL;
	CPolygon*	                m_Poly;
	CInput*                     m_Input;
	POINT                       m_Pt;
	XMMATRIX                    m_World;
	float                       m_MoveSpeed;
	float	                    m_ImgW;
	float                       m_ImgH;
	float                       m_ScreenImg;
	bool                        m_IsAlive;

public:
	void Init(float x, float y, float z, int number, bool flag);
	void Uninit();
	void Update();
	void Draw();
};