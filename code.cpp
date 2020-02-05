#include <PCF8574.h>

#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/io.h>
#include <avr/wdt.h>

#define Reset_AVR() wdt_enable(WDTO_30MS);
#define SLAVE_ADDR 9
#define ANSWERSIZE 5
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int manualPin = 12;

LiquidCrystal_I2C lcd(0x27, 16, 2);
PCF8574 expander1(0x20);
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'.','0','#','D'}
};
byte rowPins[ROWS] = {4, 5, 6, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 9, 10, 11}; //connect to the column pinouts of the keypad

Keypad tkeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int n = 0;
int check = 0;
int exe = 0;
char mode;

//PCF8574 expander;

void setup() {
  expander1.begin();
  for(int e = 0; e < 8; e++)
  {
    expander1.pinMode(e, OUTPUT);
  }

  for(int e = 0; e < 8; e++)
  {
    expander1.digitalWrite(e, HIGH);
  }
 // expander.pinMode(1, INPUT);
  lcd.init();
  lcd.backlight();
  // Initialize I2C communications as Master
  Wire.begin();
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //display.display();
  //delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(manualPin, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
  digitalWrite(manualPin, LOW);

  //expander.digitalWrite(0, HIGH);
  
  // Setup serial monitor
  Serial.begin(9600);

  
      lcd.setCursor(3, 0);
      lcd.print("Welcome in");
      lcd.setCursor(3, 1);
      lcd.print("PyroSystem");
      digitalWrite(A0, HIGH);
      delay(200);
      digitalWrite(A0, LOW);
      digitalWrite(A1, HIGH);
      delay(200);
      digitalWrite(A1, LOW);
      digitalWrite(A2, HIGH);
      delay(200);
      digitalWrite(A2, LOW);
      digitalWrite(A0, HIGH);
      delay(200);
      digitalWrite(A1, HIGH);
      delay(200);
      digitalWrite(A2, HIGH);
      delay(200);
      
     
      digitalWrite(A0, LOW);
      digitalWrite(A1, LOW);
      digitalWrite(A2, LOW);
      delay(500);

      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
}

void loop() 
{
char tryit = tkeypad.getKey();
if(tryit == '.')
{
  testmode();
}
  selectMode();  
  
//  //delay(50);
//  Wire.beginTransmission(SLAVE_ADDR);
//  Wire.write(0);
//  Wire.endTransmission();
//  Wire.requestFrom(SLAVE_ADDR,ANSWERSIZE);
//  String response = "";
//  while (Wire.available()) {
//      char b = Wire.read();
//      response += b;
//  } 
  
}
void  Menu()
{
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("1. 1 channel");
      lcd.setCursor(0, 1);
      lcd.print("2. Multi channels");
      n = 0;
      
      while(1)
      {   
  char tkey = tkeypad.waitForKey();
  if(tkey == 'B')
    {
      if(n<2)
      {
        n++;
      }
    }
    if(tkey == 'A')
    {
      if(n>0)
      {
        n--;
      }
    }
  switch(n)
  {
    case 0:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("1. 1 channel");
      lcd.setCursor(0, 1);
      lcd.print("2. Multi channels");
      check = n;
    break;
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("2. Multi channels");
      lcd.setCursor(0, 1);
      lcd.print("3. Time mode");
      check = n;
    break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("3. Time mode");
      lcd.setCursor(0, 1);
      lcd.print("4. Back");
      check = n;
    break;
    default:
    break;
  }
  Chose(tkey);
}
}


int GetInt2()
{
  String todisplay;
  int retn;
  lcd.setCursor(0, 1);
  lcd.print("##             ");
  again:
  char a = tkeypad.waitForKey();
  if(checkNmbr(a))
  {
    goto again;
  }
  todisplay += a;
  lcd.setCursor(0, 1);
  lcd.print(todisplay);
  againb:
  char b = tkeypad.waitForKey();
  if(checkNmbr(b))
  {
    goto againb;
  }
  todisplay += b;
  lcd.setCursor(0, 1);
  lcd.print(todisplay);
  
  return (a-48)*10 + b-48;
  
  
}


void Chose(char tkey)
{
  switch(tkey)
  {
    case '1':
      oneChannel();
      break;
    case '2':
      multiChannel();
      break;
    case '3':
      timeMode();
      break;
    case '4':
      selectMode();
      break;
    default:
      delay(1);
      break;
  }
}
void oneChannel()
{
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Chose channel");
  lcd.setCursor(0, 1);
  lcd.print("Default");
again:
int one = GetInt2();
//if(checkNmbr(exe))
//{
//  goto again;
//}
ChoseChannel(one);
  
}
void ChoseChannel(int mykey)
{

  int times;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Chose channel");
  lcd.setCursor(0, 1);
  lcd.print(mykey);
  Serial.println(mykey);
  
exe = mykey;
repeat:
char wait = tkeypad.waitForKey();
if(wait == '#')
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1. Instant");
  lcd.setCursor(0, 1);
  lcd.print("2. With delay");
  minimenu:
  char which = tkeypad.waitForKey();
 
  if(which == '2')
  {
    times = timer();
    repeatiti:
    char thr = tkeypad.waitForKey();
    if(thr == '#')
    {
      Ready(exe, times);
    }
    else
     goto repeatiti;
  }
  else if(which == '1')
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Confirm?");
    lcd.setCursor(0, 1);
    lcd.print("Push #");
    repeatit:
    char thr = tkeypad.waitForKey();
    if(thr == '#')
    {
      Ready(exe, times);
    }
    else
      goto repeatit;
  }
  else
    goto minimenu;
 }
 else
  goto repeat;



}
void Ready(int exe, int times)
{
  goback:
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("READY...");
  readyy:
  char now = tkeypad.waitForKey();
  if(now == 'D')
  {
    Execute(exe, times);
  }
  else if(now == 'C')
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Are you sure?");
    lcd.setCursor(0, 1);
    lcd.print("# - yes  * - no");
    waitonemoretime:
    char exitq = tkeypad.waitForKey();
    if(exitq == '#')
    {
      Menu();
    }
    else if(exitq == '.')
    {
      goto goback;
    }
    else
    {
      goto waitonemoretime;
    }
  }
  else
  {
    goto readyy;
  }
  
}

void ReadyMulti(int times, int chs[], int chnmbr)
{
  goback:
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("READY...");
  staythere:
  char now = tkeypad.waitForKey();
  if(now == 'D')
  {
    ExecuteMulti(times, chs, chnmbr);
  }
  else if(now == 'C')
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cancel?");
    lcd.setCursor(0, 1);
    lcd.print("# - yes  * - no");
    waitonemoretime:
    char exitq = tkeypad.waitForKey();
    if(exitq == '#')
    {
      Menu();
    }
    else if(exitq == '.')
    {
      goto goback;
    }
    else
    {
      goto waitonemoretime;
    }
  }
  else
  {
    goto staythere;
  }
  
}void ReadyMultiT(int times, int chs[], int chnmbr, int chNe)
{
  goback:
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("READY...");
  staythere:
  char now = tkeypad.waitForKey();
  if(now == 'D')
  {
    TimeExecute(chs, times);
  }
  else if(now == 'C')
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cancel?");
    lcd.setCursor(0, 1);
    lcd.print("# - yes  * - no");
    waitonemoretime:
    char exitq = tkeypad.waitForKey();
    if(exitq == '#')
    {
      Menu();
    }
    else if(exitq == '.')
    {
      goto goback;
    }
    else
    {
      goto waitonemoretime;
    }
  }
  else
  {
    goto staythere;
  }
  
}


void Execute(int pin, int times)
{
  if(times != 0)
    {
      beeper(times);
    }
    //Serial.write(pin);
      expander1.digitalWrite(pin-1, LOW);
      delay(1000);
      expander1.digitalWrite(pin-1, HIGH);
  //Serial.println(timer());
  Menu();
}
void ExecuteMulti(int times, int chs[], int chnmbr)
{
  beeper(times);
  for(int j = 0; j < chnmbr; j++)
    {
      //Serial.write(chs[j]);
      expander1.digitalWrite(chs[j]-1, LOW);
    }
      delay(1000);
  for(int j = 0; j < chnmbr; j++)
    {
      expander1.digitalWrite(chs[j]-1, HIGH);
    }
  //digitalWrite(pin, HIGH);
  //Serial.println(timer());
  Menu();
}

int timer()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter time (sec):");
  
  int res = GetInt();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter time (sec):");
  lcd.setCursor(0, 1);
  lcd.print(res);
  return res;
  
  
}

int timerS()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Start time (sec):");
 
  //char times = tkeypad.waitForKey();
  
  int res = GetInt();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Start time (sec):");
  
  lcd.setCursor(0, 1);
  lcd.print(res);
  return res;
  
  
}

void beeper(int times)
{
  for(int i = 0; i <= times; i++)
  {
    
    if(times - i == 99)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("READY...");
        lcd.setCursor(0, 1);
      }
      if(times - i == 9)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("READY...");
        lcd.setCursor(0, 1);
      }
      if(times - i == 0)
      {
        digitalWrite(3, HIGH);
        delay(1000);
        digitalWrite(3, LOW);
      }
      else if(times - i < 5)
      {
        
        lcd.setCursor(0, 1);
        lcd.print(times-i);
        for(int j = 0; j < 4; j++)
        {
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(3, LOW);
          delay(50);
        }
        delay(600);
         
      }
    else
    {
      lcd.setCursor(0, 1);
      lcd.print(times-i);
      digitalWrite(3, HIGH);
      delay(500);
      digitalWrite(3, LOW);
      delay(500);
    }
  }
}

int GetInt()
{
  String todisplay;
  int retn;
  lcd.setCursor(0, 1);
  lcd.print("###             ");

  again:
  char a = tkeypad.waitForKey();
  if(checkNmbr(a))
  {
    goto again;
  }
  todisplay += a;
  lcd.setCursor(0, 1);
  lcd.print(todisplay);
  againb:
  char b = tkeypad.waitForKey();
  if(checkNmbr(b))
  {
    goto againb;
  }
  todisplay += b;
  lcd.setCursor(0, 1);
  lcd.print(todisplay);

  againc:
  char c = tkeypad.waitForKey();
  if(checkNmbr(c))
  {
    goto againc;
  }
  todisplay += c;
  lcd.setCursor(0, 1);
  lcd.print(todisplay);
  int result = (a-48)*100 + (b-48)*10 + c-48;
  return result;
  
  
}

void testmode()
{
      int inst = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("PROGRAMMING MODE");
      Serial.println("Insert command: ");
  while(1)
      {
        
          char inputt = Serial.read();
          //Serial.println(inputt);
//          if(inputt == '&')
//          {
//            for(int q = 0; q < 8; q++)
//            {
//              expander1.digitalWrite(q, LOW);
//            }
//            delay(1000);
//            for(int q = 0; q < 8; q++)
//            {
//              expander1.digitalWrite(q, HIGH);
//            }
//          }
//          
//          if(inputt == '!')
//          {
//            inputt = 8;
//          }
//          if(inputt == '@')
//          {
//            inputt = 9;
//          }
//          if(inputt == '#')
//          {
//            inputt = 10;
//          }
//          if(inputt == '$')
//          {
//            inputt = 11;
//          }
//          if(inputt >=0; inputt < 16)
//          {
//            expander1.digitalWrite(inputt, LOW);
//            delay(1000);
//            expander1.digitalWrite(inputt, HIGH);
//          }
          
          switch(inputt)
          {
            case '0':
                  expander1.digitalWrite(0, LOW);
                  delay(1000);
                  expander1.digitalWrite(0, HIGH);
            break;
            case '1':
                  expander1.digitalWrite(1, LOW);
                  delay(1000);
                  expander1.digitalWrite(1, HIGH);
            break;
            case '2':
                  expander1.digitalWrite(2, LOW);
                  delay(1000);
                  expander1.digitalWrite(2, HIGH);
            break;
            case '3':
                  expander1.digitalWrite(3, LOW);
                  delay(1000);
                  expander1.digitalWrite(3, HIGH);
            break;
            case '4':
                  expander1.digitalWrite(4, LOW);
                  delay(1000);
                  expander1.digitalWrite(4, HIGH);
            break;
            case '5':
                  expander1.digitalWrite(5, LOW);
                  delay(1000);
                  expander1.digitalWrite(5, HIGH);
            break;
            case '6':
                  expander1.digitalWrite(6, LOW);
                  delay(1000);
                  expander1.digitalWrite(6, HIGH);
            break;
            case '7':
                  expander1.digitalWrite(7, LOW);
                  delay(1000);
                  expander1.digitalWrite(7, HIGH);
            break;
            case '!':
                  expander1.digitalWrite(8, LOW);
                  delay(1000);
                  expander1.digitalWrite(8, HIGH);
            break;
            case '@':
                  expander1.digitalWrite(9, LOW);
                  delay(1000);
                  expander1.digitalWrite(9, HIGH);
            break;
            case '#':
                  expander1.digitalWrite(10, LOW);
                  delay(1000);
                  expander1.digitalWrite(10, HIGH);
            break;
            case '$':
                  expander1.digitalWrite(11, LOW);
                  delay(1000);
                  expander1.digitalWrite(11, HIGH);
            break;
            case '&':
            for(int k = 0; k< 12; k++)
            {
              expander1.digitalWrite(k, LOW);
            }    
            delay(1000);
            for(int k = 0; k< 12; k++)
            {
              expander1.digitalWrite(k, HIGH);
            }    
            break;
            case 'B':
            for(int q = 0; q < 4; q ++)
            {
                  digitalWrite(3, HIGH);
                  delay(50);
                  digitalWrite(3, LOW);
                  delay(50);
            }    
            break;
            
            default:
            break;
          }
      }
}
void multiChannel()
{
      int times = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Channels qnty:");
      int chnmbr = getQ();
      int chs[chnmbr];
      repeat:
      char checkit = tkeypad.waitForKey();
      if(checkit != '#')
      {
        goto repeat;
      }
      for(int i = 0; i < chnmbr; i++)
      {
        chs[i] = multiChChoose(i);
        repeatyy:
        char checkit = tkeypad.waitForKey();
        if(checkit != '#')
        {
          goto repeatyy;
        }
      }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1. Instant");
  lcd.setCursor(0, 1);
  lcd.print("2. With delay");
  justamoment:
   char which = tkeypad.waitForKey();
    if(which == '2')
    {
      times = timer();
      waitforit:
      char thr = tkeypad.waitForKey();
      if(thr == '#')
      {
        ReadyMulti(times, chs, chnmbr);
      }
      else
      {
        goto waitforit;
      }
    }
  else if(which == '1')
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Confirm?");
    lcd.setCursor(0, 1);
    lcd.print("Push #");
    stayandwait:
    char thr = tkeypad.waitForKey();
    if(thr == '#')
    {
      Ready(exe, times);
    }
    else
    {
      goto stayandwait;
    }
  }
  else
  {
    goto justamoment;
  }
      
}

int multiChChoose(int i)
{
  String todisplay;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Choose ch");
  lcd.setCursor(10, 0);
  lcd.print(i+1);
  lcd.setCursor(0, 1);
  lcd.print("##             ");

  again:
  char a = tkeypad.waitForKey();
  if(checkNmbr(a))
  {
    goto again;
  }
  todisplay += a;
  lcd.setCursor(0, 1);
  lcd.print(todisplay);

  againb:
  char b = tkeypad.waitForKey();
  if(checkNmbr(b))
  {
    goto againb;
  }
  todisplay += b;
  lcd.setCursor(0, 1);
  lcd.print(todisplay);
  
  return (a-48)*10 + b-48;

}

int multiChChooseT(int i)
{
  String todisplay;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Choose time");
  lcd.setCursor(12, 0);
  lcd.print(i+1);
  lcd.setCursor(0, 1);
  lcd.print("##             ");
  waitma:
  char a = tkeypad.waitForKey();
  if(checkNmbr(a))
  {
    goto waitma;
  }
  todisplay += a;
  lcd.setCursor(0, 1);
  lcd.print(todisplay);
  againmb:
  char b = tkeypad.waitForKey();
  if(checkNmbr(b))
  {
    goto againmb;
  }
  todisplay += b;
  lcd.setCursor(0, 1);
  lcd.print(todisplay);
  
  return (a-48)*10 + b-48;

}

int getQ()
{
  String todisplay;
  //char insert = tkeypad.waitForKey();
  //insert = checkNmbr(insert);
  lcd.setCursor(0, 1);
  lcd.print("##             ");
  again:
  char a = tkeypad.waitForKey();
  if(checkNmbr(a))
  {
    goto again;
  }
  todisplay += a;
  lcd.setCursor(0, 1);
  lcd.print(todisplay);
  againb:
  char b = tkeypad.waitForKey();
  if(checkNmbr(b))
  {
    goto againb;
  }
  todisplay += b;
  lcd.setCursor(0, 1);
  lcd.print(todisplay);
  Serial.println((a-48)*10 + b-48);
  return (a-48)*10 + b-48;
}
bool checkNmbr(char checking)
{
  if(checking == 'A')
   return true;
  else if(checking == 'B')
   return true;
  else if(checking == 'C')
   return true;
  else if(checking == 'D')
   return true;
  else if(checking == '#')
   return true;
  else if(checking == '.')
   return true;
else
   return false;
}

void onlysharp()
{
  
}

void timeMode()
{
      int times = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Channels qnty:");
      int chnmbr = getQ();
      lcd.setCursor(0, 1);
      lcd.print(chnmbr);
      lcd.setCursor(1, 1);
      lcd.print(" ");
      int chs[20];
      int timeBreaks[20];
        stayhere:
      char thrt = tkeypad.waitForKey();
        if(thrt != '#')
        {
          goto stayhere;
        }
      
      for(int i = 0; i < chnmbr; i++)
      {
        chs[i] = multiChChoose(i);
        stayheret:
      char thrt = tkeypad.waitForKey();
        if(thrt != '#')
        {
          goto stayheret;
        }
      }
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("1. Same time");
      lcd.setCursor(0, 1);
      lcd.print("2. Dfrnt times");
      
      //againm:
      repeatac:
      char vari = tkeypad.waitForKey();

      if(vari == '1')
      {
        int times = multiChChooseT(1);
        stayhereta:
      char thrta = tkeypad.waitForKey();
        if(thrta != '#')
        {
          goto stayhereta;
        }
        for(int i = 0; i < chnmbr; i++)
          {
            
            timeBreaks[i] = times;
          }
      }
      else if(vari == '2')
      {
        for(int i = 0; i < chnmbr; i++)
          {
            timeBreaks[i] = multiChChooseT(i);
            stayheretb:
              char thrtb = tkeypad.waitForKey();
                if(thrtb != '#')
                {
                  goto stayheretb;
                }
          }
      }
      else
      {
        goto repeatac;
      }
      
//      switch(choose)
//      {
//        case '1':
//        int times = multiChChooseT(1);
//        for(int i = 0; i < chnmbr; i++)
//          {
//            
//            timeBreaks[i] = times;
//          }
//          break;
//        case '2':
//        for(int i = 0; i < chnmbr; i++)
//          {
//            timeBreaks[i] = multiChChooseT(i);
//          }
//          break;
//        default:
//        goto againm;
//        break;
//      }
      

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Start time: ");
      int waitt = timerS();
      waitwaitat:
      char getStarta = tkeypad.waitForKey();      
            if(getStarta != '#')
            {
              goto waitwaitat;
            }

      goback:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("READY...");

      staythere:
  char now = tkeypad.waitForKey();
  if(now == 'D')
  {
    beeper(waitt);
      for(int i = 0; i < chnmbr; i++)
      {
        TimeExecute(chs[i], timeBreaks[i]);
        Serial.println("DONE");
      }
  }
  else if(now == 'C')
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cancel?");
    lcd.setCursor(0, 1);
    lcd.print("# - yes  * - no");
    waitonemoretime:
    char exitq = tkeypad.waitForKey();
    if(exitq == '#')
    {
      Menu();
    }
    else if(exitq == '.')
    {
      goto goback;
    }
    else
    {
      goto waitonemoretime;
    }
  }
  else
  {
    goto staythere;
  }

  
//      waitwaita:
//      char getStart = tkeypad.waitForKey();
//            if(getStart != '#')
//            {
//              goto waitwaita;
//            }
//      beeper(waitt);
      
      
      Menu();
}

int TimeBreaks(int i)
{
  String todisplay;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Choose break tm");
  lcd.setCursor(10, 0);
  lcd.print(i+1);
  lcd.setCursor(0, 1);
  lcd.print("##             ");
  
  char a = tkeypad.waitForKey();
  todisplay += a;
  lcd.setCursor(0, 1);
  lcd.print(todisplay);
  
  char b = tkeypad.waitForKey();
  todisplay += b;
  lcd.setCursor(0, 1);
  lcd.print(todisplay);

  tkeypad.waitForKey();
  
  return (a-48)*10 + b-48;
}

void TimeExecute(int chnmbr, int timeBreaks)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Channel");

  lcd.setCursor(8, 0);
  lcd.print(chnmbr);
  
  expander1.digitalWrite(chnmbr-1, LOW);
  delay(500);
  expander1.digitalWrite(chnmbr-1, HIGH);
  for(int p = 0; p < timeBreaks; p++)
  {
    if(timeBreaks - p == 99)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("READY...");
        lcd.setCursor(0, 1);
      }
      if(timeBreaks - p == 9)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("READY...");
        lcd.setCursor(0, 1);
      }
      lcd.setCursor(0, 1);
      int letit = timeBreaks - p;
      lcd.print(letit);
      delay(1000);
  }
  //Serial.println("Executed" + chnmbr);
}

void goMenu(char check)
{
  if(check == 'C')
    Menu();
}

void selectMode()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("1. Programmable");
  lcd.setCursor(0, 1);
  lcd.print("2. Manual");
  while(mode != '1' || mode != '2')
  {
  mode = tkeypad.waitForKey();
  switch(mode)
  {
    case '1':
      Menu();
    break;
    case '2':
      Manual();
    break;
    default:
    break;
  }
  }
}

void Manual()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MANUAL MODE");
  digitalWrite(manualPin, HIGH);
  while(mode != '.')
  {
    mode = tkeypad.waitForKey();
  }
  digitalWrite(manualPin, LOW);
  selectMode();
}
