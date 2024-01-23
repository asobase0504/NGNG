float2 g_animationUV;
float4 g_diffuse;
bool g_hasMainTexture;
bool g_hasMaskTexture;

// ���[���h�r���[�v���W�F�N�V�����̍\����
struct WVP
{
	float4x4 mtxWorld;
	float4x4 cameraView;
	float4x4 cameraProjection;
};
WVP g_wvp;

sampler textureSampler : register(s0);		// ���C���̃e�N�X�`���T���v���[
sampler maskTextureSampler : register(s1);	// �}�X�N�̃e�N�X�`���T���v���[

struct VS_INPUT
{	// ���_�V�F�[�_�[���͗p
	float4 pos : POSITION;
	float3 nor : NORMAL;
	float4 col : COLOR0;
	float2 texCoord : TEXCOORD0;
};
struct VS_OUTPUT
{	// ���_�V�F�[�_�[�o�͗p
	float4 pos : SV_POSITION;
	float4 col : COLOR0;
	float2 texCoord : TEXCOORD0;
};

//��������������������������������������������������������������
// ���_���ˉe��Ԃֈړ�
//��������������������������������������������������������������
float4 TransVertex(float4 vtx)
{
	vtx = mul(vtx, g_wvp.mtxWorld);
	vtx = mul(vtx, g_wvp.cameraView);
	vtx = mul(vtx, g_wvp.cameraProjection);
	return vtx;
}

//��������������������������������������������������������������
// �e�N�X�`�����W���K��
//��������������������������������������������������������������
float2 NormalizeTexCoord(float2 texCoord)
{
	float2 normalizedTexCoord;
	normalizedTexCoord.x = texCoord.x - floor(texCoord.x);
	normalizedTexCoord.y = texCoord.y - floor(texCoord.y);
	return normalizedTexCoord;
}

//��������������������������������������������������������������
// �G���g���|�C���g
//��������������������������������������������������������������
float4 Entry(float4 pos : POSITION) : SV_POSITION
{
	return pos;
}

//��������������������������������������������������������������
// ���_�V�F�[�_�[
//��������������������������������������������������������������
VS_OUTPUT VS_Main(VS_INPUT inVS)
{
	VS_OUTPUT outVS;
	outVS.pos = TransVertex(inVS.pos);
	outVS.col = inVS.col;

	// �e�N�X�`��UV�A�j���[�V����
	float2 animCoord = g_animationUV;
	outVS.texCoord = inVS.texCoord + animCoord;

	return outVS;
}

struct PS_OUTPUT
{	// �s�N�Z���V�F�[�_�[�o�͗p
	float4 col : SV_Target;
};

//��������������������������������������������������������������
// �s�N�Z���V�F�[�_�[
//��������������������������������������������������������������
PS_OUTPUT PS_Main(VS_OUTPUT inVS)
{
	PS_OUTPUT outPS;
	float2 normalizedTexCoord = NormalizeTexCoord(inVS.texCoord);
	float4 maskColor = float4(1.0f,1.0f,1.0f,1.0f);

	// �e�N�X�`���T���v�����O
	if (g_hasMainTexture)
	{	// ���C���e�N�X�`��
		outPS.col = tex2D(textureSampler, normalizedTexCoord);
	}

	if (g_hasMaskTexture)
	{	// �}�X�N�e�N�X�`��
		maskColor = tex2D(maskTextureSampler, normalizedTexCoord);
		outPS.col *= maskColor;
	}

	outPS.col *= g_diffuse;

	return outPS;
}

//��������������������������������������������������������������
// �e�N�j�b�N
//��������������������������������������������������������������
technique TechShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS_Main();
		PixelShader = compile ps_2_0 PS_Main();
	}
}