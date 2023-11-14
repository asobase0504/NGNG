//**************************************************************
//
// �Q�[����ʂ̃w�b�_�[
// Author:Hamada Ryuuga
//
//**************************************************************
#ifndef _GAME_H_		//���̃}�N������`����ĂȂ�������
#define _GAME_H_		//2�d�C���N���[�h�h�~�̃}�N����`

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
class CMap;
class CMapFade;

//==============================================================
// �Q�[���N���X
//==============================================================
class CGame : public CMode
{
public:
	CGame();
	~CGame();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	CCameraGame* GetCamera() { return m_camera; }

	void SetChangeMap();
	void ChangeMap(std::string);
private:
	CPlayerManager* m_player;	// �v���C���[
	CEnemyManager* m_enemy;		// �G
	CCameraGame* m_camera;
	CMap* m_map;
	CLight* m_light;
	CMapFade* m_mapFade;
};
#endif