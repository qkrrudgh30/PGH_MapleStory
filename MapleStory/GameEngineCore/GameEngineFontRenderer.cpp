#include "PreCompile.h"
#include "GameEngineFontRenderer.h"

GameEngineRenderTarget* GameEngineFontRenderer::FontTarget = nullptr;

GameEngineFontRenderer::GameEngineFontRenderer() 
	: Font(nullptr)
	, FontSize(20.0f)
	, Color(float4::WHITE)
	, ScreenPostion(float4::ZERO)
{
}

GameEngineFontRenderer::~GameEngineFontRenderer() 
{
}

void GameEngineFontRenderer::SetText(const std::string& _Text, const std::string& _Font)
{
	Text = _Text;
	Font = GameEngineFont::Find(_Font);
}

void GameEngineFontRenderer::Start() 
{
	if (nullptr == FontTarget)
	{
		FontTarget = GameEngineRenderTarget::Create("FontTarget");
		FontTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), float4::ZERO);
	}

	PushRendererToMainCamera();
}

// 랜더링 파이프라인이 필요가 아직은 없어요
void GameEngineFontRenderer::Render(float _DeltaTime) 
{
	// 이거는 랜더타겟을 해야겠네요.
	if (nullptr == Font)
	{
		return;
	}

	// 이녀석이 내부에서 무슨짓을 하는지는 모르지만.
	// 기존 화면에다가 그리면 안되죠?
	// 랜더타겟
	// 글자는 또다른 랜더타겟에 그릴겁니다.
	
	// 이전에 존재했던 랜더타겟을 얻고
	// GameEngineRenderTarget::GetPrevRenderTarget();
	//FontTarget->Setting();

	Font->FontDraw(Text, FontSize, ScreenPostion, Color, static_cast<int>(LR) | static_cast<int>(TB));
	GameEngineRenderingPipeLine::AllShaderReset();
	//GameEngineRenderTarget::SetPrevRenderTarget();
	// FontTarget->R();
}