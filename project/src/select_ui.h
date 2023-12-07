//**************************************************************
//
// �I������Ă�Object�ɂ���ē���s����������UI
// Author: Yuda Kaito
//
//**************************************************************
#ifndef _SELECT_UI_H_
#define _SELECT_UI_H_

//==============================================================
// include
//==============================================================
#include "object.h"

//==============================================================
// �O���錾
//==============================================================
class CObject2d;
class CText;

//==============================================================
// �N���X
//==============================================================
class CSelectUI : public CObject
{
private:
public:
	CSelectUI(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CSelectUI();

	HRESULT Init() override;
	void Update() override;

	void SetText(std::string);

private:
	CObject2d* m_ground;	// ���n

	CText* m_keyIcon;	// �Ή��L�[�̃e�L�X�g
	CText* m_text;		// �e�L�X�g
};
#endif	// _ITEM_DATA_H_