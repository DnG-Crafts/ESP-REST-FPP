#include "WiFi.h"


#define WIFI_SSID   "wifi-ssid"
#define WIFI_PASS   "wifi-password"
#define WIFI_HOSTNAME   "fpprest"

#define FPP_HOSTIP   "127.0.0.1"  // hostname or ip address of fpp on the network

WiFiClient client;
#include "funcs.h"



#define Button1 4   //GPIO 4
#define Button2 16  //GPIO 16
#define Button3 17  //GPIO 17
#define Button4 5   //GPIO 5



void setup() {
  
  pinMode(Button1, INPUT_PULLUP); // set pins high so the trigger is applying "GND" pulling it low.
  pinMode(Button2, INPUT_PULLUP);
  pinMode(Button3, INPUT_PULLUP);
  pinMode(Button4, INPUT_PULLUP);

  
  //start serial, only needed for debug
 // Serial.begin(115200);

  //connect wifi
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  WiFi.hostname(WIFI_HOSTNAME);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Wifi failed to connect");
  }

  Serial.println("started");
}

        

void loop() {

  if (digitalRead(Button1) == LOW){  
    getRESTCommand("/api/playlist/show/start");
    delay(1000);
  }

  if (digitalRead(Button2) == LOW){  
    getRESTCommand("/api/command/Next Playlist Item");
    delay(1000);
  }
  
  if (digitalRead(Button3) == LOW){ 
    getRESTCommand("/api/command/Prev Playlist Item");
    delay(1000);
  }

  if (digitalRead(Button4) == LOW){ 
    getRESTCommand("/api/playlists/stop");
    delay(1000);
  }


/*
  // print received data to serial
  while (client.available()) {
    String c = client.readString();
    Serial.println(c);
  }
*/

}






/*
     --------------------GET examples-------------------- 
     
     play fseq by name
     getRESTCommand("/api/command/FSEQ Effect Start/blue_button");


     start playlist, replace "PLAYLISTNAME" with the name of the playlist you want to start
     getRESTCommand("/api/playlist/PLAYLISTNAME/start");


     stop playlist, you can also "pause", "resume", "stopgracefully"
     getRESTCommand("/api/playlists/stop");


     play next item in play list
     getRESTCommand("/api/command/Next Playlist Item");


     play previous item in playlist
     getRESTCommand("/api/command/Prev Playlist Item");


     stop test
     getRESTCommand("/api/command/Test Stop");




     --------------------POST examples--------------------

     start test
     postRESTCommand("/api/command","{\"command\":\"Test Start\",\"multisyncCommand\":false,\"multisyncHosts\":\"\",\"args\":[\"1000\",\"RGB Cycle\",\"1-300\",\"R-G-B\"]}");

     stop test
     postRESTCommand("/api/command","{\"command\":\"Test Stop\",\"multisyncCommand\":false,\"multisyncHosts\":\"\",\"args\":[]}");

     set volume
     postRESTCommand("/api/system/volume","{\"volume\": 34}");



     
*/
