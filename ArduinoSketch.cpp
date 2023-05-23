#include <SPI.h>
#include <Ethernet.h>
#include <iarduino_RTC.h>
//#include <SD.h>
iarduino_RTC time(RTC_DS1307);
#include <TM1637Display.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0x57, 0x57 };  //mac адрес сетевой карты Ethernet-шилда
IPAddress ip(192, 168, 157, 157);                     //ip сетевой карты
EthernetServer server(80);                            //имя и порт web-сервера

//Пины подключения дисплея
#define CLK 2
#define DIO 3
TM1637Display display(CLK, DIO);

#define DHTPIN 5  // Digital pin connected to the DHT sensor
#define DHTTYPE DHT21
DHT dht(DHTPIN, DHTTYPE);

OneWire oneWire(4);              //Пин датчиков температуры DS18B20 - digital 4
DallasTemperature ds(&oneWire);  //Передать ссылку на oneWire библиотеке DallasTemperature

unsigned long timing = 0;  //Переменная для хранения точки отсчета времени

void setup() {
  Ethernet.begin(mac, ip);
  server.begin();
  time.begin();
  ds.begin();
  dht.begin();
  //time.settime(0, 02, 14, 04, 2, 23, 5);  //Настройка времени - 0  сек, 05 мин, 17 час, 28, янв, 2023 год, суббота

  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
  display.setBrightness(0x0f);  //Задать яркость дисплея
}

void loop() {
  float h, t, hic;
  if (timing == 0 || millis() - timing > 600000) {  //если timing равен 0 (только что включили ардуинку) или больше 10 минут, то...
    timing = millis();
    ds.requestTemperatures();                       //...запрашиваем температуру с датчиков DS
    display.showNumberDec(ds.getTempCByIndex(0));   // вывод температуры на дисплей
    h = dht.readHumidity();                   // Read humidity with DHT21
    t = dht.readTemperature();                // Read temperature as Celsius with DHT21
    hic = dht.computeHeatIndex(t, h, false);  // Compute heat index in Celsius with DHT21
  }

  EthernetClient client = webserver.available();
  client.println("HTTP/1.1 200 OK");
  client.println("Connection: close");
  client.println();
  client.println("<!DOCTYPE HTML><html><head>");
  client.println("<meta http-equiv='refresh' content='60';><meta http-equiv='Content-Type' content='text/html;charset=UTF-8'>");
  client.println("<style> h3 {margin-bottom: -15px;}</style>");
  client.println("<title>Smart House</title></head><body align='center'>");
  client.println("<h3><font face='Arial'>");
  client.println(time.gettime("d.m.Y"));
  client.println("</h3>");
  client.println("<h1>");
  client.println(time.gettime("H:i"));
  client.println("</font></h1>");
  client.println("<p><font size='55' color='red' face='Arial Black'>");
  client.println(ds.getTempCByIndex(0));
  client.println("&#176;C");
  client.println("</font></p>");
  client.println("<h3><font face='Arial'>");
  client.println("Ощущается как");
  client.println("</font></h3>");
  client.println("<p><font size='55' color='red' face='Arial Black'>");
  client.println(hic);
  client.println("&#176;C");
  client.println("</font></p>");
  client.println("<h3><font face='Arial'>");
  client.println("Влажность");
  client.println("</font></h3>");
  client.println("<p><font size='55' color='red' face='Arial Black'>");
  client.println(h);
  client.println("%");
  client.println("</font></p>");
  client.println("<p><font size='55' color='red' face='Arial Black'>");
  client.println(t);
  client.println("&#176;C");
  client.println("</font></p>");
  client.println("</body></html>");
  client.stop();
}
