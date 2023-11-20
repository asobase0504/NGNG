//**************************************************************
//
// �X�L��
// Author : ����]��
//
//**************************************************************
#ifndef _SKILL_ENTITY_H_			// ���̃}�N����`������ĂȂ�������
#define _SKILL_ENTITY_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "task.h"
#include "character.h"

//==============================================================
// �O���錾
//==============================================================
class CCharacter;
class CCollision;

//==============================================================
// �X�L���N���X
//==============================================================
class CSkillEntity : public CTask
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
	virtual void InitAbility() = 0;							// �X�L�����n�܂�Ƃ�
	virtual void AllWayAbility() {}							// ������
	virtual void HitAbility(CCharacter* Target) = 0;		// �X�L���������������̌���

protected:		// �����o�ϐ�
	CCharacter*		m_apChara;			// �L�����N�^�[�̃C���X�^���X
	CCharacter::ERelation m_relation;
	CCollision*		m_Collision;		// �����蔻��

	std::string		m_Name;				// �X�L����
	float			m_Duration;			// ���ʎ���
};
#endif