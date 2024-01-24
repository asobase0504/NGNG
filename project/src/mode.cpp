//**************************************************************
//
// モード
// Author:Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "mode.h"
#include "map.h"
#include "map_fade.h"

#include "player_manager.h"

//==============================================================
// マップの作成
//==============================================================
void CMode::CreateMap(std::string inPath)
{
	if (m_map != nullptr)
	{
		m_map->Uninit();
		m_map = nullptr;
	}

	m_map = new CMap;
	m_map->Load(inPath);
	m_map->Init();

	m_mapFade = CMapFade::Create();
}

void CMode::ChangeMap()
{
	CPlayerManager::GetInstance()->GetPlayer()->OffUpdate();
	CreateMap(m_map->GetNextMapPath());
}
