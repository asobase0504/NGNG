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
// コンストラクタ
//-----------------------------------------------------------------------------
CStageImgui::CStageImgui() :
	m_sliderIntmodel(0),
	m_sliderIntmesh(0)
{
}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CStageImgui::~CStageImgui()
{
}

//-----------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------
HWND CStageImgui::Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice)
{
	// 初期化
	HWND outWnd = CImguiProperty::Init(hWnd, pDevice);

	// 鉄球データを初期化
	m_Pendulum.type = 0;
	m_Pendulum.coefficient = 0.0f;
	m_Pendulum.destRot.x = 0.0f;
	m_Pendulum.destRot.y = 0.0f;
	m_Pendulum.destRot.z = 0.0f;

	// ボールデータを初期化
	m_Ball.rotType = 0;
	m_Ball.radius = 0.0f;
	m_Ball.rotSpeed = 0.0f;

	// 丸太データを初期化
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
// 終了
//-----------------------------------------------------------------------------
void CStageImgui::Uninit(HWND hWnd, WNDCLASSEX wcex)
{
	CImguiProperty::Uninit(hWnd, wcex);
}

//-----------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------
bool CStageImgui::Update()
{


	CImguiProperty::Update();
	ImguiCreate();
	// テキスト表示
	ImGui::Text("FPS  : %.2f", ImGui::GetIO().Framerate);

	CStageImgui::EditMesh();

	//ImGui::SliderFloat3(u8"ロット", &sliderRot.x, -3.14f, 3.14f);
	//ImGui::Separator();

	ImGui::End();


	return false;

}

//--------------------------------------------------
// 描画
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
// タスクバーの更新
//--------------------------------------------------
void CStageImgui::TaskBarUpdate(void)
{
	if (!ImGui::BeginMenuBar())
	{//タスクバー
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
// エネミーの設定
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
// Playerの動き
//--------------------------------------------------
void CStageImgui::EditPlayer()
{
	
}

//--------------------------------------------------
// ウインドウ出力処理
//--------------------------------------------------
void CStageImgui::Imguigold(void)
{
	// ウインドウの命名
	ImGui::Begin("gold", nullptr, ImGuiWindowFlags_MenuBar);
	ImGui::End();
}

//--------------------------------------------------
// ウインドウ出力処理
//--------------------------------------------------
void CStageImgui::Imguifilecord(void)
{
	// ウインドウの命名
	static char textSeve[MAX_TEXT] = "STAGE0";
	ImGui::Begin("gold", nullptr, ImGuiWindowFlags_MenuBar);
	ImGui::InputText(u8"保存したい名まえ", textSeve, sizeof(textSeve));

	m_SavefileNeme = textSeve;
	
	ImGui::End();
}

//--------------------------------------------------
// ウインドウ出力処理
//--------------------------------------------------
void CStageImgui::ImguiEnemy(void)
{
	// ウインドウの命名
	ImGui::Begin(u8"Enemy", nullptr, ImGuiWindowFlags_MenuBar);
	ImGui::End();
}

//--------------------------------------------------
// 選んでるモテル
//--------------------------------------------------
bool CStageImgui::GetAnimati()
{
	return m_Animation;
}

//--------------------------------------------------
// 選んでるモテル
//--------------------------------------------------
int CStageImgui::selectModel()
{
	return m_indexBuilding;
}

//--------------------------------------------------
// ウインドウ出力処理
//--------------------------------------------------
void CStageImgui::ImguiCreate(void)
{
	// ウインドウの命名
	ImGui::Begin(u8"生成ボタン", nullptr, ImGuiWindowFlags_MenuBar);

	if (ImGui::Button(u8"Mesh生成"))
	{// ボタンが押された
	
	}

	ImGui::End();
}

//--------------------------------------------------
// ウインドウ出力処理
//--------------------------------------------------
void CStageImgui::ImguiPlarer(void)
{

	ImGui::End();
}

//========================
//ウィンドウだしてやるやつ
//========================
void CStageImgui::ImguiChangenumber(std::string number, int Number)
{


	ImGui::End();
}

//========================
//ウィンドウだしてやるやつ
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
		ofn.lpstrInitialDir = szPath;	// 初期フォルダ位置
		ofn.lpstrFile = szFile;			// 選択ファイル格納
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".json\0.x");
		ofn.lpstrFilter = TEXT("jsonファイル(*.json)\0*.json\0Xファイル(*.x)\0*.x\0");
		ofn.lpstrTitle = TEXT("テキストファイルを保存します。");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
	}
	if (GetSaveFileName(&ofn)) {
		MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);
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
//ウィンドウだしてやるやつ
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
		ofn.lpstrInitialDir = szPath;	// 初期フォルダ位置
		ofn.lpstrFile = szFile;			// 選択ファイル格納
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".json");
		ofn.lpstrFilter = TEXT("jsonファイル(*.json)\0*.json\0");
		ofn.lpstrTitle = TEXT("テキストファイル読み込む。");
		ofn.Flags = OFN_FILEMUSTEXIST;

	}
	if (GetOpenFileName(&ofn)) {
		//MessageBox(hWnd, szFile, TEXT("これを読み込むぞぉ"), MB_OK);
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

