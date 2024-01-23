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
#include "map_model.h"

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

	m_model = CMapModel::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_model->LoadModel("BOX");
	m_NowModelName = "BOX";
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
	//ImguiCreate();
	// �e�L�X�g�\��
	ImGui::Text("FPS  : %.2f", ImGui::GetIO().Framerate);
	CMap* map = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetMap();
	//�����钸�_�ɍs���{�^��
	if (ImGui::Button(u8"Save"))
	{// �{�^���������ꂽ
		funcFileSave(CApplication::GetInstance()->GetWindow());
	}

	// �E�C���h�E�̖���
	ImGui::Begin(u8"���f��", nullptr, ImGuiWindowFlags_MenuBar);

	CStageImgui::EditModel();

	ImGui::End();

	// �E�C���h�E�̖���
	ImGui::Begin(u8"���b�V��", nullptr, ImGuiWindowFlags_MenuBar);

	CStageImgui::EditMesh();

	ImGui::End();
	// �E�C���h�E�̖���
	ImGui::Begin(u8"�G�l�~�[���X�g", nullptr, ImGuiWindowFlags_MenuBar);

	CStageImgui::EditEnemy();

	ImGui::End();


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
void CStageImgui::EditModel()
{
	float modelPos[3];

	modelPos[0] = m_model->GetPos().x;
	modelPos[1] = m_model->GetPos().y;
	modelPos[2] = m_model->GetPos().z;

	ImGui::DragFloat3(u8"model�̈ʒu", &modelPos[0],0.5f, -5000.0f, 5000.0f);

	m_model->SetPos(D3DXVECTOR3(modelPos[0], modelPos[1], modelPos[2]));

	float modelRot[3];

	modelRot[0] = m_model->GetRot().x;
	modelRot[1] = m_model->GetRot().y;
	modelRot[2] = m_model->GetRot().z;

	ImGui::DragFloat3(u8"model�̉�]", &modelRot[0], 0.01f, -3.14f, 3.14f);

	m_model->SetRot(D3DXVECTOR3(modelRot[0], modelRot[1], modelRot[2]));

	float modelSize[3];

	modelSize[0] = m_model->GetSize().x;
	modelSize[1] = m_model->GetSize().y;
	modelSize[2] = m_model->GetSize().z;

	ImGui::DragFloat3(u8"model�̃T�C�Y", &modelSize[0], 0.1f, 0.0f, 400.0f);

	m_model->SetSize(D3DXVECTOR3(modelSize[0], modelSize[1], modelSize[2]));

	//--------------------
	//�z�u���Ă����f���ݒ�
	//--------------------
	std::vector<std::string> model =  CApplication::GetInstance()->GetKey();

	if (ImGui::BeginCombo(u8"���f���̃^�C�v", m_NowModelName.c_str(), 0))
	{//����ݒ�
		for (int i = 0; i < model.size(); i++)
		{
			const bool is_selected = ((int)m_indexTex == i);

			if (ImGui::Selectable(model[i].c_str(), is_selected))
			{// �I�΂ꂽ�I�����ɕύX
				m_indexTex = i;
				m_NowModelName = model[i].c_str();
				m_model->LoadModel(m_NowModelName);
			}

			if (is_selected)
			{// �I�����̍��ڂ��J��
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	CMap* map = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetMap();
	if (ImGui::Button(u8"���f������"))
	{// �{�^���������ꂽ
		CMapModel*popmodel = CMapModel::Create(m_model->GetPos(), m_model->GetRot(), m_model->GetSize());
		popmodel->LoadModel(m_NowModelName);
		map->SetMapModel(popmodel);
	}

	CMapModel*pop_model = nullptr;
	bool list = false;

	if (ImGui::BeginCombo(u8"�������Ă郂�f��", m_NowEnemyName.c_str(), 0))
	{//����ݒ�
		for (int i = 0; i < map->GetNumModel(); i++)
		{
			const bool is_selected2 = ((int)m_indexNouEnemy == i);
			std::string m_model = std::to_string(i);
			if (ImGui::Selectable(m_model.c_str(), is_selected2))
			{// �I�΂ꂽ�I�����ɕύX
				m_indexNouEnemy = i;
				m_NowEnemyName = m_indexNouEnemy;
				list = true;
			}

			if (is_selected2)
			{// �I�����̍��ڂ��J��
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	if (map->GetNumModel() != 0)
	{
		pop_model = map->GetMapModel(m_indexNouEnemy);
	}
	
	if (pop_model != nullptr)
	{
		float modelPosPop[3];
		float modelRotPop[3];
		float modelSizePop[3];
		modelPosPop[0] = pop_model->GetPos().x;
		modelPosPop[1] = pop_model->GetPos().y;
		modelPosPop[2] = pop_model->GetPos().z;

		ImGui::DragFloat3(u8"�I��ł�model�̈ʒu", &modelPosPop[0], 0.5f, -5000.0f, 5000.0f);

		pop_model->SetPos(D3DXVECTOR3(modelPosPop[0], modelPosPop[1], modelPosPop[2]));

		modelRotPop[0] = pop_model->GetRot().x;
		modelRotPop[1] = pop_model->GetRot().y;
		modelRotPop[2] = pop_model->GetRot().z;

		ImGui::DragFloat3(u8"�I��ł�model�̉�]", &modelRotPop[0], 0.01f, -3.14f, 3.14f);

		pop_model->SetRot(D3DXVECTOR3(modelRotPop[0], modelRotPop[1], modelRotPop[2]));

		modelSizePop[0] = m_model->GetSize().x;
		modelSizePop[1] = m_model->GetSize().y;
		modelSizePop[2] = m_model->GetSize().z;

		ImGui::DragFloat3(u8"�I��ł�model�̃T�C�Y", &modelSizePop[0], 0.1f, 0.0f, 50000.0f);
	
		pop_model->SetSize(D3DXVECTOR3(modelSizePop[0], modelSizePop[1], modelSizePop[2]));

		if (ImGui::Button(u8"�o�Ă郂�f���̕ύX�i��őI�����Ă��ɂȂ��j"))
		{// �{�^���������ꂽ
			pop_model->LoadModel(m_NowModelName);
		}
	}
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
	ImGui::DragInt(u8"�I�����Ă郁�b�V��", &sliderInt, 0, map->GetNumMesh()-1,1);

	CMesh *mesh = map->GetMapMesh(sliderInt);
	if (mesh)
	{
		std::vector<std::vector<float>> List = mesh->GetY();
		int SizeX = List[0].size();
		int SizeZ = mesh->GetY().size();
	

		ImGui::DragInt2(u8"�I�����Ă钸�_::XZ", &point[0], 1.0f, 0, SizeX-1);
		if (point[1] >= SizeZ)
		{
			point[1] = SizeZ-1;
		}
		meshMoveFloat = List[point[1]][point[0]];

		ImGui::DragFloat(u8"�I�����Ă钸�_", &meshMoveFloat,0.5f, -5000.0f, 5000.0f);

	
		List[point[1]][point[0]] = meshMoveFloat;

		ImGui::DragInt2(u8"�אڂ��Ă钸�_���������ނ�::XZ", &pointMax[0],1.0f, 0, SizeX - 1);
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

			D3DXVECTOR3 PlayerPos = D3DXVECTOR3(((MeshSize.x*point[0]) - MeshSize.x*(SizeX*0.50f)), List[point[1]][point[0]], ((MeshSize.z*point[1]) - MeshSize.z*(SizeZ*0.50f)));
			CPlayerManager::GetInstance()->GetPlayer()->SetPos(PlayerPos);
			
		}
		if (ImGui::Button(u8"�d�͂�����"))
		{
			CPlayerManager::GetInstance()->GetPlayer()->SetInertiaMoveLock(true);
		}
		if (ImGui::Button(u8"�d�͂�t����"))
		{
			CPlayerManager::GetInstance()->GetPlayer()->SetInertiaMoveLock(false);
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
		D3DXVECTOR3 MeshSize = mesh->GetOneMeshSize();
		D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();
		
		PlayerPos.x += MeshSize.x*(SizeX*0.5f);
		PlayerPos.z -= MeshSize.z*(SizeZ*0.5f);
		int ListX = PlayerPos.x / MeshSize.x;
		
		int ListZ = PlayerPos.z / MeshSize.x;
		if (ListZ <= -1)
		{
			ListZ *= -1;
		}
		if (ListX >= SizeX)
		{
			ListX = SizeX - 1;
		}
		if (ListZ >= SizeZ)
		{
			ListZ = SizeZ - 1;

		}
		if (ListX <= -1)
		{
			ListX = 0;
		}
		if (ListZ <= -1)
		{
			ListZ = 0;
		}
		if (ListZ >= -1|| ListX >= -1)
		{
			meshSizeFloatHave[0] = List[ListZ][ListX];
			ImGui::Text(u8"POPX%d :Z%d", ListX, ListZ);
			ImGui::DragFloat(u8"�G��Ă钸�_", &meshSizeFloatHave[0],  0.5f, -5000.0f, 5000.0f);
			List[ListZ][ListX] = meshSizeFloatHave[0];
		}
		else
		{
			ImGui::Text(u8"���_���}�C�i�X�ɂȂ��Ă��܂��܂���", ListX, ListZ);
		}
	

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
void CStageImgui::funcFileSave(HWND hWnd)
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
		CMap* map = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetMap();
		map->Save(szFile);
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

