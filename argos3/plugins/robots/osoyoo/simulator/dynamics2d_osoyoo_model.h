/**
 * @file <osoyoo/simulator/dynamics2d_osoyoo_model.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef DYNAMICS2D_OSOYOO_MODEL_H
#define DYNAMICS2D_OSOYOO_MODEL_H

namespace argos {
   class CDynamics2DDifferentialSteeringControl;
   class CDynamics2DGripper;
   class CDynamics2DGrippable;
   class CDynamics2DOsoyooModel;
}

#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_single_body_object_model.h>
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_differentialsteering_control.h>
#include <argos3/plugins/robots/osoyoo/simulator/osoyoo_entity.h>

namespace argos {

   class CDynamics2DOsoyooModel : public CDynamics2DSingleBodyObjectModel {

   public:

      CDynamics2DOsoyooModel(CDynamics2DEngine& c_engine,
                              COsoyooEntity& c_entity);
      virtual ~CDynamics2DOsoyooModel();

      virtual void Reset();

      virtual void UpdateFromEntityStatus();
      
   private:

      COsoyooEntity& m_cOsoyooEntity;
      CWheeledEntity& m_cWheeledEntity;

      CDynamics2DDifferentialSteeringControl m_cDiffSteering;

      const Real* m_fCurrentWheelVelocity;

   };

}

#endif
