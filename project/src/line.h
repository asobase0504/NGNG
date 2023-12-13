//**************************************************************
//
// ���C���`�揈��(line.h)
// Author : �������l
// �T�v : ���C���������s��
//
//**************************************************************
#ifndef _LINE_H_		// ���̃}�N����`������ĂȂ�������
#define _LINE_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "object.h"

//==============================================================
// ���C���N���X
// Author : �������l
// �T�v : ���C���������s���N���X
//==============================================================
class CLine : public CObject
{
public:
	// ���_�t�H�[�}�b�g
	const unsigned int	FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE);

	//--------------------------------------------------------------
	// �\���̒�`
	//--------------------------------------------------------------
	// ���_�f�[�^
	typedef struct
	{
		D3DXVECTOR3			pos;			// ���_���W
		D3DXVECTOR3			nor;			// �@���x�N�g��
		D3DCOLOR			col;			// ���_�J���[
	}VERTEX_3D;

	//--------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------
	static CLine *Create(void);				// �I�u�W�F�N�g�̐���

	//--------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------
	explicit CLine();
	~CLine();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update() override;		// �X�V
	void Draw() override;		// �`��

	void SetRotTarget(const D3DXVECTOR3* rot) { m_targetRot = rot; }
	void SetPosTarget(const D3DXVECTOR3* pos) { m_targetPos = pos; }

	void SetVtx();								// ���_���W�Ȃǂ̐ݒ�
	void SetColor(const D3DXCOLOR& color) override;			// ���_�J���[�̐ݒ�
	void SetLine(D3DXVECTOR3 start, D3DXVECTOR3 goal);	// ���C���̐ݒu

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	LPDIRECT3DVERTEXBUFFER9 m_vtxBuff;			// ���_�o�b�t�@
	D3DXVECTOR3 m_start;			// �n�_
	D3DXVECTOR3 m_goal;				// �I�_
	const D3DXVECTOR3* m_targetPos;
	const D3DXVECTOR3* m_targetRot;
};
#endif
