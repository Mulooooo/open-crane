#include <Arduino.h>
#include "Ultrasonic.h"
#include "LiquidCrystal.h"

#define MAX_HEIGHT 70
#define MAX_TRAVEL 300

Ultrasonic tall_sanic(7);
Ultrasonic wide_sanic(8);
LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 9);

static int base_height;
static int base_travel;

int get_height(Ultrasonic &height_captor){
  return (MAX_HEIGHT-(height_captor.read()*10));
}

int get_travel_distance(Ultrasonic &travel_captor){
  return (MAX_TRAVEL-(travel_captor.read()*10));
}

int clamp(int value){
  return (value < 0)?0:value;
}

void print3digits(int value, int col, int row){
  lcd.setCursor(col, row);
  value = clamp(value);
  lcd.print(value / 100);
  lcd.print((value % 100) / 10);
  lcd.print(value % 10);
}

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("H:   mm");
  lcd.setCursor(0, 1);
  lcd.print("T:   mm");
  base_height = get_height(tall_sanic);
  base_travel = get_travel_distance(wide_sanic);
}

void loop()
{
  print3digits(get_height(tall_sanic)-base_height, 2, 0);
  print3digits(get_travel_distance(wide_sanic)-base_travel, 2, 1);
  delay(50);
}