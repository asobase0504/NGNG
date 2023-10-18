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
#include "statue.h"
#include "enemy_manager.h"
#include "statue_manager.h"
#include "item_manager.h"
#include "item_data.h"
#include "player_manager.h"
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
#include "object_mesh.h"

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

	/*CObjectPolygon3D* object = CObjectPolygon3D::Create();
	object->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	object->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));*/

	{
		CObjectX* testX = CObjectX::Create(D3DXVECTOR3(50.0f, 25.0f, 0.0f));
		testX->LoadModel("BOX");
		testX->SetMoveRot(D3DXVECTOR3(0.0f, 0.01f, 0.0f));
		testX->CalculationVtx();
	}

	// �v���C���[�̐ݒ�
	CPlayer* pPlayer = CPlayerManager::GetInstance()->CreatePlayer(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	CEnemyManager::GetInstance()->CreateEnemy(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 50.0f), CEnemyManager::NONE);

	CMesh::Create();

	CItemManager::GetInstance()->CreateItem(D3DXVECTOR3(200.0f, 0.0f, 0.0f), ITEM_POWER_UP);
	m_camera->SetTargetPos(pPlayer->GetPos());

	CStatue* pStatue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(100.0f, 0.0f, 100.0f));

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