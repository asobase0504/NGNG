//=========================================
// 
// プレイヤークラス
// Author YudaKaito
// 
//=========================================
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

//-----------------------------------------
// include
//-----------------------------------------
class CPlayer;

//-----------------------------------------
// オペレータークラス
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
	virtual int			TakeItem() { return -1; }
	virtual bool		Skill_1() = 0;
	virtual bool		Skill_2() = 0;
	virtual bool		Skill_3() = 0;
	virtual bool		Skill_4() = 0;

	// Setter
	void SetToOrder(CPlayer* inOrder) { m_toOrder = inOrder; }
	CPlayer* GetToOrder() { return m_toOrder; }
protected:
	CPlayer* m_toOrder;	// 命令先
	int chargeCount;
};

#endif // !_OPERATE_H_
