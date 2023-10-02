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
	m_vtxBuff(nullptr)
{
	D3DXMatrixIdentity(&m_mtxWorld);
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
		&m_vtxBuff,
		NULL);

	VERTEX_3D* pVtx;	// ���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_vtxBuff->Unlock();

	return S_OK;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CObjectPolygon3D::Uninit()
{
	// �j��
	if (m_vtxBuff != nullptr)
	{
		m_vtxBuff->Release();
		m_vtxBuff = nullptr;
	}
	Release();
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CObjectPolygon3D::Update()
{
}

//--------------------------------------------------------------
// �`��
//--------------------------------------------------------------
void CObjectPolygon3D::Draw()
{
	// �f�o�C�X�ւ̃|�C���^
	// �f�o�C�X�̎擾
 	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// �J�����O�̐ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h���W�s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_vtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CApplication::GetInstance()->GetTexture()->GetTexture(GetTexture()));

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// ���C�g��L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �e�N�X�`���X�e�[�W�X�e�[�g�����ɖ߂�
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// �J�����O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//�f�o�C�X�ݒ�̏�����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// Z�e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// ���e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

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
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(Tex.P0, Tex.P2);
	pVtx[1].tex = D3DXVECTOR2(Tex.P1, Tex.P2);
	pVtx[2].tex = D3DXVECTOR2(Tex.P0, Tex.P3);
	pVtx[3].tex = D3DXVECTOR2(Tex.P1, Tex.P3);

	//���_�o�b�t�@���A�����b�N
	m_vtxBuff->Unlock();
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
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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
	m_vtxBuff->Unlock();
}

//--------------------------------------------------------------
// �F�̐ݒ�
//--------------------------------------------------------------
void CObjectPolygon3D::SetColor(const D3DXCOLOR& Collar)
{
	CObject::SetColor(Collar);

	VERTEX_3D *pVtx; //���_�ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXCOLOR color(GetColor());

	//�e�N�X�`���̍��W�ݒ�
	//���_�J���[�̐ݒ�
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//���_�o�b�t�@���A�����b�N
	m_vtxBuff->Unlock();
}
