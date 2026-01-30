/**
 * @file <argos3/plugins/robots/osoyoo/simulator/osoyoo_measures.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef OSOYOO_MEASURES_H
#define OSOYOO_MEASURES_H

#include <argos3/core/utility/datatypes/datatypes.h>
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/math/vector3.h>

using namespace argos;

extern UInt8 OSOYOO_POWERON_LASERON;
extern const Real OSOYOO_MASS;
extern const Real OSOYOO_WIDTH;
extern const Real OSOYOO_HEIGHT;
extern const Real OSOYOO_LENGTH;
extern const Real OSOYOO_WHEEL_OFFSET_X;
extern const Real OSOYOO_WHEEL_OFFSET_Y;
// extern const Real OSOYOO_BASE_RADIUS;
extern const Real OSOYOO_BASE_ELEVATION;
extern const Real OSOYOO_BASE_HEIGHT;
extern const Real OSOYOO_LOWER_BODY_HEIGHT;
extern const Real OSOYOO_BASE_TOP;
// extern const Real UPPER_BODY_RADIUS;

extern const Real OSOYOO_HALF_LENGTH;
extern const Real OSOYOO_HALF_WIDTH;
extern const Real OSOYOO_FOOTPRINT_RADIUS;

extern const Real OSOYOO_WHEEL_RADIUS;
extern const Real OSOYOO_INTERWHEEL_DISTANCE;
extern const Real OSOYOO_HALF_INTERWHEEL_DISTANCE;
/* Visual-only wheel thickness (does NOT belong in measures) */
extern const Real OSOYOO_WHEEL_WIDTH;      // 2 cm, looks reasonable
extern const Real OSOYOO_HALF_WHEEL_WIDTH;

extern const Real OSOYOO_IR_SENSOR_RING_ELEVATION;
// extern const Real OSOYOO_IR_SENSOR_RING_RADIUS;
extern const Real OSOYOO_IR_SENSOR_RING_RANGE;
extern const Real OSOYOO_ULTRASONIC_RANGE;
extern const CRadians OSOYOO_LED_RING_START_ANGLE;
// extern const Real OSOYOO_LED_RING_RADIUS;
extern const Real OSOYOO_LED_RING_ELEVATION;
extern const Real OSOYOO_RAB_ELEVATION;

extern const Real OSOYOO_ULTRASOUND_SENSORS_RING_ELEVATION;
// extern const Real OSOYOO_ULTRASOUND_SENSORS_RING_RADIUS;
extern const CRange<Real> OSOYOO_ULTRASOUND_SENSORS_RING_RANGE;

extern const CVector2 OSOYOO_IR_SENSORS_GROUND_OFFSET[4];

extern const CVector3 OSOYOO_LEDS_OFFSET[3];

extern const Real OSOYOO_LIDAR_ELEVATION;
// extern const Real OSOYOO_LIDAR_SENSORS_FAN_RADIUS;
extern const CRadians OSOYOO_LIDAR_ANGLE_SPAN;
extern const CRange<Real> OSOYOO_LIDAR_SENSORS_RING_RANGE;

extern const Real OSOYOO_MAX_FORCE;
extern const Real OSOYOO_MAX_TORQUE;
extern const Real OMNIDIRECTIONAL_CAMERA_ELEVATION;

#endif
