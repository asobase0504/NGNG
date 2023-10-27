//**************************************************************
//
// ���Ǘ�
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
// �O���錾
//==============================================================
class CCollisionBox;

//==============================================================
// �G�Ǘ��N���X
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
		MAX
	};

	// �R���X�g���N�^�ƃf�X�g���N�^
	~CStatueManager();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// �ÓI�����o�֐�
	CStatue* CreateStatue(D3DXVECTOR3 pos, EType type);			// ���̐���
	CStatue* RandomCreateBlood(D3DXVECTOR3 pos);				// ���̍Ւd�����_������
	CStatue* RandomCreateChest(D3DXVECTOR3 pos);				// �󔠃����_������
	CStatue* RandomCreateLuck(D3DXVECTOR3 pos);					// �^�̍Ւd�����_������
	CStatue* RandomCreateCombat(D3DXVECTOR3 pos);				// �킢�̍Ւd�����_������

	CStatue* GetStatue() { return m_pStatue; }
	CCollisionBox* GetStatueBox() { return m_pStatue->GetCollisionBox(); }

private:		// �����o�ϐ�
	CStatue* m_pStatue;
};
#endif

