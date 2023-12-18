//**************************************************************
//
// �G�Ǘ�
// Author : ���c�喲
//
//**************************************************************
#ifndef _ENEMY_MANAGER_H_			// ���̃}�N����`������ĂȂ�������
#define _ENEMY_MANAGER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "task.h"
#include "enemy.h"
#include "enemy_data_base.h"

//==============================================================
// �O���錾
//==============================================================
class CObjectX;
class CController;
class CEnemy;
class CCollisionBox;

//==============================================================
// �G�Ǘ��N���X
//==============================================================
class CEnemyManager : public CTask
{
public:	// �V���O���g���p�̃C���X�^���X
	static CEnemyManager* GetInstance();
private:
	CEnemyManager();
	static CEnemyManager* m_enemyManager;

public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	~CEnemyManager();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Uninit() override;

	// �ÓI�����o�֐�
	CEnemy* CreateEnemy(D3DXVECTOR3 pos, CEnemyDataBase::EEnemyType type, int level);			// �G�l�~�[�̐���
	// �����_���X�|�[��
	CEnemy* RandomSpawn();

private:		// �����o�ϐ�
};
#endif