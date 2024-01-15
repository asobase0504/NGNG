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
	enum ERarity
	{
		RARITY_NONE = -1,
		RARITY_COMMON = 0,
		RARITY_UNCOMMON,
		RARITY_RARE,
		RARITY_LOSE,	// �͂���(�^�̍Ւd�p)
		RARITY_MAX,
		RARITY_NOSELECT, // �I�΂�邱�Ƃ̂Ȃ��A�C�e��(�G���[�g�p�Ƃ�)
	};

	enum EItemType
	{
		ITEM_NONE = -1,
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
		ITEM_ELITE,				// �G���[�g���ǂ���
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
	std::string GetItemName(EItemType inState) { return m_itemInfo[inState][0]; }
	std::string GetItemMemo(EItemType inState) { return m_itemInfo[inState][1]; }
	std::string GetItemIconTextureKey(EItemType inState) { return m_itemInfo[inState][2]; }

private:	// �����o�ϐ�
	std::array<CItem*, ITEM_MAX> m_item;
	std::array<std::string[3], ITEM_MAX> m_itemInfo;	// ����

	int m_countKill;	// �E������
	int m_maxAddLife;	// ���₹��ő�l
	int m_frame;		// ���ʎ���
};

using item_count = std::array<unsigned int, CItemDataBase::ITEM_MAX>;
#endif	// _ITEM_DATA_
