//**************************************************************
//
// XL
// Author : ûüì]
//
//**************************************************************
#ifndef _SKILLENTITY_H_			// ±Ì}Nè`ª³êÄÈ©Á½ç
#define _SKILLENTITY_H_			// ñdCN[hh~Ì}Nè`

//==============================================================
// include
//==============================================================
#include "skill.h"

//==============================================================
// Oûé¾
//==============================================================
class CCharacter;

//==============================================================
// XLNX
//==============================================================
class CSkillEntity : public CSkill
{
public:
	// RXgN^ÆfXgN^
	explicit CSkillEntity(int nPriority = 3);
	~CSkillEntity();

	//vg^Cvé¾
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;

	// ÃIoÖ
	static CSkillEntity *Create(D3DXVECTOR3 pos);			// XLÌ¶¬

private:		// oÏ
	CCharacter*		m_apChara;				// LN^[ÌCX^X
	int				m_ID[MAX_SKILL];		// XLID
};
#endif