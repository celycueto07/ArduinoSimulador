/*DADO */

byte dado [6][4]={
{0,0,0,1},
{0,0,1,0},
{0,0,1,1},
{0,1,0,0},
{0,1,0,1},
{0,1,1,0}
};

//Variables 
const int ledPIN = 13;
int cont=0;
int gana=0;
int pierde=0;
int numAnt=0;
int pulsa=0;
int num1,num2;
int suma=0;

//funciones
int jugada(int num1, int num2);//valida cuando el jugador gana o pierde
int lanzadas (int ante);//validad la continuacion de la jugada


void setup()
{
/* DADO  */	
	Serial.begin(9600);
	pinMode(ledPIN , OUTPUT);// Led
	
	//Led de dado 1
	pinMode(11, INPUT);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(6, OUTPUT);
	
	//led de dado 2	
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
	
	
}



void loop()
{
	pulsa = digitalRead(11);
	
	if(pulsa==1){
		
		
		num1= random(1,7);
		num2= random(1,7);
		suma=num1+num2;
		
		
		
		digitalWrite(2, dado[num1-1][3]);
		digitalWrite(3, dado[num1-1][2]);
		digitalWrite(4, dado[num1-1][1]);
		digitalWrite(6, dado[num1-1][0]);
		
		digitalWrite(7, dado[num2-1][3]);
		digitalWrite(8, dado[num2-1][2]);
		digitalWrite(9, dado[num2-1][1]);
		digitalWrite(10, dado[num2-1][0]);
		
		
		if( jugada(num1,num2)==2){
			gana++;
			cont++;
			
			Serial.print("Ha ganado la partida. sacó: ");
			Serial.println(num1+num2);
			
			Serial.print("Numero de tiros:  ");
			Serial.println(cont);
			
			Serial.print("Numero de partidas ganadas: ");
			Serial.println(gana);
			
			Serial.print("Numero de partidas perdidas: ");
			Serial.println(pierde);
			
			cont=0;
			pulsa=0;
		} else if(jugada(num1,num2)==3){
			pierde++;
			cont++;
			
			
			Serial.print("Perdió!!!. sacó: ");
			Serial.println(num1,num2);
			
			Serial.print("Lanzadas:  ");
			Serial.println(cont);
			
			Serial.print("Partidas ganadas: ");
			Serial.println(gana);
			
			Serial.print("Partidas perdidas:  ");
			Serial.println(pierde);
			
			
			cont=0;
			
		}else if(jugada(num1,num2)==1){
			
			Serial.print("Debe repetir el numero:");
			Serial.print(suma);
			Serial.println(",para ganar ");
			cont++;
			numAnt=num1+num2;
			lanzadas(numAnt);
			
			
		}else if(jugada(num1,num2)==0){
			
			Serial.print("No repitió el numero: ");
			Serial.println(numAnt);
			cont=0;
		}
		
		
		while(pulsa==1){
			pulsa=digitalRead(11);
		}
	}
	
	
	
}


int jugada(int num1, int num2){
	
	int aux = num1 + num2;
	
	if(((aux==4)||(aux==5)||(aux==6)||(aux==8)||(aux==9)||(aux==10))  &&cont==0){
		
		digitalWrite(ledPIN,HIGH);
		delay(100);
		digitalWrite(ledPIN,LOW);
		delay(100);
		digitalWrite(ledPIN,HIGH);
		delay(100);
		
		return 1;	//Debe repetir el numero
		
		
	}else if(((aux==7)||(aux==11)) && (cont==0)){
		
		digitalWrite(ledPIN,LOW);
		return 2;	//Gana la partida
		
	}else if(((aux==2)||(aux==3)||(aux==12)) && (cont==0)){
		
		return 3;	//Pierde la partida
	}
	else{
		
		digitalWrite(ledPIN,LOW);
		return 0;
	}
}

int lanzadas(int numAnt){
	
	int bandera=0;
	
	while(bandera==0){	
		
		pulsa = digitalRead(11);
		
		if	(pulsa==1){
			
			while(pulsa==1){
				pulsa=digitalRead(11);
			}	
			
			num1= random(1,7);
			num2= random(1,7);
			suma=num1+num2;
			
			digitalWrite(ledPIN,HIGH);
			delay(200);
			digitalWrite(ledPIN,LOW);
			delay(200);
			digitalWrite(ledPIN,HIGH);
			delay(200);
			
			digitalWrite(2, dado[num1-1][3]);
			digitalWrite(3, dado[num1-1][2]);
			digitalWrite(4, dado[num1-1][1]);
			digitalWrite(6, dado[num1-1][0]);
			
			digitalWrite(7, dado[num2-1][3]);
			digitalWrite(8, dado[num2-1][2]);
			digitalWrite(9, dado[num2-1][1]);
			digitalWrite(10, dado[num2-1][0]);
			
			digitalWrite(ledPIN,HIGH);
			delay(200);
			digitalWrite(ledPIN,LOW);
			delay(200);
			digitalWrite(ledPIN,HIGH);
			delay(200);
			
			if(numAnt==suma){
				
				gana++;
				cont++;
				
				Serial.print("Ganó!! sacó: ");
				Serial.println(suma);
				
				Serial.print("Lanzadas:  ");
				Serial.println(cont);
				
				Serial.print("Partidas ganadas: ");
				Serial.println(gana);
				
				Serial.print("Partidas perdidas: ");
				Serial.println(pierde);
				
				cont=0;
				bandera=1;
				digitalWrite(ledPIN,LOW);
				return 0;
			}else if(suma==7){
				
				pierde++;
				cont++;
				
				Serial.print("Perdió!!. sacó: ");
				Serial.println(suma);
				
				Serial.print("Lanzadas:  ");
				Serial.println(cont);
				
				Serial.print("Partidas ganadas: ");
				Serial.println(gana);
				
				Serial.print("Partidas perdidas:  ");
				Serial.println(pierde);
				
				cont=0;
				bandera=1;
				digitalWrite(ledPIN,LOW);
				return 0;
			}else {
				
				Serial.print("No ha sacado el numero: ");
				Serial.print(numAnt);
				Serial.print(",Numero lanzado: ");
				Serial.println(suma);
				cont ++;
				
				digitalWrite(ledPIN,HIGH);
				delay(100);
				digitalWrite(ledPIN,LOW);
				delay(100);
			}
			digitalWrite(ledPIN,HIGH);
			delay(100);
		}
		
	}
	return 0;
}


