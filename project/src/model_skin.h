//=============================================================================
//
// 3D���f���N���X(model3D.h)
// Author : �������l
// �T�v : 3D���f���������s��
//
//=============================================================================
#ifndef _MODEL_SKIN_H_			// ���̃}�N����`������ĂȂ�������
#define _MODEL_SKIN_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include "model_skin_group.h"

#define SKIN_ANIME_SPEED 60.0f / 4800.0f

//=============================================================================
// 3D���f���N���X
// Author : Hamada Ryuga
// �T�v : 3D���f���������s���N���X
//=============================================================================
// �X�L�����b�V���N���X
class CSkinMesh : public CObject
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CSkinMesh *Create(std::string Name);		// 3D���f���̐���

	CSkinMesh();
	~CSkinMesh() {
		Release();
	}
	HRESULT Init() override { return S_OK; }
	void Uninit() override { CObject::Uninit(); }
	void Update() override;

	//�X�L�����b�V����������
	HRESULT Init(std::string pMeshPass);
	HRESULT AllocateBoneMatrix(LPD3DXFRAME pFrameRoot, LPD3DXMESHCONTAINER pMeshContainerBase);
	HRESULT AllocateAllBoneMatrices(LPD3DXFRAME pFrameRoot, LPD3DXFRAME pFrameBase);
	void ShaderDraw(MYMESHCONTAINER*, MYFRAME*);
	void RenderMeshContainer(MYMESHCONTAINER*, MYFRAME*);
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	void DrawFrame(LPD3DXFRAME);
	//�������
	void Release();

	//�`�揈��
	void Draw();
	//�I�u�W�F�N�g�̃A�j���[�V�����ύX( ���b�V���I�u�W�F�N�g�̑���p�ԍ�, �ύX����A�j���[�V�����ԍ� )
	void ChangeAnim(DWORD);
	//���݂̃A�j���[�V�����ԍ��擾
	DWORD GetAnimTrack() { return m_CurrentTrack; }
	//���݂̃A�j���[�V�����^�C��(�A�j���[�V�����J�n����̎���)���擾
	DWORD GetAnimTime() { return m_AnimeTime; }
	//�A�j���[�V�������x���擾
	float GetAnimSpeed() { return m_AnimSpeed; }
	//�A�j���[�V�������x��ݒ�
	void SetAnimSpeed(float _AnimSpeed) { m_AnimSpeed = _AnimSpeed; }
private:
	//�Ώۂ̃{�[��������
	MYFRAME* SearchBoneFrame(std::string _BoneName, D3DXFRAME* _pFrame);
public:
	//�{�[���̃}�g���b�N�X�擾( �{�[���̖��O )
	D3DXMATRIX GetBoneMatrix(std::string _BoneName);
	//�{�[���̃}�g���b�N�X�|�C���^�擾( �{�[���̖��O )
	D3DXMATRIX* GetpBoneMatrix(std::string _BoneName);
private:
	//�ǉ�
	//���ׂẴt���[���|�C���^�i�[�����֐�
	void CreateFrameArray(LPD3DXFRAME _pFrame);

	LPD3DXFRAME m_pFrameRoot;	//�{�[�����

	// �A�j���[�V����
	LPD3DXANIMATIONCONTROLLER m_pAnimController;	//�A�j���[�V�����R���g���[��
	std::vector<LPD3DXANIMATIONSET> m_pAnimSet;	//�A�j���[�V�����f�[�^�i�[�p
	DWORD m_AnimeTime;	//���݂̃A�j���[�V�������J�n����Ă���̎���(1/60�b)
	float m_AnimSpeed;	//�A�j���[�V�����X�s�[�h
	DWORD m_CurrentTrack;	//���݂̃A�j���[�V�����g���b�N
	D3DXTRACK_DESC m_CurrentTrackDesc;	//���݂̃A�j���[�V�����f�[�^�g���b�N
	DWORD m_animeEndTime;				// �A�j���[�V�����I���t���[��

	bool m_isLoop;	// Loop�������ǂ���
	bool m_isAnimeEnd;	// ���A�j���[�V�������I��点����
};
#endif