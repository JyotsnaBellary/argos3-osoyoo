add_library(osoyoo_shared_test STATIC osoyoo_test.h osoyoo_test.cpp)
add_library(osoyoo_test MODULE osoyoo_test.h osoyoo_test.cpp)
target_link_libraries(osoyoo_test
  argos3core_simulator
  argos3plugin_simulator_osoyoo
  argos3plugin_simulator_genericrobot)
