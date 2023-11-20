//**************************************************************
//
// Object
// Author : �l�c����
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "object.h"
#include "object2d.h"
#include "application.h"
#include "input.h"

//==============================================================
// ���_���
//==============================================================
const D3DXVECTOR3 CObject2d::m_Vtx[ANCHOR_MAX][4] =
{
	{
	D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
	D3DXVECTOR3(+1.0f, -1.0f, 0.0f),
	D3DXVECTOR3(-1.0f, +1.0f, 0.0f),
	D3DXVECTOR3(+1.0f, +1.0f, 0.0f),
	},
	{
	D3DXVECTOR3(0.0f, -1.0f, 0.0f),
	D3DXVECTOR3(+2.0f, -1.0f, 0.0f),
	D3DXVECTOR3(0.0f, +1.0f, 0.0f),
	D3DXVECTOR3(+2.0f, +1.0f, 0.0f),
	}
};

//--------------------------------------------------------------
// �R���X�g���N�g�֐�
//--------------------------------------------------------------
CObject2d::CObject2d(CTaskGroup::EPriority list) :
	CObject(list,CTaskGroup::EPushMethod::PUSH_CURRENT), m_vtxBuff(nullptr),
	m_anchor(ANCHOR_CENTER)
{
}

//--------------------------------------------------------------
// �f�X�g���N�g�֐�
//--------------------------------------------------------------
CObject2d::~CObject2d()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CObject2d::Init()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = 10.0f;

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,		//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_vtxBuff,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//------------------------ 
	// ���_���̐ݒ�
	//------------------------
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@���A�����b�N����
	m_vtxBuff->Unlock();

	 m_counterAnim = 0;
	 m_patternAnimX = 1;
	 m_patternAnimY = 1;

	 m_divisionX = 1;
	 m_divisionY = 1;
	 m_divisionMAX = m_divisionX*m_divisionY;

	 m_animationSpeed = 0;
	 m_animationSpeedCount = 0;

	 m_timar = 0;
	 m_timaCount = 0;
	 m_isOnAnimation = false;
	 m_isLoop = false;

	return S_OK;
}

//--------------------------------------------------------------
// �|���S���̏I��
//--------------------------------------------------------------
void CObject2d::Uninit()
{
	// �j��
	if (m_vtxBuff != nullptr)
	{
		m_vtxBuff->Release();
		m_vtxBuff = nullptr;
	}
	CTask::Uninit();
}

//--------------------------------------------------------------
// �|���S���̍X�V
//--------------------------------------------------------------
void CObject2d::Update()
{
	CObject::Update();

	VERTEX_2D *pVtx; //���_�ւ̃|�C���^

	// ���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 addPos[4];
	D3DXMATRIX mtx;	// �v�Z�p�}�g���b�N�X

	//�}�g���b�N�X�쐬
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, m_rot.z);

	//���_���W
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&addPos[i], &m_Vtx[m_anchor][i], &mtx);

		pVtx[i].pos.x = m_pos.x + (addPos[i].x * m_size.x);	// �T�C�Y�ύX
		pVtx[i].pos.y = m_pos.y + (addPos[i].y * m_size.y);	// �T�C�Y�ύX
		pVtx[i].pos.z = 0.0f;
	}

	//���_�o�b�t�@���A�����b�N
	m_vtxBuff->Unlock();

	Animation();	// �A�j���[�V�����̍X�V
}

//--------------------------------------------------------------
// �|���S���̕`��
//--------------------------------------------------------------
void CObject2d::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_vtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̎擾
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(GetTexture()));
	
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�v���~�e�B�u(�|���S��)��
	pDevice->SetTexture(0, NULL);
}

//--------------------------------------------------------------
// create�֐�
//--------------------------------------------------------------
CObject2d *CObject2d::Create(CTaskGroup::EPriority list)
{
	CObject2d * pObject = nullptr;
	pObject = new CObject2d(list);

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//--------------------------------------------------------------
// �ʒu��object���ɓ����Ă��邩�ۂ�
// Author : Yuda Kaito
//--------------------------------------------------------------
bool CObject2d::PointAndAABB(const D3DXVECTOR3& inPos)
{
	bool hitX = (m_pos.x + m_size.x > inPos.x) && (m_pos.x - m_size.x < inPos.x);
	bool hitY = (m_pos.y + m_size.y > inPos.y) && (m_pos.y - m_size.y < inPos.y);

	if (hitX && hitY)
	{
		return true;
	}

	return false;
}

//--------------------------------------------------------------
// �A�j���[�V�����̓���
//--------------------------------------------------------------
void CObject2d::Animation()
{
	if (!m_isOnAnimation)
	{
		return;
	}

	m_timaCount++;

	if (m_timaCount >= m_timar)
	{
		m_animationSpeedCount++;
		if (m_animationSpeedCount >= m_animationSpeed)
		{
			m_animationSpeedCount = 0;
			m_patternAnimX++;

			if (m_patternAnimX > m_divisionX)
			{//�A�j���[�V����
				m_patternAnimX = 0;
				m_patternAnimY++;
				if (m_patternAnimY >= m_divisionY)
				{
					m_patternAnimY = 0;
					if (!m_isLoop)
					{
						Uninit();
					}
					return;
				}
			}

			float U = 1.0f / (m_divisionX);
			float V = 1.0f / (m_divisionY);
			float AnimU = U * (m_patternAnimX);
			float AnimV = V * (m_patternAnimY);
			SetTex(PositionVec4(AnimU, AnimU + U, AnimV, AnimV + V));
		}
	}
}

//--------------------------------------------------------------
// �Z�b�g�e�N�X�`��(2d)
//--------------------------------------------------------------
void CObject2d::SetTex(PositionVec4 Tex)
{
	VERTEX_2D *pVtx; //���_�ւ̃|�C���^

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

void CObject2d::SetTexPos(float BesideSplit, float nNumIndex)
{
	//���_���W�ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumIndex / BesideSplit, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nNumIndex + 1) / BesideSplit, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nNumIndex / BesideSplit, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nNumIndex + 1) / BesideSplit, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_vtxBuff->Unlock();
}

//--------------------------------------------------------------
// �F�̐ݒ�
//--------------------------------------------------------------
void CObject2d::SetColor(const D3DXCOLOR& inColor)
{
	m_color = inColor;	// �F�̑��

	VERTEX_2D *pVtx;	// ���_�ւ̃|�C���^

	// ���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	// ���_�o�b�t�@���A�����b�N
	m_vtxBuff->Unlock();
}

//--------------------------------------------------------------
// Animation�̖����ݒ�֐�
//--------------------------------------------------------------
void CObject2d::SetAnimation(const int U, const int V,const int Speed,const int Drawtimer,const bool loop)
{
	m_divisionX = U;
	m_divisionY = V;
	m_divisionMAX = m_divisionY*m_divisionX;

	m_patternAnimX = 0;
	m_patternAnimY = 0;
	m_animationSpeed = Speed;
	m_timar = Drawtimer;
	m_isOnAnimation = true;
	m_isLoop = loop;

	//�\�����W���X�V
	SetTex(PositionVec4(
		1.0f / m_divisionX * (m_patternAnimX / (m_divisionX))
		, 1.0f / m_divisionX *(m_patternAnimX / (m_divisionX)) + 1.0f / m_divisionX
		, 1.0f / m_divisionY * (m_patternAnimY % (m_divisionY))
		, 1.0f / m_divisionY * (m_patternAnimY % (m_divisionY)+1.0f / m_divisionY* m_divisionY)));
}
