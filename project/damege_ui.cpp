#include "damege_ui.h"

const int CDamegeUI::DELETE_TIME	(60);

CDamegeUI::CDamegeUI()
{
}

CDamegeUI::~CDamegeUI()
{
}

HRESULT CDamegeUI::Init()
{
	CProcedure3D::Init();
	m_time = 0;
	return S_OK;
}

void CDamegeUI::Update()
{
	CProcedure3D::Update();

	if (m_time >= (DELETE_TIME * 0.5f))
	{
		float alpha = (DELETE_TIME - m_time) / (DELETE_TIME - DELETE_TIME * 0.5f);
		SetColorAlpha(alpha);
	}

	if (m_time >= DELETE_TIME)
	{
		Uninit();
	}
	m_time++;
}

CDamegeUI * CDamegeUI::Create(D3DXVECTOR3 pos, D3DXCOLOR color, const int inNumber)
{
	CDamegeUI* ui;
	ui = new CDamegeUI;

	assert(ui != nullptr);

	ui->Init();
	ui->SetNumber(inNumber);
	ui->SetPos(pos);
	ui->SetColor(color);
	ui->SetSize(D3DXVECTOR3(2.5f, 2.5f, 0.0f));
	ui->SetMove(D3DXVECTOR3(0.0f, 0.1f, 0.0f));

	return ui;
}
