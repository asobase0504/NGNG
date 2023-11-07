//==================================================
// procedure.h
// Author: ���c�喲
//==================================================
#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object2d.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CNumber;

//**************************************************
// �N���X
//**************************************************
class CProcedure : public CObject
{
private:
	static const int NUM_DIGIT = 3;
public:
public:
	explicit CProcedure();
	~CProcedure() override;

	HRESULT Init() override;
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, const int digit);
	void Uninit() override;
	void Update() override;
	void Draw() override {}

	void SetPos(const D3DXVECTOR3& inPos) override;
	void AddPos(const D3DXVECTOR3& inPos) { SetPos(inPos + GetPos()); }

	void SetColor(const D3DXCOLOR& inColor);
	void AddColor(const D3DXCOLOR& inColor);

	void SetSize(const D3DXVECTOR3& inSize);
	void AddSize(const D3DXVECTOR3& inSize);

	void SetNumber(int inNumber);
	void AddNumber(int inNumber) { SetNumber(m_number + inNumber); }
	int GetNumber() { return m_number; }

	static CProcedure* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const int digit);

private:
	// Number�^�̔z��
	std::vector<CNumber*> m_pNumber;
	// ����
	int m_number;
	int m_digit;
	float m_interval;
};

#endif // _TIMER_H_
