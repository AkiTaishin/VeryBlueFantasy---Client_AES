#pragma once

class CCharacterSelectButton;
class CInput;
class CFirstCharacter : public CGameObject
{
private:

	ID3D11Buffer*	                        m_VertexBuffer = NULL;
	CCharacterSelectButton*	                m_Button;
	CInput*                                 m_Input;
	XMMATRIX                                m_World;
	float	                                m_ImgW;
	float                                   m_ImgH;
	float                                   m_ScreenImg;
	int                                     m_Location;

public:
	void Init(std::string fileName, float x, float y);
	void Uninit();
	void Update();
	void Draw();
};