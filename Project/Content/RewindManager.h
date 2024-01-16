#pragma once

//1분 3600
#define REWIND_TIME 0.85f
#define MAX_REWIND_SECOND 90
#define MAX_REWIND_FRAME MAX_REWIND_SECOND * 60 + 60
#define REWIND_FRAME_TIME 0.0166666f //1초에 60장

class GameObject;
class Scene;

struct RewindObjectData
{
	GameObject* Obj;

	bool bVisible;

	//pos, rot, scale
	Matrix WorldMatrix;

	//animkey, idx
	std::wstring AnimKey;
	UINT FrameIdx;
};

enum class eRewindState
{
	None,
	Record,
	RecordSave,
	CCTV,
	PlayBack,
	Pause,
	Rewind,
	BlackOut,
};

enum class eRewindEvent
{
	None,
	RewindStart,
	RewindTVThumb,
	RewindEnd,
};


class RewindManager
{
public:
	RewindManager();
	virtual ~RewindManager();
	RewindManager(const RewindManager&) = delete;
	RewindManager& operator=(const RewindManager&) = delete;

	void Initialize(Scene* Scene);
	void LateUpdate();
	void RegisterRewindObject(GameObject* const obj) { Assert(obj, ASSERT_MSG_NULL), mRewindObjects.push_back(obj); };
	
	eRewindState GetRewindState() const { return mState; }
	void SetRewindState(const eRewindState state) { mState = state; }

	void Rewind();
	void CCTVPlay();
	void GameClear();
	int GetCCTVSpeed() const;

private:
	void record();
	void recordSave();
	void play();
	void playBack();
	void pause();
	void rewind();
	void blackOut();
	void DrawFrame(int frameIdx);

	

	eRewindState mState;
	float mFrameTime;
	float mCurTime;
	float mTimeScale;

	int mMAXFrameIdx;
	int mCurFrameIdx;
	int mCCTVSpeedIdx;
	//1분 3600


	//rewind
	float mRewindFrame;
	float mTVThumTime;
	eRewindEvent mRewindEvent;

	GameObject* mTimerUI;
	std::vector<GameObject*> mRewindObjects;
	std::vector<RewindObjectData> mRewindFrameDatasArray[MAX_REWIND_FRAME];
};

