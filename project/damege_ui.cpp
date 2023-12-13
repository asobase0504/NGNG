#include "damege_ui.h"

const int CDamegeUI::DELETE_TIME	(60);
static int cnt = 0;

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CDamegeUI::CDamegeUI() :
	m_time(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CDamegeUI::~CDamegeUI()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CDamegeUI::Init()
{
	cnt++;
	CProcedure3D::Init();
	m_time = 0;
	return S_OK;
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CDamegeUI::Update()
{
	CProcedure3D::Update();

	if (m_time >= (DELETE_TIME * 0.5f))
	{
		float alpha = (DELETE_TIME - m_time) / (DELETE_TIME - DELETE_TIME * 0.5f);
		//SetColorAlpha(alpha);
	}

	if (m_time >= DELETE_TIME)
	{
		Uninit();
	}
	m_time++;
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CDamegeUI * CDamegeUI::Create(D3DXVECTOR3 pos, D3DXCOLOR color, const int inNumber)
{
	CDamegeUI* ui;
	ui = new CDamegeUI;

	assert(ui != nullptr);

	ui->SetPos(pos);
	ui->Init();
	ui->SetNumber(inNumber);
	ui->SetColor(color);
	ui->SetSize(D3DXVECTOR3(2.5f, 2.5f, 0.0f));
	ui->SetMove(D3DXVECTOR3(0.0f, 0.1f, 0.0f));

	return ui;
}
