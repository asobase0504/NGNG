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
class CCollision;
class CSkillEntity;
class CSkill;

//==============================================================
// �G�̍s���p�^�[���f�[�^�x�[�X
//==============================================================
class CSkillDataBase
{
public:
	using ABILITY = std::function<CSkillEntity*(CCharacter*)>;

	struct BASE
	{
		int				CT;				// �N�[���^�C��
		int				stock;			// �X�g�b�N��
		float			damage;			// �_���[�W��
		float			knockback;		// �m�b�N�o�b�N��
		float			duration;		// ��������
		float			interval;		// ���i�q�b�g�̏ꍇ���̓����蔻����o��������܂ł̎���
		float			deceleration;	// ������
		float			invincible;		// ���G����
		D3DXVECTOR3		size;			// �����蔻��̑傫��
	};

	struct SKILL_INFO
	{
		BASE baseInfo;
		ABILITY ability;
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
	SKILL_INFO	GetInfo(std::string tag) { return m_dates[tag]; }
	ABILITY		GetAbility(std::string tag) { return m_dates[tag].ability; }
	int			GetCT(std::string tag) { return m_dates[tag].baseInfo.CT; }
	int			GetStack(std::string tag) { return m_dates[tag].baseInfo.stock; }
	float		GetDamage(std::string tag) { return m_dates[tag].baseInfo.damage; }
	float		GetKnockBack(std::string tag) { return m_dates[tag].baseInfo.knockback; }
	float		GetDuration(std::string tag) { return m_dates[tag].baseInfo.duration; }
	float		GetInterval(std::string tag) { return m_dates[tag].baseInfo.interval; }
	float		GetDeceleration(std::string tag) { return m_dates[tag].baseInfo.deceleration; }
	float		GetInvincible(std::string tag) { return m_dates[tag].baseInfo.invincible; }
	D3DXVECTOR3 GetSize(std::string tag) { return m_dates[tag].baseInfo.size; }

private:	// �����o�ϐ�
	CCollision *m_Collision;
	std::unordered_map<std::string, SKILL_INFO> m_dates;
};
#endif