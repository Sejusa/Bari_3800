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
bool on = false;

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
  if(digitalRead(button_on) == HIGH && on == false) //Si pulsamos el pulsador.
  {
    move('R');
    on = true;
  }

  if(digitalRead(button_on) == HIGH && on == true)
    {
      move('S');
      on = false;
    }
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
