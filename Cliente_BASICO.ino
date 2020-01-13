#include "painlessMesh.h"


#define   MESH_PREFIX     "FincaSanPedro"
#define   MESH_PASSWORD   "FincaSanPedro"
#define   MESH_PORT       5555

Scheduler     userScheduler; // to control your personal task
painlessMesh  mesh;
//bool dato = false;
String mensajeS = " ";
void receivedCallback( uint32_t from, String &msg );

//int UltimaPosicion=0;
//
//int lineas = 0;
//int lineasc = 0;
//byte idMensaje = 0;
//char c;
String mensaje = "";
#define intervalo 1000
//unsigned long milisAnterior = 0;
//boolean espera = true;
//boolean envio = false;
//bool m = false;
String mensajeVuelve= "";

int idInv = 0;
//bool eliminacion = false;

size_t logServerId = 0;

// Send message to the logServer every 10 seconds
Task myLoggingTask(10000, TASK_FOREVER, []() {

  if (mensajeS != " ") 
  {
    
    if (mesh.sendSingle(logServerId, mensajeS)) {
        mensajeS = " ";

         mensajeVuelve.reserve(5);
        mensajeVuelve = "00,01;";
        Serial.print(mensajeVuelve);
    }
    else 
    {
         mensajeVuelve.reserve(5);
        mensajeVuelve = "00,00;";
        Serial.print(mensajeVuelve);      
    }
  }
});

void setup() {
  Serial.begin(9600);
  //SD.begin(CS_PIN);

  //mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT, WIFI_AP_STA, 6 );
  mesh.onReceive(&receivedCallback);

  // Add the task to the your scheduler
  userScheduler.addTask(myLoggingTask);
  myLoggingTask.enable();

 //ESP.wdtFeed();

}

void loop() {
  userScheduler.execute(); // it will run mesh scheduler as well
  mesh.update();
  if (Serial.available())
  {
    mensajeS = Serial.readString();
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
