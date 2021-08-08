
/*
  Web client

 This sketch connects to a website (wifitest.adafruit.com/testwifi/index.html)
 using the WiFi module.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */


//#include <SPI.h>
//#include <WiFiNINA.h>

  #define SPIWIFI       SPI
  #define SPIWIFI_SS    10   // Chip select pin
  #define SPIWIFI_ACK    9   // a.k.a BUSY or READY pin
  #define ESP32_RESETN   8   // Reset pin
  #define ESP32_GPIO0   -1   // Not connected

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables to save date and time
String formattedDate;
//String months;
//String hours;
//String minutes;
//String seconds;

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "Carti Vamps Only";        // your network SSID (name)
char pass[] = "metamorphosis";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)

char server[] = "wifitest.adafruit.com";    // name address for adafruit test
char path[]   = "/testwifi/index.html";

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;



String get_time() {
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  WiFi.setPins(SPIWIFI_SS, SPIWIFI_ACK, ESP32_RESETN, ESP32_GPIO0, &SPIWIFI);
  while (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    delay(1000);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }
  //Serial.print("Found firmware "); Serial.println(fv);

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to SSID: ");
  Serial.print(ssid);
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  do {
    status = WiFi.begin(ssid, pass);
    //delay(100);     // wait until connection is ready!
  } while (status != WL_CONNECTED);
  
  Serial.println();
  Serial.print("Connected to: ");
  Serial.println(ssid);

  Serial.print("Establishing connection with NTP");
  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  
  // GMT -1 = -3600
  // GMT 0 = 0
  //timeClient.setTimeOffset(-14400); 
  timeClient.setTimeOffset(-18000); 

  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  Serial.println();

  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
  formattedDate = timeClient.getFormattedDate();
  Serial.print("Recieved time: ");
  Serial.println(formattedDate);
  
  return formattedDate;
}
