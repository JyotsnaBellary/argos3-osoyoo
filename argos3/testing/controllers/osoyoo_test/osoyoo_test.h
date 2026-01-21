/*
 * AUTHOR: Jyotsna Bellary <jyotsna.bellary@uni-konstanz.de>
 *
 * A test controller for testing the working of all newly added sensors to new osoyoo.
 *
 * The controller uses the proximity sensor to detect obstacles and the
 * wheels to move the robot around.
 *
 * The controller uses the light sensors to detect light sources.
 * 
 * This controller is meant to be used with the XML files:
 *    experiments/osoyoo_test.argos
 */

#ifndef OSOYOO_TEST_H
#define OSOYOO_TEST_H

/*
 * Include some necessary headers.
 */
/* Definition of the CCI_Controller class. */
#include <argos3/core/control_interface/ci_controller.h>
/* Definition of the differential steering actuator */
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
/* Definition of proximity sensor */
// #include <argos3/plugins/robots/generic/control_interface/ci_proximity_sensor.h>
// #include <argos3/plugins/robots/osoyoo/control_interface/ci_osoyoo_light_sensor.h>
#include <argos3/plugins/robots/osoyoo/control_interface/ci_osoyoo_proximity_sensor.h>
#include <argos3/plugins/robots/osoyoo/control_interface/ci_osoyoo_ultrasonic_sensor.h>
// #include <argos3/plugins/robots/osoyoo/control_interface/ci_osoyoo_base_ground_sensor.h>
// #include <argos3/plugins/robots/osoyoo/control_interface/ci_osoyoo_lidar_sensor.h>
// #include <argos3/plugins/robots/osoyoo/control_interface/ci_osoyoo_colored_blob_omnidirectional_camera_sensor.h>
// #include <argos3/plugins/robots/osoyoo/simulator/osoyoo_colored_blob_perspective_camera_default_sensor.h>
#include <argos3/plugins/robots/osoyoo/control_interface/ci_osoyoo_imu_sensor.h>
#include <argos3/plugins/robots/generic/control_interface/ci_leds_actuator.h>

/*
 * All the ARGoS stuff in the 'argos' namespace.
 * With this statement, you save typing argos:: every time.
 */
using namespace argos;

/*
 * A controller is simply an implementation of the CCI_Controller class.
 */
class COsoyooTest : public CCI_Controller {

public:

   /* Class constructor. */
   COsoyooTest();

   /* Class destructor. */
   virtual ~COsoyooTest() {}

   /*
    * This function initializes the controller.
    * The 't_node' variable points to the <parameters> section in the XML
    * file in the <controllers><osoyoo_test_controller> section.
    */
   virtual void Init(TConfigurationNode& t_node);

   /*
    * This function is called once every time step.
    * The length of the time step is set in the XML file.
    */
   virtual void ControlStep();

   /*
   * This function logs the light sensor readings to the console.
   */
   void LogLightReadings() const;

   /*
   * This function logs the light sensor readings to the console.
   */
   void LogGroundSensorReadings() const;

   /*
   * This function logs the lidar sensor readings to the console.
   */
   void LogLidarSensorReadings() const;

   /*
   * This function logs the color of the light using Camera sensor to the console.
   */
   void LogLightUsingCameraSensorReadings() const;

   /*
    * Calculates the vector to the closest light.
    */
   // virtual CVector2 VectorToLight();

   /*
   * This function avoids obstacles using the proximity sensors.
   */
   void AvoidObstaclesWithProximitySensors();

   /*
    * This function tests the IMU sensor.
    */
   void TestIMUSensor();

   /*
   * This function tests the ultrasonic sensor.
   */
   void TestUltrasonicSensor();
   
   /*
    * This function resets the controller to its state right after the
    * Init().
    * It is called when you press the reset button in the GUI.
    * In this example controller there is no need for resetting anything,
    * so the function could have been omitted. It's here just for
    * completeness.
    */
   virtual void Reset();

   /*
    * Called to cleanup what done by Init() when the experiment finishes.
    * In this example controller there is no need for clean anything up,
    * so the function could have been omitted. It's here just for
    * completeness.
    */
   virtual void Destroy() {}

private:

   /* Pointer to the differential steering actuator */
   CCI_DifferentialSteeringActuator* m_pcWheels;

   /* Pointer to the osoyoo proximity sensor */
   CCI_OsoyooProximitySensor* m_pcProximity;

   /* Pointer to the osoyoo ultrasonic sensor */
   CCI_OsoyooUltrasonicSensor* m_pcUltrasonic;

   /* Pointer to the osoyoo base ground sensor */
   // CCI_OsoyooBaseGroundSensor* m_pcGround;

   /* Pointer to the new osoyoo light sensor*/
   // CCI_OsoyooLightSensor* m_pcLight;

   /* Pointer to the new osoyoo Lidar sensor*/
   // CCI_OsoyooLIDARSensor* m_pcLidar;

   // CCI_LEDsActuator* m_pcLEDs;

   /*
    * The following variables are used as parameters for the
    * algorithm. You can set their value in the <parameters> section
    * of the XML configuration file, under the
    * <controllers><osoyoo_test_controller> section.
    */
   /* Wheel speed. */
   Real m_fWheelVelocity;

   /* Pointer to the omnidirectional camera sensor */
   // CCI_OsoyooColoredBlobOmnidirectionalCameraSensor* m_pcCamera;

   /* Pointer to the new IMU sensor */
   CCI_OSOYOOIMUSensor* m_pcIMU;

   // CCI_ColoredBlobPerspectiveCameraSensor* m_pcCamera;
   // CCI_LEDsActuator* m_pcLedAct;


};

#endif
