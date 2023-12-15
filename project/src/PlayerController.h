//**************************************************************
// Controller
// プレイヤークラス
// Author YudaKaito
// 
//**************************************************************
#ifndef _PLAYER_OPERATE_H_
#define _PLAYER_OPERATE_H_

#include "controller.h"

//--------------------------------------------------------------
// プレイヤークラス
//--------------------------------------------------------------
class CPlayerController : public CController
{
public:
	CPlayerController(int inInputIndex);
	~CPlayerController() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	D3DXVECTOR3 Move() override;

	bool		Jump() override;
	bool		Dash(bool dash) override;
	bool		Skill_1() override;
	bool		Skill_2() override;
	bool		Skill_3() override;
	bool		Skill_4() override;
	int			TakeItem() override;
	bool		Select();

private:
	int m_nInputIdx;
};

#endif // !_PLAYER_OPERATE_H_
