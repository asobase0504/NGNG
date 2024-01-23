//==================================================
// score
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "application.h"

#include "procedure.h"
#include "number.h"

//**************************************************
// �ÓI�����o�ϐ�
//**************************************************

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CProcedure::CProcedure() :
	CObject(CTaskGroup::LEVEL_SYSTEM),
	m_align(LEFT),
	m_pNumber(nullptr)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CProcedure::~CProcedure()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CProcedure::Init()
{
	CObject::Init();
	return S_OK;
}

//--------------------------------------------------
// �������@�I�[�o�[���[�h
//--------------------------------------------------
HRESULT CProcedure::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, const int inNumber)
{
	CObject::Init();
	m_number = inNumber;

	m_minimumDigit = 1;

	m_size = size;

	// �����𐔂���
	CalDigit();

	m_pos = pos;
	SetPos(m_pos);

	return S_OK;
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CProcedure::Update()
{
	if (m_pNumber != nullptr && *m_pNumber != m_number)
	{
		SetNumber(*m_pNumber);
	}
}

//--------------------------------------------------
// �ʒu�̐ݒ�Ƒ傫���̐ݒ�
//--------------------------------------------------
void CProcedure::SetPos(const D3DXVECTOR3& inPos)
{
	CObject::SetPos(inPos);

	int cnt = 0;
	for (CNumber* displayNumber : m_numberObj)
	{
		float posX = 0.0f;
		switch (m_align)
		{
		case CProcedure::LEFT:
			posX = inPos.x + displayNumber->GetSize().x * 1.75f * cnt;
			break;
		case CProcedure::RIGHT:
			posX = inPos.x + displayNumber->GetSize().x * 1.75f * (cnt - m_digit);
			break;
		case CProcedure::CENTER:
			posX = inPos.x + displayNumber->GetSize().x * 1.75f * ((float)cnt - (m_digit - 1) * 0.5f);
			break;
		default:
			assert(false);
			break;
		}

		displayNumber->SetPos(D3DXVECTOR3(posX, inPos.y, 0.0f));
		cnt++;
	}
}

//--------------------------------------------------
// �F�̐ݒ�
//--------------------------------------------------
void CProcedure::SetColor(const D3DXCOLOR & inColor)
{
	for (CNumber* displayNumber : m_numberObj)
	{
		displayNumber->SetColor(inColor);
	}
}

//--------------------------------------------------
// �F�̉��Z
//--------------------------------------------------
void CProcedure::AddColor(const D3DXCOLOR & inColor)
{
	for (CNumber* displayNumber : m_numberObj)
	{
		displayNumber->SetColor(inColor + displayNumber->GetColor());
	}
}

//--------------------------------------------------
// �傫���̐ݒ�
//--------------------------------------------------
void CProcedure::SetSize(const D3DXVECTOR3 & inSize)
{
	for (CNumber* displayNumber : m_numberObj)
	{
		displayNumber->SetSize(inSize);
	}
	SetPos(m_pos);
}

//--------------------------------------------------
// �傫���̉��Z
//--------------------------------------------------
void CProcedure::AddSize(const D3DXVECTOR3 & inSize)
{
	for (CNumber* displayNumber : m_numberObj)
	{
		displayNumber->AddSize(inSize);
	}
}

//--------------------------------------------------
// �l�̐ݒ�
//--------------------------------------------------
void CProcedure::SetNumber(int inNumber)
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
	for (CNumber* displayNumber : m_numberObj)
	{
		displayNumber->SetNumber(aPosTexU[cnt]);
		displayNumber->SetTexPos(10.0f, (float)aPosTexU[cnt]);
		cnt++;
	}
}

void CProcedure::SetNumber(const int * inNumber)
{
	m_pNumber = inNumber;
	SetNumber(*m_pNumber);
}

//--------------------------------------------------
// �`�悵�Ȃ���I������
//--------------------------------------------------
void CProcedure::SetDisplay(bool isDisplay)
{
	for (CNumber* displayNumber : m_numberObj)
	{
		displayNumber->SetDisplay(isDisplay);
	}
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CProcedure *CProcedure::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int number)
{
	CProcedure *pProcedure;
	pProcedure = new CProcedure;

	assert(pProcedure != nullptr);

	pProcedure->Init(pos, size, number);

	return pProcedure;
}

void CProcedure::SetMinimumDigit(int count)
{
	m_minimumDigit = count;
	SetNumber(m_number);
}

//--------------------------------------------------
// �����𐔂���
//--------------------------------------------------
void CProcedure::CalDigit()
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
			CNumber* number = CNumber::Create();
			m_numberObj.push_back(number);	// �ǉ�
			number->SetSize(m_size);
			SetEndChildren(number);
			diff--;
		}
	}

	while (m_minimumDigit > m_numberObj.size())
	{
		CNumber* number = CNumber::Create();
		m_numberObj.push_back(number);	// �ǉ�
		number->SetSize(m_size);
		SetEndChildren(number);
		m_digit++;
	}

	SetPos(m_pos);
}