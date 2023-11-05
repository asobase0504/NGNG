//**************************************************************
//
// �X�e�[�^�X
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _STATUS_H_			// ���̃}�N����`������ĂȂ�������
#define _STATUS_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//--------------------------------------------------------------
// include
//--------------------------------------------------------------
#include "task.h"

//--------------------------------------------------------------
// �O���錾
//--------------------------------------------------------------
class CCharacter;

//==============================================================
// �X�e�[�^�X
//==============================================================
template <class T>
class CStatus
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	CStatus() :
		m_max(0),
		m_current(0),
		m_base(0),
		m_addItem(0),
		m_mulItem(0.0f),
		m_addBuff(0),
		m_mulBuff(0.0f)
	{
	}

	~CStatus() {}

	HRESULT Init() { return S_OK; }
	HRESULT Init(const T& inBase)
	{
		m_base = inBase;
		m_max = inBase;
		m_addItem = 0;
		m_addBuff = 0;

		return S_OK;
	}
	void Uninit()
	{
	}
	void Update() {}

	// ���݂̒l�̕ύX
	void SetCurrent(const T& inNumber)
	{
		if (m_max < inNumber)
		{
			m_current = m_max;
			return;
		}

		m_current = inNumber;
	}

	void AddCurrent(T inNumber) { SetCurrent(m_current + inNumber); }
	void MulCurrent(float inNumber) { SetCurrent(m_current * inNumber); }
	T GetCurrent() { return m_current; }
	T GetMax() { return m_max; }
	T GetBase() { return m_base; }
	T GetAddItem() { return m_addItem; }
	T GetBuffItem() { return m_addBuff; }
	float GetMulItem() { return m_mulItem; }
	float GetMulBuff() { return m_mulBuff; }

	bool MaxCurrentSame() { return m_current >= m_max; }

	void AddItemEffect(T inAdd) { m_max += inAdd; }

private:	// �����o�ϐ�
	T m_max;			// �ő�l
	T m_current;		// ���ݒl
	T m_base;			// ��b�l
	T m_addItem;		// �A�C�e���ɂ����Z�l
	float m_mulItem;	// �A�C�e���ɂ���Z�l

	T m_addBuff;		// ��ԕω��ɂ����Z�l
	float m_mulBuff;	// ��ԕω��ɂ���Z�l
};
#endif
