//==================================================
// procedure.h
// Author: 梶田大夢
//==================================================
#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

//**************************************************
// インクルード
//**************************************************
#include "object2d.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************
class CNumber;

//**************************************************
// クラス
//**************************************************
class CProcedure : public CObject
{
private:
	static const int NUM_DIGIT = 3;
public:
	// 揃え方
	enum EAlign
	{
		LEFT,	// 左揃え
		RIGHT,	// 右揃え
		CENTER,	// 中央揃え
	};

public:
	explicit CProcedure();
	~CProcedure() override;

	HRESULT Init() override;
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, const int digit);
	void Update() override;
	void Draw() override {}

	void SetPos(const D3DXVECTOR3& inPos) override;
	void AddPos(const D3DXVECTOR3& inPos) { SetPos(inPos + GetPos()); }

	void SetColor(const D3DXCOLOR& inColor);
	void AddColor(const D3DXCOLOR& inColor);

	void SetSize(const D3DXVECTOR3& inSize);
	void AddSize(const D3DXVECTOR3& inSize);

	void SetNumber(int inNumber);
	void SetNumber(const int* inNumber);
	void AddNumber(int inNumber) { SetNumber(m_number + inNumber); }
	int GetNumber() { return m_number; }

	void SetDisplay(bool isDisplay) override;

	static CProcedure* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const int inNumber);

	void SetAlign(EAlign inAlign) { m_align = inAlign; SetPos(m_pos); }

private:
	void CalDigit();
private:
	// Number型の配列
	std::list<CNumber*> m_numberObj;

	const int* m_pNumber;
	int m_number;

	// 桁数
	int m_digit;
	float m_interval;

	EAlign m_align;	// 揃え方
};

#endif // _TIMER_H_

