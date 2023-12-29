//**************************************************************
//
// �킢�̍Ւd
// Author : ���c�喲
//
//**************************************************************

// include
#include "statue_combat.h"
#include "player_manager.h"
#include "enemy_manager.h"
#include "input.h"
#include "utility.h"
#include "map.h"
#include "game.h"
#include "application.h"
#include "difficult.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CStatueCombat::CStatueCombat()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CStatueCombat::~CStatueCombat()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CStatueCombat::Init()
{
	// ����������
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	CStatue::Init(pos, rot);
	LoadModel("STATUE_COMBAT");
	m_uiText = "�킢���n�߂�";

	return S_OK;
}

//--------------------------------------------------------------
// �I����
//--------------------------------------------------------------
bool CStatueCombat::Select(CCharacter * selectCharacter)
{
	D3DXVECTOR3 pos = GetPos();

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		// �G�̐���
		float randX = FloatRandom(1.5f, 0.5f);
		float randZ = FloatRandom(1.5f, 0.5f);

		CDifficult *pDiff = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetDifficult();
		int exp = pDiff->GetEnemyLevel();

		CEnemy* enemy = CEnemyManager::GetInstance()->CreateEnemy(D3DXVECTOR3(pos.x * randX, pos.y, pos.z * randZ), CEnemyDataBase::SKELTON, exp);
		enemy->TakeItem(CItemDataBase::ITEM_ELITE);
		enemy->SetIsElite();
	}

	m_collisionCylinder->Uninit();
	m_collisionCylinder = nullptr;

	return true;
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CStatueCombat* CStatueCombat::Create(D3DXVECTOR3 pos)
{
	CStatueCombat* pStatuecombat;
	pStatuecombat = new CStatueCombat;
	pStatuecombat->SetPos(pos);
	pStatuecombat->Init();

	return pStatuecombat;
}