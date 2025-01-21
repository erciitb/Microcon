# Setting Up the Playground

## Prerequisites

To implement Gemini AI response text-to-speech, ensure you have the following:

### Arduino Setup
1. **Latest Arduino Version Installed** https://www.arduino.cc/en/software
2. **ESP32 Board Manager URL**  
   Add the following link to the "Additional Board Manager URLs" section in the Preferences of the Arduino IDE:  
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

Refer to the image below for guidance:

![Preferences Section](https://github.com/user-attachments/assets/4723f110-8145-49d0-a762-84dd3d625ac3)

3. Once the ESP32 Board Manager URL is added, install the latest version of the ESP32 libraries from the Board Manager, as shown below.  
*(Note: You may need to change this version later for the AI chatbot activity, as specified in the README file of the respective folders, such as "Speech to Text" and "Text to Speech.")*

![ESP32 Libraries](https://github.com/user-attachments/assets/0ac6bbe7-c0a6-4e4e-90a0-d4f49cff8fcc)

---

# Activity 

## Introducing Cloud Service

For the first part, we will introduce to ardiuno iot cloud , by which you can control your esp remotely. 😊

To do this, follow these steps:  
1. Use a cloud service, such as **Arduino Cloud**.  
- Sign up for Arduino Cloud using [this link](https://www.arduino.cc/).  
- Install the **Arduino Client Agent** by following the on-screen instructions.  
2. Set up your device.  
3. Add a "Thing" to this device.  
4. Upload the provided code to your device.  
5. Finally, monitor the data on the Arduino Cloud dashboard.

---

# AI Chatbot 

## Circuit Setup
Refer to the image file **`circdiag.jpg`** from the repository.  
- The circuit diagram on the left is for the speaker.  
- The circuit diagram on the right is for the microphone.  
- **Do not connect the two microcontrollers initially**—execute them separately. Later, connect them together.
- 
![circdiag](https://github.com/user-attachments/assets/f186d416-e5cd-41dc-804f-dfdd80b3fc39)

---

### Text-to-Speech + Gemini AI (For Those with a Speaker)
1. Navigate to the **Team_A folder** in this repository and follow the instructions provided.  
2. In this segment, you will implement **text-to-speech** functionality. Whenever Gemini is asked a question, the response will be output through the speaker.

---

### Speech-to-Text (For Those with a Microphone)
1. Navigate to the **Team_B folder** in this repository and follow the instructions provided.  
2. In this segment, you will implement **speech-to-text** functionality. The ESP32 will display a text output when you speak into the microphone.

---

## Final Integration 

1. Once you have two separate devices for **text-to-speech** and **speech-to-text**, it's time to integrate them via UART communication.  
- The text output from the **speech-to-text** ESP will be sent to the **text-to-speech** ESP.  
- The response from Gemini AI will then be played through the speaker.

2. Navigate to the **chatbot folder** in the repository for schematics and additional resources.
