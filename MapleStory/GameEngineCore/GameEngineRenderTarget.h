// <hide/>

// GameEngineRenderTarget.h

#pragma once
#include "GameEngineTexture.h"
#include <vector>

// 설명 : 랜더링 파이프 라인을 통해 그려지게될 텍스쳐들을 관리하는 클래스.
class GameEngineRenderTarget : public GameEngineRes<GameEngineRenderTarget>
{
public:
    // constrcuter destructer
    GameEngineRenderTarget();
    ~GameEngineRenderTarget();

    // delete Function
    GameEngineRenderTarget(const GameEngineRenderTarget& _Other) = delete;
    GameEngineRenderTarget(GameEngineRenderTarget&& _Other) noexcept = delete;
    GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _Other) = delete;
    GameEngineRenderTarget& operator=(GameEngineRenderTarget&& _Other) noexcept = delete;

    static GameEngineRenderTarget* Create(const std::string& _Name);

    void CreateRenderTargetTexture(ID3D11Texture2D* _Texture, float4 _Color);

    void Clear();

    void Setting();

protected:
    std::vector<GameEngineTexture*>      RenderTargets;
    std::vector<ID3D11RenderTargetView*> RenderTargetViews;
    std::vector<float4>                  ClearColors;

    ID3D11DepthStencilView*              DepthStencilView;

private:

};