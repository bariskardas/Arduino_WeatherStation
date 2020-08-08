#define BEKLE 3                    //gsm 
#include <Wire.h>     // I2C haberleşme protokolünü sağlamak için
#include <SoftwareSerial.h> // gsm kütüphanesi
SoftwareSerial gsm(10,11); // gsm 10 11 girişleri rx ve tx girişleridir.
#include <Sim800l.h>
String smsMetni = "";
char gelen;


int r ;
int ruz;
int toprak;
int referans;
//int isi = 0;
int sicaklik;
float humi, temp;
int nem;
double bas;

#include <LiquidCrystal_I2C.h>    // lcd  kütüphanesi
LiquidCrystal_I2C lcd(0x27,16,2); // lcd tanımı   0x27 lcd adresi ,16 sütün(karakter) 2 satırdan oluşur
#include <SFE_BMP180.h>           //basınc kütüphanesi
#include <DHT11.h>                //sıcaklık kütüphanesi
#define DHT11PIN 6               // sıcaklık dijital pin 6
DHT11 dht11(DHT11PIN);            // değişken tanımı


SFE_BMP180 pressure;              // basınc değişken

double baseline; // baseline pressure

//toprak sensörü değişkenleri ve analog giriş atama
const int prob = A1;
int olcum_sonucu;


void SMSgonder(String mesaj) {
  
  gsm.print("AT+CMGF=1\r");     // mesaj tipini seç
  delay(100);
  gsm.println("AT+CMGS=\"+905348953105\"");// telefon numarasi degistir   //mesaj gönderme
  delay(100);
  
  gsm.println(mesaj);
  delay(100);
  gsm.println((char)26);
  delay(100);
  gsm.println();
  delay(100);
  gsm.println("AT+CMGD=1,4"); // silmek için
  delay(100);
  gsm.println("AT+CMGF=1");   // mesaj tipini seç
  delay(100);
  gsm.println("AT+CNMI=1,2,0,0,0"); //mesaj geldiğini belirtmek için
  
  delay(200);
  smsMetni = "";
}


void smscoz() {

      while (gsm.available()) {    // available /* Yeni porta gelen bir mesaj var mı */
        delay(BEKLE);
        gelen = gsm.read();
      //-----------------------------------
    
        if (gelen == '#') {
          if (gsm.available()) {
            delay(BEKLE);
    
    lcd.setCursor (0, 1);
                        lcd.print(gelen);
            gelen = gsm.read();
            if (gelen == 'O') {
    lcd.setCursor (1, 1);
                        lcd.print(gelen);
              if (gsm.available()) {
                delay(BEKLE);
    
                gelen = gsm.read();
                if (gelen == 'R') {
    lcd.setCursor (2, 1);
                                lcd.print(gelen);
                  if (gsm.available()) {
                    delay(BEKLE);
                    gelen = gsm.read();
                    if (gelen == 'T') {
    lcd.setCursor (3, 1);
                                        lcd.print(gelen);
                      if (gsm.available()) {
                        delay(BEKLE);
    
                        gelen = gsm.read();
                        if (gelen == 'A') {
    lcd.setCursor (4, 1);
                                                lcd.print(gelen);
                          if (gsm.available()) {
                            delay(BEKLE);
                            gelen = gsm.read();
                            if (gelen == 'M') {
    lcd.setCursor (5, 1);
                                       lcd.print(gelen);

                              if (gsm.available()) {
                                delay(BEKLE);
    
    lcd.setCursor (0, 0);
    lcd.println("ORTAM >>> Rapor ");
    
    lcd.setCursor (6, 1);
                                       lcd.print("         ");
                                      
    
                                gsm.print("AT+CMGF=1\r");
                                delay(100);
                                gsm.println("AT+CMGS=\"+905348953105\"");// telefon numarasi degistir
                                delay(100);
                                
                                gsm.println("Sizin icin Sistem Sonuclari");
                                delay(100);
                                gsm.print("RUZGAR......"); gsm.print(ruz); gsm.println(" m/s");
                                delay(100);
                                gsm.print("Toprak......"); gsm.print(toprak); gsm.println(" %");
                                delay(100);
                                gsm.print("BASINC......"); gsm.print(baseline); gsm.println(" hPa");
                                delay(100);
                                gsm.print("ISI........."); gsm.print(temp); gsm.println(" C");
                                delay(100);
                                gsm.print("Nem........."); gsm.print(humi); gsm.println(" %");
                                gsm.println((char)26);
                                delay(100);
                                gsm.println();
                                delay(100);
                                gsm.println("AT+CMGD=1,4");
                                delay(100);
                                gsm.println("AT+CMGF=1");
                                delay(100);
                                gsm.println("AT+CNMI=1,2,0,0,0");
                                delay(200);
                                smsMetni = "";
                                
                              }  }}}}}}}}}}}
  
 else if (gelen == '*') {
          if (gsm.available()) {
            delay(BEKLE);
    
    lcd.setCursor (0, 1);
                        lcd.print(gelen);
            gelen = gsm.read();
            if (gelen == 'H') {
    lcd.setCursor (1, 1);
                        lcd.print(gelen);
              if (gsm.available()) {
                delay(BEKLE);
    
                gelen = gsm.read();
                if (gelen == 'O') {
    lcd.setCursor (2, 1);
                                lcd.print(gelen);
                  if (gsm.available()) {
                    delay(BEKLE);
                    gelen = gsm.read();
                    if (gelen == 'C') {
    lcd.setCursor (3, 1);
                                        lcd.print(gelen);
                      if (gsm.available()) {
                        delay(BEKLE);
    
                        gelen = gsm.read();
                        if (gelen == 'A') {
    lcd.setCursor (4, 1);
                                                lcd.print(gelen);
                          if (gsm.available()) {
                            delay(BEKLE);
                            gelen = gsm.read();
                            if (gelen == 'M') {
    lcd.setCursor (5, 1);
                                       lcd.print(gelen);


          if (gsm.available()) {
                                delay(BEKLE);
    
    lcd.setCursor (0, 0);
    lcd.println("Hocam >>>> Rapor");
    lcd.setCursor (7, 1);
                                       lcd.print("         ");
    
             gsm.print("AT+CMGF=1\r");
             delay(100);
             gsm.println("AT+CMGS=\"+905348953105\"");// telefon numarasi degistir
             delay(100);
             gsm.println("Merhaba Hocam Sizin icin Sistem Sonuclari");
             delay(100);
             gsm.print("RUZGAR......"); gsm.print(ruz); gsm.println(" m/s");
             delay(100);
             gsm.print("Toprak......"); gsm.print(toprak); gsm.println(" %");
             delay(100);
             gsm.print("BASINC......"); gsm.print(baseline); gsm.println(" hPa");
             delay(100);
             gsm.print("ISI........."); gsm.print(temp); gsm.println(" C");
             delay(100);
             gsm.print("Nem........."); gsm.print(humi); gsm.println(" %");
             gsm.println((char)26);
            delay(100);
            gsm.println();
            delay(100);
            gsm.println("AT+CMGD=1,4");
            delay(100);
            gsm.println("AT+CMGF=1");
            delay(100);
            gsm.println("AT+CNMI=1,2,0,0,0");
            delay(200);
            smsMetni = "";
                              } } } }}}}}}}}}}}



void setup()
{

if (pressure.begin())   // basınc sensörü çalışma kontrolü
    Serial.println("BMP180 init success");
  else
  {
    Serial.println("BMP180 init fail (disconnected?)\n\n");
    while(1); // Pause forever.
  }
 
    
lcd.init();           // lcd ekranı başlatmak için söndürür 
lcd.backlight();      // lcd ekranın ışığını açar 
lcd.begin(16,2);      // 16x2 lik lcd yi başlatır
  Serial.begin(9600); // PC Seri haberleşme başlangıç baud hızı
  while (!Serial) {
      ; 
    } 

 lcd.setCursor (0, 0);     // (sütun,satır) 1.sütun 1.satır diye geçer
    lcd.println("  AKILLI  HAVA  ");  // lcd ye yazı yazma
    lcd.setCursor (0, 1);    // 1.sütun 2.satır
    lcd.println("   ISTASYONU     ");
    delay (5000);   // 5 saniye bekler
    lcd.clear();    // lcd'deki verileri temizler


  pinMode(7, OUTPUT);
    digitalWrite(7, HIGH);
    delay(100);
    digitalWrite(7, LOW);
    gsm.begin(9600);
    delay(100);
    gsm.println("AT+CMGF=1");
    delay(100);
    gsm.println("AT+CNMI=1,2,0,0,0");
    delay(100);
    gsm.println("AT+CMGD=1,4");
    delay(100);
    SMSgonder("Cihaz ile baglanti kuruldu");


    delay(100);

    gsm.flush();

}



void loop()
{
  
smscoz();
  
  baseline = getPressure();  
  double a,P;
  P = getPressure();
  a = pressure.altitude(P,baseline);
 
  delay(100);
  
for (int say = 0; say < 1; say++)
    {
      smscoz();
      
    //sıcaklık ve nem değişkenleri oluştur  
dht11.read(humi, temp);  //değişkenlerdeki veriyi oku
lcd.setCursor(0,0);      //lcd ye yazdırma
lcd.print("TEMP:");
lcd.print(temp);
lcd.print(" C");
Serial.print("TEMP:");   //seri port ekranına yazdırma
Serial.print(temp);
Serial.println();

lcd.setCursor(0,1);      //lcd ye yazdırma
lcd.print("NEM:");
lcd.print(humi);
lcd.print(" %");
Serial.print("NEM:");
Serial.print(humi);
Serial.println();

delay(4000);
}

lcd.clear();

for (int sayim = 0; sayim < 40; sayim++)
    {
      smscoz();
      olcum_sonucu = analogRead(prob);
      toprak = map(abs(olcum_sonucu), 0, 1024, 99, 0);

lcd.setCursor(0,0);
  lcd.print("TOPRAK:");
  lcd.print(toprak);
   lcd.print(" %");
   
  Serial.print("TOPRAK:");
  Serial.print(toprak);
  Serial.println();

lcd.setCursor(0,1);  
lcd.print("BASINC:");
    lcd.print(baseline,1);
    lcd.print("hPa");
   Serial.print("BASINC:");
  Serial.print(baseline);
  Serial.println();
  delay(100);
}
lcd.clear();


/*int sensorValue = analogRead(A2);
  //Map 0-1023 to discrete 0-50-100...250 values for LED
  analogWrite(0, sensorValue * (51.0 / 1023.0) * 50);
  
  if(sensorValue >= 0){
    lcd.setCursor(0,0);  
    lcd.print("RUZGAR:");
    lcd.print(sensorValue);
    lcd.print(" m/s");
     Serial.print("RUZGAR:");
     Serial.print(sensorValue);
     Serial.println(" m/s");
     Serial.println();
     
  }
*/

for (int say = 0; say < 40; say++)
    {
  int ruzsensoru = analogRead(A2);
      r = map(abs(ruzsensoru), 0, 410, 0.0, 70.0);
      ruz = (float)ruzsensoru / 5.85;
      if (ruz < 0.2)
      {
        ruz = 0;
      }

      lcd.setCursor(0, 0);

      lcd.print("Ruzgar: ");
      lcd.print(ruz);
      lcd.print(" m/s");
      Serial.print("RUZGAR:");
     Serial.print(ruz);
     Serial.println(" m/s");

      delay(100);
    }
    lcd.clear();
smscoz();
}


double getPressure()
{
  char status;
  double T,P,p0,a;

  status = pressure.startTemperature();
  if (status != 0)
  {
   
    delay(status);

    status = pressure.getTemperature(T);
    if (status != 0)
    {  
      status = pressure.startPressure(3);
      if (status != 0)
      {
        delay(status);
        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}
