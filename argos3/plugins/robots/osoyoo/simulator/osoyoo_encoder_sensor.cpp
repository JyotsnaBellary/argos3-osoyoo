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
    m_fLeftDistance  = 0.0;
    m_fRightDistance = 0.0;

   m_sReading.WheelAxisLength = OSOYOO_WHEEL_DISTANCE;
}

void COsoyooEncoderSensor::Update() {
   /* Duration of one simulation step (seconds) */
   const Real fTimeStep = CPhysicsEngine::GetSimulationClockTick();

   /* Wheel angular velocities (rad/s) */
   const Real fLeftWheelAngularVelocity  = m_pcWheels->GetWheelVelocity(0);
   const Real fRightWheelAngularVelocity = m_pcWheels->GetWheelVelocity(1);

   /* Wheel linear velocities (m/s) */
   const Real fLeftWheelLinearVelocity  =
      fLeftWheelAngularVelocity  * OSOYOO_WHEEL_RADIUS;
   const Real fRightWheelLinearVelocity =
      fRightWheelAngularVelocity * OSOYOO_WHEEL_RADIUS;

   /* Distance traveled during this timestep (m) */
   const Real fLeftWheelDeltaDistance  =
      fLeftWheelLinearVelocity  * fTimeStep;
   const Real fRightWheelDeltaDistance =
      fRightWheelLinearVelocity  * fTimeStep;

   /* Accumulate total distance (optional state) */
   m_fLeftDistance  += fLeftWheelDeltaDistance;
   m_fRightDistance += fRightWheelDeltaDistance;

   /* Encoder output: delta since last update */
   m_sReading.CoveredDistanceLeftWheel  = fLeftWheelDeltaDistance;
   m_sReading.CoveredDistanceRightWheel = fRightWheelDeltaDistance;
}

void COsoyooEncoderSensor::Reset() {
   m_fLeftDistance  = 0.0f;
   m_fRightDistance = 0.0f;

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
