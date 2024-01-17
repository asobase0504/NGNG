//**************************************************
// 
// particle_imgui.h
// Author  : katsuki mizuki
// Author  : Yuda Kaito
// 
//**************************************************
#ifndef _STAGE_IMGUI_H_	// このマクロが定義されてなかったら
#define _STAGE_IMGUI_H_	// 2重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "imgui_property.h"


class CMapModel;
//--------------------------------------------------
// パーティクル用のImgui表示クラス
//--------------------------------------------------
class CStageImgui : public CImguiProperty
{
public:
	enum DATATYPE
	{
		ENEMY = 0,		// Enemy
		MODEL,			// モデル
		MESH,			// Mesh
		MAX			//あんただれや？
	};

private:	
	

	// 定義
	struct Pendulum
	{
		int type;
		float coefficient;
		D3DXVECTOR3 destRot;
	};

	struct Ball
	{
		int rotType;
		float radius;
		float  rotSpeed;
	};

	struct Wood
	{
		int coolTime;
		float rot;
		float rotSpeed;
		float move;
	};

	static const int D3DXyz = 3;//XYZ初期化用
public:
	CStageImgui();
	~CStageImgui();

	HWND Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice) override;
	void Uninit(HWND hWnd, WNDCLASSEX wcex) override;
	bool Update() override;
	void Draw() override;

	int GetMesh() const { return m_sliderIntmesh; }
	int GetModel() const { return m_sliderIntmodel; }
	int GetEnemy() const { return m_sliderIntEnemy; }

	int GetModelEnemy() const { return m_indexEnemy; }
	
	Ball GetBall() const { return m_Ball; }
	Wood GetWood() const { return m_Wood; }
	Pendulum GetPendulum() const { return m_Pendulum; }

	void Imguigold();
	void ImguiEnemy();
	void ImguiChangenumber(std::string number,int Number);

	int selectModel();
	bool GetAnimati();

	const D3DXVECTOR3& GetRot() { return D3DXVECTOR3(m_sliderRot3[0], m_sliderRot3[1], m_sliderRot3[2]); }
	const D3DXVECTOR3& GetPosV() { return D3DXVECTOR3(m_PosVSet[0], m_PosVSet[1], m_PosVSet[2]); }
	const D3DXVECTOR3& GetPosR() { return D3DXVECTOR3(m_PosRSet[0], m_PosRSet[1], m_PosRSet[2]); }


	const D3DXVECTOR3& GetposRDest() { return D3DXVECTOR3(m_posRDest[0], m_posRDest[1], m_posRDest[2]); }
	const D3DXVECTOR3& GetposVDest() { return D3DXVECTOR3(m_posVDest[0], m_posVDest[1], m_posVDest[2]); }
	const D3DXVECTOR3& GetDistance() { return D3DXVECTOR3(m_fDistance[0], m_fDistance[1], m_fDistance[2]); }

	std::string GetPass() { return m_CameraAnimationPass; }

	std::string Getfile() { return m_SavefileNeme; }
	

	void SetVtx(int inx,int Llst) { m_Vtx[Llst] = inx; }
	
private: // プライベート関数
	void TaskBarUpdate();
	void EditMesh();
	void EditModel();
	void EditCamera();
	void EditEnemy();

	void EditPlayer();
	void ImguiCreate();
	void Imguifilecord();
	void ImguiPlarer();


	void funcFileSave(HWND hWnd);
	void funcFileLoad(HWND hWnd, CStageImgui::DATATYPE Mode);
private: // メンバー変数

	const int MeshMax = 100;
	static const int	MAX_TEXT = 1024;		// テキストの最大文字数
	const char*	WINDOW_NAME = "test";	// ウインドウの名前 (キャプションに表示)

	D3DXVECTOR3 sliderRot;			// meshの回転やりたかった....

	bool m_Gura = false;			// 重力
	bool m_MoveIron = false;		// 鉄球動かさない設定（スクロールバー）
	Ball m_Ball;					// 設置したBallの表示名（受け取る箱）
	Pendulum m_Pendulum;			// 設置したPendulumの表示名（受け取る箱）
	Wood m_Wood;					// 設置したWoodの表示名（受け取る箱）	

	int m_sliderIntmodel;

	int m_indexBuilding = 0;			// 編集したいモデルの表示ID（コンボボックス）
	int m_indexEmemy = 0;			// 編集したいモデルの表示ID（コンボボックス）

	std::string m_NowModelName;		// 設置したモデルの表示名（コンボボックス）
	float m_sliderPos3[3];			// 回転するタマの座標（受け取る箱）	
	float m_sliderRot3[3];			// 回転するタマの回転（受け取る箱）	
	float m_sliderNowRot3[3];			// 回転するタマの回転（受け取る箱）	
	float m_PosVSet[3];			// 自由の時座標設定するよう	
	float m_PosRSet[3];			// 自由の時座標設定するよう	
	float m_sliderPlayerPos[3];			// プレイヤーの位置（受け取る箱）	


	int m_sliderIntmesh;					// meshのType選択（スクロールバー）
	int m_sliderIntEnemy = 0;				// EnemyのType選択（スクロールバー）
	signed int m_indexModel = 0;			// 編集したいモデルの表示ID（コンボボックス）
	signed int m_indexTex = 0;				// 編集したいテクスチャの表示ID（コンボボックス）
	signed int m_indexNouEnemy;				//編集したいエネミーの表示ID（コンボボックス）
	signed int m_indexmeshAnimation = 0;	// 編集したいメッシュのアニメーション番号表示ID（コンボボックス）
	signed int m_indexmeshNumber = 0;		// 編集したいメッシュの番号の表示ID（コンボボックス）

	signed int m_indexCamera = 0;			// 編集したいカメラAnimationの番号の表示ID（コンボボックス）
	signed int m_indexCameraAnimation = 0;	// 編集したいカメラAnimationの中の座標番号の表示ID（コンボボックス）

	signed int m_indexEnemy = 0;				// 編集したいtekiの表示ID（コンボボックス）

	signed int m_indexEnemyBoss = 0;				// 編集したいBOSSアニメーションの表示ID（コンボボックス）
	std::string m_NowMeshName;				// 編集したいmeshの表示名（コンボボックス）
	std::string m_NowEnemyName;				// 編集したいエネミーの表示名（コンボボックス）
	std::string m_NowMeshNumberName;			// 編集したいアニメーションNumberの表示名（コンボボックス）
	std::string m_NowCameraNumberName;		// 編集したいCameraNumberの表示名（コンボボックス）
	std::string m_NowCameraAnimationNumberName;	// 編集したいCameraアニメーションNumberの表示名（コンボボックス）
	std::string m_CameraAnimationPass;		// 編集したいCameraアニメーションNumberの表示名（）

	std::string m_BossAnime;
	std::string m_SavefileNeme;		// Saveしたいfile名（）

	bool m_Animation = false;					// アニメーションするかしないか
	bool m_Izing = false;
	
	int m_KeySet;


	//カメラのプレイヤー追従機能の編集
	float m_posRDest[3];			// 自由の時座標設定するよう	
	float m_posVDest[3];			// 自由の時座標設定するよう	
	float m_fDistance[3];			//なんこれ

	int m_BossAnimation;
	int m_BossAnimationType = 0;

	int m_BossKeySet = 0;

	int m_Vtx[3];

	std::vector<bool> m_list;
	D3DXVECTOR3 m_PlayerPos;

	
	CMapModel*m_model;
	
};

#endif // !_IMGUI_PROPERTY_H_
