//**************************************************************
//
// 選択できる実体
// Author: Yuda Kaito
//
//**************************************************************
#ifndef _SELECT_ENTITY_H_
#define _SELECT_ENTITY_H_

//==============================================================
// include
//==============================================================
#include "objectX.h"

//==============================================================
// 前方宣言
//==============================================================
class CCollisionCylinder;
class CCollisionBox;
class CCharacter;
class CSelectUI;
class CProcedure3D;

//==============================================================
// クラス
//==============================================================
class CSelectEntity : public CObjectX
{
public:
	CSelectEntity();
	~CSelectEntity();

	HRESULT Init() override;

	void Update() override;

	CCollisionCylinder* GetSelectCollision() { return m_collisionCylinder; }
	CCollisionBox* GetCollisionBox() { return m_collisionBox; }

	void DisplayUI();
	void NoDisplayUI() { m_isNearCharacter = false; }

	virtual bool Select(CCharacter* selectCharacter) = 0;	// 選ばれた時の処理

	CProcedure3D* GetCostUI() { return m_costUI; }

protected:
	CCollisionCylinder* m_collisionCylinder;	// 選択できる当たり判定
	CCollisionBox* m_collisionBox;				// 押し出しを行なう当たり判定
	CSelectUI* m_ui;
	CProcedure3D* m_costUI;	//コストを3D空間状に描画
	std::string m_uiText;
	bool m_isNearCharacter;		// キャラクターに一番近いエンティティであるか否か
};
#endif	// _ITEM_MODEL_H_
