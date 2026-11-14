#ifdef radio_fungi
modded class Fungi_Radio_Base
{
 override void SetMediaType(EntityAI item)
 {
  super.SetMediaType(item);
  Zen_Cassette_Base cassette = Zen_Cassette_Base.Cast(item);
  if (!cassette)
   return;
  string zenSoundSet = Zen_Cassette_Base.GetZenMusicSoundSet(cassette.GetType());
  if (!GetGame().ConfigIsExisting("CfgSoundSets " + zenSoundSet))
   return;
  m_IsMediaTypePlaylist = false;
  SoundSets.Clear();
  SoundSet = zenSoundSet;
  m_CurrentTrackIndex = 0;
 }
}
modded class fungi_base_radio_shelf_V2
{
 override void SetMediaType(EntityAI item)
 {
  super.SetMediaType(item);
  Zen_Cassette_Base cassette = Zen_Cassette_Base.Cast(item);
  if (!cassette)
   return;
  string zenSoundSet = Zen_Cassette_Base.GetZenMusicSoundSet(cassette.GetType());
  if (!GetGame().ConfigIsExisting("CfgSoundSets " + zenSoundSet))
   return;
  m_IsMediaTypePlaylist = false;
  SoundSets.Clear();
  SoundSet = zenSoundSet;
  m_CurrentTrackIndex = 0;
 }
}
#endif
