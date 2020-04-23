#include "DHT.h" //DHT Bibliothek laden

#define DHTPIN 7 //Der Sensor wird an PIN 2 angeschlossen    

#define DHTTYPE DHT22    // Es handelt sich um den DHT11 Sensor

DHT dht(DHTPIN, DHTTYPE); //Der Sensor wird ab jetzt mit „dth“ angesprochen

void setup() {
    Serial.begin(9600); //Serielle Verbindung starten

    dht.begin(); //DHT11 Sensor starten
}

void loop() {

    delay(2000); //Zwei Sekunden Vorlaufzeit bis zur Messung (der Sensor ist etwas träge)


    float Luftfeuchtigkeit = dht.readHumidity(); //die Luftfeuchtigkeit auslesen und unter „Luftfeutchtigkeit“ speichern

    float Temperatur = dht.readTemperature();//die Temperatur auslesen und unter „Temperatur“ speichern

    Serial.print("Luftfeuchtigkeit: "); //Im seriellen Monitor den Text und 
    Serial.print(Luftfeuchtigkeit); //die Dazugehörigen Werte anzeigen
    Serial.println(" %");
    Serial.print("Temperatur: ");
    Serial.print(Temperatur);
    Serial.println(" Grad Celsius");

}