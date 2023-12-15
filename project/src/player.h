//**************************************************************
//
// プレイヤー
// Author : 髙野馨將
//
//**************************************************************
#ifndef _PLAYER_H_			// このマクロ定義がされてなかったら
#define _PLAYER_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "character.h"
#include "collision_cylinder.h"

//==============================================================
// 前方宣言
//==============================================================
class CController;
class CCollisionCylinder;
class CPlayerAbnormalUI;

//==============================================================
// プレイヤークラス
//==============================================================
class CPlayer : public CCharacter
{
public:
	// コンストラクタとデストラクタ
	explicit CPlayer(int nPriority = 5);
	~CPlayer();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;

	// 静的メンバ関数
	static CPlayer *Create(D3DXVECTOR3 pos);			// プレイヤーの生成

	// Setter
	void SetController(CController* inOperate);
	void SetPos(const D3DXVECTOR3& inPos);

	void OnUpdate() { m_isUpdate = true; }
	void OffUpdate() { m_isUpdate = false; }

	void TakeItem(int id) override;	// アイテムを拾う

	void AddAbnormalStack(const int id, const int cnt = 1) override;

private:
	void PAttack();		// 攻撃
	void Move();		// 移動
	void Jump();		// ジャンプ
	void Select();		// 選ぶ

private:		// メンバ変数
	bool			m_isjump;		// ジャンプしているかどうか
	bool			m_isdash;		// ダッシュしているかどうか
	bool			m_isskill;		// スキルを使用しているかどうか
	bool			m_isUpdate;		// 更新を止めるか否か。
	bool			m_isResult;		// リザルト中か否か

	CController*	m_controller;	// 命令を出す人

	// UI
	std::list<CPlayerAbnormalUI*> m_abnormalUI;	// 状態異常やバフなどのアイコンを表示
};
#endif