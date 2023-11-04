//**************************************************************
//
// �Q�[�����̃J����
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "camera_game.h"
#include "input.h"

//==============================================================
// �萔
//==============================================================
const float CCameraGame::DISTANCE = 145.0f;

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CCameraGame::CCameraGame()
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CCameraGame::~CCameraGame()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CCameraGame::Init()
{
	CCamera::Init();
	m_rot = D3DXVECTOR3(0.45f, 0.0f, 0.0f);
	return S_OK;
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CCameraGame::Update()
{
	CCamera::Update();

	if (m_targetPos == nullptr)
	{
		return;
	}

	m_posR = *m_targetPos;
	//m_posR.z += 50.0f;
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -DISTANCE);

	D3DXVECTOR3 mouseMove = CInput::GetKey()->GetMouseMove();

	m_rot.x += mouseMove.y * 0.01f;
	m_rot.y += mouseMove.x * 0.01f;

	if (m_rot.x >= (D3DX_PI * 0.5f))
	{
		m_rot.x = (D3DX_PI * 0.5f) * 0.9f;
	}
	if (m_rot.x <= (-D3DX_PI * 0.5f))
	{
		m_rot.x = -(D3DX_PI * 0.5f) * 0.9f;
	}

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxRot, mtxTrans;

	D3DXMatrixIdentity(&mtxWorld);	// �s�񏉊����֐�

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);		// �s���]�֐�
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);						// �s��|���Z�֐� 

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_posR.x, m_posR.y, m_posR.z);	// �s��ړ��֐�
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);	// �s��|���Z�֐�

	// D3DXVECTOR3�ɔ��f
	D3DXVec3TransformCoord(&m_posV, &m_posV, &mtxWorld);
}
