
#include "extension.h"

#include "PlayerManager.h"
#include "sm/sourcemod_players.h"
#include "sm/sourcemod_types.h"

namespace sm{
    inline namespace sourcemod {
        extern IGameConfig* g_pGameConf;
        extern ICvar* icvar;

        inline namespace players {
            static int lifestate_offset = -1;

            int GetLifeState(CBaseEntity* pEntity)
            {
                if (lifestate_offset == -1)
                {
                    if (!g_pGameConf->GetOffset("m_lifeState", &lifestate_offset))
                    {
                        lifestate_offset = -2;
                    }
                }

                if (*((uint8_t*)pEntity + lifestate_offset) == LIFE_ALIVE)
                {
                    return PLAYER_LIFE_ALIVE;
                }
                else
                {
                    return PLAYER_LIFE_DEAD;
                }
            }

            int GetLifeState(IGamePlayer* player)
            {
                if (lifestate_offset == -1)
                {
                    if (!g_pGameConf->GetOffset("m_lifeState", &lifestate_offset))
                    {
                        lifestate_offset = -2;
                    }
                }

                if (lifestate_offset < 0)
                {
                    IPlayerInfo* info = player->GetPlayerInfo();
                    if (info == NULL)
                    {
                        return PLAYER_LIFE_UNKNOWN;
                    }
                    return info->IsDead() ? PLAYER_LIFE_DEAD : PLAYER_LIFE_ALIVE;
                }

                auto edict = player->GetEdict();
                if (edict == NULL)
                {
                    return PLAYER_LIFE_UNKNOWN;
                }

                CBaseEntity* pEntity;
                IServerUnknown* pUnknown = edict->GetUnknown();
                if (pUnknown == NULL || (pEntity = pUnknown->GetBaseEntity()) == NULL)
                {
                    return PLAYER_LIFE_UNKNOWN;
                }

                return GetLifeState(pEntity);
            }

            const char* GetClientName(IGamePlayer* pPlayer)
            {
                if (!pPlayer)
                    return icvar->FindVar("hostname")->GetString();
                return pPlayer->GetName();
            }

            void ChangeClientTeam(IGamePlayer* pPlayer, int team) {
                IPlayerInfo* pInfo = pPlayer->GetPlayerInfo();
                return pInfo->ChangeTeam(team);
            }

            bool IsPlayerAlive(IGamePlayer* player) {
                return GetLifeState(player) == PLAYER_LIFE_ALIVE;
            }

            bool IsPlayerAlive(CBaseEntity* pEntity) {
                return pEntity && GetLifeState(pEntity) == PLAYER_LIFE_ALIVE;
            }

            bool IsClientConnected(IGamePlayer* pPlayer) {
                return pPlayer && pPlayer->IsConnected();
            }

            int GetArmorValue(IGamePlayer* pPlayer) {
                return pPlayer->GetPlayerInfo()->GetArmorValue();
            }

            int GetHealth(IGamePlayer* pPlayer) {
                return pPlayer->GetPlayerInfo()->GetHealth();
            }

        }
    }
}