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
	m_modelData{
	"BOX", }
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
	if (m_collisionCylinder->ToCylinder(CPlayerManager::GetInstance()->GetPlayerCylinder()))
	{
		int a = 0;
	}

	CObjectX::Update();

#ifdef _DEBUG
	CDebugProc::Print("StatueCollisionBox�Fpos(%f,%f,%f)\n", m_collisionBox->GetPos().x, m_collisionBox->GetPos().y, m_collisionBox->GetPos().z);
	CDebugProc::Print("StatueCollisionCylinder�Fpos(%f,%f,%f)\n", m_collisionCylinder->GetPos().x, m_collisionCylinder->GetPos().y, m_collisionCylinder->GetPos().z);
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
CStatue* CStatue::Create(const D3DXVECTOR3& inPos)
{
	CStatue* pStatue = nullptr;
	pStatue = new CStatue;

	if (pStatue != nullptr)
	{
		pStatue->Init();
		pStatue->SetPos(inPos);
		pStatue->m_collisionBox = CCollisionBox::Create(inPos, D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(10.0f,10.0f,10.0f));
		pStatue->m_collisionCylinder = CCollisionCylinder::Create(inPos,15.0f, 15.0f);
	}

	return pStatue;
}