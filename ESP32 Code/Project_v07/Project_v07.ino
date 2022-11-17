#include<WiFi.h>
#include<FirebaseESP32.h>

#define WIFI_SSID "99-195 A_2.4G"
#define WIFI_PASSWORD "0957725712"

#define FIREBASE_HOST     "https://abac-semester2-2021-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH     "ksHVQ4HNjopTnAZm1QQIeqCcH3e871aXlZc4e0Xf"

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
    int Time = Hour.intData()*60*60*1000;
      if(AUTO_MODE.intData()==1||Manual.intData()==1){
        if(millis()==Hour.intData()*60*60*1000){
        

    ////////////////////////////////////////////////////////////// 

    // Water part
        if (Moister_coverting_from_S <=Moister_from_config|| SW_Water.intData() == 1){ // if moister lower than the config value its going to be activated 
          digitalWrite(Led_Water, HIGH); //BLUE LED


          Serial.println();
          Serial.print("Led_Water=");
          Serial.print(Led_Water);
          Serial.println();
          }
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
          Fert_A_time_converting=0;
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
          Fert_B_time_converting=0;
          }
    //////////////////////////////////////////////////////////////
    
//==========================================================================
      }
      }
    delay(Hour.intData()*60*60*1000);
    delay(86400000-(Hour.intData()*60*60*1000));
    Day++;
}
