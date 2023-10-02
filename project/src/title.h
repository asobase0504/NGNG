//**************************************************************
//
// ���� ( �^�C�g�� )
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _TITLE_H_
#define _TITLE_H_

//==============================================================
// include
//==============================================================
#include "mode.h"

//==============================================================
// �O���錾
//==============================================================
class CSelect;
class CObject2d;

//==============================================================
// �^�C�g���N���X
//==============================================================
class CTitle :public CMode
{
	// �J�ڐ�
	enum ESelectMode
	{
		MODE_GAME = 0,		// �Q�[�����	
		MODE_TUTORIAL,		// �`���[�g���A�����
		MODE_RANKING,		// �����L���O���
		MODE_END,			// �I��
		MODE_MAX
	};

public:
	CTitle();
	~CTitle() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:

	CSelect* m_start;
	CObject2d* m_startShadow;
};
#endif