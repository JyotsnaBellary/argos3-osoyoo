#include <argos3/core/simulator/sensor.h>
#include <argos3/plugins/robots/osoyoo/control_interface/ci_osoyoo_encoder_sensor.h>
#include <argos3/plugins/robots/osoyoo/simulator/osoyoo_entity.h>
#include "osoyoo_measures.h"

namespace argos {

class COsoyooEncoderSensor :
   public CSimulatedSensor,
   public CCI_OsoyooEncoderSensor {

public:
   void SetRobot(CComposableEntity& c_entity) override;
   void Init(TConfigurationNode& t_tree) override;
   void Update() override;
   void Reset() override;

private:
   COsoyooEntity*  m_pcOsoyoo;
   CWheeledEntity* m_pcWheels;

   CVector3 m_fPrevLeft;
   CVector3 m_fPrevRight;

   Real m_fLeftDistance;
   Real m_fRightDistance;

};

}