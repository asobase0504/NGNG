//**************************************************************
//
// ステータス
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _STATUS_H_			// このマクロ定義がされてなかったら
#define _STATUS_H_			// 二重インクルード防止のマクロ定義

//--------------------------------------------------------------
// include
//--------------------------------------------------------------
#include "task.h"

//--------------------------------------------------------------
// 前方宣言
//--------------------------------------------------------------
class CCharacter;

//==============================================================
// ステータス
//==============================================================
template <class T>
class CStatus
{
public:
	// コンストラクタとデストラクタ
	CStatus() :
		m_max(0),
		m_current(0),
		m_base(0),
		m_addItem(0),
		m_mulItem(1.0f),
		m_addBuff(0),
		m_mulBuff(1.0f),
		m_isMax(false)
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
	void Update() {}

	// 現在の値の変更
	void SetCurrent(const T& inNumber)
	{
		if (m_max < inNumber && m_isMax)
		{
			m_current = m_max;
			return;
		}

		m_current = inNumber;
	}

	void AddCurrent(T inNumber) { SetCurrent(m_current + inNumber); }
	void MulCurrent(float inNumber) { SetCurrent(m_current * inNumber); }
	T GetCurrent() { return m_current; }
	T GetBase() { return m_base; }
	T GetAddItem() { return m_addItem; }
	T GetBuffItem() { return m_addBuff; }
	T CalStatus() { return m_current = ((m_base + m_addBuff + m_addItem) * (T)(m_mulBuff * m_mulItem)); }

	float GetMulItem() { return m_mulItem; }
	float GetMulBuff() { return m_mulBuff; }

	// 現在の値が上限を越しているか否か
	bool MaxCurrentSame() { return m_isMax ? m_current >= m_max : false; }

	void AddMax(T inAdd) { m_max += inAdd; CalStatus(); }
	void AddBaseState(T inAdd) { m_base += inAdd; CalStatus(); }
	void AddItemEffect(T inAdd) { m_addItem += inAdd; CalStatus(); }
	void ResetItemEffect(T inAdd) { m_addItem = 0; CalStatus(); }
	void AddBuffEffect(T inAdd) { m_addBuff += inAdd; CalStatus(); }
	void ResetBuffEffect(T inAdd) { m_addBuff = 0; CalStatus(); }

	// 最大値
	void ResetMax(T inAdd) { m_max = 0;}
	T GetMax() { return m_max; }
	void AttachMax() { m_isMax = true; }

private:	// メンバ変数
	T m_max;			// 最大値
	T m_current;		// 現在値
	T m_base;			// 基礎値
	T m_addItem;		// アイテムによる加算値
	float m_mulItem;	// アイテムによる乗算値

	T m_addBuff;		// 状態変化による加算値
	float m_mulBuff;	// 状態変化による乗算値

	bool m_isMax;
};
#endif
