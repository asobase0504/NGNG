//**************************************************************
//
// �I�u�W�F�N�gX���� [objectX.h]
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//==============================================================
// include
//==============================================================
#include "object.h"

//==============================================================
// �O���錾
//==============================================================
class CObjectPolygon3D;

//==============================================================
// �N���X�̒�`
//==============================================================
class CObjectX : public CObject
{
public:
	//--------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------
	explicit CObjectX(CTaskGroup::EPriority nPriority = CTaskGroup::LEVEL_3D_1);
	~CObjectX() override;

	//--------------------------------------------------------------
	// �����o�[�֐�
	//--------------------------------------------------------------
	HRESULT Init() override;	// ������

	/* �`�� */
	void Draw() override;
	void DrawMaterial();
	void Projection();			// ���s���e����

	/* �������� */
	static CObjectX *Create(D3DXVECTOR3 pos, CTaskGroup::EPriority nPriority = CTaskGroup::LEVEL_3D_1);
	void LoadModel(std::string aFileName);		// ���f���̓ǂݍ��ݏ���

	/* �傫���{�� */
	void SetScale(const D3DXVECTOR3& inScale);
	const D3DXVECTOR3& GetScale() const { return m_scale; }

	/* ��]�n�� */
	void SetRot(const D3DXVECTOR3& inRot) override;
	void SetMtxRot(const D3DXVECTOR3& inRot);
	void SetMtxRot(const D3DXMATRIX& inRot) { m_mtxRot = inRot; }
	void SetMtxQuaternion(const D3DXQUATERNION& inQuaternion) { D3DXMatrixRotationQuaternion(&m_mtxRot, &inQuaternion); }
	const D3DXMATRIX& GetMtxRot() { return m_mtxRot; }

	/* ���_�ʒu */
	void CalculationVtx();	// ���_�ő召�l�̌v�Z
	void SetMaxVtx(const D3DXVECTOR3& Maxvtx) { m_maxVtx = Maxvtx; }	// ���_�ő�l�ݒ�
	const D3DXVECTOR3& GetMaxVtx() { return m_maxVtx; }					// ���_�ő�l�擾
	void SetMinVtx(const D3DXVECTOR3& Minvtx) { m_maxVtx = Minvtx; }	// ���_�ő�l�ݒ�
	const D3DXVECTOR3& GetMinVtx() { return m_minVtx; }					// ���_�ŏ��l�擾

	/* �e�q�֌W */
	void SetParent(CObjectX* inParent) { m_parent = inParent; }	// �e���f���̐ݒ�
	CObjectX* GetParent() const { return m_parent; }				// �e���f���̎擾

	/* �}�e���A���֌W */
	void SetMaterialDiffuse(unsigned int index, const D3DXCOLOR& inColor);
	const D3DXCOLOR& GetMaterialDiffuse(unsigned int index) { return m_materialDiffuse.at(index); }

	/* �����x */
	void SetColorAlpha(float inAlpha) { m_color.a = inAlpha; }

	/* OutLine */
	void AttachOutLine(bool isAttach = true) { m_isHasOutLine = isAttach; }
	/* Shadow */
	void AttachShadow(bool isAttach = true) { m_isHasShadow = isAttach; }

	/* �����蔻�� */
	bool SphereAndAABB(CObjectX* inObjectX,D3DXVECTOR3* outPos = nullptr);
	bool RayAndAABB(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inNormal, D3DXVECTOR3* outPos = nullptr);
	bool SegmentAndAABB(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inPos2, D3DXVECTOR3* outPos = nullptr);

	float AABBAndPointLength(CObjectX* inObject, D3DXVECTOR3* outDist = nullptr);

private:
	//--------------------------------------------------------------
	// �����o�[�ϐ�
	//--------------------------------------------------------------
	D3DXVECTOR3 m_scale;		// �傫���{��

	D3DXVECTOR3 m_minVtxOrigin;	// ���f���̒��_�ŏ��l�f�t�H���g�l
	D3DXVECTOR3 m_maxVtxOrigin;	// ���f���̒��_�ő�l�f�t�H���g�l
	D3DXVECTOR3 m_minVtx;		// ���f���̒��_�ŏ��l
	D3DXVECTOR3 m_maxVtx;		// ���f���̒��_�ő�l

	D3DXMATRIX m_mtxRot;		// ��]�s��

	LPD3DXMESH m_mesh;			// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_buffMat;	// �}�e���A�����ւ̃|�C���^
	std::unordered_map<unsigned int,D3DXCOLOR> m_materialDiffuse;	// �}�e���A����Diffuse
	DWORD m_numMat;				// �}�e���A�����̐�

	CObjectX *m_parent;		// �e���f���̏��
	bool m_isCollision;		// �����蔻�肪�K�v��

	bool m_isHasOutLine;	// �A�E�g���C�����g����
	bool m_isHasShadow;		// �A�E�g���C�����g����

	bool m_isBlackFlash;

	std::string modelKey;
};
#endif