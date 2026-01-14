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
                      OSOYOO_WHEEL_DISTANCE,
                      c_entity.GetConfigurationNode()),
      m_fCurrentWheelVelocity(m_cWheeledEntity.GetWheelVelocities()) {
      /* Create the body with initial position and orientation */
      cpBody* ptBody =
         cpSpaceAddBody(GetDynamics2DEngine().GetPhysicsSpace(),
                        cpBodyNew(OSOYOO_MASS,
                                  cpMomentForCircle(OSOYOO_MASS,
                                                    0.0f,
                                                    OSOYOO_BASE_RADIUS + OSOYOO_BASE_RADIUS,
                                                    cpvzero)));
      const CVector3& cPosition = GetEmbodiedEntity().GetOriginAnchor().Position;
      ptBody->p = cpv(cPosition.GetX(), cPosition.GetY());
      CRadians cXAngle, cYAngle, cZAngle;
      GetEmbodiedEntity().GetOriginAnchor().Orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
      cpBodySetAngle(ptBody, cZAngle.GetValue());
      /* Create the body shape */
      cpShape* ptShape =
         cpSpaceAddShape(GetDynamics2DEngine().GetPhysicsSpace(),
                         cpCircleShapeNew(ptBody,
                                          OSOYOO_BASE_RADIUS,
                                          cpvzero));
      ptShape->e = 0.0; // No elasticity
      ptShape->u = 0.7; // Lots of friction
      /* Constrain the actual base body to follow the diff steering control */
      m_cDiffSteering.AttachTo(ptBody);
      /* Set the body so that the default methods work as expected */
      SetBody(ptBody, OSOYOO_BASE_TOP);
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
      if((m_fCurrentWheelVelocity[OSOYOO_LEFT_WHEEL] != 0.0f) ||
         (m_fCurrentWheelVelocity[OSOYOO_RIGHT_WHEEL] != 0.0f)) {
         m_cDiffSteering.SetWheelVelocity(m_fCurrentWheelVelocity[OSOYOO_LEFT_WHEEL],
                                          m_fCurrentWheelVelocity[OSOYOO_RIGHT_WHEEL]);
      }
      else {
         /* No, we don't want to move - zero all speeds */
         m_cDiffSteering.Reset();
      }
   }

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_DYNAMICS2D_OPERATIONS_ON_ENTITY(COsoyooEntity, CDynamics2DOsoyooModel);

   /****************************************/
   /****************************************/

}
