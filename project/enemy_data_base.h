//**************************************************************
//
// �G�̍s���p�^�[���f�[�^�x�[�X
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _ENEMY_DATA_BASE_H_			// ���̃}�N����`������ĂȂ�������
#define _ENEMY_DATA_BASE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// �G�̍s���p�^�[���f�[�^�x�[�X
//==============================================================
class CEnemyDataBase
{
public:
	enum ACTIVITY_STATE
	{
		ACTIVITY_IDLE = 0,
		ACTIVITY_MAX
	};

	using ACTIVITY_FUNC = void(CEnemyDataBase::*)();

public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CEnemyDataBase();
	~CEnemyDataBase();

	ACTIVITY_FUNC GetActivityFunc(ACTIVITY_STATE inState) { return m_activityFunc[inState]; }
private:
	//�@�X�L���̃X�e�[�g�֐�
	void Activity_Idel();

private:	// �����o�ϐ�
	static const ACTIVITY_FUNC m_activityFunc[];
};
#endif