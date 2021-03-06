#pragma once

#include "sourcemod_types.h"

namespace sm {
    namespace sdktools {
        namespace detail {
            bool SDK_OnLoad(char* error, size_t maxlength, bool late);
            void SDK_OnUnload();
        }
        void RemovePlayerItem(CBasePlayer * player, CBaseCombatWeapon *pItem);
        CBaseEntity *GivePlayerItem(CBasePlayer *player, const char *item, int iSubType = 0);
        void SetLightStyle(int style, const char *value);
        int GivePlayerAmmo(CBasePlayer * player, int amount, int ammotype, bool suppressSound=false);
        void SetEntityModel(CBaseEntity *entity, const char *model);
        bool AcceptEntityInput(CBaseEntity * dest, const char *input, CBaseEntity *  activator=nullptr, CBaseEntity *  caller=nullptr, int outputid=0);
        void ForcePlayerSuicide(CBasePlayer * player, bool bExplode = false, bool bForce = false);
        void EquipPlayerWeapon(CBasePlayer * player, CBaseEntity *entity);
    }
}