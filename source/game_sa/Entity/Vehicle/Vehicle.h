/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <optional>
#include <extensions/EntityRef.hpp>

#include "Physical.h"
#include "AEVehicleAudioEntity.h"
#include "tHandlingData.h"
#include "tFlyingHandlingData.h"
#include "AutoPilot.h"
#include "eVehicleHandlingFlags.h"
#include "StoredCollPoly.h"
#include "VehicleModelInfo.h"
#include "tBoatHandlingData.h"
#include "PtrList.h"
#include "RideAnimData.h"
#include "DamageManager.h"
#include "FxSystem.h"
#include "Fire.h"

#include <Enums/eControllerType.h>

/*  Thanks to MTA team for https://github.com/multitheftauto/mtasa-blue/blob/master/Client/game_sa/CVehicleSA.cpp */

class CWeapon;
class CPed;
class CPlane;
class CHeli;
class CPedGroup;
class CVehicleAnimGroup;

enum eCarWeapon : uint8 {
    CAR_WEAPON_NOT_USED       = 0,
    CAR_WEAPON_HEAVY_GUN      = 1,
    CAR_WEAPON_FREEFALL_BOMB  = 2,
    CAR_WEAPON_LOCK_ON_ROCKET = 3,
    CAR_WEAPON_DOUBLE_ROCKET  = 4,
};

enum eCarLockState : uint32 {
    CARLOCK_NOT_USED = 0,
    CARLOCK_UNLOCKED,
    CARLOCK_LOCKED,
    CARLOCK_LOCKOUT_PLAYER_ONLY,
    CARLOCK_LOCKED_PLAYER_INSIDE,
    CARLOCK_COP_CAR,
    CARLOCK_FORCE_SHUT_DOORS,
    CARLOCK_SKIP_SHUT_DOORS
};

enum eVehicleAppearance {
    VEHICLE_APPEARANCE_NONE = 0,
    VEHICLE_APPEARANCE_AUTOMOBILE = 1,
    VEHICLE_APPEARANCE_BIKE = 2,
    VEHICLE_APPEARANCE_HELI = 3,
    VEHICLE_APPEARANCE_BOAT = 4,
    VEHICLE_APPEARANCE_PLANE = 5,
};

enum eVehicleLightsFlags : uint32 {
    VEHICLE_LIGHTS_TWIN = 1,
    VEHICLE_LIGHTS_IGNORE_DAMAGE = 4,
    VEHICLE_LIGHTS_DISABLE_FRONT = 16,
    VEHICLE_LIGHTS_DISABLE_REAR = 32
};

enum eVehicleCreatedBy : uint8 {
    UNUSED_VEHICLE = 0,
    RANDOM_VEHICLE,
    MISSION_VEHICLE,
    PARKED_VEHICLE,
    PERMANENT_VEHICLE
};

enum eBombState {
    BOMB_TIMED_NOT_ACTIVATED = 1,
    BOMB_IGNITION = 2,
    BOMB_STICKY = 3,
    BOMB_TIMED_ACTIVATED = 4,
    BOMB_IGNITION_ACTIVATED = 5
};

enum eVehicleOverrideLightsState {
    NO_CAR_LIGHT_OVERRIDE = 0,
    FORCE_CAR_LIGHTS_OFF = 1,
    FORCE_CAR_LIGHTS_ON = 2
};

enum eCarPiece {
    CAR_PIECE_DEFAULT     = 0,
    CAR_PIECE_BONNET      = 1,
    CAR_PIECE_BOOT        = 2,
    CAR_PIECE_BUMP_FRONT  = 3,
    CAR_PIECE_BUMP_REAR   = 4,
    CAR_PIECE_DOOR_LF     = 5,
    CAR_PIECE_DOOR_RF     = 6,
    CAR_PIECE_DOOR_LR     = 7,
    CAR_PIECE_DOOR_RR     = 8,
    CAR_PIECE_WING_LF     = 9,
    CAR_PIECE_WING_RF     = 10,
    CAR_PIECE_WING_LR     = 11,
    CAR_PIECE_WING_RR     = 12,
    CAR_PIECE_WHEEL_LF    = 13, // front wheel for 2 wheel bike
    CAR_PIECE_WHEEL_RF    = 14,
    CAR_PIECE_WHEEL_RL    = 15, // rear wheel for 2 wheel bike
    CAR_PIECE_WHEEL_RR    = 16,
    CAR_PIECE_BIKEWHEEL_F = 17,
    CAR_PIECE_BIKEWHEEL_R = 18,
    CAR_PIECE_WINDSCREEN  = 19,
};
constexpr inline eCarPiece eCarPiece_WheelPieces[]{ CAR_PIECE_WHEEL_LF, CAR_PIECE_WHEEL_RF, CAR_PIECE_WHEEL_RL, CAR_PIECE_WHEEL_RR };

// Do not change the order!
enum eRotationAxis : int32 {
    AXIS_X = 0,
    AXIS_Y = 1,
    AXIS_Z = 2
};

typedef int32 eOrdnanceType;
typedef int32 eBikeWheelSpecial;

enum eFlightModel : int32 {
    FLIGHT_MODEL_UNK = 0,
    FLIGHT_MODEL_BARON = 1,
    FLIGHT_MODEL_RC = 2,
    FLIGHT_MODEL_PLANE = 3, // also used for cars
    FLIGHT_MODEL_UNK2 = 4,
    FLIGHT_MODEL_BOAT = 5,
    FLIGHT_MODEL_HELI = 6, // also used for hydra
};

enum tWheelState : int32 {
    WHEEL_STATE_NORMAL,   // standing still or rolling normally
    WHEEL_STATE_SPINNING, // rotating but not moving
    WHEEL_STATE_SKIDDING,
    WHEEL_STATE_FIXED,    // not rotating
};

enum class eVehicleCollisionComponent : uint16
{
    DEFAULT = 0x0,
    BONNET = 0x1,
    BOOT = 0x2,
    BUMP_FRONT = 0x3,
    BUMP_REAR = 0x4,
    DOOR_LF = 0x5,
    DOOR_RF = 0x6,
    DOOR_LR = 0x7,
    DOOR_RR = 0x8,
    WING_LF = 0x9,
    WING_RF = 0xA,
    WING_LR = 0xB,
    WING_RR = 0xC,
    WINDSCREEN = 0x13,
};

struct tHydraulicData {
    // applied when the vehicle is moving
    // or when hopping keys are pressed (numpad keys)
    float m_fSuspensionNormalUpperLimit;
    float m_fSuspensionNormalLowerLimit;

    // applied when the suspension is extended, like when you press the horn button (caps lock on pc)
    // or when numpad keys are pressed
    float m_fSuspensionExtendedUpperLimit;
    float m_fSuspensionExtendedLowerLimit;

    // applied when the vehicle is at rest (idle/not moving)
    // and does NOT apply if numpad keys are pressed (car hopping)
    float m_fSuspensionNormalIdleUpperLimit;
    float m_fSuspensionNormalIdleLowerLimit;
    float m_aWheelSuspension[4];
};

VALIDATE_SIZE(tHydraulicData, 0x28);

class NOTSA_EXPORT_VTABLE CVehicle : public CPhysical {
public:
    using Ref = notsa::EntityRef<CVehicle>;

public:
    static constexpr auto NUM_VEHICLE_UPGRADES = 15u;

public:
    enum class eComedyControlState : uint8 {
        INACTIVE,
        STEER_RIGHT,
        STEER_LEFT
    };
public:
    CAEVehicleAudioEntity m_vehicleAudio;
    tHandlingData*        m_pHandlingData;
    tFlyingHandlingData*  m_pFlyingHandlingData;
    union { // TODO: The struct in `tHandlingData` is exactly the same thing, so use that here too! (Requires renaming fields in `tHandlingData`)
        eVehicleHandlingFlags m_nHandlingFlagsIntValue;
        struct {
            uint32 b1gBoost : 1;
            uint32 b2gBoost : 1;
            uint32 bNpcAntiRoll : 1;
            uint32 bNpcNeutralHandl : 1;
            uint32 bNoHandbrake : 1;
            uint32 bSteerRearwheels : 1;
            uint32 bHbRearwheelSteer : 1;
            uint32 bAltSteerOpt : 1;

            uint32 bWheelFNarrow2 : 1;
            uint32 bWheelFNarrow : 1;
            uint32 bWheelFWide : 1;
            uint32 bWheelFWide2 : 1;
            uint32 bWheelRNarrow2 : 1;
            uint32 bWheelRNarrow : 1;
            uint32 bWheelRWide : 1;
            uint32 bWheelRWide2 : 1;

            uint32 bHydraulicGeom : 1;
            uint32 bHydraulicInst : 1; // ..alled (bHydraulicInstalled)
            uint32 bHydraulicNone : 1;
            uint32 bNosInst : 1; // ...alled (bNosInstalled)
            uint32 bOffroadAbility : 1;
            uint32 bOffroadAbility2 : 1;
            uint32 bHalogenLights : 1;
            uint32 bProcRearwheelFirst : 1;
            uint32 bUseMaxspLimit : 1;
            uint32 bLowRider : 1;
            uint32 bStreetRacer : 1;
            uint32 bSwingingChassis : 1;
        } handlingFlags;
    };
    CAutoPilot m_autoPilot;
    union {
        struct {
            uint32 m_nVehicleUpperFlags;
            uint32 m_nVehicleLowerFlags;
        };
        struct {
            uint32 bIsLawEnforcer : 1;               // Is this guy chasing the player at the moment
            uint32 bIsAmbulanceOnDuty : 1;           // Ambulance trying to get to an accident
            uint32 bIsFireTruckOnDuty : 1;           // Firetruck trying to get to a fire
            uint32 bIsLocked : 1;                    // Is this guy locked by the script (cannot be removed)
            uint32 bEngineOn : 1;                    // For sound purposes. Parked cars have their engines switched off (so do destroyed cars)
            uint32 bIsHandbrakeOn : 1;               // How's the handbrake doing ?
            uint32 bLightsOn : 1;                    // Are the lights switched on ?
            uint32 bFreebies : 1;                    // Any freebies left in this vehicle ?

            uint32 bIsVan : 1;                       // Is this vehicle a van (doors at back of vehicle)
            uint32 bIsBus : 1;                       // Is this vehicle a bus
            uint32 bIsBig : 1;                       // Is this vehicle big
            uint32 bLowVehicle : 1;                  // Need this for sporty type cars to use low getting-in/out anims
            uint32 bComedyControls : 1;              // Will make the car hard to control (hopefully in a funny way)
            uint32 bWarnedPeds : 1;                  // Has scan and warn peds of danger been processed?
            uint32 bCraneMessageDone : 1;            // A crane message has been printed for this car already
            uint32 bTakeLessDamage : 1;              // This vehicle is stronger (takes about 1/4 of damage)

            uint32 bIsDamaged : 1;                   // This vehicle has been damaged and is displaying all its components
            uint32 bHasBeenOwnedByPlayer : 1;        // To work out whether stealing it is a crime
            uint32 bFadeOut : 1;                     // Fade vehicle out
            uint32 bIsBeingCarJacked : 1;            //
            uint32 bCreateRoadBlockPeds : 1;         // If this vehicle gets close enough we will create peds (coppers or gang members) round it
            uint32 bCanBeDamaged : 1;                // Set to FALSE during cut scenes to avoid explosions
            uint32 bOccupantsHaveBeenGenerated : 1;  // Is true if the occupants have already been generated. (Shouldn't happen again)
            uint32 bGunSwitchedOff : 1;              // Level designers can use this to switch off guns on boats

            uint32 bVehicleColProcessed : 1;         // Has ProcessEntityCollision been processed for this car?
            uint32 bIsCarParkVehicle : 1;            // Car has been created using the special CAR_PARK script command
            uint32 bHasAlreadyBeenRecorded : 1;      // Used for replays
            uint32 bPartOfConvoy : 1;
            uint32 bHeliMinimumTilt : 1;             // This heli should have almost no tilt really
            uint32 bAudioChangingGear : 1;           // sounds like vehicle is changing gear
            uint32 bIsDrowning : 1;                  // is vehicle occupants taking damage in water (i.e. vehicle is dead in water)
            uint32 bTyresDontBurst : 1;              // If this is set the tyres are invincible

            uint32 bCreatedAsPoliceVehicle : 1;      // True if this guy was created as a police vehicle (enforcer, policecar, miamivice car etc)
            uint32 bRestingOnPhysical : 1;           // Don't go static cause car is sitting on a physical object that might get removed
            uint32 bParking : 1;
            uint32 bCanPark : 1;
            uint32 bFireGun : 1;                     // Does the ai of this vehicle want to fire it's gun?
            uint32 bDriverLastFrame : 1;             // Was there a driver present last frame ?
            uint32 bNeverUseSmallerRemovalRange : 1; // Some vehicles (like planes) we don't want to remove just behind the camera.
            uint32 bIsRCVehicle : 1;                 // Is this a remote controlled (small) vehicle. True whether the player or AI controls it.

            uint32 bAlwaysSkidMarks : 1;             // This vehicle leaves skidmarks regardless of the wheels' states.
            uint32 bEngineBroken : 1;                // Engine doesn't work. Player can get in but the vehicle won't drive
            uint32 bVehicleCanBeTargetted : 1;       // The ped driving this vehicle can be targeted, (for Torenos plane mission)
            uint32 bPartOfAttackWave : 1;            // This car is used in an attack during a gang war
            uint32 bWinchCanPickMeUp : 1;            // This car cannot be picked up by any ropes.
            uint32 bImpounded : 1;                   // Has this vehicle been in a police impounding garage
            uint32 bVehicleCanBeTargettedByHS : 1;   // Heat seeking missiles will not target this vehicle.
            uint32 bSirenOrAlarm : 1;                // Set to TRUE if siren or alarm active, else FALSE

            uint32 bHasGangLeaningOn : 1;
            uint32 bGangMembersForRoadBlock : 1;     // Will generate gang members if NumPedsForRoadBlock > 0
            uint32 bDoesProvideCover : 1;            // If this is false this particular vehicle can not be used to take cover behind.
            uint32 bMadDriver : 1;                   // This vehicle is driving like a lunatic
            uint32 bUpgradedStereo : 1;              // This vehicle has an upgraded stereo
            uint32 bConsideredByPlayer : 1;          // This vehicle is considered by the player to enter
            uint32 bPetrolTankIsWeakPoint : 1;       // If false shooting the petrol tank will NOT Blow up the car
            uint32 bDisableParticles : 1;            // Disable particles from this car. Used in garage.

            uint32 bHasBeenResprayed : 1;            // Has been resprayed in a respray garage. Reset after it has been checked.
            uint32 bUseCarCheats : 1;                // If this is true will set the car cheat stuff up in ProcessControl()
            uint32 bDontSetColourWhenRemapping : 1;  // If the texture gets remapped we don't want to change the colour with it.
            uint32 bUsedForReplay : 1;               // This car is controlled by replay and should be removed when replay is done.
        } vehicleFlags;
    };

    uint32            m_TimeOfCreation;

    uint8             m_nPrimaryColor, m_nSecondaryColor, m_nTertiaryColor, m_nQuaternaryColor; // m_colour1 - m_colour4
    uint8             m_anExtras[2]; // m_comp1 - m_comp2
    std::array<int16, NUM_VEHICLE_UPGRADES> m_upgrades;
    float             m_wheelScale;

    uint16            m_CarAlarmState;
    int16             m_nForcedRandomRouteSeed; // if this is non-zero the random wander gets deterministic, ForcedRandomSeed

    CPed*             m_pDriver;
    CPed*             m_apPassengers[8]{};
    uint8             m_nNumPassengers;
    uint8             m_nNumGettingIn;
    uint8             m_nGettingInFlags;
    uint8             m_nGettingOutFlags;
    uint8             m_nMaxPassengers;
    uint8             m_nWindowsOpenFlags; // initialised, but not used?
    uint8             m_nNitroBoosts;

    int8              m_vehicleSpecialColIndex;
    CEntity*          m_pEntityWeAreOn; // we get it from CWorld::ProcessVerticalLine or ProcessEntityCollision, it's entity under us,
                                        // only static entities (buildings or roads)

    CFire*            m_pFire;

    float             m_fSteerAngle;
    float             m_f2ndSteerAngle; // used for steering 2nd set of wheels or elevators etc..
    float             m_GasPedal;
    float             m_BrakePedal;

//protected:
    eVehicleCreatedBy m_nCreatedBy;

public:
    int16             m_nExtendedRemovalRange;        // when game wants to delete a vehicle, it gets min(m_wExtendedRemovalRange, 170.0)

    uint8             m_nBombOnBoard : 3;             // 0 = None
                                                      // 1 = Timed
                                                      // 2 = On ignition
                                                      // 3 = remotely set ?
                                                      // 4 = Timed Bomb has been activated
                                                      // 5 = On ignition has been activated
    uint8            m_nOverrideLights : 2;           // uses enum NO_CAR_LIGHT_OVERRIDE, FORCE_CAR_LIGHTS_OFF, FORCE_CAR_LIGHTS_ON
    uint8            m_ropeType : 2;                  // See `eRopeType` (also called `m_nWinchType`)
    uint8            m_nGunsCycleIndex : 2;           // Cycle through alternate gun hard-points on planes/helis
    uint8            m_nOrdnanceCycleIndex : 2;       // Cycle through alternate ordnance hard-points on planes/helis

    uint8            m_nUsedForCover;                 // Has n number of cops hiding/attempting to hid behind it
    uint8            m_nAmmoInClip;                   // Used to make the guns on boat do a reload (20 by default).
    uint8            m_nPacMansCollected;             // initialised, but not used?
    uint8            m_nPedsPositionForRoadBlock;     // 0, 1 or 2
    uint8            m_nNumCopsForRoadBlock;

    float            m_fDirtLevel; // Dirt level of vehicle body texture: 0.0f=fully clean, 15.0f=maximum dirt visible, aka nBodyDirtLevel

    uint8            m_nCurrentGear;
    float            m_fGearChangeCount; // used as parameter for cTransmission::CalculateDriveAcceleration, but doesn't change

    float            m_fWheelSpinForAudio;

    float            m_fHealth; // 1000.0f = full health. 0 -> explode

    CVehicle*        m_pTowingVehicle;            // m_pTractor
    CVehicle*        m_pVehicleBeingTowed;        // m_pTrailer

    // uint32 m_bFireAutoFlare; // In Mobile

    CEntity*         m_BombOwner; // Who Installed Bomb On Me

    uint32           m_nTimeTillWeNeedThisCar;     // game won't try to delete this car while this time won't reach

    uint32           m_nGunFiringTime;             // last time when gun on vehicle was fired (used on boats)
    uint32           m_nTimeWhenBlowedUp;          // game will delete vehicle when 60 seconds after this time will expire

    uint16           m_nCopsInCarTimer;            // timer for police car (which is following player) occupants to stay in car. If this timer reachs
                                            // some value, they will leave a car. The timer increases each frame if player is stopped in car,
                                            // otherway it resets

    uint16          m_wBombTimer;           // goes down with each frame
    CEntity*        m_pWhoDetonatedMe;      // if vehicle was detonated, game copies m_BombOwner here

    // we get these values from CCollision::IsStoredPolyStillValidVerticalLine or CWorld::ProcessVerticalLine
    float           m_LastFrontHeight, m_LastRearHeight;

    uint8           m_NumOilSpillsToDo; // initialised, unused
    float           m_OilSpillLastX, m_OilSpillLastY; // unused

    eCarLockState   m_eDoorLockState;

    uint32          m_nProjectileWeaponFiringTime;           // manual-aimed projectiles for hunter, lock-on projectile for hydra
    uint32          m_nAdditionalProjectileWeaponFiringTime; // manual-aimed projectiles for hydra

    uint32          m_nTimeForMinigunFiring;                 // minigun on hunter

    uint8           m_nLastWeaponDamageType;                 // see eWeaponType, -1 if no damage
    CEntity*        m_pLastDamageEntity;

    uint8           m_nRadioStation; // unused
    uint8           m_nRainHitCount; // initialised, unused
    uint8           m_nSoundIndex;   // initialised, unused

    eCarWeapon      m_nVehicleWeaponInUse;

    uint32          m_HornCounter;
    uint8           m_HornPattern;
    uint8           m_nCarHornTimer; // car horn related

    eComedyControlState m_comedyControlState;

    uint8           m_nHasslePosId;

    CStoredCollPoly m_FrontCollPoly;          // poly which is under front part of car
    CStoredCollPoly m_RearCollPoly;           // poly which is under rear part of car
    tColLighting    m_anCollisionLighting[4]; // left front, left rear, right front, right rear

    FxSystem_c*     m_pOverheatParticle;
    FxSystem_c*     m_pFireParticle;
    FxSystem_c*     m_pDustParticle;

    union {
        uint8 m_nRenderLightsFlags;
        struct {
            uint8 m_bRightFront : 1;
            uint8 m_bLeftFront : 1;
            uint8 m_bRightRear : 1;
            uint8 m_bLeftRear : 1;
        } m_renderLights;
    };

//protected:
    RwTexture*   m_CustomPlateTexture;

    float        m_fSteer;
    eVehicleType m_baseVehicleType;
    eVehicleType m_vehicleType; // Hack to have stuff be 2 classes at once, like vortex which can act like a car and a boat

    int16        m_remapTxd; // const char* m_remapTxdName;       // In Mobile
    int16        m_newRemapTxd; // const char* m_newRemapTxdName; // In Mobile
    RwTexture*   m_pRemapTexture;

public:
    inline static float WHEELSPIN_TARGET_RATE = 1.0f; // 0x8D3498
    inline static float WHEELSPIN_INAIR_TARGET_RATE = 10.0f; // 0x8D349C
    inline static float WHEELSPIN_RISE_RATE = 0.95f; // 0x8D34A0
    inline static float WHEELSPIN_FALL_RATE = 0.7f; // 0x8D34A4

    inline static bool ms_forceVehicleLightsOff; // 0xC1CC18

    inline static bool s_bPlaneGunsEjectShellCasings; // 0xC1CC19, unused
    inline static float m_fAirResistanceMult = 2.5f; // 0x8D34A8
    inline static float ms_fRailTrackResistance = 0.003f; // 0x8D34AC
    inline static float ms_fRailTrackResistanceDefault = 0.003f; // 0x8D34B0

    inline static bool bDisableRemoteDetonation; // 0xC1CC00
    inline static bool bDisableRemoteDetonationOnContact; // 0xC1CC01
    inline static bool m_bEnableMouseSteering; // 0xC1CC02
    inline static bool m_bEnableMouseFlying; // 0xC1CC03
    inline static eControllerType m_nLastControlInput; // 0xC1CC04

    inline static std::array<CColModel, 4> m_aSpecialColModel; // 0xC1CC78
    inline static std::array<CVehicle*, 4> m_aSpecialColVehicle; // 0xC1CC08
    inline static std::array<tHydraulicData, 4> m_aSpecialHydraulicData; // 0xC1CB60

    // inline static CEntity* m_pTappedGasTankVehicle; // In Mobile

    static constexpr auto Type = VEHICLE_TYPE_IGNORE;

public:
    bool GetHasDualExhausts(); // Only Mobile?

protected:
    float GetNewSteeringAmt();

public:
    static void* operator new(size_t size);
    static void* operator new(size_t size, int32 poolRef);

    static void operator delete(void* data);
    static void operator delete(void* data, int32 poolRef);

    CVehicle(eVehicleCreatedBy createdBy);
    ~CVehicle() override;
    static void Shutdown();

    void SetModelIndex(uint32 index) override;
    bool SetupLighting() override;
    void RemoveLighting(bool reset) override;
    void PreRender() override;
    void Render() override;
    void SetupRender();
    void ResetAfterRender();
    void DeleteRwObject() override;
    void SpecialEntityPreCollisionStuff(CPhysical* physical, bool doingShift, bool& skipTestEntirely, bool& skipCol, bool& forceBuildingCol, bool& forceSoftCol) override;
    uint8 SpecialEntityCalcCollisionSteps(bool& doPreCheckAtFullSpeed, bool& doPreCheckAtHalfSpeed) override;

    virtual void ProcessControlCollisionCheck(bool applySpeed) { /* Do nothing */ }

    bool CanBeDeleted();

    virtual void ProcessControlInputs(uint8 playerNum) { /* Do nothing */ }
    // component index in m_apModelNodes array
    virtual void GetComponentWorldPosition(int32 componentId, CVector& outPos) { /* Do nothing */ }
    // component index in m_apModelNodes array
    virtual bool IsComponentPresent(int32 componentId) { return false; }

    virtual void OpenDoor(CPed* ped, int32 componentId, eDoors door, float doorOpenRatio, bool playSound) { /* Do nothing */ }

    virtual void ProcessOpenDoor(CPed* ped, uint32 doorComponentId, uint32 animGroup, uint32 animId, float fTime);

    //!!!!!!!!!!!!!!!!!!!
    // PAY CLOSE ATTENTION TO WHICH VERSION OF THE FUNCTIONS DOWN BELOW YOU'RE CALLING!
    //!!!!!!!!!!!!!!!!!!!
    virtual float GetDooorAngleOpenRatioU32(uint32 door) const { return 0.0F; }
    virtual float GetDooorAngleOpenRatio(const eDoors door) const { return 0.0F; }
    virtual bool IsDoorReadyU32(uint32 door) const { return false; }
    virtual bool IsDoorReady(eDoors door) const { return false; }
    virtual bool IsDoorFullyOpenU32(uint32 door) const { return false; }
    virtual bool IsDoorFullyOpen(eDoors door) const { return false; }
    virtual bool IsDoorClosedU32(uint32 door) const { return false; }
    virtual bool IsDoorClosed(eDoors door) const { return false; }
    virtual bool IsDoorMissingU32(uint32 door) const { return false; }
    virtual bool IsDoorMissing(eDoors door) const { return false; }

    void SetRemapTexDictionary(int32 txdId);

    int32 GetRemapIndex();
    void SetRemap(int32 remapIndex);

    // check if car has roof as extra
    virtual bool IsOpenTopCar() { return false; }
    // remove ref to this entity
    virtual void RemoveRefsToVehicle(CEntity* entity) { /* Do nothing */ }
    virtual void BlowUpCar(CEntity* damager, bool bHideExplosion) { /* Do nothing */ }
    virtual void BlowUpCarCutSceneNoExtras(bool bNoCamShake, bool bNoSpawnFlyingComps, bool bDetachWheels, bool bExplosionSound) { /* Do nothing */ }
    virtual bool SetUpWheelColModel(CColModel* wheelCol) { return false; }
    // returns false if it's not possible to burst vehicle's tyre or it is already damaged. bPhysicalEffect=true applies random moving force to vehicle
    virtual bool BurstTyre(uint8 tyreComponentId, bool bPhysicalEffect) { return false; }
    virtual bool IsRoomForPedToLeaveCar(uint32 doorId, CVector* arg1) { return false; }
    virtual void ProcessDrivingAnims(CPed* driver, bool bBlend);
    // get special ride anim data for bile or quad
    virtual CRideAnimData* GetRideAnimData() { return nullptr; }
    void DoDriveByShootings();

    virtual void SetupSuspensionLines() { /* Do nothing */ }
    virtual CVector AddMovingCollisionSpeed(CVector& point) { return {}; }
    void UpdateClumpAlpha();
    void KillPedsInVehicle();
    void KillPedsGettingInVehicle();
    void ActivateBomb();
    void ActivateBombWhenEntered();

    virtual void Fix() { /* Do nothing */ } // 0x6D6390
    virtual void SetupDamageAfterLoad() { /* Do nothing */ }
    virtual void DoBurstAndSoftGroundRatios() { /* Do nothing */ }

    virtual float GetHeightAboveRoad() const;

    virtual void PlayCarHorn() { /* Do nothing */ }
    virtual int32 GetNumContactWheels() { return 4; }

    void ProcessDelayedExplosion();

    void SetGettingInFlags(uint8 doorId);
    void SetGettingOutFlags(uint8 doorId);
    void ClearGettingInFlags(uint8 doorId);
    void ClearGettingOutFlags(uint8 doorId);
    void SetIsHandbrakeOn(bool newIsHandbrakeOn) { vehicleFlags.bIsHandbrakeOn = newIsHandbrakeOn; }
    bool GetIsHandbrakeOn() const { return false; }
    uint8 GetCurrentGear() const { return m_nCurrentGear; }
    // bool ClutchDisengaged() const; // unused, In VC
    void SetSteerAngle(float) { m_fSteerAngle; }
    float GetSteerAngle() const { return m_fSteerAngle; }
    void Set2ndSteerAngle(float) { m_f2ndSteerAngle; }
    float Get2ndSteerAngle() const { return m_f2ndSteerAngle; }

    void SetGasPedal(float pedal) { m_GasPedal = pedal; }
    float GetGasPedal() const { return m_GasPedal; }
    void SetBrakePedal(float pedal) { m_BrakePedal = pedal; }
    float GetBrakePedal() const { return m_BrakePedal; }
    bool AddPassenger(CPed* passenger);
    bool AddPassenger(CPed* passenger, uint8 seatNumber);
    void RemovePassenger(CPed* passenger);

    void SetDriver(CPed* driver);
    void RemoveDriver(bool arg0);

    CPed* SetUpDriver(int32 pedType, bool arg1, bool arg2);
    CPed* SetupPassenger(int32 seatNumber, int32 pedType, bool arg2, bool arg3);
    void FillVehicleWithPeds(bool bSetClothesToAfro);
    bool IsPassenger(const CPed* ped) const;
    [[nodiscard]] bool IsPassenger(int32 modelIndex) const;
    bool IsDriver(const CPed* ped) const;
    [[nodiscard]] bool IsDriver(int32 modelIndex) const;
    void UpdatePassengerList();
    CPed* PickRandomPassenger();

    float ProcessWheelRotation(tWheelState wheelState, const CVector& arg1, const CVector& arg2, float arg3);
    void SetCollisionLighting(tColLighting lighting);
    void UpdateLightingFromStoredPolys();
    void CalculateLightingFromCollision();

    eCarWheel FindTyreNearestPoint(CVector2D point);
    eVehicleType GetVehicleType() const { return m_vehicleType; }
    eVehicleType GetBaseVehicleType() const { return m_baseVehicleType; }

    void ReduceVehicleDamage(float& damage);

    bool CanUseCameraHeightSetting(); // In Mobile

    bool CanVehicleBeDamaged(CEntity* damager, eWeaponType weapon, bool& bDamagedDueToFireOrExplosionOrBullet);
    void InflictDamage(CEntity* damager, eWeaponType weapon, float intensity, CVector coords);
    virtual void VehicleDamage(float damageIntensity, eVehicleCollisionComponent collisionComponent, CEntity* damager, CVector* vecCollisionCoors, CVector* vecCollisionDirection, eWeaponType weapon) { /* Do nothing */ }

    bool IsUpsideDown() const;
    bool IsOnItsSide() const;
    bool UsesSiren() const;

    bool CarHasRoof() const;

    bool UsesTandemSeating() const { return m_pHandlingData->m_bTandemSeats; }

    void SetCarDoorLocks(eCarLockState newLockState) { m_eDoorLockState = newLockState; }
    bool CanPedOpenLocks(const CPed* ped) const;
    [[nodiscard]] bool CanDoorsBeDamaged() const;
    bool CanPedEnterCar();
    virtual bool CanPedStepOutCar(bool bIgnoreSpeedUpright = false) const;
    virtual bool CanPedJumpOutCar(CPed* ped);
    bool IsSphereTouchingVehicle(CVector posn, float radius);
    bool IsAlarmActivated() const { return m_CarAlarmState; }

    void ProcessCarAlarm();

    void DoFixedMachineGuns();
    bool IsVehicleNormal() const;

    void FlagToDestroyWhenNextProcessed() override { /* Do nothing */ }

    void ChangeLawEnforcerState(bool bIsEnforcer);
    bool IsLawEnforcementVehicle() const;
    static bool ShufflePassengersToMakeSpace();

    void SetCanBeDamaged(bool damageFlag) { vehicleFlags.bCanBeDamaged = damageFlag; }

    void ExtinguishCarFire();

    void FlyingControl(eFlightModel flightModel, float leftRightSkid, float steeringUpDown, float steeringLeftRight, float accelerationBreakStatus);
    float HeightAboveCeiling(float arg0, eFlightModel arg1);
    bool  DoBladeCollision(CVector pos, CMatrix& matrix, int16 rotorType, float radius, float damageMult);
    template<typename PtrListType>
    bool BladeColSectorList(PtrListType& ptrList, CColModel& colModel, CMatrix& matrix, int16 rotorType, float damageMult);
    static void SetComponentAtomicAlpha(RpAtomic* atomic, int32 alpha);
    void SetComponentVisibility(RwFrame* component, uint32 visibilityState);
    void SetComponentRotation(RwFrame* component, eRotationAxis axis, float angle, bool bResetPosition);
    void SetTransmissionRotation(RwFrame* component, float angleL, float angleR, CVector wheelPos, bool isFront);

    void ProcessBoatControl(tBoatHandlingData* boatHandling, float* fWaterResistance, bool bCollidedWithWorld, bool bPostCollision);
    void ApplyBoatWaterResistance(tBoatHandlingData* boatHandling, float fImmersionDepth);
    void DoBoatSplashes(float fWaterDamping);

    void SetEngineOn(bool value) { vehicleFlags.bEngineOn = value; }

    void FireFixedMachineGuns();
    // static void HeliDustGenerate(CEntity *heli, float radius, float ground, int32 rnd); // unused, In VC
    void DoSunGlare();
    [[nodiscard]] eVehicleAppearance GetVehicleAppearance() const;

    void AddDamagedVehicleParticles();
    void MakeDirty(CColPoint& colPoint);

    bool AddWheelDirtAndWater(CColPoint& colPoint, bool isProduceWheelDrops, bool isWheelsSpinning, bool isWheelInWater);

    void AddWaterSplashParticles();
    void AddExhaustParticles();
    bool AddSingleWheelParticles(tWheelState wheelState, uint32 arg1, float arg2, float arg3, CColPoint* arg4, CVector* arg5, float arg6, int32 arg7, uint32 surfaceType, bool* bloodState, uint32 arg10);

    bool GetVehicleLightsStatus();
    bool DoHeadLightEffect(eVehicleDummy dummyId, CMatrix& vehicleMatrix, uint8 lightId, uint8 lightState);
    void DoHeadLightBeam(eVehicleDummy dummyId, CMatrix& matrix, bool arg2);
    void DoHeadLightReflectionSingle(CMatrix& matrix, bool isRight);
    void DoHeadLightReflectionTwin(CMatrix& matrix);
    void DoHeadLightReflection(CMatrix& matrix, uint32 flags, bool left, bool right);
    bool DoTailLightEffect(int32 lightId, CMatrix& matrix, uint8 arg2, uint8 arg3, uint32 arg4, uint8 arg5);
    void DoReverseLightEffect(int32 lightId, CMatrix& matVehicle, bool isRight, bool forcedOff, uint32 nLightFlags, bool lightsOn);
    void DoVehicleLights(CMatrix& matrix, eVehicleLightsFlags flags);

    bool GetSpecialColModel();

    void AddVehicleUpgrade(int32 modelId);
    void RemoveVehicleUpgrade(int32 upgradeModelIndex);
    void RemoveAllUpgrades();
    void SetupUpgradesAfterLoad();
    // return upgrade model id or -1 if not present
    int32 GetUpgrade(int32 upgradeId);
    // return upgrade model id or -1 if not present
    int32 GetReplacementUpgrade(int32 nodeId);
    // int16* GetVehicleUpgradeArray(); // unused

    void SetWindowOpenFlag(uint8 doorId);
    void ClearWindowOpenFlag(uint8 doorId);

    [[nodiscard]] int32 GetSpareHasslePosId() const;
    void SetHasslePosId(int32 hasslePos, bool enable);

    void InitWinch(int32 arg0);
    void UpdateWinch();
    void RemoveWinch();
    void ReleasePickedUpEntityWithWinch() const;
    void PickUpEntityWithWinch(CEntity* entity) const;
    CEntity* QueryPickedUpEntityWithWinch() const;
    float GetRopeHeightForHeli() const;
    void SetRopeHeightForHeli(float height) const;

    void RenderDriverAndPassengers();
    void PreRenderDriverAndPassengers();

    CVehicle* GetVehicleTowedByThisOne() { return m_pVehicleBeingTowed; }

    virtual bool GetTowHitchPos(CVector& outPos, bool bCheckModelInfo, CVehicle* vehicle);
    virtual bool GetTowBarPos(CVector& outPos, bool bCheckModelInfo, CVehicle* vehicle);

    virtual bool SetTowLink(CVehicle* tractor, bool setMyPosToTowBar) { return false; }
    virtual bool BreakTowLink() { return false; }

    virtual float FindWheelWidth(bool bRear) { return 0.25F; }

    void ProcessWeapons();

    void GetPlaneWeaponFiringStatus(bool& status, eOrdnanceType& ordnanceType);
    void SelectPlaneWeapon(bool bChange, eOrdnanceType type);
    void DoPlaneGunFireFX(CWeapon* weapon, CVector& particlePos, CVector& gunshellPos, int32 particleIndex);
    void FirePlaneGuns();
    void FireUnguidedMissile(eOrdnanceType type, bool bCheckTime);
    CEntity* ScanAndMarkTargetForHeatSeekingMissile(CEntity* entity);
    void FireHeatSeakingMissile(CEntity* targetEntity, eOrdnanceType ordnanceType, bool arg2);
    void PossiblyDropFreeFallBombForPlayer(eOrdnanceType ordnanceType, bool arg1);
    int32 GetPlaneNumGuns();
    float GetPlaneGunsAutoAimAngle();
    uint32 GetPlaneGunsRateOfFire();
    CVector GetPlaneGunsPosition(int32 gunId);
    uint32 GetPlaneOrdnanceRateOfFire(eOrdnanceType type);
    CVector GetPlaneOrdnancePosition(eOrdnanceType type);
    void SetFiringRateMultiplier(float multiplier);
    float GetFiringRateMultiplier();

    bool CanBeDriven() const;

    void UpdateTrailerLink(bool arg0, bool arg1);
    void UpdateTractorLink(bool arg0, bool arg1);

    void ReactToVehicleDamage(CPed* ped);

    void ProcessSirenAndHorn(bool arg0);

    int32 GetVehicleCreatedBy() const { return m_nCreatedBy; }
    void SetVehicleCreatedBy(eVehicleCreatedBy createdBy);
    bool GetIsLawEnforcer() const { return vehicleFlags.bIsLawEnforcer; }

    bool CanPedLeanOut(CPed* ped);

    virtual bool Save();
    virtual bool Load();

    // This Only Mobile Function
    /*
    CVector GetGasTankPosition();
    static CEntity* GetTappedGasTankVehicle() { return m_pTappedGasTankVehicle; }
    static void SetTappedGasTankVehicle(CEntity* tappedGasTankVehicle);
    */

    uint8 GetBodyDirtLevelUInt8(); // unused, in mobile
    float GetBodyDirtLevel() { return m_fDirtLevel; } // unused
    void SetBodyDirtLevel(float dirtLevel);
    void SetMatrixForOrientation(float orientation);

protected:
    bool CustomCarPlate_TextureCreate(CVehicleModelInfo* model);
    void CustomCarPlate_TextureDestroy();

    void ProcessWheel(CVector& wheelFwd, CVector& wheelRight, CVector& wheelContactSpeed, CVector& wheelContactPoint, int32 wheelsOnGround, float thrust, float brake, float adhesion, int8 wheelId, float* wheelSpeed, tWheelState* wheelState, uint16 wheelStatus);
    void ProcessBikeWheel(CVector& wheelFwd, CVector& wheelRight, CVector& wheelContactSpeed, CVector& wheelContactPoint, int32 wheelsOnGround, float thrust, float brake, float adhesion, float destabTraction, int8 wheelId, float* wheelSpeed, tWheelState* wheelState, eBikeWheelSpecial special, uint16 wheelStatus);

    RpAtomic* CreateUpgradeAtomic(CBaseModelInfo* model, const UpgradePosnDesc* upgradePosn, RwFrame* parentComponent, bool isDamaged);
    RpAtomic* CreateReplacementAtomic(CBaseModelInfo* model, RwFrame* component, int16 arg2, bool bDamaged, bool bIsWheel);
    void AddUpgrade(int32 modelIndex, int32 upgradeIndex);
    void RemoveUpgrade(int32 upgradeId);
    void AddReplacementUpgrade(int32 modelIndex, int32 nodeId);
    void RemoveReplacementUpgrade(int32 nodeId);
    bool SetVehicleUpgradeFlags(int32 upgradeModelIndex, int32 mod, int32& resultModelIndex);
    bool ClearVehicleUpgradeFlags(int32 modelId, int32 upgradeIndex);

public: // all NOTSA functions
    void ApplyTurnForceToOccupantOnEntry(CPed* passenger);
    CPed* GetDriver() const { return m_pDriver; }
    bool IsPedOfModelInside(eModelID model) const;
    void DestroyVehicleAndDriverAndPassengers(CVehicle* vehicle);
    bool AreAnyOfPassengersFollowerOfGroup(const CPedGroup& group);
    auto GetPassengerIndex(const CPed* ped) const -> std::optional<size_t>;
    auto GetHealth() const noexcept { return m_fHealth; }

    // m_baseVehicleType start
    [[nodiscard]] bool IsVehicleTypeValid()     const { return m_baseVehicleType != VEHICLE_TYPE_IGNORE; }
    [[nodiscard]] bool IsAutomobile()           const { return m_baseVehicleType == VEHICLE_TYPE_AUTOMOBILE; }
    [[nodiscard]] bool IsMonsterTruck()         const { return m_baseVehicleType == VEHICLE_TYPE_MTRUCK; }
    [[nodiscard]] bool IsQuad()                 const { return m_baseVehicleType == VEHICLE_TYPE_QUAD; }
    [[nodiscard]] bool IsHeli()                 const { return m_baseVehicleType == VEHICLE_TYPE_HELI; }
    [[nodiscard]] bool IsPlane()                const { return m_baseVehicleType == VEHICLE_TYPE_PLANE; }
    [[nodiscard]] bool IsBoat()                 const { return m_baseVehicleType == VEHICLE_TYPE_BOAT; }
    [[nodiscard]] bool IsTrain()                const { return m_baseVehicleType == VEHICLE_TYPE_TRAIN; }
    [[nodiscard]] bool IsFakeAircraft()         const { return m_baseVehicleType == VEHICLE_TYPE_FHELI || m_baseVehicleType == VEHICLE_TYPE_FPLANE; }
    [[nodiscard]] bool IsBike()                 const { return m_baseVehicleType == VEHICLE_TYPE_BIKE; }
    [[nodiscard]] bool IsBMX()                  const { return m_baseVehicleType == VEHICLE_TYPE_BMX; }
    [[nodiscard]] bool IsTrailer()              const { return m_baseVehicleType == VEHICLE_TYPE_TRAILER; }
    // m_baseVehicleType end

    // m_vehicleType start
    [[nodiscard]] bool IsSubVehicleTypeValid() const { return m_vehicleType != VEHICLE_TYPE_IGNORE; }
    [[nodiscard]] bool IsSubAutomobile()       const { return m_vehicleType == VEHICLE_TYPE_AUTOMOBILE; }
    [[nodiscard]] bool IsSubMonsterTruck()     const { return m_vehicleType == VEHICLE_TYPE_MTRUCK; }
    [[nodiscard]] bool IsSubQuad()             const { return m_vehicleType == VEHICLE_TYPE_QUAD; }
    [[nodiscard]] bool IsSubHeli()             const { return m_vehicleType == VEHICLE_TYPE_HELI; }
    [[nodiscard]] bool IsSubPlane()            const { return m_vehicleType == VEHICLE_TYPE_PLANE; }
    [[nodiscard]] bool IsSubBoat()             const { return m_vehicleType == VEHICLE_TYPE_BOAT; }
    [[nodiscard]] bool IsSubTrain()            const { return m_vehicleType == VEHICLE_TYPE_TRAIN; }
    [[nodiscard]] bool IsSubFakeAircraft()     const { return m_vehicleType == VEHICLE_TYPE_FHELI || m_vehicleType == VEHICLE_TYPE_FPLANE; }
    [[nodiscard]] bool IsSubBike()             const { return m_vehicleType == VEHICLE_TYPE_BIKE; }
    [[nodiscard]] bool IsSubBMX()              const { return m_vehicleType == VEHICLE_TYPE_BMX; }
    [[nodiscard]] bool IsSubTrailer()          const { return m_vehicleType == VEHICLE_TYPE_TRAILER; }

    [[nodiscard]] bool IsSubRoadVehicle()      const { return !IsSubHeli() && !IsSubPlane() && !IsSubTrain(); }
    [[nodiscard]] bool IsSubFlyingVehicle()    const { return IsSubHeli() && IsSubPlane(); }
    // m_vehicleType end

    [[nodiscard]] bool IsTransportVehicle()    const { return m_nModelIndex == MODEL_TAXI    || m_nModelIndex == MODEL_CABBIE; }
    [[nodiscard]] bool IsAmphibiousHeli()      const { return m_nModelIndex == MODEL_SEASPAR || m_nModelIndex == MODEL_LEVIATHN; }
    [[nodiscard]] bool IsConstructionVehicle() const { return m_nModelIndex == MODEL_DUMPER  || m_nModelIndex == MODEL_DOZER || m_nModelIndex == MODEL_FORKLIFT; }

    [[nodiscard]] bool IsRealBike() const { return m_pHandlingData->m_bIsBike;  }
    [[nodiscard]] bool IsRealHeli() const { return m_pHandlingData->m_bIsHeli;  }
    [[nodiscard]] bool IsRealPlane()const { return m_pHandlingData->m_bIsPlane; }
    [[nodiscard]] bool IsRealBoat() const { return m_pHandlingData->m_bIsBoat;  }

    [[nodiscard]] eVehicleCreatedBy GetCreatedBy() const      { return m_nCreatedBy; }
    [[nodiscard]] bool IsCreatedBy(eVehicleCreatedBy v) const { return v == m_nCreatedBy; }
    [[nodiscard]] bool IsMissionVehicle() const { return m_nCreatedBy == MISSION_VEHICLE; }

    bool CanUpdateHornCounter() { return m_CarAlarmState == 0 || m_CarAlarmState == -1 || m_info.m_nStatus == STATUS_WRECKED; }

    CPlane* AsPlane() { return reinterpret_cast<CPlane*>(this); }
    CHeli*  AsHeli()  { return reinterpret_cast<CHeli*>(this); }

    CVehicleModelInfo* GetVehicleModelInfo() const;

    CVector GetDummyPositionObjSpace(eVehicleDummy dummy) const;
    CVector GetDummyPosition(eVehicleDummy dummy, bool bWorldSpace = true);

    /// get position of driver seat dummy (Object Space)
    CVector GetDriverSeatDummyPositionOS() const;

    /// get position of driver seat dummy (World Space)
    CVector GetDriverSeatDummyPositionWS();

    [[nodiscard]] auto GetRopeID() const { return (uint32)&m_nFlags + 1; } // yep, flags + 1
    [[nodiscard]] CVehicleAnimGroup& GetAnimGroup() const;
    [[nodiscard]] AssocGroupId GetAnimGroupId() const;

    auto HasDriver() const { return m_pDriver != nullptr; }
    auto HasPassengerAtSeat(int32 seat) const { return m_apPassengers[seat] != nullptr; } // TODO: Figure out a good enum for this
    auto GetPassengers() const { return std::span{ m_apPassengers, m_nMaxPassengers }; }
    auto GetMaxPassengerSeats() { return std::span{ m_apPassengers, m_nMaxPassengers }; } // NOTE: Added this because I plan to refactor `GetPassengers()`

    [[nodiscard]] float GetDefaultAirResistance() const {
        if (m_pHandlingData->m_fDragMult <= 0.01f) {
            return m_pHandlingData->m_fDragMult;
        } else {
            return m_pHandlingData->m_fDragMult / 1000.0f / 2.0f;
        }
    }

    /// Is there a driver who is also a ped
    bool IsDriverAPlayer() const;

    /// Is the vehicle totally flipped (Should probably be moved to `CPlaceable`)
    [[nodiscard]] bool IsTotallyUpsideDown() const { return GetUp().z < 0.f; }

    /// Is there enough space for at least one more passenger - TODO: -1 is only for buses
    [[nodiscard]] bool HasSpaceForAPassenger() const { return m_nMaxPassengers -1 > m_nNumPassengers; }

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    auto Constructor(eVehicleCreatedBy createdBy) {
        this->CVehicle::CVehicle(createdBy);
        return this;
    }

    auto Destructor() {
        this->CVehicle::~CVehicle();
        return this;
    }

};
VALIDATE_SIZE(CVehicle, 0x5A0);

bool IsValidModForVehicle(uint32 modelId, CVehicle* vehicle);
bool IsVehiclePointerValid(CVehicle* vehicle);
RpAtomic* RemoveUpgradeCB(RpAtomic* atomic, void* data);
RpAtomic* FindUpgradeCB(RpAtomic* atomic, void* data);
RwObject* RemoveObjectsCB(RwObject* object, void* data);
RwFrame* RemoveObjectsCB(RwFrame* component, void* data);
RwObject* CopyObjectsCB(RwObject* object, void* data);
RwObject* FindReplacementUpgradeCB(RwObject* object, void* data);
RpAtomic* RemoveAllUpgradesCB(RpAtomic* atomic, void* data);
RpMaterial* SetCompAlphaCB(RpMaterial* material, void* data);
RwObject* SetVehicleAtomicVisibilityCB(RwObject* object, void* data);
RwFrame* SetVehicleAtomicVisibilityCB(RwFrame* component, void* data);
void DestroyVehicleAndDriverAndPassengers(CVehicle* vehicle);
void SetVehicleAtomicVisibility(RpAtomic* atomic, int16 state);

inline void CVehicle::SetMatrixForOrientation(float orientation) {
    CMatrix& mat = *m_matrix;
    const auto fVar28 = std::sinf(orientation);
    const auto fVar29 = std::cosf(orientation);

    mat.GetRight() = CVector(fVar28, -fVar29, 0.0f);
    mat.GetForward() = CVector(fVar29, fVar28, 0.0f);
    mat.GetUp() = CVector(0.0f, 0.0f, 1.0f);
}

// Only Mobile
inline uint8 CVehicle::GetBodyDirtLevelUInt8() {
    return (int32)m_fDirtLevel & 0xF;
}

// inline
inline void CVehicle::SetBodyDirtLevel(float dirtLevel) {
    m_fDirtLevel = dirtLevel;
}
