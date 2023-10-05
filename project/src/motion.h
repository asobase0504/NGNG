//**************************************************************
//
// ���[�V��������(motion.h)
// Auther�F�������l
// �T�v : ���[�V�����N���X�̐ݒ�
//
//**************************************************************
#ifndef _MOTION_H_			// ���̃}�N����`������ĂȂ�������
#define _MOTION_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "objectX.h"
#include "renderer.h"

//==============================================================
// �O���錾
//==============================================================
class CParts;
class CModel3D;

//==============================================================
// ���[�V�����N���X
// Author : �������l
// �T�v : ���[�V�����ݒ���s���N���X
//==============================================================
class CMotion
{
public:
	//--------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------
	static const unsigned int MAX_MOTION;			// ���[�V�������̍ő吔
	static const unsigned int MAX_MODEL_PARTS;		// ���f�����̍ő吔
	static const unsigned int MAX_KEY;				// �L�[�̍ő吔
	static const unsigned int MAX_KEYSET;			// �L�[�ݒ�̍ő吔
	static const unsigned int MOTION_BLEND_FRAM;	// ���[�V�����u�����h�̃t���[����

	//--------------------------------------------------------------
	// �L�[�\���̂��`
	//--------------------------------------------------------------
	typedef struct
	{
		D3DXVECTOR3		pos;	// ���݈ʒu
		D3DXVECTOR3		rot;	// ���݂̌���
	}MyKey;

	//--------------------------------------------------------------
	// �L�[�ݒ�\���̂��`
	//--------------------------------------------------------------
	typedef struct
	{
		int		nFrame;				// �t���[����
		std::vector<MyKey>	pKey;	// �L�[���
	}MyKeySet;

	//--------------------------------------------------------------
	// ���[�V�����ݒ�\���̂��`
	//--------------------------------------------------------------
	typedef struct
	{
		int nNumKey;		// �L�[��
		int nCntKeySet;		// �L�[�Z�b�g�J�E���g
		int nCntFrame;		// �t���[���J�E���g
		bool bLoop;			// ���[�v�g�p��
		bool bMotion;		// ���[�V�������s���Ă��邩
		std::vector<MyKeySet> pKeySet;	// �L�[�ݒ���
	}MyMotion;

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CMotion(const char *pFileName);
	~CMotion();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void Update();	// �X�V
	void Uninit(void);	// �I��

	void SetPartsOrigin();							// �p�[�c�����Ƃ̏ꏊ�ɔz�u����

	void SetMotion(const int nCntMotionSet);		// ���[�V�����̏����ݒ�
	bool GetMotion() { return m_isMotion; }			// ���[�V�������s���Ă��邩�擾

	void SetParts(D3DXMATRIX mtxWorld);				// �p�[�c�̐ݒ�
	CParts* GetParts(int index) { return m_parts[index]; }	// ���[�V�����u�����h���s���Ă��邩�擾

	void SetNumMotion(const int nNumMotion);		// ���[�V�����ԍ��̐ݒ�
	void SetUseMotion(bool isMotion) { m_isMotion = isMotion; }			// ���[�V�������s���Ă��邩�ݒ�
	void SetMotionBlend(bool isBlend) { m_isMotionBlend = isBlend; }		// ���[�V�����u�����h���s���Ă��邩�ݒ�

	int GetMaxParts() { return m_maxParts; }				// �p�[�c�̍ő吔�̎擾
	bool GetMotionBlend() { return m_isMotionBlend; }		// ���[�V�����u�����h���s���Ă��邩�擾

private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void Init();	// ������

	void PlayMotion();	// ���[�V�����̍Đ�
	void MotionBlend();	// ���[�V�����u�����h
	void LoodSetMotion(const char *pFileName);	// ���[�V�����ǂݍ���
	void CntReset(const int nNumMotionOld);		// �J�E���g���Z�b�g

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CModel3D* m_parent;					// �e
	std::vector<MyMotion> m_motion;		// ���[�V����
	std::vector<CParts*> m_parts;		// �p�[�c
	std::vector<char*> m_partsFile;		// �p�[�c��X�t�@�C����
	int m_maxParts;						// �p�[�c��
	int m_numMotion;					// �������[�V����
	bool m_isMotion;					// ���[�V�������s����
	bool m_isMotionBlend;				// ���[�V�����u�����h
};
#endif

