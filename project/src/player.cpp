//**************************************************************
//
// �v���C���[
// Author : ����]��
//
//**************************************************************

// include
#include "player.h"
#include "Controller.h"
#include "application.h"
#include "objectX.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CPlayer::CPlayer(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CPlayer::~CPlayer()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CPlayer::Init()
{
	m_apModel.resize(1);

	// ���f���̓ǂݍ���
	m_apModel[0] = CObjectX::Create(GetPos());
	m_apModel[0]->LoadModel("BOX");
	m_apModel[0]->SetMoveRot(D3DXVECTOR3(0.0f, 0.01f, 0.0f));
	m_apModel[0]->SetMaterialDiffuse(0, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));
	m_apModel[0]->CalculationVtx();

	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CPlayer::Uninit(void)
{
	// �R���g���[���[�̔j��
	if (m_controller != nullptr)
	{
		delete m_controller;
		m_controller = nullptr;
	}

	CObject::Release();
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CPlayer::Update(void)
{
	if (m_controller == nullptr)
	{
		return;
	}

	// �ړ�
	Move();

	// �W�����v
	Jump();

	// ���W�X�V
	Updatepos();

	// �X�V����
	CObject::Update();

#ifdef _DEBUG
	CDebugProc::Print("Player�Fpos(%f,%f,%f)\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("Player�Fmove(%f,%f,%f)\n", m_move.x, m_move.y, m_move.z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------
void CPlayer::Draw(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p

	//���݂̃}�e���A�����ێ�
	pDevice->GetMaterial(&matDef);

	//�p�[�c�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�p�[�c�̃��f���̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�p�[�c�̃��f���̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
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
// ����
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
// �ړ�
//--------------------------------------------------------------
void CPlayer::Move()
{
	// �ړ���
	SetMove(m_controller->Move());
}

//--------------------------------------------------------------
// �W�����v
//--------------------------------------------------------------
void CPlayer::Jump()
{
	bool jump = false;

	// �W�����v��
	jump = m_controller->Jump();

	if (jump)
	{
		m_move.y += 25.0f;
		jump = false;
	}

	if (m_pos.y > 0.0f)
	{
		// �d��
		m_move.y -= 1.0f;
	}
}

//--------------------------------------------------------------
// �_�b�V��
//--------------------------------------------------------------
void CPlayer::Dash()
{
	// �ړ��ʂ̎擾
	D3DXVECTOR3 move = GetMove();

	// �_�b�V��
	m_isdash = m_controller->Dash();

	if (m_isdash)
	{
		// �_�b�V�����x
		move.x *= DASH_SPEED;
		move.z *= DASH_SPEED;
	}

	// �ړ��ʂ̐ݒ�
	SetMove(move);
}

//--------------------------------------------------------------
// ���W�̍X�V
//--------------------------------------------------------------
void CPlayer::Updatepos()
{
	// ���W�̎擾
	D3DXVECTOR3 pos = GetPos();

	SetPosOld(pos);			// �O��̈ʒu�̕ۑ�
	pos += GetMove();		// �ʒu�̍X�V

	// ���W�̐ݒ�
	SetPos(pos);
	m_apModel[0]->SetPos(pos);
}

//--------------------------------------------------------------
// �R���g���[���[�̐ݒ�
//--------------------------------------------------------------
void CPlayer::SetController(CController * inOperate)
{
	m_controller = inOperate;
	m_controller->SetToOrder(this);
}