//**************************************************************
//
// result
// Author: Buriya Kota
//
//**************************************************************
#ifndef _RESULT_H_
#define _RESULT_H_

//==============================================================
// include
//==============================================================
#include "task.h"

//==============================================================
// �O���錾
//==============================================================
class CObject2d;
class CText;
class CUIBackGround;

//==============================================================
// �N���X
//==============================================================
class CResult : public CTask
{
private:

public:
	CResult(CTaskGroup::EPriority list = CTaskGroup::LEVEL_3D_1);
	~CResult();

	HRESULT Init() override;
	void Update() override;

	static CResult* Create();

private:
	CObject2d* m_bg;

	// ��ԏ�
	CObject2d* m_loseBG;
	CText* m_loseText;

	// �f�[�^
	CUIBackGround* m_dataBG;
	CText* m_dataText;
	CObject2d* m_dataTextBG;
	CObject2d* m_dataTextBGOutLine;

	/* ��� */
	CUIBackGround* m_infoBG;
	CText* m_infoText;
	CObject2d* m_infoTextBG;
	CObject2d* m_infoTextBGOutLine;

	// ���W�A�C�e��
	CObject2d* m_takeItemTextBG;
	CText* m_takeItemText;

	// �o�b�N
	CObject2d* m_backBGOutLine;
	CObject2d* m_backBG;
	CText* m_backText;
};
#endif	// _GOLD_NUGGET_H_