/**
 * @file <argos3/plugins/robots/generic/control_interface/ci_osoyoo_proximity_sensor.cpp>
 *
 * @author Jyotsna Bellary <jyotsnabellary@gmail.com>
 */


#include "ci_osoyoo_ultrasonic_sensor.h"

#ifdef ARGOS_WITH_LUA
#include <argos3/core/wrappers/lua/lua_utility.h>
#endif

namespace argos {
CCI_OsoyooUltrasonicSensor::~CCI_OsoyooUltrasonicSensor() = default;

CCI_OsoyooUltrasonicSensor::CCI_OsoyooUltrasonicSensor()  {
   m_sReading.Distance = 0.0f;
}

const CCI_OsoyooUltrasonicSensor::SReading& CCI_OsoyooUltrasonicSensor::GetReading() const {
   return m_sReading;
}

#ifdef ARGOS_WITH_LUA
void CCI_OsoyooUltrasonicSensor::CreateLuaState(lua_State* pt_lua_state) {
   CLuaUtility::OpenRobotStateTable(pt_lua_state, "ultrasonic");
   CLuaUtility::AddToTable(pt_lua_state, "distance", m_sReading.Distance);
   CLuaUtility::CloseRobotStateTable(pt_lua_state);
}
#endif

#ifdef ARGOS_WITH_LUA
void CCI_OsoyooUltrasonicSensor::ReadingsToLuaState(lua_State* pt_lua_state) {
   lua_getfield(pt_lua_state, -1, "ultrasonic");
   lua_pushnumber(pt_lua_state, m_sReading.Distance);
   lua_setfield(pt_lua_state, -2, "distance");
   lua_pop(pt_lua_state, 1);
}
#endif

std::ostream& operator<<(std::ostream& c_os,
                          const CCI_OsoyooUltrasonicSensor::SReading& s_reading) {
   c_os << "Distance=<" << s_reading.Distance << " m>";
   return c_os;
}

} // namespace argos
