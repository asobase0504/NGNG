//**************************************************************
//
// ライン描画処理(line.h)
// Author : 唐�ｱ結斗
// 概要 : ライン生成を行う
//
//**************************************************************
#ifndef _LINE_H_		// このマクロ定義がされてなかったら
#define _LINE_H_		// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "object.h"

//==============================================================
// ラインクラス
// Author : 唐�ｱ結斗
// 概要 : ライン生成を行うクラス
//==============================================================
class CLine : public CObject
{
public:
	// 頂点フォーマット
	const unsigned int	FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE);

	//--------------------------------------------------------------
	// 構造体定義
	//--------------------------------------------------------------
	// 頂点データ
	typedef struct
	{
		D3DXVECTOR3			pos;			// 頂点座標
		D3DXVECTOR3			nor;			// 法線ベクトル
		D3DCOLOR			col;			// 頂点カラー
	}VERTEX_3D;

	//--------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------
	static CLine *Create(void);				// オブジェクトの生成

	//--------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------
	explicit CLine();
	~CLine();

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update() override;		// 更新
	void Draw() override;		// 描画

	void SetRotTarget(const D3DXVECTOR3* rot) { m_targetRot = rot; }
	void SetPosTarget(const D3DXVECTOR3* pos) { m_targetPos = pos; }

	void SetVtx();								// 頂点座標などの設定
	void SetColor(const D3DXCOLOR& color) override;			// 頂点カラーの設定
	void SetLine(D3DXVECTOR3 start, D3DXVECTOR3 goal);	// ラインの設置


	static bool m_alldisplay;

private:
	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	LPDIRECT3DVERTEXBUFFER9 m_vtxBuff;			// 頂点バッファ
	D3DXVECTOR3 m_start;			// 始点
	D3DXVECTOR3 m_goal;				// 終点
	const D3DXVECTOR3* m_targetPos;
	const D3DXVECTOR3* m_targetRot;
};
#endif
