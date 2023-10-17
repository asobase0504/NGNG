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
#include "objectX.h"
#include "item_data.h"

//==============================================================
// �O���錾
//==============================================================
class CCollisionSphere;

//==============================================================
// �N���X
//==============================================================
class CItemModel : public CObjectX
{
private:
	static const float TAKE_RANGE;
public:
	CItemModel(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CItemModel();

	HRESULT Init() override;
	HRESULT Init(int inId);
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CItemModel* Create(const D3DXVECTOR3& inPos, int inId);

	CCollisionSphere* GetCollision() { return m_collision; }

	int GetID() { return m_ID; }

private:
	// �A�C�e���̃��f���f�[�^
	int m_ID;
	std::string m_modelData[ITEM_MAX];
	CCollisionSphere* m_collision;
};
#endif	// _ITEM_MODEL_H_