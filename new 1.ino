#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial gsm(9, 10);//rx,tx gsm module pins
LiquidCrystal lcd(7,6,5,4,3,2);   //defining lcd pins
int t, tu,svalue,avgValue;
int buf[10],temp,buz=13,ct,m,k,l;
float bh,bg,wh,hp,gp,wg,b,B,u;
void setup() 
{
  Serial.begin(9600); 
  gsm.begin(9600);
  pinMode(buz,OUTPUT);
  beep(2);
  lcd.begin(16,2);     
  lcd.setCursor(0,0);
  lcd.print("BIDIRECTIONAL EM");
  lcd.setCursor(0,1);
  lcd.print(" BILLING SYSTEM ");
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("HOME:   K:      ");
  lcd.setCursor(0,1);
  lcd.print("GRID:   K:      ");
}

void loop()
{
  k=hp=analogRead(A0);  //receive frm GRID
  l=gp=analogRead(A1);  //Send to Grid
  lcd.setCursor(5,0);
  lcd.print("   ");
  lcd.setCursor(5,1);
  lcd.print("   ");
  lcd.setCursor(5,0);
  lcd.print(k);
  lcd.setCursor(5,1);
  lcd.print(l);
  delay(100);
  wh+=(hp/1000);
  wg+=(gp/1000);//to grid
  ct++;
  if(ct==10)
  {
    Serial.print(m);
    Serial.print(" day completed Home Load:");
    Serial.print(wh);Serial.print("KWh");
    Serial.print(" Grid Load:");
    Serial.print(wg);Serial.println("KWh");
    lcd.setCursor(10,0);
    lcd.print(wh);
    lcd.setCursor(10,1);
    lcd.print(wg);
    if(wh<14)
      u=1.75;
    else
      u=2.75;
    m++;
    ct=0;
    if(m==30)
    {
      lcd.setCursor(0,0);
      lcd.print("HB:     PB:0    ");
      lcd.setCursor(0,1);
      lcd.print("GB:     RB:0    ");
      beep(2);
      gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1000 milli seconds or 1 second
      gsm.println("AT+CMGS=\"9490233326\"\r"); // Replace x with mobile number
      delay(1000);
      Serial.print("  Month completed---!");
      Serial.print("Home Bill:");
      gsm.print("  Month completed---!");
      gsm.print("Home Bill:");
      bh= wh*u;
      Serial.print(bh);
      lcd.setCursor(3,0);
      lcd.print(bh);
      Serial.print(" Grid Bill:");
      gsm.print(bh);
      gsm.print(" Grid Bill:");
      bg= wg*4;
      Serial.println(bg);
      lcd.setCursor(3,1);
      lcd.print(bg);
      gsm.print(bg);
      if(bh>bg)
      {
        Serial.print("Paying Bill:");
        gsm.print("Paying Bill:");
        b=bh-bg;
        Serial.print(b);
        lcd.setCursor(11,0);
        lcd.print(b);
        gsm.print(b);
      }
      else if(bg>bh)
      {
        Serial.print("Receving Bill:");
        gsm.print("Receving Bill:");
        B=bg-bh;
        Serial.println(B);
        lcd.setCursor(11,1);
        lcd.print(B);
        gsm.println(B);
      }
      delay(100);
      gsm.println((char)26);// ASCII code of CTRL+Z
      m=0;bh=0;bg=0;
      wh=0;wg=0;
      //while(1);
      lcd.print("HOME:   K:      ");
      lcd.setCursor(0,1);
      lcd.print("GRID:   K:      ");
	  }
  }
}
void beep(int bp)
{
  for(int s=0;s<bp;s++)
  {
    digitalWrite(buz,HIGH);  
    delay(200);
    digitalWrite(buz,LOW);  
    delay(200);
  }
}
/*
Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
delay(1000);  // Delay of 1000 milli seconds or 1 second
Serial.println("AT+CMGS=\"9963850072\"\r"); // Replace x with mobile number
delay(1000);
Serial.print("VEHICLE LOCATED AT:");
Serial.print("http://maps.google.com/maps?q=");
Serial.print(g_lat,6);Serial.print(", ");Serial.println(g_lon,6);
delay(100);
Serial.println((char)26);// ASCII code of CTRL+Z
delay(6000);
*/



