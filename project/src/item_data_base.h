//**************************************************************
//
// item_data.h
// Author : Buriya HIROHITO
// 
//**************************************************************
#ifndef _ITEM_DATA_
#define _ITEM_DATA_

class CItem;

class CItemDataBase
{
public:

	enum EItemType
	{
		ITEM_NONE = -1,
		ITEM_POWER_UP,
		ITEM_POWER_ON,
		ITEM_POWER_TO,
		ITEM_DANGO,				// ����
		ITEM_SHURIKEN,			// �藠��
		ITEM_GETA,				// ����
		ITEM_UMBRELLA,			// �P
		ITEM_HYOUTAN,			// �Ђ傤����
		ITEM_BANBOO_WATERBOX,	// �|�̐���
		ITEM_OMAMORI,			// �����
		ITEM_KIBORI,			// �F�̖ؒ���
		ITEM_BAKUTIKU,			// ���|
		ITEM_MAKIBISI,			// �܂��т�
		ITEM_HEAD,				// ��
		ITEM_KUNAI,				// ���Ȃ�
		ITEM_FUR,				// �є�
		ITEM_KITUNEMEN,			// �ϖ�
		ITEM_KAZAGURUMA,		// ����
		ITEM_KOBAN,				// ����
		ITEM_ONIMEN,			// �S��
		ITEM_BROKEN_KABUTO,		// ��ꂽ��
		ITEM_CROW_FEATHER,		// �J���X�̉H
		ITEM_TOISI,				// �u��
		ITEM_DRIP_BAG,			// �_�H��
		ITEM_CHICK,				// �Ђ悱
		ITEM_ZOURI,				// ����
		ITEM_ARROW,				// ��
		ITEM_SEED,				// ��q
		ITEM_FETTERS,			// ���g
		ITEM_SHIELD,			// ��
		ITEM_TABI,				// ����
		ITEM_FLINT,				// �ΑŐ�
		ITEM_FLOWER,			// ��
		ITEM_IRON_WIRE,			// �S��
		ITEM_HANNYA,			// �͂�ɂ�̂߂�
		ITEM_MAX
	};
private:
	explicit CItemDataBase();
	static CItemDataBase* m_instance;
	void Init();
public:
	static CItemDataBase* GetInstance();
	~CItemDataBase();

	static void Uninit();

public:
	CItem* GetItemData(EItemType inState) { return m_item[inState]; }

private:	// �����o�ϐ�
	std::array<CItem*, ITEM_MAX> m_item;
};

using item_count = std::array<unsigned int, CItemDataBase::ITEM_MAX>;
#endif	// _ITEM_DATA_
