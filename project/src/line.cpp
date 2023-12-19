//**************************************************************
//
// ���C���`�揈��(line.h)
// Author : �������l
// �T�v : ���C���������s��
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "line.h"
#include "renderer.h"
#include "application.h"


bool CLine::m_alldisplay = true;

//--------------------------------------------------------------
// �C���X�^���X����
// Author : �������l
// �T�v : 2D�I�u�W�F�N�g�𐶐�����
//--------------------------------------------------------------
CLine* CLine::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CLine *pLine = nullptr;

	// �������̉��
	pLine = new CLine;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pLine != nullptr);

	// ���l�̏�����
	pLine->Init();

	// �C���X�^���X��Ԃ�
	return pLine;
}

//--------------------------------------------------------------
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//--------------------------------------------------------------
CLine::CLine() :
	CObject(CTaskGroup::EPriority::LEVEL_3D_1)
{
	m_vtxBuff = nullptr;						// ���_�o�b�t�@
	m_mtxWorld = {};							// ���[���h�}�g���b�N�X
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �傫��
	m_start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �n�_
	m_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �I�_
}

//--------------------------------------------------------------
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//--------------------------------------------------------------
CLine::~CLine()
{
}

//--------------------------------------------------------------
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//--------------------------------------------------------------
HRESULT CLine::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,									// ���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&m_vtxBuff,
		NULL);

	assert(m_vtxBuff != nullptr);

	// �|���S�����̐ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �傫��

	// ���_���W�̐ݒ�
	SetVtx();

	// �F�̐ݒ�
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//--------------------------------------------------------------
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//--------------------------------------------------------------
void CLine::Uninit()
{
	//���_�o�b�t�@��j��
	if (m_vtxBuff != nullptr)
	{
		m_vtxBuff->Release();

		m_vtxBuff = nullptr;
	}

	CObject::Uninit();
}

//--------------------------------------------------------------
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//--------------------------------------------------------------
void CLine::Update()
{
	CObject::Update();
	m_pos = *m_targetPos;
	m_rot = *m_targetRot;
	SetVtx();
}

//--------------------------------------------------------------
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//--------------------------------------------------------------
void CLine::Draw()
{
	if (!m_isDisplay || !m_alldisplay)
	{
		return;
	}

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	D3DXMatrixIdentity(&m_mtxWorld);
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �����̔��f
	// �s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	// �s��|���Z�֐� (������ * ��O������������Ɋi�[)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);		// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// Z�e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);

	// ���e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���C�g�𖳌�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_vtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���C���`��
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);

	// ���C�g��L��	
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// Z�e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// ���e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, nullptr);
}

//--------------------------------------------------------------
// ���_���W�Ȃǂ̐ݒ�
// Author : �������l
// �T�v : 3D���_���W�Arhw�A���_�J���[��ݒ肷��
//--------------------------------------------------------------
void CLine::SetVtx()
{
	//���_���ւ̃|�C���^�𐶐�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = m_start;
	pVtx[1].pos = m_goal;

	// �e���_�̖@���̐ݒ�(*�x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_vtxBuff->Unlock();
}

//--------------------------------------------------------------
// ���_�J���[�̐ݒ�
// Author : �������l
// �T�v : ���_�J���[��ݒ肷��
//--------------------------------------------------------------
void CLine::SetColor(const D3DXCOLOR& color)
{
	CObject::SetColor(color);

	//���_���ւ̃|�C���^�𐶐�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;

	//���_�o�b�t�@���A�����b�N
	m_vtxBuff->Unlock();
}

//--------------------------------------------------------------
// ���_�J���[�̐ݒ�
// Author : �������l
// �T�v : ���_�J���[��ݒ肷��
//--------------------------------------------------------------
void CLine::SetLine(D3DXVECTOR3 start, D3DXVECTOR3 goal)
{
	// �n�_
	m_start = start;

	// �I�_
	m_goal = goal;

	// ���_���W�̐ݒ�
	SetVtx();
}
