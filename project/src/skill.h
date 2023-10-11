//**************************************************************
//
// �X�L��
// Author : ����]��
//
//**************************************************************
#ifndef _SKILL_H_			// ���̃}�N����`������ĂȂ�������
#define _SKILL_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "task.h"

//==============================================================
// �O���錾
//==============================================================
class CCharacter;

//==============================================================
// �X�L���N���X
//==============================================================
class CSkill : public CTask
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CSkill(int nPriority = 3);
	~CSkill();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;

private:		// �����o�ϐ�
	std::vector<CCharacter*>		m_apChara;		// �L�����N�^�[�̃C���X�^���X
};
#endif