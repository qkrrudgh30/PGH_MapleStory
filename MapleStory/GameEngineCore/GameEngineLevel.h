#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
#include <list>
#include <map>

enum class CAMERAORDER
{
	MAINCAMERA,
	USER0,
	USER1,
	USER2,
	USER3,
	USER4,
	USER5,
	USER6,
	USER7,
	UICAMERA,
};

// 설명 : 화면(타이틀 화면, 플레이 화면, 인벤토리 화면)
class GameEngineCore;
class GameEngineActor;
class GameEngineCamera;
class GameEngineRenderer;
class GameEngineTransform;
class GameEngineCameraActor;
class GameEngineLevel :
	public GameEngineNameObject ,
	public GameEngineUpdateObject
{
	friend GameEngineCore;
	friend GameEngineActor;
	friend GameEngineCamera;
	friend GameEngineRenderer;
	// 레벨이 현재까지 얼마나 켜져있었는지 시간을 잴수 있게 한다.

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	GameEngineCamera* GetMainCamera() 
	{
		return Cameras[static_cast<int>(CAMERAORDER::MAINCAMERA)];
	}

	GameEngineCamera* GetUICamera()
	{
		return Cameras[static_cast<int>(CAMERAORDER::UICAMERA)];
	}

	GameEngineCameraActor* GetMainCameraActor();

	GameEngineTransform& GetMainCameraActorTransform();

	GameEngineCameraActor* GetUICameraActor();

	GameEngineTransform& GetUICameraActorTransform();

	//template<typename ReturnType, typename ActorType, typename GroupIndexType>
	//ReturnType* CreateActor(GroupIndexType _ObjectGroupIndex)
	//{
	//	return CreateActor<ActorType>(static_cast<int>(_ObjectGroupIndex));
	//}

	template<typename ActorType, typename GroupIndexType>
	ActorType* CreateActor(GroupIndexType _ObjectGroupIndex)
	{
		return CreateActor<ActorType>(static_cast<int>(_ObjectGroupIndex));
	}

	template<typename ActorType>
	ActorType* CreateActor(const std::string _Name, int _ObjectGroupIndex = 0)
	{
		CreateActor(_ObjectGroupIndex);
	}

	template<typename ActorType>
	ActorType* CreateActor(int _ObjectGroupIndex = 0)
	{
		GameEngineActor* NewActor = new ActorType();
		NewActor->SetLevel(this);
		NewActor->SetOrder(_ObjectGroupIndex);
		NewActor->Start();

		// AllActors[_ObjectGroupIndex]게 사용하면
		// 없으면 만들어버리고 있으면
		// 찾아서 리턴해준다.
		std::list<GameEngineActor*>& Group = AllActors[_ObjectGroupIndex];

		Group.push_back(NewActor);

		return dynamic_cast<ActorType*>(NewActor);
	}


	template<typename GroupIndexType>
	std::list<GameEngineActor*> GetGroup(GroupIndexType _ObjectGroupIndex)
	{
		return AllActors[static_cast<int>(_ObjectGroupIndex)];
	}

	std::list<GameEngineActor*> GetGroup(int _ObjectGroupIndex)
	{
		return AllActors[_ObjectGroupIndex];
	}

	template<typename ObjectType, typename GroupIndexType>
	std::list<ObjectType*> GetConvertToGroup(GroupIndexType _ObjectGroupIndex)
	{
		return GetConvertToGroup<ObjectType>(static_cast<int>(_ObjectGroupIndex));
	}


	template<typename ObjectType>
	std::list<ObjectType*> GetConvertToGroup(int _ObjectGroupIndex)
	{
		std::list<ObjectType*> Result;
		for (GameEngineActor* Object : AllActors[_ObjectGroupIndex])
		{
			Result.push_back(dynamic_cast<ObjectType*>(Object));
		}

		return Result;
	}

	void PushRendererToMainCamera(GameEngineRenderer* _Renderer)
	{
		PushRenderer(_Renderer, static_cast<int>(CAMERAORDER::MAINCAMERA));
	}

protected:
	



private:
	// 0번 그룹 플레이어
	// 1번 그룹 몬스터
	// 2번 그룹
	std::map<int, std::list<GameEngineActor*>> AllActors;
	std::list<GameEngineUpdateObject*> DeleteObject;

	void ActorUpdate(float _DelataTime);

	void LevelUpdate(float DeltaTime);

	void RemoveActor(GameEngineActor* _Actor);

	void OverChildMove(GameEngineLevel* _NextLevel);

private:
	// 0번 백그라운드
	// 1번 플레이어
	// 2번 UI
	std::vector<GameEngineCamera*> Cameras;

	void PushCamera(GameEngineCamera* _Camera, CAMERAORDER _Order) 
	{
		PushCamera(_Camera, static_cast<int>(_Order));
	}

	

	void PushRendererToUICamera(GameEngineRenderer* _Renderer)
	{
		PushRenderer(_Renderer, static_cast<int>(CAMERAORDER::UICAMERA));
	}

	void PushRenderer(GameEngineRenderer* _Renderer, CAMERAORDER _Order) 
	{
		PushRenderer(_Renderer, static_cast<int>(_Order));
	}

	void PushCamera(GameEngineCamera* _Camera, int _CameraOrder);

	void PushRenderer(GameEngineRenderer* _Renderer, int _CameraOrder);

	void Render(float _DelataTime);

	void Release(float _DelataTime);
};

