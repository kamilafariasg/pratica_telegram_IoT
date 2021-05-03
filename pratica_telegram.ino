#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
// Inicializando a conexao WIFI com o Roteador
char ssid[] = "wifi";           // nome do seu roteador WIFI (SSID)
char password[] = "a1b2c3d4e5";   // senha do roteador WIFI
// Inicializa o BOT Telegram - copie aqui a chave Token quando configurou o seu BOT - entre aspas
#define BOTtoken "528420337:AAHLwwVuklQ2P8mbUh5-7CdIgq7mSzy5uYI"  // sua chave Token Bot
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int Bot_mtbs = 1000;      // tempo entre a leitura das mensagens
long Bot_lasttime;        // ultima mensagem lida
bool Start = false;
const int ledPin = 4;    // GPIO_4do LED azul
int ledStatus = 0;
void handleNewMessages(int numNewMessages){
      Serial.print("Mensagem recebida = ");
      Serial.println(String(numNewMessages));
      for (int i = 0; i < numNewMessages; i++){
         String chat_id = String(bot.messages[i].chat_id);
       String text = bot.messages[i].text;
          String from_name = bot.messages[i].from_name;
          if (from_name == "") from_name = "Guest";
          if (text == "/ledon")                              //  comando Ledon
             {digitalWrite(ledPin, HIGH);                       // acende LED azul
              ledStatus = 1;
       bot.sendMessage(chat_id, "LED esta aceso", "");  // envia mensagem
    } 
         If (text == "/ledoff")                                //  comando Ledoff
           { ledStatus = 0;
              digitalWrite(ledPin,LOW );                         // apaga LED azul
           bot.sendMessage(chat_id, "LED esta apagado", "");   // envia mensagem
    }
        if (text == "/status")     {                             // comando estado do LED
        if (ledStatus) {
             bot.sendMessage(chat_id, "LED esta aceso", ""); }
       else {
           bot.sendMessage(chat_id, "LED esta apagado", "");
      }
 }
    if (text == "/start")                                  // comando comeca
    {String welcome = "Bem-vindo a Biblioteca Universal Arduino Telegram Bot, " + from_name + ".\n";
      welcome += "Esse é um exemplo de controle do Led.\n\n";
      welcome += "/ledon : para acender o LED\n";
      welcome += "/ledoff : para apagar o LED\n";
      welcome += "/status : mostra o estado do LED\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}
void setup() {
      Serial.begin(115200);
     WiFi.mode(WIFI_STA);          // Configura o WIFI do NodeMCU para modo estação
     WiFi.disconnect();            // desconecta o WIFI
     delay(100);                   // atraso de 100 milisegundos
     Serial.print("Conectando Wifi: ");
     Serial.println(ssid);
     WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)   // aguardando a conexão WEB  {Serial.print(".");
           delay(500);                           // atraso de 0,5 segundos
  }
  Serial.println("");
  Serial.println("WiFi conectado");       // WIFI conectado
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(ledPin, OUTPUT);                // configura o pino do LED como saida
  delay(10);
  digitalWrite(ledPin, HIGH);             // inicializa o LED como apagado
}
void loop(){
  if (millis() > Bot_lasttime + Bot_mtbs)    // controlando as mensagens { 
          int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
       while (numNewMessages)                  // numero de novas mensagens{
                 Serial.println("Resposta recebida do Telegram");
                 handleNewMessages(numNewMessages);
                 numNewMessages=bot.getUpdates(bot.last_message_received + 1);
    }
Bot_lasttime = millis();}
}
