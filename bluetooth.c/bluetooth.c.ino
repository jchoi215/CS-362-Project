// Jae RIm Choi - jchoi215
//
// Lab 9: Reading two analog values with arduino and plotting data in the Processing application 
//
// Description - In this project we take an arduino and connect 2 out of the four different analog sensors
//               in our project we connected a photoresistor and a potentiometer to read the value, as other
//               sensors were not availiable. During the running process, arduino reads the two values, 
//               converts them into a string and sends the data out to the Processing program to be parsed
//               and plotted along the graph.
// 
// Assumption  - "Graphs are built in to arduino libraries"
//                 It turned out that arduinos do not have a set library for graphs thus it needed
//                 a seperate program to actually plot the data. The arduino gathers the information
//                 using analog read, and writes them out to other programs such as Processing, Flash
//                 or MAX/MSP to graph the data. 
//               
//               "Graph is simple to make"
//                 This turned out to be true at least for program called Processing. Although it required
//                 a seperate set of code to be written in that Processing program however it 
//                 was not very difficult at all as the structure was very much like arduino.
//
// References  -  
//               Where to download Processing application and how to set up handshake with arduino. 
//                 https://learn.sparkfun.com/tutorials/connecting-arduino-to-processing#introduction
//               Man Page on Processing: how to parse
//                 https://processing.org/reference/
//               Basic structure of the code for Processing and arduino
//                 https://www.arduino.cc/en/tutorial/graph
//               Different way to plot the graph 
//                 https://www.youtube.com/watch?v=C_gyGXWIgHY
//               How to connect photoresistor - forgot
//                 http://physcomp.flosscience.com/home/unit-8/photoresistors-and-analog-read



#define PIN_RED 8
#define PIN_GREEN 9
#define PIN_BLUE 10

char x = -1;

int led[] = {PIN_RED, PIN_GREEN, PIN_BLUE};

void setup(){
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  Serial.begin(9600); 
  randomSeed(analogRead(0));
}


void ledOn(int active){
  if(active == 4){
    digitalWrite(PIN_RED,   (int) random(0, 255));
    digitalWrite(PIN_GREEN, (int) random(0, 255));
    digitalWrite(PIN_BLUE,  (int) random(0, 255));
  }
  else{
    for(int i = 0; i < 3; i++){
      if(led[i] == active) digitalWrite(led[i], HIGH);
      else digitalWrite(led[i], LOW);
    }  
  }
}

void controlLed(){  
  while(Serial.available() > 0){ 
    x = Serial.read();
    
    switch(x){
      case '1': ledOn(PIN_RED);   break;
      case '2': ledOn(PIN_GREEN); break;
      case '3': ledOn(PIN_BLUE);  break;
      case '4': ledOn(4);         break;
      default:
        digitalWrite(PIN_RED, LOW);
        digitalWrite(PIN_GREEN, LOW);
        digitalWrite(PIN_BLUE, LOW); 
        break;
    }
  }

  if(x == '4'){ ledOn(4); delay(10);}
}

void loop(){
  controlLed();
  delay(10);
}
