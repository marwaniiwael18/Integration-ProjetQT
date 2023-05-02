#include <Wire.h>
#include <Servo.h>

//#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

Servo moteur; // créer un objet Servo pour contrôler le moteur
int ledRouge = 13; // broche pour la LED rouge
int ledVerte = 12; // broche pour la LED verte
int bouton = 2; // broche pour le bouton
bool etat = false; // variable pour enregistrer l'état de la barrière

char data;

void setup() 
{
  Serial.begin(9600); // initialiser la communication série à 9600 bauds
  pinMode(ledRouge, OUTPUT); // configure la broche de la LED rouge en sortie
  pinMode(ledVerte, OUTPUT); // configure la broche de la LED verte en sortie
  pinMode(bouton, INPUT_PULLUP); // configure la broche du bouton en entrée avec pull-up
  moteur.attach(9); // attache le moteur à la broche 9
}

void loop() 
{
  if (digitalRead(bouton) == LOW) 
  { // vérifie si le bouton est enfoncé
    if (etat == false) // si la barrière est fermée
    {
      digitalWrite(ledRouge, LOW); // éteint le LED rouge
      digitalWrite(ledVerte, HIGH); // allume le LED verte
      moteur.write(90); // positionne le moteur à 90 degrés
      delay(1000); // attend une seconde
      etat = true; // enregistre que la barrière est ouverte
      Serial.println("Barriere ouverte"); // envoyer un message via la communication série
    }
    else // si la barrière est ouverte
    {
      digitalWrite(ledRouge, HIGH); // allume le LED rouge
      digitalWrite(ledVerte, LOW); // éteint le LED verte
      moteur.write(0); // positionne le moteur à 0 degré
      delay(1000); // attend une seconde
      etat = false; // enregistre que la barrière est fermée
      Serial.println("Barriere fermee"); // envoyer un message via la communication série
    }

  } 
  if (Serial.available())
  {     

    data=Serial.read();  
    if(data=='1') 
    {
      digitalWrite(ledRouge, HIGH); // allume le LED rouge
      digitalWrite(ledVerte, LOW); // éteint le LED verte
      moteur.write(0); // positionne le moteur à 0 degré
      delay(1000); // attend une seconde
      etat = false; // enregistre que la barrière est fermée
      Serial.println("Barriere fermee"); // envoyer un message via la communication série
    }
    if(data=='0') 
    {
      digitalWrite(ledRouge, LOW); // éteint le LED rouge
      digitalWrite(ledVerte, HIGH); // allume le LED verte
      moteur.write(90); // positionne le moteur à 90 degrés
      delay(1000); // attend une seconde
      etat = true; // enregistre que la barrière est ouverte
      Serial.println("Barriere ouverte"); // envoyer un message via la communication série
    } 
   
    
  }
}