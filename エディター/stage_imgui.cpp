//**************************************************
//
// Hackathon ( imgui_property.cpp )
// Author  : katsuki mizuki
// Author  : Tanaka Kouta
// Author  : Hamada Ryuga
// Author  : Yuda Kaito
//
//**************************************************

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "stage_imgui.h"
//-----------------------------------------------------------------------------
// imgui
//-----------------------------------------------------------------------------
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"
#include <implot.h>

//-----------------------------------------------------------------------------
// json
//-----------------------------------------------------------------------------
#include <fstream>

//-----------------------------------------------------------------------------
// stage
//-----------------------------------------------------------------------------
#include "game.h"
#include "texture.h"
#include "title.h"
#include "object.h"
#include "player.h"
#include "game.h"
#include "camera.h"
#include "enemy.h"

#include "player.h"
//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
CStageImgui::CStageImgui() :
	m_sliderIntmodel(0),
	m_sliderIntmesh(0)
{
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CStageImgui::~CStageImgui()
{
}

//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------
HWND CStageImgui::Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice)
{
	// ������
	HWND outWnd = CImguiProperty::Init(hWnd, pDevice);

	// �S���f�[�^��������
	m_Pendulum.type = 0;
	m_Pendulum.coefficient = 0.0f;
	m_Pendulum.destRot.x = 0.0f;
	m_Pendulum.destRot.y = 0.0f;
	m_Pendulum.destRot.z = 0.0f;

	// �{�[���f�[�^��������
	m_Ball.rotType = 0;
	m_Ball.radius = 0.0f;
	m_Ball.rotSpeed = 0.0f;

	// �ۑ��f�[�^��������
	m_Wood.coolTime = 0;
	m_Wood.rot = 0.0f;
	m_Wood.rotSpeed = 0.0f;
	m_Wood.move = 0.0f;
	for (int i = 0; i < D3DXyz; i++)
	{
		m_sliderRot3[i] = 0.0f;
		m_sliderNowRot3[i] = 0.0f;
		m_PosVSet[i] = 0.0f;
		m_PosRSet[i] = 0.0f;
		m_posRDest[i] = 10.0f;
		m_posVDest[i] = 0.0f;
		m_fDistance[i] = 1.0f;
	}
	m_posVDest[1] = D3DX_PI;

	m_BossAnimation = 0;
	m_KeySet = 0;
	m_indexModel = 0;
	m_indexNouEnemy = 0;
	return outWnd;
}

//-----------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------
void CStageImgui::Uninit(HWND hWnd, WNDCLASSEX wcex)
{
	CImguiProperty::Uninit(hWnd, wcex);
}

//-----------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------
bool CStageImgui::Update()
{


	CImguiProperty::Update();
	ImguiCreate();
	// �e�L�X�g�\��
	ImGui::Text("FPS  : %.2f", ImGui::GetIO().Framerate);

	CStageImgui::EditMesh();

	//ImGui::SliderFloat3(u8"���b�g", &sliderRot.x, -3.14f, 3.14f);
	//ImGui::Separator();

	ImGui::End();


	return false;

}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CStageImgui::Draw()
{
	CImguiProperty::Draw();
}

//--------------------------------------------------
// EditModel
//--------------------------------------------------
void CStageImgui::EditModel(void)
{
	ImGui::Separator();
}

//--------------------------------------------------
// �^�X�N�o�[�̍X�V
//--------------------------------------------------
void CStageImgui::TaskBarUpdate(void)
{
	if (!ImGui::BeginMenuBar())
	{//�^�X�N�o�[
		return;
	}

	ImGui::EndMenuBar();
}

//--------------------------------------------------
// EditMesh
//--------------------------------------------------
void CStageImgui::EditMesh(void)
{
	static int sliderInt = 10;
	static int AnimationSpeed = 10;
	static float meshSizeFloat[2];
	static float meshMoveFloat;
	static D3DXVECTOR3 meshMovePoptimeFloat;
	static char textmesh[MAX_TEXT] = "";
	static bool Reverse = false;

	int Meshint = 0;

	
}

//--------------------------------------------------
// EditMesh
//--------------------------------------------------
void CStageImgui::EditCamera(void)
{
	

}
//--------------------------------------------------
// �G�l�~�[�̐ݒ�
//--------------------------------------------------
void CStageImgui::EditEnemy()
{
	
}

//--------------------------------------------------
// BOSS
//--------------------------------------------------
void CStageImgui::EditBoss(CBoss* BossEnemy)
{
	
}

//--------------------------------------------------
// Player�̓���
//--------------------------------------------------
void CStageImgui::EditPlayer()
{
	
}

//--------------------------------------------------
// �E�C���h�E�o�͏���
//--------------------------------------------------
void CStageImgui::Imguigold(void)
{
	// �E�C���h�E�̖���
	ImGui::Begin("gold", nullptr, ImGuiWindowFlags_MenuBar);
	ImGui::End();
}

//--------------------------------------------------
// �E�C���h�E�o�͏���
//--------------------------------------------------
void CStageImgui::Imguifilecord(void)
{
	// �E�C���h�E�̖���
	static char textSeve[MAX_TEXT] = "STAGE0";
	ImGui::Begin("gold", nullptr, ImGuiWindowFlags_MenuBar);
	ImGui::InputText(u8"�ۑ����������܂�", textSeve, sizeof(textSeve));

	m_SavefileNeme = textSeve;
	
	ImGui::End();
}

//--------------------------------------------------
// �E�C���h�E�o�͏���
//--------------------------------------------------
void CStageImgui::ImguiEnemy(void)
{
	// �E�C���h�E�̖���
	ImGui::Begin(u8"Enemy", nullptr, ImGuiWindowFlags_MenuBar);
	ImGui::End();
}

//--------------------------------------------------
// �I��ł郂�e��
//--------------------------------------------------
bool CStageImgui::GetAnimati()
{
	return m_Animation;
}

//--------------------------------------------------
// �I��ł郂�e��
//--------------------------------------------------
int CStageImgui::selectModel()
{
	return m_indexBuilding;
}

//--------------------------------------------------
// �E�C���h�E�o�͏���
//--------------------------------------------------
void CStageImgui::ImguiCreate(void)
{
	// �E�C���h�E�̖���
	ImGui::Begin(u8"�����{�^��", nullptr, ImGuiWindowFlags_MenuBar);

	if (ImGui::Button(u8"Mesh����"))
	{// �{�^���������ꂽ
	
	}

	ImGui::End();
}

//--------------------------------------------------
// �E�C���h�E�o�͏���
//--------------------------------------------------
void CStageImgui::ImguiPlarer(void)
{

	ImGui::End();
}

//========================
//�E�B���h�E�����Ă����
//========================
void CStageImgui::ImguiChangenumber(std::string number, int Number)
{


	ImGui::End();
}

//========================
//�E�B���h�E�����Ă����
//========================
void CStageImgui::funcFileSave(HWND hWnd, CStageImgui::DATATYPE Mode)
{
	static OPENFILENAME     ofn;
	static TCHAR            szPath[MAX_PATH];
	static TCHAR            szFile[MAX_PATH];

	if (szPath[0] == TEXT('\0')) {
		GetCurrentDirectory(MAX_PATH, szPath);
	}
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrInitialDir = szPath;	// �����t�H���_�ʒu
		ofn.lpstrFile = szFile;			// �I���t�@�C���i�[
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".json\0.x");
		ofn.lpstrFilter = TEXT("json�t�@�C��(*.json)\0*.json\0X�t�@�C��(*.x)\0*.x\0");
		ofn.lpstrTitle = TEXT("�e�L�X�g�t�@�C����ۑ����܂��B");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
	}
	if (GetSaveFileName(&ofn)) {
		MessageBox(hWnd, szFile, TEXT("�t�@�C������t���ĕۑ�"), MB_OK);
	}

	if (szFile[0] != '\0')
	{
		if (Mode == CStageImgui::ENEMY)
		{
			
		}
		if (Mode == CStageImgui::MESH)
		{
		
		}
		if (Mode == CStageImgui::MODEL)
		{
			
		}
	}
	SetCurrentDirectory(szPath);
}

//========================
//�E�B���h�E�����Ă����
//========================
void CStageImgui::funcFileLoad(HWND hWnd, CStageImgui::DATATYPE Mode)
{
	static OPENFILENAME     ofn;
	static TCHAR            szPath[MAX_PATH];
	static TCHAR            szFile[MAX_PATH];

	if (szPath[0] == TEXT('\0')) {
		GetCurrentDirectory(MAX_PATH, szPath);
	}
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrInitialDir = szPath;	// �����t�H���_�ʒu
		ofn.lpstrFile = szFile;			// �I���t�@�C���i�[
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".json");
		ofn.lpstrFilter = TEXT("json�t�@�C��(*.json)\0*.json\0");
		ofn.lpstrTitle = TEXT("�e�L�X�g�t�@�C���ǂݍ��ށB");
		ofn.Flags = OFN_FILEMUSTEXIST;

	}
	if (GetOpenFileName(&ofn)) {
		//MessageBox(hWnd, szFile, TEXT("�����ǂݍ��ނ���"), MB_OK);
	}

	if (szFile[0] != '\0')
	{
		SetCurrentDirectory(szPath);
		if (Mode == CStageImgui::ENEMY)
		{
		}
		if (Mode == CStageImgui::MESH)
		{
		}
		if (Mode == CStageImgui::MODEL)
		{
			
		}
	}
	SetCurrentDirectory(szPath);
}

