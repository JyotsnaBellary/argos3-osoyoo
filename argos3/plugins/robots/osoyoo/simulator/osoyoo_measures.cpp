/**
 * @file <argos3/plugins/robots/osoyoo/simulator/osoyoo_measures.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "osoyoo_measures.h"

/****************************************/
/****************************************/
// Measures from here:
// https://emanual.robotis.com/docs/en/platform/osoyoo/features/

UInt8 OSOYOO_POWERON_LASERON   = 3;
const Real OSOYOO_MASS = 0.4f;
const Real OSOYOO_BASE_RADIUS    = 0.169; //important used for collision
const Real OSOYOO_BASE_ELEVATION = 0.045;
const Real OSOYOO_BASE_HEIGHT    = 0.351;
const Real OSOYOO_LOWER_BODY_HEIGHT    = 0.0934; // height of the lower body part
const Real OSOYOO_UPPER_BODY_HEIGHT = OSOYOO_BASE_HEIGHT - OSOYOO_LOWER_BODY_HEIGHT;
const Real OSOYOO_BASE_TOP       = OSOYOO_BASE_ELEVATION + OSOYOO_BASE_HEIGHT;
const Real OSOYOO_COLUMN_RADIUS       = 0.01f;  // tubes ~1cm
const Real OSOYOO_COLUMN_HEIGHT       = OSOYOO_UPPER_BODY_HEIGHT;
const Real OSOYOO_NUM_COLUMNS         = 3;

const Real OSOYOO_WHEEL_RADIUS        = 0.036; //important
const Real OSOYOO_WHEEL_DISTANCE      = 0.235;
const Real OSOYOO_HALF_WHEEL_DISTANCE = OSOYOO_WHEEL_DISTANCE * 0.5;
const Real UPPER_BODY_RADIUS = OSOYOO_BASE_RADIUS * 0.95f;


// const CVector3 OSOYOO_LEDS_OFFSET[3] = {
//    CVector3( 0.04,  0.025, OSOYOO_BASE_TOP),
//    CVector3(-0.05,  0.000, OSOYOO_BASE_TOP),
//    CVector3( 0.04, -0.025, OSOYOO_BASE_TOP)
// };

// extern const Real OSOYOO_IR_SENSORS_RING_ELEVATION;
// extern const Real OSOYOO_IR_SENSORS_RING_RADIUS;
// extern const Real OSOYOO_IR_SENSORS_RING_RANGE;

const Real OSOYOO_LIDAR_CENTER_ELEVATION   = -0.03;  // Lidar hight is considered in the robot height
                                                         // Hence, negative value
const Real OSOYOO_LIDAR_ELEVATION          = OSOYOO_BASE_TOP + OSOYOO_LIDAR_CENTER_ELEVATION;
const Real OSOYOO_LIDAR_SENSORS_FAN_RADIUS = OSOYOO_BASE_RADIUS;
const CRadians OSOYOO_LIDAR_ANGLE_SPAN(ToRadians(CDegrees(360.0)));
const CRange<Real> OSOYOO_LIDAR_SENSORS_RING_RANGE(0.150, 12.00);

const Real OSOYOO_MAX_FORCE           = 2.0f; // Are these the right values?
const Real OSOYOO_MAX_TORQUE          = 2.0f;

const CRadians OSOYOO_LED_RING_START_ANGLE   = CRadians((ARGOS_PI / 8.0f) * 0.5f);
const Real OSOYOO_LED_RING_RADIUS            = OSOYOO_BASE_RADIUS + 0.007;
const Real OSOYOO_LED_RING_ELEVATION         = 0.086f;
const Real OSOYOO_RAB_ELEVATION              = OSOYOO_LED_RING_ELEVATION;

const Real OSOYOO_IR_SENSOR_RING_ELEVATION       = 0.06f; // is this correct?
const Real OSOYOO_IR_SENSOR_RING_RADIUS          = OSOYOO_BASE_RADIUS;
const CRadians OSOYOO_IR_SENSOR_RING_START_ANGLE = CRadians((2 * ARGOS_PI / 8.0f) * 0.5f);
const Real OSOYOO_IR_SENSOR_RING_RANGE           = 0.1f;
const Real OSOYOO_ULTRASONIC_RANGE = 0.3f;

const Real OMNIDIRECTIONAL_CAMERA_ELEVATION = 0.288699733f;

// Readings from here:
// https://emanual.robotis.com/docs/en/platform/osoyoo/appendix_lds_01/

/****************************************/
/****************************************/
