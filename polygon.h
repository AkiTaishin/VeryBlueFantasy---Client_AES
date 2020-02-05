#pragma once

class CInput;
class CPolygon : public CGameObject
{
private:

	ID3D11Buffer*	            m_VertexBuffer = NULL;
	CTexture*		            m_Texture1 = NULL;
	CTexture*		            m_Texture2 = NULL;
	CInput*                     m_Input = NULL;
	POINT                       m_Pt;
	XMMATRIX                    m_World;

public:
	int                         m_number;

	void Init(std::string fileName1, std::string fileName2, float width, float hight);
	void Init(std::string fileName1, std::string fileName2, float width, float hight, float alpha);
	void Init(std::string fileName, float width, float hight, float alpha);
	void Uninit();
	void Update();
	void Draw(int number);
};