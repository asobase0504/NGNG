//============================
//
// �����ݒ�
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "words.h"

#include "application.h"
#
#include "object2D.h"
#include "font.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CWords::CWords(CTaskGroup::EPriority list) :CObject2d(list)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CWords::~CWords()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CWords::Init(void)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	CObject2d::Init();

	return S_OK;
}

//------------------------------------
// �`��
//------------------------------------
void CWords::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, GetVtx(), 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̎擾
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTex);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�v���~�e�B�u(�|���S��)��
	pDevice->SetTexture(0, NULL);
}

//------------------------------------
// create
//------------------------------------
CWords *CWords::Create(const char*Text, D3DXVECTOR3 pos, D3DXVECTOR3 Size, CFont::FONT Type)
{
	CWords * pObject = nullptr;
	pObject = new CWords();

	if (pObject != nullptr)
	{
		pObject->SetPos(pos);
		pObject->SetSize(Size);
		pObject->Init();
		pObject->Setwords(Text, Type);

	}
	return pObject;
}

//=============================================================================
// GetPos�֐�
//=============================================================================
void CWords::Setwords(const char*Text, CFont::FONT Type)
{
	std::string Txt = Text;
	if (Txt != "")
	{
		m_pTex = CFont::GetFont(Text, Type);
	}
	else
	{
		m_pTex = nullptr;
		SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
}
