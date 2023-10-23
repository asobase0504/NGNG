//**************************************************************
//
// ��
// Author: ���c �喲
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "statue.h"
#include "collision_box.h"
#include "player_manager.h"
#include "player.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CStatue::CStatue(CTaskGroup::EPriority list) :
	m_modelData("BOX")
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CStatue::~CStatue()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CStatue::Init()
{
	CObjectX::Init();
	m_collisionBox = CCollisionBox::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRot(),D3DXVECTOR3(10.0f, 10.0f, 10.0f));
	m_collisionCylinder = CCollisionCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15.0f, 15.0f);
	LoadModel(m_modelData);

	return S_OK;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CStatue::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CStatue::Update()
{
	m_collisionBox->SetPos(GetPos());
	m_collisionCylinder->SetPos(GetPos());

	bool a = CPlayerManager::GetInstance()->GetPlayer()->GetCollision()->ToBox(m_collisionBox, true);

	if (a)
	{
		// �����o�����ʒu
		D3DXVECTOR3 extrusion = ((CCollisionCylinder*)CPlayerManager::GetInstance()->GetPlayer()->GetCollision())->GetExtrusion();
		CPlayerManager::GetInstance()->GetPlayer()->SetPos(D3DXVECTOR3(extrusion));
		CPlayerManager::GetInstance()->GetPlayer()->GetCollision()->SetPos(D3DXVECTOR3(extrusion));

		CPlayerManager::GetInstance()->GetPlayer()->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	CObjectX::Update();

#ifdef _DEBUG
	CDebugProc::Print("StatueCollisionBox:pos(%f,%f,%f)\n", m_collisionBox->GetPos().x, m_collisionBox->GetPos().y, m_collisionBox->GetPos().z);
	CDebugProc::Print("StatueCollisionCylinder:pos(%f,%f,%f)\n", m_collisionCylinder->GetPos().x, m_collisionCylinder->GetPos().y, m_collisionCylinder->GetPos().z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// �`��
//--------------------------------------------------------------
void CStatue::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CStatue* CStatue::Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot)
{
	CStatue* pStatue = nullptr;
	pStatue = new CStatue;

	if (pStatue != nullptr)
	{
		pStatue->Init();
		pStatue->SetPos(inPos);
		pStatue->m_collisionBox = CCollisionBox::Create(inPos, inRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		pStatue->m_collisionCylinder = CCollisionCylinder::Create(inPos,15.0f, 15.0f);
	}

	return pStatue;
}

bool CStatue::Touch(CPlayer* pPlayer)
{
	if (m_collisionCylinder->ToCylinder((CCollisionCylinder*)pPlayer->GetCollision()))
	{
		return true;
	}

	return false;
}