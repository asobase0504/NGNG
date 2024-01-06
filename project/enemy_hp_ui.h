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
public:
	static CEnemy_HPUI *Create(CCharacter* pEnemy);

	CEnemy_HPUI();
	~CEnemy_HPUI() override;

	HRESULT Init() override;
	void Update() override;

	void SetEnemy(CCharacter* enemy) { m_pEnemy = enemy; }
private:
	bool m_isShow;						// ���g��`�悷�邩�ۂ�
	CCharacter* m_pEnemy;				// �G�l�~�[
	CObjectPolygon3D* m_outline;		// �w�i(��)
	CObjectPolygon3D* m_background;		// �w�i(��)
	CObjectPolygon3D* m_gageHP;			// ���̗�
	CObjectPolygon3D* m_gageDamage;		// �󂯂��_���[�W
	std::list<CObjectPolygon3D*> m_abnormalIcons;		// ��Ԉُ�
};

#endif