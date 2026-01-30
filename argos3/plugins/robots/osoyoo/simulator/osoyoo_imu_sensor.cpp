#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include "osoyoo_imu_equipped_entity.h"

#include "osoyoo_imu_sensor.h"

namespace argos
{

    /****************************************/
    /****************************************/

    /****************************************/
    /****************************************/

    COSOYOOIMUSensor::COSOYOOIMUSensor() : m_bAddNoise(false), m_pcRNG(NULL)
    {
    }

    /****************************************/
    /****************************************/

    void COSOYOOIMUSensor::Init(TConfigurationNode &t_tree)
    {
        CCI_OSOYOOIMUSensor::Init(t_tree);
        Real fNoiseLevel = 0.0f;
        GetNodeAttributeOrDefault(t_tree, "noise_level", fNoiseLevel, fNoiseLevel);
        if (fNoiseLevel < 0.0f)
        {
            THROW_ARGOSEXCEPTION("Can't specify a negative value for the noise level"
                                 << " of the osoyoo IMU sensor");
        }
        else if (fNoiseLevel > 0.0f)
        {
            m_bAddNoise = true;
            m_cNoiseRange.Set(-fNoiseLevel, fNoiseLevel);
            m_pcRNG = CRandom::CreateRNG("argos");
        }
    }

    /****************************************/
    /****************************************/

    void COSOYOOIMUSensor::SetRobot(CComposableEntity &c_entity)
    {
        try
        {
            //m_pcImuEntity = &(c_entity.GetComponent<COSOYOOIMUEquippedEntity>("osoyoo_imu"));
            // m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
            m_pcImuEntity =
   &(c_entity.GetComponent<COSOYOOIMUEquippedEntity>("osoyoo_imu[imu]"));
m_pcImuEntity->Enable();


        //         m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
        // //  m_pcControllableEntity = &(c_entity.GetComponent<CControllableEntity>("controller"));
        //  m_pcImuEntity = &(c_entity.GetComponent<COSOYOOIMUEquippedEntity>("imu"));
        //  m_pcImuEntity->Enable();
        }
        catch (CARGoSException &ex)
        {
            THROW_ARGOSEXCEPTION_NESTED("Can't set robot for the osoyoo imu sensor", ex);
        }
    }

    /****************************************/
    /****************************************/

    void COSOYOOIMUSensor::Update()
    {
        // CRadians cOrientationX, cOrientationY, cOrientationZ;
        // m_pcEmbodiedEntity->GetOriginAnchor().Orientation.ToEulerAngles(cOrientationZ, cOrientationY, cOrientationX);
        // m_sReading.Pitch = cOrientationX;
        // m_sReading.Roll = cOrientationY;
        // m_sReading.Yaw = cOrientationZ;
        // if (m_bAddNoise)
        // {
        //     m_sReading.Pitch += CRadians(m_pcRNG->Uniform(m_cNoiseRange));
        //     m_sReading.Roll += CRadians(m_pcRNG->Uniform(m_cNoiseRange));
        //     m_sReading.Yaw += CRadians(m_pcRNG->Uniform(m_cNoiseRange));
        // }
        m_sReading.Pitch = m_pcImuEntity->GetPitch();
    m_sReading.Roll  = m_pcImuEntity->GetRoll();
    m_sReading.Yaw   = m_pcImuEntity->GetYaw();

    if (m_bAddNoise) {
        m_sReading.Pitch += CRadians(m_pcRNG->Uniform(m_cNoiseRange));
        m_sReading.Roll  += CRadians(m_pcRNG->Uniform(m_cNoiseRange));
        m_sReading.Yaw   += CRadians(m_pcRNG->Uniform(m_cNoiseRange));
    }
    }

    /****************************************/
    /****************************************/

    void COSOYOOIMUSensor::Reset()
    {
    }

    /****************************************/
    /****************************************/

    /****************************************/
    /****************************************/

    REGISTER_SENSOR(COSOYOOIMUSensor,
                    "osoyoo_imu", "default",
                    "Raffaele Todesco   [raffaele.todesco@ulb.be]",
                    "1.0",
                    "The osoyoo IMU sensor",
                    "The sensor returns the pitch, roll and yaw of the robot\n"
                    "that represents the rotation of the robot.\n"
                    "For usage, refer to [ci_osoyoo_imu_sensor.h]\n\n"
                    "REQUIRED XML CONFIGURATION\n\n"
                    "   <controllers>\n"
                    "      ...\n"
                    "      <my_controller>\n"
                    "         ...\n"
                    "         <sensors>\n"
                    "            ...\n"
                    "            <osoyoo_imu implementation=\"default\"/>\n"
                    "            ...\n"
                    "         <sensors/>\n"
                    "         ...\n"
                    "      <my_controller/>\n"
                    "      ...\n"
                    "   <controllers>\n\n",
                    "Usable");
}
