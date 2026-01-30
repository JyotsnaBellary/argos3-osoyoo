/**
 * @file <osoyoo/simulator/qtopengl_osoyoo.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "qtopengl_osoyoo.h"
#include "osoyoo_entity.h"
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/plugins/simulator/entities/led_equipped_entity.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_widget.h>
#include <argos3/plugins/robots/osoyoo/simulator/osoyoo_measures.h>

namespace argos
{

   /****************************************/
   /****************************************/

   CQTOpenGLOsoyoo::CQTOpenGLOsoyoo() : m_unVertices(40)
   {
      /* Reserve the needed display lists */
      m_unLists = glGenLists(2);

      /* Assign indices for better referencing (later) */
      m_unWheelList = m_unLists;
      m_unBodyList = m_unLists + 1;

      /* Create the wheel display list */
      glNewList(m_unWheelList, GL_COMPILE);
      RenderWheel();
      glEndList();

      /* Create the body display list */
      glNewList(m_unBodyList, GL_COMPILE);
      RenderBody();
      glEndList();
   }

   /****************************************/
   /****************************************/

   CQTOpenGLOsoyoo::~CQTOpenGLOsoyoo()
   {
      glDeleteLists(m_unLists, 5);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLOsoyoo::Draw(COsoyooEntity &c_entity)
   {
      /* Place the body */
      glCallList(m_unBodyList);

      /* Place the wheels */
      /* Left wheel */
glPushMatrix();
glTranslated(OSOYOO_WHEEL_OFFSET_X, +OSOYOO_HALF_INTERWHEEL_DISTANCE, 0.0f);
glCallList(m_unWheelList);
glPopMatrix();

/* Right wheel */
glPushMatrix();
glTranslated(OSOYOO_WHEEL_OFFSET_X, -OSOYOO_HALF_INTERWHEEL_DISTANCE, 0.0f);
glCallList(m_unWheelList);
glPopMatrix();

   }

   /* Dark plastic (Lower body) */
   void CQTOpenGLOsoyoo::SetBaseMaterial()
   {
      const GLfloat ambient_diffuse[] = {0.15f, 0.15f, 0.15f, 1.0f}; // dark gray
      const GLfloat specular[] = {0.05f, 0.05f, 0.05f, 1.0f};
      const GLfloat shininess[] = {5.0f};
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambient_diffuse);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
   }
   
   /* Rubber (Wheels) */
   void CQTOpenGLOsoyoo::SetWheelMaterial()
   {
      const GLfloat ambient_diffuse[] = {0.05f, 0.05f, 0.05f, 1.0f}; // dark rubber
      const GLfloat specular[] = {0.00f, 0.00f, 0.00f, 1.0f};
      const GLfloat shininess[] = {1.0f};
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambient_diffuse);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
   }

   void CQTOpenGLOsoyoo::RenderWheel()
   {
      SetWheelMaterial();
      CRadians cAngleStep = CRadians::TWO_PI / m_unVertices;

      /* Right side */
      CVector2 cVertex(OSOYOO_WHEEL_RADIUS, 0.0f);
      CRadians cAngle(CRadians::TWO_PI / m_unVertices);
      CVector3 cNormal(-1.0f, -1.0f, 0.0f);
      cNormal.Normalize();
      glBegin(GL_POLYGON);
      for (GLuint i = 0; i <= m_unVertices; i++)
      {
         glNormal3d(cNormal.GetX(), cNormal.GetY(), cNormal.GetZ());
         glVertex3d(cVertex.GetX(), -OSOYOO_HALF_WHEEL_WIDTH, OSOYOO_WHEEL_RADIUS + cVertex.GetY());
         cVertex.Rotate(cAngle);
         cNormal.RotateY(cAngle);
      }
      glEnd();
      /* Left side */
      cVertex.Set(OSOYOO_WHEEL_RADIUS, 0.0f);
      cNormal.Set(-1.0f, 1.0f, 0.0f);
      cNormal.Normalize();
      cAngle = -cAngle;
      glBegin(GL_POLYGON);
      for (GLuint i = 0; i <= m_unVertices; i++)
      {
         glNormal3d(cNormal.GetX(), cNormal.GetY(), cNormal.GetZ());
         glVertex3d(cVertex.GetX(), OSOYOO_HALF_WHEEL_WIDTH, OSOYOO_WHEEL_RADIUS + cVertex.GetY());
         cVertex.Rotate(cAngle);
         cNormal.RotateY(cAngle);
      }
      glEnd();
      /* Tire */
      cNormal.Set(1.0f, 0.0f, 0.0f);
      cVertex.Set(OSOYOO_WHEEL_RADIUS, 0.0f);
      cAngle = -cAngle;
      glBegin(GL_QUAD_STRIP);
      for (GLuint i = 0; i <= m_unVertices; i++)
      {
         glNormal3d(cNormal.GetX(), cNormal.GetY(), cNormal.GetZ());
         glVertex3d(cVertex.GetX(), -OSOYOO_HALF_WHEEL_WIDTH, OSOYOO_WHEEL_RADIUS + cVertex.GetY());
         glVertex3d(cVertex.GetX(), OSOYOO_HALF_WHEEL_WIDTH, OSOYOO_WHEEL_RADIUS + cVertex.GetY());
         cVertex.Rotate(cAngle);
         cNormal.RotateY(cAngle);
      }
      glEnd();
   }

   void CQTOpenGLOsoyoo::RenderBody()
   {

      SetBaseMaterial();
      const Real z0 = OSOYOO_BASE_ELEVATION;
   const Real z1 = OSOYOO_BASE_TOP;

   glBegin(GL_QUADS);

   /* Top */
   glNormal3d(0, 0, 1);
   glVertex3d(+OSOYOO_HALF_LENGTH, +OSOYOO_HALF_WIDTH, z1);
   glVertex3d(+OSOYOO_HALF_LENGTH, -OSOYOO_HALF_WIDTH, z1);
   glVertex3d(-OSOYOO_HALF_LENGTH, -OSOYOO_HALF_WIDTH, z1);
   glVertex3d(-OSOYOO_HALF_LENGTH, +OSOYOO_HALF_WIDTH, z1);

   /* Bottom */
   glNormal3d(0, 0, -1);
   glVertex3d(+OSOYOO_HALF_LENGTH, +OSOYOO_HALF_WIDTH, z0);
   glVertex3d(-OSOYOO_HALF_LENGTH, +OSOYOO_HALF_WIDTH, z0);
   glVertex3d(-OSOYOO_HALF_LENGTH, -OSOYOO_HALF_WIDTH, z0);
   glVertex3d(+OSOYOO_HALF_LENGTH, -OSOYOO_HALF_WIDTH, z0);

   /* Front */
   glNormal3d(1, 0, 0);
   glVertex3d(+OSOYOO_HALF_LENGTH, +OSOYOO_HALF_WIDTH, z0);
   glVertex3d(+OSOYOO_HALF_LENGTH, -OSOYOO_HALF_WIDTH, z0);
   glVertex3d(+OSOYOO_HALF_LENGTH, -OSOYOO_HALF_WIDTH, z1);
   glVertex3d(+OSOYOO_HALF_LENGTH, +OSOYOO_HALF_WIDTH, z1);

   /* Back */
   glNormal3d(-1, 0, 0);
   glVertex3d(-OSOYOO_HALF_LENGTH, +OSOYOO_HALF_WIDTH, z0);
   glVertex3d(-OSOYOO_HALF_LENGTH, +OSOYOO_HALF_WIDTH, z1);
   glVertex3d(-OSOYOO_HALF_LENGTH, -OSOYOO_HALF_WIDTH, z1);
   glVertex3d(-OSOYOO_HALF_LENGTH, -OSOYOO_HALF_WIDTH, z0);

   /* Left */
   glNormal3d(0, 1, 0);
   glVertex3d(+OSOYOO_HALF_LENGTH, +OSOYOO_HALF_WIDTH, z0);
   glVertex3d(+OSOYOO_HALF_LENGTH, +OSOYOO_HALF_WIDTH, z1);
   glVertex3d(-OSOYOO_HALF_LENGTH, +OSOYOO_HALF_WIDTH, z1);
   glVertex3d(-OSOYOO_HALF_LENGTH, +OSOYOO_HALF_WIDTH, z0);

   /* Right */
   glNormal3d(0, -1, 0);
   glVertex3d(+OSOYOO_HALF_LENGTH, -OSOYOO_HALF_WIDTH, z0);
   glVertex3d(-OSOYOO_HALF_LENGTH, -OSOYOO_HALF_WIDTH, z0);
   glVertex3d(-OSOYOO_HALF_LENGTH, -OSOYOO_HALF_WIDTH, z1);
   glVertex3d(+OSOYOO_HALF_LENGTH, -OSOYOO_HALF_WIDTH, z1);

   glEnd();
   }
   
   class CQTOpenGLOperationDrawOsoyooNormal : public CQTOpenGLOperationDrawNormal
   {
   public:
      void ApplyTo(CQTOpenGLWidget &c_visualization,
                   COsoyooEntity &c_entity)
      {
         static CQTOpenGLOsoyoo m_cModel;
         c_visualization.DrawRays(c_entity.GetControllableEntity());
         c_visualization.DrawEntity(c_entity.GetEmbodiedEntity());
         m_cModel.Draw(c_entity);
      }
   };

   class CQTOpenGLOperationDrawOsoyooSelected : public CQTOpenGLOperationDrawSelected
   {
   public:
      void ApplyTo(CQTOpenGLWidget &c_visualization,
                   COsoyooEntity &c_entity)
      {
         c_visualization.DrawBoundingBox(c_entity.GetEmbodiedEntity());
      }
   };

   REGISTER_QTOPENGL_ENTITY_OPERATION(CQTOpenGLOperationDrawNormal, CQTOpenGLOperationDrawOsoyooNormal, COsoyooEntity);

   REGISTER_QTOPENGL_ENTITY_OPERATION(CQTOpenGLOperationDrawSelected, CQTOpenGLOperationDrawOsoyooSelected, COsoyooEntity);
}