/**
 * @file <argos3/plugins/robots/osoyoo/simulator/osoyoo_base_ground_rotzonly_sensor.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/floor_entity.h>
#include <argos3/plugins/simulator/entities/ground_sensor_equipped_entity.h>

#include "osoyoo_base_ground_rotzonly_sensor.h"
using namespace std;
namespace argos {

   /****************************************/
   /****************************************/

   static CRange<Real> UNIT(0.0f, 1.0f);

   /****************************************/
   /****************************************/
   COsoyooBaseGroundRotZOnlySensor::COsoyooBaseGroundRotZOnlySensor() :
      m_pcEmbodiedEntity(nullptr),
      m_pcFloorEntity(nullptr),
      m_pcGroundSensorEntity(nullptr),
      m_pcRNG(nullptr),
      m_bAddNoise(false),
      m_cSpace(CSimulator::GetInstance().GetSpace()) {}

   /****************************************/
   /****************************************/

   void COsoyooBaseGroundRotZOnlySensor::SetRobot(CComposableEntity& c_entity) {
      m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
      m_pcGroundSensorEntity = &(c_entity.GetComponent<CGroundSensorEquippedEntity>("ground_sensors"));
      m_pcGroundSensorEntity->Enable();
      m_pcFloorEntity = &m_cSpace.GetFloorEntity();
   }

   /****************************************/
   /****************************************/

   void COsoyooBaseGroundRotZOnlySensor::Init(TConfigurationNode& t_tree) {
      try {
         CCI_OsoyooBaseGroundSensor::Init(t_tree);
         /* Parse noise level */
         Real fNoiseLevel = 0.0f;
         GetNodeAttributeOrDefault(t_tree, "noise_level", fNoiseLevel, fNoiseLevel);
         if(fNoiseLevel < 0.0f) {
            THROW_ARGOSEXCEPTION("Can't specify a negative value for the noise level of the osoyoo ground sensor");
         }
         else if(fNoiseLevel > 0.0f) {
            m_bAddNoise = true;
            m_cNoiseRange.Set(-fNoiseLevel, fNoiseLevel);
            m_pcRNG = CRandom::CreateRNG("argos");
         }
         m_tReadings.resize(4);
         /* sensor is enabled by default */
         Enable();
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in osoyoo rotzonly ground sensor", ex);
      }
   }

   /****************************************/
   /****************************************/

   void COsoyooBaseGroundRotZOnlySensor::Update() {
      /* sensor is disabled--nothing to do */
      if (IsDisabled()) {
        return;
      }
      /*
       * We make the assumption that the robot is rotated only wrt to Z
       */
      /* Get robot position and orientation */
      const CVector3& cEntityPos = m_pcEmbodiedEntity->GetOriginAnchor().Position;
      const CQuaternion& cEntityRot = m_pcEmbodiedEntity->GetOriginAnchor().Orientation;
      CRadians cRotZ, cRotY, cRotX;
      cEntityRot.ToEulerAngles(cRotZ, cRotY, cRotX);
      /* Set robot center */
      CVector2 cCenterPos(cEntityPos.GetX(), cEntityPos.GetY());
      /* Position of sensor on the ground after rototranslation */
      CVector2 cSensorPos;
      /* Go through the sensors */
      for(UInt32 i = 0; i < m_tReadings.size(); ++i) {
         /* Calculate sensor position on the ground */
         cSensorPos = m_pcGroundSensorEntity->GetSensor(i).Offset;
         cSensorPos.Rotate(cRotZ);
         cSensorPos += cCenterPos;
         /* Get the color */
         const CColor& cColor = m_pcFloorEntity->GetColorAtPoint(cSensorPos.GetX(),
                                                                 cSensorPos.GetY());
         /* Set the reading */
         m_tReadings[i].Value = cColor.ToGrayScale() / 255.0f;
         /* Apply noise to the sensor */
         if(m_bAddNoise) {
            m_tReadings[i].Value += m_pcRNG->Uniform(m_cNoiseRange);
         }
         /* Set the final reading */
         m_tReadings[i].Value = m_tReadings[i].Value < 0.5f ? 0.0f : 1.0f;
      }
   }

   /****************************************/
   /****************************************/

   void COsoyooBaseGroundRotZOnlySensor::Reset() {
      for(UInt32 i = 0; i < GetReadings().size(); ++i) {
         m_tReadings[i].Value = 0.0f;
      }
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(COsoyooBaseGroundRotZOnlySensor,
                   "osoyoo_ground", "rot_z_only",
                   "Carlo Pinciroli [ilpincy@gmail.com]",
                   "1.0",
                   "The osoyoo base ground sensor.",
                   "This sensor accesses the osoyoo base ground sensor. For a complete description\n"
                   "of its usage, refer to the ci_osoyoo_base_ground_sensor.h interface. For the XML\n"
                   "configuration, refer to the default ground sensor.\n",
                   "Usable"
		  );

}
