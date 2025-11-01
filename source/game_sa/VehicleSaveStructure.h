#pragma once

#include "Matrix.h"
class CVehicle;

class CVehicleSaveStructure {
public:
    CMatrix m_matrix;
    uint8   m_VehicleCreatedBy; // unused
    uint8   m_nPrimaryColor, m_nSecondaryColor, m_nTertiaryColor, m_nQuaternaryColor; // m_Colour1 - m_Colour4
    uint16  m_CarAlarmState;
    uint8   m_nMaxPassengers;
    float   m_fSteerAngle;
    float   m_fGasPedal;
    float   m_fBrakePedal;
    uint32  m_nVehicleUpperFlags;
    uint32  m_nVehicleLowerFlags;

    // In Mobile:
    // float m_nHealth;
    // eCarLockState m_eDoorLockState;
    // uint32 m_nPhysicalFlags;
    // float m_fMass;
    // float m_fTurnMass;
    // float m_fBuoyancyConstant;
public:
    static void InjectHooks();

    void Construct(CVehicle* v);
    void Extract(CVehicle* v);
};
VALIDATE_SIZE(CVehicleSaveStructure, 0x68);
