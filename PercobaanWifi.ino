#include "WiFi.h"
#include "EmonLib.h"             // Include Emon Library
#include <HTTPClient.h>         // http
//Tegangan RST
EnergyMonitor v_r;             // Create an instance
EnergyMonitor v_s;             // Create an instance
EnergyMonitor v_t;             // Create an instance

//WIFI
const char* ssid = "ArnetTSM";
const char* password = "arnet2023";

//ESP32
const char* idEsp32 = "E1";
const char* stoName = "TSM";

void setup()
{
  Serial.begin(9600);
  // Set WiFi to station mode and disconnect from an AP if it was previously connected.
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  v_r.voltage(27, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
  v_s.voltage(26, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
  v_t.voltage(25, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
}

void loop()
{
  //  Saat Connect
  while (WiFi.status() == WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.print("Connect");
    delay(1000);
    v_r.calcVI(20, 100);        // Calculate all. No.of half wavelengths (crossings), time-out
    float supplyVoltageR   = v_r.Vrms;             //extract Vrms into Variable
    v_s.calcVI(20, 100);
    float supplyVoltageS   = v_s.Vrms;
    v_t.calcVI(20, 100);
    float supplyVoltageT   = v_t.Vrms;
    default_work_mode(supplyVoltageR, supplyVoltageS, supplyVoltageT);
  }

  //  Saat Tidak Connect
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.print("Disconnect");
    delay(1000);
    v_r.calcVI(20, 100);        // Calculate all. No.of half wavelengths (crossings), time-out
    float supplyVoltageR   = v_r.Vrms;             //extract Vrms into Variable
    v_s.calcVI(20, 100);
    float supplyVoltageS   = v_s.Vrms;
    v_t.calcVI(20, 100);
    float supplyVoltageT   = v_t.Vrms;
    default_work_mode(supplyVoltageR, supplyVoltageS, supplyVoltageT);
  }
}
void default_work_mode(float vR, float vS, float vT) {
  if (vR < 100 or vS < 100 or vT < 100) {
    Serial.println("PLN MATI");
    digitalWrite(13, HIGH);
  } else {
    Serial.println("PLN HIDUP");
    digitalWrite(13, LOW);
  }
}
//Fungsi Kirim Data
//Fungsi Get Data
//link https://script.google.com/macros/s/AKfycbwaZyQ2CMXzGFFlql-IJF8eWpX2Tj_lbGNreO98huo7i_WqiuyBh3Q2SfKKMLXJ7yN6/exec?id=(NOMOR ID)&status=all
//Fungsi Tambah Data
// https://script.google.com/macros/s/AKfycbwaZyQ2CMXzGFFlql-IJF8eWpX2Tj_lbGNreO98huo7i_WqiuyBh3Q2SfKKMLXJ7yN6/exec?sto_name=SPA&v_r=7&v_s=7&v_t=7&method=POST

void contohHttp() {
  HTTPClient http;

  //  USE_SERIAL.print("[HTTP] begin...\n");
  // configure traged server and url
  //http.begin("link https://script.google.com/macros/s/AKfycbwaZyQ2CMXzGFFlql-IJF8eWpX2Tj_lbGNreO98huo7i_WqiuyBh3Q2SfKKMLXJ7yN6/exec?id="+idEsp32+"&status=all", ca); //HTTPS
  http.begin("https://script.google.com/macros/s/AKfycbwaZyQ2CMXzGFFlql-IJF8eWpX2Tj_lbGNreO98huo7i_WqiuyBh3Q2SfKKMLXJ7yN6/exec?id=" + (String)idEsp32 + "&status=all"); //HTTP

  //  USE_SERIAL.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    //    USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
//    Serial.println("[HTTP] GET... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
      //      USE_SERIAL.println(payload);
    }
  } else {
    //    USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    Serial.println(http.errorToString(httpCode).c_str());
  }

  http.end();
}
