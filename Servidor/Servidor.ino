#include "painlessMesh.h"

#define   MESH_PREFIX     "FincaSanCarlos"
#define   MESH_PASSWORD   "FincaSanCarlos"
#define   MESH_PORT       5555

String mensajeS = "";
//unsigned long tiempo;

Scheduler     userScheduler; // to control your personal task
painlessMesh  mesh;
// Prototype
void receivedCallback( uint32_t from, String &msg );


Task logServerTask(10000, TASK_FOREVER, []() {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& msg = jsonBuffer.createObject();
  msg["topic"] = "logServer";
  msg["nodeId"] = mesh.getNodeId();

  String str;
  msg.printTo(str);
  mesh.sendBroadcast(str);
  
});

//SoftwareSerial mySerial(5,4);
void setup() {
  Serial.begin(9600);
 // mySerial.begin(9600);
  //mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE | DEBUG ); // all types on
  //mesh.setDebugMsgTypes( ERROR | CONNECTION | SYNC | S_TIME );  // set before init() so that you can see startup messages
  //mesh.setDebugMsgTypes( ERROR | CONNECTION | S_TIME );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT, WIFI_AP_STA, 6 );
  mesh.onReceive(&receivedCallback);

  mesh.onNewConnection([](size_t nodeId) {
    //Serial.printf("New Connection %u\n", nodeId);
  });

  mesh.onDroppedConnection([](size_t nodeId) {
    //Serial.printf("Dropped Connection %u\n", nodeId);
  });

  // Add the task to the your scheduler
  userScheduler.addTask(logServerTask);
  logServerTask.enable();

  //ESP.wdtFeed();
}

void loop() {
  userScheduler.execute(); // it will run mesh scheduler as well
  mesh.update();
//  tiempo=millis();
  if (Serial.available()) {
    mensajeS = Serial.readString();
    mesh.sendBroadcast(mensajeS);
//    tiempo=0;
  }

//  if(tiempo>320000)
//  {
//    ESP.reset();
//  }

}

void receivedCallback( uint32_t from, String &msg ) {
  //Serial.println(msg.c_str());
  Serial.print(msg.c_str());
}
