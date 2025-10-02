# AR4 Robotic Arm – Qt6 Control & Vision Interface

## 📌 Project Overview

This project is a **Qt6-based GUI application** developed to control and monitor a robotic arm (AR4, or similar) while integrating computer vision (OpenCV) and calibration tools. The application is structured into multiple tabs, each handling a specific part of the robotics workflow:

- **Robot Control Tab** → Manual driving, mode switching, speed/motor management.
    
- **Calibration Tab** → Camera calibration pipeline for undistortion & parameter tuning.
    
- **Object Detection Tab** → Real-time video preview, basic object detection logic (stubbed for future YOLO/AI integration).
    

The main goal of this project was **educational**: to understand how robotics interfaces are built in real-world applications using **Qt, OpenCV, and C++ threading**.

---

## ⚡ Features Implemented

### 1. **Robot Control Tab**

- Forward, Backward, Left, Right, Stop controls (buttons + keyboard shortcuts).
    
- **Modes**:
    
    - _Joint Jog Mode_ → Select and jog a specific joint.
        
    - _Planar XYZ Mode_ → Select axis (X, Y, Z) for Cartesian control.
        
- **Speed Control**: Slider (0–100%) with real-time updates.
    
- **Motor Enable/Disable** checkbox with guard logic.
    
- **Connection Handling**: Controls are disabled until robot connection is confirmed.
    
- **Logging**: All actions (buttons, key events, mode changes) recorded in a text box.
    

### 2. **Calibration Tab**

- Start camera calibration by selecting multiple chessboard images.
    
- Runs OpenCV’s `findChessboardCorners`, `cornerSubPix`, and `calibrateCamera`.
    
- Shows calibration metrics: **RMS error** and **image size**.
    
- Supports **Save/Load calibration parameters** (YAML).
    
- Provides **test preview** → load an image and apply undistortion using computed calibration parameters.
    
- Slider + SpinBox pairs for Exposure, Brightness, and Contrast (normalized values prepared for future camera API integration).
    

### 3. **Object Detection Tab**

- Displays live video frames.
    
- HUD overlay showing model info and placeholder status.
    
- Simple **HSV color thresholding + contour detection** pipeline.
    
- YOLO integration prepared as a stub (UI and logic ready, model to be added).
    

### 4. **General Architecture**

- Modularized per-tab (ObjectDetectionTab, CalibrationTab, RobotControl).
    
- Defensive programming (null checks, guards).
    
- Reusable helpers: `matToQImage`, logging system, UI-to-normalized-value conversion.
    
- Clear Qt signal-slot design (UI → signals → slots → logic).
    

---

## 🧑‍💻 My Contribution (Student-Level Work)

- Implemented **Qt6 GUI design** with `.ui` files for each tab.
    
- Built **Robot Control Tab logic** (keyboard + button driving, speed management, motor safety).
    
- Integrated **OpenCV camera calibration** pipeline with YAML save/load.
    
- Developed **Object Detection Tab stubs** (HUD overlay, HSV-based detection).
    
- Added **logging features** across tabs for debugging and feedback.
    
- Learned threading, OpenCV, and Qt event handling concepts in the process.
    

---

## 🔧 Future Improvements (Next Steps)

If another developer or robotics engineer wants to take this project forward, here’s what they should improve:

### 🔹 Object Detection Tab

- Integrate a real model (e.g., **YOLOv8, TensorRT**) for robust object detection.
    
- Add **multi-threaded frame capture & processing** (to reduce UI lag).
    
- Implement **object-to-robot communication** (e.g., auto-pick-and-place).
    

### 🔹 Calibration Tab

- Link sliders/spin boxes directly to **camera hardware APIs** (e.g., OpenCV `VideoCapture::set`).
    
- Store/load calibration profiles per camera.
    
- Add **real-time preview** instead of static image undistortion.
    

### 🔹 Robot Control Tab

- Replace dummy signals with **real robot communication** (serial/TCP/IP, ROS bridge, EtherCAT).
    
- Add **safety features**: watchdogs, emergency stop, deadman switches.
    
- Implement **inverse kinematics (IK)** for Planar XYZ control.
    
- Expand to **6-DOF control** with joint angles display.
    

### 🔹 General / Professional Enhancements

- Refactor into **Model-View-Controller (MVC)** for scalability.
    
- Package the project as a **ROS2 node with Qt GUI frontend**.
    
- Add **unit tests** for calibration, detection, and control logic.
    
- Optimize for **real-time performance** (OpenCV GPU backend, Qt threads).
    

---

## 🚀 Skills Learned & Demonstrated

- **Qt6 Framework**: UI design, signals/slots, custom widgets.
    
- **OpenCV**: Camera calibration, image processing, matrix operations.
    
- **C++ Fundamentals**: Event handling, signal blocking, enums, RAII.
    
- **Robotics Concepts**: Joint vs Cartesian control, calibration workflow, vision integration.
    

---

## 📌 Summary

This project is an **educational robotics control GUI**, designed and built as part of a learning journey.  
It demonstrates how **real robotics engineers structure control software**, while leaving space for professional extensions (ROS integration, AI detection models, IK solvers).

It serves as a strong **portfolio piece** that shows:  
✅ Practical Qt6 + OpenCV coding skills  
✅ Understanding of robotics workflow (control, calibration, detection)  
✅ Awareness of future improvements toward production-level systems

---

🔥 **Note for Recruiters / Developers**:  
This project is a student-level prototype. If taken further with hardware integration, it can become a **full robotics control suite** suitable for research and industrial robots.