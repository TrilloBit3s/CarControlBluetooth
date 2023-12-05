/*
Dev por "Michael" Trillobit3sGames
trillobit3s@gmail.com - estuartyy@gmail.com 
carrinho controlado por bluetooth
05/02/2017
Ultima atualização 03/12/2023

USE APENAS OS CARACTERES EM SEU CÓDIGO

F = PARA FRENTE => S = PARA  
B = PARA TRÁS => S = PARA
L = PARA ESQUERDA => S = PARA
R = PARA DIREITA => S = PARA

S = PARADO

V = BUZINA => v = buzina desligada
W = LED FRENTE => w = led frente desligado
U = LED TRÁS => u = led trás   desligado 
*/

//biblioteca bluetooth SoftwareSerial
#include <SoftwareSerial.h>

#define LED_Verd_Esq 4 //define LED verde 1
#define LED_Verd_Dir 7 //define LED verde 2
#define LED_Verm_Esq 8 //define LED vermelho 1 
#define LED_Verm_Dir 12 //define LED vermelho 2

#define BUZZER 13 //Buzina

SoftwareSerial BT(0, 1); //TX, RX respetively
String readvoice; //leitura de voz

const int motorA1  = 3; //Motor lado esquerdo
const int motorA2  = 5; //Motor lado esquerdo
const int motorB1  = 6; //Motor lado direito
const int motorB2  = 9; //Motor lado direito

const int ENA = 10; //ENA
const int ENB = 11; //ENB 

const int BTState = 2; //comunicação do Bluetooth.

int state_rec; //variavel para armazenamento de dados.
int vSpeed = 255; //Define velocidade padrão 0 a 255.
char state; //state recebe os caracteres do celular

void setup() {
  BT.begin(9600);
  Serial.begin(9600);

  pinMode(LED_Verd_Esq, OUTPUT);
  pinMode(LED_Verd_Dir, OUTPUT);
  pinMode(LED_Verm_Esq, OUTPUT);
  pinMode(LED_Verm_Dir, OUTPUT);
  
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  pinMode(motorA1, LOW);
  pinMode(motorA2, LOW);
  pinMode(motorB1, LOW);
  pinMode(motorB2, LOW);
  pinMode(ENA, LOW);
  pinMode(ENB, LOW);
  
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  
  pinMode(BTState, INPUT);
}  

void loop() {

  analogWrite(ENA, 255); //velovidade do motor esquerdo
  analogWrite(ENB, 255); //velovidade do motor direito

      //O BUG do comando de voz esta relacionado a esta parte, mantenha ele aqui
      while (BT.available()){ //Verifique se há um byte disponível
        delay(10); //Atraso adicionado para tornar a coisa estável
        char c = BT.read(); //Conduzir uma leitura em série
        readvoice += c;
      } 

  if (readvoice.length() > 0) {
    Serial.println(readvoice);

      if(readvoice == "*para frente#")
      {
        digitalWrite(motorA1, LOW); 
        digitalWrite(motorA2, vSpeed);//coloque valores ex:100 
        digitalWrite(motorB1, vSpeed);// valores de 0 a 255
        digitalWrite(motorB2, LOW);
        delay(500);
      }
      else if(readvoice == "*para trás#")
      {
        digitalWrite(motorA1, vSpeed);
        digitalWrite(motorA2, LOW); 
        digitalWrite(motorB1, LOW); 
        digitalWrite(motorB2, vSpeed);
        delay(500);
      }
      else if (readvoice == "*esquerda#") 
      {
        digitalWrite(motorA1, LOW);   
        digitalWrite(motorA2, vSpeed);
        digitalWrite(motorB1, LOW); 
        digitalWrite(motorB2, vSpeed);
        delay(600);
        digitalWrite(motorA1, LOW);   
        digitalWrite(motorA2, LOW);
        digitalWrite(motorB1, LOW); 
        digitalWrite(motorB2, LOW);
      }
      else if (readvoice == "*direita#")
      {
        digitalWrite(motorA1, vSpeed); 
        digitalWrite(motorA2, LOW);
        digitalWrite(motorB1, vSpeed);      
        digitalWrite(motorB2, LOW); 
        delay(600);
        digitalWrite(motorA1, LOW); 
        digitalWrite(motorA2, LOW);
        digitalWrite(motorB1, LOW);      
        digitalWrite(motorB2, LOW); 
      }
      else if (readvoice == "*pare#")
      {
        digitalWrite(motorA1, LOW);
        digitalWrite(motorA2, LOW);
        digitalWrite(motorB1, LOW);
        digitalWrite(motorB2, LOW);
      }
      else if (readvoice == "*ligar o farol da frente#")
      {      
        digitalWrite(LED_Verd_Esq, HIGH);
        digitalWrite(LED_Verd_Dir, HIGH);
      }
      else if (readvoice == "*desligar o farol da frente#")
      {
        digitalWrite(LED_Verd_Esq, LOW);
        digitalWrite(LED_Verd_Dir, LOW); 
      }
      else if (readvoice == "*ligar o farol de trás#")
      {      
        digitalWrite(LED_Verm_Esq, HIGH);
        digitalWrite(LED_Verm_Dir, HIGH);
      }
      else if (readvoice == "*desligar o farol de trás#")
      {
        digitalWrite(LED_Verm_Esq, LOW);
        digitalWrite(LED_Verm_Dir, LOW);  
      }
      else if (readvoice == "*ligar a buzina#")
      {      
        tone(BUZZER, 1000);
      }
      else if (readvoice == "*desligar a buzina#")
      {
        noTone(BUZZER);
      }
      else if (readvoice == "*ligar os faróis#")
      {
        digitalWrite(LED_Verd_Esq, HIGH);
        digitalWrite(LED_Verd_Dir, HIGH);
        digitalWrite(LED_Verm_Esq, HIGH);
        digitalWrite(LED_Verm_Dir, HIGH);
      }
      else if (readvoice == "*desligar os faróis#")
      {      
        digitalWrite(LED_Verd_Esq, LOW);
        digitalWrite(LED_Verd_Dir, LOW); 
        digitalWrite(LED_Verm_Esq, LOW);
        digitalWrite(LED_Verm_Dir, LOW);
      }
  
    readvoice="";
  }

  //Conexão perdida para o carrinho.
  if (digitalRead(BTState) == LOW) {
    state_rec = 'S';
  }

    // Salva os valores da variável 'state'
  if (Serial.available() > 0) {
    state_rec = Serial.read();
    state = state_rec;
    //Serial.println(vSpeed); //mostra na serial a velocidade

  // Altera a velocidade de acordo com valores especificados.
  if (state == '0'){
    vSpeed = 0;
  }
  else if (state == '4'){
    vSpeed = 100;
  }
  else if (state == '6'){
    vSpeed = 155;
  }
  else if (state == '7'){
    vSpeed = 180;
  }
  else if (state == '8'){
    vSpeed = 200;
  }
  else if (state == '9'){
    vSpeed = 230;
  }
  else if (state == 'q'){
    vSpeed = 255;
  }  

      if (state != 'S'){
        Serial.print(state);
      }

  if (state == 'F'){ //FRENTE. 
    andarParaFrente();
  }

  else if (state == 'B'){ //TRÁS. 
    andarParaTras();
  }

  else if (state == 'L'){ //ESQUERDA. 
    andarParaEsquerda();
  }  

  else if (state == 'R'){ //DIREITA.       
    andarParaDireita();
  }

  else if (state == 'F' && state == 'R'){ //FRENTE DIREITA. 
    frenteDireita();
  }

  else if (state == 'F' && state == 'L'){ //FRENTE ESQUERDA.
    frenteEsquerda();
  }

  else if (state == 'B' && state == 'R'){ //TRÁS DIREITA. 
    trasDireita();
  }
   
  else if (state == 'B' && state == 'L'){ //TRÁS ESQUERDA.
    trasEsquerda();
  }

  else if (state == 'W'){ //Farol Frente Ligado
    farolFrenteLigado();
  }

  else if (state == 'w'){ //Farol Frente Desligado
    farolFrenteDesligado();
  }

  else if (state == 'U'){ //Farol Tras Ligado
    farolTrasLigado();
  }

  else if (state == 'u'){ //Farol Tras Desligado
    farolTrasDesligado();
  }

  else if (state == 'V'){ //ligar Buzina
    ligarBuzina();
  }

  else if (state == 'v'){ //Desligar Buzina
    desligarBuzina();
  }

    else{
      ficarParado();
    }
  }
}
  
  void andarParaFrente()
  {
    digitalWrite(motorA1, 0);
    digitalWrite(motorA2, vSpeed);
    digitalWrite(motorB1, vSpeed);
    digitalWrite(motorB2, 0);
  }
  void andarParaTras()
  {
    digitalWrite(motorA1, vSpeed);
    digitalWrite(motorA2, 0);
    digitalWrite(motorB1, 0);
    digitalWrite(motorB2, vSpeed);
  }
  void andarParaDireita()
  {
    digitalWrite(motorA1, vSpeed);
    digitalWrite(motorA2, LOW);
	digitalWrite(motorB1, vSpeed);
    digitalWrite(motorB2, LOW);
  }
  void andarParaEsquerda()
  {
    digitalWrite(motorA1, LOW);
	digitalWrite(motorA2, vSpeed);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, vSpeed);
  }
  void ficarParado()
  {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
  }
  void trasEsquerda()
  {
    digitalWrite(motorA1, vSpeed); 
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, 150);    
    digitalWrite(motorB2, LOW);  
  }
  void trasDireita()
  {
    digitalWrite(motorA1, LOW);   
    digitalWrite(motorA2, vSpeed);
    digitalWrite(motorB1, LOW);   
    digitalWrite(motorB2, 150); 
  }
  void frenteEsquerda()
  {
    digitalWrite(motorA1, LOW);   
    digitalWrite(motorA2, vSpeed);
    digitalWrite(motorB1, LOW); 
    digitalWrite(motorB2, 150); 
  }
  void frenteDireita()
  {
    digitalWrite(motorA1, 150); 
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, vSpeed);      
    digitalWrite(motorB2, LOW);   
  }
  void farolFrenteLigado()
  {
    digitalWrite(LED_Verd_Esq, HIGH);
    digitalWrite(LED_Verd_Dir, HIGH);
  }
  void farolFrenteDesligado()
  {
    digitalWrite(LED_Verd_Esq, LOW);
    digitalWrite(LED_Verd_Dir, LOW); 
  }
  void farolTrasLigado()
  {
    digitalWrite(LED_Verm_Esq, HIGH);
    digitalWrite(LED_Verm_Dir, HIGH);
  }
  void farolTrasDesligado()
  {
    digitalWrite(LED_Verm_Esq, LOW);
    digitalWrite(LED_Verm_Dir, LOW); 
  }
  void ligarBuzina()
  {
    tone(BUZZER, 1000);
  }
  void desligarBuzina()
  {
    noTone(BUZZER);
  }