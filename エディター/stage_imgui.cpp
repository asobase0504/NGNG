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
#include "application.h"
#include "player.h"
#include "map.h"
#include "object_mesh.h"
#include "player_manager.h"
#include "enemy_data_base.h"

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
	CMap* map = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetMap();
	//�����钸�_�ɍs���{�^��
	if (ImGui::Button(u8"Save"))
	{// �{�^���������ꂽ
		map->Save("data/test.json");
	}

	CStageImgui::EditMesh();
	CStageImgui::EditEnemy();
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
	static int sliderInt = 0;
	static int point[2] = {0.0};
	static int pointMax[2] = { 0.0 };
	static float meshSizeFloat[2];
	static float meshMoveFloat;
	static float meshSizeFloatHave[3];
	static D3DXVECTOR3 meshMovePoptimeFloat;
	static char textmesh[MAX_TEXT] = "";
	static bool Reverse = false;

	int Meshint = 0;
	CMap* map = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetMap();
	ImGui::SliderInt(u8"�I�����Ă郁�b�V��", &sliderInt, 0, map->GetNumMesh()-1);

	CMesh *mesh = map->GetMapMesh(sliderInt);
	if (mesh)
	{
		std::vector<std::vector<float>> List = mesh->GetY();
		int SizeX = List[0].size();
		int SizeZ = mesh->GetY().size();
	

		ImGui::SliderInt2(u8"�I�����Ă钸�_::XZ", &point[0], 0, SizeX-1);
		if (point[1] >= SizeZ)
		{
			point[1] = SizeZ-1;
		}
		meshMoveFloat = List[point[1]][point[0]];

		ImGui::SliderFloat(u8"�I�����Ă钸�_", &meshMoveFloat, -5000.0f, 5000.0f);

	
		List[point[1]][point[0]] = meshMoveFloat;

		ImGui::SliderInt2(u8"�אڂ��Ă钸�_���������ނ�::XZ", &pointMax[0], 0, SizeX - 1);
		if (pointMax[1] >= SizeZ)
		{
			pointMax[1] = SizeZ - 1;
		}

		//�����钸�_�ɍs���{�^��
		if (ImGui::Button(u8"�܂Ƃ߂ē����l�ɂ���"))
		{// �{�^���������ꂽ
			for (int pointZ = 0; pointZ <= pointMax[1]; pointZ++)
			{
				for (int pointX = 0; pointX <= pointMax[0]; pointX++)
				{
					int Z = point[1] + pointZ;
					if (Z >= SizeZ - 1)
					{
						Z = SizeZ - 1;
					}
					int X = point[0] + pointX;
					if (X >= SizeX - 1)
					{
						X = SizeX - 1;
					}
					List[Z][X] = meshMoveFloat;
				}
			}
		}
			
		//�����钸�_�ɍs���{�^��
		if (ImGui::Button(u8"�I�����Ă钸�_�ɍs��"))
		{// �{�^���������ꂽ
			D3DXVECTOR3 MeshSize = mesh->GetOneMeshSize();
			CPlayerManager::GetInstance()->GetPlayer()->SetPos(D3DXVECTOR3((MeshSize.x*point[0]) - MeshSize.x*(SizeX*0.49f), 3000, (MeshSize.z*point[1])+ MeshSize.z*(SizeZ*0.49f)));
		}
		
		mesh->SetY(List);
		
		//for (int i = 0; i < 1; i++)
		//{
		//	int test = m_Vtx[i];
		//	int hoge = 0;
		//	int hoge2 = 0;
		//	hoge = test / SizeZ;
		//	hoge2 = test / SizeX;
		//	meshSizeFloatHave[i] = List[hoge][hoge2];
		//	ImGui::Text(u8"POPX%d :Z%d", hoge, hoge2);
		//	ImGui::SliderFloat(u8"�G��Ă钸�_", &meshSizeFloatHave[i], -5000.0f, 5000.0f);
		//	List[hoge][hoge2] = meshSizeFloatHave[i];
		//}

		mesh->SetY(List);

		

		
	}
	
	ImGui::Separator();


}

//--------------------------------------------------
// �G�l�~�[�̐ݒ�
//--------------------------------------------------
void CStageImgui::EditEnemy()
{
		static int draw_lines = 3;
		static int max_height_in_lines = 10;

		CMap* map = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetMap();
		ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 1), ImVec2(FLT_MAX, ImGui::GetTextLineHeightWithSpacing() * max_height_in_lines));
		// Demonstrate using ImGuiTableColumnFlags_AngledHeader flag to create angled headers
	
	
		if (ImGui::TreeNode(u8"���̃}�b�v�ŏo��G�l�~�["))
		{
			const char* column_names[] = { "PopList","SKELTON", "TENGU", "TENGU_CHILD", "MONSTER", "SKY_MONSTER", "NURIKABE", "ONI_BIG", "ONI", "KARAKASA", "KAPPA", "GYUUKI", "FOX", "DULLAHAN", "GASYADOKURO","NINE_FOX" };
			const int columns_count = IM_ARRAYSIZE(column_names);
		
			const int rows_count = 1;

			static ImGuiTableFlags table_flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_Hideable | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_HighlightHoveredColumn;
			static bool bools[columns_count * rows_count] = {}; // Dummy storage selection storage
			static int frozen_cols = 1;
			static int frozen_rows = 2;
			
			for (int i = 0; i < columns_count - 1; i++)
			{
				bools[i + 1] = map->GetEnemyPopList(i);
			}

			if (columns_count != m_list.size())
			{
				m_list.resize(columns_count);
			}

		
			if (ImGui::BeginTable("table_angled_headers", columns_count, table_flags, ImVec2(0.0f, 17 * 12)))
			{
				ImGui::TableSetupColumn(column_names[0], ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_NoReorder);
				for (int n = 1; n < columns_count; n++)
					ImGui::TableSetupColumn(column_names[n], ImGuiTableColumnFlags_AngledHeader | ImGuiTableColumnFlags_WidthFixed);
				ImGui::TableSetupScrollFreeze(frozen_cols, frozen_rows);

				ImGui::TableAngledHeadersRow(); // Draw angled headers for all columns with the ImGuiTableColumnFlags_AngledHeader flag.
				ImGui::TableHeadersRow();       // Draw remaining headers and allow access to context-menu and other functions.
				for (int row = 0; row < rows_count; row++)
				{
					ImGui::PushID(row);
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					ImGui::AlignTextToFramePadding();
					ImGui::Text(u8"POP%d", row);
					for (int column = 1; column < columns_count; column++)
						if (ImGui::TableSetColumnIndex(column))
						{
							ImGui::PushID(column);
							ImGui::Checkbox("", &bools[row * columns_count + column]);
							ImGui::PopID();
						}
					ImGui::PopID();
				}
				ImGui::EndTable();
			}
		
			for (int i = 0; i < columns_count - 1; i++)
			{
				m_list[i] = bools[i + 1];
			}
			map->EnemyPopList(m_list);
			ImGui::TreePop();
		}
	

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

