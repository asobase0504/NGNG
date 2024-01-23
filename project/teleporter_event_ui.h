//**************************************************************
//
// �e���|�[�^�[�C�x���g
// Author: Yuda Kaito
//
//**************************************************************
#ifndef _TELEPORTER_EVENT_UI_H_
#define _TELEPORTER_EVENT_UI_H_

//==============================================================
// include
//==============================================================
#include "object.h"

//==============================================================
// �O���錾
//==============================================================
class CObject2d;
class CText;
class CProcedure;

//==============================================================
// �N���X
//==============================================================
class CTeleporterEventUI : public CObject
{
private:
	static const D3DXVECTOR3 GROUND_POS;	// �o�[�ʒu
	static const D3DXVECTOR3 BAR_POS;	// �o�[�ʒu
	static const D3DXVECTOR3 BAR_SIZE;	// �o�[������
	static const D3DXVECTOR3 TEXT_POS;	// �e�L�X�g�ʒu
	static const int DISPLAY_TIME;	// �\������
public:
	CTeleporterEventUI(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CTeleporterEventUI();

	HRESULT Init() override;
	void Update() override;

	void SetReferenceTime(const int* inTime) { m_referenceTime = inTime; }
	void SetReferenceIsBossKill(const bool* inTime) { m_referenceIsBossKill = inTime; }

private:
	CObject2d* m_barGround;	// �Q�[�W�̉��n
	CObject2d* m_bar;		// �Q�[�W
	CText* m_chargeText;		// "�ς��E��"
	CText* m_bosskillText;		// "�{�X��|��"
	CObject2d* m_completeLine[2];		// �������C��

	const int* m_referenceTime;	// �Q�ƃ^�C��
	const bool* m_referenceIsBossKill;	// �G�̔r��
};
#endif	// _ITEM_DATA_H_