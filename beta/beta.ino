int new_v = 0;
volatile unsigned long tmp[80] = {0};
volatile int nbr_interuption = 0;
int dt = 0;
int val[33] = {0};
void setup() {
  pinMode(2, INPUT);
  Serial.begin(115200);
    Serial.println("Read");
  attachInterrupt(0, ir, LOW);

}

void loop() {
            
	if(nbr_interuption > 0)
		dt = micros()-tmp[nbr_interuption-1];
	if(nbr_interuption >= 80 ||  dt > 11000 && nbr_interuption > 1)
	{
                 cli();
                int b = 0;
		for(int a = 2; a < nbr_interuption ; a += 2)
		{
			if(tmp[a]-tmp[a-1] <1000)
				val[b] = 0;
			else
				val[b] = 1;
                        b++;
                        
		}
                Serial.println();
		EICRA = (EICRA&~(1<<ISC01|1<<ISC00)); //Interuption à logique bas
                //Serial.print("ee");Serial.println(value);
	       // Serial.println(nbr_interuption);
        nbr_interuption = 0;
        sei();
        new_v = 1;	
	}
        if(new_v)
        {
          cli();
          for(int a = 0; a<33;a++)
            Serial.print(val[a]);
          Serial.println();
          new_v = 0;
          sei();
        }
}
void ir()
{
	tmp[nbr_interuption] = micros();
	if(nbr_interuption == 0)
		EICRA = (EICRA&~(1<<ISC01))|(1<<ISC00); //Interuption à chaque changement logique
	if(nbr_interuption == 1)
	{
		int dt = (tmp[1]-tmp[0]);
		if(dt <= 9700 && dt >= 9400)
			nbr_interuption++;
		else
			nbr_interuption = 0;
	}
	else
		nbr_interuption++;
  
}
