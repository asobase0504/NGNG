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
class CCollision;

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

	// �ÓI�����o�֐�
	static CSkill	*Create();									// �X�L���̐���

	bool Skill();												// �X�L��
	// Getter
	int	GetCT() { return m_CT; }

	// Setter
	void SetSkill(std::string tag, CCharacter *chara);			// �X�L���̐ݒ�
	void SetCT(int ct) { m_CT = ct; }

	std::string GetName() { return m_Name; }

private:		// �����o�ϐ�
	CCharacter*		m_apChara;			// �L�����N�^�[�̃C���X�^���X
	CCollision*		m_Collision;		// �����蔻��
	int				m_CT;				// �N�[���^�C��
	float			m_Duration;			// ���ʎ���
	float			m_atkSpd;			// �U�����x
	bool			m_isCollision;		// �������Ă��邩�ǂ���	
	std::string		m_Name;				// �X�L����
};
#endif