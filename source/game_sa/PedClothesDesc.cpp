#include "StdInc.h"

#include "PedClothesDesc.h"

void CPedClothesDesc::InjectHooks() {
    RH_ScopedClass(CPedClothesDesc);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Constructor, 0x5A8020);
    RH_ScopedInstall(Initialise, 0x5A78F0);
    RH_ScopedInstall(GetIsWearingBalaclava, 0x5A7950);
    RH_ScopedInstall(HasVisibleNewHairCut, 0x5A7970);
    RH_ScopedInstall(HasVisibleTattoo, 0x5A79D0);
}

CPedClothesDesc::CPedClothesDesc() {
    Initialise();
}

// 0x5A78F0
void CPedClothesDesc::Initialise() {
    std::ranges::fill(ModelKeys, 0);
    std::ranges::fill(TextureKeys, 0);
    SetFatStat(0.0f);
    SetStrengthStat(0.0f);
}

// 0x5A7910
void CPedClothesDesc::SetModel(uint32 modelId, eClothesModelPart modelPart) {
    ModelKeys[modelPart] = modelId;
}

// 0x5A7920
void CPedClothesDesc::SetModel(const char* model, eClothesModelPart modelPart) {
    if (model)
        ModelKeys[modelPart] = CKeyGen::GetUppercaseKey(model);
    else
        ModelKeys[modelPart] = 0;
}

// 0x5A7950
bool CPedClothesDesc::GetIsWearingBalaclava() {
    return IsWearingModel("balaclava", CLOTHES_MODEL_SPECIAL);
}

// 0x5A7970
bool CPedClothesDesc::HasVisibleNewHairCut(int32 type) {
    /* Balaclava hides the hair */
    if (ModelKeys[CLOTHES_MODEL_SPECIAL] == CKeyGen::GetUppercaseKey("balaclava")) {
        return false;
    }

    /* Hats hide the hair */
    if (ModelKeys[CLOTHES_MODEL_HATS] != 0) {
        return false;
    }

    if (ModelKeys[CLOTHES_MODEL_HEAD] == CKeyGen::GetUppercaseKey("head")) {
        return false;
    }

    return type != 1 || ModelKeys[CLOTHES_MODEL_HEAD] == CKeyGen::GetUppercaseKey("afro");
}

// 0x5A79D0
bool CPedClothesDesc::HasVisibleTattoo() {
    // NOTE: Android: CLOTHES_TEX_TATTOOS1 = 4, CLOTHES_TEX_TATTOOS9 = 12
    for (int i = eClothesTexturePart::CLOTHES_TEXTURE_LOWER_LEFT_ARM; i <= eClothesTexturePart::CLOTHES_TEXTURE_UPPER_BACK; ++i) {
        if (TextureKeys[i] != 0) return true;
    }

    return false;
}

// 0x5A8050
void CPedClothesDesc::SetTextureAndModel(uint32 texture, uint32 model, eClothesTexturePart texturePart) {
    plugin::CallMethod<0x5A8050, CPedClothesDesc*, uint32, uint32, eClothesTexturePart>(this, texture, model, texturePart);
}

// 0x5A8080
void CPedClothesDesc::SetTextureAndModel(const char* textureName, const char* modelName, eClothesTexturePart texturePart) {
    plugin::CallMethod<0x5A8080, CPedClothesDesc*, const char*, const char*, eClothesTexturePart>(this, textureName, modelName, texturePart);
}

