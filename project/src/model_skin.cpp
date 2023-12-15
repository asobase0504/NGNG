//=============================================================================
//
// 3Dモデルクラス(model3D.h)
// Author : 唐﨑結斗
// 概要 : 3Dモデル生成を行う
//
//=============================================================================

//==============================================================
// include
//==============================================================
#include "model_skin.h"
#include "application.h"
#include "renderer.h"
#include "model_skin_group.h"
#include "texture.h"
#include "utility.h"
#include "camera.h"
#include "light.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CSkinMesh::CSkinMesh() :
	CObject(CTaskGroup::LEVEL_3D_1)
{
	//単位行列化
	D3DXMatrixIdentity(&(this->m_mtxWorld));
	//アニメーション時間初期化
	m_AnimeTime = 0;
	//アニメーションスピード初期化
	m_AnimSpeed = SKIN_ANIME_SPEED; // 固定

	//現在のアニメーショントラック初期化
	m_CurrentTrack = 0;
	//アニメーションデータトラック初期化
	//有効にする
	m_CurrentTrackDesc.Enable = true;
	//影響度100%
	m_CurrentTrackDesc.Weight = 1;
	//開始位置初期化
	m_CurrentTrackDesc.Position = 0;
	//速度
	m_CurrentTrackDesc.Speed = 1;

	m_isLoop = false;
	m_isAnimeEnd = false;
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CSkinMesh::Init(std::string pMeshPass)
{
	CObject::Init();
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	std::string TmpMeshPass;
	TmpMeshPass = pMeshPass;

	CSkinMeshGroup::SSkinMeshInfo info = CSkinMeshGroup::GetInstance()->GetSkinMeshInfo(pMeshPass);

	m_pFrameRoot = info.frameRoot;
	m_pAnimController = info.pAnimController;

	//ボーン行列初期化
	AllocateAllBoneMatrices(m_pFrameRoot, m_pFrameRoot);

	m_pAnimSet.resize(m_pAnimController->GetNumAnimationSets());

	//アニメーショントラックの取得
	for (DWORD i = 0; i < m_pAnimController->GetNumAnimationSets(); i++)
	{
		//アニメーション取得
		m_pAnimController->GetAnimationSet(i, &(m_pAnimSet[i]));
	}

	//すべてのフレーム参照変数の生成
	CreateFrameArray(m_pFrameRoot);
	return S_OK;
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CSkinMesh::Update()
{
	//アニメーション時間を更新
	m_AnimeTime++;

	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	// 行列初期化関数(第1引数の行列を単位行列に初期化)
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}

//--------------------------------------------------------------
//スキンメッシュの描画
//--------------------------------------------------------------
void CSkinMesh::Draw()
{
	//現在のアニメーション番号を適応
	m_pAnimController->SetTrackAnimationSet(0, m_pAnimSet[m_CurrentTrack]);
	//0(再生中の)トラックからトラックデスクをセットする
	m_pAnimController->SetTrackDesc(0, &(m_CurrentTrackDesc));
	//アニメーション時間データの更新
	m_pAnimController->AdvanceTime(m_AnimSpeed, NULL);
	//アニメーションデータを更新
	UpdateFrameMatrices(m_pFrameRoot, &m_mtxWorld);
	//アニメーション描画
	DrawFrame(m_pFrameRoot);
	//0(再生中の)トラックから更新したトラックデスクを取得する
	m_pAnimController->GetTrackDesc(0, &m_CurrentTrackDesc);
}

//--------------------------------------------------------------
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : モーションキャラクター3Dを生成する
//--------------------------------------------------------------
CSkinMesh * CSkinMesh::Create(std::string Name)
{
	// オブジェクトインスタンス
	CSkinMesh *pSkinMesh = nullptr;

	// メモリの解放
	pSkinMesh = new CSkinMesh;

	// メモリの確保ができなかった
	assert(pSkinMesh != nullptr);

	// 数値の初期化
	pSkinMesh->Init(Name);

	// インスタンスを返す
	return pSkinMesh;
}

//--------------------------------------------------------------
// release
//--------------------------------------------------------------
void CSkinMesh::Release()
{

}

//--------------------------------------------------------------
//ボーン行列の初期化
//--------------------------------------------------------------
HRESULT CSkinMesh::AllocateBoneMatrix(LPD3DXFRAME pFrameRoot, LPD3DXMESHCONTAINER pMeshContainerBase)
{
	MYFRAME *pFrame = NULL;
	DWORD dwBoneNum = 0;

	//メッシュコンテナの型をオリジナルの型として扱う
	//(メッシュコンテナ生成時にオリジナルの型として作っているので問題はないが、
	//基本ダウンキャストは危険なので多用は避けるべき)
	MYMESHCONTAINER *pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;

	//スキンメッシュでなければ
	if (pMeshContainer->pSkinInfo == NULL)
	{
		return S_OK;
	}

	//ボーンの数取得
	dwBoneNum = pMeshContainer->pSkinInfo->GetNumBones();
	//各ボーンのワールド行列格納用領域を確保
	pMeshContainer->ppBoneMatrix.resize(dwBoneNum);

	//ボーンの数だけループ
	for (DWORD i = 0; i < dwBoneNum; i++)
	{
		//子フレーム(ボーン)のアドレスを検索してpFrameに格納
		pFrame = (MYFRAME*)D3DXFrameFind(pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(i));
		//子フレームがなければ処理を終了する
		if (pFrame == NULL)
		{
			return E_FAIL;
		}
		//各ボーンのワールド行列格納用変数に最終行列を格納
		pMeshContainer->ppBoneMatrix[i] = &pFrame->CombinedTransformationMatrix;
	}
	return S_OK;
}

//--------------------------------------------------------------
// マテリアル内全体のボーン行列の初期化
//--------------------------------------------------------------
HRESULT CSkinMesh::AllocateAllBoneMatrices(LPD3DXFRAME pFrameRoot, LPD3DXFRAME pFrame)
{
	//階層の走査(メモリを確保したメッシュコンテナ領域を探す処理)
	if (pFrame->pMeshContainer != nullptr)
	{
		//ボーン行列の初期化処理
		if (FAILED(AllocateBoneMatrix(pFrameRoot, pFrame->pMeshContainer)))
		{
			return E_FAIL;
		}
	}
	//再起判断処理
	if (pFrame->pFrameSibling != nullptr)
	{
		if (FAILED(AllocateAllBoneMatrices(pFrameRoot, pFrame->pFrameSibling)))
		{
			return E_FAIL;
		}
	}
	if (pFrame->pFrameFirstChild != nullptr)
	{
		if (FAILED(AllocateAllBoneMatrices(pFrameRoot, pFrame->pFrameFirstChild)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

void CSkinMesh::ShaderDraw(MYMESHCONTAINER* pMeshContainer, MYFRAME* pFrame)
{
	//スキンメッシュの描画
	if (pMeshContainer->pSkinInfo == NULL)
	{
		//通常メッシュの場合
		MessageBox(NULL, "スキンメッシュXファイルの描画に失敗しました。", NULL, MB_OK);
		exit(EOF);
	}

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	DWORD i, k;
	DWORD dwBlendMatrixNum;
	DWORD dwPrevBoneID;
	LPD3DXBONECOMBINATION pBoneCombination;
	UINT iMatrixIndex;
	D3DXMATRIX mStack;

	extern LPD3DXEFFECT pEffect;		// シェーダー
	if (pEffect == nullptr)
	{
		assert(false);
		return;
	}

	/* pEffectに値が入ってる */

	//-------------------------------------------------
	// シェーダの設定
	//-------------------------------------------------

	// 計算用マトリックス
	D3DXMATRIX mtxScale;
	D3DXMATRIX mtxSize;
	D3DXMATRIX mtxTrans;
	D3DXMATRIX mtxRot;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 大きさを反映
	D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);
	// 大きさを反映
	D3DXMatrixScaling(&mtxSize, 1.03f, 1.03f, 1.03f);
	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMATRIX mtxParent;
	D3DXMatrixIdentity(&mtxParent);

	//------------------------------------------------------------------------------------------//

	// タスクグループ情報
	CTaskGroup* taskGroup = CApplication::GetInstance()->GetTaskGroup();

	// カメラ情報
	CCamera* pCamera = (CCamera*)taskGroup->SearchRoleTop(CTask::ERole::ROLE_CAMERA, GetPriority());

	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	if (pCamera != nullptr)
	{
		viewMatrix = pCamera->GetMtxView();
		projMatrix = pCamera->GetMtxProje();
	}

	pEffect->SetTechnique(m_hTechnique);
	pEffect->Begin(NULL, 0);

	// ワールド射影変換行列
	// シェーダーに行列を渡す
	pEffect->SetMatrix(m_hWorld, &m_mtxWorld);
	pEffect->SetMatrix(m_hScale, &mtxScale);
	pEffect->SetMatrix(m_hSize, &mtxSize);
	pEffect->SetMatrix(m_hRot, &mtxRot);
	pEffect->SetMatrix(m_hTrans, &mtxTrans);
	pEffect->SetMatrix(m_hProj, &projMatrix);
	pEffect->SetMatrix(m_hView, &viewMatrix);

	// シェーダーに目的の値を渡す
	pEffect->SetFloat(m_hTimeTarget, m_TimeTarget);

	// シェーダーにカメラ座標を渡す
	D3DXVECTOR3 c = pCamera->GetPos();
	D3DXVECTOR3 camerapos = D3DXVECTOR3(c.x, c.y, c.z);
	D3DXVECTOR3 objpos = GetPos();

	D3DXVECTOR3 vec = camerapos - objpos;

	D3DXVec3Normalize(&vec, &vec);
	NormalizeAngle(vec.x);
	NormalizeAngle(vec.y);
	NormalizeAngle(vec.z);

	pEffect->SetVector(m_hCameraVec, &D3DXVECTOR4(vec.x, vec.y, vec.z, 0.0f));

	// シェーダーに描画から経過した時間を渡す
	pEffect->SetFloat(m_hTime, 0);

	// ライト情報
	CLight* lightClass = (CLight*)taskGroup->SearchRoleTop(CTask::ERole::ROLE_LIGHT, GetPriority());

	if (lightClass == nullptr)
	{
		lightClass = (CLight*)taskGroup->SearchRoleTop(CTask::ERole::ROLE_LIGHT, GetPriority() - 1);
	}

	D3DLIGHT9 light = lightClass->GetLight(0);

	// ライトの方向
	D3DXVECTOR4 lightDir = D3DXVECTOR4(light.Direction.x, light.Direction.y, light.Direction.z, 0);
	// ライトの方向をシェーダーに渡す
	pEffect->SetVector(m_hvLightDir, &lightDir);


	//ボーンテーブルからバッファの先頭アドレスを取得
	pBoneCombination = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneBuffer->GetBufferPointer());
	//dwPrevBoneIDにUINT_MAXの値(0xffffffff)を格納
	dwPrevBoneID = UINT_MAX;
	//スキニング計算
	for (i = 0; i < pMeshContainer->dwBoneNum; i++)
	{
		dwBlendMatrixNum = 0;
		//影響している行列数取得
		for (k = 0; k < pMeshContainer->dwWeight; k++)
		{
			//UINT_MAX(-1)
			if (pBoneCombination[i].BoneId[k] != UINT_MAX)
			{
				//現在影響を受けているボーンの数
				dwBlendMatrixNum = k;
			}
		}
		//ジオメトリブレンディングを使用するために行列の個数を指定
		pDevice->SetRenderState(D3DRS_VERTEXBLEND, dwBlendMatrixNum);
		pEffect->SetInt(m_hMtxNum, (int)&dwBlendMatrixNum);
	
		//影響している行列の検索
		for (k = 0; k < pMeshContainer->dwWeight; k++)
		{
			//iMatrixIndexに1度の呼び出しで描画出来る各ボーンを識別する値を格納
			//( このBoneID配列の長さはメッシュの種類によって異なる
			//( インデックスなしであれば　=　頂点ごとの重み であり
			// インデックスありであれば　=　ボーン行列パレットのエントリ数)
			//現在のボーン(i番目)からみてk番目のボーンid
			iMatrixIndex = pBoneCombination[i].BoneId[k];
			//行列の情報があれば
			if (iMatrixIndex != UINT_MAX)
			{
				//mStackにオフセット行列*ボーン行列を格納
				mStack = pMeshContainer->pBoneOffsetMatrices[iMatrixIndex] * (*pMeshContainer->ppBoneMatrix[iMatrixIndex]);
				//行列スタックに格納
				pDevice->SetTransform(D3DTS_WORLDMATRIX(k), &mStack);
			}
			pEffect->SetMatrixArray(m_hBoneStack, &mStack, i);
		}

		D3DMATERIAL9 TmpMat = pMeshContainer->pMaterials[pBoneCombination[i].AttribId].MatD3D;
		TmpMat.Emissive.a = TmpMat.Diffuse.a = TmpMat.Ambient.a = 1.0f;

		//dwPrevBoneIDに属性テーブルの識別子を格納
		dwPrevBoneID = pBoneCombination[i].AttribId;

		// モデルの色の設定 
		{
			D3DXVECTOR4 Diffuse;
			Diffuse = D3DXVECTOR4(TmpMat.Diffuse.r, TmpMat.Diffuse.g, TmpMat.Diffuse.b, TmpMat.Diffuse.a);

			Diffuse.w = m_color.a;

			pEffect->SetVector(m_hvDiffuse, &Diffuse);
		}
		{
			D3DXVECTOR4 Ambient;
			//Ambient = D3DXVECTOR4(pMat[nCntMat].MatD3D.Ambient.r, pMat[nCntMat].MatD3D.Ambient.g, pMat[nCntMat].MatD3D.Ambient.b, pMat[nCntMat].MatD3D.Ambient.a);
			Ambient = D3DXVECTOR4(0.0f, 0.0f, 0.0f, TmpMat.Ambient.a);
			pEffect->SetVector(m_hvAmbient, &Ambient);
		}

		LPDIRECT3DTEXTURE9 texture = CTexture::GetInstance()->GetTexture("TOON");
		if (texture != nullptr)
		{// テクスチャの適応
			tex0 = texture;
		}

		// テクスチャの設定
		pEffect->SetTexture(m_hTexture, tex0);
		// 通常モデルの描画
		pEffect->BeginPass(1);
		pMeshContainer->MeshData.pMesh->DrawSubset(i);
		pEffect->EndPass();

	}
	pEffect->End();

}

//--------------------------------------------------------------
//フレーム内のそれぞれのメッシュをレンダリングする
//--------------------------------------------------------------
void CSkinMesh::RenderMeshContainer(MYMESHCONTAINER* pMeshContainer, MYFRAME* pFrame)
{
	extern LPD3DXEFFECT pEffect;		// シェーダー
	if (pEffect == nullptr)
	{
		assert(false);
		return;
	}

	/* pEffectに値が入ってる */

	//スキンメッシュの描画
	if (pMeshContainer->pSkinInfo == NULL)
	{
		//通常メッシュの場合
		MessageBox(NULL, "スキンメッシュXファイルの描画に失敗しました。", NULL, MB_OK);
		exit(EOF);
	}

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	DWORD i, k;
	DWORD dwBlendMatrixNum;
	LPD3DXBONECOMBINATION pBoneCombination;
	UINT iMatrixIndex;
	D3DXMATRIX mStack;

	//ボーンテーブルからバッファの先頭アドレスを取得
	pBoneCombination = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneBuffer->GetBufferPointer());
	//スキニング計算
	for (i = 0; i < pMeshContainer->dwBoneNum; i++)
	{
		dwBlendMatrixNum = 0;
		//影響している行列数取得
		for (k = 0; k < pMeshContainer->dwWeight; k++)
		{
			//UINT_MAX(-1)
			if (pBoneCombination[i].BoneId[k] != UINT_MAX)
			{
				//現在影響を受けているボーンの数
				dwBlendMatrixNum = k;
			}
		}
		//ジオメトリブレンディングを使用するために行列の個数を指定
		pDevice->SetRenderState(D3DRS_VERTEXBLEND, dwBlendMatrixNum);
		//影響している行列の検索
		for (k = 0; k < pMeshContainer->dwWeight; k++)
		{
			//iMatrixIndexに1度の呼び出しで描画出来る各ボーンを識別する値を格納
			//( このBoneID配列の長さはメッシュの種類によって異なる
			//( インデックスなしであれば　=　頂点ごとの重み であり
			// インデックスありであれば　=　ボーン行列パレットのエントリ数)
			//現在のボーン(i番目)からみてk番目のボーンid
			iMatrixIndex = pBoneCombination[i].BoneId[k];
			//行列の情報があれば
			if (iMatrixIndex != UINT_MAX)
			{
				//mStackにオフセット行列*ボーン行列を格納
				mStack = pMeshContainer->pBoneOffsetMatrices[iMatrixIndex] * (*pMeshContainer->ppBoneMatrix[iMatrixIndex]);
				//行列スタックに格納
				pDevice->SetTransform(D3DTS_WORLDMATRIX(k), &mStack);
			}
		}
		D3DMATERIAL9 TmpMat = pMeshContainer->pMaterials[pBoneCombination[i].AttribId].MatD3D;
		pDevice->SetMaterial(&TmpMat);
		pDevice->SetTexture(0, pMeshContainer->ppTextures[pBoneCombination[i].AttribId]);
		//メッシュの描画
		pMeshContainer->MeshData.pMesh->DrawSubset(i);
	}
}

//--------------------------------------------------------------
//フレームをレンダリングする。
//--------------------------------------------------------------
void CSkinMesh::DrawFrame(LPD3DXFRAME pFrameBase)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pFrame->pMeshContainer;
	while (pMeshContainer != NULL)
	{
		//SHADER_KIND a = GetpShader()->GetShaderKind();
		////シェーダを使用しているのなら専用の描画関数に飛ばす
		//if( GetpShader() != NULL && GetpShader()->GetShaderKind() == SHADER_KIND_LAMBERT ){
		// ShaderDraw( pDevice, ControlNum, pMeshContainer, pFrame ); 
		//}else{
		ShaderDraw(pMeshContainer, pFrame);
		// }
		//次のメッシュコンテナへアクティブを移す
		pMeshContainer = (MYMESHCONTAINER*)pMeshContainer->pNextMeshContainer;
	}
	if (pFrame->pFrameSibling != NULL)
	{
		DrawFrame(pFrame->pFrameSibling);
	}
	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawFrame(pFrame->pFrameFirstChild);
	}
}

//--------------------------------------------------------------
//フレーム内のメッシュ毎にワールド変換行列を更新する
//--------------------------------------------------------------
void CSkinMesh::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	MYFRAME *pFrame = (MYFRAME*)pFrameBase;
	if (pParentMatrix != NULL)
	{
		//CombinedTransformationMatrixに最終行列を格納
		D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);
	}
	else
	{
		//CombinedTransformationMatrixに最終行列を格納
		pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
	}
	if (pFrame->pFrameSibling != NULL)
	{
		UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
	}
	if (pFrame->pFrameFirstChild != NULL)
	{
		UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
	}
}

//--------------------------------------------------------------
//すべてのフレームポインタ格納処理関数
//--------------------------------------------------------------
void CSkinMesh::CreateFrameArray(LPD3DXFRAME _pFrame)
{
	if (_pFrame == nullptr) { return; }
	//フレームアドレス格納
	MYFRAME* pMyFrame = (MYFRAME*)_pFrame;
	m_animeEndTime++;

	//子フレーム検索
	if (pMyFrame->pFrameFirstChild != NULL) 
	{
		CreateFrameArray(pMyFrame->pFrameFirstChild);
	}
	//兄弟フレーム検索
	if (pMyFrame->pFrameSibling != NULL) 
	{
		CreateFrameArray(pMyFrame->pFrameSibling);
	}
}

//--------------------------------------------------------------
//オブジェクトのアニメーション変更( 変更するアニメーション番号 )
//--------------------------------------------------------------
void CSkinMesh::ChangeAnim(DWORD _NewAnimNum)
{
	// -の値になるようだったら。
	if (_NewAnimNum < 0)
	{
		_NewAnimNum = 0;
	}
	// 最大値を超えようとしてたら
	if (_NewAnimNum > m_pAnimController->GetNumAnimationSets())
	{
		_NewAnimNum = m_pAnimController->GetNumAnimationSets();
	}

	//新規アニメーションに変更
	m_CurrentTrack = _NewAnimNum;
	//アニメーションタイムを初期化
	m_AnimeTime = 0;
	//アニメーションを最初の位置から再生させる
	m_pAnimController->GetTrackDesc(0, &m_CurrentTrackDesc);
	m_CurrentTrackDesc.Position = 0;
	m_pAnimController->SetTrackDesc(0, &m_CurrentTrackDesc);
}

//--------------------------------------------------------------
//対象のボーンを検索
//--------------------------------------------------------------
MYFRAME* CSkinMesh::SearchBoneFrame(std::string _BoneName, D3DXFRAME* _pFrame)
{
	MYFRAME* pFrame = (MYFRAME*)_pFrame;
	if (strcmp(pFrame->Name, _BoneName.c_str()) == 0)
	{
		return pFrame;
	}
	if (_pFrame->pFrameSibling != NULL)
	{
		pFrame = SearchBoneFrame(_BoneName, _pFrame->pFrameSibling);
		if (pFrame != NULL) 
		{
			return pFrame;
		}
	}
	if (_pFrame->pFrameFirstChild != NULL)
	{
		pFrame = SearchBoneFrame(_BoneName, _pFrame->pFrameFirstChild);
		if (pFrame != NULL) 
		{
			return pFrame;
		}
	}
	return NULL;
}

//--------------------------------------------------------------
//ボーンのマトリックス取得( ボーンの名前 )
//--------------------------------------------------------------
D3DXMATRIX CSkinMesh::GetBoneMatrix(std::string _BoneName)
{
	MYFRAME* pFrame = SearchBoneFrame(_BoneName, m_pFrameRoot);
	//ボーンが見つかれば
	if (pFrame != NULL) 
	{
		//ボーン行列を返す
		return pFrame->CombinedTransformationMatrix;
	}
	//ボーンが見つからなければ
	else 
	{
		//単位行列を返す
		D3DXMATRIX TmpMatrix;
		D3DXMatrixIdentity(&TmpMatrix);
		return TmpMatrix;
	}
}

//--------------------------------------------------------------
//ボーンのマトリックスポインタ取得( ボーンの名前 )
//--------------------------------------------------------------
D3DXMATRIX* CSkinMesh::GetpBoneMatrix(std::string _BoneName)
{
	//注意）RokDeBone用に設定(対象ボーンの一つ先の行列をとってくる)
	MYFRAME* pFrame = SearchBoneFrame(_BoneName, m_pFrameRoot);
	//ボーンが見つかれば
	if (pFrame != NULL) 
	{
		return &pFrame->CombinedTransformationMatrix;
	}
	//ボーンが見つからなければ
	else 
	{
		//NULLを返す
		return NULL;
	}
}
