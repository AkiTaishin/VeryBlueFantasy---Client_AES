#ifndef CUBE_H_
#define CUBE_H_

class CCube : public CGameObject {
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	CTexture* m_Texture = NULL;
	XMVECTOR m_Quaternion;
	float MoveSpeed = 0.1f;
	float RotationSpeed = 0.2f;
	float RotX, RotZ = 0.0f;
	float RotY = 0.0f;

public:
	CCube() {};
	~CCube() {};

	void Init();
	void Uninit();
	void Update();
	void Draw();
};

#endif // !CUBE_H_
