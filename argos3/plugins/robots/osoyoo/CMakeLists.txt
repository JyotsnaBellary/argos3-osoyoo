#Set all if conditions later.

#
# Osoyoo headers
#
set(ARGOS3_HEADERS_PLUGINS_ROBOTS_OSOYOO_CONTROLINTERFACE
  # control_interface/ci_osoyoo_base_ground_sensor.h
  # control_interface/ci_osoyoo_lidar_sensor.h
  control_interface/ci_osoyoo_proximity_sensor.h
  control_interface/ci_osoyoo_ultrasonic_sensor.h
  # control_interface/ci_osoyoo_colored_blob_omnidirectional_camera_sensor.h
  control_interface/ci_osoyoo_imu_sensor.h
)
set(ARGOS3_HEADERS_PLUGINS_ROBOTS_OSOYOO_SIMULATOR
    simulator/dynamics2d_osoyoo_model.h
    simulator/dynamics3d_osoyoo_model.h
    # simulator/osoyoo_base_ground_rotzonly_sensor.h
    # simulator/osoyoo_lidar_default_sensor.h
    simulator/osoyoo_proximity_default_sensor.h
    simulator/osoyoo_ultrasonic_default_sensor.h
    # simulator/osoyoo_colored_blob_omnidirectional_camera_rotzonly_sensor.h
    simulator/osoyoo_imu_equipped_entity.h
    simulator/osoyoo_imu_sensor.h
    simulator/osoyoo_entity.h
    simulator/osoyoo_measures.h

    )
    
#
# Osoyoo sources
#
set(ARGOS3_SOURCES_PLUGINS_ROBOTS_OSOYOO
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_OSOYOO_CONTROLINTERFACE}
  # control_interface/ci_osoyoo_base_ground_sensor.cpp
  # control_interface/ci_osoyoo_lidar_sensor.cpp
  control_interface/ci_osoyoo_proximity_sensor.cpp
  control_interface/ci_osoyoo_ultrasonic_sensor.cpp
  # control_interface/ci_osoyoo_colored_blob_omnidirectional_camera_sensor.cpp
  control_interface/ci_osoyoo_imu_sensor.cpp
)

set(ARGOS3_SOURCES_PLUGINS_ROBOTS_OSOYOO
  ${ARGOS3_SOURCES_PLUGINS_ROBOTS_OSOYOO}
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_OSOYOO_SIMULATOR}
  simulator/dynamics2d_osoyoo_model.cpp
  simulator/dynamics3d_osoyoo_model.cpp
  # simulator/osoyoo_base_ground_rotzonly_sensor.cpp
  # simulator/osoyoo_lidar_default_sensor.cpp
  simulator/osoyoo_proximity_default_sensor.cpp
  simulator/osoyoo_ultrasonic_default_sensor.cpp
  # simulator/osoyoo_colored_blob_omnidirectional_camera_rotzonly_sensor.cpp
  simulator/osoyoo_imu_equipped_entity.cpp
  simulator/osoyoo_imu_sensor.cpp
  simulator/osoyoo_entity.cpp
  simulator/osoyoo_measures.cpp
)

#
# For compiling graphical visualizations
#
set(ARGOS3_HEADERS_PLUGINS_ROBOTS_OSOYOO_SIMULATOR
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_OSOYOO_SIMULATOR}
  simulator/qtopengl_osoyoo.h)

set(ARGOS3_SOURCES_PLUGINS_ROBOTS_OSOYOO
  ${ARGOS3_SOURCES_PLUGINS_ROBOTS_OSOYOO}
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_OSOYOO_SIMULATOR}
  # simulator/qtopengl_osoyoo.h
  simulator/qtopengl_osoyoo.cpp)

#
# Create Osoyoo plugin
#
add_library(argos3plugin_simulator_osoyoo SHARED ${ARGOS3_SOURCES_PLUGINS_ROBOTS_OSOYOO})

target_link_libraries(argos3plugin_simulator_osoyoo
    argos3core_simulator
    argos3plugin_simulator_dynamics2d
    argos3plugin_simulator_dynamics3d
    argos3plugin_simulator_entities
    argos3plugin_simulator_genericrobot
    argos3plugin_simulator_media)
if(ARGOS_COMPILE_QTOPENGL)
  target_link_libraries(argos3plugin_simulator_osoyoo
    argos3plugin_simulator_qtopengl
    ${QT_LIBRARIES} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})
endif(ARGOS_COMPILE_QTOPENGL)


#
# Add plugin to ARGOS_PLUGIN_PATH
#
set(ARGOS_PLUGIN_PATH "${ARGOS_PLUGIN_PATH}:${CMAKE_CURRENT_BINARY_DIR}" CACHE INTERNAL "ARGoS plugin path")

install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_OSOYOO_CONTROLINTERFACE} DESTINATION include/argos3/plugins/robots/osoyoo/control_interface)
install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_OSOYOO_SIMULATOR} DESTINATION include/argos3/plugins/robots/osoyoo/simulator)
install(DIRECTORY simulator/models DESTINATION include/argos3/plugins/simulator/visualizations/qt-opengl)
install(FILES simulator/osoyoo_texture_bottom.png simulator/osoyoo_texture_side.png simulator/osoyoo_texture_top.png DESTINATION include/argos3/plugins/simulator/visualizations/qt-opengl/textures)

install(TARGETS argos3plugin_simulator_osoyoo
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos3
  ARCHIVE DESTINATION lib/argos3)