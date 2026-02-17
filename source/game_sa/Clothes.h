/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AnimationEnums.h"
#include "eClothesModelPart.h"
#include "eClothesTexturePart.h"

class CPedClothesDesc;
class CPlayerPed;

class CClothes {
public:
    static uint32 (&ms_clothesRules)[600];
    static uint32& ms_numRuleTags;
    static int32& ms_clothesImageId;

public:
    static void RebuildPlayer(CPlayerPed* player, bool forReplay);
    static void RebuildCutscenePlayer(CPlayerPed* pPlayer, int32 modelId);
    static void ConstructPedModel(uint32 modelId, CPedClothesDesc& clothesDesc, const CPedClothesDesc* oldClothesDesc, bool cutsceneVersion);
    static void Test();
    static void RenderTest();
    static void RebuildPlayerIfNeeded(CPlayerPed* player);

    static void Init();

    static AssocGroupId GetDefaultPlayerMotionGroup();
    static AssocGroupId GetPlayerMotionGroupToLoad();
    static void RequestMotionGroupAnims();

    static eClothesModelPart   GetTextureDependency(eClothesTexturePart tex);
    static eClothesTexturePart GetDependentTexture(eClothesModelPart model);

    static void LoadClothesFile();

private: // NOTSA:
    friend void InjectHooksMain();
    static void InjectHooks();

    static void AddRule(uint32 rule) {
        ms_clothesRules[ms_numRuleTags] = rule;
        ms_numRuleTags += 1;
    }
};
