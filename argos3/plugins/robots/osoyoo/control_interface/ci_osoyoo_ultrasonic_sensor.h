/**
 * @file <argos3/plugins/robots/generic/control_interface/ci_osoyoo_ultrasonic_sensor.h>
 *
 * @author Danesh Tarapore <daneshtarapore@gmail.com>
 */

#ifndef CCI_OSOYOO_ULTRASONIC_SENSOR_H
#define CCI_OSOYOO_ULTRASONIC_SENSOR_H

namespace argos
{
   class CCI_OsoyooUltrasonicSensor;
}

#include <argos3/core/utility/math/angles.h>
#include <argos3/core/control_interface/ci_sensor.h>

namespace argos
{

   class CCI_OsoyooUltrasonicSensor : public CCI_Sensor {

public:

/**
 * Class constructor
 */
CCI_OsoyooUltrasonicSensor();

/**
 * Class destructor
 */
virtual ~CCI_OsoyooUltrasonicSensor();

// Sensor readings
   struct SReading {
      Real Distance;   // meters
   };

   const SReading& GetReading() const;

#ifdef ARGOS_WITH_LUA
      virtual void CreateLuaState(lua_State *pt_lua_state);

      virtual void ReadingsToLuaState(lua_State *pt_lua_state);
#endif

   protected:
      SReading m_sReading;
   };

   std::ostream& operator<<(std::ostream& c_os, const CCI_OsoyooUltrasonicSensor::SReading& s_reading);

}

#endif
