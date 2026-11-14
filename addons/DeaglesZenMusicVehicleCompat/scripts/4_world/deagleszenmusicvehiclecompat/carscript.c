modded class CarScript
{
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();

		DeaglesZenMusicVehicleCompat.UnlockCassetteSlots(this);
	}

	override Zen_Cassette_Base GetZenMusicCassette()
	{
		return DeaglesZenMusicVehicleCompat.GetCassette(this);
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		if (slot_name == "Cassette")
		{
			if (g_Game.IsDedicatedServer())
			{
				StopZenMusicSongServer(false);
			}
			else
			{
				m_IsPlayingZenMusic = false;
			}
		}
	}

	override bool CanDisplayAttachmentSlot(int slot_id)
	{
		if (!super.CanDisplayAttachmentSlot(slot_id))
			return false;

		return !DeaglesZenMusicVehicleCompat.ShouldHideAttachmentSlot(this, slot_id);
	}

}
