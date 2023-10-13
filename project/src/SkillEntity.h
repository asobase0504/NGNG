//**************************************************************
//
// �X�L��
// Author : ����]��
//
//**************************************************************
#ifndef _SKILLENTITY_H_			// ���̃}�N����`������ĂȂ�������
#define _SKILLENTITY_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "skill.h"

//==============================================================
// �O���錾
//==============================================================
class CCharacter;

//==============================================================
// �X�L���N���X
//==============================================================
class CSkillEntity : public CSkill
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CSkillEntity(int nPriority = 3);
	~CSkillEntity();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;

	// �ÓI�����o�֐�
	static CSkillEntity *Create(D3DXVECTOR3 pos);			// �X�L���̐���

private:		// �����o�ϐ�
	CCharacter*		m_apChara;				// �L�����N�^�[�̃C���X�^���X
	int				m_ID[MAX_SKILL];		// �X�L��ID
};
#endif