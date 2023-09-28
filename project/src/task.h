//=============================================================================
//
// �����N���X
// Author : Yuda Kaito
//
//=============================================================================
#ifndef _TASK_H_			// ���̃}�N����`������ĂȂ�������
#define _TASK_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include <Windows.h>
#include "task_group.h"

//=============================================================================
// �^�X�N�N���X
//=============================================================================
class CTask
{
public:
	// �^�C�v
	enum ERole
	{
		ROLE_NONE = 0,
		ROLE_OBJECT,
		ROLE_MODE,
		ROLE_CAMERA,
		ROLE_LIGHT,
		ROLE_STAGE,
		ROLE_MAX
	};

public:
	CTask(CTaskGroup::EPriority inPriority = CTaskGroup::EPriority::LEVEL_3D_1, CTaskGroup::EPushMethod inMethod = CTaskGroup::EPushMethod::PUSH_CURRENT, CTask* inTask = nullptr);
	virtual ~CTask();

	virtual HRESULT Init() = 0;
	virtual void Uninit();
	virtual void Update() {}
	virtual void Draw() {}

	void Release() { m_isDeleted = true; }

	/* ���X�g�\�� */
	void SetPrev(CTask* inTask) { m_prev = inTask; }
	CTask* GetPrev() { return m_prev; }
	void SetNext(CTask* inTask) { m_next = inTask; }
	CTask* GetNext() { return m_next; }

	/* �j���\�� */
	bool IsDeleted() { return m_isDeleted; }

	/* �j����ی삷�� */
	void AttachProtect() { m_isProtect = true; }
	bool IsProtect() { return m_isProtect; }

	/* ���� */
	void SetRole(const ERole& inJobRole) { m_role = inJobRole; }
	const ERole& GetRole() const { return m_role; }

	/* �D�揇�� */
	CTaskGroup::EPriority GetPriority() { return m_priority; }

	/* �X�V����K�v�����邩 */
	bool NeedUpdate() { return m_isUpdate; }

	/* �|�[�Y */
	void SetPouseUpdate(bool isUpdate) { m_isPouseUpdate = isUpdate; }	// �|�[�Y���ɍX�V���s�������߂�
	void PauseOn() { m_isUpdate = m_isPouseUpdate; }						// �X�V���s�����s��Ȃ����|�[�Y��ԂŔ��f
	void PauseOff() { if (!m_isPouseUpdate) { m_isUpdate = true; } }	// �|�[�Y��ԂŎ~�܂��Ă����X�V���ғ�������

private:
	CTaskGroup::EPriority m_priority;

	CTask* m_prev;		// �O�̃^�X�N
	CTask* m_next;		// ��̃^�X�N

	// �e�q�֌W
	CTask* m_pearent;	// �e
	std::list<CTask*> m_childrens;	// �q

	bool m_isDeleted;	// �j���\��
	bool m_isProtect;	// �S�̔j������ی삷��

	ERole m_role;		// ����

	bool m_isUpdate;		// �X�V���s����
	bool m_isPouseUpdate;	// �|�[�Y���ɍX�V�������s����
};
#endif
