//**************************************************************
//
// �J����
// Author : Hamada Ryuuga
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _CAMERA_H_
#define _CAMERA_H_

//==============================================================
// include
//==============================================================
#include "renderer.h"
#include "task.h"

//==============================================================
// �J�����N���X
//==============================================================
class CCamera : public CTask
{
private:
	static const float VIEWING_ANGLE;	// ����p
public:
	CCamera(CTaskGroup::EPriority inPriority = CTaskGroup::LEVEL_3D_1);
	~CCamera() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Set(int Type);

	// Getter
	const D3DXMATRIX& GetMtxProje() { return m_MtxProject; }
	const D3DXMATRIX& GetMtxView() { return m_MtxView; }
	const D3DXVECTOR3& GetPos() { return m_posV; }

	const D3DXVECTOR3 VectorCombinedRot(const D3DXVECTOR3& inVector);

	// �J������h�炷
	void Shake(float ShakeFrame, float Magnitude);

protected:
	D3DXVECTOR3 m_posV;			// �ʒu
	D3DXVECTOR3 m_posVDest;		// �ړI�n����̍�
	D3DXVECTOR3 m_posR;			// �����_
	D3DXVECTOR3 m_posRDest;		// �ړI�n����̍�
	D3DXVECTOR3 m_vecU;			// �x�N�g��
	D3DXVECTOR3 m_rot;			// �ʒu��]
	D3DXMATRIX m_MtxProject;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_MtxView;		// �r���[�}�g���b�N�X
	int m_Type;

	/* �h�� */
	float m_nCntFrame;	// �h���t���[���J�E���g
	float m_Magnitude;	// �h��
};

#endif		// _CAMERA_H_
