
// เอามาจาก info ในเว็บ 
// อย่าลืมเอา " // " ออก
//#define BLYNK_TEMPLATE_ID " "
//#define BLYNK_DEVICE_NAME " "

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// ใช้อันไหน เลือกอันนั้น
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"


#include <SimpleTimer.h>  
SimpleTimer timer;

#include <DHT.h>
#define DHTTYPE DHT11   // ใช้ตัวไหน ให้เปลี่ยนเป็นตัวนั้น DHT22
#define DHTPIN D5       //  ใช้ขาไหนเปลี่ยนเป็นขานั้น แนะนำให้ใช้ D5 เหมือนเดิม
DHT dht(DHTPIN, DHTTYPE);

#define rel1 D6


BLYNK_WRITE(V2){
  int valV2 = param.asInt(); 
  digitalWrite(rel1, valV2);
}


void dhtTest(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}



void setup()
{
  Serial.begin(115200);

  pinMode(rel1, OUTPUT);
  digitalWrite(rel1, LOW);
  
  timer.setInterval(3000L, dhtTest);  // หน่วงเวลา
  dht.begin();
  BlynkEdgent.begin();
}

void loop() {
  timer.run();
  BlynkEdgent.run();
}
