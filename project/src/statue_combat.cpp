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

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CStatueCombat::CStatueCombat(int nPriority)
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

	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CStatueCombat::Uninit()
{
	// �I������
	CStatue::Uninit();
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CStatueCombat::Update()
{
	// �X�V����
	CStatue::Update();

	// �v���C���[���G��Ă��鎞
	if (!Touch())
	{
		return;
	}

	D3DXVECTOR3 pos = GetPos();

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		// �G�̐���
		float randX = FloatRandom(1.5f, 0.5f);
		float randZ = FloatRandom(1.5f, 0.5f);

		CEnemyManager::GetInstance()->CreateEnemy(D3DXVECTOR3(pos.x * randX, pos.y, pos.z * randZ), D3DXVECTOR3(50.0f, 50.0f, 50.0f), CEnemyManager::NONE);
	}

#ifdef _DEBUG
#if 0
	CDebugProc::Print("CombatPos(%f,%f,%f)\n", GetPos().x, GetPos().y, GetPos().z);
#endif // 0
#endif // _DEBUG
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