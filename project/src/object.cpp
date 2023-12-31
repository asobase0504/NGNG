//**************************************************************
//
// オブジェクト
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "object.h"
#include "application.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CObject::CObject(CTaskGroup::EPriority inPriority, CTaskGroup::EPushMethod inMethod) :
	CTask(inPriority, inMethod),
	m_pos(0.0f, 0.0f, 0.0f),			// 位置
	m_posOld(0.0f, 0.0f, 0.0f),			// 過去の位置
	m_move(0.0f, 0.0f, 0.0f),			// 移動量
	m_rot(0.0f, 0.0f, 0.0f),			// 向き
	m_moveRot(0.0f, 0.0f, 0.0f),		// 回転量
	m_size(0.0f, 0.0f, 0.0f),			// 大きさ
	m_color(1.0f, 1.0f, 1.0f,1.0f),		// 色
	m_type(NONE),
	m_TimeTarget(120),
	tex0(nullptr),
	m_mtxWorldParent(nullptr),
	m_isDisplay(true)
{
	SetRole(ROLE_OBJECT);
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CObject::~CObject()
{
}

HRESULT CObject::Init()
{
	extern LPD3DXEFFECT pEffect;	// シェーダー

	// これさぁ・・・やっぱ用途ごとの名前じゃないほうが良かったんじゃ？
	// ハンドルの初期化
	m_hTechnique = pEffect->GetTechniqueByName("Diffuse");			// エフェクト
	m_hTexture = pEffect->GetParameterByName(NULL, "Tex");			// テクスチャ
	m_hvLightDir = pEffect->GetParameterByName(NULL, "vLightDir");	// ライトの方向
	m_hvDiffuse = pEffect->GetParameterByName(NULL, "vDiffuse");	// 頂点カラー
	m_hvAmbient = pEffect->GetParameterByName(NULL, "vAmbient");	// 頂点カラー
	m_hWorld = pEffect->GetParameterByName(NULL, "mWorld");			// ワールド行列
	m_hProj = pEffect->GetParameterByName(NULL, "mProj");			// プロジェクション行列
	m_hView = pEffect->GetParameterByName(NULL, "mView");			// ビュー行列
	m_hTime = pEffect->GetParameterByName(NULL, "Test");			// 時間
	m_hTimeTarget = pEffect->GetParameterByName(NULL, "TimeTarget");// 目標時間
	m_hSize = pEffect->GetParameterByName(NULL, "mSize");		// サイズ設定
	m_hRot = pEffect->GetParameterByName(NULL, "mRot");
	m_hTrans = pEffect->GetParameterByName(NULL, "mTrans");
	m_hParent = pEffect->GetParameterByName(NULL, "mParent");
	m_hScale = pEffect->GetParameterByName(NULL, "mScale");
	m_hCameraVec = pEffect->GetParameterByName(NULL, "vEyeVec");
	m_hvEyePos = pEffect->GetParameterByName(NULL, "mEyePos");
	m_hMtxNum = pEffect->GetParameterByName(NULL, "iMtxNum");
	m_hBoneStack = pEffect->GetParameterByName(NULL, "mBoneStack");

	m_TimeCnt = m_TimeTarget;

	m_shaderIndex = 0;
	
	return S_OK;
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CObject::Update()
{
	m_posOld = m_pos;

	// 移動
	AddPos(GetMove());
	AddRot(GetMoveRot());

	m_mtxWorld;
}

//--------------------------------------------------------------
// 指定された種別を探す
//--------------------------------------------------------------
CObject* CObject::SearchType(EType inType, int inPriority)
{
	CTaskGroup* taskGroup = CApplication::GetInstance()->GetTaskGroup();

	// 指定したpriority中にある先頭CObjectを取得
	CObject* now = (CObject*)taskGroup->SearchRoleTop(CTask::ERole::ROLE_OBJECT, inPriority);

	while (now != nullptr)
	{
		CObject* next = (CObject*)taskGroup->SearchSameRoleNext(now);	// nowから次のCObjectを探す。
		if (now->GetType() == inType)
		{// 予定したタイプかチェック
			return now;	// 合っていたら返す。
		}
		now = next;
	}
	return nullptr;
}

//--------------------------------------------------------------
// 自身と同じ種別のobjectを探す
//--------------------------------------------------------------
CObject* CObject::NextSameType()
{
	CTaskGroup* taskGroup = CApplication::GetInstance()->GetTaskGroup();
	CObject* now = (CObject*)taskGroup->SearchSameRoleNext(this);
	EType type = this->GetType();

	while (now != nullptr)
	{
		CObject* next = (CObject*)taskGroup->SearchSameRoleNext(now);
		if (now->GetType() == type)
		{
			return now;
		}
		now = next;
	}
	return nullptr;
}

//--------------------------------------------------------------
// 一つタイプに処理をかける
//--------------------------------------------------------------
void CObject::TypeAllFunc(CObject::EType inType, CTaskGroup::EPriority inPriority, std::function<void(CObject*)> inFunc)
{
	// 最初に見つけた指定したタイプのobjectを持ってくる
	CObject* now = SearchType(inType, inPriority);

	while (now != nullptr)
	{
		CObject* next = now->NextSameType();	// 同じタイプのobjectを持ってくる

		if (now != nullptr)
		{
			inFunc(now);
		}

		now = next;
	}
}

//--------------------------------------------------------------
// 大きさの乗算
//--------------------------------------------------------------
void CObject::MulSize(const D3DXVECTOR3& inRatio)
{
	D3DXVECTOR3 size;
	size.x = m_size.x * inRatio.x;
	size.y = m_size.y * inRatio.y;
	size.z = m_size.z * inRatio.z;
	SetSize(size);
}
