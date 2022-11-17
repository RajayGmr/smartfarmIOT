#include<WiFi.h>
#include<FirebaseESP32.h>

#define WIFI_SSID "99-195 A_2.4G"
#define WIFI_PASSWORD "0957725712"

#define FIREBASE_HOST     "https://ce4301-week-9-cw-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH     "fXvjRLsF0qnPZ0igkvJfVyCHDO9fJcEMXghvVfY3"

FirebaseData Fert_A,Fert_B,Moister,Hour,   SW_Water,SW_Fert_A,SW_Fert_B,     AUTO_MODE, Manual,firebaseData; 
FirebaseJson json;

//From Firebase
double Moister_from_config=0;
int Fert_A_time=0;
int Fert_B_time=0;
//
//int SW_Water =0;
//int SW_Fert_A = 0;
//int SW_Fert_B = 0;
//int Manual = 0;

//int AUTO_MODE = 0;
//From sensor or Input
double Moister_from_S = 6;

//Output
int Led_Water=10;
int Led_Fert_A=11;
int Led_Fert_B=12;


double Moister_coverting_from_S=0;
double Fert_A_time_converting=0;
double Fert_B_time_converting=0;
int Day=1;

void setup() {

//////////////////////////////////////////////////////////////

  //Check the connection with the internet\

  Serial.begin(115200);   //UART0 Monitor Baudrade bps
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) //When it is not yet connected
  {
      Serial.print(".");
      delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////

  //Check connection between Firebase and ESP32

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  //Set database read timeout to 1 minute (max 15 minutes)

  
  Firebase.setReadTimeout(Fert_A, 1000 * 60);
  Firebase.setwriteSizeLimit(Fert_A, "tiny");
  Firebase.setReadTimeout(Fert_B, 1000 * 60);
  Firebase.setwriteSizeLimit(Fert_B, "tiny");
  Firebase.setReadTimeout(Hour, 1000 * 60);
  Firebase.setwriteSizeLimit(Hour, "tiny");
  Firebase.setReadTimeout(Moister, 1000 * 60);
  Firebase.setwriteSizeLimit(Moister, "tiny");


  
  Firebase.setReadTimeout(SW_Water, 1000 * 60);
  Firebase.setwriteSizeLimit(SW_Water, "tiny");
  Firebase.setReadTimeout(SW_Fert_A, 1000 * 60);
  Firebase.setwriteSizeLimit(SW_Fert_A, "tiny");
  Firebase.setReadTimeout(SW_Fert_B, 1000 * 60);
  Firebase.setwriteSizeLimit(SW_Fert_B, "tiny");
  
  Firebase.setReadTimeout(AUTO_MODE, 1000 * 60);
  Firebase.setwriteSizeLimit(AUTO_MODE, "tiny");
  Firebase.setReadTimeout(Manual, 1000 * 60);
  Firebase.setwriteSizeLimit(Manual, "tiny");

  

  Serial.println("------------------------------------");
  Serial.println("FIREBASE Connected...");  
  
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
  //Pin IN/OUT
  pinMode(Led_Water , OUTPUT);
  pinMode(Led_Fert_A, OUTPUT);
  pinMode(Led_Fert_B , OUTPUT);
  pinMode(Moister_from_S , INPUT);

//////////////////////////////////////////////////////////////
}

void loop() {
  
    if(Firebase.getInt(Manual, "Manual/Manual")){ 
    Serial.print("Manual = "); 
    Serial.println(Manual.intData());
    }
    if(Firebase.getInt(AUTO_MODE, "AUTO_MODE/AUTO_MODE")){ 
    Serial.print("AUTO_MODE = "); 
    Serial.println(AUTO_MODE.intData());
    }


    if(AUTO_MODE.intData()==1){
      switch (Day){
      case 1:
         if(Firebase.getInt(Fert_A, "Day1/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day1/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day1/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day1/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 2:
         if(Firebase.getInt(Fert_A, "Day2/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day2/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day2/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day2/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 3:
         if(Firebase.getInt(Fert_A, "Day3/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day3/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day3/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day3/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 4:
         if(Firebase.getInt(Fert_A, "Day4/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day4/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day4/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day4/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 5:
         if(Firebase.getInt(Fert_A, "Day5/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day5/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day5/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day5/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 6:
         if(Firebase.getInt(Fert_A, "Day6/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day6/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day6/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day6/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 7:
         if(Firebase.getInt(Fert_A, "Day7/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day7/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day7/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day7/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 8:
         if(Firebase.getInt(Fert_A, "Day8/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day8/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day8/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day8/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 9:
         if(Firebase.getInt(Fert_A, "Day9/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day9/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day9/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day9/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 10:
         if(Firebase.getInt(Fert_A, "Day10/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day10/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day10/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day10/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 11:
         if(Firebase.getInt(Fert_A, "Day11/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day11/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day11/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day11/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 12:
         if(Firebase.getInt(Fert_A, "Day12/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day12/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day12/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day12/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 13:
         if(Firebase.getInt(Fert_A, "Day13/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day13/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day13/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day13/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 14:
         if(Firebase.getInt(Fert_A, "Day14/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day14/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day14/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day14/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 15:
         if(Firebase.getInt(Fert_A, "Day15/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day15/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day15/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day15/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 16:
         if(Firebase.getInt(Fert_A, "Day16/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day16/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day16/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day16/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 17:
         if(Firebase.getInt(Fert_A, "Day17/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day17/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day17/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day17/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 18:
         if(Firebase.getInt(Fert_A, "Day18/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day18/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day18/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day18/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 19:
         if(Firebase.getInt(Fert_A, "Day19/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day19/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day19/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day19/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 20:
         if(Firebase.getInt(Fert_A, "Day20/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day20/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day20/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day20/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 21:
         if(Firebase.getInt(Fert_A, "Day21/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day21/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day21/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day21/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 22:
         if(Firebase.getInt(Fert_A, "Day22/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day22/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day22/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day22/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 23:
         if(Firebase.getInt(Fert_A, "Day23/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day23/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day23/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day23/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 24:
         if(Firebase.getInt(Fert_A, "Day24/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day24/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day24/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day24/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
       case 25:
         if(Firebase.getInt(Fert_A, "Day25/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day25/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day25/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day25/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
       case 26:
         if(Firebase.getInt(Fert_A, "Day26/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day26/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day26/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day26/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
       case 27:
         if(Firebase.getInt(Fert_A, "Day27/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day27/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day27/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day27/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
       case 28:
         if(Firebase.getInt(Fert_A, "Day28/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day28/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day28/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day28/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
       case 29:
         if(Firebase.getInt(Fert_A, "Day29/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day29/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day29/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day29/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
       case 30:
         if(Firebase.getInt(Fert_A, "Day30/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day30/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day30/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day30/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
       case 31:
         if(Firebase.getInt(Fert_A, "Day31/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day31/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day31/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day31/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
       case 32:
         if(Firebase.getInt(Fert_A, "Day32/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day32/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day32/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day32/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break; 
      case 33:
         if(Firebase.getInt(Fert_A, "Day33/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day33/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day33/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day33/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 34:
         if(Firebase.getInt(Fert_A, "Day34/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day34/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day34/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day34/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 35:
         if(Firebase.getInt(Fert_A, "Day35/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day35/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day35/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day35/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 36:
         if(Firebase.getInt(Fert_A, "Day36/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day36/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day36/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day36/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 37:
         if(Firebase.getInt(Fert_A, "Day37/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day37/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day37/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day37/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
      case 38:
         if(Firebase.getInt(Fert_A, "Day38/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
         Serial.print("Fert_A = "); 
         Serial.println(Fert_A.intData());
         }
         if(Firebase.getInt(Fert_B, "Day38/Fert_B")){ 
         Serial.print("Fert_B = "); 
         Serial.println(Fert_B.intData());
         }
        if(Firebase.getInt(Hour, "Day38/Hour")){ 
        Serial.print("Hour = "); 
        Serial.println(Hour.intData());
        }
          if(Firebase.getInt(Moister, "Day38/Moister")){ 
          Serial.print("Moister = "); 
          Serial.println(Moister.intData());
      }
      break;
    }
    }
    if(Manual.intData()==1) {     
    if(Firebase.getInt(SW_Water, "Manual/SW_Water")){ 
    Serial.print("SW_Water = "); 
    Serial.println(SW_Water.intData());
    }
    if(Firebase.getInt(SW_Fert_B, "Manual/SW_Fert_B")){ 
    Serial.print("SW_Fert_B = "); 
    Serial.println(SW_Fert_B.intData());
    }
    if(Firebase.getInt(SW_Fert_A, "Manual/SW_Fert_A")){ 
    Serial.print("SW_Fert_A = "); 
    Serial.println(SW_Fert_A.intData());
    }
     }

    json.set("/LIVE_MOISTER_LEVEL",Moister_coverting_from_S);
    Firebase.updateNode(firebaseData,"/Monitor",json);

  
    Moister_from_config = Moister.intData();
    Fert_B_time = Fert_B.intData();
    Fert_A_time = Fert_A.intData();


//    SW_Water = SW_Water.intData();  
//    SW_Fert_A = SW_Fert_A.intData();
//    SW_Fert_B = SW_Fert_B.intData();

   
    Serial.println();

    
//==========================================================================
  // Operation parts  
    Moister_coverting_from_S = Moister_from_S*99/4095;//Covert 0-4095 to 0-99%        
    Serial.println();
    Serial.print("Live Moister Value =");
    Serial.print(Moister_coverting_from_S);
    Serial.println();
    Serial.print("millis() =");
    Serial.print(millis());
    
    int Time = Hour.intData()*60*60*1000;
      if(AUTO_MODE.intData()==1||Manual.intData()==1){
        if(millis()==Hour.intData()*60*60*1000||Manual.intData()==1){
        

    ////////////////////////////////////////////////////////////// 

    // Water part
        if (Moister_coverting_from_S <=Moister_from_config|| SW_Water.intData() == 1){ // if moister lower than the config value its going to be activated 
          digitalWrite(Led_Water, HIGH); //BLUE LED


          Serial.println();
          Serial.print("Led_Water=");
          Serial.print(Led_Water);
          Serial.println();
          }
          digitalWrite(Led_Water, LOW);
    ////////////////////////////////////////////////////////////// 

    //////////////////////////////////////////////////////////////                            

    // Fertilizer A
    
    Fert_A_time_converting = Fert_A_time*60000; // make it time 60seconds
        if(Fert_A_time_converting!=0||SW_Fert_A.intData()==1){
          digitalWrite(Led_Fert_A, HIGH); // GREEN LED
      
          Serial.println();
          Serial.print("Led_Fert_A=");
          Serial.print(Led_Fert_A);

          Serial.println();
          Serial.print("Fertilizer A time =");
          Serial.print(Fert_A_time_converting);
          delay(Fert_A_time_converting);
          digitalWrite(Led_Fert_A, LOW);
          }
    //////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////// 

    // Fertilizer B
    
    Fert_B_time_converting = Fert_B_time*60000; // make it time 60seconds
          if(Fert_B_time_converting!=0||SW_Fert_B.intData()==1){
          digitalWrite(Led_Fert_B, HIGH); // GREEN LED
      
          Serial.println();
          Serial.print("Led_Fert_B=");
          Serial.print(Led_Fert_B);
          Serial.print("Fertilizer B time =");
          Serial.print(Fert_B_time_converting);
          delay(Fert_B_time_converting);
          digitalWrite(Led_Fert_B, LOW);
          }
    //////////////////////////////////////////////////////////////
    
//==========================================================================
      }
      }
      if(AUTO_MODE.intData()==1){
    delay(Hour.intData()*60*60*1000);
    delay(86400000-(Hour.intData()*60*60*1000));
    Day++;}
}
