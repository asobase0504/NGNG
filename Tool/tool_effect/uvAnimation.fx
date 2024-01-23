float2 g_animationUV;
float4 g_diffuse;
bool g_hasMainTexture;
bool g_hasMaskTexture;

// ワールドビュープロジェクションの構造体
struct WVP
{
	float4x4 mtxWorld;
	float4x4 cameraView;
	float4x4 cameraProjection;
};
WVP g_wvp;

sampler textureSampler : register(s0);		// メインのテクスチャサンプラー
sampler maskTextureSampler : register(s1);	// マスクのテクスチャサンプラー

struct VS_INPUT
{	// 頂点シェーダー入力用
	float4 pos : POSITION;
	float3 nor : NORMAL;
	float4 col : COLOR0;
	float2 texCoord : TEXCOORD0;
};
struct VS_OUTPUT
{	// 頂点シェーダー出力用
	float4 pos : SV_POSITION;
	float4 col : COLOR0;
	float2 texCoord : TEXCOORD0;
};

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 頂点を射影空間へ移動
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
float4 TransVertex(float4 vtx)
{
	vtx = mul(vtx, g_wvp.mtxWorld);
	vtx = mul(vtx, g_wvp.cameraView);
	vtx = mul(vtx, g_wvp.cameraProjection);
	return vtx;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// テクスチャ座標正規化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
float2 NormalizeTexCoord(float2 texCoord)
{
	float2 normalizedTexCoord;
	normalizedTexCoord.x = texCoord.x - floor(texCoord.x);
	normalizedTexCoord.y = texCoord.y - floor(texCoord.y);
	return normalizedTexCoord;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// エントリポイント
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
float4 Entry(float4 pos : POSITION) : SV_POSITION
{
	return pos;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 頂点シェーダー
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
VS_OUTPUT VS_Main(VS_INPUT inVS)
{
	VS_OUTPUT outVS;
	outVS.pos = TransVertex(inVS.pos);
	outVS.col = inVS.col;

	// テクスチャUVアニメーション
	float2 animCoord = g_animationUV;
	outVS.texCoord = inVS.texCoord + animCoord;

	return outVS;
}

struct PS_OUTPUT
{	// ピクセルシェーダー出力用
	float4 col : SV_Target;
};

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ピクセルシェーダー
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
PS_OUTPUT PS_Main(VS_OUTPUT inVS)
{
	PS_OUTPUT outPS;
	float2 normalizedTexCoord = NormalizeTexCoord(inVS.texCoord);
	float4 maskColor = float4(1.0f,1.0f,1.0f,1.0f);

	// テクスチャサンプリング
	if (g_hasMainTexture)
	{	// メインテクスチャ
		outPS.col = tex2D(textureSampler, normalizedTexCoord);
	}

	if (g_hasMaskTexture)
	{	// マスクテクスチャ
		maskColor = tex2D(maskTextureSampler, normalizedTexCoord);
		outPS.col *= maskColor;
	}

	outPS.col *= g_diffuse;

	return outPS;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// テクニック
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
technique TechShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS_Main();
		PixelShader = compile ps_2_0 PS_Main();
	}
}