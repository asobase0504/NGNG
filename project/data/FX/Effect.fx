// -------------------------------------------------------------
// �O���[�o���ϐ�
// -------------------------------------------------------------

float4x4 mWorld;
float4x4 mProj;
float4x4 mView;
float4x4 mWVP;
float4x4 mSize;
float4x4 mRot;
float4x4 mTrans;
float4x4 mParent;
float4x4 mScale;

float4 vLightDir;	// ���C�g�̕���
float4 vDiffuse;	// ���C�g�����b�V���̐F
float4 vAmbient;	// �F
float3 vEyeVec;		// �J�����ƃI�u�W�F�̕����x�N�g��
float3 vEyeDir;		// �J�����̌���

float Test;
float TimeTarget;

// -------------------------------------------------------------
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
// -------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos			: POSITION;			// �ʒu
	float4 Color		: COLOR0;			// �F
	float2 Tex			: TEXCOORD0;		// �e�N�X�`��
	float3 Normal		: TEXCOORD1;
};

// -------------------------------------------------------------
// �e�N�X�`��
// -------------------------------------------------------------
texture Tex;
sampler Samp = sampler_state
{
	Texture = <Tex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;

	AddressU = WRAP;
	AddressV = WRAP;
};

//=========================================
// ���_�V�F�[�_�[
//=========================================
VS_OUTPUT MATRIX_VS(
	float4 Pos    : POSITION,	// ���[�J���ʒu���W
	float4 Normal : NORMAL,		// �@���x�N�g��
	float2 Tex : TEXCOORD		// �e�N�X�`���̖@���x�N�g��
)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;		// �o�̓f�[�^

	float4x4 WVP = mul(mWorld, mSize);
	WVP = mul(WVP, mRot);
	WVP = mul(WVP, mTrans);
	WVP = mul(WVP, mParent);

	return Out;
}

//=========================================
// ���_�V�F�[�_�[
//=========================================
VS_OUTPUT VS(
	float4 Pos    : POSITION,	// ���[�J���ʒu���W
	float4 Normal : NORMAL,		// �@���x�N�g��
	float2 Tex : TEXCOORD		// �e�N�X�`���̖@���x�N�g��
)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;		// �o�̓f�[�^

	float4x4 WVP = mul(mWorld, mScale);
	WVP = mul(WVP, mRot);
	WVP = mul(WVP, mTrans);

	float4x4 MVP = mul(WVP, mView);
	MVP = mul(MVP, mProj);

	// ���W�ϊ�
	Out.Pos = mul(Pos, MVP);

	// �e�N�X�`�����W
	Out.Tex = Tex;

	// �g�U���{����
	float3 L = -(vLightDir.xyz);		// ���[�J�����W�n�ł̃��C�g�x�N�g��

	//�@���x�N�g���B
	float3 N = normalize(Normal.xyz);

	Out.Normal = N;
	Out.Color = vDiffuse *(max(vAmbient, dot(N, N)));;

	return Out;
}

//=========================================
// ���_�V�F�[�_�[�E��
//=========================================
VS_OUTPUT BLACK_VS(
	float4 Pos    : POSITION,	// ���[�J���ʒu���W
	float4 Normal : NORMAL,		// �@���x�N�g��
	float2 Tex : TEXCOORD		// �e�N�X�`���̖@���x�N�g��
)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;		// �o�̓f�[�^

	float4x4 WVP = mul(mWorld, mScale);
	WVP = mul(WVP, mRot);
	float4 n = mul(Normal, WVP);
	WVP = mul(WVP, mTrans);

	float4x4 MVP = mul(WVP, mView);
	MVP = mul(MVP, mProj);

	float4 pos = mul(Pos, MVP);
	n.zw = 0;

	// ���W�ϊ�
	Out.Pos = pos + 0.5f*n;

	// �e�N�X�`�����W
	Out.Tex = Tex;

	// �g�U���{����
	float3 L = -(vLightDir.xyz);		// ���[�J�����W�n�ł̃��C�g�x�N�g��

	//�@���x�N�g���B
	float3 N = -normalize(Normal.xyz);

	Out.Color = float4(1.0f,1.0f,1.0f,1.0f);

	Out.Normal = N;

	return Out;
}

//=========================================
//�s�N�Z���V�F�[�_�[
//=========================================
float4 PS(VS_OUTPUT In) : COLOR
{
	return In.Color;		// �g�U���{����(�e�N�X�`���̐F)
}

//=========================================
// PS : ���]�������Ȃ�������
//=========================================
float4 VSPS(VS_OUTPUT In) : COLOR
{
	return In.Color;		// �g�U���{����(�e�N�X�`���̐F)
}

//=========================================
// �����V�F�[�_�[
//=========================================
float4 Mono_PS(VS_OUTPUT In) : COLOR
{
	/* ���� : �s�N�Z���V�F�[�_�[�̓s�N�Z���P�ʂŏ������ʂ�̂ŁA
	�����������珙�X�ɊD�F�ɂ���̂̓V�F�[�_�[�̏����ł͂Ȃ��̂ł́H
	�Ƃ������A�i�X�D�F�ɂȂ鏈���͓���̂ł́H */

	//float ColSimple = (In.Color.r + In.Color.g + In.Color.b) / 3.0f;

	//In.Color.r -= (In.Color.r - ColSimple) / 120 * (Test - 120) * -1;
	//In.Color.g -= (In.Color.g - ColSimple) / 120 * (Test - 120) * -1;
	//In.Color.b -= (In.Color.b - ColSimple) / 120 * (Test - 120) * -1;

	//In.Color = float4(In.Color.r, In.Color.g, In.Color.b, 1.0f);

	return In.Color;		// �g�U���{����(�e�N�X�`���̐F)
}

//=========================================
//�g�D�[�����_�V�F�[�_�[
//=========================================
VS_OUTPUT ToonVS(float4 Pos    : POSITION,
	float4 Normal : NORMAL,
	float2 Tex : TEXCOORD0)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;		// �o�̓f�[�^

	Out.Normal = normalize(Normal.xyz);

	// ���W�ϊ�
	Out.Pos = mul(Pos, mWVP);

	// �e�N�X�`�����W
	Out.Tex = Tex;

	// �g�U���{����
	float3 L = -(vLightDir.xyz);	// ���[�J�����W�n�ł̃��C�g�x�N�g��

	//�@���x�N�g���B
	float3 N = normalize(Normal.xyz);

	Out.Color = vDiffuse;

	return Out;
}

//=========================================
//�g�D�[���s�N�Z���V�F�[�_�[
//=========================================
float4 ToonPS(VS_OUTPUT In) : COLOR0
{
	float4 Out;

	//�n�[�t�����o�[�g�g�U�Ɩ��ɂ�郉�C�e�B���O�v�Z
	float3 L = -(vLightDir.xyz);	// ���[�J�����W�n�ł̃��C�g�x�N�g��

	//�@���x�N�g���B
	float3 N = In.Normal;

	float p = (max(vAmbient, dot(N, L))) + (max(vAmbient, dot(N, -L)));
	p = p * 0.5f + 0.5f;
	p = p * p;
	
	//�F�����e�N�Z���̂t�����Ƃ��A�g�D�[���}�b�v�e�N�X�`���[������̔��˗����擾����
	float4 Col = In.Color * tex2D(Samp, float2(p, 0.0f));
	
	//�F�����i�[����
	Out = Col;
	
	return Out;
}


// -------------------------------------------------------------
// �e�N�j�b�N
// -------------------------------------------------------------
technique Diffuse
{
	pass P0
	{
		VertexShader = compile vs_2_0 ToonVS();
		PixelShader = compile ps_2_0 ToonPS();
	}
	pass P1
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 Mono_PS();
	}
	pass P2
	{
		VertexShader = compile vs_2_0 BLACK_VS();
		PixelShader = compile ps_2_0 VSPS();
	}
	pass P3
	{
		VertexShader = compile vs_2_0 MATRIX_VS();
		PixelShader = compile ps_2_0 PS();
	}
}
