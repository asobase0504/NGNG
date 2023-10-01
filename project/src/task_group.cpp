//**************************************************************
//
// �}�l�[�W���[
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "task_group.h"
#include "task.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
// Author : Yuda Kaito
//=============================================================================
CTaskGroup::CTaskGroup() :
	m_priorityNumber(0)
{
	m_list.clear();
}

//=============================================================================
// �f�X�g���N�^
// Author : Yuda Kaito
//=============================================================================
CTaskGroup::~CTaskGroup()
{
}

//=============================================================================
// ������
// Author : Yuda Kaito
//=============================================================================
HRESULT CTaskGroup::Init()
{
	return S_OK;
}

//=============================================================================
// �S�Ẵ^�X�N�ɏ������s��
// Author : Yuda Kaito
//=============================================================================
void CTaskGroup::AllProcess(std::function<void(CTask*)> func)
{
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		PriorityProcess(i, func);
	}
}

//=============================================================================
// �w�肳�ꂽpriority�ɂ���^�X�N�S�Ă̏������s��
// Author : Yuda Kaito
//=============================================================================
void CTaskGroup::PriorityProcess(int cnt, std::function<void(CTask*)> func)
{
	if (m_list.count(cnt) == 0)
	{
		return;
	}

	int taskCnt = 0;

	CTask* now = m_list.at(cnt).top;

	while (now != nullptr)
	{
		CTask* next = now->GetNext();

		func(now);
		taskCnt++;

		now = next;
	}

	CDebugProc::Print("Priority %d : %d\n",cnt, taskCnt);
}

//=============================================================================
// �I��
// Author : Yuda Kaito
//=============================================================================
void CTaskGroup::Uninit()
{
	AllProcess([](CTask* task)
	{
		task->Uninit();
		task->Release();
	});

	DeleteTask();	// �^�X�N���X�g�̍폜
}

//=============================================================================
// �X�V
// Author : Yuda Kaito
//=============================================================================
void CTaskGroup::Update()
{
	AllProcess([](CTask* task)
	{
		if (!task->IsDeleted())
		{
			if (task->NeedUpdate())
			{
				task->Update();
			}
		}
	});

	DeleteTask();	// �^�X�N���X�g�̍폜
}

//=============================================================================
// �`��
// Author : Yuda Kaito
//=============================================================================
void CTaskGroup::Draw()
{
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		if (m_list.count(i) == 0)
		{
			continue;
		}

		// ��ʃN���A(Z�o�b�t�@�̃N���A)
		CRenderer::GetInstance()->GetDevice()->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

		{
			CTask* now = m_list.at(i).top;

			while (now != nullptr)
			{
				CTask* next = now->GetNext();
				if (!now->IsDeleted())
				{
					now->Draw();
				}
				now = next;
			}
		}
	}
}

//=============================================================================
// �������Ă���^�X�N�̔j��
// Author : Yuda Kaito
//=============================================================================
void CTaskGroup::AllRelease()
{
	AllProcess([](CTask* task)
	{
		if (!task->IsProtect())
		{
			task->Release();
		}
	});

	DeleteTask();	// �^�X�N���X�g�̍폜
}

//=============================================================================
// ��΂Ƀ^�X�N��j��
// Author : Yuda Kaito
//=============================================================================
void CTaskGroup::AbsolutelyRelease()
{
	AllProcess([](CTask* task) {task->Release(); });
}

//=============================================================================
// �w�肵��priority�̃^�X�N��j��
// Author : Yuda Kaito
//=============================================================================
void CTaskGroup::PriorityRelease(const EPriority inPriotity)
{
	if (m_list.count(inPriotity) == 0)
	{
		return;
	}

	CTask* now = m_list.at(inPriotity).top;

	while (now != nullptr)
	{
		if (!now->IsProtect())
		{
			now->Release();
		}
		now = now->GetNext();
	}
}

//=============================================================================
// ���X�g�̍Ō�Ƀ^�X�N������
// Author : Yuda Kaito
//=============================================================================
void CTaskGroup::SetPushCurrent(CTask * inTask, int inPriority)
{
	if (m_list.count(inPriority) == 0)
	{
		SList inList;
		inList.top = nullptr;
		inList.current = nullptr;
		m_list.insert(std::make_pair(inPriority, inList));

		if (m_priorityNumber < inPriority)
		{
			m_priorityNumber = inPriority;
		}
	}

	SList* list = &m_list.at(inPriority);

	if (list->current == nullptr && list->top == nullptr)
	{
		list->top = inTask;
		list->current = inTask;
	}
	else
	{
		CTask* current = list->current;		// �O�񖖔�
		list->current = inTask;				// �V�K����
		list->current->SetPrev(current);	// �V�K�����̑O�ɑO�񖖔���ݒ�
		current->SetNext(list->current);	// �O�񖖔��̌�ɐV�K������ݒ�
	}
}

//=============================================================================
// ���X�g�̍ŏ��Ƀ^�X�N������
// Author : Yuda Kaito
//=============================================================================
void CTaskGroup::SetPushTop(CTask * inTask, int inPriority)
{
	if (m_list.count(inPriority) == 0)
	{
		SList inList;
		m_list.insert(std::make_pair(inPriority, inList));
		m_list.at(inPriority).top = nullptr;
		m_list.at(inPriority).current = nullptr;

		if (m_priorityNumber < inPriority)
		{
			m_priorityNumber = inPriority;
		}
	}

	if (m_list.at(inPriority).current == nullptr && m_list.at(inPriority).top == nullptr)
	{
		m_list.at(inPriority).top = inTask;
		m_list.at(inPriority).current = inTask;
	}
	else
	{
		CTask* top = m_list.at(inPriority).top;		// �O��擪
		m_list.at(inPriority).top = inTask;			// �V�K�擪
		m_list.at(inPriority).top->SetNext(top);	// �V�K�擪�̎��ɑO��擪��ݒ�
		top->SetPrev(m_list.at(inPriority).top);	// �V�K�擪�̌�ɐV�K�擪��ݒ�
	}
}

//=============================================================================
// �Q�Ƃ����^�X�N�̎��Ƀ^�X�N������
// Author : Yuda Kaito
//=============================================================================
void CTaskGroup::SetNextTask(CTask* inReference, CTask* inTask)
{
	if (inReference == nullptr)
	{
		SetPushCurrent(inTask, 0);
		return;
	}

	CTask* currentNext = inReference->GetNext();	// next�̕ۑ�

	if (currentNext != nullptr)
	{
		inTask->SetNext(currentNext);
		inTask->SetPrev(inReference);
		inReference->SetNext(inTask);
		currentNext->SetPrev(inTask);
	}
	else
	{
		m_list.at((int)inReference->GetPriority()).current = inTask;
		inTask->SetNext(nullptr);
		inTask->SetPrev(inReference);
		inReference->SetNext(inTask);
	}
}

//=============================================================================
// �Q�Ƃ����^�X�N�̑O�Ƀ^�X�N������
// Author : Yuda Kaito
//=============================================================================
void CTaskGroup::SetPrevTask(CTask* inReference, CTask* inTask)
{
	if (inReference == nullptr)
	{
		SetPushCurrent(inTask);
		return;
	}

	CTask* currentPrev = inReference->GetPrev();	// next�̕ۑ�

	if (currentPrev != nullptr)
	{
		inTask->SetNext(inReference);
		inTask->SetPrev(currentPrev);
		currentPrev->SetNext(inTask);
		inReference->SetPrev(inTask);
	}
	else
	{
		m_list.at((int)inReference->GetPriority()).top = inTask;
		inTask->SetNext(inReference);
		inTask->SetPrev(nullptr);
		inReference->SetPrev(inTask);
	}

}

//=============================================================================
// �^�X�N�̖������Ƃ̌���(Top�����猟�����Č��������擪��Ԃ�)
// Author : Yuda Kaito
//=============================================================================
CTask * CTaskGroup::SearchRoleTop(int inRole, int inPriority)
{
	if (m_list.count(inPriority) == 0)
	{
		// ������̃��X�g���Ȃ������ꍇ
		assert(false);
		return nullptr;
	}

	CTask* now = m_list.at(inPriority).top;

	while (now != nullptr)
	{
		CTask* next = now->GetNext();
		if (now->GetRole() == inRole)
		{
			return now;
		}
		now = next;
	}
	return nullptr;
}

//=============================================================================
// �^�X�N�̖������Ƃ̌���(Current�����猟�����Č��������擪��Ԃ�)
// Author : Yuda Kaito
//=============================================================================
CTask * CTaskGroup::SearchRoleCurrent(int inRole, int inPriority)
{
	if (m_list.count(inPriority) == 0)
	{
		// ������̃��X�g���Ȃ������ꍇ
		assert(false);
		return nullptr;
	}

	CTask* now = m_list.at(inPriority).current;

	while (now != nullptr)
	{
		CTask* prev = now->GetPrev();
		if (now->GetRole() == inRole)
		{
			return now;
		}
		now = prev;
	}
	return nullptr;
}

//=============================================================================
// �󂯂Ƃ����^�X�N�Ɠ��������̃^�X�N������(Next�����猟��)
// Author : Yuda Kaito
//=============================================================================
CTask * CTaskGroup::SearchSameRoleNext(CTask* inTask)
{
	CTask* now = inTask->GetNext();
	CTask::ERole role = inTask->GetRole();

	while (now != nullptr)
	{
		CTask* next = now->GetNext();
		if (now->GetRole() == role)
		{
			return now;
		}
		now = next;
	}
	return nullptr;
}

//=============================================================================
// �󂯂Ƃ����^�X�N�Ɠ��������̃^�X�N������(Prev�����猟��)
// Author : Yuda Kaito
//=============================================================================
CTask * CTaskGroup::SearchSameRolePrev(CTask * inTask)
{
	CTask* now = inTask;
	CTask::ERole role = inTask->GetRole();

	while (now != nullptr)
	{
		CTask* prev = now->GetPrev();
		if (now->GetRole() == role)
		{
			return now;
		}
		now = prev;
	}
	return nullptr;
}

//=============================================================================
// �|�[�Y���ɍX�V���~�߂�object�̍X�V���~�߂�
// Author : Yuda Kaito
//=============================================================================
void CTaskGroup::Pause(bool isPause)
{
	if (isPause)
	{
		AllProcess([](CTask* task) { task->PauseOn(); });
	}
	else
	{
		AllProcess([](CTask* task) { task->PauseOff(); });
	}
}

//=============================================================================
// �^�X�N�̍폜
// Author : Yuda Kaito
//=============================================================================
void CTaskGroup::DeleteTask()
{
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		// �폜
		auto Delete = [i, this](CTask* tack)
		{
			CTask* next = tack->GetNext();
			CTask* prev = tack->GetPrev();

			if (!tack->IsDeleted())
			{
				return;
			}

			// �O��̏�Ԃ��擾
			bool isNextNullptr = (next == nullptr);
			bool isPrevNullptr = (prev == nullptr);

			if (!isNextNullptr && !isPrevNullptr)
			{ // �O��Ƀ^�X�N�������Ă���ꍇ
				next->SetPrev(prev);
				prev->SetNext(next);
			}
			else if (!isNextNullptr && isPrevNullptr)
			{ // ��̂݃^�X�N�������Ă���ꍇ
				m_list.at(i).top = next;
				next->SetPrev(nullptr);
			}
			else if (isNextNullptr && !isPrevNullptr)
			{ // �O�̂݃^�X�N�������Ă���ꍇ
				m_list.at(i).current = prev;
				prev->SetNext(nullptr);
			}
			else
			{ // �O��Ƀ^�X�N�������Ă��Ȃ��ꍇ
				m_list.at(i).current = nullptr;
				m_list.at(i).top = nullptr;
				m_list.erase(i);
			}

			tack->Uninit();	// �I��
			delete tack;	// �폜
		};

		// priority�̑S�Ă�Tack�Ɉ����̊֐����s��
		PriorityProcess(i, Delete);
	}
}
