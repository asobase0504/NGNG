//**************************************************************
//
// �I�u�W�F�N�gX��ǂݍ���ŕۑ����鏈�� [objectX_group.h]
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _SKINMESH_GROUP_H_
#define _SKINMESH_GROUP_H_

//==============================================================
// include
//==============================================================


//�h���t���[���\���� (���ꂼ��̃��b�V���p�̍ŏI���[���h�s���ǉ�����j
struct MYFRAME : public D3DXFRAME
{
	D3DXMATRIX CombinedTransformationMatrix;
	// �I�t�Z�b�g�s��(�C���f�b�N�X�t�`��p)
	D3DXMATRIX OffsetMat;
	// �s��e�[�u���̃C���f�b�N�X�ԍ�(�C���f�b�N�X�t�p)
	DWORD OffsetID;
};

//�h�����b�V���R���e�i�[�\����(
//�R���e�i�[���e�N�X�`���𕡐����Ă�悤�Ƀ|�C���^�[�̃|�C���^�[��ǉ�����j
struct MYMESHCONTAINER : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*  ppTextures;
	DWORD dwWeight; //�d�݂̌��i�d�݂Ƃ͒��_�ւ̉e���B�j
	DWORD dwBoneNum; //�{�[���̐�
	LPD3DXBUFFER pBoneBuffer; //�{�[���E�e�[�u��
	std::vector<D3DXMATRIX*> ppBoneMatrix; //�S�Ẵ{�[���̃��[���h�s��̐擪�|�C���^�[
	std::vector<D3DXMATRIX> pBoneOffsetMatrices; //�t���[���Ƃ��Ẵ{�[���̃��[���h�s��̃|�C���^�[
	LPD3DXMESH pOriMesh; //�I���W�i�����b�V���p
	DWORD NumPaletteEntries; //�p���b�g�T�C�Y

							 // Work�p
	std::vector<D3DXMATRIX> m_WorkBoneMatArray;
	// �e������t���[���ւ̎Q�Ɣz��B�`�掞�ɂ��̃t���[���̍s����g���B
	std::vector<MYFRAME*> BoneFrameArray;
	MYMESHCONTAINER()
	{
		ppBoneMatrix.clear();
		pBoneOffsetMatrices.clear();
	}
};

//X�t�@�C�����̃A�j���[�V�����K�w��ǂ݉����Ă����N���X��h��������B
//ID3DXAllocateHierarchy�͔h�����邱�Ƒz�肵�Đ݌v����Ă���B
class MY_HIERARCHY : public ID3DXAllocateHierarchy
{
public:
	MY_HIERARCHY() {}
	STDMETHOD(CreateFrame)(THIS_ LPCSTR, LPD3DXFRAME*);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCTSTR, CONST D3DXMESHDATA*, CONST D3DXMATERIAL*,
		CONST D3DXEFFECTINSTANCE*, DWORD, CONST DWORD *, LPD3DXSKININFO, LPD3DXMESHCONTAINER *);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER);
private:
};

//==============================================================
// �N���X�̒�`
//==============================================================
class CSkinMeshGroup
{
private: /* �v���C�x�[�g�萔 */
	static const wchar_t* filePath;

public:
	struct SSkinMeshInfo
	{
		LPD3DXFRAME frameRoot;	// �{�[�����
		LPD3DXANIMATIONCONTROLLER pAnimController;	// �A�j���[�V�����R���g���[��
		MY_HIERARCHY cHierarchy;	// �q�G�����L�[�N���X�ϐ�
	};
public:
	//--------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------
private:
	CSkinMeshGroup();
	static CSkinMeshGroup* m_instance;
public:
	static CSkinMeshGroup* GetInstance();
	~CSkinMeshGroup();

	//--------------------------------------------------------------
	// �����o�[�֐�
	//--------------------------------------------------------------
	void LoadAll();		// �S�Ă̓ǂݍ���
	void UnloadAll();	// �S�Ă̔j��
	void Load(std::string inKey, std::string inFileName);	// �w��̓ǂݍ���
	void Load(std::vector<std::string> inModel) { Load(inModel[0], inModel[1]); }			// �w��̓ǂݍ���
	void Unload(std::string inKey);				// �w��̔j��

	SSkinMeshInfo GetSkinMeshInfo(std::string inTag) { return m_skinMesh[inTag]; }

	void FreeAnim(std::string inKey, LPD3DXFRAME pFrame);
private: /* �v���C�x�[�g�֐� */
	//bool ExistsKey(std::string inKey) { return m_skinMesh.count(inKey) != 0; }	// Map���Ɏw�肳�ꂽKey�����݂��邩�ۂ�
private:
	std::map<std::string, SSkinMeshInfo, std::less<>> m_skinMesh;	// �X�L�����b�V���̏��
	std::list<std::string> m_keyList;	// Key�̏��Q
};
#endif