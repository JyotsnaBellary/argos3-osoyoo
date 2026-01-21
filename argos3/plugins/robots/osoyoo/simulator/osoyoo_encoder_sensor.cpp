#include "osoyoo_encoder_sensor.h"
namespace argos {

void COsoyooEncoderSensor::SetRobot(CComposableEntity& c_entity) {
   try {
      /* Get the wheeled entity component */
      m_pcWheels =
         &(c_entity.GetComponent<CWheeledEntity>("wheels"));
   }
   catch(CARGoSException& ex) {
      THROW_ARGOSEXCEPTION_NESTED(
         "Can't set robot for the osoyoo encoder sensor", ex);
   }
}

void COsoyooEncoderSensor::Init(TConfigurationNode&) {
    m_fLeftDist  = 0.0;
    m_fRightDist = 0.0;

   m_sReading.WheelAxisLength = OSOYOO_WHEEL_DISTANCE;
}

void COsoyooEncoderSensor::Update() {
   /* Time step */
   const Real fDt = CPhysicsEngine::GetSimulationClockTick();

   /* Angular velocities (rad/s) */
   Real wL = m_pcWheels->GetWheelVelocity(0);
   Real wR = m_pcWheels->GetWheelVelocity(1);

   /* Linear velocities (m/s) */
   Real vL = wL * OSOYOO_WHEEL_RADIUS;
   Real vR = wR * OSOYOO_WHEEL_RADIUS;

   /* Integrate distance */
   Real dL = vL * fDt;
   Real dR = vR * fDt;

   m_fLeftDist  += dL;
   m_fRightDist += dR;

   /* Encoder reports delta since last step */
   m_sReading.CoveredDistanceLeftWheel  = dL;
   m_sReading.CoveredDistanceRightWheel = dR;
}

void COsoyooEncoderSensor::Reset() {
   m_fLeftDist  = 0.0f;
   m_fRightDist = 0.0f;

   m_sReading.CoveredDistanceLeftWheel  = 0.0f;
   m_sReading.CoveredDistanceRightWheel = 0.0f;
}

REGISTER_SENSOR(COsoyooEncoderSensor,
                "osoyoo_encoder",
                "default",
                "Jyotsna Bellary",
                "1.0",
                "Osoyoo wheel encoder sensor",
                "Returns wheel displacement per timestep",
                "Returns the distance covered by each wheel since the last update"
                );

} // namespace argos
