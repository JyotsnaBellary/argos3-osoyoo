/**
 * @file <argos3/plugins/robots/osoyoo/simulator/osoyoo_proximity_default_sensor.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef OSOYOO_PROXIMITY_DEFAULT_SENSOR_H
#define OSOYOO_PROXIMITY_DEFAULT_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class COsoyooProximityDefaultSensor;
}

#include <argos3/plugins/robots/osoyoo/control_interface/ci_osoyoo_proximity_sensor.h>
#include <argos3/plugins/robots/generic/simulator/proximity_default_sensor.h>

namespace argos {

   class COsoyooProximityDefaultSensor : public CCI_OsoyooProximitySensor,
                                            public CSimulatedSensor {

   public:

      COsoyooProximityDefaultSensor();

      virtual ~COsoyooProximityDefaultSensor();

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();

      virtual void Reset();

   private:

      CProximityDefaultSensor* m_pcProximityImpl;

   };

}

#endif
