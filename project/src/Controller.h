//=========================================
// 
// �v���C���[�N���X
// Author YudaKaito
// 
//=========================================
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

//-----------------------------------------
// include
//-----------------------------------------
#include <d3dx9.h>
#include "Player.h"

//-----------------------------------------
// �I�y���[�^�[�N���X
//-----------------------------------------
class CController
{
public:
	CController();
	virtual ~CController();

	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();

	virtual D3DXVECTOR3 Move() = 0;
	virtual bool		Jump() = 0;
	virtual bool		Dash() = 0;

	// Setter
	void SetToOrder(CPlayer* inOrder) { m_toOrder = inOrder; }
protected:
	CPlayer* m_toOrder;	// ���ߐ�
	int chargeCount;
};

#endif // !_OPERATE_H_
