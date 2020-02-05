#pragma once

class CInput;
class CPolygon;
class CManager;
class CParty : public CGameObject
{
private:
	//CManager*                   m_Scene;
	ID3D11Buffer*	            m_VertexBuffer = NULL;
	CPolygon*                   m_Poly;
	CInput*                     m_Input;
	POINT                       m_Pt;
	XMMATRIX                    m_World;
	float                       m_MoveSpeed;
	float	                    m_ImgW;
	float                       m_ImgH;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};