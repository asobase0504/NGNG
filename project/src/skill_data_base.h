//**************************************************************
//
// �X�L���f�[�^�x�[�X
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _SKILL_DATA_BASE_H_			// ���̃}�N����`������ĂȂ�������
#define _SKILL_DATA_BASE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//--------------------------------------------------------------
// �O���錾
//--------------------------------------------------------------
class CCharacter;

//==============================================================
// �G�̍s���p�^�[���f�[�^�x�[�X
//==============================================================
class CSkillDataBase
{
public:
	using ABILITY = std::function<void(CCharacter*)>;

	struct BASE
	{
		int CT;
		int stock;
	};

	struct SKILL_INFO
	{
		BASE baseInfo;
		ABILITY ability;
		ABILITY abilityHit;
	};

private:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CSkillDataBase();
	static CSkillDataBase* m_instance;
public:
	static CSkillDataBase* GetInstance();
	~CSkillDataBase();
	static void Uninit();
private:
	void Init();
public:
	SKILL_INFO GetInfo(std::string tag) { return m_dates[tag]; }
	ABILITY GetAbility(std::string tag) { return m_dates[tag].ability; }
	ABILITY GetHitAbility(std::string tag) { return m_dates[tag].abilityHit; }
	int GetCT(std::string tag) { return m_dates[tag].baseInfo.CT; }
	int GetStack(std::string tag) { return m_dates[tag].baseInfo.stock; }

private:	// �����o�ϐ�

	std::unordered_map<std::string, SKILL_INFO> m_dates;
};
#endif