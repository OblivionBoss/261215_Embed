#define Button_Pin 22
#define Sound_Pin  26
hw_timer_t *My_timer = NULL; //
                 //L_A L_B   C   D   E    F    G    A    B   H_C   H_D  H_E  H_F  H_G  H_A
                 //0    1    2   3   4    5    6    7    8    9    10   11   12   13   14
int NoteFreq[] = {932,988,1047,1175,1319,1397,1568,1760,1976,2093,2349,2637,2794,3136,3520}; // octave 6 hearable else is shit
int SharpNoteFreq[] = {1109,1245,1480,1661,1865,2217,2489,2960,3322,3729}; //C#, Eb, F#, G#, Bb, H_C#, H_Eb, H_F#, H_G#, H_Bb
int Note[(int) (sizeof (NoteFreq) / sizeof (NoteFreq[0]))];
int SharpNote[(int) (sizeof (SharpNoteFreq) / sizeof (SharpNoteFreq[0]))];
                 //   Whole ,  Half ,Quarter, Eighth  , Sixteenth ,Tirty-second
double Duration[] = {   4   ,   2   ,   1   ,   0.5   ,    0.25   ,    0.125   }; 
double Speed = 0.25; // 0.25 -> 0.5 -> 1 -> 2 -> 4 -> 0.25 -> REPEAT

void IRAM_ATTR speedUP(){
  if(Speed < 4) Speed *= 2 ;
  else Speed = 0.25;
  Serial.println(Speed);
}

void setupRegNote(){ for(int i = 0; i < (int) (sizeof (Note) / sizeof (Note[0])); i++) Note[i] = F2T(NoteFreq[i]); }
void setupSharpNote(){ for(int i = 0; i < (int) (sizeof (SharpNote) / sizeof (SharpNote[0])); i++) SharpNote[i] = F2T(SharpNoteFreq[i]); }

void NoteBlock(int lambda, double Duration){// use T,input 0 to mute
  int time = millis();
  while(millis() - time < 1000*Duration/Speed) timerAlarmWrite(My_timer,(int) lambda, true);
  //delay(1000*Duration*Speed);
}

void RestBlock(double Duration){// use T,input 0 to mute
  int time = millis();
  while(millis() - time < 1000*Duration/Speed) timerAlarmWrite(My_timer, 0 , true);
}

//void DoubleTieBlock(int lambdaF, int DF,int lambdaS, int DS){// use T,input 0 to mute
//  timerAlarmWrite(My_timer,(int) lambdaF, true);
//  timerAlarmWrite(My_timer,(int) lambdaS, true);
//  delay(1000*(DF+DS)*Speed);
//}

double Dot(double D,int t){
	double tmp = 1;
	for(int i = 0; i < t; i++) tmp *= 2;
	return D*(1 + ((tmp-1)/tmp));
}

void testNote(){ for(int i = 0; i < (int) (sizeof (Note) / sizeof (Note[0])); i++) NoteBlock(Note[i],Duration[2]); }

int F2T(int F) { return (1000000/(F*2)); }

void TetrisKorobeiniki(){
  NoteBlock(Note[11],Duration[2]);
  NoteBlock(Note[8],Duration[3]);
  NoteBlock(Note[9],Duration[3]);
  NoteBlock(Note[10],Duration[2]);
  NoteBlock(Note[9],Duration[3]);
  NoteBlock(Note[8],Duration[3]);

  NoteBlock(Note[7],Duration[2]);
  NoteBlock(Note[7],Duration[3]);
  NoteBlock(Note[9],Duration[3]);
  NoteBlock(Note[11],Duration[2]);
  NoteBlock(Note[10],Duration[3]);
  NoteBlock(Note[9],Duration[3]);

  NoteBlock(Note[8],Dot(Duration[2], 1));
  NoteBlock(Note[9],Duration[3]);
  NoteBlock(Note[10],Duration[2]);
  NoteBlock(Note[11],Duration[2]);

  NoteBlock(Note[9],Duration[2]);
  NoteBlock(Note[7],Duration[2]);
  NoteBlock(Note[7],Duration[2]);
  RestBlock(Duration[2]);

  RestBlock(Duration[3]);
  NoteBlock(Note[10],Duration[2]);
  NoteBlock(Note[12],Duration[3]);
  NoteBlock(Note[14],Duration[2]);
  NoteBlock(Note[13],Duration[3]);
  NoteBlock(Note[12],Duration[3]);

  NoteBlock(Note[11],Dot(Duration[2], 1));
  NoteBlock(Note[9],Duration[3]);
  NoteBlock(Note[11],Duration[2]);
  NoteBlock(Note[10],Duration[3]);
  NoteBlock(Note[9],Duration[3]);

  NoteBlock(Note[8],Dot(Duration[2], 1));
  NoteBlock(Note[9],Duration[3]);
  NoteBlock(Note[10],Duration[2]);
  NoteBlock(Note[11],Duration[2]);

  NoteBlock(Note[9],Duration[2]);
  NoteBlock(Note[7],Duration[2]);
  NoteBlock(Note[7],Duration[2]);
  RestBlock(Duration[2]);

  NoteBlock(Note[11],Duration[1]);
  NoteBlock(Note[9],Duration[1]);

  NoteBlock(Note[10],Duration[1]);
  NoteBlock(Note[8],Duration[1]);

  NoteBlock(Note[9],Duration[1]);
  NoteBlock(Note[7],Duration[1]);

  NoteBlock(SharpNote[3],Duration[0]);

  NoteBlock(Note[11],Duration[1]);
  NoteBlock(Note[9],Duration[1]);

  NoteBlock(Note[10],Duration[1]);
  NoteBlock(Note[8],Duration[1]);

  NoteBlock(Note[9],Duration[2]);
  NoteBlock(Note[11],Duration[2]);
  NoteBlock(Note[14],Duration[2]);
  NoteBlock(Note[14],Duration[2]);

  NoteBlock(SharpNote[8],Duration[0]);
  // LOOP HERE
  RestBlock(Duration[3]);
  NoteBlock(Note[10],Duration[2]);
  NoteBlock(Note[12],Duration[3]);
  NoteBlock(Note[14],Duration[2]);
  NoteBlock(Note[13],Duration[3]);
  NoteBlock(Note[12],Duration[3]);

  RestBlock(Duration[3]);
  NoteBlock(Note[11],Duration[2]);
  NoteBlock(Note[9],Duration[3]);
  NoteBlock(Note[11],Duration[2]);
  NoteBlock(Note[10],Duration[3]);
  NoteBlock(Note[9],Duration[3]);

  RestBlock(Duration[3]);
  NoteBlock(Note[8],Duration[2]);
  NoteBlock(Note[9],Duration[3]);
  NoteBlock(Note[10],Duration[2]);
  NoteBlock(Note[11],Duration[2]);

  RestBlock(Duration[3]);
  NoteBlock(Note[9],Duration[2]);
  NoteBlock(Note[7],Duration[3]);
  NoteBlock(Note[7],Duration[2]);
  RestBlock(Duration[2]);
}

void IMBLUE(){ 
  //Initial
  NoteBlock(Note[7],Duration[1]);

  for(int l = 0 ; l < 3 ; l++){
    NoteBlock(Note[8],Duration[2]);
    NoteBlock(Note[3],Duration[2]);
    NoteBlock(Note[6],Duration[2]);
    NoteBlock(Note[8],Duration[2]);

    NoteBlock(Note[9],Duration[2]);
    NoteBlock(Note[4],Duration[2]);
    NoteBlock(Note[7],Duration[2]);
    NoteBlock(Note[8],Duration[2]);

    NoteBlock(Note[8],Duration[2]);
    NoteBlock(Note[6],Duration[2]);
    NoteBlock(Note[8],Duration[2]);
    NoteBlock(Note[10],Duration[2]);

    NoteBlock(Note[11],Duration[2]);
    NoteBlock(Note[6],Duration[2]);
    NoteBlock(Note[10],Duration[2]);
    NoteBlock(Note[9],Duration[2]);
  }

  //End
  NoteBlock(Note[6],Duration[2]);
  NoteBlock(Note[5],Duration[2]);
  NoteBlock(Note[6],Duration[2]);
  NoteBlock(Note[7],Duration[2]);
}

void PacMan(){
  NoteBlock(Note[1],Duration[4]);
  NoteBlock(Note[8],Duration[4]);
  NoteBlock(SharpNote[2],Duration[4]);
  NoteBlock(Note[3],Duration[4]);
  NoteBlock(Note[8],Duration[5]);
  NoteBlock(Note[5],Dot(Duration[3],1));
  NoteBlock(Note[3],Duration[3]);
  NoteBlock(Note[2],Duration[4]);
  NoteBlock(Note[9],Duration[4]);
  NoteBlock(Note[6],Duration[4]);
  NoteBlock(Note[4],Duration[4]);
  NoteBlock(Note[9],Duration[5]);
  NoteBlock(Note[6],Dot(Duration[3],1));
  NoteBlock(Note[4],Duration[3]);

  NoteBlock(Note[1],Duration[4]);
  NoteBlock(Note[8],Duration[4]);
  NoteBlock(SharpNote[2],Duration[4]);
  NoteBlock(Note[3],Duration[4]);
  NoteBlock(Note[8],Duration[5]);
  NoteBlock(Note[5],Dot(Duration[3],1));
  NoteBlock(Note[3],Duration[3]);
  NoteBlock(Note[3],Duration[5]);
  NoteBlock(Note[4],Duration[5]);
  NoteBlock(Note[5],Duration[4]);
  NoteBlock(Note[5],Duration[5]);
  NoteBlock(SharpNote[2],Duration[5]);
  NoteBlock(Note[6],Duration[4]);
  NoteBlock(Note[6],Duration[5]);
  NoteBlock(SharpNote[3],Duration[4]);
  NoteBlock(Note[7],Duration[3]);
  NoteBlock(Note[8],Duration[3]);
}

void IRAM_ATTR onTimer(){  digitalWrite(Sound_Pin, !digitalRead(Sound_Pin)); }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(Button_Pin, INPUT_PULLUP);//if press OFF (LOW) else ON (HIGH) INPUT_PULLUP
  pinMode(Sound_Pin, OUTPUT);
  attachInterrupt(Button_Pin, &speedUP, RISING); // RISING or FALLING
  My_timer = timerBegin(1, 80, true);
  timerAttachInterrupt(My_timer, &onTimer, true); // point to the ISR
  timerAlarmWrite(My_timer, 1000000, true);
  timerAlarmEnable(My_timer);
  setupRegNote();
  setupSharpNote();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Sound_Pin, HIGH);
  //testNote();
  //for(int i = 0; i < (int) (sizeof (NoteFreq) / sizeof (NoteFreq[0])); i++){
  //  Serial.println(Note[i]);
  //}
  //IMBLUE(); //Too high
  //TetrisKorobeiniki(); //Too high
  PacMan(); 
}
