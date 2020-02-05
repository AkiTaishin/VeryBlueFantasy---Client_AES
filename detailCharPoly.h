#pragma once

class CPolygon;
class CDetailCharPoly : public CGameObject
{
private:

	ID3D11Buffer*	            m_VertexBuffer = NULL;
	CPolygon*	                m_Poly;
	POINT                       m_Pt;
	XMMATRIX                    m_World;
	float                       m_MoveSpeed;
	float	                    m_ImgW;
	float                       m_ImgH;

public:
	void Init(std::string fileName);
	void Uninit();
	void Update();
	void Draw();
};