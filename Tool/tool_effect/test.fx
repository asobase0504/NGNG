// �萔���W�X�^�͍ő�ŁA���_�V�F�[�_�[��256�A�s�N�Z���V�F�[�_�[��32�܂Ő錾�ł���
// 2_0�Ȃ�16�܂ł̉\��������܂�
float4x4 worldViewProjectionMatrix : register(c0);

texture g_tex;

// ���[���h�r���[�v���W�F�N�V�����̍\����
struct WVP
{
	float4x4 mtxWorld;
	float4x4 cameraView;
	float4x4 cameraProjection;
};
WVP g_wvp;

// �I�u�W�F�N�g�̃e�N�X�`���ApDevice->SetTexture()�Őݒ肳�ꂽ���
sampler textureSampler : register(s0);

// input�͂悭�Ă��Aoutput����_���ȃZ�}���e�B�N�X������
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

// �ꎞ���W�X�^�̍ő吔�𒴂���ƃR���p�C���G���[���o��炵��
// �i���g_...�̕ϐ�����̊֐��Ɏg����͍̂ő�R�܂Łj
// ���_���ˉe��Ԃֈړ�
float4 TransVertex(float4 vtx)
{
	vtx = mul(vtx, g_wvp.mtxWorld);
	vtx = mul(vtx, g_wvp.cameraView);
	vtx = mul(vtx, g_wvp.cameraProjection);
	return vtx;
}

// �e�N�X�`�����W���K��
float2 NormalizeTexCoord(float2 texCoord)
{
	float2 normalizedTexCoord;
	normalizedTexCoord.x = texCoord.x - floor(texCoord.x);
	normalizedTexCoord.y = texCoord.y - floor(texCoord.y);
	return normalizedTexCoord;
}

// �����̊|���Z( A * B )�͒P���ȏ�Z�ŁAmul�͍s��̏�Z�ɂȂ�
// �G���g���|�C���g�̊֐���p�ӂ��Ȃ��ƃR���p�C���G���[
VS_OUTPUT test(VS_INPUT inVS)
{
	VS_OUTPUT outVS;
	outVS.pos = TransVertex(inVS.pos);
	outVS.col = inVS.col;
	outVS.texCoord = inVS.texCoord;
	return outVS;
}

struct PS_OUTPUT
{	// �s�N�Z���V�F�[�_�[�o�͗p
	float4 col : SV_Target;
};

// memo0: vertexShader�̕Ԃ�l�������Ƃ��Ȃ��ƁA��ʑS�̂�tex2D(textureSampler, inPS.texCoord)�̕Ԃ�l�̐F�ɓh��Ԃ��ꂽ�肷��
PS_OUTPUT PS_Main(VS_OUTPUT inVS)
{
	PS_OUTPUT outPS;
	//float2 normalizedTexCoord = NormalizeTexCoord(inVS.texCoord);

	// �e�N�X�`���T���v�����O
	outPS.col = tex2D(textureSampler, inVS.texCoord) * inVS.col;
	return outPS;
}

technique TechShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 test();
		PixelShader = compile ps_2_0 PS_Main();
	}
}