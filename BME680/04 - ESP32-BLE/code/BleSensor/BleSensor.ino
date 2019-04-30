#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Adafruit_BME680.h>
 
Adafruit_BME680 sensor;
BLEDescriptor humidityDescriptor(BLEUUID((uint16_t)0x2901));
BLEDescriptor temperatureDescriptor(BLEUUID((uint16_t)0x2901));

BLECharacteristic humidityCharacteristic(
  BLEUUID((uint16_t)0x2A6F),
  BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
BLECharacteristic temperatureCharacteristic(
  BLEUUID((uint16_t)0x2A6E),
  BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

bool bleClientConnected = false;

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* server) {
    bleClientConnected = true;
  };

  void onDisconnect(BLEServer* server) {
    bleClientConnected = false;
  }
};

void init_sensor(Adafruit_BME680& sensor) {
  sensor.setTemperatureOversampling(BME680_OS_8X);
  sensor.setHumidityOversampling(BME680_OS_2X);
  sensor.setPressureOversampling(BME680_OS_4X);
  sensor.setIIRFilterSize(BME680_FILTER_SIZE_3);
  sensor.setGasHeater(320, 150); // 320*C für 150 Millisekunden
}

void setup() {
  Serial.begin(115200);
  if (!sensor.begin(0x77)) {
    Serial.println("Konnte keinen BME680-Sensor finden.");
    return;
  }
  init_sensor(sensor);

  BLEDevice::init("ESP32-SENSOR");
  BLEServer* server = BLEDevice::createServer();
  server->setCallbacks(new MyServerCallbacks());
  BLEService* service = server->createService(BLEUUID((uint16_t)0x181A));

  humidityDescriptor.setValue("Luftfeuchte 0-100%");
  humidityCharacteristic.addDescriptor(&humidityDescriptor);
  humidityCharacteristic.addDescriptor(new BLE2902());
  service->addCharacteristic(&humidityCharacteristic);

  temperatureDescriptor.setValue("Temperatur -40-125°C");
  temperatureCharacteristic.addDescriptor(&temperatureDescriptor);
  temperatureCharacteristic.addDescriptor(new BLE2902());
  service->addCharacteristic(&temperatureCharacteristic);
  
  service->start();
  server->startAdvertising();
}

void loop() {
  if (bleClientConnected) {
    const uint16_t humidity = sensor.readHumidity() * 100;
    const int16_t temperature = sensor.readTemperature() * 100;
    humidityCharacteristic.setValue((uint8_t*)&humidity, 2);
    humidityCharacteristic.notify();
    temperatureCharacteristic.setValue((uint8_t*)&temperature, 2);
    temperatureCharacteristic.notify();
  }
  delay(500);
}
