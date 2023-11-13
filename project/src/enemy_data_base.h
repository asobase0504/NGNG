//**************************************************************
//
// �G�̍s���p�^�[���f�[�^�x�[�X
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _ENEMY_DATA_BASE_H_			// ���̃}�N����`������ĂȂ�������
#define _ENEMY_DATA_BASE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// �O���錾
//==============================================================
class CEnemy;

//==============================================================
// �G�̍s���p�^�[���f�[�^�x�[�X
//==============================================================
class CEnemyDataBase
{
public:
	using ACTIVITY_FUNC = std::function<void(CEnemy*)>;

	enum EActivityPattern
	{
		PATTERN_STANDBY,
		PATTERN_AIR_GO,
		PATTERN_AIR_KEEP_DISTANCE,
		PATTERN_GROUND_GO,
		PATTERN_GROUND_KEEP_DISTANCE,
		PATTERN_GROUND_GO_ATTACK,
		PATTERN_GOLEM,
		PATTERN_GOLEM_LASER,
		MAX_PATTERN
	};
private:
	explicit CEnemyDataBase();
	static CEnemyDataBase* m_instance;
	void Init();
public:
	static CEnemyDataBase* GetInstance();
	~CEnemyDataBase();

	static void Uninit();
public:
	ACTIVITY_FUNC GetActivityFunc(EActivityPattern inState) { return m_activityFunc[inState]; }
private:
	
private:	// �����o�ϐ�
	std::vector<ACTIVITY_FUNC> m_activityFunc;

};
#endif