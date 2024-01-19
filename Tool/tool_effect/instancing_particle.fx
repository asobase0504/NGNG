float3 g_cameraPos;

// テクスチャ
texture g_tex;

// ワールドビュープロジェクションの構造体
struct WVP
{
	float4x4 mtxWorld;
	float4x4 cameraView;
	float4x4 cameraProjection;
};
WVP g_wvp;

sampler textureSampler = sampler_state {
	texture = <g_tex>;
	MipFilter = LINEAR;
	MinFilter = POINT;
	MagFilter = POINT;
};

struct VS_INPUT
{
	float2 vtx : POSITION;
	float2 texCoord : TEXCOORD0;
};
struct VS_INSTANCEDATA
{	// 頂点シェーダー入力用
	float3 pos : POSITION1;
	float4 col : COLOR1;
};
struct VS_OUTPUT
{	// 頂点シェーダー出力用
	float4 pos : SV_POSITION;
	float4 col : COLOR1;
	float2 texCoord : TEXCOORD0;
};

// 頂点を射影空間へ移動
float4 TransVertex(float4 vtx, float4x4 mtx)
{
	vtx = mul(vtx, mtx);
	vtx = mul(vtx, g_wvp.cameraView);
	vtx = mul(vtx, g_wvp.cameraProjection);
	return vtx;
}

// テクスチャ座標正規化
float2 NormalizeTexCoord(float2 texCoord)
{
	float2 normalizedTexCoord;
	normalizedTexCoord.x = texCoord.x - floor(texCoord.x);
	normalizedTexCoord.y = texCoord.y - floor(texCoord.y);
	return normalizedTexCoord;
}

float4 Entry(float4 pos : POSITION) : SV_POSITION
{
	return pos;
}

VS_OUTPUT VS_Main(VS_INPUT inVS, VS_INSTANCEDATA instData)
{
	VS_OUTPUT outVS;

	float4x4 mtxView = g_wvp.cameraView;
	float4x4 mtxWorld;
	mtxWorld._11 = mtxView._11;
	mtxWorld._12 = mtxView._21;
	mtxWorld._13 = mtxView._31;
	mtxWorld._14 = 0.0f;
	mtxWorld._21 = mtxView._12;
	mtxWorld._22 = mtxView._22;
	mtxWorld._23 = mtxView._32;
	mtxWorld._24 = 0.0f;
	mtxWorld._31 = mtxView._13;
	mtxWorld._32 = mtxView._23;
	mtxWorld._33 = mtxView._33;
	mtxWorld._34 = 0.0f;
	mtxWorld._41 = instData.pos.x;
	mtxWorld._42 = instData.pos.y;
	mtxWorld._43 = instData.pos.z;
	mtxWorld._44 = 1.0f;

	outVS.pos = TransVertex(float4(inVS.vtx.x, inVS.vtx.y, 0.0f, 1.0f), mtxWorld);
	outVS.col = instData.col;
	outVS.texCoord = inVS.texCoord;

	return outVS;
}

struct PS_OUTPUT
{	// ピクセルシェーダー出力用
	float4 col : SV_Target;
};

PS_OUTPUT PS_Main(VS_OUTPUT inVS)
{
	PS_OUTPUT outPS;
	float2 normalizedTexCoord = NormalizeTexCoord(inVS.texCoord);

	// テクスチャサンプリング
	outPS.col = tex2D(textureSampler, inVS.texCoord) * inVS.col;
	return outPS;
}

technique TechShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS_Main();
		PixelShader = compile ps_2_0 PS_Main();
	}
}