//**************************************************************
//
// HP�o�[
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "take_item_ui.h"
// �`�敨
#include "object2d.h"
#include "text_object.h"

//==============================================================
// include
//==============================================================
const D3DXVECTOR2 CTakeItemUI::CENTER_POS	(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - 75.0f);	// ���S���W
const D3DXVECTOR2 CTakeItemUI::ICON_POS		(-140.0f, 0.0f);	// �A�C�R���ʒu
const D3DXVECTOR2 CTakeItemUI::NAME_POS		(-117.5f, -25.0f);	// ���O�ʒu
const D3DXVECTOR2 CTakeItemUI::TEXT_POS		(-110.0f, 0.0f);	// �e�L�X�g�ʒu
const int CTakeItemUI::DISPLAY_TIME = 180;		// �\������

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CTakeItemUI::CTakeItemUI(CTaskGroup::EPriority list) :
	m_displayCnt(0)
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CTakeItemUI::~CTakeItemUI()
{
}

//--------------------------------------------------------------
// ������
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
// �X�V
//--------------------------------------------------------------
void CTakeItemUI::Update()
{
	// �\�����ԕ��A�`�悵����
	if (m_displayCnt >= DISPLAY_TIME)
	{
		m_displayCnt = 0;
		Uninit();
	}

	m_displayCnt++;
}

//--------------------------------------------------------------
// �E�����A�C�e���̐ݒ�
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
