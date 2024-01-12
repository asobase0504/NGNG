//**************************************************************
//
// �������Ǘ�
// Author : ���c�喲
//
//**************************************************************
#ifndef _STATUE_MANAGER_H_			// ���̃}�N����`������ĂȂ�������
#define _STATUE_MANAGER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "task.h"
#include "statue.h"

//==============================================================
// �������N���X
//==============================================================
class CStatueManager : public CTask
{
public:	// �V���O���g���p�̃C���X�^���X
	static CStatueManager* GetInstance();
private:
	CStatueManager();
	static CStatueManager* m_statueManager;

public:
	enum EType
	{
		NONE = 0,
		BLOOD,
		CHEST,
		LUCK,
		COMBAT,
		TELEPORTER,
		MAX
	};

	// �R���X�g���N�^�ƃf�X�g���N�^
	~CStatueManager();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Uninit() override;

	// �����v���Z�X
	CStatue* CreateStatue(D3DXVECTOR3 pos,int type);	// ���̐���
	CStatue* CreateStatue(int type);					// ���̐���
	CStatue* RandomCreate();			// �����_���ȑ�����
	CStatue* RandomCreateChest();		// �󔠃����_������

private:		// �����o�ϐ�
};
#endif

