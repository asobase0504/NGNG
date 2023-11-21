//**************************************************************
//
// �I�u�W�F�N�gX��ǂݍ���ŕۑ����鏈�� [objectX_group.cpp]
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "application.h"
#include "renderer.h"
#include "model_skin_group.h"
#include "file.h"


//--------------------------------------------------------------
//�t���[�����쐬����
//--------------------------------------------------------------
HRESULT MY_HIERARCHY::CreateFrame(LPCSTR Name, LPD3DXFRAME *ppNewFrame)
{
	//�V�����t���[���A�h���X�i�[�p�ϐ���������
	*ppNewFrame = nullptr;
	//�t���[���̗̈�m��
	MYFRAME* pFrame = new MYFRAME;

	//�̈�m�ۂ̎��s���̏���
	if (pFrame == nullptr)
	{
		return E_OUTOFMEMORY;
	}

	//�t���[�����i�[�p�̈�m��
	pFrame->Name = new TCHAR[lstrlen(Name) + 1];
	//�̈�m�ۂ̎��s���̏���
	if (!pFrame->Name)
	{
		return E_FAIL;
	}

	//�t���[�����i�[
	strcpy(pFrame->Name, Name);
	//�s��̏�����
	D3DXMatrixIdentity(&pFrame->TransformationMatrix);
	//D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);
	//�ǉ��F�I�t�Z�b�g�֌W������
	/*pFrame->OffsetID = 0xFFFFFFFF;
	D3DXMatrixIdentity(&(pFrame->OffsetMat));*/
	//�V�K�t���[���̃��b�V���R���e�i������
	pFrame->pMeshContainer = NULL;
	//�V�K�t���[���̌Z��t���[���A�h���X�i�[�p�ϐ�������
	pFrame->pFrameSibling = NULL;
	//�V�K�t���[���̎q�t���[���A�h���X�i�[�p�ϐ�������
	pFrame->pFrameFirstChild = NULL;
	//�O���̐V�K�t���[���A�h���X�i�[�p�ϐ��ɁA�쐬�����t���[���̃A�h���X���i�[
	*ppNewFrame = pFrame;
	return S_OK;
}

//--------------------------------------------------------------
//���b�V���R���e�i�[���쐬����
//--------------------------------------------------------------
HRESULT MY_HIERARCHY::CreateMeshContainer(LPCSTR Name, CONST D3DXMESHDATA* pMeshData,
	CONST D3DXMATERIAL* pMaterials, CONST D3DXEFFECTINSTANCE* pEffectInstances,
	DWORD NumMaterials, CONST DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppMeshContainer)
{
	//���[�J�������p
	MYMESHCONTAINER *pMeshContainer = NULL;
	//���b�V���̖ʂ̐����i�[
	int iFacesAmount;
	//�ꎞ�I��DirectX�f�o�C�X�擾�p
	LPDIRECT3DDEVICE9 pDevice = NULL;
	//�ꎞ�I�ȃ��b�V���f�[�^�i�[�p
	LPD3DXMESH pMesh = NULL;
	//���b�V���R���e�i�i�[�p�ϐ�������
	*ppMeshContainer = NULL;
	//�{�[���̐��i�[�p�ϐ�������
	DWORD dwBoneNum = 0;
	//pMesh��"�O��������"���b�V���A�h���X���i�[
	pMesh = pMeshData->pMesh;
	//���b�V���R���e�i�̈�̓��I�m��
	pMeshContainer = new MYMESHCONTAINER;
	//�̈�m�ێ��s��
	if (pMeshContainer == NULL)
	{
		return E_OUTOFMEMORY;
	}
	//���b�V���R���e�i��������
	ZeroMemory(pMeshContainer, sizeof(MYMESHCONTAINER));
	//���b�V���R���e�i�̖��O�i�[�p�̈�𓮓I�m��
	pMeshContainer->Name = new TCHAR[lstrlen(Name) + 1];
	//���s���̏���
	if (!pMeshContainer->Name)
	{
		return E_FAIL;
	}
	//�m�ۂ����̈�Ƀ��b�V���R���e�i�����i�[
	strcpy(pMeshContainer->Name, Name);
	//DirectX�f�o�C�X�擾
	pMesh->GetDevice(&pDevice);
	//���b�V���̖ʂ̐����擾
	iFacesAmount = pMesh->GetNumFaces();
	//- ���b�V���̃}�e���A���ݒ� -//
	//���b�V���̃}�e���A�������i�[(�ő��1��)
	pMeshContainer->NumMaterials = max(1, NumMaterials);
	//���b�V���R���e�i�́A�}�e���A���f�[�^�i�[�̈�𓮓I�m��
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	//���b�V���R���e�i�́A�e�N�X�`���f�[�^�i�[�̈�𓮓I�m��
	pMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	//���b�V���R���e�i�́A�ʂ��ƂɎ���3�̗אڐ���񂪊i�[���ꂽDWORD�^�̃A�h���X�i�[�p(�|�C���^)�ϐ�
	pMeshContainer->pAdjacency = new DWORD[iFacesAmount * 3];
	//�̈�m�ۂ̎��s���̏���
	if ((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL))
	{
		return E_FAIL;
	}
	//�O�������̗אڐ��������b�V���R���e�i�Ɋi�[
	memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * iFacesAmount * 3);
	//�e�N�X�`���f�[�^�i�[�p�̈��������(memset���g�p����0�Œ��g�𖄂߂�)
	memset(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);
	//�����̃}�e���A������0����Ȃ��ꍇ
	if (NumMaterials > 0)
	{
		//�O�������̃}�e���A���f�[�^�A�h���X�����b�V���R���e�i�Ɋi�[
		memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);

		int iMaterial;
		//�}�e���A���������[�v������
		for (iMaterial = 0; (DWORD)iMaterial < NumMaterials; iMaterial++)
		{
			//�e�N�X�`���̃t�@�C������NULL�łȂ����(�e�N�X�`���f�[�^�������)
			if (pMeshContainer->pMaterials[iMaterial].pTextureFilename == NULL)
			{
				continue;
			}

			//�e�N�X�`���̃t�@�C���p�X�ۑ��p�ϐ�
			TCHAR strTexturePath[MAX_PATH];
			//�e�N�X�`���̃t�@�C���p�X��ۑ�(�ēǂݍ��ݎ��ɕK�v)
			strcpy_s(strTexturePath, lstrlen(pMeshContainer->pMaterials[iMaterial].pTextureFilename) + 1, pMeshContainer->pMaterials[iMaterial].pTextureFilename);
			//�e�N�X�`�����̓ǂݍ���
			if (FAILED(D3DXCreateTextureFromFile(pDevice, strTexturePath,
				&pMeshContainer->ppTextures[iMaterial])))
			{
				//���s���̏���
				//�e�N�X�`���t�@�C�����i�[�p
				CHAR TexMeshPass[255];
				//�ǋL
				//�����Ȃ���΁AGraph�t�H���_�𒲂ׂ�
				//���j�t�@�C�����̌������ɁA�K�������Ƀt�@�C���������鎖���m�F���Ă���
				//  strcpy_s��strcat_s���g���悤�ɂ���(���̏ꍇ�́A��ɂ��� 
				//    �e�N�X�`���̃t�@�C��������A����ɂ��̃t�@�C�����̒�����0�łȂ���� �̏���if��)�B
				//  TexMeshPass�ɁAX�t�@�C��������ꏊ�Ɠ����f�B���N�g���ƁA�e�N�X�`���̃t�@�C������
				//  �����������̂��i�[
				// strcpy_s( TexMeshPass, sizeof( TexMeshPass ) , "./../Source/Graph/" );
				strcpy_s(TexMeshPass, sizeof(TexMeshPass), "./Graph/");
				strcat_s(TexMeshPass, sizeof(TexMeshPass) - strlen(TexMeshPass) - strlen(strTexturePath) - 1, strTexturePath);
				//�e�N�X�`�����̓ǂݍ���
				if (FAILED(D3DXCreateTextureFromFile(pDevice, TexMeshPass,
					&pMeshContainer->ppTextures[iMaterial])))
				{
					pMeshContainer->ppTextures[iMaterial] = NULL;
				}
				//�e�N�X�`���̃t�@�C���p�X��NULL�ɂ���
				pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
			}
		}
	}
	else
	{
		//- �}�e���A���Ȃ��̏ꍇ -//
		//�e�N�X�`���t�@�C������NULL��
		pMeshContainer->pMaterials[0].pTextureFilename = NULL;
		//�}�e���A���f�[�^������(memset���g�p���Ē��g��0�Ŗ��߂�)
		memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
		//�}�e���A���J���[��0.5�ɐݒ�
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		//�X�y�L������0.5�ɐݒ�(��Őݒ肵���}�e���A���J���[��0.5�̐ݒ���R�s�[)
		pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
	}

	//���b�V�������i�[(����͒ʏ탁�b�V���Ɗ��S�ɕ����Ă��邽�߂��ׂăX�L�����b�V�����ƂȂ�)
	pMeshContainer->pSkinInfo = pSkinInfo;
	//�Q�ƃJ�E���^
	pSkinInfo->AddRef();
	//�{�[���̐����擾
	dwBoneNum = pSkinInfo->GetNumBones();
	//�t���[��(�{�[��)�P�ʂł̃��[���h�s��i�[�p�̈�̓��I�m��
	pMeshContainer->pBoneOffsetMatrices.resize(dwBoneNum);
	//�{�[���̐��������[�v������
	for (DWORD i = 0; i < dwBoneNum; i++)
	{
		//�p�t���[��(�{�[��)�̃I�t�Z�b�g�s����擾���Ċi�[
		memcpy(&pMeshContainer->pBoneOffsetMatrices[i],
			pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i), sizeof(D3DMATRIX));
	}
	//- �ϊ���� -//
	//���b�V���R���e�i�ɃI���W�i����pMesh�����i�[
	D3DVERTEXELEMENT9 Decl[MAX_FVF_DECL_SIZE];
	pMesh->GetDeclaration(&Decl[0]);
	pMesh->CloneMesh(pMesh->GetOptions(), &Decl[0], pDevice, &pMeshContainer->pOriMesh);
	//���b�V���̃^�C�v���`
	pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

	//- �Œ�p�C�v���C���`��p�ɕϊ� -//
	//�V�F�[�_�ŕ`�悷��ꍇ�͕ʓr�ϊ����K�v
	//���_�P�ʂł̃u�����h�̏d�݂ƃ{�[���̑g�ݍ��킹�e�[�u����K�������V�������b�V����Ԃ��B
	if (FAILED(pMeshContainer->pSkinInfo->ConvertToBlendedMesh(
		pMeshContainer->pOriMesh,			// ���̃��b�V���f�[�^�A�h���X
		NULL,								// �I�v�V����(���݂͎g���Ă��Ȃ�����NULL�ł���)
		pMeshContainer->pAdjacency,			// ���̃��b�V���̗אڐ����
		NULL,								// �o�̓��b�V���̗אڐ����
		NULL,								// �e�ʂ̐V�����C���f�b�N�X�l�i�[�p�ϐ��̃A�h���X
		NULL,								// �p���_�̐V�����C���f�b�N�X�l�i�[�p�ϐ��̃A�h���X
		&pMeshContainer->dwWeight,			// �{�[���̉e���̈�ʓ�����̍ő吔�i�[�p�ϐ��̃A�h���X
		&pMeshContainer->dwBoneNum,			// �{�[���̑g�ݍ��킹�e�[�u���Ɋ܂܂��{�[�����i�[�p�ϐ��̃A�h���X
		&pMeshContainer->pBoneBuffer,		// �{�[���̑g�ݍ��킹�e�[�u���ւ̃|�C���^
		&pMeshContainer->MeshData.pMesh		// �o�͂���郁�b�V���A�h���X�i�[�p�ϐ��̃A�h���X(�Œ�p�C�v���C���p)
	)))
	{
		return E_FAIL;
	}
	//���[�J���ɐ����������b�V���R���e�i�[���Ăяo�����ɃR�s�[����
	*ppMeshContainer = pMeshContainer;
	//�Q�ƃJ�E���^�𑝂₵���̂Ō��炷
	SAFE_RELEASE(pDevice);
	return S_OK;
}

//--------------------------------------------------------------
//�t���[����j������
//--------------------------------------------------------------
HRESULT MY_HIERARCHY::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	//2�e����h�~
	// if (pFrameToFree == NULL)return S_FALSE;
	SAFE_DELETE_ARRAY(pFrameToFree->Name);
	if (pFrameToFree->pFrameFirstChild)
	{
		DestroyFrame(pFrameToFree->pFrameFirstChild);
	}
	if (pFrameToFree->pFrameSibling)
	{
		DestroyFrame(pFrameToFree->pFrameSibling);
	}
	SAFE_DELETE(pFrameToFree);
	return S_OK;
}

//--------------------------------------------------------------
//���b�V���R���e�i�[��j������
//--------------------------------------------------------------
HRESULT MY_HIERARCHY::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	int iMaterial;
	MYMESHCONTAINER *pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
	SAFE_DELETE_ARRAY(pMeshContainer->Name);
	SAFE_RELEASE(pMeshContainer->pSkinInfo);
	SAFE_DELETE_ARRAY(pMeshContainer->pAdjacency);
	SAFE_DELETE_ARRAY(pMeshContainer->pMaterials);
	pMeshContainer->ppBoneMatrix.clear();
	if (pMeshContainer->ppTextures != NULL)
	{
		for (iMaterial = 0; (DWORD)iMaterial < pMeshContainer->NumMaterials; iMaterial++)
		{
			//�e�N�X�`�����
			SAFE_RELEASE(pMeshContainer->ppTextures[iMaterial]);
		}
	}
	SAFE_DELETE_ARRAY(pMeshContainer->ppTextures);
	SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
	SAFE_RELEASE(pMeshContainer->pOriMesh);
	if (pMeshContainer->pBoneBuffer != NULL)
	{
		SAFE_RELEASE(pMeshContainer->pBoneBuffer);
		pMeshContainer->pBoneOffsetMatrices.clear();
	}
	SAFE_DELETE(pMeshContainer);
	pMeshContainerBase = NULL;
	return S_OK;
}

//==============================================================
// �萔
//==============================================================
const wchar_t* CSkinMeshGroup::filePath = L"Data/FILE/skinmesh.json";
CSkinMeshGroup* CSkinMeshGroup::m_instance = nullptr;

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CSkinMeshGroup::CSkinMeshGroup()
{
}

CSkinMeshGroup * CSkinMeshGroup::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CSkinMeshGroup;
	}
	return m_instance;
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CSkinMeshGroup::~CSkinMeshGroup()
{
}

//--------------------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------------------
void CSkinMeshGroup::LoadAll()
{
	nlohmann::json list = LoadJson(filePath);

	int size = (int)list["MODEL"].size();

	std::string test = list["MODEL"][0][0];
	for (int i = 0; i < size; ++i)
	{
		Load(list["MODEL"].at(i));
	}
}

//--------------------------------------------------------------
// �ǂݍ���
//--------------------------------------------------------------
void CSkinMeshGroup::Load(std::string inKey, std::string inFileName)
{
	std::string fileName = inFileName;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// X�t�@�C������A�j���[�V�������b�V����ǂݍ��ݍ쐬����
	if (FAILED(D3DXLoadMeshHierarchyFromX(fileName.c_str(), D3DXMESH_MANAGED, pDevice,
		&m_skinMesh[inKey].cHierarchy, NULL, &m_skinMesh[inKey].frameRoot, &m_skinMesh[inKey].pAnimController)))
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", fileName.c_str(), MB_OK);
		return;
	}
}

//--------------------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------------------
void CSkinMeshGroup::UnloadAll()
{
	m_skinMesh.clear();
}

//--------------------------------------------------------------
// ���
//--------------------------------------------------------------
void CSkinMeshGroup::Unload(std::string inKey)
{
	m_skinMesh[inKey].cHierarchy;
	m_skinMesh[inKey].frameRoot;
	m_skinMesh[inKey].pAnimController;

	if (m_skinMesh[inKey].frameRoot != nullptr)
	{
		//�{�[���t���[���֌W���
		FreeAnim(inKey,m_skinMesh[inKey].frameRoot);
		//���̑����(�e�N�X�`���̎Q�ƃf�[�^�Ȃ�)�̉��
		m_skinMesh[inKey].cHierarchy.DestroyFrame(m_skinMesh[inKey].frameRoot);
		m_skinMesh[inKey].frameRoot = nullptr;
	}
	//�A�j���[�V�����R���g���[���[���
	SAFE_RELEASE(m_skinMesh[inKey].pAnimController);

	m_skinMesh.erase(inKey);

}


//--------------------------------------------------------------
//�S�Ă̊K�w�t���[�����������
//--------------------------------------------------------------
void CSkinMeshGroup::FreeAnim(std::string inKey,LPD3DXFRAME pFrame)
{
	if (pFrame->pMeshContainer != NULL)
	{
		m_skinMesh[inKey].cHierarchy.DestroyMeshContainer(pFrame->pMeshContainer);
		pFrame->pMeshContainer = NULL;
	}
	if (pFrame->pFrameSibling != NULL)
		FreeAnim(inKey,pFrame->pFrameSibling);
	if (pFrame->pFrameFirstChild != NULL)
		FreeAnim(inKey,pFrame->pFrameFirstChild);
}