const int red = 4;
const int blue = 5;
String text;
String red_str;
String blue_str;
int red_int;
int blue_int;
String off_text = "S";
int flag = 0;
long previous_millis_red;
long previous_millis_blue;

void setup()
{
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop()
{
  text = Serial.readString();
  if(text == off_text) // Serial input is OFF
  {
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    flag = 0;
  }
  else if(text != "") // Serial input is ON
  {
    red_str = "";
    blue_str = "";
    int i = 1;
    while(i < text.length() && text[i] != 'B')
    {
      red_str = red_str + text[i];
      i++;
    }
    i++;
    while(i < text.length())
    {
      blue_str = blue_str + text[i];
      i++;
    }
    red_int = atoi(red_str.c_str());
    blue_int = atoi(blue_str.c_str());
    flag = 1;
    digitalWrite(red, HIGH);
    digitalWrite(blue, HIGH);
    previous_millis_red = millis();
    previous_millis_blue = millis();
  }
  else
  {
    if(flag) // previous input is ON
    {
      if(millis() - previous_millis_red >= red_int)
      {
        // high if low, low if high
        if(digitalRead(red) == LOW)
          digitalWrite(red, HIGH);
        else
          digitalWrite(red, LOW);
        
        previous_millis_red = millis();
      }
      if(millis() - previous_millis_blue >= blue_int)
      {
        // high if low, low if high
        if(digitalRead(blue) == LOW)
          digitalWrite(blue, HIGH);
        else
          digitalWrite(blue, LOW);
        
        previous_millis_blue = millis();
      }
    }
  }
}
