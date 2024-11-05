# IoT Projesi - ESP32 ile PIR ve Ultrasonik Sensör Kullanımı

Bu proje, ESP32 geliştirme kartı, PIR Hareket Sensörü, Ultrasonik Mesafe Sensörü, RGB LED ve Node-RED platformu kullanılarak tasarlanmış bir Nesnelerin İnterneti (IoT) uygulamasıdır. Proje, sensör verilerini MQTT protokolü kullanarak Node-RED üzerinden izlemeyi ve kontrol etmeyi sağlar.

## Kullanılan Bileşenler
- **ESP32**: Merkezi kontrol birimi olarak kullanılmıştır.
- **PIR Hareket Sensörü**: Hareket algılama işlevi görür.
- **Ultrasonik Mesafe Sensörü (HC-SR04)**: Mesafe ölçümleri yapmak için kullanılır.
- **RGB LED**: Durum göstergesi olarak görev yapar.
- **Dirençler**: LED bağlantıları için kullanılmıştır.
- **BreadBoard**: Devre elemanlarının bağlantısını kolaylaştırır.
- **Node-RED**: Sensör verilerini görselleştirmek ve kontrol etmek için kullanılan platform.
- **Mosquitto MQTT Broker**: ESP32 ve Node-RED arasında veri iletişimi için kullanılır.

## Projenin İşleyişi
1. **Hareket Algılama**: PIR sensörü hareket algıladığında, ESP32 üzerindeki kod çalışarak mesafe sensörünü devreye sokar.
2. **Mesafe Ölçümü**: Ultrasonik sensör 0-50 cm arasında bir mesafe ölçtüğünde, RGB LED 250 ms aralıklarla yanıp söner.
3. **MQTT İletişimi**: Ölçülen mesafe değerleri MQTT üzerinden Mosquitto broker'a gönderilir ve Node-RED'de gösterilir.
4. **Node-RED Dashboard**: Dashboard üzerinde mesafe sensörünün verileri ve bir kontrol butonu bulunur. Bu buton, LED'in davranışını kontrol eder.

## Devre Bağlantıları
- **ESP32**:
  - 5V: BreadBoard'un besleme hattına
  - GND: BreadBoard'un toprak hattına
- **PIR Sensörü**:
  - VCC: BreadBoard'un besleme hattına
  - GND: BreadBoard'un toprak hattına
  - OUT: ESP32'nin dijital pinine
- **Ultrasonik Sensör (HC-SR04)**:
  - VCC: BreadBoard'un besleme hattına
  - GND: BreadBoard'un toprak hattına
  - TRIG: ESP32'nin dijital pinine
  - ECHO: ESP32'nin dijital pinine
- **RGB LED**:
  - R, G, B pinleri: ESP32'nin dijital pinlerine dirençler aracılığıyla bağlanır
  - COM: BreadBoard'un toprak hattına

## Kurulum Talimatları
1. Wokwi simülasyon linkine [buradan](https://wokwi.com/projects/399671421782657025) ulaşarak projeyi çalıştırın.
2. Node-RED'i bilgisayarınıza kurun ve çalıştırın. Node-RED kurulumu için [buradan](https://nodered.org/docs/getting-started/) yararlanabilirsiniz.
3. Node-RED üzerinde `21100011016-Flows.json` dosyasını import edin.
4. Simülasyonu başlatın ve terminalde "Wi-Fi connected" ve "MQTT connected" mesajlarını gördükten sonra, PIR sensörü üzerinde "simulate motion" seçeneği ile hareket simüle edin.
5. Ultrasonik sensör üzerinden mesafe değerini değiştirerek LED'in yanıp sönme durumunu gözlemleyin.
6. Node-RED Dashboard'da sensör verilerini ve kontrol butonunu kullanarak LED'in davranışını ayarlayın.

## Kullanılan Kütüphaneler
- **PubSubClient**: MQTT iletişimi için kullanılır.
- **WiFi**: ESP32'nin Wi-Fi bağlantısını sağlamak için kullanılır.

## Node-RED ve Simülasyon
- **Node-RED Dashboard**: Mesafe sensörünün verilerini bir gauge göstergesi ile görüntüler. LED'in kontrolünü sağlayan bir switch bulunmaktadır.
- **Wokwi Simülasyonu**: Wokwi platformunda, ESP32 ve sensör devreleri simüle edilir ve sistemin çalışma prensipleri gözlemlenir.

## Referanslar ve Kaynaklar
1. [PIR Sensör Devresi](https://wokwi.com/projects/375773184726322177)
2. [Ultrasonik Sensör Devresi](https://wokwi.com/projects/360523796394304513)
3. [RGB LED Devresi](https://wokwi.com/projects/394570674947171329)
4. [Node-RED Dashboard Kurulumu](https://flows.nodered.org/node/node-red-dashboard)
5. [MQTT ile Veri Alışverişi](https://www.youtube.com/watch?v=lEXQ9w1z7Aw&list=PLGlKxZrcyaVDFqdtvZwfy326rurYZovuO&index=13)

## Notlar
- Node-RED Dashboard'da oluşabilecek gecikmeler, Wokwi simülasyon platformu kaynaklı olabilir.
- Kodunuzun her satırı, ne işe yaradığına dair açıklamalar içermelidir.
