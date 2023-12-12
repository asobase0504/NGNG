//**************************************************************
//
// NUMBER
// Author:hamada ryuuga
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "number3D.h"
#include "application.h"

//--------------------------------------------------------------
// �R���X�g���N�g�֐�
//--------------------------------------------------------------
CNumber3D::CNumber3D(CTaskGroup::EPriority list) : CObjectPolygon3D(list)
{
}

//--------------------------------------------------------------
// �f�X�g���N�g�֐�
//--------------------------------------------------------------
CNumber3D::~CNumber3D()
{
}

//--------------------------------------------------------------
// �������֐�
//--------------------------------------------------------------
HRESULT CNumber3D::Init()
{
	m_myNumber = 0;
	m_speed = 0.0f;
	CObjectPolygon3D::Init();
	CObjectPolygon3D::SetTexture("NUMBER");
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	SetTex(PositionVec4(0.0f, 0.1f, 0.0f, 1.0f));
	m_isRelease = false;
	m_deathTimar = 0;
	m_isMove = true;
	return S_OK;
}

//--------------------------------------------------------------
// �j���֐�
//--------------------------------------------------------------
void CNumber3D::Uninit()
{
	CObjectPolygon3D::Uninit();
}

//--------------------------------------------------------------
// �X�V�֐�
//--------------------------------------------------------------
void CNumber3D::Update()
{
	CObjectPolygon3D::Update();

	if (m_isRelease)
	{
		m_deathTimar--;

		m_col.a -= 1.0f / m_deathTimarMax;

		m_pos.y -= 1.0f;

		CObjectPolygon3D::SetColor(m_col);

		if (m_deathTimar <= 0)
		{
			Uninit();
			return;
		}
	}
	if (m_isMove)
	{
		m_speed += (0.0f - m_speed) * 0.5f;	//�i�ړI�̒l-���݂̒l�j�������W��

		SetTex(PositionVec4(0.1f * m_myNumber, 0.1f * m_myNumber + 0.1f, 0.0f + m_speed, 1.0f + m_speed));
	}
}

//--------------------------------------------------------------
// �����֐�
//--------------------------------------------------------------
CNumber3D *CNumber3D::Create()
{
	CNumber3D * pObject = nullptr;
	pObject = new CNumber3D;

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//--------------------------------------------------------------
// �����܂ł̎��Ԑݒ�֐�
//--------------------------------------------------------------
void CNumber3D::ReleaseTimer(int nTimar)
{
	m_deathTimar = nTimar;
	m_deathTimarMax = m_deathTimar;
	m_isRelease = true;
}
