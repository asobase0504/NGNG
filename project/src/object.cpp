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
	m_type(NONE)
{
	SetRole(ROLE_OBJECT);
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CObject::~CObject()
{
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
