#include "ui_bg.h"

CUIBackGround::CUIBackGround()
{
}

CUIBackGround::~CUIBackGround()
{
}

CUIBackGround * CUIBackGround::Create(D3DXVECTOR2 inPos, D3DXVECTOR2 inSize,float alpha)
{
	CUIBackGround* ui_bg = new CUIBackGround;
	ui_bg->Init();
	ui_bg->SetPos(D3DXVECTOR3(inPos.x, inPos.y, 0.0f));
	ui_bg->SetSize(D3DXVECTOR3(inSize.x, inSize.y, 0.0f));

	ui_bg->m_outLine = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	ui_bg->m_outLine->SetPos(D3DXVECTOR3(inPos.x, inPos.y, 0.0f));
	ui_bg->m_outLine->SetSize(D3DXVECTOR3(inSize.x + 2.0f, inSize.y + 2.0f, 0.0f));
	ui_bg->m_outLine->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, alpha));
	ui_bg->SetEndChildren(ui_bg->m_outLine);

	auto CreateCorner = [&ui_bg, &alpha](int index, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	{
		ui_bg->m_corner[index] = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
		ui_bg->m_corner[index]->SetPos(D3DXVECTOR3(pos.x, pos.y, 0.0f));
		ui_bg->m_corner[index]->SetSize(D3DXVECTOR3(size.x, size.y, 0.0f));
		ui_bg->m_corner[index]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
		ui_bg->SetEndChildren(ui_bg->m_corner[index]);
	};

	CreateCorner(0, D3DXVECTOR2(inPos.x - inSize.x - 1.0f, inPos.y - inSize.y + 9.0f), D3DXVECTOR2(1.0f, 11.0f));
	CreateCorner(1, D3DXVECTOR2(inPos.x - inSize.x + 10.0f, inPos.y - inSize.y - 1.0f), D3DXVECTOR2(10.0f, 1.0f));

	CreateCorner(2, D3DXVECTOR2(inPos.x + inSize.x + 1.0f, inPos.y - inSize.y + 9.0f), D3DXVECTOR2(1.0f, 11.0f));
	CreateCorner(3, D3DXVECTOR2(inPos.x + inSize.x - 10.0f, inPos.y - inSize.y - 1.0f), D3DXVECTOR2(10.0f, 1.0f));

	CreateCorner(4, D3DXVECTOR2(inPos.x - inSize.x - 1.0f, inPos.y + inSize.y - 9.0f), D3DXVECTOR2(1.0f, 11.0f));
	CreateCorner(5, D3DXVECTOR2(inPos.x - inSize.x + 10.0f, inPos.y + inSize.y + 1.0f), D3DXVECTOR2(10.0f, 1.0f));

	CreateCorner(6, D3DXVECTOR2(inPos.x + inSize.x + 1.0f, inPos.y + inSize.y - 9.0f), D3DXVECTOR2(1.0f, 11.0f));
	CreateCorner(7, D3DXVECTOR2(inPos.x + inSize.x - 10.0f, inPos.y + inSize.y + 1.0f), D3DXVECTOR2(10.0f, 1.0f));

	ui_bg->m_bg = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	ui_bg->m_bg->SetPos(D3DXVECTOR3(inPos.x, inPos.y, 0.0f));
	ui_bg->m_bg->SetSize(D3DXVECTOR3(inSize.x, inSize.y, 0.0f));
	ui_bg->m_bg->SetColor(D3DXCOLOR(0.1f, 0.1f, 0.1f, alpha));
	ui_bg->SetEndChildren(ui_bg->m_bg);

	return ui_bg;
}