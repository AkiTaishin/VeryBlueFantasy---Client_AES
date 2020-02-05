#pragma once

class CPolygon;
class CInput;
class CLoginButton : public CGameObject
{
private:

	ID3D11Buffer*	            m_VertexBuffer = NULL;
	CPolygon*	                m_Poly;
	CInput*                     m_Input;
	POINT                       m_Pt;
	XMMATRIX                    m_World;
	float	                    m_ImgW;
	float                       m_ImgH;

public:
	void Init(float x, float y);
	void Uninit();
	void Update();
	void Draw();
};