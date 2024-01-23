//**************************************************************
//
// HPバー
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "take_item_ui.h"
// 描画物
#include "object2d.h"
#include "text_object.h"

//==============================================================
// include
//==============================================================
const D3DXVECTOR2 CTakeItemUI::CENTER_POS	(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - 75.0f);	// 中心座標
const D3DXVECTOR2 CTakeItemUI::ICON_POS		(-140.0f, 0.0f);	// アイコン位置
const D3DXVECTOR2 CTakeItemUI::NAME_POS		(-117.5f, -25.0f);	// 名前位置
const D3DXVECTOR2 CTakeItemUI::TEXT_POS		(-110.0f, 0.0f);	// テキスト位置
const int CTakeItemUI::DISPLAY_TIME = 180;		// 表示時間

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CTakeItemUI::CTakeItemUI(CTaskGroup::EPriority list) :
	m_displayCnt(0)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CTakeItemUI::~CTakeItemUI()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CTakeItemUI::Init()
{
	CObject::Init();
	m_displayCnt = 0;

	m_ground = CObject2d::Create(CTaskGroup::LEVEL_2D_UI);
	m_ground->SetPos((D3DXVECTOR3)CENTER_POS);
	m_ground->SetSize(D3DXVECTOR3(200.0f,50.0f,0.0f));
	m_ground->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.15f));
	SetEndChildren(m_ground);

	m_itemIcon = CObject2d::Create(CTaskGroup::LEVEL_2D_UI);
	m_itemIcon->SetPos((D3DXVECTOR3)(CENTER_POS + ICON_POS));
	m_itemIcon->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	SetEndChildren(m_itemIcon);
	return S_OK;
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CTakeItemUI::Update()
{
	// 表示時間分、描画したら
	if (m_displayCnt >= DISPLAY_TIME)
	{
		m_displayCnt = 0;
		Uninit();
	}

	m_displayCnt++;
}

//--------------------------------------------------------------
// 拾ったアイテムの設定
//--------------------------------------------------------------
void CTakeItemUI::SetTakeItem(CItemDataBase::EItemType inType)
{
	CItemDataBase* itemData = CItemDataBase::GetInstance();
	m_name = CText::Create(D3DXVECTOR3(CENTER_POS + NAME_POS), D3DXVECTOR3(15.0f, 15.0f, 0.0f), 0, 0, itemData->GetItemName(inType).c_str());
	SetEndChildren(m_name);

	m_text = CText::Create(D3DXVECTOR3(CENTER_POS + TEXT_POS), D3DXVECTOR3(7.5f, 7.5f, 0.0f), 0, 0, itemData->GetItemMemo(inType).c_str());
	SetEndChildren(m_text);

	m_itemIcon->SetTexture(itemData->GetItemIconTextureKey(inType));
}
