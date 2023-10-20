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
#include <array>

//==============================================================
// 前方宣言
//==============================================================
class CObjectX;
class CCollision;

//==============================================================
// プレイヤークラス
//==============================================================
class CCharacter : public CObject
{
private:		// ステータス構造体
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
	static CCharacter *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// プレイヤーの生成

	CCollision* GetCollision() { return m_collision[0]; }

	std::vector<CObjectX*> GetModel() { return m_apModel; }

	void Damege(const int inDamage);

	//==============================================================
	// ゲッターとセッター
	//==============================================================
	// ジャンプ回数
	CStatus<unsigned int> GetJumpCount() { return m_jumpCount; }
	void SetJumpCount(CStatus<unsigned int> hp) { m_jumpCount = hp; }

	// 攻撃力
	CStatus<unsigned int> GetAtk() { return m_attack; }
	void SetAtk(CStatus<unsigned int> atk) { m_attack = atk; }

	// バリアの回復時間
	CStatus<unsigned int> GetBarrierRepopTime() { return m_barrierRePopTime; }
	void SetBarrierRepopTime(CStatus<unsigned int> barrierRe) { m_barrierRePopTime = barrierRe; }

	// HP
	CStatus<int> GetHp() { return m_hp; }
	void SetHp(CStatus<int> hp) { m_hp = hp; }

	// 追加HP
	CStatus<int> GetAddHp() { return m_addHp; }
	void SetAddHp(CStatus<int> addHp) { m_addHp = addHp; }

	// 追加HPの減少時間
	CStatus<int> GetAddHpSub() { return m_addHpSubTime; }
	void SetAddHpSub(CStatus<int> addHpsub) { m_addHpSubTime = addHpsub; }

	// バリア
	CStatus<int> GetBarrier() { return m_barrier; }
	void SetBarrier(CStatus<int> barrier) { m_barrier = barrier; }

	// 防御力
	CStatus<int> GetDeffence() { return m_defense; }
	void SetDefence(CStatus<int> def) { m_defense = def; }

	// クリティカル率
	CStatus<float> GetCriticalRate() { return m_criticalRate; }
	void SetCriticalRate(CStatus<float> crtrate) { m_criticalRate = crtrate; }

	// クリティカルダメージ
	CStatus<float> GetCriticalDamage() { return m_criticalDamage; }
	void SetCriticalDamage(CStatus<float> cridmg) { m_criticalDamage = cridmg; }

	// 移動速度
	CStatus<float> GeSpeed() { return m_movePower; }
	void SetSpeed(CStatus<float> move) { m_movePower = move; }

	// ジャンプ力
	CStatus<float> GetJumpPower() { return m_jumpPower; }
	void SetJumpPower(CStatus<float> jump) { m_jumpPower = jump; }

private:
	virtual void Attack();
	virtual void Move();
	void UpdatePos();			// 座標の更新

protected:		// メンバ変数
	std::vector<CObjectX*>		m_apModel;		// モデルのインスタンス
	std::vector<CCollision*>	m_collision;	// 当たり判定
private:		// メンバ変数
	D3DXMATRIX		m_mtxWorld;					// ワールドマトリックス

protected:		// ステータス

	// 持っているアイテムの個数をそれぞれ管理
	item_count m_haveItem;

	CStatus<int> m_hp;							// 体力
	CStatus<int> m_addHp;						// 追加体力
	CStatus<int> m_addHpSubTime;				// 追加体力の減少量
	CStatus<int> m_barrier;						// バリア
	CStatus<unsigned int> m_barrierRePopTime;	// バリアの復活時間
	CStatus<unsigned int> m_attack;				// 攻撃力
	CStatus<int> m_defense;						// 防御力
	CStatus<float> m_criticalRate;				// クリティカル率
	CStatus<float> m_criticalDamage;			// クリティカルダメージ
	CStatus<float> m_movePower;					// 移動力
	CStatus<float> m_jumpPower;					// ジャンプ力
	CStatus<unsigned int> m_jumpCount;			// ジャンプ回数
};
#endif
