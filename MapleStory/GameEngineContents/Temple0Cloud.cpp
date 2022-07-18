#include "PreCompile.h"
#include "Temple0Cloud.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Temple0Cloud::Temple0Cloud()
	: mpRenderer(nullptr)
	, mfWidth(0)
	, mfHeight(0)
	, mfPositionX(0)
	, mfPositionY(0)
{
}

Temple0Cloud::~Temple0Cloud() 
{
}

void Temple0Cloud::Start()
{
	mfWidth = 2327.f;
	mfHeight = 935.f;
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->SetTexture("Temple0Cloud.png", 0);
	
	mpRenderer->GetTransform().SetLocalScale({ mfWidth, mfHeight, 1.f });
	mpRenderer->GetTransform().SetLocalPosition({ 0.f, 50.f, 1.f });
}

void Temple0Cloud::Update(float _DeltaTime)
{
}

void Temple0Cloud::End()
{
}
