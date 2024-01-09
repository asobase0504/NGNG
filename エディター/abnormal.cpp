//**************************************************************
//
// item_data
// Author: Buriya Kota
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "abnormal.h"
#include "abnormal_data_base.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CAbnormal::CAbnormal(CTaskGroup::EPriority list) :
	m_getFunc(nullptr),
	m_lostFunc(nullptr),
	m_allwayFunc(nullptr)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CAbnormal::~CAbnormal()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CAbnormal::Init()
{
	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CAbnormal::Uninit()
{
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CAbnormal::Update()
{
	m_effectTime--;
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CAbnormal* CAbnormal::Create(CAbnormalDataBase::EAbnormalType inId)
{
	CAbnormal* pAbnormalData = nullptr;
	pAbnormalData = new CAbnormal;

	if (pAbnormalData != nullptr)
	{
		pAbnormalData->Init();
	}

	return pAbnormalData;
}
