#pragma once

class CPolygon;
class CInput;
class CHeaderSound : public CGameObject
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

	/// <summary>
	/// �N���b�N���ꂽ���ǂ���
	/// �ʏ펞��False
	/// </summary>
	bool                        m_IsClick;

	/// <summary>
	/// ��ʂ̉������X�N���[���T�C�Y�ɍ��킹��
	/// SCREEN_WIDTH / m_ImgW
	/// </summary>
	float                       m_ScreenImg;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};