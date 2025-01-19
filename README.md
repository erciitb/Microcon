
# Setting Up the PlayGround

## Prerequisites
For implementing Gemini AI response text-to-speech, ensure you have the following:

### Arduino Setup
- Latest Arduino version installed
- ESP32 Board Manager URL:
  ```
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
  ```
- Add the above link to additional board manager URL in the prefernce section in the IDE as shown in the below pic/.

  <img width="1710" alt="Image" src="https://github.com/user-attachments/assets/4723f110-8145-49d0-a762-84dd3d625ac3" />

Once esp32 board manager url is added , you can install the latest version of Esp32 libraies from the board manger as shown as the below image .( you might have to change this vrsion later for the upcomin gai chatbot activity , which is mentioned we in the readme file of teh respective  folders , ie speech to text and text to speech)


# Activity 

## Introducing sensors and cloud service

 for the frist part we will be using connecting a DHT11 sensor to esp32 and monitor its data remotly ....:)

 For that we need a cloud service , here we are going to use ardiuno cloud , 
- kindly to the this link and sign up for ardiuno cloud and install the ardiuno clint agent ( just follow on screen instructons)
- setup a device
- add a thing to this device
- upload teh code to the device
- finally monitor the data on dashboard

# AI Chat bot 

## text to speech + Gemini Ai ( if you got speacker follow this ) 

-  Navigate to Team_A folder in this repo and follow the instructions their 
-  in this particular segment we will be working on text to speech , i.e when ever gemini is asked a question , the response has to seen in the speacker.


## Speech to text ( if you got microphone ) 

-  Navigate to Team_A folder in this repo and follow the instructions their
-  in this particular segment we will be working on speech to text , i.e yor esp should show you a text output when you speak onto you microphone

## Final Integration 

- Now you have two devices , text to speech and speech to text .... what next ??
- integrate both of them via uart communication, i.e the text ouput in the speech to text is given to the text to speech vala esp and the response from gemin is given to speacker
- navigate to chatbot folder in the repo for schmatics and etc ..

  


