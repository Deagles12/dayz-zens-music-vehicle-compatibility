class CfgPatches
{
 class DeaglesZenMusicVehicleCompat_Legacy
 {
  units[] = {}; weapons[] = {}; requiredVersion = 0.1;
  requiredAddons[] = {"DeaglesZenMusicVehicleCompat", "Apoc_humvee", "Apoc_Pickup", "Apoc_Suv1", "UAZ_3163", "UAZ_3962", "Van_Airboat", "Van_Catamaran", "Van_FishingTrawler", "Van_HouseBoat", "Van_Jetski", "Van_PatrolBoat", "Van_RHIB", "Van_Sailboat", "Van_WoodenBoat", "Van_Yacht"};
 };
};
class CfgVehicles
{

	class CarScript;
	class UAZ_3163: CarScript
	{
		class GUIInventoryAttachmentsProps
		{
			class Body
			{
				attachmentSlots[] =
				{
					"Reflector_1_1",
					"Reflector_2_1",
					"UAZ_3163_doors_hood",
					"UAZ_3163_doors_trunk",
					"UAZ_3163_doors_driver",
					"UAZ_3163_doors_codriver",
					"UAZ_3163_doors_cargo1",
					"UAZ_3163_doors_cargo2",
					"UAZ_3163_migalki",
					"Cassette"
				};
			};
		};
	};

	class UAZ_3163_black: UAZ_3163
	{
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class Body: Body {};
		};
	};
	class UAZ_3163_Red: UAZ_3163
	{
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class Body: Body {};
		};
	};
	class UAZ_3163_blue: UAZ_3163
	{
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class Body: Body {};
		};
	};
	class UAZ_3163_green: UAZ_3163
	{
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class Body: Body {};
		};
	};
	class UAZ_3163_white: UAZ_3163
	{
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class Body: Body {};
		};
	};
	class UAZ_3163_gamekeeper: UAZ_3163
	{
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class Body: Body {};
		};
	};
	class UAZ_3163_Police: UAZ_3163
	{
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class Body: Body {};
		};
	};
	class UAZ_3163_Ambulance: UAZ_3163
	{
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class Body: Body {};
		};
	};
	class UAZ_3163_MCHS: UAZ_3163
	{
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class Body: Body {};
		};
	};
	class UAZ_3163_VP: UAZ_3163
	{
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class Body: Body {};
		};
	};
	class UAZ_3163_emergency_service: UAZ_3163
	{
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class Body: Body {};
		};
	};

	class UAZ_3962: CarScript
	{
		class GUIInventoryAttachmentsProps
		{
			class Body
			{
				attachmentSlots[] =
				{
					"Reflector_1_1",
					"Reflector_2_1",
					"WalkieTalkie",
					"UAZ_3962_doors_trunk",
					"UAZ_3962_doors_driver",
					"UAZ_3962_doors_codriver",
					"UAZ_3962_doors_cargo1",
					"UAZ_3962_doors_cargo2",
					"Cassette"
				};
			};
		};
	};

	class UAZ_3962_green: UAZ_3962
	{
		class GUIInventoryAttachmentsProps
		{
			class Body
			{
				attachmentSlots[] =
				{
					"Reflector_1_1",
					"Reflector_2_1",
					"UAZ_3962_doors_trunk",
					"UAZ_3962_doors_hood",
					"UAZ_3962_doors_driver",
					"UAZ_3962_doors_codriver",
					"UAZ_3962_doors_cargo1",
					"UAZ_3962_doors_cargo2",
					"Cassette"
				};
			};
		};
	};
	class UAZ_3962_MCHS: UAZ_3962
	{
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class Body: Body {};
		};
	};
	class UAZ_3962_VAI: UAZ_3962
	{
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class Body: Body {};
		};
	};
	class UAZ_3962_milicia: UAZ_3962
	{
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class Body: Body {};
		};
	};
};

class CfgSlots
{
	class Slot_Cassette
	{
		name = "Cassette";
		displayName = "$STR_CfgVehicles_ZenCassette0";
		selection = "Cassette";
		ghostIcon = "set:zen_music image:cassette_icon";
	};
};
