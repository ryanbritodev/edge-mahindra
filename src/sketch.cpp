/* 
------------------ FIAP --------------------
SPRINT 1 - TECH MAHINDRA
EDGE COMPUTING & COMPUTER SYSTEMS
Participantes:
Prof. Flávio Grassi PF2013
Arthur Cotrick Pagani RM554510
Diogo Leles Franciulli RM558487
Felipe Sousa de Oliveira RM559085
Ryan Brito Pereira Ramos RM554497
--------------------------------------------

Você sabia que um carro de Fórmula E pode chegar a temperaturas internas de até 60°C?

Este projeto criado para Sprint 1 da matéria de Edge Computing & Computer Systems visa aprimorar o conforto e a segurança dos pilotos na Fórmula E.
O dispositivo tem como objetivo monitorar e alertar sobre condições adversas dentro do cockpit, mensurando grandezas como temperatura, umidade e luminosidade.
Além disso, o sistema tem como funcionalidade a abertura de um compartimento de ventilação que visa melhorar as condições internas do veículo.
Através de uma rede de dispositivos IoT integrados ao cockpit do piloto, informações cruciais são captadas e processadas em tempo
real para garantir a segurança e o conforto do piloto.

Esta solução não apenas visa garantir a segurança do piloto em situações críticas,
mas também busca envolver o público de forma emocionante com as informações atualizadas em tempo real.
Ao fornecer informações sobre as condições do veículo em tempo real e tomar decisões de segurança
de forma automática e eficiente, o projeto permite que pessoas de todas as idades e níveis de
conhecimento sobre automobilismo se envolvam e se emocionem com a competição da Fórmula E.

Para garantir a segurança do piloto, a ventilação não pode ser aberta em um ambiente escuro por algumas razões:
• SEGURANÇA DENTRO DE TÚNEIS: Durante a corrida, o carro pode passar por túneis ou áreas com pouca iluminação. Abrir o sistema de resfriamento e ventilação nesses ambientes
pode desorientar o piloto devido à entrada repentina de luz ou ruído, afetando sua concentração e capacidade de manobra.
• PRESENÇA DE DETRITOS: Em áreas escuras, a visibilidade é limitada, e há um risco maior de detritos ou objetos no caminho que não são visíveis
a olho nu. Abrir nosso dispositivo de ventilação e resfriamento pode permitir a entrada desses detritos, causando desconforto ou até mesmo danificando componentes internos do cockpit.
• INTERFERÊNCIA NA AERODINÂMICA: Com o nosso sistema refrigeração e ventilação aberto, podemos alterar a aerodinâmica do veículo, especialmente em alta velocidade. Em condições de baixa visibilidade,
qualquer mudança inesperada na dinâmica do carro pode ser perigosa, afetando o controle e a estabilidade do veículo.

Lista de dispositivos utilizados nesse sistema:
• Um sensor de luz (fotoresistor) para medir a luminosidade ambiente.
• Um sensor de temperatura e umidade DHT22 para medir as condições dentro do cockpit.
• Três LEDs (vermelho, amarelo e verde) para indicar diferentes níveis de alerta.
• Um servomotor para abrir automaticamente a ventilação do cockpit.
• Um display LCD para exibir as informações ao piloto.
• Um Arduino Uno R3 para controlar todos os componentes.
*/

#include <LiquidCrystal.h>  // Biblioteca para controle do display LCD
#include <DHT.h>            // Biblioteca para o sensor de temperatura e umidade DHT22
#include <Servo.h>          // Biblioteca para controle do servomotor

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2); // Inicialização do display LCD

int ldr = A2; // Pino analógico conectado ao sensor de luz (fotoresistor)
#define DHT_PIN 13 // Pino digital conectado ao sensor DHT22
#define DHT_TYPE DHT22 // Tipo do sensor (DHT22)
DHT dht(DHT_PIN, DHT_TYPE); // Inicialização do sensor DHT22

int ledRed = 7; // Pino digital conectado ao LED vermelho
int ledYellow = 6; // Pino digital conectado ao LED amarelo
int ledGreen = 9; // Pino digital conectado ao LED verde

int servoPin = 8; // Pino digital conectado ao servomotor
Servo ejectServo; // Instância do servomotor para chamar alguns métodos

int num_readings = 5; // Número de leituras para calcular a média da luminosidade
float light_avg = 0; // Variável para armazenar a média da luminosidade
bool sistemaAtivo = false; // Variável para indicar se o sistema de refrigeração está ativado

byte raio[] = { // Definição de um símbolo personalizado de um raio para o display LCD
  B00010,
  B00110,
  B01100,
  B11111,
  B11111,
  B00110,
  B01100,
  B01000
};

void setup() {
  lcd.createChar(0, raio); // Criação do símbolo personalizado
  lcd.begin(16, 2); // Inicialização do display LCD com 16 colunas e 2 linhas
  lcd.print("Mahindra Racing"); // Exibição do texto inicial no display LCD
  lcd.setCursor(0, 1);
  lcd.print("#ChasingSuccess");
  delay(3000); // Aguarda 3 segundos
  lcd.clear(); // Limpa o display LCD
  lcd.setCursor(1, 0);
  lcd.write(byte(0)); // Exibe o símbolo personalizado no display LCD
  lcd.print(" Bem-vindo,");
  lcd.setCursor(14, 0);
  lcd.write(byte(0));
  lcd.setCursor(0, 1);
  lcd.print(" Nyck de Vries!");
  delay(5000); // Aguarda 5 segundos
  lcd.clear(); // Limpa o display LCD
  pinMode(ldr, INPUT); // Configura o pino do sensor de luz como entrada
  pinMode(ledRed, OUTPUT); // Configura o pino do LED vermelho como saída
  pinMode(ledYellow, OUTPUT); // Configura o pino do LED amarelo como saída
  pinMode(ledGreen, OUTPUT); // Configura o pino do LED verde como saída
  ejectServo.attach(servoPin); // Conecta o servo motor ao pino correspondente
  Serial.begin(9600); // Inicializa a comunicação serial
  dht.begin(); // Inicializa o sensor DHT22
  digitalWrite(ledRed, LOW); // Desliga o LED vermelho
  digitalWrite(ledYellow, LOW); // Desliga o LED amarelo
  digitalWrite(ledGreen, LOW); // Desliga o LED verde
  ejectServo.write(90); // Define a posição inicial do servo motor
}

void openVentilation() {
  light_avg = 0;
  
  for (int i = 0; i < num_readings; i++) {
    light_avg += analogRead(ldr); // Realiza leituras do sensor de luz
    delay(100);
  }
  
  light_avg /= num_readings; // Calcula a média da luminosidade
  float light_level = map(light_avg, 1023, 0, 0, 100); // Converte a média para uma escala de 0 a 100
  
  if (light_level < 40) { // Verifica se a luminosidade é baixa
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Luz BAIXA");
    lcd.setCursor(0, 1);
    lcd.print("Aguardar");
    delay(5000); // Aguarda 5 segundos
    return;
  }
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  INICIANDO");
  lcd.setCursor(0, 1);
  lcd.print(" RESFRIAMENTO");
  
  digitalWrite(ledRed, HIGH); // Liga o LED vermelho
  delay(1000); // Aguarda 1 segundo
  digitalWrite(ledRed, LOW); // Desliga o LED vermelho
  
  digitalWrite(ledYellow, HIGH); // Liga o LED amarelo
  delay(1000); // Aguarda 1 segundo
  digitalWrite(ledYellow, LOW); // Desliga o LED amarelo
  
  digitalWrite(ledGreen, HIGH); // Liga o LED verde
  delay(1000); // Aguarda 1 segundo
  digitalWrite(ledGreen, LOW); // Desliga o LED verde
  
  ejectServo.write(0); // Move o servo para a posição de ventilação
  
  sistemaAtivo = true; // Ativa o sistema de refrigeração

  lcd.clear(); // Limpa o display LCD
}

void desativarVentilacao() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" RESFRIAMENTO");
  lcd.setCursor(0, 1);
  lcd.print("   EFETUADO");
  delay(5000); // Aguarda 5 segundos
  
  ejectServo.write(90); // Retorna o servo à posição inicial
  
  sistemaAtivo = false; // Desativa o sistema de refrigeração
  lcd.clear(); // Limpa o display LCD
}

void loop() {
  light_avg = 0;
  
  for (int i = 0; i < num_readings; i++) {
    light_avg += analogRead(ldr); // Realiza leituras do sensor de luz
    delay(100);
  }
  
  light_avg /= num_readings; // Calcula a média da luminosidade
  float light_level = map(light_avg, 1023, 0, 0, 100); // Converte a média para uma escala de 0 a 100
  
  float temp = dht.readTemperature(); // Lê a temperatura ambiente
  float hum = dht.readHumidity(); // Lê a umidade ambiente
  
  if (isnan(temp) || isnan(hum)) { // Verifica se os valores de temperatura e umidade são válidos
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro no DHT22");
    delay(5000); // Aguarda 5 segundos
    return;
  }
  
  lcd.clear();
  lcd.setCursor(0, 0);
  if (temp >= 30 && temp <= 50) { // Verifica se a temperatura está dentro da faixa normal
    lcd.print("Temp. NORMAL");
    lcd.setCursor(0, 1);
    lcd.print("Temp. = ");
    lcd.print(temp);
    lcd.write(223); // Exibe o símbolo de graus Celsius
    lcd.print("C");
  } else if (temp > 50) { // Verifica se a temperatura está alta
    if (!sistemaAtivo) { // Verifica se o sistema de refrigeração está inativo
      openVentilation(); // Abre a ventilação se o sistema estiver inativo
    }
    lcd.print("Temp. ALTA");
    lcd.setCursor(0, 1);
    lcd.print("Temp. = ");
    lcd.print(temp);
    lcd.write(223); // Exibe o símbolo de graus Celsius
    lcd.print("C");
  } else { // Se a temperatura estiver baixa
    if (sistemaAtivo) { // Verifica se o sistema de refrigeração está ativo
      desativarVentilacao(); // Desativa o sistema de refrigeração se a temperatura voltar ao normal
    }
    lcd.print("Temp. BAIXA");
    lcd.setCursor(0, 1);
    lcd.print("Temp. = ");
    lcd.print(temp);
    lcd.write(223); // Exibe o símbolo de graus Celsius
    lcd.print("C");
  }
  
  if (sistemaAtivo) { // Se o sistema de refrigeração estiver ativo, exibir a temperatura
    lcd.clear();
    lcd.print("Temp. ALTA");
    lcd.setCursor(0, 1);
    lcd.print("Temp. = ");
    lcd.print(temp);
    lcd.write(223); // Exibe o símbolo de graus Celsius
    lcd.print("C");
  } else if (!sistemaAtivo && light_level < 40) { // Se o sistema estiver inativo e a luminosidade for baixa
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Luz BAIXA");
    lcd.setCursor(0, 1);
    lcd.print("Aguardar");
  }
  
  delay(5000); // Aguarda 5 segundos
  
  lcd.clear();
  lcd.setCursor(0, 0);
  if (hum >= 50 && hum <= 70) { // Verifica se a umidade está dentro da faixa normal
    lcd.print("Umidade. OK");
  } else if (hum > 70) { // Verifica se a umidade está alta
    lcd.print("Umidade. ALTA");
  } else { // Se a umidade estiver baixa
    lcd.print("Umidade. BAIXA");
  }
  
  if (!sistemaAtivo && light_level < 40) { // Se o sistema estiver inativo e a luminosidade for baixa
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Luz BAIXA");
    lcd.setCursor(0, 1);
    lcd.print("Aguardar");
  } else { // Se a luminosidade estiver normal
    lcd.setCursor(0, 1);
    lcd.print("Umid. = ");
    lcd.print(hum);
    lcd.print("%");
  }
  
  delay(5000); // Aguarda 5 segundos
  
  lcd.clear();
  lcd.setCursor(0, 0);
  
  if (light_level < 40) { // Verifica se a luminosidade é baixa
    lcd.print("Luz BAIXA");
  } else { // Se a luminosidade for normal
    lcd.print("Luz NORMAL");
  }
  
  lcd.setCursor(0, 1);
  lcd.print("Luz = ");
  lcd.print(light_level);
  lcd.print("%");
  
  delay(5000); // Aguarda 5 segundos
}
