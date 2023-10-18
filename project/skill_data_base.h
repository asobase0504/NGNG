//**************************************************************
//
// �X�L���f�[�^�x�[�X
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _SKILL_DATA_BASE_H_			// ���̃}�N����`������ĂȂ�������
#define _SKILL_DATA_BASE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include <unordered_map>

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
		int		CT;				// �N�[���^�C��
		int		stock;			// �X�g�b�N
		int		duration;		// ���ʎ���
		float	damage;			// �_���[�W��
		float	KnockBack;		// �m�b�N�o�b�N��
	};

	struct SKILL_INFO
	{
		BASE baseInfo;
		ABILITY ability;
		ABILITY abilityHit;
	};

	enum SKILL_TYPE
	{
		YAMATO_ATTACK
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
	SKILL_INFO GetInfo(std::string tag) { return m_skillDataBase[tag]; }
	ABILITY GetAbility(std::string tag) { return m_skillDataBase[tag].ability; }
	ABILITY GetHitAbility(std::string tag) { return m_skillDataBase[tag].abilityHit; }
	int GetCT(std::string tag) { return m_skillDataBase[tag].baseInfo.CT; }
	int GetStock(std::string tag) { return m_skillDataBase[tag].baseInfo.stock; }
	int GetDuration(std::string tag) { return m_skillDataBase[tag].baseInfo.duration; }
	float GetDamage(std::string tag) { return m_skillDataBase[tag].baseInfo.damage; }
	float GetKnockBack(std::string tag) { return m_skillDataBase[tag].baseInfo.KnockBack; }

private:	// �����o�ϐ�
	std::unordered_map<std::string, SKILL_INFO> m_skillDataBase;
};
#endif