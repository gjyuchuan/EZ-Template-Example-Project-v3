# 📡 Smart Claw: Using Distance Sensors in VEX V5 Override

## What Do Our Two Distance Sensors Do?
Our V5 Distance Sensors shoot an invisible laser beam and tell the robot **how many millimeters (mm) away** an object is:
* **Empty claw:** Reads a big number (`200+ mm`, or `9999` when nothing is in front of it).
* **Pin or Cup inside the claw:** Reads a small number (usually **`30 mm` to `70 mm`**).

Instead of guessing when to close the claw, the robot can **see** the Pin or Cup and clamp it automatically!

---

## 🔌 Step 0: Connect & Configure Your Sensor Ports (5 Mins)
Before writing any code, tell the robot which V5 Smart Ports (`1–21`) the two sensors are plugged into:

1. **Check the ports on the V5 Brain:** Turn on the Brain → tap **Devices** → find the two **Distance Sensor** icons and write down their port numbers (for example, `Port 10` and `Port 11`).
2. **Add them to `include/subsystems.hpp`:** Open `include/subsystems.hpp` and add these two lines using your actual port numbers:
   ```cpp
   // Distance Sensors in the claw (replace 10 and 11 with your Brain port numbers)
   inline pros::Distance distLeft(10);
   inline pros::Distance distRight(11);
   ```
3. **Verify the connection in code:** You can check `distLeft.is_installed()` in `src/main.cpp`'s `opcontrol()` to make sure both cables and ports match:
   ```cpp
   if (!distLeft.is_installed() || !distRight.is_installed()) {
     master.print(0, 0, "ERR: Check Ports! ");
   } else {
     master.print(0, 0, "L:%d R:%d   ", distLeft.get(), distRight.get());
   }
   pros::delay(50); // Keeps the controller screen from updating too fast
   ```

---

## 🛠️ Step 1: Read & Measure the "Sweet Spot" (15 Mins)
Now that your sensors are connected, find the exact millimeter number when a Pin or Cup is seated inside our flex wheels.

1. Place a **Pin** inside the claw where the flex wheels grip it best.
2. Read the live millimeter numbers on the **V5 Controller screen** (or go to **Devices → Distance Sensor** on the V5 Brain).
3. Write down your **"Grab Threshold"** in your Engineering Notebook:
   * Empty Claw Reading: `______ mm`
   * Pin Seated Reading: `______ mm` *(Example: `45 mm`)*
   * Cup Seated Reading: `______ mm` *(Example: `60 mm`)*

---

## 🧪 Step 2: Test & Tune in `src/smart_claw_test.cpp` (15 Mins)
Before changing our main match autons, test your threshold safely in our dedicated test file:

1. **Edit Threshold:** Open `src/smart_claw_test.cpp` and plug in your measured millimeter threshold (e.g., `55`).
2. **Upload Code:** Build and upload your code to the V5 Brain.
3. **Set Up:** Place a Pin or Cup in front of the robot on the field.
4. **Select Routine:** On the Brain's **Auton Menu**, select **Smart Claw Test**.
5. **Run & Verify:** Start the autonomous routine and confirm the robot drives forward, detects the object, and clamps cleanly without pushing it away. Adjust the millimeter value in `src/smart_claw_test.cpp` until it grabs reliably every time.

---

## 🎮 Step 3: Driver Control "Auto-Clamp" (25 Mins) -- in src/main.cpp
Once your threshold works in the test routine, add it to driver control! When the driver holds down a button (`R2`) to intake a Pin/Cup, the claw stays open until **either** distance sensor sees the object, then automatically snaps shut.

```cpp
// Put inside your opcontrol() while(true) loop:
if (master.get_digital(DIGITAL_R2)) {
  // Check if a Pin or Cup is inside the claw (< 55 mm)
  if (distLeft.get() < 55 || distRight.get() < 55) {
    clawB.move(-64); // Object detected! Auto-clamp!
    spin.move(0);    // Stop spinning once grabbed
  } else {
    clawB.move(32);  // Keep claw open while approaching
    spin.move(64);   // Spin flex wheels to pull Pin/Cup in
  }
}
```
**Why use `||` (OR)?** If a Pin enters slightly crooked on the left or right side, whichever sensor sees it first will trigger the grab!

---

## 🤖 Step 4: Autonomous "Smart Grab" (30 Mins) -- src/autons.cpp 
Right now, `lRight()` drives a guessed distance (`6 inches`) at slow speed and hopes the Pin is in the claw. Let's upgrade it so the robot **drives until the sensor sees the Pin, then clamps immediately**!

### ❌ BEFORE (Guessing Distance - src/autons.cpp)
```cpp
spin.move(32);
chassis.pid_drive_set(6, 15, false, true); // Hopes the Pin is at 6 inches
chassis.pid_wait();
pros::delay(200);
clawB.move(-64); // Clamps even if the Pin isn't there!
```

### ✅ AFTER (Sensor-Guided Smart Grab - src/autons.cpp)
```cpp
spin.move(40); // Start flex wheels pulling in
chassis.pid_drive_set(12_in, 35); // Drive slowly toward the Pin (up to 12 in max)

// Keep driving until EITHER sensor sees the Pin (< 55 mm) OR the 12-inch drive finishes
while (distLeft.get() > 55 && distRight.get() > 55 && chassis.is_driving()) {
  pros::delay(10);
}

chassis.drive_set(0, 0); // Stop motors AND cancel PID cleanly!
clawB.move(-64);         // Snap claw shut on the Pin
pros::delay(250);        // Give claw a split-second to grip tight
spin.move(0);            // Stop intake motor
```

### ⭐ Bonus Challenge: Auto-Square on a Goal (Using Both Sensors!)
Since we have **two** sensors (Left and Right), if `distLeft.get()` and `distRight.get()` read the **same number** (within `10 mm`) when facing a Goal, the robot knows it is lined up straight before dropping a Pin or Cup!
