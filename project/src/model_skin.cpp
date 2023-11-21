//=============================================================================
//
// 3D���f���N���X(model3D.h)
// Author : �������l
// �T�v : 3D���f���������s��
//
//=============================================================================

//==============================================================
// include
//==============================================================
#include "model_skin.h"
#include "application.h"
#include "renderer.h"
#include "model_skin_group.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CSkinMesh::CSkinMesh()
{
	//�P�ʍs��
	D3DXMatrixIdentity(&(this->m_mtxWorld));
	//�A�j���[�V�������ԏ�����
	m_AnimeTime = 0;
	//�A�j���[�V�����X�s�[�h������
	m_AnimSpeed = SKIN_ANIME_SPEED; // �Œ�

	//���݂̃A�j���[�V�����g���b�N������
	m_CurrentTrack = 0;
	//�A�j���[�V�����f�[�^�g���b�N������
	//�L���ɂ���
	m_CurrentTrackDesc.Enable = true;
	//�e���x100%
	m_CurrentTrackDesc.Weight = 1;
	//�J�n�ʒu������
	m_CurrentTrackDesc.Position = 0;
	//���x
	m_CurrentTrackDesc.Speed = 1;

	m_isLoop = false;
	m_isAnimeEnd = false;
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CSkinMesh::Init(std::string pMeshPass)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	std::string TmpMeshPass;
	TmpMeshPass = pMeshPass;

	CSkinMeshGroup::SSkinMeshInfo info = CSkinMeshGroup::GetInstance()->GetSkinMeshInfo(pMeshPass);

	m_pFrameRoot = info.frameRoot;
	m_pAnimController = info.pAnimController;

	//�{�[���s�񏉊���
	AllocateAllBoneMatrices(m_pFrameRoot, m_pFrameRoot);

	m_pAnimSet.resize(m_pAnimController->GetNumAnimationSets());

	//�A�j���[�V�����g���b�N�̎擾
	for (DWORD i = 0; i < m_pAnimController->GetNumAnimationSets(); i++)
	{
		//�A�j���[�V�����擾
		m_pAnimController->GetAnimationSet(i, &(m_pAnimSet[i]));
	}

	//���ׂẴt���[���Q�ƕϐ��̐���
	CreateFrameArray(m_pFrameRoot);
	return S_OK;
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CSkinMesh::Update()
{
	//�A�j���[�V�������Ԃ��X�V
	m_AnimeTime++;

	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}

//--------------------------------------------------------------
//�X�L�����b�V���̕`��
//--------------------------------------------------------------
void CSkinMesh::Draw()
{
	//���݂̃A�j���[�V�����ԍ���K��
	m_pAnimController->SetTrackAnimationSet(0, m_pAnimSet[m_CurrentTrack]);
	//0(�Đ�����)�g���b�N����g���b�N�f�X�N���Z�b�g����
	m_pAnimController->SetTrackDesc(0, &(m_CurrentTrackDesc));
	//�A�j���[�V�������ԃf�[�^�̍X�V
	m_pAnimController->AdvanceTime(m_AnimSpeed, NULL);
	//�A�j���[�V�����f�[�^���X�V
	UpdateFrameMatrices(m_pFrameRoot, &m_mtxWorld);
	//�A�j���[�V�����`��
	DrawFrame(m_pFrameRoot);
	//0(�Đ�����)�g���b�N����X�V�����g���b�N�f�X�N���擾����
	m_pAnimController->GetTrackDesc(0, &m_CurrentTrackDesc);
}

//--------------------------------------------------------------
// �C���X�^���X����
// Author : �������l
// �T�v : ���[�V�����L�����N�^�[3D�𐶐�����
//--------------------------------------------------------------
CSkinMesh * CSkinMesh::Create(std::string Name)
{
	// �I�u�W�F�N�g�C���X�^���X
	CSkinMesh *pSkinMesh = nullptr;

	// �������̉��
	pSkinMesh = new CSkinMesh;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pSkinMesh != nullptr);

	// ���l�̏�����
	pSkinMesh->Init(Name);

	// �C���X�^���X��Ԃ�
	return pSkinMesh;
}

//--------------------------------------------------------------
// release
//--------------------------------------------------------------
void CSkinMesh::Release()
{

}

//--------------------------------------------------------------
//�{�[���s��̏�����
//--------------------------------------------------------------
HRESULT CSkinMesh::AllocateBoneMatrix(LPD3DXFRAME pFrameRoot, LPD3DXMESHCONTAINER pMeshContainerBase)
{
	MYFRAME *pFrame = NULL;
	DWORD dwBoneNum = 0;

	//���b�V���R���e�i�̌^���I���W�i���̌^�Ƃ��Ĉ���
	//(���b�V���R���e�i�������ɃI���W�i���̌^�Ƃ��č���Ă���̂Ŗ��͂Ȃ����A
	//��{�_�E���L���X�g�͊댯�Ȃ̂ő��p�͔�����ׂ�)
	MYMESHCONTAINER *pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;

	//�X�L�����b�V���łȂ����
	if (pMeshContainer->pSkinInfo == NULL)
	{
		return S_OK;
	}

	//�{�[���̐��擾
	dwBoneNum = pMeshContainer->pSkinInfo->GetNumBones();
	//�e�{�[���̃��[���h�s��i�[�p�̈���m��
	pMeshContainer->ppBoneMatrix.resize(dwBoneNum);

	//�{�[���̐��������[�v
	for (DWORD i = 0; i < dwBoneNum; i++)
	{
		//�q�t���[��(�{�[��)�̃A�h���X����������pFrame�Ɋi�[
		pFrame = (MYFRAME*)D3DXFrameFind(pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(i));
		//�q�t���[�����Ȃ���Ώ������I������
		if (pFrame == NULL)
		{
			return E_FAIL;
		}
		//�e�{�[���̃��[���h�s��i�[�p�ϐ��ɍŏI�s����i�[
		pMeshContainer->ppBoneMatrix[i] = &pFrame->CombinedTransformationMatrix;
	}
	return S_OK;
}

//--------------------------------------------------------------
// �}�e���A�����S�̂̃{�[���s��̏�����
//--------------------------------------------------------------
HRESULT CSkinMesh::AllocateAllBoneMatrices(LPD3DXFRAME pFrameRoot, LPD3DXFRAME pFrame)
{
	//�K�w�̑���(���������m�ۂ������b�V���R���e�i�̈��T������)
	if (pFrame->pMeshContainer != nullptr)
	{
		//�{�[���s��̏���������
		if (FAILED(AllocateBoneMatrix(pFrameRoot, pFrame->pMeshContainer)))
		{
			return E_FAIL;
		}
	}
	//�ċN���f����
	if (pFrame->pFrameSibling != nullptr)
	{
		if (FAILED(AllocateAllBoneMatrices(pFrameRoot, pFrame->pFrameSibling)))
		{
			return E_FAIL;
		}
	}
	if (pFrame->pFrameFirstChild != nullptr)
	{
		if (FAILED(AllocateAllBoneMatrices(pFrameRoot, pFrame->pFrameFirstChild)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//--------------------------------------------------------------
//�t���[�����̂��ꂼ��̃��b�V���������_�����O����
//--------------------------------------------------------------
void CSkinMesh::RenderMeshContainer(MYMESHCONTAINER* pMeshContainer, MYFRAME* pFrame)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	DWORD i, k;
	DWORD dwBlendMatrixNum;
	DWORD dwPrevBoneID;
	LPD3DXBONECOMBINATION pBoneCombination;
	UINT iMatrixIndex;
	D3DXMATRIX mStack;

	//�X�L�����b�V���̕`��
	if (pMeshContainer->pSkinInfo == NULL)
	{
		//�ʏ탁�b�V���̏ꍇ
		MessageBox(NULL, "�X�L�����b�V��X�t�@�C���̕`��Ɏ��s���܂����B", NULL, MB_OK);
		exit(EOF);
	}

	//�{�[���e�[�u������o�b�t�@�̐擪�A�h���X���擾
	pBoneCombination = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneBuffer->GetBufferPointer());
	//dwPrevBoneID��UINT_MAX�̒l(0xffffffff)���i�[
	dwPrevBoneID = UINT_MAX;
	//�X�L�j���O�v�Z
	for (i = 0; i < pMeshContainer->dwBoneNum; i++)
	{
		dwBlendMatrixNum = 0;
		//�e�����Ă���s�񐔎擾
		for (k = 0; k < pMeshContainer->dwWeight; k++)
		{
			//UINT_MAX(-1)
			if (pBoneCombination[i].BoneId[k] != UINT_MAX)
			{
				//���݉e�����󂯂Ă���{�[���̐�
				dwBlendMatrixNum = k;
			}
		}
		//�W�I���g���u�����f�B���O���g�p���邽�߂ɍs��̌����w��
		pDevice->SetRenderState(D3DRS_VERTEXBLEND, dwBlendMatrixNum);
		//�e�����Ă���s��̌���
		for (k = 0; k < pMeshContainer->dwWeight; k++)
		{
			//iMatrixIndex��1�x�̌Ăяo���ŕ`��o����e�{�[�������ʂ���l���i�[
			//( ����BoneID�z��̒����̓��b�V���̎�ނɂ���ĈقȂ�
			//( �C���f�b�N�X�Ȃ��ł���΁@=�@���_���Ƃ̏d�� �ł���
			// �C���f�b�N�X����ł���΁@=�@�{�[���s��p���b�g�̃G���g����)
			//���݂̃{�[��(i�Ԗ�)����݂�k�Ԗڂ̃{�[��id
			iMatrixIndex = pBoneCombination[i].BoneId[k];
			//�s��̏�񂪂����
			if (iMatrixIndex != UINT_MAX)
			{
				//mStack�ɃI�t�Z�b�g�s��*�{�[���s����i�[
				mStack = pMeshContainer->pBoneOffsetMatrices[iMatrixIndex] * (*pMeshContainer->ppBoneMatrix[iMatrixIndex]);
				//�s��X�^�b�N�Ɋi�[
				pDevice->SetTransform(D3DTS_WORLDMATRIX(k), &mStack);
			}
		}
		D3DMATERIAL9 TmpMat = pMeshContainer->pMaterials[pBoneCombination[i].AttribId].MatD3D;
		TmpMat.Emissive.a = TmpMat.Diffuse.a = TmpMat.Ambient.a = 1.0f;
		pDevice->SetMaterial(&TmpMat);
		pDevice->SetTexture(0, pMeshContainer->ppTextures[pBoneCombination[i].AttribId]);
		//dwPrevBoneID�ɑ����e�[�u���̎��ʎq���i�[
		dwPrevBoneID = pBoneCombination[i].AttribId;
		//���b�V���̕`��
		pMeshContainer->MeshData.pMesh->DrawSubset(i);
	}
}

//--------------------------------------------------------------
//�t���[���������_�����O����B
//--------------------------------------------------------------
void CSkinMesh::DrawFrame(LPD3DXFRAME pFrameBase)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pFrame->pMeshContainer;
	while (pMeshContainer != NULL)
	{
		//SHADER_KIND a = GetpShader()->GetShaderKind();
		////�V�F�[�_���g�p���Ă���̂Ȃ��p�̕`��֐��ɔ�΂�
		//if( GetpShader() != NULL && GetpShader()->GetShaderKind() == SHADER_KIND_LAMBERT ){
		// ShaderDraw( pDevice, ControlNum, pMeshContainer, pFrame ); 
		//}else{
		RenderMeshContainer(pMeshContainer, pFrame);
		// }
		//���̃��b�V���R���e�i�փA�N�e�B�u���ڂ�
		pMeshContainer = (MYMESHCONTAINER*)pMeshContainer->pNextMeshContainer;
	}
	if (pFrame->pFrameSibling != NULL)
	{
		DrawFrame(pFrame->pFrameSibling);
	}
	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawFrame(pFrame->pFrameFirstChild);
	}
}

//--------------------------------------------------------------
//�t���[�����̃��b�V�����Ƀ��[���h�ϊ��s����X�V����
//--------------------------------------------------------------
void CSkinMesh::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	MYFRAME *pFrame = (MYFRAME*)pFrameBase;
	if (pParentMatrix != NULL)
	{
		//CombinedTransformationMatrix�ɍŏI�s����i�[
		D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);
	}
	else
	{
		//CombinedTransformationMatrix�ɍŏI�s����i�[
		pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
	}
	if (pFrame->pFrameSibling != NULL)
	{
		UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
	}
	if (pFrame->pFrameFirstChild != NULL)
	{
		UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
	}
}

//--------------------------------------------------------------
//���ׂẴt���[���|�C���^�i�[�����֐�
//--------------------------------------------------------------
void CSkinMesh::CreateFrameArray(LPD3DXFRAME _pFrame)
{
	if (_pFrame == nullptr) { return; }
	//�t���[���A�h���X�i�[
	MYFRAME* pMyFrame = (MYFRAME*)_pFrame;
	m_animeEndTime++;

	//�q�t���[������
	if (pMyFrame->pFrameFirstChild != NULL) 
	{
		CreateFrameArray(pMyFrame->pFrameFirstChild);
	}
	//�Z��t���[������
	if (pMyFrame->pFrameSibling != NULL) 
	{
		CreateFrameArray(pMyFrame->pFrameSibling);
	}
}

//--------------------------------------------------------------
//�I�u�W�F�N�g�̃A�j���[�V�����ύX( �ύX����A�j���[�V�����ԍ� )
//--------------------------------------------------------------
void CSkinMesh::ChangeAnim(DWORD _NewAnimNum)
{
	// -�̒l�ɂȂ�悤��������B
	if (_NewAnimNum < 0)
	{
		_NewAnimNum = 0;
	}
	// �ő�l�𒴂��悤�Ƃ��Ă���
	if (_NewAnimNum > m_pAnimController->GetNumAnimationSets())
	{
		_NewAnimNum = m_pAnimController->GetNumAnimationSets();
	}

	//�V�K�A�j���[�V�����ɕύX
	m_CurrentTrack = _NewAnimNum;
	//�A�j���[�V�����^�C����������
	m_AnimeTime = 0;
	//�A�j���[�V�������ŏ��̈ʒu����Đ�������
	m_pAnimController->GetTrackDesc(0, &m_CurrentTrackDesc);
	m_CurrentTrackDesc.Position = 0;
	m_pAnimController->SetTrackDesc(0, &m_CurrentTrackDesc);
}

//--------------------------------------------------------------
//�Ώۂ̃{�[��������
//--------------------------------------------------------------
MYFRAME* CSkinMesh::SearchBoneFrame(std::string _BoneName, D3DXFRAME* _pFrame)
{
	MYFRAME* pFrame = (MYFRAME*)_pFrame;
	if (strcmp(pFrame->Name, _BoneName.c_str()) == 0)
	{
		return pFrame;
	}
	if (_pFrame->pFrameSibling != NULL)
	{
		pFrame = SearchBoneFrame(_BoneName, _pFrame->pFrameSibling);
		if (pFrame != NULL) 
		{
			return pFrame;
		}
	}
	if (_pFrame->pFrameFirstChild != NULL)
	{
		pFrame = SearchBoneFrame(_BoneName, _pFrame->pFrameFirstChild);
		if (pFrame != NULL) 
		{
			return pFrame;
		}
	}
	return NULL;
}

//--------------------------------------------------------------
//�{�[���̃}�g���b�N�X�擾( �{�[���̖��O )
//--------------------------------------------------------------
D3DXMATRIX CSkinMesh::GetBoneMatrix(std::string _BoneName)
{
	MYFRAME* pFrame = SearchBoneFrame(_BoneName, m_pFrameRoot);
	//�{�[�����������
	if (pFrame != NULL) 
	{
		//�{�[���s���Ԃ�
		return pFrame->CombinedTransformationMatrix;
	}
	//�{�[����������Ȃ����
	else 
	{
		//�P�ʍs���Ԃ�
		D3DXMATRIX TmpMatrix;
		D3DXMatrixIdentity(&TmpMatrix);
		return TmpMatrix;
	}
}

//--------------------------------------------------------------
//�{�[���̃}�g���b�N�X�|�C���^�擾( �{�[���̖��O )
//--------------------------------------------------------------
D3DXMATRIX* CSkinMesh::GetpBoneMatrix(std::string _BoneName)
{
	//���ӁjRokDeBone�p�ɐݒ�(�Ώۃ{�[���̈��̍s����Ƃ��Ă���)
	MYFRAME* pFrame = SearchBoneFrame(_BoneName, m_pFrameRoot);
	//�{�[�����������
	if (pFrame != NULL) 
	{
		return &pFrame->CombinedTransformationMatrix;
	}
	//�{�[����������Ȃ����
	else 
	{
		//NULL��Ԃ�
		return NULL;
	}
}
