# 🏠 Pametna kuća

Ovaj repozitorij sadrži izvorni C++ kod za maturski rad na temu automatizacije pametne kuće pomoću **ESP32-S3** mikrokontrolera. Sistem je dizajniran da demonstrira osnove **ugrađenih sistema (Embedded Systems) i kućne automatizacije** kroz tri nezavisna podsistema koji se izvršavaju paralelno i donose odluke u realnom vremenu na osnovu senzorskih očitavanja.

## ✨ Glavne funkcionalnosti

* 🌧️ **Pametni štrik (Zaštita od kiše):** Koristi senzor kiše za detekciju padavina. Kada kiša počne, sistem automatski aktivira servo motor koji uvlači mehanizam štrika pod strehu krova, štiteći veš. Kada se vrijeme razvedri, štrik se vraća u početni položaj.
* 💡 **Pametna rasvjeta:** Oslanja se na fotootpornik (LDR) koji mjeri nivo ambijentalne svjetlosti. Kada padne mrak (ili vrijednost senzora pređe zadani prag), unutrašnja LED rasvjeta se automatski uključuje.
* 🚨 **Laserski sigurnosni alarm:** Koristi precizni **VL53L0X Time-of-Flight (ToF)** laserski senzor. Ako objekat ili osoba priđu na udaljenost manju od 1 metra, aktivira se prodorna zvučna signalizacija (zujalica). Alarm ostaje aktivan sve dok se ne pritisne hardverski taster za resetovanje.

## 🛠️ Korišteni hardver

* **Mikrokontroler:** ESP32-S3 Dev Module
* **Senzor udaljenosti:** VL53L0X (I2C komunikacija)
* **Senzor padavina:** Modul senzora za kišu (Digitalni izlaz)
* **Senzor svjetlosti:** Fotootpornik (LDR) u formi naponskog djelitelja
* **Aktuator:** Micro Servo motor (SG90)
* **Ostalo:** Aktivna zujalica (Buzzer), LED dioda, taster (Push button)
* **Napajanje:** USB (3.3V logika za ESP32) + Eksterna 9V baterija uz Step-down konverter na 5V za napajanje servo motora.

## 💻 Potreban softver i biblioteke

Za prebacivanje koda na mikrokontroler potrebno je koristiti **Arduino IDE**.
Prije kompajliranja koda, potrebno je instalirati sljedeće biblioteke putem *Library Managera*:

1.  `ESP32Servo` - za kontrolu PWM signala servo motora na ESP arhitekturi.
2.  `Adafruit_VL53L0X` - za I2C komunikaciju sa laserskim senzorom.

Također, u *Board Manageru* mora biti instaliran **ESP32 by Espressif Systems** paket, a kao ploča odabran **ESP32S3 Dev Module**.

## 🚀 Instalacija i pokretanje

1. Klonirajte ovaj repozitorij na svoj računar:
   ```bash
   git clone https://github.com/TvojUsername/TvojRepozitorij.git
   ```
2. Otvorite fajl `objedinjeno_strik_svjetlo_alarm.ino` u Arduino IDE.
3. Povežite ESP32-S3 sa računarom putem USB kabla.
4. Odaberite tačan COM port.
5. Kliknite na dugme **Upload**.
6. Otvorite **Serial Monitor** (Baud rate: 115200) za praćenje statusa sistema u realnom vremenu.

## 🎓 O autoru

Ovaj projekat je kreiran u sklopu maturskog rada.
**Autor:** Sara Omerović
**Predmet:** Napredna primijenjena informatika 
**Ustanova:** JU Četvrta gimnazija Ilidža

