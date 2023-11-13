//**************************************************************
//
// �L�����N�^�[�I�����
// Author : ���c�喲
//
//**************************************************************
#ifndef _CHARACTER_SELECT_H_
#define _CHARACTER_SELECT_H_

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
// �L�����N�^�[�I���N���X
//==============================================================
class CCharacterSelect :public CMode
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
	CCharacterSelect();
	~CCharacterSelect() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	CSelect* m_start;
	CObject2d* m_startShadow;
};
#endif
