//**************************************************************
//
// �L�����N�^�[
// Author : ���c�喲
//
//**************************************************************
#ifndef _CHARACTER_H_			// ���̃}�N����`������ĂȂ�������
#define _CHARACTER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "object.h"

//==============================================================
// �O���錾
//==============================================================
class CObjectX;

//==============================================================
// �v���C���[�N���X
//==============================================================
class CCharacter : public CObject
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CCharacter(int nPriority = 3);
	~CCharacter();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// �ÓI�����o�֐�
	static CCharacter *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// �v���C���[�̐���

private:		// �����o�ϐ�
	std::vector<CObjectX*>		m_apModel;		// ���f���̃C���X�^���X
	D3DXMATRIX		m_mtxWorld;					// ���[���h�}�g���b�N�X
};
#endif
