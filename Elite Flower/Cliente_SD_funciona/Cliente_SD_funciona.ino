#include "painlessMesh.h"
#include <SD.h>
#include <SPI.h>
#include <string.h>

#define   MESH_PREFIX     "FincaSanPedro"
#define   MESH_PASSWORD   "FincaSanPedro"
#define   MESH_PORT       5555

Scheduler     userScheduler; // to control your personal task
painlessMesh  mesh;
//bool dato = false;
String mensajeS = " ";
void receivedCallback( uint32_t from, String &msg );


#define CS_PIN 16

File myFile;


int UltimaPosicion=0;
String mensajeGuardado;
char minuto;
char minutoant;
byte cons;


int lineas = 0;
int lineasc = 0;
byte idMensaje = 0;
char c;
String mensaje = "";
#define intervalo 1000
unsigned long milisAnterior = 0;
boolean espera = true;
boolean envio = false;
bool m = false;
String mensajeVuelve= "";

int idInv = 0;
bool eliminacion = false;

size_t logServerId = 0;

// Send message to the logServer every 10 seconds
Task myLoggingTask(10000, TASK_FOREVER, []() {

  if (mensajeS != " ") {
    
//    if (logServerId == 0) {
//      if (dato == false)
//      {
//        Serial.print(1);
//        dato = true;
//      }
//    }
    if (mesh.sendSingle(logServerId, mensajeS)) {
        mensajeS = " ";

        mensajeVuelve.reserve(5);
        mensajeVuelve = "00,01;";
        Serial.print(mensajeVuelve);

        myFile = SD.open("Datos.txt");
        int peso = myFile.size();//guarda el tamaño del fichero                  
                  if(myFile)
                  {
                    if(UltimaPosicion>=peso)   
                    
                    {
                      UltimaPosicion=0;
                      SD.remove("Datos.txt");
                    }
                    myFile.seek(UltimaPosicion);
////                    
                    while(myFile.available())
                      {                   
                    mensajeS = myFile.readString();
                    UltimaPosicion = myFile.position();
////                    mensajeS= String(mensajeGuardado);
////buffer[myFile.readBytesUntil(';', buffer, sizeof(buffer) - 1)] = 0;
////       while (myFile.read() != ';');
////       mensajeS=buffer;
////                    if(mensajeGuardado==59)//ASCII de ;
////                     {            
////                      break;
////                     }
       
                   }
                   myFile.close();
                 }
    }
    else 
    {
         mensajeVuelve.reserve(5);
        mensajeVuelve = "00,00;";
        Serial.print(mensajeVuelve);
       // mensajeGuardado=mensajeS;
       
        
          if(minutoant==minuto)
          {
            cons=1;
          }
          else
          {
            cons=0;
          }
  
           minutoant=minuto;
        
         if((minuto == 48 || minuto == 53)  && cons==0)  //guarda un archivo no enviado solo del minuto del intervalo
 
                 {
                    myFile = SD.open("Datos.txt", FILE_WRITE);//abrimos  el archivo
                    if (myFile) 
                   {
                     myFile.print(mensajeS);
                     myFile.close();
               
                    }
                  }

    }
  }
});

void setup() {
  Serial.begin(9600);
  SD.begin(CS_PIN);

  //mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT, WIFI_AP_STA, 6 );
  mesh.onReceive(&receivedCallback);

  // Add the task to the your scheduler
  userScheduler.addTask(myLoggingTask);
  myLoggingTask.enable();

  //ESP.wdtDisable();
  ESP.wdtFeed();
 


}

void loop() {
  userScheduler.execute(); // it will run mesh scheduler as well
  mesh.update();
  if (Serial.available())
  {
    mensajeS = Serial.readString();
  
    minuto=mensajeS.charAt(17);
    mensajeGuardado=mensajeS;
    
  }
}

void receivedCallback( uint32_t from, String &msg ) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(msg);
  if (root.containsKey("topic")) {
    if (String("logServer").equals(root["topic"].as<String>())) {
      logServerId = root["nodeId"];
    }
  } else {
    Serial.print(msg);
  }
}
