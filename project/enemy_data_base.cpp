//**************************************************************
//
// �G�l�~�[�f�[�^�x�[�X
// Author : YudaKaito
//
//**************************************************************

// �}�N����`
#define UPDATE_FUNC_CAST(func) (static_cast<void(CEnemyDataBase::*)()>(&(func)))

//==============================================================
// include
//==============================================================
#include "enemy_data_base.h"

CEnemyDataBase::CEnemyDataBase()
{
}

CEnemyDataBase::~CEnemyDataBase()
{
}

void CEnemyDataBase::Activity_Idel()
{
}
