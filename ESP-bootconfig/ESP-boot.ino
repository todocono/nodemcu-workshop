/* Example nodemcu workshop
  by Rodolfo Cossovich http://rudi.plobot.com
  This example code is in the public domain.

  try function1 and function2
*/


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <EEPROM.h>

#include "control.h"
#include "about.h"
#include "microajax.h"
#include "style.h"


#define D0 16     //onboard LED 
#define D1 5
#define D2 4
#define D3 0
#define D4 2      //onboard LED
#define D5 14
#define D6 12
#define D7 13
#define D8 15   //needs to be open when flashing
// D9 USB
// D10 USB
//#define pinSD2 9 //reserved
#define SD3 10

//pins for ultrasound
#define trigPin D0
#define echoPin D1

//pins for ultrasound
#define PWMA D1
#define DIRA D3
#define PWMB D2
#define DIRB D4


/*
   This example serves a "hello world" on a WLAN and a SoftAP at the same time.
   The SoftAP allow you to configure WLAN parameters at run time. They are not setup in the sketch but saved on EEPROM.

   Connect your computer or cell phone to wifi network ESP_ap with password 12345678. A popup may appear and it allow you to go to WLAN config. If it does not then navigate to http://192.168.4.1/wifi and config it there.
   Then wait for the module to connect to your wifi and take note of the WLAN IP it got. Then you can disconnect from ESP_ap and return to your regular WLAN.

   Now the ESP8266 is in your network. You can reach it through http://192.168.x.x/ (the IP you took note of) or maybe at http://esp8266.local too.

   This is a captive portal because through the softAP it will redirect any http request to http://192.168.4.1/
*/




/* Set these to your desired softAP credentials. They are not configurable at runtime */
const char *softAP_ssid = "WRITEHERE";
const char *softAP_password = "12345678";

/* hostname for mDNS. Should work at least on windows. Try http://esp8266.local */
const char *myHostname = "esp8266";

/* Don't set this wifi credentials. They are configurated at runtime and stored on EEPROM */
char ssid[32] = "";
char password[32] = "";

// DNS server
//const byte DNS_PORT = 53;
//DNSServer dnsServer;

// Web server
ESP8266WebServer server(80);

/* Soft AP network parameters */
IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);


/** Should I connect to WLAN asap? */
boolean connect;

/** Last time I tried to connect to WLAN */
long lastConnectTry = 0;

/** Current WLAN status */
int status = WL_IDLE_STATUS;



int ledState = LOW;

unsigned long previousMillis = 0;
const long interval = 500;


void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(D4, OUTPUT);
  delay(1000);
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAPConfig(apIP, apIP, netMsk);
  WiFi.softAP(softAP_ssid, softAP_password);
  delay(500); // Without delay I've seen the IP address blank
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  /* Setup the DNS server redirecting all the domains to the apIP */
  //  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  // dnsServer.start(DNS_PORT, "*", apIP);

  /* Setup web pages: root, wifi config pages, SO captive portal detectors and not found. */
  server.on("/", handleRoot);
  server.on("/wifi", handleWifi);
  server.on("/wifisave", handleWifiSave);
  server.on("/update", handleUpdate);
  server.on("/generate_204", handleRoot);  //Android captive portal. Maybe not needed. Might be handled by notFound handler.
  server.on("/fwlink", handleRoot);  //Microsoft captive portal. Maybe not needed. Might be handled by notFound handler
  server.on ( "/control.html", []() {
    Serial.println("control.html");
    server.send ( 200, "text/html", PAGE_Control );
  }  );
  server.on ( "/about.html", []() {
    Serial.println("about.html");
    server.send ( 200, "text/html", PAGE_About );
  }  );
 
  server.on("/function1", function1);
  server.on("/function2", function2);
  server.onNotFound ( handleNotFound );
  server.begin(); // Web server start
  Serial.println("HTTP server started");
  loadCredentials(); // Load WLAN credentials from network
  connect = strlen(ssid) > 0; // Request WLAN connect if there is a SSID
}

void connectWifi() {
  Serial.println("Connecting as wifi client...");
  WiFi.disconnect();
  WiFi.begin ( ssid, password );
  int connRes = WiFi.waitForConnectResult();
  Serial.print ( "connRes: " );
  Serial.println ( connRes );
}


void breathe ( void ) {
  float currentMillis = millis() / 5000.0;
  int value = 512.0 + 512 * sin( currentMillis * 2.0 * PI  );
  analogWrite(BUILTIN_LED, value);
}

void function1 ( void ) {
  digitalWrite (D4, HIGH);
   Serial.println ( "Function1" );
    server.sendContent(
    "<html><head></head><body>"
    "<h1>Function1</h1></body>"
  );
}

void function2 ( void ) {
digitalWrite (D4, LOW);
 Serial.println ( "Function2");
  server.sendContent(
    "<html><head></head><body>"
    "<h1>Function2</h1>"
  );
}


void loop() {
  if (connect) {
    Serial.println ( "Connect requested" );
    connect = false;
    connectWifi();
    lastConnectTry = millis();
  }
  {
    int s = WiFi.status();
    if (s == 0 && millis() > (lastConnectTry + 60000) ) {
      /* If WLAN disconnected and idle try to connect */
      /* Don't set retry time too low as retry interfere the softAP operation */
      connect = true;
    }
    if (status != s) { // WLAN status change
      Serial.print ( "Status: " );
      Serial.println ( s );
      status = s;
      if (s == WL_CONNECTED) {
        /* Just connected to WLAN */
        Serial.println ( "" );
        Serial.print ( "Connected to " );
        Serial.println ( ssid );
        Serial.print ( "IP address: " );
        Serial.println ( WiFi.localIP() );

        /* // Setup MDNS responder
          if (!MDNS.begin(myHostname)) {
           Serial.println("Error setting up MDNS responder!");
          } else {
           Serial.println("mDNS responder started");
           // Add service to MDNS-SD
           MDNS.addService("http", "tcp", 80);
          }
        */
      } else if (s == WL_NO_SSID_AVAIL) {
        WiFi.disconnect();
      }
    }
  }
  // Do work:
  //DNS
  // dnsServer.processNextRequest();
  //HTTP
  server.handleClient();
  breathe();

}

