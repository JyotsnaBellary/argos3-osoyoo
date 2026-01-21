/**
 * @file <osoyoo/simulator/osoyoo_entity.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef OSOYOO_ENTITY_H
#define OSOYOO_ENTITY_H

namespace argos {
   class CControllableEntity;
   class CEmbodiedEntity;
   class COsoyooEntity;
   class COSOYOOIMUEquippedEntity;
   class CProximitySensorEquippedEntity; 
}

#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/plugins/simulator/entities/wheeled_entity.h>
#include <argos3/plugins/simulator/entities/perspective_camera_equipped_entity.h>
#include <argos3/plugins/robots/osoyoo/simulator/osoyoo_imu_equipped_entity.h>

namespace argos {

   class COsoyooEntity : public CComposableEntity {

   public:

      ENABLE_VTABLE();

   public:

      COsoyooEntity();

      COsoyooEntity(const std::string& str_id,
                   const std::string& str_controller_id,
                   const CVector3& c_position = CVector3(),
                   const CQuaternion& c_orientation = CQuaternion(),
                   Real f_rab_range = 0.8f,
                   size_t un_rab_data_size = 2,
                   const std::string& str_bat_model = "",
                   const CRadians& c_omnicam_aperture = ToRadians(CDegrees(70.0f)),
                     bool b_perspcam_front = true,
                   const CRadians& c_perspcam_aperture = ToRadians(CDegrees(33.75f)),
                   Real f_perspcam_focal_length = 0.035f,
                   Real f_perspcam_range = 3.0f
                  );
      
      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset();
      virtual void Destroy();

      virtual void UpdateComponents();
      
      inline CControllableEntity& GetControllableEntity() {
         return *m_pcControllableEntity;
      }

      inline CEmbodiedEntity& GetEmbodiedEntity() {
         return *m_pcEmbodiedEntity;
      }

      inline CProximitySensorEquippedEntity& GetUltrasonicSensorEquippedEntity() {
         return *m_pcUltrasonicSensorEquippedEntity;
      }

      inline CProximitySensorEquippedEntity& GetProximitySensorEquippedEntity() {
         return *m_pcProximitySensorEquippedEntity;
      }

      inline COSOYOOIMUEquippedEntity& GetIMUEquippedEntity() {
         return *m_pcIMUEquippedEntity;
      }

      inline CWheeledEntity& GetWheeledEntity() {
         return *m_pcWheeledEntity;
      }

      virtual std::string GetTypeDescription() const {
         return "osoyoo";
      }

   private:

      void SetLEDPosition();

   private:

      CControllableEntity*                   m_pcControllableEntity;
      CEmbodiedEntity*                       m_pcEmbodiedEntity;
      CProximitySensorEquippedEntity*        m_pcProximitySensorEquippedEntity;
      CProximitySensorEquippedEntity*        m_pcUltrasonicSensorEquippedEntity;
      CWheeledEntity*                        m_pcWheeledEntity;
      COSOYOOIMUEquippedEntity*              m_pcIMUEquippedEntity;
   };

}

#endif
