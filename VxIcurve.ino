//*************************************************************************************
//*************************************************************************************
//****************************MEASURE V-I CURVE****************************************
//*************************AQUIRE UP TO FIVE DATA**************************************
//*************************************************************************************


//****** HARDWARE DEFINITIONS
#define LED 7
#define PWMPin 5
//*******VARIABLES DEFINITIONS
char Character[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };  //Excel Column
int option, i, ii, j, jj, PWPin;
float ADC_0, ADC_1, VOLT, CURR, DV;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(PWMPin, OUTPUT);
  analogReference(DEFAULT);
  analogWrite(PWMPin, 255);
}



void loop()

{
  if (Serial.available() > 0)

  {
    option = Serial.read();
  }

  switch (option)

  {


    case 'A':  //Send data to cell

      digitalWrite(LED, HIGH);
      jj = 2;

      for (i = 5; i <= 255; i = i + 5) {
        analogWrite(PWMPin, i);
        delay(10);

        ADC_0 = 0;
        for (j = 0; j < 100; j++)  //READING VOLTAGE TO CALCULATE CURRENT
        {
          delay(1);
          ADC_0 = ADC_0 + analogRead(0);
        }
        ADC_0 = ADC_0 / 100;

        ADC_1 = 0;
        for (j = 0; j < 100; j++)  //READING VOLTAGE CAPACITOR
        {
          delay(1);
          ADC_1 = ADC_1 + analogRead(1);
        }
        ADC_1 = (ADC_1 / 100);

        DV = (ADC_1 - ADC_0);

        CURR = (5000 * ADC_0 / 1023) / 47;  //R = 47 Ohm
        VOLT = (5.0 * DV / 1023);


        Serial.print("CELL,SET,");    //Specify the Excel Cell
        Serial.print(Character[ii]);  //Specify the Column
        Serial.print(jj);             //Specify the Line
        Serial.print(",");
        Serial.println(CURR);  //Send the data to specific cell

        Serial.print("CELL,SET,");
        Serial.print(Character[ii + 1]);
        Serial.print(jj);
        Serial.print(",");
        Serial.println(VOLT);
        jj = jj + 1;
      }
      ii = ii + 2;
      if (ii > 9) {
        ii = 0;
      }
      digitalWrite(LED, LOW);
      option = 100;
      break;



    case 'D':
      //**********RESETTING THE SPREADSHEET******************

      ii = 0;
      jj = 2;
      digitalWrite(LED, HIGH);
      for (i = 0; i <= 51; i = i + 1) {
        Serial.print("DATA,");
        Serial.print(0);
        Serial.print(",");
        Serial.print(0);
        Serial.print(",");
        Serial.print(0);
        Serial.print(",");
        Serial.print(0);
        Serial.print(",");
        Serial.print(0);
        Serial.print(",");
        Serial.print(0);
        Serial.print(",");
        Serial.print(0);
        Serial.print(",");
        Serial.print(0);
        Serial.print(",");
        Serial.print(0);
        Serial.print(",");
        Serial.println(0);
      }
      Serial.println("RESETROW");
      //delay(500);
      digitalWrite(LED, LOW);

      option = 100;
      break;


    case 'E':  //Receiving Parameters
               //**In this Application we are not using this functionality**

      digitalWrite(LED, HIGH);
      Serial.parseInt();
      Serial.parseInt();
      Serial.parseInt();
      Serial.parseInt();
      digitalWrite(LED, LOW);

      option = 100;
      break;

    default:
      delay(1);
  }
}
