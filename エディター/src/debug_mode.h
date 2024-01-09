//**************************************************************
//
// �Q�[�����(�f�o�b�O)�̃w�b�_�[
// Author:���c�喲
//
//**************************************************************
#ifndef _DEBUG_MODE_H_		//���̃}�N������`����ĂȂ�������
#define _DEBUG_MODE_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "mode.h"

//==============================================================
// �}�N���錾
//==============================================================

//==============================================================
// �O���錾
//==============================================================
class CPlayerManager;
class CEnemyManager;
class CCameraGame;
class CLight;

//==============================================================
// �f�o�b�O���[�h�N���X
//==============================================================
class CDebugMode : public CMode
{
public:
	CDebugMode();
	~CDebugMode();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	CCameraGame* GetCamera() { return m_camera; }
private:
	CPlayerManager* m_player;	// �v���C���[
	CEnemyManager* m_enemy;		// �G
	CCameraGame* m_camera;
	CLight* m_light;
};
#endif
