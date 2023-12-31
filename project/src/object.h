//**************************************************************
//
// オブジェクト
// Author : Hamada Ryuuga
// AUthor : Yuda Kaito
//
//**************************************************************
#ifndef _OBJECT_H_			// このマクロ定義がされてなかったら
#define _OBJECT_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "renderer.h"
#include "task.h"

//==============================================================
// オブジェクトクラス
//==============================================================
class CObject : public CTask
{
public:
	enum EType
	{
		ENEMY = 0,
		PLAYER,
		GOAL,
		MODE,
		MODEL,
		PLAIN,
		PAUSE,
		POLYGON,
		MAX,
		NONE
	};

public:
	CObject(CTaskGroup::EPriority inPriority = CTaskGroup::LEVEL_2D_BG, CTaskGroup::EPushMethod inMethod = CTaskGroup::EPushMethod::PUSH_CURRENT);
	virtual ~CObject() override;

	HRESULT Init() override;
	void Update() override;

	/* 種類系 */
	void SetType(const EType inType) { m_type = inType; }
	EType GetType() { return m_type; }
	static CObject* SearchType(EType inType, int inPriority);
	CObject* NextSameType();

	// 一つタイプ全てに処理をかける
	static void TypeAllFunc(CObject::EType inType, CTaskGroup::EPriority inPriority, std::function<void(CObject*)> inFunc);

	/* 位置系 */
	virtual void SetPos(const D3DXVECTOR3 &inPos) { m_pos = inPos; }
	void AddPos(const D3DXVECTOR3 &inPos) { SetPos(m_pos + inPos); }
	void MulPos(const float inRatio) { SetPos(m_pos * inRatio); }
	D3DXVECTOR3 &GetPos() { return m_pos; }

	/* 位置系 */
	virtual void SetPosOld(const D3DXVECTOR3 &inPos) { m_posOld = inPos; }
	void AddPosOld(const D3DXVECTOR3 &inPos) { SetPos(m_posOld + inPos); }
	void MulPosOld(const float inRatio) { SetPos(m_posOld * inRatio); }
	const D3DXVECTOR3 &GetPosOld() const { return m_posOld; }

	/* 移動系 */
	virtual void SetMove(const D3DXVECTOR3 &inMove) { m_move = inMove; }
	void AddMove(const D3DXVECTOR3 &inMove) { SetMove(m_move + inMove); }
	void MulMove(const float &inRatio) { SetMove(m_move * inRatio); }
	const D3DXVECTOR3 &GetMove() const { return m_move; }
	virtual void SetMoveY(const float inMove) { m_move.y = inMove; }
	void AddMoveY(const float inMove) { SetMoveY(m_move.y + inMove); }
	virtual void SetMoveXZ(const float X, const float Z) { m_move.x = X; m_move.z = Z;}
	void AddMoveXZ(const float X, const float Z) { SetMoveXZ(m_move.x + X, m_move.z + Z); }

	/* 向き系 */
	virtual void SetRot(const D3DXVECTOR3 &inRot) { m_rot = inRot; }
	void AddRot(const D3DXVECTOR3 &inRot) { SetRot(m_rot + inRot); }
	void MulRot(const float &inRatio) { SetRot(m_rot * inRatio); }
	const D3DXVECTOR3 &GetRot() const { return m_rot; }

	/* 回転系 */
	virtual void SetMoveRot(const D3DXVECTOR3 &inMove) { m_moveRot = inMove; }
	void AddMoveRot(const D3DXVECTOR3 &inMove) { SetMove(m_moveRot + inMove); }
	void MulMoveRot(const float &inRatio) { SetMove(m_moveRot * inRatio); }
	const D3DXVECTOR3 &GetMoveRot() const { return m_moveRot; }

	/* 大きさ系 */
	virtual void SetSize(const D3DXVECTOR3 &inSize) { m_size = inSize; }
	void AddSize(const D3DXVECTOR3 &inSize) { SetSize(m_size + inSize); }
	void MulSize(const D3DXVECTOR3 &inRatio);
	void MulSize(const float &inRatio) { SetSize(m_size * inRatio); }
	const D3DXVECTOR3 &GetSize() const { return m_size; }

	/* 色系 */
	virtual void SetColor(const D3DXCOLOR &inColor) { m_color = inColor; }
	virtual void SetColor(float r, float g, float b, float a) { SetColor(D3DXCOLOR(r,g,b,a)); }
	void AddColor(const D3DXCOLOR &inColor) { SetColor(m_color + inColor); }
	void AddColor(float r, float g, float b, float a) { AddColor(D3DXCOLOR(r, g, b, a)); }
	void MulColor(const float &inRatio) { SetColor(m_color * inRatio); }
	const D3DXCOLOR &GetColor() const { return m_color; }

	// 透明色のみ
	virtual void SetColorAlpha(float inAlpha) { SetColor(D3DXCOLOR(m_color.r,m_color.g,m_color.b,inAlpha)); }
	void AddColorAlpha(float inAlpha) { SetColorAlpha(m_color.a + inAlpha); }
	void MulColorAlpha(float inRatio) { SetColorAlpha(m_color.a * inRatio); }
	float GetColorAlpha() const { return m_color.a; }

	/* ワールドマトリックス */
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }	// 設定
	const D3DXMATRIX& GetMtxWorld() { return m_mtxWorld; }				// 取得

	void SetMtxWorldParent(D3DXMATRIX* mtxWorld) { m_mtxWorldParent = mtxWorld; }	// 親設定

	/* テスクチャ系 */
	void SetTexture(std::string inKey) { m_textureKey = inKey; }
	std::string GetTexture() { return m_textureKey; }

	float m_TimeCnt;
	float m_TimeTarget;

	virtual void SetDisplay(bool display) { m_isDisplay = display; }

protected:

	//=========================================
	//ハンドル一覧
	//=========================================
	IDirect3DTexture9*	tex0;	// テクスチャ保存用
	IDirect3DTexture9*	tex1;	// テクスチャ保存用
	D3DXHANDLE			m_hView;		// view行列
	D3DXHANDLE			m_hProj;		// projection行列
	D3DXHANDLE			m_hWorld;		// ワールド行列
	D3DXHANDLE			m_hvLightDir;	// ライトの方向
	D3DXHANDLE			m_hvEyePos;		// 視点の位置
	D3DXHANDLE			m_hvDiffuse;	// 頂点色
	D3DXHANDLE			m_hvAmbient;	// 頂点色
	D3DXHANDLE			m_hTechnique;	// テクニック
	D3DXHANDLE			m_hTexture;		// テクスチャ
	D3DXHANDLE			m_hTime;		// 時間を渡す
	D3DXHANDLE			m_hTimeTarget;	// 目標時間
	D3DXHANDLE			m_hSize;		// サイズ
	D3DXHANDLE			m_hRot;			// 角度
	D3DXHANDLE			m_hTrans;		// 変換用 
	D3DXHANDLE			m_hParent;		// 親子関係
	D3DXHANDLE			m_hScale;		// スケール
	D3DXHANDLE			m_hCameraVec;	// カメラの向き
	D3DXHANDLE			m_hMtxNum;		// マトリックスの数
	D3DXHANDLE			m_hBoneStack;	// ボーンのマテリアル情報

	int m_shaderIndex;

	D3DXVECTOR3 m_pos;				// 位置
	D3DXVECTOR3 m_posOld;			// 過去の位置
	D3DXVECTOR3 m_move;				// 移動量
	D3DXVECTOR3 m_rot;				// 向き
	D3DXVECTOR3 m_moveRot;			// 回転量
	D3DXVECTOR3 m_size;				// 大きさ
	D3DXCOLOR m_color;				// 色
	D3DXMATRIX m_mtxWorld;			// ワールドマトリックス
	D3DXMATRIX* m_mtxWorldParent;	// 親のワールドマトリックス

	EType m_type;	// 種別
	std::string m_textureKey;	// テクスチャにアクセスするキー

	bool m_isDisplay;
};
#endif