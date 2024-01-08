//**************************************************************
//
// スキル
// Author : 髙野馨將
//
//**************************************************************
#ifndef _SKILL_H_			// このマクロ定義がされてなかったら
#define _SKILL_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "task.h"

//==============================================================
// 前方宣言
//==============================================================
class CCharacter;

//==============================================================
// スキルクラス
//==============================================================
class CSkill : public CTask
{
public:
	// コンストラクタとデストラクタ
	explicit CSkill();
	~CSkill();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Update() override;

	// 静的メンバ関数
	static CSkill* Create();	// 生成

	bool Use();	//使用

	// Getter
	int	GetCT() { return m_CT; }
	int GetStock() { return m_stock; }
	int GetMaxStock() { return m_stockMax; }

	// Setter
	void SetSkill(std::string tag, CCharacter *chara);		// スキルの設定
	void SetCT(int ct) { m_CT = ct; }

	std::string GetName() { return m_Name; }

private:		// メンバ変数
	CCharacter*		m_apChara;			// キャラクターのインスタンス
	int				m_CT;				// クールタイム
	float			m_Duration;			// 効果時間
	float			m_atkSpd;			// 攻撃速度
	bool			m_isCollision;		// 当たっているかどうか
	int m_stockMax;
	int m_stock;
	std::string		m_Name;				// スキル名
};
#endif