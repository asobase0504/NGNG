//**************************************************************
//
// �L�����N�^�[
// Author : ���c�喲
//
//**************************************************************
#ifndef _CHARACTER_H_			// ���̃}�N����`������ĂȂ�������
#define _CHARACTER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "object.h"
#include "status.h"

//==============================================================
// �O���錾
//==============================================================
class CObjectX;
class CCollision;

//==============================================================
// �v���C���[�N���X
//==============================================================
class CCharacter : public CObject
{
private:		// �X�e�[�^�X�\����
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CCharacter(int nPriority = 3);
	~CCharacter();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// �ÓI�����o�֐�
	static CCharacter *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// �v���C���[�̐���

	CCollision* GetCollision() { return m_collision[0]; }

	std::vector<CObjectX*> GetModel() { return m_apModel; }

	void Damege(const int inDamage);

private:
	virtual void Attack();
	virtual void Move();
	void UpdatePos();			// ���W�̍X�V

protected:		// �����o�ϐ�
	std::vector<CObjectX*>		m_apModel;		// ���f���̃C���X�^���X
	std::vector<CCollision*>	m_collision;	// �����蔻��
private:		// �����o�ϐ�
	D3DXMATRIX		m_mtxWorld;					// ���[���h�}�g���b�N�X

protected:		// �X�e�[�^�X

	CStatus<int> m_hp;					// �̗�
	CStatus<int> m_addHp;				// �ǉ��̗�
	CStatus<int> m_addHpSubTime;		// �ǉ��̗͂̌�����
	CStatus<int> m_barrier;				// �o���A
	CStatus<int> m_barrierRePopTime;	// �o���A�̕�������
	CStatus<int> m_attack;				// �U����
	CStatus<int> m_defense;				// �h���
	CStatus<float> m_criticalRate;		// �N���e�B�J����
	CStatus<float> m_criticalDamage;	// �N���e�B�J���_���[�W
	CStatus<float> m_movePower;			// �ړ���
	CStatus<float> m_jumpPower;			// �W�����v��
	CStatus<int> m_jumpCount;			// �W�����v��
};
#endif
