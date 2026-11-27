# 🚀 Robot Cruise Control: What is PID & Why Tune It?

## What is PID?
Think of **PID** as your robot’s **smart cruise control + automatic brakes**. Without tuning it, your robot either stops short, slides past the target, or drifts off-angle—especially as the battery drains.

We only adjust **two numbers** in `src/pid_tuning.cpp`:
* **`kP` (Gas Pedal):** How hard the robot pushes toward the target.
* **`kD` (Brakes):** How hard the robot slows down right before the target so it stops on a dime without overshooting.

## Why Tune It Before Our Tournament?
1. **Same spot every time:** Hits the exact inch and angle whether the battery is at 100% or 70%.
2. **Faster autons:** No more wasting seconds waiting on extra `pros::delay()` pauses.
3. **Cleaner code:** Cuts out messy "baby-step" fixes.

---
## 💻 How Our Code Improves After Tuning

Right now, `lRight()` has to use **3 extra moves, slow speeds, and delays** just to back up and turn because the robot drifts:

### ❌ BEFORE (Untuned — Clunky & Slow)
```cpp
// Split into 3 choppy steps + delays to fix drift
chassis.pid_drive_set(-5, 32*DRIVE_SPEED, false, true); 
chassis.pid_turn_set(70, 36*TURN_SPEED, false); 
chassis.pid_wait();
pros::delay(400/WAIT_TIME);
chassis.pid_drive_set(-10, 32*DRIVE_SPEED, false, true); 
chassis.pid_wait();
chassis.pid_turn_set(33, 64*TURN_SPEED, false); 
```

### ✅ AFTER (Tuned — Fast, Clean & Accurate)
```cpp
// 1 straight backup + 1 crisp turn at higher speed (zero delays!)
chassis.pid_drive_set(-15_in, 80); 
chassis.pid_wait();
chassis.pid_turn_set(33_deg, 80); 
chassis.pid_wait();
```

---

## 🎯 Practice Goal (2 Steps)
1. **Turn Test:** Make the robot turn **90°** and stop dead square on a tile seam.
2. **Drive Test:** Make the robot drive **24 inches** (1 field tile) and stop right on the seam.

### 📝 Quick Tuning Cheat Sheet

| What the Robot Does | What to Change |
| :--- | :--- |
| **Stops short** and crawls slowly | **Increase `kP`** (+1 or +2) |
| **Goes past** the line (overshoots) | **Increase `kD`** (+10 or +15) |
| **Shakes/wobbles** at the end | **Decrease `kD`** (-5 or -10) |
| **Stops dead on the tile seam** | **Done!** Save those numbers |

