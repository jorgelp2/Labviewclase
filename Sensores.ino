uint16_t const cabecera="EFFE";
uint32_t Hexa;
char estado="A",s[17];
float sensor1, sensor2, sensor3, tempC, tempC1, tempC2, mv, mv1, mv2, Voltaje, Voltaje1, Voltaje2;
float temp1;
int in1=0, in2=A1, in3=A2;
unsigned long codigo;
unsigned char *dato, *voltaje;
String Exa; 
int condicion=0;

struct trama
{
  uint16_t cabecera;
  char estado;
  float voltaje1;
  float voltaje2;
  float voltaje3;
  uint8_t otros;
  uint8_t cheksum;
};

struct trama trama2;

uint8_t chequeo(void* d, unsigned char n)
{
 uint8_t c=0;
 unsigned char* ptr = d;
 unsigned char i;
 c = ptr[0];
 for (i=0;i<n-1;i++)
 {
  c=c^ptr[i+1];
 }
 return(c); 
 }

void setup() {
    Serial.begin(9600);
}

void loop() {
  //LECTURA SENSORES
  tempC = analogRead(in1);
  tempC1 = analogRead(in2);
  tempC2 = analogRead(in3);
  //CONVERSION A VOLATAJE
  mv = (tempC*5000)/1023;
  Voltaje = mv/1000;
  //Voltaje = 1.5;
  //voltaje=(unsigned char*)(&Voltaje);
  //Serial.print(*voltaje, HEX);
  mv1 = (tempC1*5000)/1023;
  Voltaje1 = mv1/1000;
  mv2 = (tempC2*5000)/1023;
  Voltaje2 = mv2/1000;  
  //VALORES TRAMA
  trama2.cabecera=0XFEEF;
  trama2.estado=0X41;
  trama2.voltaje1=Voltaje;
  trama2.voltaje2=Voltaje1;
  trama2.voltaje3=Voltaje2;
  trama2.otros=0.0;
  trama2.cheksum=chequeo(&trama2.estado,sizeof(trama2)-3);
   
  dato = (unsigned char*)(&trama2);
  int x= sizeof(trama2);
  for (int i=0; i<x; i++)
  {
    //Serial.print(*(dato+i), HEX);
    codigo=*(dato+i);
    sprintf(s, "%02x", codigo);
    Serial.print(s);
    //Exa=String(*(dato+i),HEX);
    //Serial.print(Exa);
        
  }
  delay(2000);
  Serial.println();
  
//Serial.println(sizeof(trama2)); 
  
//  
}
