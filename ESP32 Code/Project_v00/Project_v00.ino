#include<WiFi.h>
#include<FirebaseESP32.h>

#define WIFI_SSID "99-195 A_2.4G"
#define WIFI_PASSWORD "0957725712"

#define FIREBASE_HOST     "https://ce4301-week-9-cw-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH     "fXvjRLsF0qnPZ0igkvJfVyCHDO9fJcEMXghvVfY3"

FirebaseData firebaseData;
FirebaseJson json;
boolean Fert_A;
boolean Fert_B;
int Led_Fert_B = x;
int Led_Fert_A = x;
int Led_Water = x;
double Moister;
double Moister_coverting = 0;
double Moister_from_senser =x;
double Moister_coverting_from_S=0;
double Day =1;
int Valve_Fert_A = x;
int Valve_Fert_B = x;
int Valve_Water = x;

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
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  Serial.println("------------------------------------");
  Serial.println("FIREBASE Connected...");  
  
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////

  //Pin IN/OUT
  pinMode(Led_Fert_B , OUTPUT);
  pinMode(Led_Fert_A , OUTPUT);
  pinMode(Led_Water , OUTPUT);
  pinMode(Moister , INPUT);                       <====== change all to pin no.
  pinMode(Valve_Fert_A , OUTPUT);
  pinMode(Valve_Fert_B , OUTPUT);
  pinMode(Valve_Water , OUTPUT);


//////////////////////////////////////////////////////////////
}

void loop() {

//==========================================================================
  // Operation parts
  
  Moister_coverting = Moister*(99/4095); // 0-4095 to 0-99% from firebase
  Moister_coverting_from_S = Moister_from_senser*(99/4095);// 0-4095 to 0-99% from moister sensor
  
  if(Moister_coverting<50||Moister_coverting_from_S<50){ // if moister lower than 50% its being activated
    
    ////////////////////////////////////////////////////////////// 
    
    // LED_FERTILIZER_A   
    
    if(Fert_A=1)
    {
      digitalWrite(Led_Fert_A, HIGH);   // RED LED
      digitalWrite(Valve_Fert_A, HIGH);  // LED_Fertiziler A = on, Valve_Fertiziler A = on
      digitalWrite(Valve_Water, HIGH); 
      digitalWrite(Led_Water, HIGH);  // BLUE LED
      delay(60000); //60s
      
      Serial.println();
      Serial.print("Led_Fert_A=");
      Serial.print(Led_Fert_A);
      Serial.println();
      Serial.print("Valve_Fert_A=");
      Serial.print(Valve_Fert_A);
      Serial.print("Led_Water=");
      Serial.print(Led_Water);
      Serial.println();
      Serial.print("Valve_Water=");
      Serial.print(Valve_Water);
    }        

    //////////////////////////////////////////////////////////////    

    ////////////////////////////////////////////////////////////// 

    // LED_FERTILIZER_B   
    if(Fert_B=1)
    {
      digitalWrite(Led_Fert_B, HIGH); // GREEN LED
      digitalWrite(Valve_Fert_B, HIGH);  // LED_Fertiziler B = on, Valve_Fertiziler B = on
      digitalWrite(Valve_Water, HIGH);
      digitalWrite(Led_Water, HIGH);  
      delay(60000); //60s
      
      Serial.println();
      Serial.print("Led_Fert_B=");
      Serial.print(Led_Fert_B);
      Serial.println();
      Serial.print("Valve_Fert_B=");
      Serial.print(Valve_Fert_B);
      Serial.print("Led_Water=");
      Serial.print(Led_Water);
      Serial.println();
      Serial.print("Valve_Water=");
      Serial.print(Valve_Water);
      }

    ////////////////////////////////////////////////////////////// 

    if(Fert_A=0&&Fert_B=0){
      digitalWrite(Led_Fert_B, LOW);
      digitalWrite(Valve_Fert_B, LOW);
      digitalWrite(Led_Fert_A, LOW);
      digitalWrite(Valve_Fert_A, LOW);// Everything = OFF but the water still flow
      digitalWrite(Led_Water, HIGH); 
      digitalWrite(Valve_Water, HIGH);  
      delay(60000); //60s
      
      Serial.println();
      Serial.print("Led_Fert_B=");
      Serial.print(Led_Fert_B);
      Serial.println();
      Serial.print("Led_Fert_A=");
      Serial.print(Led_Fert_A);
      Serial.println();
      Serial.print("Valve_Fert_B=");
      Serial.print(Valve_Fert_B);
      Serial.println();
      Serial.print("Valve_Fert_A=");
      Serial.print(Valve_Fert_A);
      Serial.println();
      Serial.print("Led_Water=");
      Serial.print(Led_Water);
      Serial.println();
      Serial.print("Valve_Water=");
      Serial.print(Valve_Water);
      }
  }
//==========================================================================

//==========================================================================

 //Firebase part
 
  //////////////////////////////////////////////////////////////

    //Bring data from firebase to ESP32

  if(Firebase.getInt(firebaseData, "/Data2")){ // similar to above but will activate when we give away the input after it is being compiled
    Serial.print("Data2 = "); 
    Serial.println(firebaseData.intData());
    }

  //////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////

    //Update Data to FireBase
  
  json.set("/LIVE_MOISTER_LEVEL",Moister_coverting_from_S); // get the define value of count which start as 0 and keep increasing and create a file "Counter" on firebase
  Firebase.updateNode(firebaseData,"/LIVE_MOISTER_LEVEL",json); //given to do the provided node

  //////////////////////////////////////////////////////////////
  
//==========================================================================
}
