/**
 * @file <argos3/plugins/robots/osoyoo/simulator/osoyoo_proximity_default_sensor.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/simulator.h>
#include <argos3/plugins/simulator/entities/proximity_sensor_equipped_entity.h>

#include "osoyoo_ultrasonic_default_sensor.h"

namespace argos {

   /****************************************/
   /****************************************/

   class COsoyooUltrasonicSensorImpl : public CProximityDefaultSensor {

   public:

      void SetRobot(CComposableEntity& c_entity) override {
         try {
            m_pcEmbodiedEntity =
               &(c_entity.GetComponent<CEmbodiedEntity>("body"));
            m_pcControllableEntity =
               &(c_entity.GetComponent<CControllableEntity>("controller"));
            m_pcProximityEntity =
               &(c_entity.GetComponent<CProximitySensorEquippedEntity>(
                  "proximity_sensors[ultrasonic]"));
            m_pcProximityEntity->Enable();
         }
         catch(CARGoSException& ex) {
            THROW_ARGOSEXCEPTION_NESTED(
               "Can't set robot for Osoyoo ultrasonic sensor", ex);
         }
      }

      /* Ultrasonic semantics */
      Real CalculateReading(Real f_distance) override {
         return f_distance;
      }
   };

   /****************************************/
   /****************************************/

   COsoyooUltrasonicDefaultSensor::COsoyooUltrasonicDefaultSensor() :
      m_pcUltrasonicImpl(new COsoyooUltrasonicSensorImpl()) {}

   /****************************************/
   /****************************************/

   COsoyooUltrasonicDefaultSensor::~COsoyooUltrasonicDefaultSensor() {
      delete m_pcUltrasonicImpl;
   }

   /****************************************/
   /****************************************/

   void COsoyooUltrasonicDefaultSensor::SetRobot(CComposableEntity& c_entity) {
      try {
         m_pcUltrasonicImpl->SetRobot(c_entity);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Can't set robot for the Osoyoo proximity default sensor", ex);
      }
   }

   /****************************************/
   /****************************************/

   void COsoyooUltrasonicDefaultSensor::Init(TConfigurationNode& t_tree) {
      m_pcUltrasonicImpl->Init(t_tree);
   }

   /****************************************/
   /****************************************/

   void COsoyooUltrasonicDefaultSensor::Update() {
      m_pcUltrasonicImpl->Update();

   /* ProximityDefaultSensor::GetReadings() returns distances */
      m_sReading.Distance = m_pcUltrasonicImpl->GetReadings()[0];
   }

   /****************************************/
   /****************************************/

   void COsoyooUltrasonicDefaultSensor::Reset() {
      m_pcUltrasonicImpl->Reset();
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(COsoyooUltrasonicDefaultSensor,
                   "osoyoo_ultrasonic", "default",
                   "Carlo Pinciroli [ilpincy@gmail.com]",
                   "1.0",
                   "The Osoyoo ultrasonic sensor.",
                   "This sensor accesses the Osoyoo ultrasonic sensor. For a complete description\n"
                   "of its usage, refer to the ci_osoyoo_ultrasonic_sensor.h interface. For the XML\n"
                   "configuration, refer to the default ultrasonic sensor.\n",
                   "Usable"
		  );

}
