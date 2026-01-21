/**
 * @file <argos3/plugins/robots/osoyoo/simulator/osoyoo_ultrasonic_default_sensor.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef OSOYOO_ULTRASONIC_DEFAULT_SENSOR_H
#define OSOYOO_ULTRASONIC_DEFAULT_SENSOR_H

namespace argos {
   class COsoyooUltrasonicDefaultSensor;
   // class CUltrasonicDefaultSensor;
}

#include <argos3/core/simulator/sensor.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/utility/configuration/argos_configuration.h>

#include <argos3/plugins/robots/osoyoo/control_interface/ci_osoyoo_ultrasonic_sensor.h>
#include <argos3/plugins/robots/generic/simulator/proximity_default_sensor.h>

namespace argos {

class COsoyooUltrasonicDefaultSensor : public CSimulatedSensor,
                                       public CCI_OsoyooUltrasonicSensor {

public:

   COsoyooUltrasonicDefaultSensor();

   virtual ~COsoyooUltrasonicDefaultSensor();

   virtual void SetRobot(CComposableEntity& c_entity);
   virtual void Init(TConfigurationNode& t_tree);
   virtual void Update();
   virtual void Reset();

private:

   CProximityDefaultSensor* m_pcUltrasonicImpl;
};

} // namespace argos

#endif
