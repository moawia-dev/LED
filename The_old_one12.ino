

enum ledStates {ON, OFF, WAVE, INCREASING}; // Here we make nicknames for the different states our program supports.
enum ledStates ledState; // We define 'ledState' as type ledStates'
enum ledStates previousLedState = ledState;

int brightness = 0; // our main variable for setting the brightness of the LEDconst int trigPin = 9;
const int echoPin = 8;
const int ledPin = 13;
const int trigPin = 9;
float velocity = 1.0; // the speed at which we change the brightness.
int p = 0; // use to keep track how often we plot
int plotFrequency = 2; // how often we plot, every Nth time.
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;


const int numReadings = 10; // higher is smoother but less responsive

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
long duration1;
float distance;
float distanceA;
float distanceB;
int ldr;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  pinMode(ledPin, OUTPUT); // set ledPin as an output.
  Serial.begin(9600); 
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);   //Reset the trigger pin
  //delay(100);
  digitalWrite(trigPin, HIGH);     //Create a 10 micro second pulse
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration1 = pulseIn(echoPin, HIGH); //Read the pulse travel time in microseconds.
  distance= duration1*0.034/2;        //Calculate the distance - speed of sound is 0.034 cm per microsecond
  
  plot("dis", distance);
  compose();
  analogWrite(ledPin, brightness);
  currentMillis = millis(); //store the current time since the program started

  
 /* int fadeAmount = 5;
if(distance < 40 && distance >=5){
  distanceA = distance; 
  fadeAmount = map(distanceA, 40, 5, 1, 5);
       brightness = brightness + fadeAmount;
       plot("4k", distance);
       if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
     }*/
}

void compose(){

    
    if(distance >= 300){
      brightness = 0;
      plot("2M", brightness);
      
    }
    
    else if(distance < 300 && distance >=150){
      distanceA = distance;
     // brightness = increase_brightness(distanceA, 1);
     brightness = map(distanceA, 300, 150, 0, 255);
   //  delay(100);
      plot("INCREASING", brightness);
      if (distanceA != distance){
        distanceA = distance;
        }
    }
  

     else if(distance < 150 && distance >=100){
      switch (ledState){
         case ON:
           plot("ON", brightness);
           brightness = 255;
            if (currentMillis - startMillis >= 250){
            changeState(OFF);
           }
           break;

         case OFF:
           plot("OFF", brightness);
           brightness = 0;
           if (currentMillis - startMillis >= 250){
            changeState(ON);
           }
           break;
      }
     }
     else if(distance < 100 && distance >=50){
      switch (ledState){
         case ON:
           plot("ON", brightness);
           brightness = 255;
            if (currentMillis - startMillis >= 150){
            changeState(OFF);
           }
           break;

         case OFF:
           plot("OFF", brightness);
           brightness = 0;
           if (currentMillis - startMillis >= 150){
            changeState(ON);
           }
           break;
      }
     }
      else if(distance < 50 && distance >=40){
      switch (ledState){
         case ON:
          // plot("ON", brightness);
           brightness = 255;
            if (currentMillis - startMillis >= 100){
            changeState(OFF);
           }
           break;

         case OFF:
         //  plot("OFF", brightness);
           brightness = 0;
           if (currentMillis - startMillis >= 100){
            changeState(ON);
           }
           break;
      }
     }else if(distance < 40 && distance >=30){
      switch (ledState){
         case ON:
          // plot("ON", brightness);
           brightness = 255;
            if (currentMillis - startMillis >= 40){
            changeState(OFF);
           }
           break;

         case OFF:
         //  plot("OFF", brightness);
           brightness = 0;
           if (currentMillis - startMillis >= 40){
            changeState(ON);
           }
           break;
      }
     }else if(distance < 30 && distance >=20){
      switch (ledState){
         case ON:
          // plot("ON", brightness);
           brightness = 255;
            if (currentMillis - startMillis >= 30){
            changeState(OFF);
           }
           break;

         case OFF:
         //  plot("OFF", brightness);
           brightness = 0;
           if (currentMillis - startMillis >= 30){
            changeState(ON);
           }
           break;
      }
     }else if(distance < 20 && distance >=10){
      switch (ledState){
         case ON:
          // plot("ON", brightness);
           brightness = 255;
            if (currentMillis - startMillis >= 20){
            changeState(OFF);
           }
           break;

         case OFF:
         //  plot("OFF", brightness);
           brightness = 0;
           if (currentMillis - startMillis >= 20){
            changeState(ON);
           }
           break;
      }
      }
      else if(distance < 10 && distance >=0){
      switch (ledState){
         case ON:
          // plot("ON", brightness);
           brightness = 255;
            if (currentMillis - startMillis >= 10){
            changeState(OFF);
           }
           break;

         case OFF:
         //  plot("OFF", brightness);
           brightness = 0;
           if (currentMillis - startMillis >= 10){
            changeState(ON);
           }
           break;
      }
     }
}
     
     
     
     
    /* else if(distance < 50 && distance >= 5){
      switch(ledState){
         case OFF:
           plot("OFF", brightness);
           brightness = 0;
           if (currentMillis - startMillis >= 200){
            changeState(WAVE);
           }
           break;
        case INCREASING:
         brightness = increase_brightness(distance, 200);
         plot("INCREASING", brightness);
         if (brightness > 250){
           changeState(WAVE);
          }
      break;
        case WAVE:
        
          plot("WAVE", brightness);
          brightness = sinewave(100,245,10); // you can tweak the parameters of the sinewave
          delay(100);
          analogWrite(ledPin, brightness);
         // if (currentMillis - startMillis >= 5000){ //change state after 5 secs by comparing the time elapsed since we last change state
          //  changeState(OFF);
          // }
           break;
      }
     }*/

  




int smooth_sensor(int sensor_value) {
    // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = sensor_value;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  return average;
  }


  void changeState(ledStates newState){
    // call to change state, will keep track of time since last state
    startMillis = millis();
    ledState = newState;
  }
  
void plot(char *state, int brightness){
    // use this function to plot a graph.
    // it will normalize the auto-scaling plotter

    if ((p % plotFrequency) == 0){
      Serial.print(state);
      Serial.print(", ");
      Serial.print(brightness);
      Serial.println(", 0, 300");
      Serial.print("Distance: ");        //Display the distance on the serial monitor
      Serial.println(distance);
    }
    p++;
  }

int increase_brightness (float distanceA, float velocity){
    return brightness = distanceA + velocity;
  }

int exponential_increase (int brightness, float velocity){
    return brightness = 1 + brightness * velocity;
}

int decrease_brightness (int brightness, float velocity){
    return brightness = brightness - 1 * velocity;
  }

int sinewave(float duration, float amplitude, int offset){
    // Generate a sine oscillation, return a number.
    // In case you are using this for analogWrite, make sure the amplitude does not exceed 256
    float period = millis()/duration; // Duration in ms determines the wavelength.
    float midpoint = amplitude / 2; // set the midpoint of the wave at half the amplitude so there are no negative numbers
    int value = midpoint + midpoint * sin ( period * 2.0 * PI );
    value = value + offset; //offset allows you to move the wave up and down on the Y-axis. Should not exceed the value of amplitude to prevent clipping.
    return value;
  }
