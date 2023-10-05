//**************************************************************
//
// �I�u�W�F�N�g
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "object.h"
#include "application.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CObject::CObject(CTaskGroup::EPriority inPriority, CTaskGroup::EPushMethod inMethod) :
	CTask(inPriority, inMethod),
	m_pos(0.0f, 0.0f, 0.0f),			// �ʒu
	m_posOld(0.0f, 0.0f, 0.0f),			// �ߋ��̈ʒu
	m_move(0.0f, 0.0f, 0.0f),			// �ړ���
	m_rot(0.0f, 0.0f, 0.0f),			// ����
	m_moveRot(0.0f, 0.0f, 0.0f),		// ��]��
	m_size(0.0f, 0.0f, 0.0f),			// �傫��
	m_color(1.0f, 1.0f, 1.0f,1.0f),		// �F
	m_type(NONE)
{
	SetRole(ROLE_OBJECT);
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CObject::~CObject()
{
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CObject::Update()
{
	m_posOld = m_pos;

	// �ړ�
	AddPos(GetMove());
	AddRot(GetMoveRot());
}

//--------------------------------------------------------------
// �w�肳�ꂽ��ʂ�T��
//--------------------------------------------------------------
CObject* CObject::SearchType(EType inType, int inPriority)
{
	CTaskGroup* taskGroup = CApplication::GetInstance()->GetTaskGroup();

	// �w�肵��priority���ɂ���擪CObject���擾
	CObject* now = (CObject*)taskGroup->SearchRoleTop(CTask::ERole::ROLE_OBJECT, inPriority);

	while (now != nullptr)
	{
		CObject* next = (CObject*)taskGroup->SearchSameRoleNext(now);	// now���玟��CObject��T���B
		if (now->GetType() == inType)
		{// �\�肵���^�C�v���`�F�b�N
			return now;	// �����Ă�����Ԃ��B
		}
		now = next;
	}
	return nullptr;
}

//--------------------------------------------------------------
// ���g�Ɠ�����ʂ�object��T��
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
// ��^�C�v�ɏ�����������
//--------------------------------------------------------------
void CObject::TypeAllFunc(CObject::EType inType, CTaskGroup::EPriority inPriority, std::function<void(CObject*)> inFunc)
{
	// �ŏ��Ɍ������w�肵���^�C�v��object�������Ă���
	CObject* now = SearchType(inType, inPriority);

	while (now != nullptr)
	{
		CObject* next = now->NextSameType();	// �����^�C�v��object�������Ă���

		if (now != nullptr)
		{
			inFunc(now);
		}

		now = next;
	}
}

//--------------------------------------------------------------
// �傫���̏�Z
//--------------------------------------------------------------
void CObject::MulSize(const D3DXVECTOR3& inRatio)
{
	D3DXVECTOR3 size;
	size.x = m_size.x * inRatio.x;
	size.y = m_size.y * inRatio.y;
	size.z = m_size.z * inRatio.z;
	SetSize(size);
}
