/**
 * @file <osoyoo/simulator/qtopengl_osoyoo.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef QTOPENGL_OSOYOO_H
#define QTOPENGL_OSOYOO_H

namespace argos {
   class CQTOpenGLOsoyoo;
   class COsoyooEntity;
}

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

namespace argos {

   class CQTOpenGLOsoyoo {

   public:

      CQTOpenGLOsoyoo();

      virtual ~CQTOpenGLOsoyoo();

      virtual void Draw(COsoyooEntity& c_entity);

   protected:

      /** Renders a wheel */
      void RenderWheel();

      /** Renders the body */
      void RenderBody();

      /** Set Base Material */ 
      void SetBaseMaterial();

      /** Set Wheel Material */
      void SetWheelMaterial(); 

      void SetWhitePlasticMaterial();
   private:

      /** Start of the display list index */
      GLuint m_unLists;

      /** Osoyoo wheel */
      GLuint m_unWheelList;

      /** Body display list */
      GLuint m_unBodyList;

      /** Upper body list */
      GLuint m_unUpperBodyList;

      /** Column list */
      GLuint m_unColumnList;

      /** Number of vertices to display the round parts */
      GLuint m_unVertices;

      /** Osoyoo camera module */
      GLuint m_unCameraList;
   };

}

#endif
