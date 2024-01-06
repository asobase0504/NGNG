//**************************************************************
//
// �G�l�~�[HPUI
// Author : �y���m��
//
//**************************************************************
#ifndef _ENEMY_HP_UI_H_	// ���̃}�N����`������ĂȂ�������
#define _ENEMY_HP_UI_H_	// ��d�C���N���[�h�h�~�̃}�N����`

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
// �G�l�~�[HPUI
//==============================================================
class  CEnemy_HPUI : public CObject
{
private:
	static const D3DXVECTOR3 GAGE_SIZE;
	static const int SUB_TIMING;
	static const int SUB_TIME;
public:
	static CEnemy_HPUI *Create(CCharacter* pEnemy);

	CEnemy_HPUI();
	~CEnemy_HPUI() override;

	HRESULT Init() override;
	void Update() override;

	void SetEnemy(CCharacter* enemy) { m_pEnemy = enemy; }

	void SetDisplay(bool display) override;
private:
	CCharacter* m_pEnemy;				// �G�l�~�[
	bool m_isDamege;
	int m_subTimingCount;
	bool m_canSub;
	int m_subTimeCount;
	float m_perHP;
	float m_perDamage;
	float m_volumeSubPerDamage;	// 1�t���[���ō���

	// ������
	CObjectPolygon3D* m_outline;		// �w�i(��)
	CObjectPolygon3D* m_background;		// �w�i(��)
	CObjectPolygon3D* m_gageHP;			// ���̗�
	CObjectPolygon3D* m_gageDamage;		// �󂯂��_���[�W
	std::list<CObjectPolygon3D*> m_abnormalIcons;		// ��Ԉُ�
};

#endif