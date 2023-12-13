//==================================================
// procedure.h
// Author: ���c�喲
//==================================================
#ifndef _PROCEDURE_3D_H_
#define _PROCEDURE_3D_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object2d.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CNumber3D;

//**************************************************
// �N���X
//**************************************************
class CProcedure3D : public CObject
{
private:
	static const int NUM_DIGIT = 3;
public:
	// ������
	enum EAlign
	{
		LEFT,	// ������
		RIGHT,	// �E����
		CENTER,	// ��������

	};

public:
	explicit CProcedure3D();
	~CProcedure3D() override;

	HRESULT Init() override;
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

	void SetDisplay(bool isDisplay) override;

	static CProcedure3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const int inNumber);

	void SetAlign(EAlign inAlign) { m_align = inAlign; SetPos(m_pos); }

private:
	void CalDigit();
private:
	// Number�^�̔z��
	std::list<CNumber3D*> m_pNumber;
	// ����
	int m_number;
	int m_digit;
	float m_interval;

	EAlign m_align;	// ������

	D3DXMATRIX m_mtxTrans;	// �ʒu�s��
};

#endif // _TIMER_H_

