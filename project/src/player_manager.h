//**************************************************************
//
// �v���C���[�Ǘ�
// Author : ���c�喲
//
//**************************************************************
#ifndef _PLAYER_MANAGER_H_			// ���̃}�N����`������ĂȂ�������
#define _PLAYER_MANAGER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "task.h"
#include "player.h"

//==============================================================
// �O���錾
//==============================================================
class CObjectX;
class CController;
class CPlayer;
class CCollisionCylinder;

//==============================================================
// �v���C���[�Ǘ��N���X
//==============================================================
class CPlayerManager : public CTask
{
public:	// �V���O���g���p�̃C���X�^���X
	static CPlayerManager* GetInstance();
private:
	CPlayerManager();
	static CPlayerManager* m_playerManager;

public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	~CPlayerManager();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// �ÓI�����o�֐�
	CPlayer* CreatePlayer(D3DXVECTOR3 pos);			// �v���C���[�̐���

	// �Q�b�^�[
	CPlayer* GetPlayer() { return m_pPlayer; }
	const D3DXVECTOR3& GetPlayerPos() { return m_pPlayer->GetPos(); }

private:		// �����o�ϐ�
	CPlayer* m_pPlayer;
};
#endif
