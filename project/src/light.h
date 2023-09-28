//=============================================================================
// 
// ���C�g�̍쐬(�w�b�_�[�t�@�C��)
// Author HAMAD
// 
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "task.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define LIGTH_MAX	(5)

//=============================================================================
// ���C�g�N���X
//=============================================================================
class CLight : public CTask
{
public:
	CLight(CTaskGroup::EPriority inPriority = CTaskGroup::LEVEL_3D_1);
	~CLight();
	HRESULT Init();
	void Uninit();
	void Update();
		
	void Set(D3DLIGHTTYPE type, D3DXCOLOR col, D3DXVECTOR3 vec, int nNum);
	D3DLIGHT9 GetLight(int num) { return m_light[num]; }

	void SetLight(D3DXVECTOR3 inVec) { m_light[0].Direction = inVec; }

private:
	 D3DLIGHT9 m_light[LIGTH_MAX];	//���C�g���
};
#endif // !_LIGHT_H_
