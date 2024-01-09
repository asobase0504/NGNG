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
	explicit CSkill();
	~CSkill();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Update() override;

	// �ÓI�����o�֐�
	static CSkill* Create();	// ����

	bool Use();	//�g�p

	// Getter
	int	GetCT() { return m_CT; }
	int GetStock() { return m_stock; }
	int GetMaxStock() { return m_stockMax; }

	// Setter
	void SetSkill(std::string tag, CCharacter *chara);		// �X�L���̐ݒ�
	void SetCT(int ct) { m_CT = ct; }

	std::string GetName() { return m_Name; }

private:		// �����o�ϐ�
	CCharacter*		m_apChara;			// �L�����N�^�[�̃C���X�^���X
	int				m_CT;				// �N�[���^�C��
	float			m_Duration;			// ���ʎ���
	float			m_atkSpd;			// �U�����x
	bool			m_isCollision;		// �������Ă��邩�ǂ���
	int m_stockMax;
	int m_stock;
	std::string		m_Name;				// �X�L����
};
#endif