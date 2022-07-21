 /*
 keyestudio 4wd BT Car V2.0
 lesson 9.1
 matrix
 http://www.keyestudio.com
*/ 
//get the data of smile pattern in the modulus tool

#include "IRremote.h"


int receiver = 3; // Signal Pin of IR receiver to Arduino Digital Pin 11
unsigned char zero[] = {0x00, 0x00, 0x00, 0x00, 0xff, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xff, 0x00, 0x00, 0x00, 0x00};
unsigned char one[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x81, 0x81, 0xff, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00};
unsigned char two[] = {0x00, 0x00, 0x00, 0x00, 0xe1, 0x91, 0x91, 0x91, 0x91, 0x8f, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00};
unsigned char three[] = {0x00, 0x00, 0x00, 0x00, 0x81, 0x81, 0x89, 0x89, 0x89, 0x89, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char four[] = {0x00, 0x00, 0x00, 0x00, 0x0f, 0x08, 0x08, 0x08, 0x08, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char five[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 0x91, 0x91, 0x91, 0x91, 0xf1, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char six[] = {0x00, 0x00, 0x00, 0x00, 0xff, 0x91, 0x91, 0x91, 0x91, 0x91, 0xf1, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char seven[] = {0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x11, 0x11, 0x11, 0xff, 0x10, 0x10, 0x00, 0x00, 0x00};
unsigned char eight[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x89, 0x89, 0x89, 0x89, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char nine[] = {0x00, 0x00, 0x00, 0x00, 0x1f, 0x11, 0x11, 0x11, 0x11, 0x11, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char clear[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{
  Serial.println(results.value, HEX);
  switch(results.value)

  {

  case 0xFF6897: Serial.println("1");  matrix_display(one);   break;
  case 0xFF9867: Serial.println("2");  matrix_display(two);    break;
  case 0xFFB04F: Serial.println("3");  matrix_display(three);   break;
  case 0xFF30CF: Serial.println("4");  matrix_display(four);   break;
  case 0xFF18E7: Serial.println("5");  matrix_display(five);   break;
  case 0xFD6897: Serial.println("6");  matrix_display(six);   break;
  case 0xFD18E7: Serial.println("7");  matrix_display(seven);   break;
  case 0xFD9867: Serial.println("8");  matrix_display(eight);   break;
  case 0xFD58A7: Serial.println("9");  matrix_display(nine);   break;
  case 0xFF4AB5: Serial.println("0");  matrix_display(zero);   break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button   ");

  }// End Case

  delay(500); // Do not get immediate repeat


} //END translateIR








#define SCL_Pin  A5  //Set clock pin to A5
#define SDA_Pin  A4  //Set data pin to A4
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  matrix_display(clear);
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
    //Set pin to output
  pinMode(SCL_Pin,OUTPUT);
  pinMode(SDA_Pin,OUTPUT);
  
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
  //Clear the matrix display
  //matrix_display(clear);
}/*--(end setup )---*/

void loop(){

 if (irrecv.decode(&results)) // have we received an IR signal?

  {
    //matrix_display(clear);
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  


  
  //matrix_display(smile);  //display smile pattern
}
//this function is used for dot matrix display
void matrix_display(unsigned char matrix_value[])
{
  IIC_start();  //the function to call the data transmission
  IIC_send(0xc0);  //Select address
  
  for(int i = 0;i < 16;i++) //Pattern data has 16 bytes
  {
     IIC_send(matrix_value[i]); //data to convey patterns
  }
  IIC_end();   //end the transmission of patterns data
  IIC_start();
  IIC_send(0x8A);  //display control, set pulse width to 4/16
  IIC_end();
}
//  the condition that data transmission starts
void IIC_start()
{
  digitalWrite(SCL_Pin,HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin,HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin,LOW);
  delayMicroseconds(3);
}
// transmit data
void IIC_send(unsigned char send_data)
{
  for(char i = 0;i < 8;i++)  //Every character has 8 bits
  {
      digitalWrite(SCL_Pin,LOW);  //pull down the SCL_Pin to change the signal of SDA
      delayMicroseconds(3);
      if(send_data & 0x01)  //1 or 0 of byte  is used to set high and low level of SDA_Pin
      {
        digitalWrite(SDA_Pin,HIGH);
      }
      else
      {
        digitalWrite(SDA_Pin,LOW);
      }
      delayMicroseconds(3);
      digitalWrite(SCL_Pin,HIGH); //Pull up SCL_Pin to stop data transmission
      delayMicroseconds(3);
      send_data = send_data >> 1;  //Detect bit by bit, so move the data right by one bit
  }
}
//the sign that data transmission ends 
void IIC_end()
{
  digitalWrite(SCL_Pin,LOW);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin,LOW);
  delayMicroseconds(3);
  digitalWrite(SCL_Pin,HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin,HIGH);
  delayMicroseconds(3);
}//****************************************************************************************
