//**************************************************************
//
// XL
// Author : ûüì]
//
//**************************************************************
#ifndef _SKILL_H_			// ±Ì}Nè`ª³êÄÈ©Á½ç
#define _SKILL_H_			// ñdCN[hh~Ì}Nè`

//==============================================================
// include
//==============================================================
#include "task.h"

//==============================================================
// Oûé¾
//==============================================================
class CCharacter;
class CCollision;

//==============================================================
// XLNX
//==============================================================
class CSkill : public CTask
{
public:
	// RXgN^ÆfXgN^
	explicit CSkill(int nPriority = 3);
	~CSkill();

	//vg^Cvé¾
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;

	// ÃIoÖ
	static CSkill	*Create();									// XLÌ¶¬

	void Skill1();												// XL1
	// Getter
	int	GetCT() { return m_CT; }

	// Setter
	void SetSkill(std::string tag, CCharacter *chara);			// XLÌÝè

private:		// oÏ
	CCharacter*		m_apChara;			// LN^[ÌCX^X
	CCollision*		m_Collision;		// ½è»è
	int				m_ID;				// XLID
	int				m_CT;				// N[^C
	float			m_Duration;			// øÊÔ
	bool			m_isCollision;		// ½ÁÄ¢é©Ç¤©	
	std::string		m_Name;				// XL¼
};
#endif