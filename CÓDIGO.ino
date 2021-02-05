#include <PubSubClient.h>

#include <UIPEthernet.h>

#include <SPI.h>

byte mac[] = {0x2E,0x03,0x96,0x8A,0x18,0x7C};
int pino2 = 2;
bool mensagem;
bool estado_sensor;
EthernetClient client;

//Inicia o MQTT
PubSubClient mqttClient(client);

 
void setup() {
Ethernet.begin(mac);

Serial.begin(9600);
pinMode(pino2,INPUT_PULLUP);

mqttClient.setServer("54.173.152.93",1883);


Serial.print("O IP do Arduino e: ");
Serial.println(Ethernet.localIP());


Serial.print("A Maskara de Rede do Arduino e: ");
Serial.println(Ethernet.subnetMask());


Serial.print("O Gateway do Arduino e: ");
Serial.println(Ethernet.gatewayIP());

Serial.println(""); //linha em branco

delay(5000); // 5 segundos


}

void loop() {

estado_sensor = digitalRead(pino2);

mqttClient.connect("luanverdelho");

if(estado_sensor == 0){
  
mensagem = mqttClient.publish("A porta do RACK esta Fechada: ", "0");
mensagem = mqttClient.publish("ar_condicionado", "FECHADA");
Serial.print("A porta do RACK esta Fechada: ");
}else{

  mensagem = mqttClient.publish("A porta do RACK esta Aberta:", "1");
  mensagem = mqttClient.publish("ar_condicionado", "ABERTA");
Serial.print("A porta do RACK esta Aberta: ");  
  }


Serial.println(estado_sensor);

mqttClient.loop();

}
