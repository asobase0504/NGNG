//==================================================
// score
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "application.h"

#include "procedure3D.h"
#include "number3D.h"
#include "renderer.h"

//**************************************************
// �ÓI�����o�ϐ�
//**************************************************

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CProcedure3D::CProcedure3D() :
	CObject(CTaskGroup::LEVEL_SYSTEM),
	m_number(0),
	m_digit(0),
	m_align(CENTER)
{
	m_numberObj.clear();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CProcedure3D::~CProcedure3D()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CProcedure3D::Init()
{
	CObject::Init();
	D3DXMatrixIdentity(&m_mtxTrans);
	Update();			// ����X�V
	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CProcedure3D::Uninit()
{
	for (CNumber3D* displayNumber : m_numberObj)
	{
		displayNumber->SetMtxWorldParent(nullptr);
	}
	CObject::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CProcedure3D::Update()
{
	CObject::Update();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxView;				// �v�Z�p�}�g���b�N�X
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �J�����̋t�s���ݒ�
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	//�ʒu�𔽉f
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	if (m_mtxWorldParent != nullptr)
	{
		//�ʒu�𔽉f
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, m_mtxWorldParent);
	}
}

//--------------------------------------------------
// �ʒu�̐ݒ�Ƒ傫���̐ݒ�
//--------------------------------------------------
void CProcedure3D::SetPos(const D3DXVECTOR3& inPos)
{
	CObject::SetPos(inPos);
	D3DXMatrixTranslation(&m_mtxTrans, inPos.x, inPos.y, inPos.z);

	int cnt = 0;
	for (CNumber3D* displayNumber : m_numberObj)
	{
		float posX = 0.0f;
		switch (m_align)
		{
		case CProcedure3D::LEFT:
			posX = displayNumber->GetSize().x * 1.75f * cnt;
			break;
		case CProcedure3D::RIGHT:
			posX = displayNumber->GetSize().x * 1.75f * (cnt - m_digit);
			break;
		case CProcedure3D::CENTER:
			posX = displayNumber->GetSize().x * 1.75f * ((float)cnt - (m_digit - 1) * 0.5f);
			break;
		default:
			assert(false);
			break;
		}

		displayNumber->SetPos(D3DXVECTOR3(posX, 0.0f, 0.0f));
		cnt++;
	}
}

//--------------------------------------------------
// �F�̐ݒ�
//--------------------------------------------------
void CProcedure3D::SetColor(const D3DXCOLOR & inColor)
{
	for (CNumber3D* displayNumber : m_numberObj)
	{
		displayNumber->SetColor(inColor);
	}
}

//--------------------------------------------------
// �F�̉��Z
//--------------------------------------------------
void CProcedure3D::AddColor(const D3DXCOLOR & inColor)
{
	for (CNumber3D* displayNumber : m_numberObj)
	{
		displayNumber->SetColor(inColor + displayNumber->GetColor());
	}
}

//--------------------------------------------------
// �傫���̐ݒ�
//--------------------------------------------------
void CProcedure3D::SetSize(const D3DXVECTOR3 & inSize)
{
	CObject::SetSize(inSize);
	for (CNumber3D* displayNumber : m_numberObj)
	{
		displayNumber->SetSize(inSize);
	}
	SetPos(m_pos);
}

//--------------------------------------------------
// �傫���̉��Z
//--------------------------------------------------
void CProcedure3D::AddSize(const D3DXVECTOR3 & inSize)
{
	for (CNumber3D* displayNumber : m_numberObj)
	{
		displayNumber->AddSize(inSize);
	}
}

//--------------------------------------------------
// �l�̐ݒ�
//--------------------------------------------------
void CProcedure3D::SetNumber(int inNumber)
{
	m_number = inNumber;
	CalDigit();

	std::vector<int> aPosTexU;		//�e���̐������i�[
	aPosTexU.resize(m_digit);

	{
		int number = inNumber;
		for (int i = m_digit - 1; i >= 0; --i)
		{
			aPosTexU[i] = number % 10;
			number /= 10;
		}
	}

	// �e�N�X�`�����W�̐ݒ�
	int cnt = 0;
	for (CNumber3D* displayNumber : m_numberObj)
	{
		displayNumber->SetNumber(aPosTexU[cnt]);
		displayNumber->SetTexPos(10.0f, (float)aPosTexU[cnt]);
		cnt++;
	}
}

//--------------------------------------------------
// �`�悵�Ȃ���I������
//--------------------------------------------------
void CProcedure3D::SetDisplay(bool isDisplay)
{
	for (CNumber3D* displayNumber : m_numberObj)
	{
		displayNumber->SetDisplay(isDisplay);
	}
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CProcedure3D *CProcedure3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int number)
{
	CProcedure3D *pProcedure;
	pProcedure = new CProcedure3D;

	assert(pProcedure != nullptr);

	pProcedure->Init();
	pProcedure->SetSize(size);
	pProcedure->SetNumber(number);
	pProcedure->SetPos(pos);

	return pProcedure;
}

//--------------------------------------------------
// �����𐔂���
//--------------------------------------------------
void CProcedure3D::CalDigit()
{
	m_digit = 0;
	int number = m_number;
	do
	{
		m_digit++;
		number *= 0.1f;
	} while (number != 0);

	int diff = m_digit - m_numberObj.size();
	while (diff != 0)
	{
		if (diff < 0)
		{ // �����ߏ莞
			m_numberObj.back()->Uninit();
			m_numberObj.pop_back();	// �폜
			diff++;
		}
		else
		{ // ��������Ȃ���
			CNumber3D* number = CNumber3D::Create();
			m_numberObj.push_back(number);	// �ǉ�
			number->SetSize(m_size);
			SetEndChildren(number);
			number->SetMtxWorldParent(&m_mtxWorld);
			diff--;
		}
	}
	SetPos(m_pos);
}