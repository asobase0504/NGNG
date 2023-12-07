//**************************************************************
//
// 敵
// Author : 梶田大夢
//
//**************************************************************
#ifndef _ENEMY_H_			// このマクロ定義がされてなかったら
#define _ENEMY_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "character.h"

//==============================================================
// マクロ宣言
//==============================================================
#define MAX_SPEED	(0.3f)

//==============================================================
// 前方宣言
//==============================================================
class CObjectX;
class CController;
class CCollisionBox;
class CCollisionSphere;
class CEnemyDataBase;
class CEnemy_HPUI;

//==============================================================
// 敵クラス
//==============================================================
class CEnemy : public CCharacter
{
public:
	using ACTIVITY_FUNC = std::function<void(CEnemy*)>;
public:
	// コンストラクタとデストラクタ
	explicit CEnemy(int nPriority = 3);
	~CEnemy();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Update() override;

	// 静的メンバ関数
	void SetActivity(ACTIVITY_FUNC NowAct) { m_Activity = NowAct; }
	ACTIVITY_FUNC GetActivity() { return m_Activity; }

	// 攻撃カウントの加算
	void SetAttackCnt(int Cnt) { m_AttackCnt = Cnt; }
	void AddAttackCnt(int Cnt) { m_AttackCnt += Cnt; }
	int GetAttackCnt() { return m_AttackCnt; }

	// 死亡時の処理
	void Died() override;

private:
	void Move();		// 移動

private:	// メンバ変数
	ACTIVITY_FUNC	m_Activity;
	int				m_AttackCnt;
	CEnemy_HPUI*	m_pEHPUI;
	int				m_dropMoney;
};
#endif