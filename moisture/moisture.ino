int y[8] = {1,2,3,4,5,6,7,8};
int d[4] = {12,11,10,9};

// Digital screen map
int digital[10][8] = {
  {6,y[0],y[1],y[2],y[3],y[4],y[5]},        // 0
  {2,y[1],y[2]},                            // 1
  {5,y[0],y[1],y[3],y[4],y[6]},             // 2
  {5,y[0],y[1],y[2],y[3],y[6]},             // 3
  {4,y[1],y[2],y[5],y[6]},                  // 4
  {5,y[0],y[2],y[3],y[5],y[6]},             // 5
  {6,y[0],y[2],y[3],y[4],y[5],y[6]},        // 6
  {3,y[0],y[1],y[2]},                       // 7
  {7,y[0],y[1],y[2],y[3],y[4],y[5],y[6]},   // 8
  {6,y[0],y[1],y[2],y[3],y[5],y[6]}         // 9
};

long  n = 1;
int   x = 100;
double del = 200000;

void setup()
{
  // Serial init on 9600 baud
  Serial.begin(9600);

  pinMode(A0, INPUT);   // Moisture sensor
  pinMode(13, OUTPUT);  // Led

  // Initialize segments
  for (int i=0;i<8;i++) {
    pinMode(y[i],OUTPUT); 
  }

  // Initialize digits
  for(int i=0;i<4;i++) {
    pinMode(d[i],OUTPUT); 
  }
}

void loop()
{
  // Retrieve moisture sensor value
  int SensorValue = analogRead(A0);
  String sValue = String(SensorValue);

  // Split sensor value to write specific number on digital screen
  int first = sValue.substring(0, 1).toInt();
  int secon = sValue.substring(1, 2).toInt();
  int third = sValue.substring(2, 3).toInt();
  
  // State: DRY
  if (SensorValue < 1000 && SensorValue >= 600) {
    digitalWrite(13, HIGH);
  }

  // State: HUMID
  if (SensorValue < 600 && SensorValue >= 370) {
    digitalWrite(13, LOW);
  }

  // State: WATER
  if (SensorValue < 370) {
    digitalWrite(13, LOW);
  }

  // Write digital screen numbers
  clearLEDs();
  pickDigit(2);
  showDigital(first);
  delayMicroseconds(del);
  
  clearLEDs();
  pickDigit(3);
  showDigital(secon);
  delayMicroseconds(del);
  
  clearLEDs();
  pickDigit(4);
  showDigital(third);
  delayMicroseconds(del);
}

/*
 * This function clears all LEDs
 */
void clearLEDs(){
  for(int i=0;i<8;i++) {
    digitalWrite(y[i],LOW);
  }
}

/*
 * Select a digit (1 to 4)
 */
void pickDigit(int x){
  for(int i=0;i<4;i++) {
    digitalWrite(d[i],HIGH);    
  }

  if(x>4) {
    x=4;
  }
  digitalWrite(d[x-1],LOW);
}

/*
 * Switch ON specific segment to display the exected number
 */
void showDigital(int x){
  for(int i=1;i<=digital[x][0];i++) {
    digitalWrite(digital[x][i], HIGH);
  }    
}
