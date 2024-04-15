int activate = 2;
int right_one = 4;
int right_two = 5;
int left_one = 9;
int  left_two = 10;

void setup()
{
  pinMode(activate, OUTPUT);
  pinMode(right_one, OUTPUT);
  pinMode(right_two, OUTPUT);
  pinMode(left_one, OUTPUT);
  pinMode(left_two, OUTPUT);
  Serial.begin(9600);
}

void loop()
{ 
  move('R');

  
  //El motor gira 5 segundos a la derecha.
  /*digitalWrite(activate, HIGH);
  digitalWrite(left_one, HIGH);
  digitalWrite(left_two, LOW);
  delay(5000);
  
  //Lo paramos
  digitalWrite(left_one, LOW);
  delay(1000);
  
  //El motor gira 5 segundos a la izquierda.
  digitalWrite(activate, LOW);
  digitalWrite(left_one, LOW);
  digitalWrite(left_two, HIGH);
  delay(5000);
  
  //Lo paramos
  digitalWrite(left_two, LOW);
  delay(1000);*/
}

void move(char mov)
{

  switch(mov)
  {
    case 'F':
      digitalWrite(right_one, HIGH);
      digitalWrite(left_one, HIGH);
      digitalWrite(right_two, LOW);
      digitalWrite(left_two, LOW);
      break;

    case 'B':
        digitalWrite(right_one, LOW);
        digitalWrite(left_one, LOW);
        digitalWrite(right_two, HIGH);
        digitalWrite(left_two, HIGH);
        break;

      case 'L':
        digitalWrite(right_one, LOW);
        digitalWrite(left_one, HIGH);
        digitalWrite(right_two, LOW);
        digitalWrite(left_two, LOW);
        break;

      case 'R':
        digitalWrite(right_one, HIGH);
        digitalWrite(left_one, LOW);
        digitalWrite(right_two, LOW);
        digitalWrite(left_two, LOW);
        break;
  }
}