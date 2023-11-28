//**************************************************************
//
// �f�o�b�O���[�h
// Author : ���c�喲
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "debug_mode.h"
#include "player.h"
#include "enemy.h"
#include "statue.h"
#include "enemy_manager.h"
#include "item_manager.h"
#include "item_data_base.h"
#include "player_manager.h"
#include "camera.h"
#include "light.h"
#include "object_polygon3d.h"
#include "PlayerController.h"

/* System�n�� */
#include "application.h"
#include "mode_fade.h"
#include "sound.h"
#include "input.h"
#include "camera_game.h"
#include "light.h"
#include "utility.h"

/* 3D�n�� */
#include "map.h"

/* Object�n�� */
#include "object_polygon3d.h"
#include "objectX.h"
#include "object_mesh.h"

#include "hp_ui.h"
#include "money_ui.h"
#include "skill_ui.h"

//==============================================================
// �萔
//==============================================================

//--------------------------------------------------------------
// �R���X�g���N�^
// Author : ���c�喲
//--------------------------------------------------------------
CDebugMode::CDebugMode()
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
// Author : ���c�喲
//--------------------------------------------------------------
CDebugMode::~CDebugMode()
{
}

//--------------------------------------------------------------
// ������
// Author : ���c�喲
//--------------------------------------------------------------
HRESULT CDebugMode::Init(void)
{
	m_camera = new CCameraGame;
	m_camera->Init();

	m_light = new CLight;
	m_light->Init();

	// �v���C���[�̐ݒ�
	CPlayer* pPlayer = CPlayerManager::GetInstance()->CreatePlayer(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	m_camera->SetTargetPos(pPlayer->GetPos());

	CHPUI::Create(pPlayer->GetHp());
	CMONEYUI::Create(pPlayer->GetMoney());
	CSKILLUI::Create(pPlayer->GetSkill(0));

	// �}�b�v�̐���
	CMap::Create("data/FILE/map/map01.json");

	return S_OK;
}

//--------------------------------------------------------------
// �I��
// Author : ���c�喲
//--------------------------------------------------------------
void CDebugMode::Uninit(void)
{

}

//--------------------------------------------------------------
// �X�V
// Author : ���c�喲
//--------------------------------------------------------------
void CDebugMode::Update(void)
{
	CInput* pInput;
	pInput = CInput::GetKey();

	CModeFade* pFade = CApplication::GetInstance()->GetFade();

	if (pInput->Trigger(DIK_F1))
	{
	//	pFade->NextMode(CApplication::MODE_DEBUG);
	}

	// T�L�[�Ń^�C�g��
	if (pInput->Trigger(DIK_1))
	{
		pFade->NextMode(CApplication::MODE_TITLE);
	}

	// S�L�[�őI�����
	if (pInput->Trigger(DIK_2))
	{
		pFade->NextMode(CApplication::MODE_SELECT);
	}

	// S�L�[�őI�����
	if (pInput->Trigger(DIK_3))
	{
		pFade->NextMode(CApplication::MODE_GAME);
	}
}