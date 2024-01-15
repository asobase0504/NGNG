//**************************************************************
//
// 像
// Author: 梶田 大夢
//
//**************************************************************
#ifndef _STATUE_H_
#define _STATUE_H_

//==============================================================
// include
//==============================================================
#include "select_entity.h"

//==============================================================
// 前方宣言
//==============================================================
class CCollisionBox;
class CCollisionCylinder;
class CPlayer;
class CObjectPolygon3D;

//==============================================================
// クラス
//==============================================================
class CStatue : public CSelectEntity
{
public:
	CStatue();
	~CStatue();

	HRESULT Init() override;
	HRESULT Init(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot);
	void Update() override;

	CCollisionBox* GetCollisionBox() { return m_collisionBox; }

	bool Touch();

	void SetRot(const D3DXVECTOR3& inRot) override;
	void SetMark(std::string inKey);
	void DeleteMark();

private:
	void UpMesh();
	CObjectPolygon3D* m_pMark;

};
#endif	// _ITEM_MODEL_H_
