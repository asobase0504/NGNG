//**************************************************************
//
// NUMBER
// Author:hamada ryuuga
//
//**************************************************************
#ifndef _NUMBER_3D_H_
#define _NUMBER_3D_H_

//==============================================================
// include
//==============================================================
#include "object_polygon3d.h"

//==============================================================
// �N���X
//==============================================================
class CNumber3D : public CObjectPolygon3D
{
public:
	enum EIconType
	{
		NUMBER,		// ����
		MINUS,		// �}�C�i�X�}�[�N
		MONEY,		// �����}�[�N
		RECOVERY,	// �񕜃}�[�N
		PERCENT,	// �p�[�Z���g
	};
public:
	CNumber3D(CTaskGroup::EPriority list = CTaskGroup::EPriority::LEVEL_3D_1);
	~CNumber3D();
	HRESULT Init() override;
	static CNumber3D* Create();

	void SetNumber(int Number) { m_myNumber = Number; }

	void AttachIcon(EIconType icon);
	EIconType GetIcon() { return m_iconType; }

private:
	int m_myNumber;
	EIconType m_iconType;
};
#endif