//Credit to BlueNightHawk https://github.com/BlueNightHawk/newlight-base-sdk/
#include <fmod/fmod_errors.h>
#include "hud.h"
#include "cl_util.h"
#include "clglobal.h"

#include "soundengine.h"

// Starts FMOD
bool CSoundEngine::InitFMOD(void)
{
	m_CurTrack = nullptr;
	FMOD_REVERB_PROPERTIES fmod_reverb_properties[] = {
		FMOD_PRESET_OFF,				//  0
		FMOD_PRESET_GENERIC,			//  1
		FMOD_PRESET_PADDEDCELL,			//  2
		FMOD_PRESET_ROOM,				//  3
		FMOD_PRESET_BATHROOM,			//  4
		FMOD_PRESET_LIVINGROOM,			//  5
		FMOD_PRESET_STONEROOM,			//  6
		FMOD_PRESET_AUDITORIUM,			//  7
		FMOD_PRESET_CONCERTHALL,		//  8
		FMOD_PRESET_CAVE,				//  9
		FMOD_PRESET_ARENA,				// 10
		FMOD_PRESET_HANGAR,				// 11
		FMOD_PRESET_CARPETTEDHALLWAY,	// 12
		FMOD_PRESET_HALLWAY,			// 13
		FMOD_PRESET_STONECORRIDOR,		// 14
		FMOD_PRESET_ALLEY,				// 15
		FMOD_PRESET_FOREST,				// 16
		FMOD_PRESET_CITY,				// 17
		FMOD_PRESET_MOUNTAINS,			// 18
		FMOD_PRESET_QUARRY,				// 19
		FMOD_PRESET_PLAIN,				// 20
		FMOD_PRESET_PARKINGLOT,			// 21
		FMOD_PRESET_SEWERPIPE,			// 22
		FMOD_PRESET_UNDERWATER			// 23
	};

	FMOD_RESULT	result = FMOD::System_Create(&m_pSystem); // Create the main system object.
	if (result != FMOD_OK)
	{
		gEngfuncs.Con_Printf("FMOD ERROR: System creation failed!\n");
		return false;
	}
	else
		gEngfuncs.Con_Printf("FMOD system successfully created.\n");

	result = m_pSystem->init(m_NumChannels, FMOD_INIT_NORMAL, 0);   // Initialize FMOD system.
	if (result != FMOD_OK)
	{
		gEngfuncs.Con_Printf("FMOD ERROR: Failed to initialize properly!\n");
		return false;
	}
	else
		gEngfuncs.Con_Printf("FMOD initialized successfully.\n");

	result = m_pSystem->createChannelGroup("MP3", &m_pMP3Group);
	if (result != FMOD_OK)
	{
		gEngfuncs.Con_Printf("FMOD ERROR: Failed to MP3 channel group\n");
		return false;
	}
	else
		gEngfuncs.Con_Printf("FMOD initialized MP3 channel group.\n");

	result = m_pSystem->createChannelGroup("SFX", &m_pSFXGroup);
	if (result != FMOD_OK)
	{
		gEngfuncs.Con_Printf("FMOD ERROR: Failed to SFX channel group\n");
		return false;
	}
	else
		gEngfuncs.Con_Printf("FMOD initialized SFX channel group.\n");

	m_pSystem->set3DSettings(1.0f, 40, 1.0f);

	return true;
}

// Stops FMOD
bool CSoundEngine::ExitFMOD(void)
{
	FMOD_RESULT	result = m_pSystem->release();

	if (result != FMOD_OK)
	{
		gEngfuncs.Con_Printf("FMOD ERROR: System did not terminate properly!\n");
		return false;
	}
	else
		gEngfuncs.Con_Printf("FMOD system terminated successfully.\n");

	return true;
}

// Update FMOD System
bool CSoundEngine::Update(void) 
{
	if (m_pSystem) {

		FMOD_RESULT result = m_pSystem->update();

		if (result != FMOD_OK) {
			gEngfuncs.Con_Printf("FMOD failed to update!.\n");
			return false;
		}

	}
	else {
		gEngfuncs.Con_Printf("FMOD System not found by update!.\n");
		return false;
	}

	return true;
}

void CSoundEngine::Think(struct ref_params_s *pparams)
{
	if (pparams->paused)
	{
		m_pMP3Group->setPaused(true);
		m_pSFXGroup->setPaused(true);
	} else {
		m_pMP3Group->setPaused(false);
		m_pSFXGroup->setPaused(false);
	}
}

bool CSoundEngine::UpdateListenerPosition(FMOD_VECTOR *pos, FMOD_VECTOR *vel, FMOD_VECTOR *forward, FMOD_VECTOR *up)
{
	FMOD_RESULT	result = m_pSystem->set3DListenerAttributes(0, pos, vel, forward, up);
	if (result != FMOD_OK)
	{
		gEngfuncs.Con_Printf("FMOD ERROR: Failed to update listener position\n");
		return false;
	}
	
	return true;
}

void CSoundEngine::ReleaseSounds(void)
{
	for (auto &it : m_CachedSounds)
	{
		it.second->release();
	}

	m_CachedSounds->clear();
}

void CSoundEngine::ReleaseChannels(void)
{
	for (auto &it : m_Channels)
	{
		it.second->stop();
	}

	m_Channels->clear();
}

void CSoundEngine::CacheSound(const char* path, const bool is_track, const bool play_everywhere)
{
	//TODO
}

FMOD::Reverb3D* CSoundEngine::CreateReverbSphere(const FMOD_REVERB_PROPERTIES* properties, const FMOD_VECTOR* pos, const float min_distance, const float max_distance)
{
	FMOD::Reverb3D* reverbSphere = nullptr;

	FMOD_RESULT	result = m_pSystem->createReverb3D(&reverbSphere);
	if (result != FMOD_OK)
	{
		gEngfuncs.Con_Printf("FMOD ERROR: Failed to create reverb sphere\n");
		return nullptr
	}

	reverbSphere->setProperties(properties);
	reverbSphere->set3DAttributes(pos, min_distance, max_distance);

	m_ReverbSpheres.push_back(reverbSphere);
	return reverbSphere;
}

FMOD::Channel* CSoundEngine::CreateChannel(FMOD::Sound* sound, const char* name, const Fmod_Group &group, const bool loop, const float volume)
{
	FMOD::Channel* channel = nullptr;

	FMOD_RESULT	result = m_pSystem->createReverb3D(&reverbSphere);
	if (result != FMOD_OK)
	{
		gEngfuncs.Con_Printf("FMOD ERROR: Failed to create channel\n");
		return nullptr
	}

	//TODO
}