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
class CCollision;

//==============================================================
// スキルクラス
//==============================================================
class CSkill : public CTask
{
public:
	// コンストラクタとデストラクタ
	explicit CSkill(int nPriority = 3);
	~CSkill();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;

	// 静的メンバ関数
	static CSkill	*Create();									// スキルの生成

	void Skill1();												// スキル1
	// Getter
	int	GetCT() { return m_CT; }

	// Setter
	void SetSkill(std::string tag, CCharacter *chara);			// スキルの設定
	void SetCT(int ct) { m_CT = ct; }

private:		// メンバ変数
	CCharacter*		m_apChara;			// キャラクターのインスタンス
	CCollision*		m_Collision;		// 当たり判定
	int				m_CT;				// クールタイム
	float			m_Duration;			// 効果時間
	bool			m_isCollision;		// 当たっているかどうか	
	std::string		m_Name;				// スキル名
};
#endif