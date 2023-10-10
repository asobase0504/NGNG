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

//==============================================================
// �萔
//==============================================================
const float CCameraGame::DISTANCE = 200.0f;

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
	m_rot = D3DXVECTOR3(0.25f, 0.0f, 0.0f);
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
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -DISTANCE);

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
