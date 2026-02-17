/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "eClothesModelPart.h"
#include "eClothesTexturePart.h"

class CPedClothesDesc {
public: // TODO: private, рowever, it's too much work
    std::array<uint32, CLOTHES_MODEL_TOTAL> ModelKeys;
    std::array<uint32, CLOTHES_TEXTURE_TOTAL> TextureKeys;

private:
    float FatStat;
    float MuscleStat; // StrengthStat

public:
    CPedClothesDesc();

    void Initialise();

    void SetTextureAndModel(uint32 tex, uint32 model, eClothesTexturePart texType);
    void SetTextureAndModel(const char* tex, const char* model, eClothesTexturePart texType);
    void SetModel(uint32 model, eClothesModelPart modelType);
    void SetModel(const char* model, eClothesModelPart modelType);

    uint32 GetModel(eClothesModelPart model) const { return ModelKeys[model]; }
    uint32 GetTexture(eClothesTexturePart tex) const { return TextureKeys[tex]; }

    uint32* GetModelKeyArray() { return ModelKeys.data(); }
    uint32* GetTextureKeyArray() { return TextureKeys.data(); }

    void  SetFatStat(float value) { FatStat = value; }
    float GetFatStat() const { return FatStat; }
    void SetStrengthStat(float value) { MuscleStat = value; }
    float GetStrengthStat() const { return MuscleStat; }

    bool GetIsWearingBalaclava();
    bool HasVisibleNewHairCut(int32 type);
    bool HasVisibleTattoo();

    bool operator==(const CPedClothesDesc& other) const {
        return ModelKeys == other.ModelKeys && TextureKeys == other.TextureKeys;
    }

private: // NOTSA:
    friend void InjectHooksMain();
    static void InjectHooks();

    CPedClothesDesc* Constructor() {
        this->CPedClothesDesc::CPedClothesDesc();
        return this;
    }

public:
    bool IsWearingModel(const char* model, std::optional<eClothesModelPart> modelPart = {}) const {
        return modelPart.has_value()
            ? ModelKeys[+*modelPart] == CKeyGen::GetUppercaseKey(model)
            : rng::contains(ModelKeys, CKeyGen::GetUppercaseKey(model));
    }
};

VALIDATE_SIZE(CPedClothesDesc, 0x78);
