/**
 * @file <osoyoo/simulator/dynamics2d_osoyoo_model.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "dynamics2d_osoyoo_model.h"
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_gripping.h>
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_engine.h>
#include "osoyoo_measures.h"

namespace argos {

   enum OSOYOO_WHEELS {
      OSOYOO_LEFT_WHEEL = 0,
      OSOYOO_RIGHT_WHEEL = 1
   };

   /****************************************/
   /****************************************/

   CDynamics2DOsoyooModel::CDynamics2DOsoyooModel(CDynamics2DEngine& c_engine,
                                                COsoyooEntity& c_entity) :
      CDynamics2DSingleBodyObjectModel(c_engine, c_entity),
      m_cOsoyooEntity(c_entity),
      m_cWheeledEntity(m_cOsoyooEntity.GetWheeledEntity()),
      m_cDiffSteering(c_engine,
                      OSOYOO_MAX_FORCE,
                      OSOYOO_MAX_TORQUE,
                      OSOYOO_INTERWHEEL_DISTANCE,
                      c_entity.GetConfigurationNode()),
      m_fCurrentWheelVelocity(m_cWheeledEntity.GetWheelVelocities()) {
      /* Create the body with initial position and orientation */
      cpBody* ptBody =
         cpSpaceAddBody(GetDynamics2DEngine().GetPhysicsSpace(),
                        cpBodyNew(OSOYOO_MASS,
                                  cpMomentForBox(OSOYOO_MASS,
                                                    OSOYOO_LENGTH,
                                                    OSOYOO_WIDTH)));
      const CVector3& cPosition = GetEmbodiedEntity().GetOriginAnchor().Position;
      ptBody->p = cpv(cPosition.GetX(), cPosition.GetY());
      CRadians cXAngle, cYAngle, cZAngle;
      GetEmbodiedEntity().GetOriginAnchor().Orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
      cpBodySetAngle(ptBody, cZAngle.GetValue());

      /* --- Chassis box --- */
cpVect tChassisVerts[4] = {
   cpv(+OSOYOO_LENGTH * 0.5f, +OSOYOO_WIDTH * 0.5f),
   cpv(+OSOYOO_LENGTH * 0.5f, -OSOYOO_WIDTH * 0.5f),
   cpv(-OSOYOO_LENGTH * 0.5f, -OSOYOO_WIDTH * 0.5f),
   cpv(-OSOYOO_LENGTH * 0.5f, +OSOYOO_WIDTH * 0.5f)
};

      /* Create the body shape */
cpShape* ptChassis =
   cpSpaceAddShape(GetDynamics2DEngine().GetPhysicsSpace(),
                   cpPolyShapeNew(ptBody,
                                  4,
                                  tChassisVerts,
                                  cpvzero));
ptChassis->e = 0.0;   // no bounce
ptChassis->u = 0.7;   // body friction
      
      /* --- Left wheel --- */
// cpShape* ptWheelL =
//    cpSpaceAddShape(GetDynamics2DEngine().GetPhysicsSpace(),
//                    cpCircleShapeNew(ptBody,
//                                     OSOYOO_WHEEL_RADIUS,
//                                     cpv(OSOYOO_WHEEL_OFFSET_X,
//                                         +OSOYOO_WHEEL_OFFSET_Y)));
// ptWheelL->e = 0.0;
// ptWheelL->u = 0.9;

// /* --- Right wheel --- */
// cpShape* ptWheelR =
//    cpSpaceAddShape(GetDynamics2DEngine().GetPhysicsSpace(),
//                    cpCircleShapeNew(ptBody,
//                                     OSOYOO_WHEEL_RADIUS,
//                                     cpv(OSOYOO_WHEEL_OFFSET_X,
//                                         -OSOYOO_WHEEL_OFFSET_Y)));
// ptWheelR->e = 0.0;
// ptWheelR->u = 0.9;
/* Constrain the actual base body to follow the diff steering control */
      m_cDiffSteering.AttachTo(ptBody);

      /* Set the body so that the default methods work as expected */
      SetBody(ptBody, OSOYOO_WHEEL_RADIUS + OSOYOO_HEIGHT);


   }

   /****************************************/
   /****************************************/

   CDynamics2DOsoyooModel::~CDynamics2DOsoyooModel() {
      m_cDiffSteering.Detach();
   }

   /****************************************/
   /****************************************/

   void CDynamics2DOsoyooModel::Reset() {
      CDynamics2DSingleBodyObjectModel::Reset();
      m_cDiffSteering.Reset();
   }

   /****************************************/
   /****************************************/

   void CDynamics2DOsoyooModel::UpdateFromEntityStatus() {
      /* Do we want to move? */
      const auto& v = m_cWheeledEntity.GetWheelVelocities();
if(v[OSOYOO_LEFT_WHEEL] != 0.0f || v[OSOYOO_RIGHT_WHEEL] != 0.0f) {
   m_cDiffSteering.SetWheelVelocity(v[0], v[1]);
}
else {
   m_cDiffSteering.Reset();
}
   }

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_DYNAMICS2D_OPERATIONS_ON_ENTITY(COsoyooEntity, CDynamics2DOsoyooModel);

   /****************************************/
   /****************************************/

}
