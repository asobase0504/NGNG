//**************************************************************
//
// �G
// Author : ���c�喲
//
//**************************************************************
#ifndef _ENEMY_H_			// ���̃}�N����`������ĂȂ�������
#define _ENEMY_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "character.h"

//==============================================================
// �}�N���錾
//==============================================================
#define MAX_SPEED	(0.3f)

//==============================================================
// �O���錾
//==============================================================
class CObjectX;
class CController;
class CCollisionBox;
class CCollisionSphere;
class CEnemyDataBase;

//==============================================================
// �G�N���X
//==============================================================
class CEnemy : public CCharacter
{
public:
	using ACTIVITY_FUNC = std::function<void(CEnemy*)>;
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CEnemy(int nPriority = 3);
	~CEnemy();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// �ÓI�����o�֐�
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// �v���C���[�̐���
	CCollisionBox* GetBox() { return m_collision; }
	void SetActivity(ACTIVITY_FUNC NowAct) { m_Activity = NowAct; }
	ACTIVITY_FUNC GetActivity() { return m_Activity; }

private:
	void Move();		// �ړ�

private:	// �����o�ϐ�
	CCollisionBox* m_collision;
	CCollisionSphere* m_collisionSphere;
	ACTIVITY_FUNC	m_Activity;
};
#endif