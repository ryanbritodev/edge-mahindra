# SPRINT 1 - TECH MAHINDRA E FIAP

Este projeto foi desenvolvido como parte da __Sprint 1__ da disciplina de __Edge Computing & Computer Systems__, ministrada pelo Prof. Flávio Grassi, para os alunos do primeiro semestre de __Engenharia de Software da FIAP__. O objetivo principal dessa Sprint foi desenvolver uma solução IoT que fosse capaz de captar informações sobre a Fórmula E, transmitindo-as de maneira criativa e acessível, permitindo que pessoas de todas as idades e níveis de conhecimento sobre automobilismo se envolvam e se emocionem com a competição.

<div style="display: flex; justify-content: space-between;">
  <img src="https://e-formula.news/files/e-formel/uploads/_NEWS/2023/12%20Dezember/Mahindra%20Livery/Mahindra-Livery-Formula-E-Season-2024.jpg" width="36.5%">
  <img src="https://mms.businesswire.com/media/20210709005496/pt/890318/22/New_Tech_M_Logo_High-res_square.jpg" width="49%" style="margin-right: auto;">
</div>

## Descrição do Projeto

O projeto consiste em um dispositivo integrado ao cockpit dos carros da Fórmula E, projetado para monitorar e alertar sobre condições adversas dentro do cockpit, tais como __temperatura, umidade e luminosidade__. Além disso, o sistema possui a funcionalidade de abrir automaticamente um compartimento de ventilação e refrigeração para melhorar as condições internas do veículo.

Por meio de uma rede de dispositivos IoT integrados ao cockpit do piloto, informações cruciais são captadas e processadas em tempo real para garantir a segurança e o conforto do piloto durante a corrida.

## Funcionalidades Principais do Sistema

- Monitoramento da temperatura, umidade e luminosidade dentro do cockpit.
- Abertura automática do compartimento de ventilação e resfriamento em caso de temperatura elevada.
- Exibição das informações de temperatura e umidade em um display LCD.
- Indicação visual de alertas por meio de LEDs de diferentes cores.
- Controle de um servo motor para abrir e fechar o compartimento de ventilação e resfriamento.

## Justificativa

A segurança dos pilotos é de extrema importância em corridas de alta velocidade como a Fórmula E. Condições adversas dentro do cockpit, como altas temperaturas e umidade, podem afetar negativamente o desempenho do piloto e até mesmo colocar sua vida em risco. Portanto, a implementação de um sistema inteligente de monitoramento e controle é essencial para garantir um ambiente seguro e confortável durante a corrida.

## Instalação e Uso

Para utilizar o sistema, siga as etapas abaixo:

1. Monte os componentes conforme o esquemático fornecido.
2. Carregue o código fonte para o Arduino Uno R3.
3. Conecte o dispositivo ao cockpit do carro da Fórmula E.
4. Ligue o sistema e monitore as condições ambientais durante a corrida.

Certifique-se de seguir as normas de segurança ao instalar e operar o dispositivo.

## Esquemático do Circuito

![Esquemático do Circuito](circuit_diagram.png)

## Componentes Utilizados

- Sensor de luz (fotoresistor)
- Sensor de temperatura e umidade DHT22
- LEDs (vermelho, amarelo e verde)
- Servo motor
- Display LCD
- Arduino Uno R3

## Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para enviar sugestões, relatar problemas ou enviar pull requests para melhorar este projeto.

## Licença

Este projeto está licenciado sob a [MIT License](LICENSE).

