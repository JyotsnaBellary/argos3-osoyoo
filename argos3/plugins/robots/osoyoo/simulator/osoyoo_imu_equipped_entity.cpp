/**
 * @file <argos3/plugins/robots/osoyoo/simulator/osoyoo_quaternion_equipped_entity.cpp>
 *
 */

#include "osoyoo_imu_equipped_entity.h"
#include <argos3/core/simulator/space/space.h>

namespace argos
{

    CRadians COSOYOOIMUEquippedEntity::GetPitch() const
    {
        return Pitch;
    }

    CRadians COSOYOOIMUEquippedEntity::GetRoll() const
    {
        return Roll;
    }

    CRadians COSOYOOIMUEquippedEntity::GetYaw() const
    {
        return Yaw;
    }

    void COSOYOOIMUEquippedEntity::setPitch(const CRadians &fPitch)
    {
        Pitch = fPitch;
    }

    void COSOYOOIMUEquippedEntity::setRoll(const CRadians &fRoll)
    {
        Roll = fRoll;
    }

    void COSOYOOIMUEquippedEntity::setYaw(const CRadians &fYaw)
    {
        Yaw = fYaw;
    }

    /****************************************/
    /****************************************/

    COSOYOOIMUEquippedEntity::COSOYOOIMUEquippedEntity(CComposableEntity *pc_parent) : CEntity(pc_parent),
                                                                                 Pitch(CRadians()), Roll(CRadians()), Yaw(CRadians())
    {
    }

    /****************************************/
    /****************************************/

    COSOYOOIMUEquippedEntity::COSOYOOIMUEquippedEntity(CComposableEntity *pc_parent,
                                                 const std::string &str_id) : CEntity(pc_parent, str_id), Pitch(CRadians()), Roll(CRadians()), Yaw(CRadians())
    {
    }

    /****************************************/
    /****************************************/

    REGISTER_STANDARD_SPACE_OPERATIONS_ON_ENTITY(COSOYOOIMUEquippedEntity);

    /****************************************/
    /****************************************/

}