const int pinPotenciometro = 34;  // Pino para o potenciômetro
const int pinNTC = 35;  // Pino para o sensor temperatura
const int pinBuzzer = 27;  // Pino para o buzzer

void setup() {
  Serial.begin(115200);
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  // Leitura do potenciômetro
  int valorPotenciometro = analogRead(pinPotenciometro);

  // Mapeia o valor do potenciômetro para uma faixa de frequência cardíaca
  int frequenciaCardiaca = map(valorPotenciometro, 0, 4095, 40, 150);

  // Leitura do sensor NTC
  int valorNTC = analogRead(pinNTC);

  // Converte o valor do NTC para temperatura em graus Celsius
  float temperatura = mapeiaTemperatura(valorNTC);

  // Valor da frequência cardíaca no Monitor Serial
  Serial.print("Frequência Cardíaca: ");
  Serial.println(frequenciaCardiaca);

  // Valor simulado da temperatura no Monitor Serial
  Serial.print("Temperatura em graus celcius: ");
  Serial.println(temperatura);

  /* Verifica se a frequência cardíaca está fora da faixa ideal 
    para uma pessoa adulta (60-100 BPM) */
  if (frequenciaCardiaca < 60 || frequenciaCardiaca > 100) {
    // Emite um alerta sonoro usando o buzzer
    digitalWrite(pinBuzzer, HIGH);
    delay(500);  // Mantém o alerta sonoro por 0,5 segundos
    digitalWrite(pinBuzzer, LOW);
  }

  // Verifica se a temperatura está fora da faixa ideal (36 - 38 graus Celsius)
  if (temperatura < 36 || temperatura > 38) {
    // Emite um alerta sonoro usando o buzzer
    digitalWrite(pinBuzzer, HIGH);
    delay(500);  // Mantém o alerta sonoro por 0,5 segundos
    digitalWrite(pinBuzzer, LOW);
  }

  delay(1000);  // Aguarda 1 segundo antes de ler novamente
}

// Função para converter a leitura do NTC para temperatura em graus Celsius
float mapeiaTemperatura(int leitura) {
  return map(leitura, 0, 4095, 20, 50); 
}