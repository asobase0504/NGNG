//**************************************************************
//
// �L�����N�^�[
// Author : ���c�喲
//
//**************************************************************

// include
#include "character.h"
#include "player.h"
#include "enemy.h"
#include "application.h"
#include "objectX.h"
#include "PlayerController.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CCharacter::CCharacter(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CCharacter::~CCharacter()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CCharacter::Init()
{
	m_apModel.resize(1);

	// ���f���̓ǂݍ���
	m_apModel[0] = CObjectX::Create(m_pos);
	m_apModel[0]->LoadModel("BOX");
	m_apModel[0]->SetMoveRot(D3DXVECTOR3(0.0f, 0.01f, 0.0f));
	m_apModel[0]->SetMaterialDiffuse(0, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));
	m_apModel[0]->CalculationVtx();

	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CCharacter::Uninit(void)
{
	// �j������
	CObject::Release();
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CCharacter::Update(void)
{
	// ���W�̍X�V����
	UpdatePos();

	// �X�V����
	CObject::Update();
}

//--------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------
void CCharacter::Draw(void)
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
CCharacter* CCharacter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�L�����N�^�[����
	CCharacter* pCharacter = new CCharacter;

	if (pCharacter != nullptr)
	{//NULL�`�F�b�N
	 //�����o�ϐ��ɑ��
		//������
		pCharacter->Init();
	}

	return pCharacter;
}

void CCharacter::Attack()
{
}

void CCharacter::Move()
{
}

//--------------------------------------------------------------
// ���W�̍X�V
//--------------------------------------------------------------
void CCharacter::UpdatePos()
{
	// ���W�̎擾
	D3DXVECTOR3 pos = GetPos();

	SetPosOld(pos);			// �O��̈ʒu�̕ۑ�
	pos += GetMove();		// �ʒu�̍X�V

	// ���W�̐ݒ�
	SetPos(pos);
	m_apModel[0]->SetPos(pos);
}