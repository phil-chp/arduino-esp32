/**
 * ESP32 mDNS query a host
 *
 * This is an example of how to query a host using mDNS.
 *
 * Instructions:
 * - Update WiFi SSID and password as necessary.
 * - Update the hostname you are trying to query accordingly
 *   - For any OS open either a shell (Linux/MacOS) or command prompt (Windows) and type: `hostname`
 * - Flash the sketch to the ESP32 board
 * - Install host software:
 *   - For Linux, install Avahi (http://avahi.org/).
 *   - For Windows, install Bonjour (http://www.apple.com/support/bonjour/).
 *   - For Mac OSX and iOS support is built in through Bonjour already.
 * - Open the Serial Monitor
 *   - You should see the IP address  of the host you are trying to query
 */

#include <WiFi.h>
#include <ESPmDNS.h>

const char ssid[] = "............";
const char password[] = "..............";

// Hostnames are formed like so: `hostname.local`, when using
// `MDNS.queryHost()`, omit the `.local`, ESPmDNS already appends it.
const char hostname[] = "my-computer";

void setup(void) {
  Serial.begin(115200);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Set up mDNS responder:
  // - first argument is the domain name, in this example
  //   the fully-qualified domain name is "esp32.local"
  // - second argument is the IP address to advertise
  //   we send our IP address on the WiFi network
  if (!MDNS.begin("esp32")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
}

void loop(void) {
  // Query the hostname, wait for 3 seconds (3000ms) for a response
  IPAddress resolvedIP = MDNS.queryHost(hostname, 3000);

  // Verify that resolvedIP was successful (in case of error it is set to `0.0.0.0`)
  if (resolvedIP) {
    Serial.print("Resolved IP: ");
    Serial.println(resolvedIP);
  } else {
    Serial.println("hostname not found");
  }
  delay(1000);
}
