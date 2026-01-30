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
const Real OSOYOO_MASS = 0.08f;
const Real OSOYOO_LENGTH = 0.19f;//Yet to confirm
const Real OSOYOO_WIDTH = 0.145; // // yet to confirm
const Real OSOYOO_BASE_ELEVATION = 0.02f;
const Real OSOYOO_HEIGHT    = 0.05;
const Real OSOYOO_BASE_TOP = OSOYOO_BASE_ELEVATION + OSOYOO_HEIGHT;


const Real OSOYOO_WHEEL_RADIUS        = 0.0325; //important
const Real OSOYOO_INTERWHEEL_DISTANCE      = 0.12;
const Real OSOYOO_HALF_INTERWHEEL_DISTANCE = OSOYOO_INTERWHEEL_DISTANCE * 0.5;

/* Visual-only wheel thickness (does NOT belong in measures) */
const Real OSOYOO_WHEEL_WIDTH = 0.02f;      // 2 cm, looks reasonable
const Real OSOYOO_HALF_WHEEL_WIDTH = OSOYOO_WHEEL_WIDTH * 0.5f;

// Wheel position along the length (negative = towards the back)
const Real OSOYOO_WHEEL_OFFSET_X = -0.03f;  // 3 cm behind center
const Real OSOYOO_WHEEL_OFFSET_Y = OSOYOO_HALF_INTERWHEEL_DISTANCE; // = 0.06

const Real OSOYOO_HALF_LENGTH = OSOYOO_LENGTH * 0.5f;
const Real OSOYOO_HALF_WIDTH  = OSOYOO_WIDTH  * 0.5f;

/* Radius of smallest circle that encloses the rectangle */
const Real OSOYOO_FOOTPRINT_RADIUS =
   Sqrt(OSOYOO_HALF_LENGTH * OSOYOO_HALF_LENGTH +
        OSOYOO_HALF_WIDTH  * OSOYOO_HALF_WIDTH);

 const Real OSOYOO_MAX_FORCE           = 2.0f; // Are these the right values?
 const Real OSOYOO_MAX_TORQUE          = 2.0f;

const Real OSOYOO_IR_SENSOR_RING_ELEVATION       = OSOYOO_BASE_ELEVATION; // is this correct?
const Real OSOYOO_IR_SENSOR_RING_RANGE           = 0.1f;
const Real OSOYOO_ULTRASONIC_RANGE = 0.3f;

// Readings from here:
// https://emanual.robotis.com/docs/en/platform/osoyoo/appendix_lds_01/

/****************************************/
/****************************************/
