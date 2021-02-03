#include <PubSubClient.h>

#include <UIPEthernet.h>

#include <SPI.h>

int pino2 = 2; // Cria uma variável para o pino 2
bool estado_sensor; // Cria uma variável para armazenar o estado do sensor  

// Variável itilizada  para enviar as mensagens utilizado o cliente MQTT
boolean mensagem;

// Define o endereço MAC que será utilizado
byte mac[] = {0x82,0xC3,0x28,0x6F,0x5A,0xD9};

// Inicia o cliente Ethernet
EthernetClient client;

// Inicia o cliente MQTT
PubSubClient mqttClient(client);

void setup() {
  // put your setup code here, to run once:

  pinMode(pino2, INPUT_PULLUP);

  // Inicia o controlador Ethernet e solicita um IP para o servidor de DHCP
  Ethernet.begin(mac);

  // Inicia o monitor Serial
  Serial.begin(9600);

  // Define o IP e porta TCP do Broker MQTT que vamos utilizar
  mqttClient.setServer("54.144.190.205", 1883);  

  // Exibe no monitor Serial as informações sobre o IP do Arduíno
  Serial.print("O IP do Arduíno e: ");
  Serial.println(Ethernet.localIP());

  // Exibe no monitor Serial as informações sobre a Máscara de Rede
  Serial.print("A mascara de Rede do Arduíno e: ");
  Serial.println(Ethernet.subnetMask());

  // Exibe no monitor Serial as informações sobre o Gateway do Arduíno 
  Serial.print("O Gateway do Arduíno e: ");
  Serial.println(Ethernet.gatewayIP());

  // Exibe uma linha em branco 
  Serial.println();
    
}

void loop() {
  // put your main code here, to run repeatedly:

  estado_sensor = digitalRead(pino2);

  // Define o nome do cliente MQTT e efetua a conexão com o servidor.
  mqttClient.connect("Vitinho");

  if(estado_sensor == 0) {
      
        mensagem = mqttClient.publish("Porta_do_Rach", "0");
        mensagem = mqttClient.publish("Porta_do_Rach", "FECHADO");

    } else {
      
        mensagem = mqttClient.publish("Porta_do_Rach", "1");
        mensagem = mqttClient.publish("Porta_do_Rach_text", "ABERTO");
        
    }

  Serial.println(estado_sensor);
  
  Serial.println();

  mqttClient.loop();

}
