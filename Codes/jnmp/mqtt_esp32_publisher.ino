// Most code is provided to us in the ECE180DA: Lab 4 Prompt

#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "";      // Enter your WiFi name
const char *password = "";  // Enter WiFi password

// MQTT Broker

// Choose a broker below
// const char *mqtt_broker = "test.mosquitto.org";
const char *mqtt_broker = "mqtt.eclipseprojects.io";

const char *topic = "test/topic";   // Enter your topic name here
// const char *mqtt_username = "emqx";
// const char *mqtt_password = "public";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
// Set software serial baud to 115200;
Serial.begin(115200);

// Connecting to a WiFi network
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
}
Serial.println("Connected to the WiFi network");

// Connecting to a MQTT broker
client.setServer(mqtt_broker, mqtt_port);
client.setCallback(callback);
while (!client.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str())) { //, mqtt_username, mqtt_password)) {
        Serial.println("mqtt broker connected");
    } else {
        Serial.print("failed with state ");
        Serial.print(client.state());
        delay(2000);
    }
}

// Try a Publish and Subscribe
client.publish(topic, "Hi I'm ESP32 ^^");
client.subscribe(topic);

}

void callback(char *topic, byte *payload, unsigned int length) {
 Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 for (int i = 0; i < length; i++) {
   Serial.print((char) payload[i]);
 }
 Serial.println();
 Serial.println("-----------------------");
}

void loop()
{
   // Publish to subscriber inside the loop
   client.publish(topic, 1);
   client.loop();
}
