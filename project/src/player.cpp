//**************************************************************
//
// vC[
// Author : ûüì]
//
//**************************************************************

// include
#include "player.h"
#include "Controller.h"
#include "application.h"
#include "objectX.h"

//--------------------------------------------------------------
// RXgN^
//--------------------------------------------------------------
CPlayer::CPlayer(int nPriority)
{

}

//--------------------------------------------------------------
// fXgN^
//--------------------------------------------------------------
CPlayer::~CPlayer()
{

}

//--------------------------------------------------------------
// ú»
//--------------------------------------------------------------
HRESULT CPlayer::Init()
{
	m_apModel.resize(1);

	// fÌÇÝÝ
	m_apModel[0] = CObjectX::Create(GetPos());
	m_apModel[0]->LoadModel("BOX");
	m_apModel[0]->SetMoveRot(D3DXVECTOR3(0.0f, 0.01f, 0.0f));
	m_apModel[0]->SetMaterialDiffuse(0, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));
	m_apModel[0]->CalculationVtx();

	return S_OK;
}

//--------------------------------------------------------------
// I¹
//--------------------------------------------------------------
void CPlayer::Uninit(void)
{
	// Rg[[Ìjü
	if (m_controller != nullptr)
	{
		delete m_controller;
		m_controller = nullptr;
	}

	CObject::Release();
}

//--------------------------------------------------------------
// XV
//--------------------------------------------------------------
void CPlayer::Update(void)
{
	// Ú®ÊÌæ¾
	D3DXVECTOR3 move = GetMove();
	// ÀWÌæ¾
	D3DXVECTOR3 pos = GetPos();

	if (m_controller == nullptr)
	{
		return;
	}

	// Ú®
	Move();

	// Wv
	Jump();

	// ÀWXV
	Updatepos();

	// XV
	CObject::Update();

#ifdef _DEBUG
	CDebugProc::Print("PlayerFpos(%f,%f,%f)\n", pos.x, pos.y, pos.z);
	CDebugProc::Print("PlayerFmove(%f,%f,%f)\n", move.x, move.y, move.z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// `æ
//--------------------------------------------------------------
void CPlayer::Draw(void)
{
	//foCXÖÌ|C^
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//vZp}gbNX
	D3DMATERIAL9 matDef;			//»ÝÌ}eAÛ¶p

	//»ÝÌ}eAðÛ
	pDevice->GetMaterial(&matDef);

	//p[cÌ[h}gbNXÌú»
	D3DXMatrixIdentity(&m_mtxWorld);

	//p[cÌfÌü«ð½f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//p[cÌfÌÊuð½f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//[h}gbNXÌÝè
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int i = 0; i < (int)m_apModel.size(); i++)
	{
		if (m_apModel[i]->GetParent() == nullptr)
		{
			m_apModel[i]->SetMtxWorld(m_mtxWorld);
		}
	}
}

//--------------------------------------------------------------
// ¶¬
//--------------------------------------------------------------
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer* pPlayer;
	pPlayer = new CPlayer(CObject::PLAYER);
	pPlayer->SetPos(pos);
	pPlayer->m_rot = rot;
	pPlayer->Init();

	return pPlayer;
}

//--------------------------------------------------------------
// Ú®
//--------------------------------------------------------------
void CPlayer::Move()
{
	// Ú®Ê
	SetMove(m_controller->Move());
}

//--------------------------------------------------------------
// Wv
//--------------------------------------------------------------
void CPlayer::Jump()
{
	// Ú®ÊÌæ¾
	D3DXVECTOR3 move = GetMove();

	bool jump = false;

	// Wv
	jump = m_controller->Jump();

	if (jump)
	{
		// WvÍ
		move.y += 25.0f;
		jump = false;
	}

	if (GetPos().y > 0.0f)
	{
		// dÍ
		move.y -= 1.0f;
	}

	// Ú®ÊÌÝè
	SetMove(move);
}

//--------------------------------------------------------------
// _bV
//--------------------------------------------------------------
void CPlayer::Dash()
{
	// Ú®ÊÌæ¾
	D3DXVECTOR3 move = GetMove();

	// _bV
	m_isdash = m_controller->Dash();

	if (m_isdash)
	{
		// _bV¬x
		move.x *= DASH_SPEED;
		move.z *= DASH_SPEED;
	}

	// Ú®ÊÌÝè
	SetMove(move);
}

//--------------------------------------------------------------
// ÀWÌXV
//--------------------------------------------------------------
void CPlayer::Updatepos()
{
	// ÀWÌæ¾
	D3DXVECTOR3 pos = GetPos();

	SetPosOld(pos);			// OñÌÊuÌÛ¶
	pos += GetMove();		// ÊuÌXV

	// ÀWÌÝè
	SetPos(pos);
	m_apModel[0]->SetPos(pos);
}

//--------------------------------------------------------------
// Rg[[ÌÝè
//--------------------------------------------------------------
void CPlayer::SetController(CController * inOperate)
{
	m_controller = inOperate;
	m_controller->SetToOrder(this);
}