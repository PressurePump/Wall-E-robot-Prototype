# DEVLOG — Wall-E Robot Prototype

A development journal documenting the full build process of an 
autonomous obstacle-avoiding robot, from first wiring test to 
finished prototype. This is Phase 1 of a larger project to build 
a compact, intelligent Wall-E desktop robot.

---

## Entry 1 — Project pivot & initial concept
**Date: 6/3/2026

### Background
Originally set out to build an Arduino laser face-tracking turret using a Pixy camera and OpenCV via serial communication. 
During testing, discovered both MG90S servos were continuous rotation 
rather than positional — meaning they spin freely instead of 
moving to a set angle. Rather than replace the servos, pivoted 
the entire concept to a wheeled robot inspired by Wall-E.

### Initial plan
- Use both MG90S continuous rotation servos as rear drive wheels
- Add a 360° caster wheel at the front for balance and steering
- Use HC-SR04 ultrasonic sensor for obstacle detection
- Build toward an autonomous, reactive robot

### Wheel layout

![View Wheel Layout Photo (Rear Drive Wheels, Caster Wheel, and Sensor)](IMG_1363.jpeg)

## Entry 2 — First build & wiring
**Date:** 6/3/2026

### Chassis
Used an AirPod box as the robot chassis — compact, lightweight, 
and just large enough to house all components internally.

### Components mounted inside chassis
- ELEGOO Uno R3 (microcontroller)
- Battery pack (power supply)
- HC-SR04 ultrasonic sensor (mounted front-facing at floor level)

### Top-down view of internals

![View Top-Down Photo of Chassis Internals](IMG_1366.jpeg)

### Wiring setup
Connected both MG90S servos to the Arduino via a breadboard. 
Left servo on pin 5, right servo on pin 6. HC-SR04 trig pin on 
9, echo pin on 10.

![View Breadboard and Servo Wiring Photo](IMG_1367.jpeg)

### Key wiring notes
- Servos are mirrored on the chassis, so forward motion requires 
  opposite write values (left: 125, right: 55)
- Servo value of 90 = stop (neutral for continuous rotation)
- Values above 90 spin one direction, below 90 the other


## Entry 3 — First test (movement + obstacle detection)
**Date:** 6/5/2026

### What was tested
First functional test with just the core components:
- ELEGOO Uno R3
- HC-SR04 ultrasonic sensor
- 2x MG90S servos (no buzzer yet)

### Behavior
Robot moves slowly forward toward a wall. When the sensor 
detects an object within 20cm, it stops immediately. No turning 
or audio logic yet — purely validating movement and detection.

### Results
✅ Both wheels spin correctly in forward direction  
✅ Robot stops cleanly at 20cm from wall  
✅ Serial monitor confirmed accurate distance readings  

### First test video

https://github.com/user-attachments/assets/48666808-96c2-47da-aac3-c13453136b9f

---

## Entry 4 — Final prototype (full feature integration)
**Date:** 6/6/2026

### What was added
Integrated the passive buzzer on pin 3 and wrote full behavior 
logic including startup sound, obstacle handling, stuck detection, 
and alert tone before turning.

### Full behavior breakdown

**On startup:**
Robot plays a 3-note ascending startup tune (1000Hz → 1500Hz → 
2000Hz) to confirm it's powered and ready.

**Moving forward:**
When no obstacle is within 20cm, robot drives forward slowly 
(left servo: 125, right servo: 55). Serial monitor prints live 
distance readings every 100ms.

**Obstacle detected:**
When distance ≤ 20cm, robot stops immediately. A timer starts. 
If the obstacle clears before 3 seconds, the robot resumes 
forward movement and the timer resets.

**Stuck for 3 seconds:**
If the same obstacle persists for 3 full seconds, the robot 
plays a 3-beep alert tune (2000Hz → 1200Hz → 2000Hz) then 
executes a right turn for 3 seconds before resuming.

**Sensor timeout:**
`pulseIn()` is called with a 20,000µs timeout — prevents the 
robot from freezing if no echo is received (open space edge case).

### Code summary

| Function | Purpose |
|---|---|
| `getDistance()` | Triggers HC-SR04, returns distance in cm |
| `moveForwardSlow()` | Drives forward at calibrated slow speed |
| `stopRobot()` | Sets both servos to 90 (neutral/stop) |
| `turnRight()` | Spins left servo faster than right to turn |
| `startupTune()` | 3-note ascending tone on boot |
| `alertTune()` | 3-beep alert before executing a turn |

### Final prototype video

### Final prototype video
[▶️ View Final Prototype Video: Full Run with Buzzer Sounds & Autonomous Navigation](https://github.com/user-attachments/assets/3baf1eca-0ff7-4d83-a28c-641112e59e20)

---

## Lessons learned

- Continuous rotation servos require calibration — value 90 is 
  stop, but the exact stop point can drift slightly per servo 
  and may need fine-tuning
- Mirrored servo mounting means forward motion needs opposite 
  write values on each side
- `pulseIn()` without a timeout will freeze the loop if no echo 
  returns — always set a timeout
- A cardboard chassis works fine for prototyping but has no 
  mounting points — next build needs a proper frame

---

## What's next — Wall-E v2

- [ ] 3D-printed compact chassis
- [ ] LCD display for Wall-E face expressions
- [ ] PIR sensor for motion-triggered reactions
- [ ] Smarter navigation (left/right decision instead of always 
      turning right)
- [ ] YouTube series documenting the full v2 build

---

*This prototype was built as a portfolio and learning project 
during freshman year at George Mason University — Electrical 
Engineering.*
