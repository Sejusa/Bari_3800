// Pines placa h
int activate = 2;
int right_one = 4;
int right_two = 5;
int left_one = 9;
int left_two = 10;

// variables para quitar debounce
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 70;

//varaibles para boton ON que sera para el programar movimiento
int button_on = 6;
int currentStateO=LOW;
int lastStateO=LOW;
unsigned long lastTimeLectureO=0;
int contO=0;

//varaibles para boton forwrad, para mover ruedas hacia delante
int button_forward = 7;
int currentStateF=LOW;
int lastStateF=LOW;
unsigned long lastTimeLectureF=0;
int contF=0;

//varaibles para boton backward, para mover ruedas hacia atras
int button_back = 8;
int currentStateB=LOW;
int lastStateB=LOW;
unsigned long lastTimeLectureB=0;
int contB=0;

//varaibles para boton right, para mover ruedas hacia derecha
int button_right = 11;
int currentStateR=LOW;
int lastStateR=LOW;
unsigned long lastTimeLectureR=0;
int contR=0;

//varaibles para boton left, para mover ruedas hacia izquierda
int button_left = 12;
int currentStateL=LOW;
int lastStateL=LOW;
unsigned long lastTimeLectureL = 0;
int contL=0;

//varaibles para controlar lista
const int MAX_SIZE=10;
int p=0;
int list_move[MAX_SIZE];
bool state_on=0;

//varaibles para controlar botones
//int cont;
int residuo=0;

void setup() {
  pinMode(activate, OUTPUT);
  pinMode(right_one, OUTPUT);
  pinMode(right_two, OUTPUT);
  pinMode(left_one, OUTPUT);
  pinMode(left_two, OUTPUT);
  pinMode(button_forward, INPUT);
  pinMode(button_back, INPUT);
  pinMode(button_right, INPUT);
  pinMode(button_left, INPUT);
  pinMode(button_on, INPUT);
  Serial.begin(9600); //Para iniciar la comunicación con la consola.:
  move(0);
}
void loop() {

   press_button(button_forward,currentStateF,lastStateF,lastTimeLectureF);
   press_button(button_back,currentStateB,lastStateB,lastTimeLectureB);
   press_button(button_left,currentStateL,lastStateL,lastTimeLectureL);
   press_button(button_right,currentStateR,lastStateR,lastTimeLectureR);
   press_button(button_on,currentStateO,lastStateO,lastTimeLectureO);
}
void move(int number)
{
  switch(number)
  {
    case 1: //Movimiento para adelante.
      digitalWrite(right_one, HIGH);
      digitalWrite(left_one, HIGH);
      digitalWrite(right_two, LOW);
      digitalWrite(left_two, LOW);
      break;

    case 2: //Movimiento hacia atrás.
        digitalWrite(right_one, LOW);
        digitalWrite(left_one, LOW);
        digitalWrite(right_two, HIGH);
        digitalWrite(left_two, HIGH);
        break;

      case 3: //Movimiento hacia la izquierda. Hacemos girar la rueda derecha pero no la izquierda para girar.
        digitalWrite(right_one, LOW);
        digitalWrite(left_one, HIGH);
        digitalWrite(right_two, LOW);
        digitalWrite(left_two, LOW);
        break;

      case 4: //Movimiento hacia la derecha. Hacemos girar la rueda izquierda pero no la derecha para girar.
        digitalWrite(right_one, HIGH);
        digitalWrite(left_one, LOW);
        digitalWrite(right_two, LOW);
        digitalWrite(left_two, LOW);
        break;

      case 0: //Para parar las ruedas.
        digitalWrite(right_one, LOW);
        digitalWrite(left_one, LOW);
        digitalWrite(right_two, LOW);
        digitalWrite(left_two, LOW);
  }
}

void press_button(int button, int &currentState, int &lastState, unsigned long &lastTimeLecture ){
      // Note: &variable to indicate the input variable is a reference of the global variables, it means,
      // that the variable chenges within function will modify the global variable
        // current state ==last state -> not press button
    if ( currentState==digitalRead(button) ) {

      lastTimeLecture = 0;
    }
    // current state!= las state-> press button,

    else{
      //if last time lecture ==0 -> we must save switch time
      if (lastTimeLecture == 0 ) {

        lastTimeLecture = millis();
      }
      else{
      // if last_time_lecture!=0, check if debounce delay has passed
        if ( millis()-lastTimeLecture> debounceDelay ){
        // if debounce  delay has passed ->state has changed
          currentState = !currentState;
        }
      }
    }

    if(lastState==LOW && currentState==HIGH){
      //0----______1
      read_inputs(button);
  
    }

  lastState=currentState;
}


//función para detectar el boton pulsado
void read_inputs(int button){
  switch(button){
    case 7:
      move(1);
      contF++;
       if((contF % 2)==residuo){ //nos servira para que en la segunda pulsacion el robot se pare
        move(0); 
      }
      break;
    case 8:
      move(2);
      contB++;
       if((contB % 2)==residuo){ //nos servira para que en la segunda pulsacion el robot se pare
        move(0);
      }
      break;
    case 11:
      move(3);
      contR++;
      if((contR % 2)==residuo){ //nos servira para que en la segunda pulsacion el robot se pare
        move(0);
      }
      break;
    case 12:
      move(4);
      contL++;
      if((contL % 2)==residuo){ //nos servira para que en la segunda pulsacion el robot se pare
        move(0);
      }
      break;
    case 6:
      contO++;
      movimiento();
      if(contO == 11){//para accionar la lista
        print_lista();
      }
      break;
      
  }


}
void movimiento(){
    //Serial.println("hola");
  
   // Serial.println(lastStateF);
  //  Serial.println(lastStateB);
  //  Serial.println(lastStateR);
  //  Serial.println(lastStateL);
    
    if (currentStateF==1)
    {
      move(0);
      add_element(1);
    //  Serial.println("hola");
    }
    if (currentStateB==1)
    {
      move(0);
      add_element(2);
     
    }
    if (currentStateR==1)
    {
      move(0);
      add_element(3);
      
    }
    if (currentStateL==1)
    {
      move(0);
      add_element(4);
     
      
    }
  
}
void print_lista()
{
  for (int i=0; i<=p; i++)
      {
        move(list_move[i]);
        delay(3000);
      }
}

void add_element(int number_list)
{
  if (p < MAX_SIZE)
  {
    list_move[p] = number_list;
    p++;
  }
}

void delete_array()
{

 for(int j = 0; j < p; j++)
 {
  list_move[j]=0;
 }
 p=0;
}

//Per poder utilitzar el programa moviment hauras de pulsa el boto amb el moviment que vols i despres mantenint pulsat el boto del moviment tindras que clicar el boto 6 per poder afegir la variable a la llista
