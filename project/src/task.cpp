//**************************************************************
//
// �����N���X
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
// �R���X�g���N�^
//--------------------------------------------------------------
CTask::CTask(CTaskGroup::EPriority inPriority, CTaskGroup::EPushMethod inMethod, CTask* inTask) :
	m_prev(nullptr),
	m_next(nullptr),
	m_isDeleted(false),
	m_isProtect(false),
	m_isUpdate(true),
	m_isPouseUpdate(false)
{
	m_priority = inPriority;

	CTaskGroup* taskGroup = CApplication::GetInstance()->GetTaskGroup();

	// �^�X�N�O���[�v�Ɏ��g��o�^����
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
// �f�X�g���N�^
//--------------------------------------------------------------
CTask::~CTask()
{
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CTask::Uninit()
{
	Release();
}
