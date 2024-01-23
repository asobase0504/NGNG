//**************************************************************
//
// �}�l�[�W���[
// Author : �l�c����
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "task_group.h"
#include "objectX_group.h"
#include "mode_fade.h"

#include "skill_data_base.h"
#include "enemy_data_base.h"
#include "item_data_base.h"
#include "abnormal_data_base.h"

/* �O���Ǎ��� */
#include "font.h"
#include "texture.h"

/* �V�[�����[�h */
#include "title.h"
#include "game.h"
#include "character_select.h"
#include "debug_mode.h"

#include "model_skin_group.h"

//==============================================================
// �ÓI�����o�[�ϐ��̏�����
//==============================================================
CApplication* CApplication::m_pApplication = nullptr;
const D3DXVECTOR3 CApplication::CENTER_POS = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f);

//--------------------------------------------------------------
// �V���O���g���ł̃C���X�^���X�̎擾
//--------------------------------------------------------------
CApplication * CApplication::GetInstance()
{
	return m_pApplication != nullptr ? m_pApplication : m_pApplication = new CApplication;
}

//--------------------------------------------------------------
// �R���X�g���N�g�֐�
//--------------------------------------------------------------
CApplication::CApplication() :
	m_texture(nullptr),
	m_renderer(nullptr),
	m_taskGroup(nullptr),
	m_fade(nullptr),
	m_mode(nullptr),
	m_sound(nullptr)
{
}

//--------------------------------------------------------------
// �f�X�g���N�g�֐�
//--------------------------------------------------------------
CApplication::~CApplication()
{

}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CApplication::Init(HWND hWnd, HINSTANCE hInstance)
{
	// Window���̃|�C���^�ۑ�
	m_window = hWnd;

	// �����O���[�v�̏���������
	m_taskGroup = new CTaskGroup;
	if (FAILED(m_taskGroup->Init()))
	{
		return E_FAIL;
	}

	// �����_���[�̏���������
	m_renderer = CRenderer::GetInstance();
	if (FAILED(m_renderer->Init(hWnd, true)))
	{
		return E_FAIL;
	}

	// ���͏����̏���������
	CInput::Create();
	if (FAILED(CInput::GetKey()->Init(hInstance, hWnd, D3DXVECTOR2(CENTER_POS.x, CENTER_POS.y))))
	{
		return E_FAIL;
	}

	// ���y�����̏���������
	m_sound = new CSound;
	if (FAILED(m_sound->Init(hWnd)))
	{
		return E_FAIL;
	}

	// objectX�̏���������
	m_objectXGroup = new CObjectXGroup;
	m_objectXGroup->LoadAll();

	// Texture�̓Ǎ���
	m_texture = CTexture::GetInstance();
	m_texture->LoadAll();

	m_modeType = CApplication::MODE_TITLE;	//���݂̃��[�h

	m_fade = CModeFade::Create();

	//���[�h�̐ݒ�
	SetMode(m_modeType);

	CSkillDataBase::GetInstance();
	CEnemyDataBase::GetInstance();
	CItemDataBase::GetInstance();

	CFont::Load(CFont::FONT_MYOUTYOU);

	return S_OK;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CApplication::Uninit()
{
	CSkillDataBase::Uninit();
	CEnemyDataBase::Uninit();
	CAbnormalDataBase::Uninit();

	if (m_taskGroup != nullptr)
	{// �I������
		m_taskGroup->Uninit();
		delete m_taskGroup;
		m_taskGroup = nullptr;
	}

	if (m_objectXGroup != nullptr)
	{// �I������
		m_objectXGroup->UnloadAll();
		delete m_objectXGroup;
		m_objectXGroup = nullptr;
	}
	
	if (m_texture != nullptr)
	{// �I������
		m_texture->UnloadAll();
		delete m_texture;
		m_texture = nullptr;
	}

	if (m_renderer != nullptr)
	{// �I������

		m_renderer->Uninit();
		delete m_renderer;
		m_renderer = nullptr;
	}

	if (m_sound != nullptr)
	{// �I������

		m_sound->Uninit();
		delete m_sound;
		m_sound = nullptr;
	}

	//���͏����̏I������
	CInput::GetKey()->Uninit();

	CSkinMeshGroup* group = CSkinMeshGroup::GetInstance();
	delete group;
	group = nullptr;
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CApplication::Update()
{
	//���͏����̍X�V����
	CInput::GetKey()->Update();

#ifdef _DEBUG
	static bool ppp = true;
	CDebugProc::Print("�|�[�Y�y F2 �z : %s\n", ppp ? "OFF" : "STOP");
	if (CInput::GetKey()->Trigger(DIK_F2))
	{
		m_taskGroup->Pause(ppp);
		ppp = !ppp;
	}
#endif // _DEBUG

	// ���݂̍őO�ʂ�ۑ�
	HWND activeWindowHandle;
	
	activeWindowHandle = GetForegroundWindow();
	if (m_window != activeWindowHandle && m_isActiveWindowThis)
	{ // �������őO�ɂ��Ȃ��Ȃ�
		m_isActiveWindowThis = false;
	}
	if (m_window == activeWindowHandle && !m_isActiveWindowThis)
	{ // �������őO�Ȃ�
		m_isActiveWindowThis = true;
	}


	m_renderer->Update();
}

//--------------------------------------------------------------
// �`��
//--------------------------------------------------------------
void CApplication::Draw()
{
	m_renderer->Draw();	// �`�揈��
}

//--------------------------------------------------------------
// ���[�h�̐ݒ�
//--------------------------------------------------------------
void CApplication::SetMode(MODE mode)
{
	m_modeType = mode;
	m_taskGroup->AllRelease();

	switch (mode)
	{
	case CApplication::MODE_TITLE:
		m_mode = new CTitle;
		break;
	case CApplication::MODE_GAME:
		m_mode = new CGame;
		break;
	case CApplication::MODE_SELECT:
		m_mode = new CCharacterSelect;
		break;
	case CApplication::MODE_DEBUG:
		m_mode = new CGame;
		//m_mode = new CDebugMode;
	default:
		break;
	}

	// ����������
	if (FAILED(m_mode->Init()))	//��ʃT�C�Y
	{
		//���������������s�����ꍇ
		return;
	}
}
