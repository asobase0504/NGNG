//**************************************************************
//
// �Q�[�����
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "enemy_manager.h"
#include "item_manager.h"
#include "item_data.h"
#include "camera.h"
#include "light.h"
#include "object_polygon3d.h"
#include "PlayerController.h"

/* Sestem�n�� */
#include "application.h"
#include "fade.h"
#include "sound.h"
#include "input.h"
#include "camera_game.h"
#include "light.h"
#include "utility.h"

/* 3D�n�� */

/* Object�n�� */
#include "object_polygon3d.h"
#include "objectX.h"

//==============================================================
// �萔
//==============================================================

//--------------------------------------------------------------
// �R���X�g���N�^
// Author : Yuda Kaito
//--------------------------------------------------------------
CGame::CGame()
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
// Author : Yuda Kaito
//--------------------------------------------------------------
CGame::~CGame()
{
}

//--------------------------------------------------------------
// ������
// Author : Yuda Kaito
//--------------------------------------------------------------
HRESULT CGame::Init(void)
{
	m_camera = new CCameraGame;
	m_camera->Init();

	m_light = new CLight;
	m_light->Init();

	//�v���C���[�̐ݒ�
	m_player[0] = CPlayer::Create(D3DXVECTOR3(50.0f,0.0f,0.0f));
	m_camera->SetTargetPos(m_player[0]->GetPos());

	m_player[0]->SetController(new CPlayerController(-1));

	CEnemyManager::GetInstance()->CreateEnemy(D3DXVECTOR3(100.0f, 0.0f, 0.0f),CEnemyManager::NONE);
	CItemManager::GetInstance()->CreateItem(D3DXVECTOR3(200.0f, 0.0f, 0.0f), ITEM_POWER_UP);

	return S_OK;
}

//--------------------------------------------------------------
// �I��
// Author : Yuda Kaito
//--------------------------------------------------------------
void CGame::Uninit(void)
{

}

//--------------------------------------------------------------
// �X�V
// Author : Yuda Kaito
//--------------------------------------------------------------
void CGame::Update(void)
{
}