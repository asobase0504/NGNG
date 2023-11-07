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
	enum EType
	{
		NONE = 0,
		SKELETON,
		MAX
	};

	// �R���X�g���N�^�ƃf�X�g���N�^
	~CEnemyManager();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// �ÓI�����o�֐�
	CEnemy* CreateEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size, EType type);			// �G�l�~�[�̐���
	// �����_���X�|�[��
	void RandomSpawn();

	std::vector<CEnemy*> GetEnemy() { return m_pEnemy; }
	//CCollisionBox* GetEnemyBox() { return m_pEnemy[0]->GetBox(); }

private:		// �����o�ϐ�
	EType m_type;
	std::vector<CEnemy*> m_pEnemy;
};
#endif