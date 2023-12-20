//**************************************************************
//
// オブジェクトX処理 [objectX.h]
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//==============================================================
// include
//==============================================================
#include "object.h"

//==============================================================
// 前方宣言
//==============================================================
class CObjectPolygon3D;

//==============================================================
// クラスの定義
//==============================================================
class CObjectX : public CObject
{
public:
	//--------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------
	explicit CObjectX(CTaskGroup::EPriority nPriority = CTaskGroup::LEVEL_3D_1);
	~CObjectX() override;

	//--------------------------------------------------------------
	// メンバー関数
	//--------------------------------------------------------------
	HRESULT Init() override;	// 初期化

	/* 描画 */
	void Draw() override;
	void DrawMaterial();
	void Projection();			// 平行投影処理

	/* 生成処理 */
	static CObjectX *Create(D3DXVECTOR3 pos, CTaskGroup::EPriority nPriority = CTaskGroup::LEVEL_3D_1);
	void LoadModel(std::string aFileName);		// モデルの読み込み処理

	/* 大きさ倍率 */
	void SetScale(const D3DXVECTOR3& inScale);
	const D3DXVECTOR3& GetScale() const { return m_scale; }

	/* 回転系統 */
	void SetRot(const D3DXVECTOR3& inRot) override;
	void SetMtxRot(const D3DXVECTOR3& inRot);
	void SetMtxRot(const D3DXMATRIX& inRot) { m_mtxRot = inRot; }
	void SetMtxQuaternion(const D3DXQUATERNION& inQuaternion) { D3DXMatrixRotationQuaternion(&m_mtxRot, &inQuaternion); }
	const D3DXMATRIX& GetMtxRot() { return m_mtxRot; }

	/* 頂点位置 */
	void CalculationVtx();	// 頂点最大小値の計算
	void SetMaxVtx(const D3DXVECTOR3& Maxvtx) { m_maxVtx = Maxvtx; }	// 頂点最大値設定
	const D3DXVECTOR3& GetMaxVtx() { return m_maxVtx; }					// 頂点最大値取得
	void SetMinVtx(const D3DXVECTOR3& Minvtx) { m_maxVtx = Minvtx; }	// 頂点最大値設定
	const D3DXVECTOR3& GetMinVtx() { return m_minVtx; }					// 頂点最小値取得

	/* 親子関係 */
	void SetParent(CObjectX* inParent) { m_parent = inParent; }	// 親モデルの設定
	CObjectX* GetParent() const { return m_parent; }				// 親モデルの取得

	/* マテリアル関係 */
	void SetMaterialDiffuse(unsigned int index, const D3DXCOLOR& inColor);
	const D3DXCOLOR& GetMaterialDiffuse(unsigned int index) { return m_materialDiffuse.at(index); }

	/* 透明度 */
	void SetColorAlpha(float inAlpha) { m_color.a = inAlpha; }

	/* OutLine */
	void AttachOutLine(bool isAttach = true) { m_isHasOutLine = isAttach; }
	/* Shadow */
	void AttachShadow(bool isAttach = true) { m_isHasShadow = isAttach; }

	/* 当たり判定 */
	bool SphereAndAABB(CObjectX* inObjectX,D3DXVECTOR3* outPos = nullptr);
	bool RayAndAABB(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inNormal, D3DXVECTOR3* outPos = nullptr);
	bool SegmentAndAABB(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inPos2, D3DXVECTOR3* outPos = nullptr);

	float AABBAndPointLength(CObjectX* inObject, D3DXVECTOR3* outDist = nullptr);

private:
	//--------------------------------------------------------------
	// メンバー変数
	//--------------------------------------------------------------
	D3DXVECTOR3 m_scale;		// 大きさ倍率

	D3DXVECTOR3 m_minVtxOrigin;	// モデルの頂点最小値デフォルト値
	D3DXVECTOR3 m_maxVtxOrigin;	// モデルの頂点最大値デフォルト値
	D3DXVECTOR3 m_minVtx;		// モデルの頂点最小値
	D3DXVECTOR3 m_maxVtx;		// モデルの頂点最大値

	D3DXMATRIX m_mtxRot;		// 回転行列

	LPD3DXMESH m_mesh;			// メッシュ情報へのポインタ
	LPD3DXBUFFER m_buffMat;	// マテリアル情報へのポインタ
	std::unordered_map<unsigned int,D3DXCOLOR> m_materialDiffuse;	// マテリアルのDiffuse
	DWORD m_numMat;				// マテリアル情報の数

	CObjectX *m_parent;		// 親モデルの情報
	bool m_isCollision;		// 当たり判定が必要か

	bool m_isHasOutLine;	// アウトラインを使うか
	bool m_isHasShadow;		// アウトラインを使うか

	bool m_isBlackFlash;

	std::string modelKey;
};
#endif