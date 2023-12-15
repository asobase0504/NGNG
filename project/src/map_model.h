//**************************************************************
//
// マップのモデル
// Author: Buriya Kota
//
//**************************************************************
#ifndef _MAP_MODEL_H_
#define _MAP_MODEL_H_

//==============================================================
// include
//==============================================================
#include "objectX.h"

//==============================================================
// 前方宣言
//==============================================================
class CCollisionBox;

//==============================================================
// クラス
//==============================================================
class CMapModel : public CObjectX
{
public:
	CMapModel();
	~CMapModel();

	HRESULT Init() override;
	HRESULT Init(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot, const D3DXVECTOR3& inSize);
	void Update() override;
	void Draw() override;

	static CMapModel* Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot, const D3DXVECTOR3& inSize);
	CCollisionBox* GetCollisionBox() { return m_collisionBox; }

private:
	CCollisionBox* m_collisionBox;
};
#endif	// _MAP_MODEL_H_
