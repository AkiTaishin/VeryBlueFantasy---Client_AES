#pragma once
#include "getCharacterInfo.h"

class CPolygon;
class CInput;
class CDetailButton : public CGameObject
{
private:

	ID3D11Buffer*	            m_VertexBuffer = NULL;
	CPolygon*	                m_Poly;
	CInput*                     m_Input;
	POINT                       m_Pt;
	XMMATRIX                    m_World;
	float	                    m_ImgW;
	float                       m_ImgH;

	// ApplyButtonÇ»ÇÁTrue
	bool                        m_IsApply;

	// Ç«Ç±Ç…ï“ê¨Ç∑ÇÈÇ©
	int                         m_FormationNumber;
	std::vector<GETINFO>        m_GetCharData;

public:
	void Init(std::string fileName, float x, float y, float alpha, bool IsTure);
	void Uninit();
	void Update();
	void Draw();
};