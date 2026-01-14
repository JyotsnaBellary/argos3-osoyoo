/**
 * @file <argos3/plugins/robots/osoyoo/simulator/osoyoo_imu_sensor.h>
 *
 */

#ifndef OSOYOO_IMU_SENSOR_H
#define OSOYOO_IMU_SENSOR_H

namespace argos
{
    class COSOYOOIMUSensor;
    class COSOYOOIMUEquippedEntity;
}

#include "../control_interface/ci_osoyoo_imu_sensor.h"
#include <argos3/core/utility/math/range.h>
#include <argos3/core/utility/math/rng.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/sensor.h>

namespace argos
{

    class COSOYOOIMUSensor : public CSimulatedSensor,
                          public CCI_OSOYOOIMUSensor
    {

    public:
        COSOYOOIMUSensor();

        virtual ~COSOYOOIMUSensor() {}

        virtual void SetRobot(CComposableEntity &c_entity);
        virtual void Init(TConfigurationNode &t_tree);
        virtual void Update();
        virtual void Reset();

    private:
        /** Reference to quaternion sensor equipped entity associated to this sensor */
        //COSOYOOIMUEquippedEntity *m_pcImuEntity;

        /** Whether to add noise or not */
        bool m_bAddNoise;

        /** Random number generator */
        CRandom::CRNG *m_pcRNG;

        /** Noise range */
        CRange<Real> m_cNoiseRange;

        /** Reference to the embodied entity */
        CEmbodiedEntity *m_pcEmbodiedEntity;

        /** Reference to the IMU equipped entity */
        COSOYOOIMUEquippedEntity *m_pcImuEntity;
    };

}

#endif