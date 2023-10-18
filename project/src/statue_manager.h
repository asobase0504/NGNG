//**************************************************************
//
// ^���Ǘ�
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
class CObjectX;
class CCollisionBox;

//==============================================================
// ���Ǘ��N���X
//==============================================================
class CStatueManager : public CTask
{
public:	// �V���O���g���p�̃C���X�^���X
	static CStatueManager* GetInstance();
private:
	CStatueManager();
	static CStatueManager* m_statueManager;

public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	~CStatueManager();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// �ÓI�����o�֐�
	CStatue* CreateStatue(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// ���̐���

	// �Q�b�^�[
	CStatue* GetPlayer() { return m_pStatue; }
	const D3DXVECTOR3& GetPlayerPos() { return m_pStatue->GetPos(); }
	CCollisionBox* GetStatueBox() { return m_pStatue->GetCollisionBox(); }

private:		// �����o�ϐ�
	CStatue *m_pStatue;
};
#endif

