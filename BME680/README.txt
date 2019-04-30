# BME680-Sensor am ESP32

Einige Beispielprogramme des ESP32-Sonderhefts basieren auf dem HDC1008-Sensor. Weil dieser qualitativ nicht sonderlich gut und auch nur noch schwer erhältlich ist, haben wir alle Beispielprogramme, die diesen Sensor verwenden, an den modernen BME680-Sensor der Firma Bosch angepasst. Zu beziehen ist er unter anderem bei Watterott (https://www.watterott.com/de/BME680-Breakout).

Der BME680 ist ein Umweltsensor, der nicht nur die Umgebungstemperatur und die Luftfeuchtigkeit sondern auch den Luftdruck und die Luftqualität misst. Wie der HDC1008 lässt sich auch der BME680 per I2C ansprechen.

Der Anschluss des BME680 an den ESP32 erfolgt mittels vier Kabeln. VCC kommt an den 3,3V-Anschluss des ESP32 und GND natürlich an GND. Der SCL-Anschluss des BME680 gehört beim ESP32 an GPIO-Pin 22 und SDA an GPIO-Pin 21 (siehe img/esp32_bme680_circuit.png).

Die Beispielprogramme basieren auf der Adafruit_BME680-Bibliothek (https://github.com/adafruit/Adafruit_BME680), die wiederum auf der Adafruit_Sensor-Bibliothek (https://github.com/adafruit/Adafruit_Sensor) aufbaut. Beide müssen daher installiert werden. Das geht zum Beispiel über den Bibliotheksverwalter der Arduino-IDE oder indem man die zu den Bibliotheken gehörenden Zip-Archive manuell im libraries-Verzeichnis der IDE auspackt.

Anschließend lassen sich die WLAN- und Bluetooth-Beispielprogramme wie gehabt übersetzen und auf das ESP32-Board spielen. Sie verhalten sich exakt so wie die Programme, die den HDC1008 verwenden.
