// SPDX-License-Identifier: MPL-2.0
// Adapted from ZenMusic by Zenarchist (https://github.com/ZenarchistCode/ZenMusic).
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

modded class BoatScript
{
	const static float ZEN_SONG_UPDATE_TIMER_SECS = 5.0;

	protected ref Timer m_ZenMusicTimer;
	protected float m_ZenMusicVolumeClient = 0.5;
	protected float m_ZenMusicVolume = 0.5;
	protected ref EffectSound m_ZenSong;
	protected bool m_IsPlayingZenMusic = false;
	int m_ZenMusicPlaySecs = -1;

	void BoatScript()
	{
		RegisterNetSyncVariableFloat("m_ZenMusicVolume");
		RegisterNetSyncVariableInt("m_ZenMusicPlaySecs");
	}

	void ~BoatScript()
	{
		if (!g_Game)
			return;

		if (g_Game.IsDedicatedServer())
			StopZenMusicSongServer();
		else
			StopZenMusicSongClient();

		delete m_ZenSong;
	}

	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();

		DeaglesZenMusicVehicleCompat.UnlockCassetteSlots(this);
	}

	Zen_Cassette_Base GetZenMusicCassette()
	{
		return DeaglesZenMusicVehicleCompat.GetCassette(this);
	}

	int GetZenMusicSongDuration()
	{
		if (GetZenMusicCassette() && !GetZenMusicCassette().IsRuined())
			return Zen_Cassette_Base.GetZenMusicSongDuration(GetZenMusicCassette().GetType());

		return -1;
	}

	void ToggleZenMusic()
	{
		if (m_ZenMusicPlaySecs == -1)
			PlayZenMusicSongServer();
		else
			StopZenMusicSongServer();
	}

	bool HasValidZenMusicCassette()
	{
		if (!GetZenMusicCassette())
			return false;

		return !GetZenMusicCassette().IsRuined() && Zen_Cassette_Base.GetZenMusicSoundSet(GetZenMusicCassette().GetType()) != "" && Zen_Cassette_Base.GetZenMusicSongDuration(GetZenMusicCassette().GetType()) > 0;
	}

	void PlayZenMusicSongServer(int skipSecs = 0)
	{
		if (!HasValidZenMusicCassette())
			return;

		m_ZenMusicPlaySecs = skipSecs;

		if (!m_ZenMusicTimer || !m_ZenMusicTimer.IsRunning())
		{
			m_ZenMusicTimer = new Timer();
			m_ZenMusicTimer.Run(ZEN_SONG_UPDATE_TIMER_SECS, this, "UpdateZenMusicSongDuration", null, true);
		}

		SetSynchDirty();
	}

	void StopZenMusicSongServer(bool turnOffRadio = false)
	{
		if (m_ZenMusicTimer)
			m_ZenMusicTimer.Stop();

		m_ZenMusicPlaySecs = -1;
		SetSynchDirty();
	}

	void UpdateZenMusicSongDuration()
	{
		if (m_ZenMusicPlaySecs < 0 || m_ZenMusicPlaySecs > GetZenMusicSongDuration() + 10)
		{
			StopZenMusicSongServer();
			return;
		}

		m_ZenMusicPlaySecs += ZEN_SONG_UPDATE_TIMER_SECS;
		SetSynchDirty();
	}

	void TurnZenMusicVolumeUp()
	{
		m_ZenMusicVolume = m_ZenMusicVolume + 0.25;
		if (m_ZenMusicVolume > 4.0)
			m_ZenMusicVolume = 4.0;

		SetSynchDirty();
	}

	void TurnZenMusicVolumeDown()
	{
		m_ZenMusicVolume = m_ZenMusicVolume - 0.25;
		if (m_ZenMusicVolume < 0)
			m_ZenMusicVolume = 0;

		SetSynchDirty();
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		if (m_ZenMusicPlaySecs >= 0)
		{
			if (m_ZenMusicPlaySecs < GetZenMusicSongDuration() && (!m_ZenSong || !m_ZenSong.IsSoundPlaying()))
				PlayZenMusicSongClient();
		}
		else
		{
			StopZenMusicSongClient();
		}

		if (m_ZenMusicVolumeClient != m_ZenMusicVolume)
		{
			m_ZenMusicVolumeClient = m_ZenMusicVolume;
			if (m_ZenSong && m_ZenSong.Zen_GetAbstractWave().IsHeaderLoaded())
			{
				m_ZenSong.Zen_SetMaxVolume(m_ZenMusicVolumeClient);
				m_ZenSong.SetSoundVolume(m_ZenMusicVolumeClient);
			}
		}
	}

	void PlayZenMusicSongClient()
	{
		if (!HasValidZenMusicCassette() || m_IsPlayingZenMusic)
			return;

		m_ZenSong = SEffectManager.CreateSound(Zen_Cassette_Base.GetZenMusicSoundSet(GetZenMusicCassette().GetType()), GetPosition(), 0, 0, false);

		if (!ZenOptions.GetBool("ZEN.ZenMusicSetting", false) && Zen_Cassette_Base.IsZenMusicCopyrighted(GetZenMusicCassette().GetType()))
		{
			StopZenMusicSongClient();
			return;
		}

		int playSecs = Zen_Cassette_Base.GetZenMusicSongDuration(GetZenMusicCassette().GetType());
		if (!m_ZenSong || !playSecs || playSecs <= 0)
			return;

		m_ZenSong.SetParent(this);
		m_ZenSong.SetLocalPosition(vector.Zero);
		m_ZenSong.SetSoundAutodestroy(true);
		m_ZenSong.Zen_SetMaxVolume(m_ZenMusicVolumeClient);
		m_ZenSong.SoundPlay();
		m_IsPlayingZenMusic = true;

		if (m_ZenMusicPlaySecs > 0 && m_ZenSong.Zen_GetAbstractWave())
		{
			float skip = (m_ZenMusicPlaySecs / playSecs);
			m_ZenSong.Zen_GetAbstractWave().SetStartOffset(skip);
		}
	}

	void StopZenMusicSongClient()
	{
		if (m_ZenSong)
		{
			m_ZenSong.SoundStop();
			m_IsPlayingZenMusic = false;
		}
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		if (slot_name == "ZenCassette" || slot_name == "Cassette")
		{
			if (g_Game.IsDedicatedServer())
				StopZenMusicSongServer();
			else
				m_IsPlayingZenMusic = false;
		}
	}

	override bool IgnoreOutOfReachCondition()
	{
		#ifdef ZenModPack
		if (!ZenModEnabled("ZenMusic"))
			return super.IgnoreOutOfReachCondition();
		#endif

		if (GetZenMusicConfig().AllowCarInventory)
			return DeaglesZenMusicVehicleCompat.PlayerInVehicle();

		return super.IgnoreOutOfReachCondition();
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionZenToggleMusic);
		AddAction(ActionZenMusicVolUp);
		AddAction(ActionZenMusicVolDn);
	}
}
