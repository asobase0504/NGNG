//**************************************************************
//
// item_model
// Author: Buriya Kota
//
//**************************************************************
#ifndef _ITEM_MODEL_H_
#define _ITEM_MODEL_H_

//==============================================================
// include
//==============================================================
#include "select_entity.h"
#include "item_data_base.h"

//==============================================================
// 前方宣言
//==============================================================
class CCollisionSphere;
class CCollisionCylinder;
class CCollision;

//==============================================================
// クラス
//==============================================================
class CItemModel : public CSelectEntity
{
private:
	static const float TAKE_RANGE;
public:
	CItemModel();
	~CItemModel();

	HRESULT Init() override;
	HRESULT Init(int inId);
	void Update() override;

	bool Select(CCharacter* selectCharacter);

	static CItemModel* Create(const D3DXVECTOR3& inPos, const D3DXMATRIX& boxmtx ,int inId);

	int GetID() { return m_ID; }

	void SetVec(D3DXMATRIX mtx) { m_mtx = mtx; }
private:
	// アイテムのモデルデータ
	int m_ID;
	CCollisionCylinder* m_collisionHit;
	D3DXMATRIX m_mtx;
};
#endif	// _ITEM_MODEL_H_