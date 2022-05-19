// <hide/>

// ContentsCore.cpp

#include "ContentsCore.h"
#include "IntroLevel.h"
#include "LoginLevel.h"
#include "CharactersLevel.h"
#include "HillOfTheMapleTreeLevel.h"
#include "SnailsLandLevel.h"

#pragma comment(lib, "GameEngineBase.lib")

ContentsCore::ContentsCore() 
    : GameEngineCore()
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
    CreateLevel<IntroLevel>("Intro");
    CreateLevel<LoginLevel>("Login");
    CreateLevel<CharactersLevel>("Characters");
    CreateLevel<HillOfTheMapleTreeLevel>("HillOfTheMapleTree");
    CreateLevel<SnailsLandLevel>("SnailsLand");

    ChangeLevel("Intro");
}

void ContentsCore::Update(float _DeltaTime)
{
    // ������ ����Ǿ���.
    // ������ ��� �޼���â�� �������Ѵ�.
}

void ContentsCore::End() 
{
    int a = 0;
}