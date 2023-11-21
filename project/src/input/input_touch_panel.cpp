//=============================================================================
//
// 入力処理 [input_touch_panel.cpp]
// Author1 : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "input_touch_panel.h"

//*************************************************************************************
//コンストラクタ
//*************************************************************************************
CInputTouchPanel::CInputTouchPanel()
{
	ZeroMemory(m_TouchPanel,sizeof(m_TouchPanel));
	m_ScreenSize = {};
}

//*************************************************************************************
//デストラクタ
//*************************************************************************************
CInputTouchPanel::~CInputTouchPanel()
{
}

//*************************************************************************************
//更新
//*************************************************************************************
void CInputTouchPanel::Update()
{
	for (int i = 0; i < MAX_TOUCH_PANEL; i++)
	{//全更新
		if (!m_TouchPanel[i].bUse)
		{//使用状態になったら
			continue;
		}


		if (!m_TouchPanel[i].bFirstTrigger && m_TouchPanel[i].bTrigger)
		{//二段階目トリガーの喪失
			m_TouchPanel[i].bTrigger = false;
		}

		if (m_TouchPanel[i].bFirstTrigger && !m_TouchPanel[i].bTrigger)
		{//一段階目トリガーの喪失
			m_TouchPanel[i].bFirstTrigger = false;
			m_TouchPanel[i].bTrigger = true;
		}
	}
}

//*************************************************************************************
//プレス処理
//*************************************************************************************
bool CInputTouchPanel::GetPress(int nNum)
{
	return m_TouchPanel[nNum].bUse;
}

//*************************************************************************************
//トリガー処理
//*************************************************************************************
bool CInputTouchPanel::GetTrigger(int nNum)
{
	//NULLチェック
	if (!m_TouchPanel[nNum].bUse)
	{
		return false;
	}

	//トリガーチェック
	if (m_TouchPanel[nNum].bTrigger)
	{
		return true;
	}
	return false;
}

//*************************************************************************************
//タッチPosのGet
//*************************************************************************************
D3DXVECTOR3 CInputTouchPanel::GetTouchPos(int nNum)
{
	return m_TouchPanel[nNum].Pos;
}

//*************************************************************************************
//タッチVecのGet
//*************************************************************************************
D3DXVECTOR3 CInputTouchPanel::GetTouchVec(int nNum)
{
	return m_TouchPanel[nNum].Vec;
}

//*************************************************************************************
//データの設定
//*************************************************************************************
void CInputTouchPanel::SetTouchData(TOUCHINPUT *pTouchData, int nCntData)
{
	//データの個数
	int nCntMax = nCntData;

	//保存可能数を超えていないか
	if (nCntMax >= MAX_TOUCH_PANEL)
	{
		nCntMax = MAX_TOUCH_PANEL - 1;
	}

	//データの保存はない
	if (nCntMax < 0)
	{
		return;
	}

	//新規登録の有無
	bool bNewRegistration = false;

	//データの更新
	for (int i = 0; i < MAX_TOUCH_PANEL; i++)
	{
		//Useチェック
		if (m_TouchPanel[i].bUse == false)
		{
			continue;
		}

		//タッチIDの検知
		if (m_TouchPanel[i].TouchData.dwID != pTouchData[nCntMax].dwID)
		{
			continue;
		}

		//タッチフラグ検知
		if (pTouchData[nCntMax].dwFlags & TOUCHEVENTF_UP)
		{//タッチ情報のロスト
			m_TouchPanel[i].bUse = false;
			//新規登録は必要ない
			bNewRegistration = true;
			break;
		}
		else if (pTouchData[nCntMax].dwFlags & TOUCHEVENTF_MOVE)
		{//フリップ情報の設定

			//一個前の位置の保存
			m_TouchPanel[i].OldPos = m_TouchPanel[i].Pos;

			//現在の位置を保存
			m_TouchPanel[i].Pos.x = RateCalculation((float)pTouchData[nCntMax].x / 100.0f, m_ScreenSize.x, SM_CXSCREEN);
			m_TouchPanel[i].Pos.y = RateCalculation((float)pTouchData[nCntMax].y / 100.0f, m_ScreenSize.y, SM_CYSCREEN);

			//2つのベクトルを足して合成ベクトルを作成します
			D3DXVECTOR3 combinedVector = m_TouchPanel[i].OldPos + m_TouchPanel[i].Pos;

			//合成ベクトルを正規化します
			D3DXVec3Normalize(&combinedVector, &combinedVector);

			//合成ベクトルの保存
			m_TouchPanel[i].Vec = combinedVector;

			//新規登録は必要ない
			bNewRegistration = true;
			break;
		}
		//フラグのロスト
		m_TouchPanel[i].bUse = false;
	}

	//データの新規保存
	for (int i = 0; i < MAX_TOUCH_PANEL; i++)
	{
		//新規登録の有無
		if (bNewRegistration)
		{
			break;
		}

		//タッチハンドルのnullチェック
		if (m_TouchPanel[i].bUse == true)
		{
			continue;
		}

		//使用状態にする
		m_TouchPanel[i].bUse = true;
		//トリガーの起動
		m_TouchPanel[i].bTrigger = false;
		m_TouchPanel[i].bFirstTrigger = true;
		//データの保存
		m_TouchPanel[i].TouchData = pTouchData[nCntMax];
		//現在の位置を保存
		m_TouchPanel[i].Pos.x = RateCalculation((float)pTouchData[nCntMax].x / 100.0f, m_ScreenSize.x, SM_CXSCREEN);
		m_TouchPanel[i].Pos.y = RateCalculation((float)pTouchData[nCntMax].y / 100.0f, m_ScreenSize.y, SM_CYSCREEN);
		//一個前の位置の登録
		m_TouchPanel[i].OldPos = m_TouchPanel[i].Pos;
		//ベクトル保存
		m_TouchPanel[i].Vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//登録完了
		break;
	}

	//次のデータの保存
	SetTouchData(pTouchData, nCntMax -1);
}

//*************************************************************************************
//割合計算
//*************************************************************************************
float CInputTouchPanel::RateCalculation(float fMax, float fWnMax, int nbet)
{
	//画面サイズ
	int nScreenMax = GetSystemMetrics(nbet);

	//割合計算
	float fRate = (float)(fMax / nScreenMax);

	//結果
	float fResult = fWnMax * fRate;

	return fResult;
}
