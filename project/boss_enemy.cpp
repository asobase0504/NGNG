#include "boss_enemy.h"
#include "hp_ui.h"

CBossEnemy::CBossEnemy()
{
}

CBossEnemy::~CBossEnemy()
{
}

HRESULT CBossEnemy::Init()
{
	CEnemy::Init();

	return S_OK;
}

void CBossEnemy::Update()
{
	CEnemy::Update();
}
