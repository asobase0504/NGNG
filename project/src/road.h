//**************************************************************
//
// ���|���S��
// Author : �y���m��
//
//**************************************************************
#ifndef _ROAD_POLYGON_H_	// ���̃}�N����`������ĂȂ�������
#define _ROAD_POLYGON_H_	// ��d�C���N���[�h�h�~�̃}�N����`

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

//==============================================================
// ���|���S���̐ݒ�
//==============================================================
class  CRoad : public CObjectPolygon3D
{
public:
	static CRoad *Create(D3DXCOLOR col);

	CRoad();
	~CRoad() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetTarget(CCharacter* pTarget) { m_target = pTarget; }
	void SetShooter(CCharacter* pShooter) { m_shooter = pShooter; }
	void SetUse(bool use) { m_isuse = use; }

private:
	CCharacter* m_target;
	CCharacter* m_shooter;
	D3DXCOLOR m_col;

	bool m_isuse;
};

#endif