class DeaglesZenMusicVehicleCompat
{
	protected static ref map<string, bool> s_MixedCassetteSlotCache = new map<string, bool>;

	static bool HasAttachmentSlot(EntityAI entity, string slotName)
	{
		if (!entity || !entity.GetInventory())
			return false;

		return entity.GetInventory().HasAttachmentSlot(InventorySlots.GetSlotIdFromString(slotName));
	}

	static bool PlayerInVehicle()
	{
		if (!g_Game || !g_Game.IsClient())
			return false;

		PlayerBase player = PlayerBase.Cast(g_Game.GetPlayer());
		return player && player.IsInVehicle();
	}

	static void UnlockCassetteSlots(EntityAI entity)
	{
		if (!entity || !entity.GetInventory())
			return;

		entity.GetInventory().SetSlotLock(InventorySlots.GetSlotIdFromString("ZenCassette"), false);
		entity.GetInventory().SetSlotLock(InventorySlots.GetSlotIdFromString("Cassette"), false);
	}

	static Zen_Cassette_Base GetCassette(EntityAI entity)
	{
		if (!entity)
			return null;

		Zen_Cassette_Base tape = Zen_Cassette_Base.Cast(entity.FindAttachmentBySlotName("ZenCassette"));
		if (tape)
			return tape;

		return Zen_Cassette_Base.Cast(entity.FindAttachmentBySlotName("Cassette"));
	}

	static bool HasCompatibleCassetteSlot(EntityAI entity)
	{
		if (HasAttachmentSlot(entity, "ZenCassette"))
			return true;

		return HasAttachmentSlot(entity, "Cassette");
	}

	static bool IsCassetteSlotName(string slotName)
	{
		return slotName == "ZenCassette" || slotName == "Cassette";
	}

	static bool IsForceCassetteOnlyVehicle(EntityAI entity)
	{
		if (!entity)
			return false;

		string className = entity.GetType();
		return className.IndexOf("UAZ_3163") == 0 || className.IndexOf("UAZ_3962") == 0;
	}

	static bool SlotArrayContains(TStringArray slots, string slotName)
	{
		foreach (string existingSlotName : slots)
		{
			if (existingSlotName == slotName)
				return true;
		}

		return false;
	}

	static bool SlotHasGhostIcon(string slotName)
	{
		if (!g_Game || slotName == "")
			return false;

		string cfgPath = "CfgSlots Slot_" + slotName + " ghostIcon";
		if (!g_Game.ConfigIsExisting(cfgPath))
			return false;

		string ghostIcon;
		g_Game.ConfigGetText(cfgPath, ghostIcon);
		return ghostIcon != "";
	}

	static bool IsLegacyFakeCassetteCompanionSlot(string slotName)
	{
		if (slotName == "WalkieTalkie")
			return true;

		if (slotName.Contains("number_gos"))
			return true;

		// RUSForma UAZ families often place emergency/police light service slots
		// into the same GUI category as the cassette slot.
		if (slotName.Contains("PoliceLight") || slotName.Contains("POLICE_LIGHT") || slotName.Contains("police_light"))
			return true;

		if (slotName.Contains("FlashingLight") || slotName.Contains("FLASHING_LIGHT") || slotName.Contains("flashing_light"))
			return true;

		if (slotName.Contains("Beacon") || slotName.Contains("BEACON") || slotName.Contains("beacon"))
			return true;

		if (slotName.Contains("Siren") || slotName.Contains("SIREN") || slotName.Contains("siren"))
			return true;

		if (slotName.Contains("Lightbar") || slotName.Contains("LIGHTBAR") || slotName.Contains("lightbar"))
			return true;

		return false;
	}

	static void GetVehicleAttachmentsPropsPaths(EntityAI entity, out TStringArray propsPaths)
	{
		propsPaths = new TStringArray;

		if (!entity || !g_Game)
			return;

		string className = entity.GetType();
		while (className != "")
		{
			string propsPath = "CfgVehicles " + className + " GUIInventoryAttachmentsProps";
			if (g_Game.ConfigIsExisting(propsPath))
				propsPaths.Insert(propsPath);

			string baseClassName;
			if (!g_Game.ConfigGetBaseName("CfgVehicles " + className, baseClassName))
				break;

			if (baseClassName == className)
				break;

			className = baseClassName;
		}
	}

	static bool SlotSharesCategoryWithCassette(EntityAI entity, string slotName)
	{
		if (!entity || !g_Game || slotName == "")
			return false;

		string cacheKey = entity.GetType() + "|" + slotName;
		if (s_MixedCassetteSlotCache.Contains(cacheKey))
			return s_MixedCassetteSlotCache.Get(cacheKey);

		TStringArray propsPaths;
		GetVehicleAttachmentsPropsPaths(entity, propsPaths);
		if (!propsPaths || propsPaths.Count() == 0)
		{
			s_MixedCassetteSlotCache.Set(cacheKey, false);
			return false;
		}

		bool found = false;
		foreach (string propsPath : propsPaths)
		{
			int categoryCount = g_Game.ConfigGetChildrenCount(propsPath);
			for (int i = 0; i < categoryCount; i++)
			{
				string categoryName;
				g_Game.ConfigGetChildName(propsPath, i, categoryName);

				string slotsPath = propsPath + " " + categoryName + " attachmentSlots";
				if (!g_Game.ConfigIsExisting(slotsPath))
					continue;

				TStringArray slots = new TStringArray;
				g_Game.ConfigGetTextArray(slotsPath, slots);

				if (!SlotArrayContains(slots, slotName))
					continue;

				if (SlotArrayContains(slots, "Cassette") || SlotArrayContains(slots, "ZenCassette"))
				{
					found = true;
					break;
				}
			}

			if (found)
				break;
		}

		s_MixedCassetteSlotCache.Set(cacheKey, found);
		return found;
	}

	static bool ShouldHideAttachmentSlot(EntityAI entity, int slotId)
	{
		if (!entity || !HasCompatibleCassetteSlot(entity))
			return false;

		string slotName = InventorySlots.GetSlotName(slotId);
		if (slotName == "" || IsCassetteSlotName(slotName))
			return false;

		if (!SlotSharesCategoryWithCassette(entity, slotName))
			return false;

		if (IsForceCassetteOnlyVehicle(entity))
			return true;

		if (IsLegacyFakeCassetteCompanionSlot(slotName))
			return true;

		return !SlotHasGhostIcon(slotName);
	}

	static bool ShouldShowZenMusicCategory(EntityAI entity)
	{
		// Legacy vehicle mods already expose a Cassette slot in their own GUI category.
		// If we also show ZenMusic, the UI renders duplicate or blank cassette slots.
		return HasAttachmentSlot(entity, "ZenCassette") && !HasAttachmentSlot(entity, "Cassette");
	}

	static bool CategoryContainsCassetteSlot(EntityAI entity, string category_name)
	{
		if (!entity || !g_Game)
			return false;

		TStringArray propsPaths;
		GetVehicleAttachmentsPropsPaths(entity, propsPaths);
		if (!propsPaths)
			return false;

		foreach (string propsPath : propsPaths)
		{
			string cfgPath = propsPath + " " + category_name + " attachmentSlots";
			if (!g_Game.ConfigIsExisting(cfgPath))
				continue;

			TStringArray slots = new TStringArray;
			g_Game.ConfigGetTextArray(cfgPath, slots);

			foreach (string slotName : slots)
			{
				if (IsCassetteSlotName(slotName))
					return true;
			}
		}

		return false;
	}

	static bool CategoryIsCassetteOnly(EntityAI entity, string category_name)
	{
		if (!entity || !g_Game)
			return false;

		TStringArray propsPaths;
		GetVehicleAttachmentsPropsPaths(entity, propsPaths);
		if (!propsPaths)
			return false;

		foreach (string propsPath : propsPaths)
		{
			string cfgPath = propsPath + " " + category_name + " attachmentSlots";
			if (!g_Game.ConfigIsExisting(cfgPath))
				continue;

			TStringArray slots = new TStringArray;
			g_Game.ConfigGetTextArray(cfgPath, slots);

			if (slots.Count() == 0)
				continue;

			foreach (string slotName : slots)
			{
				if (!IsCassetteSlotName(slotName))
					return false;
			}

			return true;
		}

		return false;
	}
}
