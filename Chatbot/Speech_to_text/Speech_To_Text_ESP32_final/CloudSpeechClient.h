#ifndef _CLOUDSPEECHCLIENT_H
#define _CLOUDSPEECHCLIENT_H
#include <WiFiClientSecure.h>
#include "Audio.h"

enum Authentication {
  USE_ACCESSTOKEN,
  USE_APIKEY
};

class CloudSpeechClient {
  WiFiClientSecure client;
  void PrintHttpBody2(Audio* audio);
  Authentication authentication;

  String ans;  // Store the transcription result (private member)

public:
  CloudSpeechClient(Authentication authentication);
  ~CloudSpeechClient();
  void Transcribe(Audio* audio);

  // Getter method for the transcription result
  String getTranscription() const { return ans; }
};

#endif // _CLOUDSPEECHCLIENT_H
