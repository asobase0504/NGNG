//**************************************************************
//
// �|���S���o���b�g
// Author : �y���m��
//
//**************************************************************
#ifndef _BULLET_POLYGON_H_	// ���̃}�N����`������ĂȂ�������
#define _BULLET_POLYGON_H_	// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "object_polygon3d.h"

//==============================================================
// �}�N���錾
//==============================================================

//==============================================================
// �O���錾
//==============================================================
class CCharacter;
class CCollision;

//==============================================================
// ���|���S���̐ݒ�
//==============================================================
class  CBullet : public CObjectPolygon3D
{
public:
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float speed);

	CBullet();
	~CBullet() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetSpeed(float speed) { m_speed = speed; }
private:
	int m_life;
	bool m_ispenetration;
	float m_speed;
	CCollision*		m_collision;
};

#endif