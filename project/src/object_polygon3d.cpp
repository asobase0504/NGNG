//**************************************************************
//
// Object
// Author : Hamada Ryuuga
// AUthor : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "object_polygon3d.h"
#include "application.h"
#include "input.h"
#include "utility.h"
#include "camera.h"
#include "renderer.h"
#include "texture.h"

//==============================================================
// �ÓI�����o�ϐ�
//==============================================================
const D3DXVECTOR3 CObjectPolygon3D::m_Vtx[4] =
{
	D3DXVECTOR3(-1.0f, +1.0f, 0.0f),
	D3DXVECTOR3(+1.0f, +1.0f, 0.0f),
	D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
	D3DXVECTOR3(+1.0f, -1.0f, 0.0f),
};

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CObjectPolygon3D::CObjectPolygon3D(CTaskGroup::EPriority list) :
	CObject(list,CTaskGroup::EPushMethod::PUSH_CURRENT),
	m_pVtxBuff(nullptr)
{
	
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CObjectPolygon3D::~CObjectPolygon3D()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CObjectPolygon3D::Init()
{
	SetType(CObject::EType::POLYGON);

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	// �f�o�C�X�̎擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,		//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�J���[�ݒ�
	for (int i = 0; i < 4; i++)
	{
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CObjectPolygon3D::Uninit()
{
	// �j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	Release();
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CObjectPolygon3D::Update()
{
	AddRot(D3DXVECTOR3(0.1f,0.1f,0.1f));
}

//--------------------------------------------------------------
// �`��
//--------------------------------------------------------------
void CObjectPolygon3D::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CRenderer::GetInstance()->GetDevice();	//�f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̎擾
	CTexture* pTexture = CTexture::GetInstance();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_textureKey));

	// ���e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���C�g�𖳌�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�|���S���̌`
		0,										//���_�̊J�n�ꏊ
		4);

	// ���C�g��L��	
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//�J�����O�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CObjectPolygon3D* CObjectPolygon3D::Create(CTaskGroup::EPriority list)
{
	CObjectPolygon3D* pObject = nullptr;
	pObject = new CObjectPolygon3D(list);

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//--------------------------------------------------------------
// �Z�b�g�e�N�X�`��(2d)
//--------------------------------------------------------------
void CObjectPolygon3D::SetTex(PositionVec4 Tex)
{
	VERTEX_3D *pVtx; //���_�ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(Tex.P0, Tex.P2);
	pVtx[1].tex = D3DXVECTOR2(Tex.P1, Tex.P2);
	pVtx[2].tex = D3DXVECTOR2(Tex.P0, Tex.P3);
	pVtx[3].tex = D3DXVECTOR2(Tex.P1, Tex.P3);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------------------
// �ʒu�̐ݒ�
//--------------------------------------------------------------
void CObjectPolygon3D::SetPos(const D3DXVECTOR3& inPos)
{
	CObject::SetPos(inPos);

	// �}�g���b�N�X�̌v�Z
	GiftMtx(&m_mtxWorld, m_pos, m_rot);
}

//--------------------------------------------------------------
// �����̐ݒ�
//--------------------------------------------------------------
void CObjectPolygon3D::SetRot(const D3DXVECTOR3& inRot)
{
	CObject::SetRot(inRot);

	// �}�g���b�N�X�̌v�Z
	GiftMtx(&m_mtxWorld, m_pos, m_rot);
}

//--------------------------------------------------------------
// �傫���̐ݒ�
//--------------------------------------------------------------
void CObjectPolygon3D::SetSize(const D3DXVECTOR3 &size)
{
	CObject::SetSize(size);

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//------------------------
	// ���_���̐ݒ�
	//------------------------
	for (int i = 0; i < 4; ++i)
	{
		pVtx[i].pos.x = m_Vtx[i].x * GetSize().x;
		pVtx[i].pos.y = m_Vtx[i].y * GetSize().y;
		pVtx[i].pos.z = m_Vtx[i].z * GetSize().z;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------------------
// �F�̐ݒ�
//--------------------------------------------------------------
void CObjectPolygon3D::SetColor(const D3DXCOLOR& Collar)
{
	CObject::SetColor(Collar);

	VERTEX_3D *pVtx; //���_�ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXCOLOR color(GetColor());

	//�e�N�X�`���̍��W�ݒ�
	//���_�J���[�̐ݒ�
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
