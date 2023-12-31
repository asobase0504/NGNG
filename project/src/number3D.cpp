//**************************************************************
//
// NUMBER
// Author:hamada ryuuga
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "number3D.h"
#include "application.h"

//--------------------------------------------------------------
// コンストラクト関数
//--------------------------------------------------------------
CNumber3D::CNumber3D(CTaskGroup::EPriority list) : 
	CObjectPolygon3D(list),
	m_myNumber(0)
{
}

//--------------------------------------------------------------
// デストラクト関数
//--------------------------------------------------------------
CNumber3D::~CNumber3D()
{
}

//--------------------------------------------------------------
// 初期化関数
//--------------------------------------------------------------
HRESULT CNumber3D::Init()
{
	m_myNumber = 0;
	CObjectPolygon3D::Init();
	CObjectPolygon3D::SetTexture("NUMBER");
	SetTex(PositionVec4(0.0f, 0.1f, 0.0f, 1.0f));
	return S_OK;
}

//--------------------------------------------------------------
// 生成関数
//--------------------------------------------------------------
CNumber3D *CNumber3D::Create()
{
	CNumber3D * pObject = nullptr;
	pObject = new CNumber3D;

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

void CNumber3D::AttachIcon(EIconType icon)
{
}
