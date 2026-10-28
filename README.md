
# AI & IoT Smart Irrigation System

A portfolio project exploring machine learning for soil moisture classification and an ESP32-based smart irrigation system simulation.

## Project Overview

This project explores two components of smart irrigation:

- **Machine Learning:** Classifies soil conditions into four categories: Dry, Very Dry, Wet, and Very Wet.
- **IoT Simulation:** Uses an ESP32-based circuit in Wokwi to simulate irrigation control using sensor readings and rule-based logic.

The machine-learning model and the IoT simulation are currently separate components.

## Project Structure

```text
ai-iot-smart-irrigation/
├── ai-model/
│   ├── README.md
│   └── smart-irrigation-agriculture.ipynb
├── iot-simulation/
│   ├── README.md
│   ├── diagram.json
│   └── sketch.ino
└── README.md
```

## Machine Learning

The notebook explores soil condition classification using:

- Logistic Regression
- Random Forest
- Gradient Boosting
- K-Nearest Neighbours (KNN)

The workflow includes data preprocessing, feature scaling, cross-validation, model evaluation, confusion matrices, and performance metrics such as accuracy, precision, recall, and F1-score.

KNN was selected for further evaluation in the assignment.

## IoT Simulation

The Wokwi simulation explores an automated irrigation system using:

- ESP32 microcontroller
- DHT22 temperature and humidity sensor
- LCD display
- Servo motor to represent a watering mechanism
- LEDs to indicate system status
- Potentiometer to simulate a changing sensor input

The current simulation uses rule-based logic. The potentiometer is a simulated input, not a physical soil moisture sensor.

## Technologies

- Python
- Pandas and NumPy
- Scikit-learn
- Google Colab / Jupyter Notebook
- ESP32
- Arduino C++
- Wokwi

## Future Improvements

- Connect the machine-learning model to the ESP32 irrigation logic.
- Integrate a real soil moisture sensor.
- Improve model validation using a clearly documented dataset source.
- Explore live monitoring and remote control.

## Project Status

Educational and portfolio project. The machine-learning and IoT components are currently developed separately.
