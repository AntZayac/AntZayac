#include <SoftwareSerial.h>
#include <Adafruit_PWMServoDriver.h>

SoftwareSerial BlSerial(7, 6); // RX, TX

// По умолчанию модуль доступен по адресу I2C 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

unsigned long tmg_0, tmg_1, tmg_2, tmg_3, tmg_4, tmg_5,tmg_6;
bool butt_0, butt_1, butt_2, flag_0, flag_1,  flag_2, svet_stol_20, svet_stol, svet, svet_lustra, svet_potoilok, svet_krov;
int rr, schot_0, schot_1, schot_2, kns_0, kns_1, skor_zatuh_led, iarcost, sinii_potolok, kras_potolok, zel_potolok, sinii_krov, kras_krov, zel_krov, dest = 3, skor_rgb = 20, svet_100;
bool rgb;
int ii=1;


void setup() {

  pwm.begin();
  pwm.setPWMFreq(90);  // Частота следования импульсов 300 Гц


  pinMode (5, OUTPUT); //реле
  pinMode (4, INPUT); //кнопка дверь
  pinMode (3, INPUT); //кнопка стол
  pinMode (2, INPUT); //кнопка окно


  Serial.begin(9600);
  BlSerial.begin(9600);

}

void loop() {
  if (rr != 666) {
    // 4095
    /** тут будут сщитаться нажатия кнопок и по их результатам общей переменной
        будет присваиватьсяопред цифра которая будет отвечать за работу того или иного
        элемента освещения
    */
    butt_0 = digitalRead (3);
    butt_1 = digitalRead (4);
    butt_2 = digitalRead (2);

    rr = 0;




    //этот блок отвечает за кнопку у стола
    if (butt_0 == 0) // этот флаг нуженд ля того чтоб один раз нажатая кнопка не считалась несколько раз за несколко итерации
      flag_0 = 0;

    if ((butt_0 == 1) and (flag_0 == 0)) { //тут ведём подщёт нажатий и обнуляем таймер считывания нажатий
      schot_0++;
      flag_0 = 1;
      tmg_0 = millis();
    }

    if (millis() - tmg_0 > 280) { //тут считываем кол нажатиё в общюю переменную и пускаем её через весь код
      rr = schot_0;
      schot_0 = 0;
    }

    if ((millis() - tmg_0 > 280) and (butt_0 == 1))// тут после долгого нажатия на кнопуку выдаётся соответствующи цифра
      rr = 6;
    if ((millis() - tmg_0 > 3000) and (butt_0 == 1))// тут после долгого нажатия на кнопуку выдаётся соответствующи цифра
      rr = 666;




    //этот блок отвечает за кнопку у двери
    if (butt_1 == 0) // этот флаг нуженд ля того чтоб один раз нажатая кнопка не считалась несколько раз за несколко итерации
      flag_1 = 0;

    if ((butt_1 == 1) and (flag_1 == 0)) { //тут ведём подщёт нажатий и обнуляем таймер считывания нажатий
      schot_1++;
      flag_1 = 1;
      tmg_1 = millis();
    }

    if (millis() - tmg_1 > 280) { //тут считываем кол нажатиё в общюю переменную и пускаем её через весь код
      kns_0 = schot_1;
      schot_1 = 0;
    }

    if ((millis() - tmg_1 > 280) and (butt_1 == 1))// тут после долгого нажатия на кнопуку выдаётся соответствующи цифра
      kns_0 = 6;


    if (kns_0 == 1)
      rr = 5;
    if (kns_0 == 2)
      rr = 4;
    if (kns_0 == 3)
      rr = 3;
    if (kns_0 == 4)
      rr = 1;
    if (kns_0 == 6)
      rr = 6;

    if ((millis() - tmg_1 > 3000) and (butt_1 == 1)) {
      rr = 666 ;
    }




    // этот блок отвечает за кнопку у окна
    if (butt_2 == 0) // этот флаг нуженд ля того чтоб один раз нажатая кнопка не считалась несколько раз за несколко итерации
      flag_2 = 0;

    if ((butt_2 == 1) and (flag_2 == 0)) { //тут ведём подщёт нажатий и обнуляем таймер считывания нажатий
      schot_2++;
      flag_2 = 1;
      tmg_2 = millis();
    }

    if (millis() - tmg_2 > 280) { //тут считываем кол нажатиё в общюю переменную и пускаем её через весь код
      kns_1 = schot_2;
      schot_2 = 0;
    }

    if ((millis() - tmg_2 > 280) and (butt_2 == 1))// тут после долгого нажатия на кнопуку выдаётся соответствующи цифра
      kns_1 = 6;

    if ((millis() - tmg_2 > 3000) and (butt_2 == 1))
      rr = 666;

    if (rr == 0) {
      if (kns_1 == 1)
        rr = 4;
      if (kns_1 == 2)
        rr = 3;
      if (kns_1 == 3)
        rr = 1;
      if (kns_1 == 4)
        rr = 5;
      if (kns_1 == 6)
        rr = 6;
    }



    // тут реализовано общение телефона по блюпупу
    if (BlSerial.available() > 0) {
      char i = BlSerial.read();

      if (i == '1')
        rr = 1;

      if (i == '2')
        rr = 2;

      if (i == '3')
        rr = 3;

      if (i == '4')
        rr = 4;

      if (i == '5')
        rr = 5;

      if (i == '6')
        rr = 6;

      if (i == 'r')
        rgb = !rgb;



      if (i == '?') {
        BlSerial.println("1-свет стол 100%");
        BlSerial.println("2-свет стол 30%");
        BlSerial.println("3-свет потолок");
        BlSerial.println("4-свет кровать");
        BlSerial.println("5-свет люстра");
        BlSerial.println("остальное сам подбирай!");
      }
    }




    //ВКЛ. И ВЫКЛ. СВЕТА НАД СТОЛОМ
    if (rr == 1)
      svet_stol = !svet_stol;

    if (svet_stol == 0) {
      if (millis() - tmg_3 > skor_zatuh_led) {    //затухание бел. ленты над столом
        tmg_3 = millis();
        if (iarcost > 20) {
          skor_zatuh_led = 1;
          iarcost = iarcost - 2;
        }
        if (iarcost > 5 && iarcost <= 20) {
          skor_zatuh_led = 5;
          iarcost--;
        }
        if (iarcost > 0 && iarcost <= 5) {
          skor_zatuh_led = 10;
          iarcost--;
        }
      }
    }
    else {            //возростание яркости до 255, белой ленты над столом
      svet_stol_20 = 0;
      if (millis() - tmg_3 > 1) {
        tmg_3 = millis();
        if (iarcost < 255) {
          iarcost = iarcost + 2;
        }
      }
    }

    //СВЕТ НАД СТОЛОМ В ПОЛ НАКАЛА ПО 2-ОМУ НАЖАТИЮ
    if (rr == 2)
      svet_stol_20 = !svet_stol_20;

    if (svet_stol_20 == 1) {
      svet_stol = 0;
      if (millis() - tmg_3 > 1) {
        tmg_3 = millis();
        if (iarcost < 50)
          iarcost++;
        else
          iarcost--;
      }
    }


    pwm.setPWM(0, 0, map (iarcost, 0, 256, 0, 4095));


    
    if (rgb == 0) {
  
      // свет лента по потолок
      if (rr == 3)
        svet_potoilok = !svet_potoilok;

      if (svet_potoilok == 1) {
        if (millis() - tmg_4 > 1) {
          tmg_4 = millis();
          if (sinii_potolok < 100) //почему 252? да просто захотел так
            sinii_potolok++;
        }
        kras_potolok = sinii_potolok;
        zel_potolok = sinii_potolok;
      }
      else {
        if (millis() - tmg_4 > 1) {
          tmg_4 = millis();
          if (sinii_potolok > 0)
            sinii_potolok--;
        }
        kras_potolok = sinii_potolok ;
        zel_potolok = sinii_potolok ;
      }


      //RGB ПОД КРОВАТЬЮ
      if (rr == 4)
        svet_krov = !svet_krov;


      if (svet_krov == 1) {
        if (millis() - tmg_5 > 1) {
          tmg_5 = millis();
          if (sinii_krov < 100) //почему 100? да просто захотел так
            sinii_krov++;
        }
        kras_krov = sinii_krov;
        zel_krov = sinii_krov;
      }
      else {
        if (millis() - tmg_5 > 1) {
          tmg_5 = millis();
          if (sinii_krov > 0)
            sinii_krov--;
        }
        kras_krov = sinii_krov;
        zel_krov = sinii_krov ;
      }


    }
    else if (rgb == 1) {

      if ((millis() - tmg_6 > 10) and (kras_potolok < 100) and (ii == 1)) {
        tmg_6 = millis();
        kras_potolok++;
      }
      else if (kras_potolok == 100)
        ii = 2;

 Serial.println (millis() - tmg_5);

      if ((millis() - tmg_4 > 1) and (zel_potolok > 0) and (ii == 2)) {
        zel_potolok--;
        tmg_4 = millis();
      }
      else
        ii = 3;

      if ((millis() - tmg_5 > 1) and (sinii_potolok < 100) and (ii == 3)) {
        sinii_potolok++;
        tmg_5 = millis();
      }
      else
        ii = 4;

      if ((millis() - tmg_4 > 1) and (kras_potolok > 0) and (ii == 4)) {
        kras_potolok--;
        tmg_4 = millis();
      }
      else
        ii = 5;

      if ((millis() - tmg_5 > 1) and (zel_potolok < 100) and (ii == 5)) {
        zel_potolok++;
        tmg_5 = millis();
      }
      else
        ii = 6;

      if ((millis() - tmg_4 > 1) and (sinii_potolok > 0) and (ii == 6)) {
        sinii_potolok--;
        tmg_4 = millis();
      }
      else
        ii = 1;
    }
    pwm.setPWM(1, 0, map(kras_potolok, 0, 100, 0, 4095));
    pwm.setPWM(2, 0, map(zel_potolok, 0, 100, 0, 2500));
    pwm.setPWM(3, 0, map(sinii_potolok, 0, 100, 0, 2000));

    pwm.setPWM(4, 0, map(kras_krov, 0, 100, 0, 4095));
    pwm.setPWM(5, 0, map(zel_krov, 0, 100, 0, 2500));
    pwm.setPWM(6, 0, map(sinii_krov, 0, 100, 0, 2500));







    // ЛЮСТРА СВЕТ ВКЛ. ВЫКЛ.
    if (rr == 5)
      svet_lustra = !svet_lustra;
    digitalWrite (5, svet_lustra);


    //OБЩЕЕ ВЫКЛЮЧЕНИЕ СВЕТА
    if (rr == 6)
      svet = !svet;
    if (svet == 1) {
      svet_stol = 0;
      svet_stol_20 = 0;
      svet = 0;
      svet_lustra = 0;
      svet_potoilok = 0;
      svet_krov = 0;
    }



    pwm.setPWM(15, 0, 4095 );
  }
  if (rr == 666) {

    pwm.setPWM(0, 0, 0);
    pwm.setPWM(1, 0, 0);
    pwm.setPWM(2, 0, 0);
    pwm.setPWM(3, 0, 0);
    pwm.setPWM(4, 0, 0);
    pwm.setPWM(5, 0, 0);
    pwm.setPWM(6, 0, 0);
    pwm.setPWM(7, 0, 0);
    pwm.setPWM(8, 0, 0);
    pwm.setPWM(9, 0, 0);
    pwm.setPWM(10, 0, 0);
    pwm.setPWM(11, 0, 0);
    pwm.setPWM(12, 0, 0);
    pwm.setPWM(15, 0, 0);
    pwm.setPWM(14, 0, 0);
    digitalWrite (5, 0);
    //  это на случай если кнопики забагуют
    pwm.setPWM(13, 0, 4095);  //  и будут нажаты дольше 3 секуед
    delay (700);             //  код уёдётв защиту поставит всё на ноль
    pwm.setPWM (13, 0, 0) ;    //  и будет мигать красным в каробке
    delay (700);             //
  }
}
