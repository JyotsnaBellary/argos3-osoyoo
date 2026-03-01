# ARGoS3 Osoyoo 
This repository contains ARGoS3 plugin for the Osoyoo.

## Prerequisites
- Install ARGoS3 from the official [repository](https://github.com/ilpincy/argos3) so that headers, libraries, and the `argos3` executable are present on your system.
- Optional (but recommended): skim through the [developer manual](https://www.argos-sim.info/dev_manual.php) to understand how ARGoS3 expects plugins to be structured.

## Build and Install
Clone this repository and navigate to the root directory:

### Clone the repository
```bash
git clone https://github.com/CPS-Konstanz/argos3-osoyoo.git
cd ~/argos3-osoyoo
```

### Install the plugin
To install the plugin, you can use the helper script or run the commands manually.

- Helper script:
  ```bash
  # configures and builds in ./build (Debug by default)
  ./build.sh           

  # same as above plus sudo make install
  ./build.sh install   
  ```

- Manual steps:

  ```bash
  mkdir -p build && cd build
  cmake -DCMAKE_BUILD_TYPE=Debug ..
  make -j$(nproc)

  # to install libraries/headers into your ARGoS3 prefix
  sudo make install    
  ```

If you prefer running without `sudo make install`, set `ARGOS_PLUGIN_PATH` to `<repo>/build/argos3/plugins/robots/<plugin>` before launching `argos3` so it can find the shared libraries.
```bash
export EXAMPLEDIR=../argos3_plugins/new_robots
export ARGOS_PLUGIN_PATH=$EXAMPLEDIR/build/newepuck
```

## Repository Layout
- `argos3/plugins/robots/Osoyoo`: implementation of the Osoyoo plugin 
- `argos3/testing`: folder contain an example controller, experiment and loop function to test the plugin.
- `build.sh`: convenience script for rebuilding and optionally installing.

## Sensors 

### Ultrasonic Sensor
Simulates a single forward-facing ultrasonic range sensor. The sensor emits one beam and measures the distance to an obstacle along that way. 

- **Type:** Single-beam range sensor (raycast based)
- **Sensor Position(angle from robot front, positive angles = left side sensors):** [0] -3°
- **Range:** 0 - 0.3 m
- **Response function:** Identity (returns raw measured distance to an object in meters)
- **Mounting height:** 0.02 m

### Encoder Sensor 
Simulates wheel encoders for the differential-drive Osoyoo robot by integrating the wheel velocities over each simulation timstep.

- **Type:** Incremental wheel displacement sensor
- **Reading:** Distance covered by each wheel since the last control step
- **Units:** meters (m)
- **Geometry:** Weel radius (0.0325), Inter-wheel distance (0.12)

### IMU Sensor 
simulates an Inertial Measurement Unit (IMU) that provides the robot's orientation as Euler angles. 
- **Reading:**
  - `pitch` – rotation around the x-axis (radians)
  - `roll` – rotation around the y-axis (radians)
  - `yaw` – rotation around the z-axis (radians)
- **Units:** radians
- **Optional noise:** `noise_level` XML attribute (additive uniform noise)

## Actuators 
The robot is implemented as a differential drive robot, the example controller provided (see example) shows how to convert the linear and angular velocity commands into left and right wheel velocities.


## Run the Sample Experiment
The `testing` folder contains a simple obstacle-avoidance experiment using the osoyoo plugin. Obstacle avoidance is based only on the proximity sensors.
To run the experiments:

```bash
argos3 -c argos3/testing/experiments/Osoyoo_test.argos
```

## References
- [ARGoS](https://www.argos-sim.info/) — the multi-robot simulator this plugin is built on.