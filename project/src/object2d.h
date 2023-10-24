//**************************************************************
//
// 2D�I�u�W�F�N�g
// Author : �l�c����
//
//**************************************************************
#ifndef _OBJECT2D_H_			// ���̃}�N����`������ĂȂ�������
#define _OBJECT2D_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "renderer.h"
#include "object.h"
#include "texture.h"

//==============================================================
// 4�_�̒��_
//==============================================================
struct PositionVec4
{
	float P0, P1, P2, P3;
	constexpr PositionVec4() : P0(0.0f), P1(0.0f), P2(0.0f), P3(0.0f) { }
	constexpr PositionVec4(float _P0, float _P1, float _P2, float _P3) : P0(_P0), P1(_P1), P2(_P2), P3(_P3) { }
};

//==============================================================
// 2D�I�u�W�F�N�g�N���X
//==============================================================
class CObject2d : public CObject
{
public:
	// ���_�t�H�[�}�b�g
	const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	enum EAnchor
	{
		ANCHOR_CENTER,
		ANCHOR_left,
	};

	// ���_�f�[�^
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;
		float rhw;
		D3DCOLOR col;
		D3DXVECTOR2 tex;	// �e�N�X�`�����W(���x��1)
	};

private:
	//polygon�̊g��T�C�Y
	static const D3DXVECTOR3 m_Vtx[4];

public:
	static CObject2d *Create(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_BG);

	CObject2d(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_BG);
	~CObject2d() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetTex(PositionVec4 Tex);
	void SetColor(const D3DXCOLOR& inColor) override;
	void SetAnimation(const int U, const int V, const int Speed, const int Drawtimer, const bool loop);

	bool PointAndAABB(const D3DXVECTOR3& inPos);
protected:
	LPDIRECT3DVERTEXBUFFER9 &GetVtx() { return m_vtxBuff; }

private:
	void Animation();

protected:
	int  m_timer;
	float m_scale;
	D3DXMATRIX m_mtxWorld;	// �}�g���b�N�X

private:
	LPDIRECT3DVERTEXBUFFER9	m_vtxBuff;

	/* �A�j���[�V�����n�� */
	// ���݂̃A�j���[�V������
	int m_counterAnim;
	int m_patternAnimX;
	int m_patternAnimY;

	// ������
	int m_divisionX;
	int m_divisionY;
	int m_divisionMAX;

	// �A�j���[�V�������x
	int m_animationSpeed;
	int m_animationSpeedCount;
	
	// �A�j���[�V��������
	int m_timar;
	int m_timaCount;

	bool m_isOnAnimation;	// �A�j���[�V�����g�p�̗L��
	bool m_isLoop;		// ���[�v�A�j���[�V�������ۂ�
};
#endif
