//**************************************************************
//
// �Q�[�����̃J����
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "camera_title.h"
#include "input.h"

//==============================================================
// �萔
//==============================================================
const float CTitleCamera::DISTANCE = 195.0f;

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CTitleCamera::CTitleCamera()
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CTitleCamera::~CTitleCamera()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CTitleCamera::Init()
{
	CCamera::Init();
	m_rot = D3DXVECTOR3(0.45f, 0.0f, 0.0f);
	return S_OK;
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CTitleCamera::Update()
{
	CCamera::Update();

	m_posR = D3DXVECTOR3(0.0f, 100.0f, DISTANCE);
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -DISTANCE);

	D3DXVECTOR3 mouseMove = CInput::GetKey()->GetMouseMove();

	m_rot.x += mouseMove.y * 0.0025f;
	m_rot.y += mouseMove.x * 0.0025f;

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
	
	// D3DXVECTOR3�ɔ��f
	D3DXVec3TransformCoord(&m_posV, &m_posV, &mtxWorld);
	// D3DXVECTOR3�ɔ��f
	D3DXVec3TransformCoord(&m_posR, &m_posR, &mtxWorld);
}
