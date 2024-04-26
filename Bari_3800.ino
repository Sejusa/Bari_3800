int activate = 2; //Para activar el puente h.
int right_one = 4;
int right_two = 5;
int left_one = 9;
int left_two = 10;
int button_forward = 7;
int button_back = 8;
int button_right = 11;
int button_left = 12;
int button_on = 6;
int on;

// Variables will change:
int buttonState = LOW;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 70;    // the debounce time; increase if the output flickers

bool motorRunning = false; // Variable para rastrear si el motor está girando o no.

int forward;
int backward;
int right;
int left;

int button;

void setup()
{
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
  Serial.begin(9600); //Para iniciar la comunicación con la consola.
}

void loop()
{ 
  actual_Button();
}

void move(char mov)
{
  switch(mov)
  {
    case 'F': //Movimiento para adelante.
      digitalWrite(right_one, HIGH);
      digitalWrite(left_one, HIGH);
      digitalWrite(right_two, LOW);
      digitalWrite(left_two, LOW);
      break;

    case 'B': //Movimiento hacia atrás.
        digitalWrite(right_one, LOW);
        digitalWrite(left_one, LOW);
        digitalWrite(right_two, HIGH);
        digitalWrite(left_two, HIGH);
        break;

      case 'L': //Movimiento hacia la izquierda. Hacemos girar la rueda derecha pero no la izquierda para girar.
        digitalWrite(right_one, LOW);
        digitalWrite(left_one, HIGH);
        digitalWrite(right_two, LOW);
        digitalWrite(left_two, LOW);
        break;

      case 'R': //Movimiento hacia la derecha. Hacemos girar la rueda izquierda pero no la derecha para girar.
        digitalWrite(right_one, HIGH);
        digitalWrite(left_one, LOW);
        digitalWrite(right_two, LOW);
        digitalWrite(left_two, LOW);
        break;
      
      case 'S': //Para parar las ruedas.
        digitalWrite(right_one, LOW);
        digitalWrite(left_one, LOW);
        digitalWrite(right_two, LOW);
        digitalWrite(left_two, LOW);
  }
}

void turn_On(int pin) { 
    int reading = digitalRead(pin);
    on = LOW;

    if (reading != lastButtonState) //Comprueba si el estado leído del botón es diferente al último estado guardado (lastButtonState).
    {
        lastDebounceTime = millis(); //Si hay un cambio en el estado del botón, actualiza el tiempo del último rebote (debounce) con el tiempo actual en milisegundos.
    }

    if ((millis() - lastDebounceTime) > debounceDelay) // Comprueba si ha pasado el tiempo de rebote (debounceDelay) desde el último rebote.
    {
      if (reading != buttonState) {
          buttonState = reading; //Si hay un cambio en el estado del botón, se actualiza la variable buttonState con el nuevo estado leído del botón. 

          if (buttonState == HIGH) 
          {
              on = !on; // Invierte el estado de la variable on. Si on es true, se convierte en false, y viceversa. 
          }
        }
    }

    if (on == HIGH) // Si el botón está presionado
    {
      if (motorRunning) // Si las ruedas ya están girando
      { 
          Serial.println("Paco");
          move('S'); // Detener las ruedas
          motorRunning = false;
      }

      else 
      {
          if(pin == forward)
          {
            move('F');
            motorRunning = true;
          }

          else if(pin == backward)
          {
            move('B');
            motorRunning = true;
          }

          else if(pin == right)
          {
            move('R');
            motorRunning = true;
          }

          else if(pin == left)
          {
            move('L');
            motorRunning = true;
          }
      }
    }

    lastButtonState = reading; //Actualiza el último estado del botón con el estado leído actual para usarlo en la próxima iteración de la función.
}
void actual_Button()
{
  forward = digitalRead(button_forward);
  backward = digitalRead(button_back);
  right = digitalRead(button_right);
  left = digitalRead(button_left);

  if(forward == 0 && backward == 0 && right == 0 && left == 0)
  {
    
  }

  if(forward == 0 && backward == 0 && right == 0 && left == 1)
  {
    button = left;
    turn_On(button);
  }

  if(forward == 0 && backward == 0 && right == 1 && left == 0)
  {
    button = right;
    turn_On(button);
  }

  if(forward == 0 && backward == 1 && right == 0 && left == 0)
  {
    button = backward;
    turn_On(button);
  }

  if(forward == 1 && backward == 0 && right == 0 && left == 0)
  {
    button = forward;
    turn_On(button);
  }
}
