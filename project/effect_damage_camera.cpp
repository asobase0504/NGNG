#include "effect_damage_camera.h"
#include "application.h"

CEffectDamageCamera::CEffectDamageCamera() : CObject2d(CTaskGroup::EPriority::LEVEL_3D_UI)
{
}

CEffectDamageCamera::~CEffectDamageCamera()
{
}

HRESULT CEffectDamageCamera::Init()
{
	CObject2d::Init();
	SetPos(CApplication::CENTER_POS);
	SetSize(CApplication::CENTER_POS);
	SetColor(D3DXCOLOR(0.02f,0.02f,0.02f,0.5f));

	m_time = 12;
	m_maxTime = 12;
	return S_OK;
}

void CEffectDamageCamera::Update()
{
	CObject2d::Update();

	float rata = (float)m_time / (float)m_maxTime * 0.1f;
	SetColorAlpha(rata);

	if (m_time <= 0)
	{
		Uninit();
	}
	m_time--;
}

CEffectDamageCamera * CEffectDamageCamera::Create()
{
	CEffectDamageCamera* effect = new CEffectDamageCamera;
	effect->Init();
	return effect;
}
