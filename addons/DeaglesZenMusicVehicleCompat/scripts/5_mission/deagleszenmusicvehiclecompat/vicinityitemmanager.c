// SPDX-License-Identifier: MPL-2.0
// Adapted from ZenMusic by Zenarchist (https://github.com/ZenarchistCode/ZenMusic).
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

modded class VicinityItemManager
{
	override bool ExcludeFromContainer_Phase3(Object object_in_cone)
	{
		#ifdef ZenModPack
		if (!ZenModEnabled("ZenMusic"))
			return super.ExcludeFromContainer_Phase3(object_in_cone);
		#endif

		#ifndef ZenModPack
		if (ZenMusic_PlayerInVehicle() && object_in_cone != NULL && !object_in_cone.IsKindOf("CarScript") && !object_in_cone.IsKindOf("BoatScript"))
			return true;
		#endif

		return super.ExcludeFromContainer_Phase3(object_in_cone);
	}

	bool ZenMusic_PlayerInVehicle()
	{
		PlayerBase player = PlayerBase.Cast(g_Game.GetPlayer());
		return player && player.IsInVehicle();
	}
}
