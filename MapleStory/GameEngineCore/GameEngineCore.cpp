// <hide/>

// GameEngineCore.cpp

#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineLevel.h"

#pragma comment(lib, "GameEngineBase.lib")

GameEngineLevel* GameEngineCore::CurrentLevel = nullptr;
GameEngineLevel* GameEngineCore::NextLevel = nullptr;

std::map<std::string, class GameEngineLevel*> GameEngineCore::AllLevels;

GameEngineCore::GameEngineCore() 
{
}

GameEngineCore::~GameEngineCore() 
{
}

GameEngineLevel* GameEngineCore::FindLevel(const std::string& _Name)
{
    std::string UpperName = GameEngineString::ToUpperReturn(_Name);

    std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevels.find(UpperName);
    if (AllLevels.end() == FindIter)
    {
        return nullptr;
    }
    return FindIter->second;
}

void GameEngineCore::CoreStart(GameEngineCore* _UserCore)
{
    _UserCore->Start();
}

void GameEngineCore::CoreUpdate(GameEngineCore* _UserCore)
{
    if (nullptr != NextLevel)
    {
        if (nullptr != CurrentLevel)
        {
            CurrentLevel->OffEvent();
        }

        CurrentLevel = NextLevel;
        NextLevel = nullptr;

        CurrentLevel->OnEvent();
        CurrentLevel->ReSetAccTime();
        GameEngineTime::GetInst()->Reset();
    }

    if (nullptr == CurrentLevel)
    {
        MsgBoxAssert("������ ���������� ������ ������ ������ ���� �����ϴ�.");
    }

    GameEngineTime::GetInst()->Update();

    float DeltaTime = GameEngineTime::GetDeltaTime();

    _UserCore->Update(DeltaTime);

    CurrentLevel->AddAccTime(DeltaTime);
    CurrentLevel->Update(DeltaTime);
    CurrentLevel->ActorUpdate(DeltaTime);
    CurrentLevel->Render(DeltaTime);
}

void GameEngineCore::CoreEnd(GameEngineCore* _UserCore) 
{
    _UserCore->End();

    for (auto& Level : AllLevels)
    {
        if (nullptr == Level.second)
        {
            continue;
        }
        delete Level.second;
        Level.second = nullptr;
    }

    GameEngineWindow::Destroy();
    GameEngineInput::Destroy();
    GameEngineTime::Destroy();
}

void GameEngineCore::InitializeLevel(GameEngineLevel* _Level, const std::string _Name)
{
    _Level->Start();
    _Level->SetName(_Name);

    AllLevels.insert(std::make_pair(_Name, _Level));
}


bool GameEngineCore::ChangeLevel(const std::string& _Name)
{
    NextLevel = FindLevel(_Name);

    if (nullptr == NextLevel)
    {
        MsgBoxAssert("�������� �ʴ� ������ �ٲٷ��� �߽��ϴ�.");
        return false;
    }
    return true;
}

void GameEngineCore::WindowCreate(const std::string& _Name, GameEngineCore* _UserCore)
{
    GameEngineWindow::GetInst()->CreateGameWindow(nullptr, _Name.c_str());
    GameEngineWindow::GetInst()->SetWindowScaleAndPosition({ 0,0 }, {1280, 720});
    GameEngineWindow::GetInst()->ShowGameWindow();
    GameEngineWindow::GetInst()->MessageLoop(
        std::bind(&GameEngineCore::CoreStart, _UserCore),
        std::bind(&GameEngineCore::CoreUpdate, _UserCore),
        std::bind(&GameEngineCore::CoreEnd, _UserCore)
    );
}