//====================================================
//
// ���f��Data
// Author : �l�c
//
//====================================================
//-------------------------------
// �C���N���[�h
//-------------------------------
#include "model_date.h"

//-------------------------------
// �f�t�H���g�R���X�g���N�^
//-------------------------------
CModelData::CModelData()
{
	IsUse = false;
	m_CommuData.Player.m_log = 0;
	m_CommuData.Player.m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CommuData.Player.m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CommuData.Player.m_motion = 0;
	m_CommuData.Player.m_pushBomComands = false;
	for (int i = 0; i < MaxModel; i++)
	{
		m_CommuData.Player.m_isPopEnemy[i].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_CommuData.Player.m_isPopEnemy[i].isDiscovery = false;
		m_CommuData.Player.m_isPopEnemy[i].isUse = true;
		m_CommuData.Player.m_isPopGimmick[i] = false;

	}
}

//-------------------------------
// �f�t�H���g�f�X�g���N�^
//-------------------------------
CModelData::~CModelData()
{

}

CDataPack::SSendPack::SSendPack() : SSendData(ESENDDATA_ENEMY)
{
}

CDataPack::SSendPack::~SSendPack()
{
}
