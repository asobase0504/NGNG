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
	struct SHP
	{
		int total;
		int base;
		int addItem;
		float mulItem;
		int addBuff;
		float mulBuff;
	};
	struct SAttack
	{
		int total;
		int base;
		int addItem;
		float mulItem;
		int addBuff;
		float mulBuff;
	};
	struct SDefense
	{
		int total;
		int base;
		int addItem;
		float mulItem;
		int addBuff;
		float mulBuff;
	};
	struct SCriticalRate
	{
		int total;
		int base;
		int addItem;
		float mulItem;
		int addBuff;
		float mulBuff;
	};
	struct SCriticalDamage
	{
		int total;
		int base;
		int addItem;
		float mulItem;
		int addBuff;
		float mulBuff;
	};
	struct SMovePower
	{
		int total;
		int base;
		int addItem;
		float mulItem;
		int addBuff;
		float mulBuff;
	};
	struct SJumpPower
	{
		int total;
		int base;
		int addItem;
		float mulItem;
		int addBuff;
		float mulBuff;
	};
	struct SJumpCount
	{
		int total;
		int base;
		int addItem;
		float mulItem;
		int addBuff;
		float mulBuff;
	};
	struct SAddHP
	{
		int total;
		int base;
		int addItem;
		float mulItem;
		int addBuff;
		float mulBuff;
	};
	struct SAddHPSubTime
	{
		int total;
		int base;
		int addItem;
		float mulItem;
		int addBuff;
		float mulBuff;
	};
	struct SBarrier
	{
		int total;
		int base;
		int addItem;
		float mulItem;
		int addBuff;
		float mulBuff;
	};
	struct SBarrierRePopTime
	{
		int total;
		int base;
		int addItem;
		float mulItem;
		int addBuff;
		float mulBuff;
	};
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

private:
	virtual void Attack();
	virtual void Move();
	void UpdatePos();			// ���W�̍X�V

protected:		// �����o�ϐ�
	std::vector<CObjectX*>		m_apModel;		// ���f���̃C���X�^���X
	std::vector<CCollision*>	m_collision;	// �����蔻��
private:		// �����o�ϐ�
	D3DXMATRIX		m_mtxWorld;					// ���[���h�}�g���b�N�X

private:		// �X�e�[�^�X

	SHP m_hp;
	SAttack m_attack;
	SDefense m_defense;
	SCriticalRate m_criticalRate;
	SCriticalDamage m_criticalDamage;
	SMovePower m_movePower;
	SJumpPower m_jumpPower;
	SJumpCount m_jumpCount;
	SAddHP m_addHp;
	SAddHPSubTime m_addHpSubTime;
	SBarrier m_barrier;
	SBarrierRePopTime m_barrierRePopTime;
};
#endif
