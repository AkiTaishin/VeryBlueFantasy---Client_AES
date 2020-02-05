#pragma once

class CPolygon;
class CInput;
class CSelectBG : public CGameObject
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

public:
	/// <summary>
	/// 画面の横幅をスクリーンサイズに合わせる
	/// SCREEN_WIDTH / m_ImgW
	/// </summary>
	float                       m_ScreenImg;
	void Init();
	void Uninit();
	void Update();
	void Draw();
};