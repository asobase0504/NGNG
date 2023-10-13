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
private:
	explicit CEnemyDataBase();
	static CEnemyDataBase* m_instance;
	void Init();
public:
	CEnemyDataBase* GetInstance();
	~CEnemyDataBase();

	static void Uninit();
public:
	ACTIVITY_FUNC GetActivityFunc(std::string inState) { return m_activityFunc[inState]; }
private:
	
private:	// �����o�ϐ�
	static std::unordered_map<std::string,ACTIVITY_FUNC> m_activityFunc;
};
#endif