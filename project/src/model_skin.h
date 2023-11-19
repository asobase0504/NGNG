//=============================================================================
//
// 3Dモデルクラス(model3D.h)
// Author : 唐﨑結斗
// 概要 : 3Dモデル生成を行う
//
//=============================================================================
#ifndef _MODEL_SKIN_H_			// このマクロ定義がされてなかったら
#define _MODEL_SKIN_H_			// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"
#define SKIN_ANIME_SPEED 60.0f / 4800.0f

#define SAFE_RELEASE(p) if (p) { (p)->Release(); (p) = nullptr; }
#define SAFE_DELETE(p) if (p) { delete (p); (p) = nullptr; }
#define SAFE_DELETE_ARRAY(p) if (p) { delete[] (p); (p) = nullptr; }

//派生フレーム構造体 (それぞれのメッシュ用の最終ワールド行列を追加する）
struct MYFRAME : public D3DXFRAME
{
	D3DXMATRIX CombinedTransformationMatrix;
	// オフセット行列(インデックス付描画用)
	D3DXMATRIX OffsetMat;
	// 行列テーブルのインデックス番号(インデックス付用)
	DWORD OffsetID;
};

//派生メッシュコンテナー構造体(
//コンテナーがテクスチャを複数持てるようにポインターのポインターを追加する）
struct MYMESHCONTAINER : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*  ppTextures;
	DWORD dwWeight; //重みの個数（重みとは頂点への影響。）
	DWORD dwBoneNum; //ボーンの数
	LPD3DXBUFFER pBoneBuffer; //ボーン・テーブル
	D3DXMATRIX** ppBoneMatrix; //全てのボーンのワールド行列の先頭ポインター
	D3DXMATRIX* pBoneOffsetMatrices; //フレームとしてのボーンのワールド行列のポインター
	LPD3DXMESH pOriMesh; //オリジナルメッシュ用
	DWORD NumPaletteEntries; //パレットサイズ

	 // Work用
	std::vector<D3DXMATRIX> m_WorkBoneMatArray;
	// 影響するフレームへの参照配列。描画時にこのフレームの行列を使う。
	std::vector<MYFRAME*> BoneFrameArray;
	MYMESHCONTAINER() {
		ppBoneMatrix = NULL;
		pBoneOffsetMatrices = NULL;
	}
};

//Xファイル内のアニメーション階層を読み下してくれるクラスを派生させる。
//ID3DXAllocateHierarchyは派生すること想定して設計されている。
class MY_HIERARCHY : public ID3DXAllocateHierarchy
{
public:
	MY_HIERARCHY() {}
	STDMETHOD(CreateFrame)(THIS_ LPCSTR, LPD3DXFRAME *);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCTSTR, CONST D3DXMESHDATA*, CONST D3DXMATERIAL*,
		CONST D3DXEFFECTINSTANCE*, DWORD, CONST DWORD *, LPD3DXSKININFO, LPD3DXMESHCONTAINER *);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER);
private:
};

//=============================================================================
// 3Dモデルクラス
// Author : Hamada Ryuga
// 概要 : 3Dモデル生成を行うクラス
//=============================================================================
// スキンメッシュクラス
class CSkinMesh : public CObject
{
public:
	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CSkinMesh *Create(std::string Name);		// 3Dモデルの生成

	CSkinMesh();
	~CSkinMesh() {
		Release();
	}
	HRESULT Init() override { return S_OK; }
	void Uninit() override { CObject::Uninit(); }
	void Update() override;

	//スキンメッシュ内部処理
	HRESULT Init(std::string pMeshPass);
	HRESULT AllocateBoneMatrix(LPD3DXFRAME pFrameRoot, LPD3DXMESHCONTAINER pMeshContainerBase);
	HRESULT AllocateAllBoneMatrices(LPD3DXFRAME pFrameRoot, LPD3DXFRAME pFrameBase);
	void RenderMeshContainer(MYMESHCONTAINER*, MYFRAME*);
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	void DrawFrame(LPD3DXFRAME);
	//フレーム解放
	void FreeAnim(LPD3DXFRAME pFrame);
	//解放処理
	void Release();

	//描画処理
	void Draw();
	//オブジェクトのアニメーション変更( メッシュオブジェクトの操作用番号, 変更するアニメーション番号 )
	void ChangeAnim(DWORD);
	//現在のアニメーション番号取得
	DWORD GetAnimTrack() { return m_CurrentTrack; }
	//現在のアニメーションタイム(アニメーション開始からの時間)を取得
	DWORD GetAnimTime() { return m_AnimeTime; }
	//アニメーション速度を取得
	float GetAnimSpeed() { return m_AnimSpeed; }
	//アニメーション速度を設定
	void SetAnimSpeed(float _AnimSpeed) { m_AnimSpeed = _AnimSpeed; }
private:
	//対象のボーンを検索
	MYFRAME* SearchBoneFrame(std::string  _BoneName, D3DXFRAME* _pFrame);
public:
	//ボーンのマトリックス取得( ボーンの名前 )
	D3DXMATRIX GetBoneMatrix(std::string  _BoneName);
	//ボーンのマトリックスポインタ取得( ボーンの名前 )
	D3DXMATRIX* GetpBoneMatrix(std::string  _BoneName);
private:
	//追加
	//すべてのフレームポインタ格納処理関数
	void CreateFrameArray(LPD3DXFRAME _pFrame);
	// フレーム参照用配列
	std::vector<MYFRAME*> m_FrameArray;			// 全フレーム参照配列
	std::vector<MYFRAME*> m_IntoMeshFrameArray;	// メッシュコンテナありのフレーム参照配列

	LPD3DXFRAME m_pFrameRoot;	//ボーン情報
	LPD3DXANIMATIONCONTROLLER m_pAnimController;	//アニメーションコントローラ
	MY_HIERARCHY m_cHierarchy;	//ヒエラルキークラス変数
	std::vector<LPD3DXANIMATIONSET> m_pAnimSet;	//アニメーションデータ格納用
	DWORD m_AnimeTime;	//現在のアニメーションが開始されてからの時間(1/60秒)
	float m_AnimSpeed;	//アニメーションスピード
	DWORD m_CurrentTrack;	//現在のアニメーショントラック
	D3DXTRACK_DESC m_CurrentTrackDesc;	//現在のアニメーションデータトラック
	D3DXMATRIX m_World;	//進行方向
};

#endif