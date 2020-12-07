​/*
www.domirobot.com
16x2 LCD Ekran
Aralık 2016
@2016, All Rights Reserved
@2016 Tüm Hakları Saklıdır. */
#include <Servo.h>
const int pwmA=6;
const int geriA=7;
const int pwmB=3;
const int geriB=2;
const int tarayici=A3;
const int sag=A0;
const int orta=A1;
const int sol=A2;
int ilk=1,i=0;
int pos;
int possol=150,possag=70;
int engel;
int saggoz,ortagoz,solgoz;
Servo kasasag;
Servo kasasol;
Servo kiskacsag;
Servo kiskacsol;
Servo kaldirac;
Servo tarama;

void setup() 
{
pinMode(tarayici,INPUT);
pinMode(pwmA,OUTPUT);
pinMode(geriA,OUTPUT);
pinMode(pwmB,OUTPUT);
pinMode(geriB,OUTPUT);

kasasag.attach(10);
kasasol.attach(11);
kiskacsag.attach(13);
kiskacsol.attach(A4);
kaldirac.attach(9);
tarama.attach(5);
}

void loop() 
{
if(ilk==1)
{
kiskacsag.write(70);
kiskacsol.write(170);
delay(3000);
kaldirac.write(60);
delay(3000);
kasasag.write(155);
kasasol.write(30);
delay(3000);
ilk=0;
}

for(pos=90;pos<=112;pos+=2)
{
    engel=digitalRead(tarayici);//   mesafe sensoru algılama yapar
    delay(1);    

    saggoz=analogRead(sag);//        cizgi sensörü algılama yapar
    ortagoz=analogRead(orta);
    solgoz=analogRead(sol);
    delay(1);
    
    digitalWrite(geriB,LOW);//       motorlar ileri yönde sürülür
    digitalWrite(geriA,LOW);
    analogWrite(pwmB,50);
    analogWrite(pwmA,60);
    delay(1);
    
    tarama.write(pos);//             tarama servosunun acısını verir
    delay(1);
    
    if(saggoz>500||orta>500||solgoz>500)
    {
      alana_gir(saggoz,ortagoz,solgoz);
    }
    if(engel==0)
    {
      cop_al(pos);
    }    
}
for(pos=112;pos>=90;pos-=2)
{
    engel=digitalRead(tarayici);
    delay(1);
    saggoz=analogRead(sag);
    ortagoz=analogRead(orta);
    solgoz=analogRead(sol);
    delay(1);
    digitalWrite(geriB,LOW);
    digitalWrite(geriA,LOW);
    analogWrite(pwmB,50);
    analogWrite(pwmA,60);
    delay(1);
    tarama.write(pos);
    delay(1);
   
    if(saggoz>500||orta>500||solgoz>500)
    {
      alana_gir(saggoz,ortagoz,solgoz);
    }
    if(engel==0)
    {
      cop_al(pos);
    }    
}
   
}

void cop_al(int pozisyon)
{   
    digitalWrite(geriB,LOW);
    digitalWrite(geriA,LOW);
    analogWrite(pwmB,LOW);
    analogWrite(pwmA,LOW);
    delay(1000);
  if(pos<117&&pos>85)
  {  
    i+=1;
    kaldirac.write(10);
    delay(1000);
    for(possol=170; possol>=70;possol-=1)
      {
        possag=70+(170-possol);
        kiskacsag.write(possag);
        kiskacsol.write(possol);
        delay(10);
      }
    delay(1000);
    kaldirac.write(100);
    delay(1000);
    for(possag=170; possag>=70;possag-=1)
      {
        possol=70+(170-possag);
        kiskacsag.write(possag);
        kiskacsol.write(possol);
        delay(10);
      }
    delay(1000);
    kaldirac.write(60);
    delay(1000);    
  }
 
  if(i==4)
  { 
    cop_dok();
    i=0;            
  }
}

void alana_gir(int saggoz,int ortagoz,int solgoz)
{
  if(saggoz>500&&ortagoz>500)
  {
    digitalWrite(geriB,HIGH);   
    digitalWrite(geriA,LOW);
    analogWrite(pwmB,150);
    analogWrite(pwmA,LOW);
    delay(500);
    digitalWrite(geriB,LOW);         
    analogWrite(pwmB,LOW);
  }
  if(solgoz>500&&ortagoz>500)
  {
    digitalWrite(geriA,HIGH);   
    digitalWrite(geriB,LOW);
    analogWrite(pwmA,150);
    analogWrite(pwmB,LOW);
    delay(500);
    digitalWrite(geriA,LOW);         
    analogWrite(pwmA,LOW);
  }
  if(solgoz>500)
  {
    digitalWrite(geriA,HIGH);   
    digitalWrite(geriB,LOW);
    analogWrite(pwmA,150);
    analogWrite(pwmB,LOW);
    delay(300);
    digitalWrite(geriA,LOW);         
    analogWrite(pwmA,LOW);
  } 
  if(saggoz>500)
  {
    digitalWrite(geriB,HIGH);   
    digitalWrite(geriA,LOW);
    analogWrite(pwmB,150);
    analogWrite(pwmA,LOW);
    delay(300);
    digitalWrite(geriB,LOW);         
    analogWrite(pwmB,LOW);
  }  
  
}

void cop_dok()
{
    saggoz=analogRead(sag);
    ortagoz=analogRead(orta);
    solgoz=analogRead(sol);
    while(saggoz<500||ortagoz<500||solgoz<500)
    {
    saggoz=analogRead(sag);
    ortagoz=analogRead(orta);
    solgoz=analogRead(sol);
    digitalWrite(geriB,HIGH);   
    digitalWrite(geriA,HIGH);
    analogWrite(pwmB,175);
    analogWrite(pwmA,175);
    delay(50);
    }
    digitalWrite(geriB,LOW);   
    digitalWrite(geriA,LOW);
    analogWrite(pwmB,LOW);
    analogWrite(pwmA,LOW);
    kasasag.write(30);
    kasasol.write(150);
    delay(2000);
    kasasag.write(155);
    kasasol.write(30);
    delay(10000);
}

