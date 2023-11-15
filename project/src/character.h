﻿//**************************************************************
//
// キャラクター
// Author : 梶田大夢
//
//**************************************************************
#ifndef _CHARACTER_H_			// このマクロ定義がされてなかったら
#define _CHARACTER_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "object.h"
#include "status.h"
#include "item_data_base.h"
#include "road.h"
#include "abnormal_data_base.h"
#include <array>

//==============================================================
// 前方宣言
//==============================================================
class CObjectX;
class CCollisionCylinder;
class CRoad;
class CAbnormal;

//==============================================================
// プレイヤークラス
//==============================================================
class CCharacter : public CObject
{
public:
	enum STATE
	{
		NONE = -1,
		GROUND,
		SKY,
		MAX
	};
public:
	// コンストラクタとデストラクタ
	explicit CCharacter(int nPriority = 3);
	~CCharacter();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// 静的メンバ関数
	static CCharacter *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// プレイヤーの生成

	CCollisionCylinder* GetCollision() { return m_collision; }

	std::vector<CObjectX*> GetModel() { return m_apModel; }

	// 状態異常の種類のカウント
	int GetAbnormalTypeCount();

	void Damage(const int inDamage);
  
	void SetPos(const D3DXVECTOR3& inPos);
	void SetRot(const D3DXVECTOR3& inRot);
	void AddUbnormalStack(const int id) { m_haveAbnormal[id].s_Time.push_back(0); m_haveAbnormal[id].s_stack++;}
	void SetInterval(const int id, const int Time) { m_haveAbnormal[id].s_interval = Time; }
	void SetUbnormalTime(const int id, const int Time) { m_haveAbnormal[id].s_effectTime = Time; }
	void SetTargetInterval(const int id, const int MAXTIME) { m_haveAbnormal[id].s_target_interval = MAXTIME; }
	void SetAttackAbnormal(const int id, bool onoff) { m_attackAbnormal[id] = onoff; }
	void DamageBlock(bool isBlock) { m_isBlock = isBlock; }
	void SetStun(bool isStun) { m_isStun = isStun; }

	int CalDamage(float SkillAtkMul);

	//==============================================================
	// ゲッターとセッター
	//==============================================================
	// ジャンプ回数
	CStatus<unsigned int>* GetJumpCount() { return &m_jumpCount; }

	// バリアの回復時間
	CStatus<unsigned int>* GetBarrierRepopTime() { return &m_barrierRePopTime; }

	// 攻撃力
	CStatus<unsigned int>* GetAtk() { return &m_attack; }

	// 攻撃速度
	CStatus<float>* GetAtkSpd() { return &m_attackSpeed; }
	
	// HP
	CStatus<int>* GetHp() { return &m_hp; }
	void SetHp(CStatus<int> hp) { m_hp = hp; }

	// 追加HP
	CStatus<int>* GetAddHp() { return &m_addHp; }

	// 追加HPの減少時間
	CStatus<int>* GetAddHpSub() { return &m_addHpSubTime; }

	// バリア
	CStatus<int>* GetBarrier() { return &m_barrier; }

	// 防御力
	CStatus<int>* GetDefense() { return &m_defense; }

	// クリティカル率
	CStatus<float>* GetCriticalRate() { return &m_criticalRate; }

	// クリティカルダメージ
	CStatus<float>* GetCriticalDamage() { return &m_criticalDamage; }

	// 移動速度
	CStatus<float>* GetSpeed() { return &m_movePower; }
	
	// ジャンプ力
	CStatus<float>* GetJumpPower() { return &m_jumpPower; }
	void SetJumpPower(CStatus<float> jump) { m_jumpPower = jump; }

	// 所持金
	CStatus<int>* GetMoney() { return &m_money; }

	// 攻撃の道
	CRoad* GetRoad() { return m_road; }

	// 状態異常
	abnormal_count GetAbnormalCount() { return m_haveAbnormal; }
	// 与える状態異常
	abnormal_attack GetAbnormalAttack() { return m_attackAbnormal; }

	// 攻撃
	void Attack(CCharacter* pEnemy, float SkillMul);
	void Abnormal();
	bool IsDied() { return m_isDied; }
	void Died() { m_isDied = true; }
  
private:
	virtual void Move();
	void UpdatePos();			// 座標の更新

protected:		// メンバ変数
	std::vector<CObjectX*>		m_apModel;		// モデルのインスタンス
	CCollisionCylinder*	m_collision;			// 当たり判定
private:		// メンバ変数

protected:		// ステータス

	// 持っているアイテムの個数をそれぞれ管理
	item_count m_haveItem;
	// 持っている状態異常の個数をそれぞれ管理
	abnormal_count m_haveAbnormal;
	// 与える状態異常を管理
	abnormal_attack m_attackAbnormal;

	bool m_isBlock;	// 防御できたかできてないか
	bool m_isDied;	// 死亡状態か否か。
	bool m_isStun;	// スタン状態かそうでないか
	STATE m_state;

	CStatus<int> m_hp;							// 体力
	CStatus<int> m_addHp;						// 追加体力
	CStatus<int> m_addHpSubTime;				// 追加体力の減少量
	CStatus<int> m_barrier;						// バリア
	CStatus<unsigned int> m_barrierRePopTime;	// バリアの復活時間
	CStatus<unsigned int> m_attack;				// 攻撃力
	CStatus<int> m_defense;						// 防御力
	CStatus<float> m_attackSpeed;				// 攻撃速度
	CStatus<float> m_criticalRate;				// クリティカル率
	CStatus<float> m_criticalDamage;			// クリティカルダメージ
	CStatus<float> m_movePower;					// 移動力
	CStatus<float> m_jumpPower;					// ジャンプ力
	CStatus<unsigned int> m_jumpCount;			// ジャンプ回数
	CStatus<int> m_money;						// 所持金

	CRoad* m_road;								// 攻撃の道みたいな
};
#endif
