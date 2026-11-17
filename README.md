# [ReAMXModX](https://github.com/rehlds/reamxmodx) [![Archived](https://img.shields.io/badge/status-Archived-lightgrey.svg?style=flat-square)](https://github.com/rehlds/reamxmodx/) [![Deprecated](https://img.shields.io/badge/status-Deprecated-red.svg?style=flat-square)](https://github.com/rehlds/reamxmodx/) [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg?style=flat-square)](./public/licenses/GPLv3.txt) [![Based on](https://img.shields.io/badge/based%20on-AMX%20Mod%20X%201.8.3--dev%20git5067-orange.svg?style=flat-square)](https://github.com/alliedmodders/amxmodx)

> [!WARNING]
> **This project is obsolete and kept read-only for historical reference only. Do not use it on servers.**
>
> Official [AMX Mod X](https://github.com/alliedmodders/amxmodx) supports [ReHLDS](https://github.com/rehlds/ReHLDS) and [ReGameDLL_CS](https://github.com/rehlds/ReGameDLL_CS) natively since [alliedmodders/amxmodx#417](https://github.com/alliedmodders/amxmodx/pull/417) (March 2017, AMX Mod X 1.9+). Extended ReHLDS/ReGameDLL features for plugins are provided by [ReAPI](https://github.com/rehlds/ReAPI).

> [!CAUTION]
> **Проект устарел и сохранён только как история. Не используйте его на серверах.**
>
> Официальный [AMX Mod X](https://github.com/alliedmodders/amxmodx) поддерживает [ReHLDS](https://github.com/rehlds/ReHLDS) и [ReGameDLL_CS](https://github.com/rehlds/ReGameDLL_CS) сам, начиная с [alliedmodders/amxmodx#417](https://github.com/alliedmodders/amxmodx/pull/417) (март 2017, AMX Mod X 1.9+). Расширенные возможности ReHLDS/ReGameDLL для плагинов даёт [ReAPI](https://github.com/rehlds/ReAPI).

## What was this?
An early (2016) fork of AMX Mod X (1.8.3 development tree, `git5067`) adapted to run on top of ReHLDS and ReGameDLL_CS,
made before upstream AMX Mod X got its own ReHLDS support. Work ended in December 2016; no releases were ever published.

Documentation: [rehlds.dev/docs/reamxmodx](https://rehlds.dev/docs/reamxmodx/)

Main changes compared to upstream at that time:
* ReHLDS API in the core (`amxmodx/sdk/mod_rehlds_api.*`) instead of engine detours (`SV_DropClient`, `Cvar_DirectSet`);
* ReHLDS/ReGameDLL API glue in the `cstrike`, `csx`, `engine`, `fakemeta` and `hamsandwich` modules;
* safety checks in `fakemeta` and `hamsandwich`, compatibility fixes for old plugins;
* Linux stack alignment fixes for natives, a memory leak fix in `unregister_forward`;
* a chat localization bug fix;
* last update: ReHLDS API 3.x, ReGameDLL API 5.x (December 2016).

## Why is it public?
Old documentation and forum threads still link here. The repository is published and archived as is,
without any changes to the code, so those links keep working and the history stays available.

## Use instead
| Need | Project |
|---|---|
| Plugin platform | [AMX Mod X](https://github.com/alliedmodders/amxmodx) 1.9+ (1.10 recommended) |
| ReHLDS / ReGameDLL / Metamod hooks and natives | [ReAPI](https://github.com/rehlds/ReAPI) |
| Engine | [ReHLDS](https://github.com/rehlds/ReHLDS) |
| Counter-Strike game library | [ReGameDLL_CS](https://github.com/rehlds/ReGameDLL_CS) |
| Metamod | [Metamod-r](https://github.com/rehlds/Metamod-R) |

## License
Same as AMX Mod X: GNU GPL v3 with the AMX Mod X exceptions, see [`public/licenses`](./public/licenses/)
([LICENSE.txt](./public/licenses/LICENSE.txt), [GPLv3](./public/licenses/GPLv3.txt), [ACKNOWLEDGEMENTS](./public/licenses/ACKNOWLEDGEMENTS.txt)).

## Credits
* [AlliedModders](https://github.com/alliedmodders) — AMX Mod X
* Adidasman and contributors — ReHLDS/ReGameDLL adaptation (2016)
* ReHLDS team
