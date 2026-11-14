// SPDX-License-Identifier: MPL-2.0
// Adapted from ZenMusic by Zenarchist (https://github.com/ZenarchistCode/ZenMusic).
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

modded class ActionZenToggleMusic
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		#ifdef ZenModPack
		if (!ZenModEnabled("ZenMusic"))
			return false;
		#endif

		HumanCommandVehicle vehCommand = player.GetCommand_Vehicle();

		if (vehCommand)
		{
			Transport trans = vehCommand.GetTransport();
			if (trans)
			{
				CarScript car;
				if (Class.CastTo(car, trans))
				{
					if (!DeaglesZenMusicVehicleCompat.HasCompatibleCassetteSlot(car))
						return false;

                    if (car.NeedElectricitySourceDevice())
                    {
                        EntityAI battery = car.GetElectricitySourceDevice();
                        if (!battery || !battery.GetCompEM() || battery.GetCompEM().GetEnergy() <= 0 || battery.IsRuined())
                            return false;
                    }

					return true;
				}

				BoatScript boat;
				if (Class.CastTo(boat, trans))
					return DeaglesZenMusicVehicleCompat.HasCompatibleCassetteSlot(boat);
			}
		}

		return false;
	}

	override void OnExecuteServer(ActionData action_data)
	{
		HumanCommandVehicle vehCommand = action_data.m_Player.GetCommand_Vehicle();
		if (!vehCommand)
			return;

		Transport trans = vehCommand.GetTransport();
		if (!trans)
			return;

		CarScript car;
		if (Class.CastTo(car, trans))
			{
            car.ToggleZenMusic();
        }

		BoatScript boat;
		if (Class.CastTo(boat, trans))
			boat.ToggleZenMusic();
	}
}
