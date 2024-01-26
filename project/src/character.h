//**************************************************************
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
#include "abnormal_data_base.h"
#include <array>

//==============================================================
// 前方宣言
//==============================================================
class CCollisionCylinder;
class CCollisionBox;
class CSkill;
class CAbnormal;
class CSkinMesh;

//==============================================================
// プレイヤークラス
//==============================================================
class CCharacter : public CObject
{
public:

	static const int MAX_SKILL;
	static const int MAX_NON_COMBAT_TIME;

	enum class ERelation
	{
		FRIENDLY,	// 友好的
		HOSTILE,	// 敵対的
		MAX
	};

	// 今いる場所
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
	void	Update() override;
	void	Draw() override;

	void SetPos(const D3DXVECTOR3& inPos);
	void SetRot(const D3DXVECTOR3& inRot);

	CCollisionCylinder* GetCollision() { return m_collision; }

	virtual void TakeItem(int id);	// アイテムを拾う

	// 攻撃
	void DealDamage(CCharacter* inChara, float SkillMul);
	virtual void TakeDamage(const int inDamage, CCharacter* inChara);
	virtual void AbDamage(const int inDamage);
	int CalDamage(float SkillAtkMul);
	void AddDamage(float inDamage) { m_addDamage = inDamage; }

	// 回復
	void Regenation();
	void Heal(int heal);
	void RatioHeal(float heal);

	// スキルの取得
	std::vector<CSkill*> GetSkill() { return m_skill; }	// 複数
	CSkill* GetSkill(int num) { return m_skill[num]; }	// 単体

	// 死亡状態か否か。
	bool IsDied() { return m_isDied; }
	virtual void Died();

	// 描画をきる
	void SetDisplay(bool display) override;

	// 状態異常
	int GetAbnormalTypeCount();	// 状態異常の種類のカウント
	virtual void AddAbnormalStack(const int id,const int cnt = 1) { m_haveAbnormal[id].s_Time.push_back(0); m_haveAbnormal[id].s_stack += cnt; }
	void SetInterval(const int id, const int Time) { m_haveAbnormal[id].s_interval = Time; }
	void SetAbnormalTime(const int id, const int Time) { m_haveAbnormal[id].s_effectTime = Time; }
	void SetTargetInterval(const int id, const int MAXTIME) { m_haveAbnormal[id].s_target_interval = MAXTIME; }
	abnormal_count GetAbnormalCount() { return m_haveAbnormal; }		// 受けてる状態異常

	// レベル
	void SetLevel(int level);
	void AddExp(int exp);
	void AddLevel();
	int GetLevel() { return m_level; }

	//==============================================================
	// ステータス
	//==============================================================
	// 体力
	void SetHp(CStatus<int> hp) { m_hp = hp; }
	CStatus<int>* GetHp() { return &m_hp; }	// HP
	CStatus<int>* GetAddHp() { return &m_addHp; }	// 追加HP
	CStatus<int>* GetAddHpSub() { return &m_addHpSubTime; }	// 追加HPの減少時間
	CStatus<int>* GetBarrier() { return &m_barrier; }	// バリア
	CStatus<unsigned int>* GetBarrierRepopTime() { return &m_barrierRePopTime; }	// バリアの回復時間

	// 攻撃
	CStatus<unsigned int>* GetAtk() { return &m_attack; }	// 攻撃力
	CStatus<float>* GetAtkSpd() { return &m_attackSpeed; }	// 攻撃速度
	CStatus<int>* GetDefense() { return &m_defense; }		// 防御力

	// クリティカル
	CStatus<float>* GetCriticalRate() { return &m_criticalRate; }	// クリティカル率
	CStatus<float>* GetCriticalDamage() { return &m_criticalDamage; }	// クリティカルダメージ
	CStatus<float>* GetSpeed() { return &m_movePower; }	// 移動速度

	// 行動
	CStatus<unsigned int>* GetJumpCount() { return &m_jumpCount; }	// ジャンプ回数
	void SetJumpPower(CStatus<float> jump) { m_jumpPower = jump; }
	CStatus<float>* GetJumpPower() { return &m_jumpPower; }	// ジャンプ力

	CStatus<int>* GetMoney() { return &m_money; }	// 所持金

	ERelation GetRelation() { return m_relation; }	// 関係

	// 状態の取得
	bool GetIsShield() { return m_isShield; }		// シールド回復するかどうか
	bool GetIsCritical() { return m_isCritical; }	// クリティカルかどうか
	int GetNumCritical() { return m_numCritical; }	// クリティカルヒットした数
	bool GetIsNonCombat() { return m_nonCombat; }	// 非戦闘時かどうか
	bool GetIsRunning() { return m_isRunning; }		// 走っているかどうか

	void DamageBlock(bool isBlock) { m_isBlock = isBlock; }
	void SetStun(bool isStun) { m_isStun = isStun; }

	// エリートかどうか
	bool GetIsElite() { return m_isElite; }
	void SetIsElite() { m_isElite = true; }

	// テレポーターを起動したかどうか
	bool GetIsTeleporter() { return m_isTeleporter; }
	void SetIsTeleporter(bool isTeleporter) { m_isTeleporter = isTeleporter; }
  
	// 攻撃の当たり判定を行なうかどうか
	void SetIsAtkCollision(bool is) { m_isAtkCollision = is; }
	bool GetIsAtkCollision() { return m_isAtkCollision; }

	// 向いている向きを変える方法
	void SetToFaceRot(bool is) { m_isToFaceRot = is; RotateToFace(); }

	// 前方に進む力
	float GetForwardJumpPoewer() { return m_forwardJumpPoewer; }
	void SetForwardJumpPoewer(float inForwardJumpPoewer) { m_forwardJumpPoewer = inForwardJumpPoewer; }

	// 効果時間の設定
	void SetEffectTime(int inEffectTime) { m_effectTime = inEffectTime; }

	// 加速する値
	void SetAcceleration(float inAcceleration) { m_acceleration = inAcceleration; }
	
	//　非戦闘時に加速する値
	void SetNonComAddSpeed(float inNonComAddSpeed) { m_nonComAddSpeed = inNonComAddSpeed; }

	// 加速中かどうか
	void SetIsAccel(bool is) { m_isAccel = is; }
	bool GetIsAccel() { return m_isAccel; }

	// アイテムの移動量
	D3DXVECTOR3 GetItemMove() { return m_itemMove; }
	void SetItemMove(D3DXVECTOR3 inItemMove) { m_itemMove = inItemMove; }

	// 今いる場所
	STATE GetState() { return m_state; }

	// 移動制御
	void SetMoveLock(bool isLock) { m_isMoveLock = isLock; }
	bool GetMoveLock() { return m_isMoveLock; }
	void SetControlLock(bool isLock) { m_isControl = isLock; }
	bool GetControlLock() { return m_isControl; }
	void SetInertiaMoveLock(bool isLock) { m_isInertiaMoveLock = isLock; }	// 慣性・重力
	bool GetInertiaMoveLock() { return m_isInertiaMoveLock; }				// 慣性・重力


	void SetIsMuteki(bool isMoteki) { m_isMuteki = isMoteki; }

protected:
	virtual void RotateToFace();	// 向いている向きを回転させる
private:
	virtual void Move();	// 移動
	void Abnormal();		// 状態異常
	void Collision();		// 当たり判定
	void FallDamage();		// 落下ダメージ

protected:		// メンバ変数
private:		// ステータス

protected:
	D3DXVECTOR3 m_groundPos;

	CSkinMesh* m_skinModel;		// モデルのインスタンス
	float m_destRot;
	CCollisionCylinder*	m_collision;	// 当たり判定
	CCollisionBox*	m_extrusion;	// 押し出し用
	ERelation m_relation;

	std::vector<CSkill*> m_skill;

	// 持っているアイテムの個数をそれぞれ管理
	item_count m_haveItem;
	// 持っている状態異常の個数をそれぞれ管理
	abnormal_count m_haveAbnormal;

	// 移動制限
	bool m_isMoveLock;			// 移動停止状態か否か。
	bool m_isControl;			// コントロールを受け付けるか否か。
	bool m_isInertiaMoveLock;	// 慣性・重力停止状態か否か

	bool m_isDied;			// 死亡状態か否か。
	bool m_isShield;		// シールドを回復するかどうか
	bool m_isCritical;		// クリティカルかどうか
	int m_numCritical;		// クリティカルヒットした数
	bool m_isBlock;			// 防御できたかできてないか
	bool m_isStun;			// スタン状態かそうでないか
	bool m_nonCombat;		// 非戦闘時
	float m_nonComAddSpeed;	// 非戦闘時に加速する値
	int m_nonCombatTime;	// 非戦闘時になる時間
	bool m_isRunning;		// 走っているかどうか
	bool m_isElite;			// エリート
	bool m_isTeleporter;	// テレポーターを起動したかどうか

	bool m_isMuteki;

	bool m_isHitDamage;			// 攻撃をうけたかどうか
	bool m_isAtkCollision;		// 攻撃を受けなくなる
	bool m_isToFaceRot;			// 向いている向きを変える方法

	float m_addDamage;

	float m_forwardJumpPoewer;	// ジャンプしたときに前方に進む力
	int m_effectTime;				// 効果時間

	float m_acceleration;		// 敵を倒したときに加速する値
	bool m_isAccel;				// 加速中かどうか

	D3DXVECTOR3 m_itemMove;

	STATE m_stateOld;
	STATE m_state;

	// ステータス
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
	CStatus<float> m_dashPower;					// 走る力
	CStatus<float> m_jumpPower;					// ジャンプ力
	CStatus<unsigned int> m_jumpCount;			// ジャンプ回数
	CStatus<int> m_money;						// 所持金
	CStatus<int> m_regenetionTime;				// 自動回復の間隔
	CStatus<int> m_regenetion;					// 自動回復の値

	int m_RegenetionCnt;

	// レベル関係
	int m_level;
	float m_exp;
	float m_reqExp;

};
#endif
