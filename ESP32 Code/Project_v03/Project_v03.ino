iti#include<WiFi.h>
#include<FirebaseESP32.h>

#define WIFI_SSID "99-195 A_2.4G"
#define WIFI_PASSWORD "0957725712"

#define FIREBASE_HOST     "https://ce4301-week-9-cw-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH     "fXvjRLsF0qnPZ0igkvJfVyCHDO9fJcEMXghvVfY3"

FirebaseData Fert_A,Fert_B,Hour,Manual_Pressed,Moister;
FirebaseJson json;

//From Firebase
double moister_from_config;
int Fert_A_time=0;
int Fert_B_time=0; 
int Manual =0;

//From sensor or Input
double Moister_from_S;

//Output
int Valve_Water;
int Valve_Fert_A;
int Valve_Fert_B;
int Led_Water;
int Led_Fert_A;
int Led_Fert_B;


double Moister_coverting_from_S=0;
double moister_from_config_coverting=0;
double Fert_A_time_converting=0;
double Fert_B_time_converting=0;

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
  Firebase.setReadTimeout(Manual_Pressed, 1000 * 60);
  Firebase.setwriteSizeLimit(Manual_Pressed, "tiny");
  Firebase.setReadTimeout(Moister, 1000 * 60);
  Firebase.setwriteSizeLimit(Moister, "tiny");
  Serial.println("------------------------------------");
  Serial.println("FIREBASE Connected...");  
  
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////

  //Pin IN/OUT
  pinMode(Led_Fert_B , OUTPUT);
  pinMode(Led_Fert_A , OUTPUT);
  pinMode(Led_Water , OUTPUT);
  pinMode(Moister_from_S , INPUT);
  pinMode(Valve_Fert_A , OUTPUT);
  pinMode(Valve_Fert_B , OUTPUT);
  pinMode(Valve_Water , OUTPUT);

//////////////////////////////////////////////////////////////
}

void loop() {
//==========================================================================
  // Operation parts

    ////////////////////////////////////////////////////////////// 

    // Water part
    
    Moister_coverting_from_S = Moister_from_S*99/4095;//Covert 0-4095 to 0-99%
    moister_from_config_coverting = moister_from_config*99/4095; //Covert 0-4095 to 0-99%
    
    if (Manual == 1|| Moister_coverting_from_S <=moister_from_config_coverting){ // if moister lower than 70% its being activated
      digitalWrite(Valve_Water, HIGH); 
      digitalWrite(Led_Water, HIGH); //BLUE LED

      Serial.println();
      Serial.print("Live Moister Value =");
      Serial.print(Moister_coverting_from_S);
      Serial.println();
      Serial.print("Manual =");
      Serial.print(Manual);
      Serial.println();
      Serial.print("Led_Water=");
      Serial.print(Led_Water);
      Serial.println();
      Serial.print("Valve_Water=");
      Serial.print(Valve_Water);
    }
    
    ////////////////////////////////////////////////////////////// 

    ////////////////////////////////////////////////////////////// 

    // Fertilizer A
    
    Fert_A_time_converting = Fert_A_time*60000; // make it time 60seconds
    if(Fert_A_time_converting!=0){
      digitalWrite(Led_Fert_A, HIGH); // GREEN LED
      digitalWrite(Valve_Fert_A, HIGH);
      
      Serial.println();
      Serial.print("Led_Fert_A=");
      Serial.print(Led_Fert_A);
      Serial.println();
      Serial.print("Valve_Fert_A=");
      Serial.print(Valve_Fert_A);
      Serial.println();
      Serial.print("Fertilizer A time =");
      Serial.print(Fert_A_time_converting);
      delay(Fert_A_time_converting);
    }
    //////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////// 

    // Fertilizer B
    
    Fert_B_time_converting = Fert_B_time*60000; // make it time 60seconds
    if(Fert_A_time_converting!=0){
      digitalWrite(Led_Fert_B, HIGH); // GREEN LED
      digitalWrite(Valve_Fert_B, HIGH);
      
      Serial.println();
      Serial.print("Led_Fert_B=");
      Serial.print(Led_Fert_B);
      Serial.println();
      Serial.print("Valve_Fert_B=");
      Serial.print(Valve_Fert_B);
      Serial.print("Fertilizer B time =");
      Serial.print(Fert_B_time_converting);
      delay(Fert_B_time_converting);
    }
    //////////////////////////////////////////////////////////////
    
//==========================================================================

//==========================================================================

 //Firebase part
 
  //////////////////////////////////////////////////////////////

    //Bring data from firebase to ESP32

  if(Firebase.getInt(Fert_A, "Testing/Fert_A")){ // similar to above but will activate when we give away the input after it is being compiled
    Serial.print("Fert_A = "); 
    Serial.println(Fert_A.intData());
    }
  if(Firebase.getInt(Fert_B, "Testing/Fert_B")){ 
    Serial.print("Fert_B = "); 
    Serial.println(Fert_B.intData());
    }
      if(Firebase.getInt(Hour, "Testing/Hour")){ 
    Serial.print("Hour = "); 
    Serial.println(Hour.intData());
    }       
      if(Manual_Pressed.getInt(Manual_Pressed, "Testing/Manual_Pressed")){ 
    Serial.print("Manual_Pressed = "); 
    Serial.println(Manual_Pressed.intData());
    }
    if(Moister.getInt(Moister, "Testing/Moister")){ 
    Serial.print("Moister = "); 
    Serial.println(Moister.intData());
    }
  
  //////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////

    //Update Data to FireBase
  
  json.set("/LIVE_MOISTER_LEVEL",Moister_coverting_from_S);
  Firebase.updateNode(firebaseData,"/LIVE_MOISTER_LEVEL",json);

  //////////////////////////////////////////////////////////////
//==========================================================================

}
