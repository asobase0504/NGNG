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

	// 現在の値の変更
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

private:	// メンバ変数
	T m_max;			// 最大値
	T m_current;		// 現在値
	T m_base;			// 基礎値
	T m_addItem;		// アイテムによる加算値
	float m_mulItem;	// アイテムによる乗算値

	T m_addBuff;		// 状態変化による加算値
	float m_mulBuff;	// 状態変化による乗算値
};
#endif
