/*

*/

#define BLYNK_PRINT Serial  // Comment this out to disable prints and save space
#define LED1 16
#define LED2 13

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Boton.h>

// Definicion de variables para conexion al servidor Blynk y conexion WiFi
char auth[] = "46469af9d6ab4d8ea349172618394f96";
char ssid[] = "ssidName";
char pass[] = "Passw0rd";

// Definicion de variables que utilizara el programa
int btnState = LOW;

Boton pepe(3);

// Definicion de variables de la App
WidgetLED wifiLED(V0);
WidgetLED led1(V1);
WidgetLED led2(V2);

BlynkTimer timer;

// ####################################### FUNCIONES #######################################

void wifiStatus() {
  Serial.print(millis());
  Serial.println(F(": wifiStatus."));

  if (WiFi.status() == WL_CONNECTED) {                // Connection established
    Serial.print(millis());
    Serial.print(F(": Connectado al Access Point.\nLocal IP: "));
    Serial.println(WiFi.localIP());
    wifiLED.on();
  }
}

// Acciones a ejecutar cada vez que se conecta al servidor Blynk
BLYNK_CONNECTED() {
    // Solicita el ultimo estado del servidor
    Blynk.syncVirtual(V1);
    Blynk.syncVirtual(V3);
}

// Obtencion del estado del boton virtual mediante el puerto virtual V3
BLYNK_WRITE(V3) {

  btnState = param.asInt();

  if(btnState) {  // Acciones cuando el valor del boton es = 1
    digitalWrite(LED1, HIGH);
    Blynk.virtualWrite(V1,HIGH);
    Blynk.virtualWrite(V3,HIGH);
    led1.on();
    //Serial.printf("LED1 %d\n",V3);
  } else {      // Acciones cuando el valor del boton es = 0
    digitalWrite(LED1, LOW);
    Blynk.virtualWrite(V1,LOW);
    Blynk.virtualWrite(V3,LOW);
    led1.off();
    //Serial.printf("LED1 %d",V3);
  }
}

void setup()
{
    // Configuracion de puerto serie para Debug
    Serial.begin(9600);

    // Configuracion de puertos de entrada/salida
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    // Definicion de conexion a la red WiFi
    Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,213), 8080);

    // Configuracion de temporizadores
    timer.setInterval(5000L, wifiStatus);
}

void loop()
{
    Blynk.run();
    timer.run();
}