#include "PreCompile.h"
#include "Monster.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	{
		GameEngineRenderer* RendererTest = CreateComponent<GameEngineRenderer>();
		//RendererTest->GetTransform().SetLocalScale({ 50, 50, 50 });
	}
}
