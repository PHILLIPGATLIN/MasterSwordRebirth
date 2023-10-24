//Credit to BlueNightHawk https://github.com/BlueNightHawk/newlight-base-sdk/
#pragma once

#include <string>
#include <unordered_map>
#include <fmod/fmod.hpp>

class CSoundEngine
{
public:
	CSoundEngine() = default;
	~CSoundEngine() = default;

	bool InitFMOD();
	bool ExitFMOD();
	bool Update();
	void Think(struct ref_params_s *pparams);
	bool UpdateListenerPosition(FMOD_VECTOR* pos, FMOD_VECTOR* vel, FMOD_VECTOR* forward, FMOD_VECTOR* up);
	void ReleaseSounds();
	void ReleaseChannels();

	//FMOD::Sound* CacheSound(const char* path, const bool is_track);
	FMOD::Sound* CacheSound(const char* path, const bool is_track, const bool play_everywhere);

	FMOD::Reverb3D* CreateReverbSphere(const FMOD_REVERB_PROPERTIES* properties, const FMOD_VECTOR* pos, const float min_distance, const float max_distance);

	FMOD::Channel* CreateChannel(FMOD::Sound *sound, const char* name, const FMOD::ChannelGroup& group, const bool loop, const float volume)

	FMOD::System *GetSystem() { return m_pSystem; }

	//No longer needed just pass NULL channel since we are not doing any submixing
	//FMOD::ChannelGroup *GetChannelGroup(eChannelGroupType channelgroupType) { return m_pChannelGroups[channelgroupType]; }

private:
	FMOD::System *m_pSystem;
	FMOD::ChannelGroup* m_pMP3Group;
	FMOD::ChannelGroup* m_pSFXGroup;

	std::unordered_map<std::string, FMOD::Sound*> m_CachedSounds;
	std::unordered_map<std::string, FMOD::Channel*> m_Channels;
	std::unordered_map<std::string, FMOD::Sound*> m_Tracks;

	FMOD::Channel* m_CurTrack;

	FMOD_REVERB_PROPERTIES fmod_reverb_properties[];

	std::vector<FMOD::Reverb3D*> m_ReverbSpheres;

	const int m_NumChannels = 512;
	//No longer needed just pass NULL channel since we are not doing any submixing
	//FMOD::ChannelGroup* m_pChannelGroups[NUM_CHANNELGROUPS];
};

extern CSoundEngine gSoundEngine;