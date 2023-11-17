// -------------------------------------------------------------
// グローバル変数
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

float4 vLightDir;	// ライトの方向
float4 vDiffuse;	// ライト＊メッシュの色
float4 vAmbient;	// 色
float3 vEyeVec;		// カメラとオブジェの方向ベクトル
float3 vEyeDir;		// カメラの向き

float Test;
float TimeTarget;

// -------------------------------------------------------------
// 頂点シェーダからピクセルシェーダに渡すデータ
// -------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos			: POSITION;			// 位置
	float4 Color		: COLOR0;			// 色
	float2 Tex			: TEXCOORD0;		// テクスチャ
	float3 Normal		: TEXCOORD1;
};

// -------------------------------------------------------------
// テクスチャ
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
// 頂点シェーダー
//=========================================
VS_OUTPUT MATRIX_VS(
	float4 Pos    : POSITION,	// ローカル位置座標
	float4 Normal : NORMAL,		// 法線ベクトル
	float2 Tex : TEXCOORD		// テクスチャの法線ベクトル
)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;		// 出力データ

	float4x4 WVP = mul(mWorld, mSize);
	WVP = mul(WVP, mRot);
	WVP = mul(WVP, mTrans);
	WVP = mul(WVP, mParent);

	return Out;
}

//=========================================
// 頂点シェーダー
//=========================================
VS_OUTPUT VS(
	float4 Pos    : POSITION,	// ローカル位置座標
	float4 Normal : NORMAL,		// 法線ベクトル
	float2 Tex : TEXCOORD		// テクスチャの法線ベクトル
)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;		// 出力データ

	float4x4 WVP = mul(mWorld, mScale);
	WVP = mul(WVP, mRot);
	WVP = mul(WVP, mTrans);

	float4x4 MVP = mul(WVP, mView);
	MVP = mul(MVP, mProj);

	// 座標変換
	Out.Pos = mul(Pos, MVP);

	// テクスチャ座標
	Out.Tex = Tex;

	// 拡散光＋環境光
	float3 L = -(vLightDir.xyz);		// ローカル座標系でのライトベクトル

	//法線ベクトル。
	float3 N = normalize(Normal.xyz);

	Out.Normal = N;
	Out.Color = vDiffuse *(max(vAmbient, dot(N, N)));;

	return Out;
}

//=========================================
// 頂点シェーダー・黒
//=========================================
VS_OUTPUT BLACK_VS(
	float4 Pos    : POSITION,	// ローカル位置座標
	float4 Normal : NORMAL,		// 法線ベクトル
	float2 Tex : TEXCOORD		// テクスチャの法線ベクトル
)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;		// 出力データ

	float4x4 WVP = mul(mWorld, mScale);
	WVP = mul(WVP, mRot);
	float4 n = mul(Normal, WVP);
	WVP = mul(WVP, mTrans);

	float4x4 MVP = mul(WVP, mView);
	MVP = mul(MVP, mProj);

	float4 pos = mul(Pos, MVP);
	n.zw = 0;

	// 座標変換
	Out.Pos = pos + 0.5f*n;

	// テクスチャ座標
	Out.Tex = Tex;

	// 拡散光＋環境光
	float3 L = -(vLightDir.xyz);		// ローカル座標系でのライトベクトル

	//法線ベクトル。
	float3 N = -normalize(Normal.xyz);

	Out.Color = float4(1.0f,1.0f,1.0f,1.0f);

	Out.Normal = N;

	return Out;
}

//=========================================
//ピクセルシェーダー
//=========================================
float4 PS(VS_OUTPUT In) : COLOR
{
	return In.Color;		// 拡散光＋環境光(テクスチャの色)
}

//=========================================
// PS : 反転時見えなくするやつ
//=========================================
float4 VSPS(VS_OUTPUT In) : COLOR
{
	return In.Color;		// 拡散光＋環境光(テクスチャの色)
}

//=========================================
// 白黒シェーダー
//=========================================
float4 Mono_PS(VS_OUTPUT In) : COLOR
{
	/* メモ : ピクセルシェーダーはピクセル単位で処理が通るので、
	もしかしたら徐々に灰色にするのはシェーダーの処理ではないのでは？
	というか、段々灰色になる処理は難しいのでは？ */

	//float ColSimple = (In.Color.r + In.Color.g + In.Color.b) / 3.0f;

	//In.Color.r -= (In.Color.r - ColSimple) / 120 * (Test - 120) * -1;
	//In.Color.g -= (In.Color.g - ColSimple) / 120 * (Test - 120) * -1;
	//In.Color.b -= (In.Color.b - ColSimple) / 120 * (Test - 120) * -1;

	//In.Color = float4(In.Color.r, In.Color.g, In.Color.b, 1.0f);

	return In.Color;		// 拡散光＋環境光(テクスチャの色)
}

//=========================================
//トゥーン頂点シェーダー
//=========================================
VS_OUTPUT ToonVS(float4 Pos    : POSITION,
	float4 Normal : NORMAL,
	float2 Tex : TEXCOORD0)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;		// 出力データ

	Out.Normal = normalize(Normal.xyz);

	// 座標変換
	Out.Pos = mul(Pos, mWVP);

	// テクスチャ座標
	Out.Tex = Tex;

	// 拡散光＋環境光
	float3 L = -(vLightDir.xyz);	// ローカル座標系でのライトベクトル

	//法線ベクトル。
	float3 N = normalize(Normal.xyz);

	Out.Color = vDiffuse;

	return Out;
}

//=========================================
//トゥーンピクセルシェーダー
//=========================================
float4 ToonPS(VS_OUTPUT In) : COLOR0
{
	float4 Out;

	//ハーフランバート拡散照明によるライティング計算
	float3 L = -(vLightDir.xyz);	// ローカル座標系でのライトベクトル

	//法線ベクトル。
	float3 N = In.Normal;

	float p = (max(vAmbient, dot(N, L))) + (max(vAmbient, dot(N, -L)));
	p = p * 0.5f + 0.5f;
	p = p * p;
	
	//色情報をテクセルのＵ成分とし、トゥーンマップテクスチャーから光の反射率を取得する
	float4 Col = In.Color * tex2D(Samp, float2(p, 0.0f));
	
	//色情報を格納する
	Out = Col;
	
	return Out;
}


// -------------------------------------------------------------
// テクニック
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
