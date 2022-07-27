#include "PreCompile.h"
#include "MPGauge.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>

MPGauge::MPGauge() 
	: mpUIRenderer(nullptr)
{
}

MPGauge::~MPGauge() 
{
}

void MPGauge::Start()
{
	mpUIRenderer = CreateComponent<GameEngineUIRenderer>();
	mpUIRenderer->SetTexture("MPGauge.png");
	mpUIRenderer->GetTransform().SetLocalScale(float4{ GameEngineWindow::GetScale().x * 0.135f, 18.f, 1.f, 1.f });
	mpUIRenderer->SetPivot(PIVOTMODE::LEFTTOP);
}

void MPGauge::Update(float _DeltaTime)
{
}
