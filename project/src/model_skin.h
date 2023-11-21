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
#include "model_skin_group.h"

#define SKIN_ANIME_SPEED 60.0f / 4800.0f

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
	void ShaderDraw(MYMESHCONTAINER*, MYFRAME*);
	void RenderMeshContainer(MYMESHCONTAINER*, MYFRAME*);
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	void DrawFrame(LPD3DXFRAME);
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
	MYFRAME* SearchBoneFrame(std::string _BoneName, D3DXFRAME* _pFrame);
public:
	//ボーンのマトリックス取得( ボーンの名前 )
	D3DXMATRIX GetBoneMatrix(std::string _BoneName);
	//ボーンのマトリックスポインタ取得( ボーンの名前 )
	D3DXMATRIX* GetpBoneMatrix(std::string _BoneName);
private:
	//追加
	//すべてのフレームポインタ格納処理関数
	void CreateFrameArray(LPD3DXFRAME _pFrame);

	LPD3DXFRAME m_pFrameRoot;	//ボーン情報

	// アニメーション
	LPD3DXANIMATIONCONTROLLER m_pAnimController;	//アニメーションコントローラ
	std::vector<LPD3DXANIMATIONSET> m_pAnimSet;	//アニメーションデータ格納用
	DWORD m_AnimeTime;	//現在のアニメーションが開始されてからの時間(1/60秒)
	float m_AnimSpeed;	//アニメーションスピード
	DWORD m_CurrentTrack;	//現在のアニメーショントラック
	D3DXTRACK_DESC m_CurrentTrackDesc;	//現在のアニメーションデータトラック
	DWORD m_animeEndTime;				// アニメーション終了フレーム

	bool m_isLoop;	// Loopしたかどうか
	bool m_isAnimeEnd;	// 一回アニメーションを終わらせたか
};
#endif