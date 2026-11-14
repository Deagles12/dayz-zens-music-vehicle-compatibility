# Zens Music Vehicle Compatibility

DayZ addon that extends Zen cassette playback to supported modded vehicles and Radio Fungi devices.

[Steam Workshop](https://steamcommunity.com/sharedfiles/filedetails/?id=3745482037)

## Features

- Adds a **Radio** inventory category with a `ZenCassette` slot to ten RaG Vehicle Pack families: ATV, Baja, Derby Car, GAZ69, armored Hummer, Jeep Willys, Landrover 110, MTVR, Schoolbus, and ZIL-130.
- Supports `ZenCassette` and legacy `Cassette` attachments. Vehicle playback uses Zen Music controls and checks the vehicle's actual electricity source on DayZ 1.30.
- Resolves Zen and Charts Music cassette SoundSets on Radio Fungi portable players and the V2 radio shelf. Existing Fungi handling applies to other cassette types.
- Includes a separate legacy addon for the original APOC, RUSForma UAZ, and Van boat integrations.

## Requirements and compatibility

| Requirement | When to load it |
| --- | --- |
| [Community Framework](https://steamcommunity.com/sharedfiles/filedetails/?id=1559212036), [Zens Core Mod](https://steamcommunity.com/sharedfiles/filedetails/?id=3702420204), and [Zens Music](https://steamcommunity.com/sharedfiles/filedetails/?id=3412251200) | Core playback, including the `ZenMusicBase` addon. |
| [RaG Core](https://steamcommunity.com/sharedfiles/filedetails/?id=3556131153) and [RaG Vehicle Pack](https://steamcommunity.com/sharedfiles/filedetails/?id=2880254695) | Required for the RaG addon included in the default Workshop package. |
| [Charts Music (1983–2000)](https://steamcommunity.com/sharedfiles/filedetails/?id=3742287199) | Optional cassette content. Load it to use Charts tapes. |
| [Radio Fungi NO Music](https://steamcommunity.com/sharedfiles/filedetails/?id=3434370604) | Optional players. The adapter activates when the `radio_fungi` script define is present. |

The optional legacy addon requires all of its vehicle patches together: `Apoc_humvee`, `Apoc_Pickup`, `Apoc_Suv1`, `UAZ_3163`, `UAZ_3962`, `Van_Airboat`, `Van_Catamaran`, `Van_FishingTrawler`, `Van_HouseBoat`, `Van_Jetski`, `Van_PatrolBoat`, `Van_RHIB`, `Van_Sailboat`, `Van_WoodenBoat`, and `Van_Yacht`. See [the declared dependencies](addons/DeaglesZenMusicVehicleCompat_Legacy/config.cpp).


The published version was tested on DayZ PC 1.30. Vehicle testing verified cassette slots on all ten RaG base families and audible playback in a RaG Landrover using Charts 1986 Vol. 2. Server validation checked attachment and SoundSet resolution for 225 playable Zen and Charts cassettes on six portable Fungi players and the V2 radio shelf, for 1,575 combinations. Audible playback, full track duration, and persistence on every device remain unverified.

## Installation

1. Subscribe to [Zens Music Vehicle Compatibility on Steam Workshop](https://steamcommunity.com/sharedfiles/filedetails/?id=3745482037) and its required mods.
2. Install the Workshop package in its own folder on the dedicated server. Copy its public `.bikey` to the server's `keys` directory when signature verification is enabled.
3. Add the compatibility mod to the server's `-mod` list after its dependencies. Load matching versions of the mods on each client. When upgrading, remove older compatibility copies from the load list.
4. For the legacy integration, load all of its dependencies and move the legacy PBO and its signature from `Optional/Legacy` into the mod's `Addons` folder. Use the same configuration on the server and each client.


## Usage

In a supported RaG vehicle, put a playable cassette in the **Radio** slot and sit in the vehicle. If the vehicle requires a battery, install a charged, non-ruined battery. With the default Zens Music bindings, press **K** to toggle playback and use **numpad + / −** to adjust volume. On a supported Fungi device, insert the cassette and use the device's normal playback controls.

## Build from source

With DayZ Tools, pack each folder under `addons/` as a separate PBO using its folder name as the PBO prefix. Preserve the script paths declared in the core `config.cpp`. Place the core and RaG PBOs in the packaged mod's `Addons` directory alongside the root `mod.cpp`. Package the legacy PBO separately under `Optional/Legacy`. Sign local builds with your own key if the server verifies signatures.

## Contributing

Use Conventional Commits for changes, for example `fix(vehicles): check the installed battery` or `docs: clarify legacy addon setup`.

## License

Original project files are available under the [MIT License](LICENSE). Files adapted from [Zenarchist's ZenMusic](https://github.com/ZenarchistCode/ZenMusic) carry an MPL-2.0 notice and are available under the [Mozilla Public License 2.0](LICENSES/MPL-2.0.txt). Third-party mods and music are distributed by their respective authors.
