#include <WiFi.h> // WiFi bağlantısı için gerekli kütüphane
#include <PubSubClient.h> // MQTT protokolü için gerekli kütüphane


// WiFi Ayarları
const char* ssid = "Wokwi-GUEST"; // WiFi SSID
const char* password = ""; // WiFi şifresi

// MQTT Broker Bilgileri
const char* mqtt_server = "test.mosquitto.org"; // MQTT sunucusunun adresi
const char* clientID = "ESP32-wokwi"; // MQTT istemci kimliği

// WiFi ve MQTT Nesneleri
WiFiClient espClient; // WiFi istemci nesnesi
PubSubClient client(espClient); // PubSubClient nesnesi, MQTT için kullanılır


const int echo= 18 ; // HC-SR04 Ultrasonic Mesafe Sensörü Bağlantısı
const int trig= 5 ; // HC-SR04 Ultrasonic Mesafe Sensörü Bağlantısı

const int pir =19; // PIR Sensörü Bağlantısı

const int RED = 16 ; // LED Bağlantısı
const int GREEN = 4 ; // LED Bağlantısı
const int BLUE = 0 ; // LED Bağlantısı

int LED_DURUM = 0; // Node-red platformunda bulunan butonun tıklanma durumuna göre LED_DURUM değişmektedir.

void setup_wifi() { // WiFi bağlantısını başlat
  delay(10);
  WiFi.begin(ssid, password); // WiFi ağına bağlanmak için SSID ve şifreyi kullan

  while (WiFi.status() != WL_CONNECTED) { // WiFi durumunu kontrol et
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnect() { // MQTT bağlantısı kurulana kadar tekrar dene
  while (!client.connected()) {
    if (client.connect(clientID)) { // MQTT sunucusuna bağlanmayı dene
      Serial.println("MQTT connected");
      client.subscribe("21100011016/Buton"); // İstemci "21100011016/Buton" konusu ile abone oldu.
      client.subscribe("21100011016/mesafe"); // İstemci "21100011016/mesafe" konusu ile abone oldu.
      
      client.publish("21100011016/mesafe", "0.0"); // İstemci "21100011016/mesafe konusuna 0.0 mesajı yayınladı.
    } else {
      Serial.print("failed, rc="); 
      Serial.print(client.state()); // Bağlantı başarısızsa hata kodunu yazdır
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {   // Mesaj geldiğinde çalışacak geri çağırma fonksiyonu
        
  String data= ""; // Gelen veriyi tutmak için değişken
  
  for (int i = 0; i < length; i++) { // Gelen veriyi "data"e ekle
    data += (char)payload[i];
  }

  if (String(topic) == "21100011016/Buton") { // data'nın 21100011016/Buton konusundan geliği durumda true olur.
    Serial.print("LED --> ");
    Serial.println(data); // gelen "data" yazdırılır

    if (data == "ON") { // Gelen veri "ON" ise LED_DURUM'u 0 yap
      LED_DURUM = 0;

    } else if (data == "OFF") { // Gelen veri "OFF" ise LED_DURUM'u 1 yap
      LED_DURUM = 1;

    }
  }
}


void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");

  pinMode(echo, INPUT); // pin durumunu INPUT/OUTPUT olarak ayarla.
  pinMode(trig, OUTPUT); // pin durumunu INPUT/OUTPUT olarak ayarla.

  pinMode(pir, INPUT); // pin durumunu INPUT/OUTPUT olarak ayarla.

  pinMode(RED, OUTPUT); // pin durumunu INPUT/OUTPUT olarak ayarla.
  pinMode(GREEN, OUTPUT); // pin durumunu INPUT/OUTPUT olarak ayarla.
  pinMode(BLUE, OUTPUT); // pin durumunu INPUT/OUTPUT olarak ayarla.

  setup_wifi(); // WiFi bağlantısını kurmak için setup_wifi fonksiyonunu çağır
  client.setServer(mqtt_server, 1883); // MQTT sunucusunu ve port numarasını ayarla
  client.setCallback(callback); // Gelen mesajlar için geri çağırma fonksiyonunu ayarla


}

void loop() {

  if (!client.connected()) { // MQTT istemcisi bağlı değilse, yeniden bağlanmayı dene
    reconnect();
  }
  client.loop(); // MQTT istemcisi döngüsünü çalıştır, gelen mesajları dinler ve bağlantıyı yönetir

  int pirSensor = digitalRead(pir); // PİR sensör hareket algıladı mı?

  digitalWrite(trig, LOW); // Trig pine düşük değer verilir.
  delay(2); // 2 mikrosaniye bekletildi.
  digitalWrite(trig, HIGH); // Trig pine yüksek değer verilir.
  delay(10); // 10 mikrosaniye bekletildi.
  digitalWrite(trig, LOW); // Trig pine düşük değer verilir.
  
  int x = pulseIn(echo, HIGH); // Yüksek seviyedeki echo sinyallerinin süresi ölçüldü.
  int distance=(0.034*x)/2; //  Hareket sensörü hesaplama

  char mesaj[50];
  snprintf(mesaj, 50, "%d", distance);
  client.publish("21100011016/mesafe", mesaj); // Mesajı MQTT ile yayınla

  if (pirSensor == HIGH) // PİR sensör hareket algıladı mı?
  {
    Serial.println("PIR sensoru hareket algiladi");
    
    if (distance >= 0 && distance <= 50 ) // Hareket sensörü 0<=x<=50 arasında mı
    {
      Serial.println("PIR sensoru hareket algiladi ve Mesafe Sensoru 0 ile 50 cm arasinda");

      if(LED_DURUM == 0) // LED_DURUM = 0 ise LED i 250 ms aralıklarla yakıp söndür.
      {

        digitalWrite(RED, HIGH); // LED YANAR
        digitalWrite(GREEN, HIGH); // LED YANAR
        digitalWrite(BLUE, HIGH); // LED YANAR
        delay(250);

        digitalWrite(RED, LOW); // LED SÖNER
        digitalWrite(GREEN, LOW); // LED SÖNER
        digitalWrite(BLUE, LOW); // LED SÖNER
        delay(250);
      }

      
    }
  }
}