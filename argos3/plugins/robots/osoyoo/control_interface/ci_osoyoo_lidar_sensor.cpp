/**
 * @file <argos3/plugins/robots/osoyoo/control_interface/ci_osoyoo_lidar_sensor.cpp>
 *
 * @author Carlo Pinciroli <ilpincy@gmail.com>
 */

#include "ci_osoyoo_lidar_sensor.h"
#include <argos3/core/utility/math/angles.h>

#ifdef ARGOS_WITH_LUA
#include <argos3/core/wrappers/lua/lua_utility.h>
#endif

namespace argos {

   /****************************************/
   /****************************************/

   CCI_OsoyooLIDARSensor::CCI_OsoyooLIDARSensor() {
   }

   /****************************************/
   /****************************************/

#ifdef ARGOS_WITH_LUA
   void CCI_OsoyooLIDARSensor::CreateLuaState(lua_State* pt_lua_state) {
   }
#endif

   /****************************************/
   /****************************************/

#ifdef ARGOS_WITH_LUA
   void CCI_OsoyooLIDARSensor::ReadingsToLuaState(lua_State* pt_lua_state) {
   }
#endif


   /****************************************/
   /****************************************/

}
