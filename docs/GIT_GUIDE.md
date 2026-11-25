# 🕹️ Git Cheat Sheet

Think of **GitHub** as a shared online locker for our robot code, and **Git** as a "save game" system so we never lose working code!

---

## 🛠️ Part 1: One-Time Setup (Do This Once on Your Laptop)

**1. Install Git**
* **Windows:** Download and run the installer from [git-scm.com](https://git-scm.com) (just click "Next" through the setup).
* **Mac:** Open the **Terminal** app, type `git --version`, and press Enter. Click **Install** if a pop-up asks for developer tools.

**2. Tell Git Who You Are**
Open the terminal in VS Code (`Ctrl + ~` or `Cmd + ~`) and run these two lines with your own name and email:
```bash
git config --global user.name "Your First Name"
git config --global user.email "your-email@example.com"
```

**3. Download Our Team Code (`git clone`)**
Go to the folder where you want to keep the code, then copy our repo link from GitHub and run:
```bash
git clone https://github.com/gjyuchuan/EZ-Template-Example-Project-v3
```
*(After this finishes, open that new folder in VS Code!)*

---

## 🚀 Part 2: Your Daily Coding Loop

Follow these steps every time you sit down to work on the robot:

### 1️⃣ Get the Newest Code (`git pull`)
Make sure you are on `main` and grab the latest updates from your teammates before you touch any code.
```bash
git checkout main
git pull
```

### 2️⃣ Make Your Own Workspace (`git checkout -b`)
Create your own "branch" (a safe copy of the code) so you don't accidentally mess up the main robot code while testing.
```bash
git checkout -b yourname-whatyouredoing
```
*(Example: `git checkout -b sam-auton-test`)*

### 3️⃣ Code & Test on Your Brain Slot!
Write your code, plug in the V5 Brain, and upload to **your assigned slot**:
```bash
pros mu --slot <YOUR_SLOT> --name "<YOUR_NAME>"
```

### 4️⃣ Save a Checkpoint (`git add` & `git commit`)
Happy with your code? Pack up your changes and label them like a save file:
```bash
git add .
git commit -m "Short note about what you changed"
```
*(Example: `git commit -m "Tuned drivetrain turn speed"`)*

### 5️⃣ Upload to GitHub (`git push`)
Send your saved branch up to GitHub:
```bash
git push -u origin yourname-whatyouredoing
```
*(Tip: If you push to the same branch again later, you only need to type `git push`!)*

### 6️⃣ Open a Pull Request (PR) on GitHub
A **Pull Request (PR)** is how you ask the team to review your code and combine it into the official `main` robot code:
1. Go to our team's page on **GitHub.com**.
2. Click the green **"Compare & pull request"** button that pops up at the top.
3. Write a quick title and a 1–2 sentence description of what your code does (and confirm you tested it on the robot!).
4. Click **"Create pull request"** and let a teammate or lead coder review and merge it.
5. Once it's merged, go back to your terminal and switch back to `main` for next time:
```bash
git checkout main
git pull
```

---

## ⚡ Quick Command Cheat Sheet

| Command | What It Does |
| :--- | :--- |
| `git status` | Checks what files you changed (great if you feel lost!) |
| `git pull` | Downloads the latest code from GitHub |
| `git checkout -b <name>` | Creates and switches to a brand-new branch |
| `git checkout main` | Switches back to the main team code |
| `git add .` | Prepares all your changed files to be saved |
| `git commit -m "note"` | Saves a checkpoint with a short description |
| `git push` | Uploads your saved branch to GitHub |

---

## 🆘 Help! Something Went Wrong!
* **Don't panic and don't force commands!** 
* Run `git status` to see what Git is thinking, and ask a teammate or mentor for help.
