//**************************************************************
//
// 根幹クラス
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "task.h"
#include "application.h"
#include "task_group.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CTask::CTask(CTaskGroup::EPriority inPriority, CTaskGroup::EPushMethod inMethod, CTask* inTask) :
	m_prev(nullptr),
	m_next(nullptr),
	m_isDeleted(false),
	m_isProtect(false),
	m_isUpdate(true),
	m_isPouseUpdate(false),
	m_parentEnd(nullptr)
{
	m_childrensEnd.clear();
	m_priority = inPriority;

	CTaskGroup* taskGroup = CApplication::GetInstance()->GetTaskGroup();

	// タスクグループに自身を登録する
	switch (inMethod)
	{
	case CTaskGroup::PUSH_CURRENT:
		taskGroup->SetPushCurrent(this, inPriority);
		break;
	case CTaskGroup::PUSH_TOP:
		taskGroup->SetPushTop(this, inPriority);
		break;
	case CTaskGroup::PUSH_NEXT:
		taskGroup->SetNextTask(inTask, this);
		break;
	case CTaskGroup::PUSH_PREV:
		taskGroup->SetPrevTask(inTask, this);
		break;
	default:
		assert(false);
		break;
	}
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CTask::~CTask()
{
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CTask::Uninit()
{
	Release();

	if (m_parentEnd != nullptr)
	{
		m_parentEnd->m_childrensEnd.remove(this);
		m_parentEnd = nullptr;
	}

	if (!m_childrensEnd.empty())
	{
		std::list<CTask*>::iterator it;
		for (it = m_childrensEnd.begin(); !m_childrensEnd.empty(); )
		{
			(*it)->Uninit();
			it = m_childrensEnd.begin();
		}
	}
	m_childrensEnd.clear();
}
