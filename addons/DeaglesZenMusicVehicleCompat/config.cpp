class CfgPatches
{
 class DeaglesZenMusicVehicleCompat
 {
  units[] = {}; weapons[] = {}; requiredVersion = 0.1;
  requiredAddons[] = {"DZ_Data", "DZ_Scripts", "ZenMusicBase"};
 };
};
class CfgMods
{
	class DeaglesZenMusicVehicleCompat
	{
		type = "mod";
		dependencies[] =
		{
			"World",
			"Mission"
		};
		class defs
		{
			class worldScriptModule
			{
				files[] =
				{
					"DeaglesZenMusicVehicleCompat/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				files[] =
				{
					"DeaglesZenMusicVehicleCompat/scripts/5_Mission"
				};
			};
		};
	};
};

class CfgVehicles
{
 class Inventory_Base;
 class Zen_Cassette_Base: Inventory_Base { inventorySlot[] += {"Cassette"}; };
};
