//**************************************************************
//
// utility.h
// Author : katsuki mizuki
//
//**************************************************************
#ifndef _UTILITY_H_	// ���̃}�N����`������ĂȂ�������
#define _UTILITY_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================

//--------------------------------------------------------------
// �o�͂Ƀe�L�X�g���o�͂���B
//--------------------------------------------------------------
#ifdef _DEBUG
#define DEBUG_PRINT(...) _RPT_BASE(_CRT_WARN, __FILE__, __LINE__, NULL, __VA_ARGS__)
#else
#define DEBUG_PRINT(...) ((void)0)
#endif

//==============================================================
// �v���g�^�C�v�錾
//==============================================================
//--------------------------------------------------------------
// �p�x�̐��K��
// ����  : pAngle / �p�x
//--------------------------------------------------------------
float NormalizeAngle(float& pAngle);

//--------------------------------------------------------------
// �z�[�~���O
// ����1  : D3DXVECTOR3 *pPosOut / �ʒu
// ����2  : D3DXVECTOR3 &posNow / ���݂̈ʒu
// ����3  : D3DXVECTOR3 &posDest / �ړI�̈ʒu
// ����4  : float fSpeed / ����
// �Ԓl  : bool / �ړI�̈ʒu�ɒ��������ǂ���
//--------------------------------------------------------------
bool Homing(D3DXVECTOR3 *pPosOut, const D3DXVECTOR3 &posNow, const D3DXVECTOR3 &posDest, float fSpeed);

//--------------------------------------------------------------
// �����m����n���Đ������ۂ����f
// ����  : float inRate / �����m��
// �Ԓl  : bool / ����
//--------------------------------------------------------------
bool IsSuccessRate(float inRate);

//--------------------------------------------------------------
// �����_�̃����_��
// ����1  : float fMax / �ő�l
// ����2  : float fMin / �ŏ��l
// �Ԓl  : float / �����_���l
//--------------------------------------------------------------
float FloatRandom(float fMax, float fMin);

//--------------------------------------------------------------
// �����̃����_��
// ����1  : int nMax / �ő�l
// ����2  : int nMin / �ŏ��l
// �Ԓl  : int / �����_���l
//--------------------------------------------------------------
int IntRandom(int nMax, int nMin);

//--------------------------------------------------------------
// sin�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
// ����1  : int nTime / �^�C��
// ����2  : float fCycle / ����
// �Ԓl  : float / 1.0f�`0.0f��sin�J�[�u
//--------------------------------------------------------------
float SinCurve(int nTime, float fCycle);

//--------------------------------------------------------------
// cos�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
// ����1  : int nTime / �^�C��
// ����2  : float fCycle / ����
// �Ԓl  : float / 1.0f�`0.0f��cos�J�[�u
//--------------------------------------------------------------
float CosCurve(int nTime, float fCycle);

//--------------------------------------------------------------
// �J�[�u�̒l���A���Ă���
// ����1  : float fCurve / �J�[�u
// ����2  : float fMax / �ő�l
// ����3  : float fMin / �ŏ��l
// �Ԓl  : float / �J�[�u
//--------------------------------------------------------------
float Curve(float fCurve, float fMax, float fMin);

//--------------------------------------------------------------
// WorldCastScreen
// ����1  : D3DXVECTOR3 *screenPos // �X�N���[�����W
// ����2  : D3DXVECTOR3 screenSize // �X�N���[���T�C�Y
// ����3  : D3DXMATRIX* mtxView // �r���[�}�g���b�N�X
// ����4  : D3DXMATRIX* mtxProjection // �v���W�F�N�V�����}�g���b�N�X
// �Ԓl   : D3DXVECTOR3 2D��3D
//--------------------------------------------------------------
D3DXVECTOR3 WorldCastScreen(D3DXVECTOR3 *screenPos,			// �X�N���[�����W
	D3DXVECTOR3 screenSize,									// �X�N���[���T�C�Y
	D3DXMATRIX* mtxView,									// �r���[�}�g���b�N�X
	D3DXMATRIX* mtxProjection);								// �v���W�F�N�V�����}�g���b�N�X

//--------------------------------------------------------------
// ScreenCastWorld
// ����1  : D3DXVECTOR3  *screenPos // �X�N���[�����W
// ����2  : D3DXVECTOR3 screenSize
// �Ԓl  : D3DXVECTOR3 / 3D��2D
//--------------------------------------------------------------
D3DXVECTOR3 ScreenCastWorld(const D3DXVECTOR3 &screenPos,			// �X�N���[�����W
	D3DXVECTOR3 screenSize);

//--------------------------------------------------------------
// ScreenCastWorld
// Author : Hamada Ryuuga
// ����1  : D3DXMATRIX  *pOut // �X�N���[�����W
// ����2  : D3DXVECTOR3 inPos
// ����3  : D3DXVECTOR3 inRot
// �Ԓl  : D3DXMATRIX / �v�Z�����}�g���b�N�X
//--------------------------------------------------------------
D3DXMATRIX *GiftMtx(D3DXMATRIX *pOut, const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot);

// �Z�o�n��
//--------------------------------------------------------------
// 2D�̊O��
// ����1  : D3DXVECTOR3  *v1 // 
// ����2  : D3DXVECTOR3*  v2
// �Ԓl  : float/ �O��
//--------------------------------------------------------------
float Vec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2);

//--------------------------------------------------------------
// 2D�̓���
// ����1  : D3DXVECTOR3  *v1 // 
// ����2  : D3DXVECTOR3*  v2
// �Ԓl  : float / ����
//--------------------------------------------------------------
float Vec2Dot(D3DXVECTOR3* v1, D3DXVECTOR3* v2);

D3DXVECTOR3 ConvertQuaternionfromRadian(const D3DXQUATERNION& inQuaternion);

const D3DXMATRIX InverseMatrixConversion(const D3DXMATRIX& inMtx);
//--------------------------------------------------------------
// Author : Hamada Ryuuga
// Author : Yuda Kaito
// ����1  : float X		// ����
// �Ԓl  : float		// �v�Z����
//--------------------------------------------------------------
namespace ease
{
// �����ŎZ�o
float InSine(float x);
float OutSine(float x);
float InOutSine(float x);

// 2�̗ݏ�ŎZ�o
float InQuad(float x);
float OutQuad(float x);
float InOutQuad(float x);

// 3�̗ݏ�ŎZ�o
float InCubic(float x);
float OutCubic(float x);
float InOutCubic(float x);

// 4�̗ݏ�ŎZ�o
float InQuart(float x);
//float OutQuart(float x);
//float InOutQuart(float x);

// 5�̗ݏ�ŎZ�o
float InQuint(float x);
//float OutQuint(float x);
//float InOutQuint(float x);

// �w���֐��ŎZ�o
float InExpo(float x);
//float OutExpo(float x);
//float InOutExpo(float x);

float InCirc(float x);
//float OutCirc(float x);
//float InOutCirc(float x);

float InBack(float x, float s = 1.70158f);
//float OutBack(float x);
//float InOutBack(float x);

float InElastic(float x, float c = (2.f * D3DX_PI) / 3.f);
float OutElastic(float x, float c = (2.f * D3DX_PI) / 3.f);
float InOutElastic(float x, float c = (2.f * D3DX_PI) / 4.5f);

float OutBounce(float x, float n = 7.5625f, float d = 2.75f);
float InBounce(float x, float n = 7.5625f, float d = 2.75f);
float InOutBounce(float x, float n = 7.5625f, float d = 2.75f);
}

#endif // !_UTILITY_H_
