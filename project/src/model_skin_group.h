//**************************************************************
//
// オブジェクトXを読み込んで保存する処理 [objectX_group.h]
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _SKINMESH_GROUP_H_
#define _SKINMESH_GROUP_H_

//==============================================================
// include
//==============================================================


//派生フレーム構造体 (それぞれのメッシュ用の最終ワールド行列を追加する）
struct MYFRAME : public D3DXFRAME
{
	D3DXMATRIX CombinedTransformationMatrix;
	// オフセット行列(インデックス付描画用)
	D3DXMATRIX OffsetMat;
	// 行列テーブルのインデックス番号(インデックス付用)
	DWORD OffsetID;
};

//派生メッシュコンテナー構造体(
//コンテナーがテクスチャを複数持てるようにポインターのポインターを追加する）
struct MYMESHCONTAINER : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*  ppTextures;
	DWORD dwWeight; //重みの個数（重みとは頂点への影響。）
	DWORD dwBoneNum; //ボーンの数
	LPD3DXBUFFER pBoneBuffer; //ボーン・テーブル
	std::vector<D3DXMATRIX*> ppBoneMatrix; //全てのボーンのワールド行列の先頭ポインター
	std::vector<D3DXMATRIX> pBoneOffsetMatrices; //フレームとしてのボーンのワールド行列のポインター
	LPD3DXMESH pOriMesh; //オリジナルメッシュ用
	DWORD NumPaletteEntries; //パレットサイズ

							 // Work用
	std::vector<D3DXMATRIX> m_WorkBoneMatArray;
	// 影響するフレームへの参照配列。描画時にこのフレームの行列を使う。
	std::vector<MYFRAME*> BoneFrameArray;
	MYMESHCONTAINER()
	{
		ppBoneMatrix.clear();
		pBoneOffsetMatrices.clear();
	}
};

//Xファイル内のアニメーション階層を読み下してくれるクラスを派生させる。
//ID3DXAllocateHierarchyは派生すること想定して設計されている。
class MY_HIERARCHY : public ID3DXAllocateHierarchy
{
public:
	MY_HIERARCHY() {}
	STDMETHOD(CreateFrame)(THIS_ LPCSTR, LPD3DXFRAME*);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCTSTR, CONST D3DXMESHDATA*, CONST D3DXMATERIAL*,
		CONST D3DXEFFECTINSTANCE*, DWORD, CONST DWORD *, LPD3DXSKININFO, LPD3DXMESHCONTAINER *);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER);
private:
};

//==============================================================
// クラスの定義
//==============================================================
class CSkinMeshGroup
{
private: /* プライベート定数 */
	static const wchar_t* filePath;

public:
	struct SSkinMeshInfo
	{
		LPD3DXFRAME frameRoot;	// ボーン情報
		LPD3DXANIMATIONCONTROLLER pAnimController;	// アニメーションコントローラ
		MY_HIERARCHY cHierarchy;	// ヒエラルキークラス変数
	};
public:
	//--------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------
private:
	CSkinMeshGroup();
	static CSkinMeshGroup* m_instance;
public:
	static CSkinMeshGroup* GetInstance();
	~CSkinMeshGroup();

	//--------------------------------------------------------------
	// メンバー関数
	//--------------------------------------------------------------
	void LoadAll();		// 全ての読み込み
	void UnloadAll();	// 全ての破棄
	void Load(std::string inKey, std::string inFileName);	// 指定の読み込み
	void Load(std::vector<std::string> inModel) { Load(inModel[0], inModel[1]); }			// 指定の読み込み
	void Unload(std::string inKey);				// 指定の破棄

	SSkinMeshInfo GetSkinMeshInfo(std::string inTag) { return m_skinMesh[inTag]; }

	void FreeAnim(std::string inKey, LPD3DXFRAME pFrame);
private: /* プライベート関数 */
	//bool ExistsKey(std::string inKey) { return m_skinMesh.count(inKey) != 0; }	// Map内に指定されたKeyが存在するか否か
private:
	std::map<std::string, SSkinMeshInfo, std::less<>> m_skinMesh;	// スキンメッシュの情報
	std::list<std::string> m_keyList;	// Keyの情報群
};
#endif