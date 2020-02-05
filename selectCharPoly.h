#pragma once

class CPolygon;
class CInput;
class CSelectCharPoly : public CGameObject
{
private:

	ID3D11Buffer*	            m_VertexBuffer = NULL;
	CPolygon*	                m_Poly;
	CInput*                     m_Input;
	POINT                       m_Pt;
	XMMATRIX                    m_World;
	float	                    m_ImgW;
	float                       m_ImgH;

	/// <summary>
	/// ID��ۑ����ăN���b�N���ꂽ�Ƃ��ɂǂ̃L�����N�^�[�ڍ׉�ʂɍs�����Ɏg�p����
	/// Init�Ŏ擾
	/// </summary>
	int                         m_CharacterID;

public:
	void Init(std::string fileName, float x, float y, int id);
	void Uninit();
	void Update();
	void Draw();
};