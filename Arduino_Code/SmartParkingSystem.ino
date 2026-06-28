#define BLYNK_TEMPLATE_ID "TMPL3jDvnYGIM"
#define BLYNK_TEMPLATE_NAME "Car Parking"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// WiFi
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// Pins
#define SLOT1 D5
#define SLOT2 D6
#define SLOT3 D7
#define SLOT4 D2   // IMPORTANT FIX

BlynkTimer timer;

// Function
void checkSlots() {
  int s1 = digitalRead(SLOT1);
  int s2 = digitalRead(SLOT2);
  int s3 = digitalRead(SLOT3);
  int s4 = digitalRead(SLOT4);

  Serial.print("S1: "); Serial.print(s1);
  Serial.print(" S2: "); Serial.print(s2);
  Serial.print(" S3: "); Serial.print(s3);
  Serial.print(" S4: "); Serial.println(s4);

  int total = (1 - s1) + (1 - s2) + (1 - s3) + (1 - s4);

  Serial.print("TOTAL: ");
  Serial.println(total);

  // Send to Blynk
  Blynk.virtualWrite(V1, s1 ? "EMPTY" : "FILLED");
  Blynk.virtualWrite(V2, s2 ? "EMPTY" : "FILLED");
  Blynk.virtualWrite(V3, s3 ? "EMPTY" : "FILLED");
  Blynk.virtualWrite(V4, s4 ? "EMPTY" : "FILLED");
  Blynk.virtualWrite(V5, total);
  delay(100);
}

void setup() {
  Serial.begin(115200);

  pinMode(SLOT1, INPUT);
  pinMode(SLOT2, INPUT);
  pinMode(SLOT3, INPUT);
  pinMode(SLOT4, INPUT);

  Serial.println("Starting...");

  WiFi.begin(ssid, pass);
  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");

  Blynk.config(BLYNK_AUTH_TOKEN);

  Serial.println("Connecting Blynk...");
  if (Blynk.connect()) {
    Serial.println("Blynk Connected ✅");
  } else {
    Serial.println("Blynk NOT Connected ❌");
  }

  timer.setInterval(1000L, checkSlots);
}

void loop() {
  Blynk.run();
  timer.run();
}

