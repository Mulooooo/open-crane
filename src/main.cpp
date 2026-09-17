#include <Arduino.h>
#include "Ultrasonic.h"
#include "LiquidCrystal.h"

#define MAX_HEIGHT 70
#define MAX_TRAVEL 300

Ultrasonic tall_sanic(2, 3);
Ultrasonic wide_sanic(4, 5);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

static int base_height;
static int base_travel;

int get_height(Ultrasonic &height_captor){
  return (MAX_HEIGHT-(height_captor.read()*10));
}

int get_travel_distance(Ultrasonic &travel_captor){
  return (MAX_TRAVEL-(travel_captor.read()*10));
}

int clamp(int value){
  if (value < 0) return 0;
  if (value > 999) return 999;
  return value;
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
  lcd.print("Hauteur  :    mm");
  lcd.setCursor(0, 1);
  lcd.print("Distance :    mm");
  base_height = get_height(tall_sanic);
  base_travel = get_travel_distance(wide_sanic);
}

void loop()
{
  print3digits(get_height(tall_sanic)-base_height, 11, 0);
  print3digits(get_travel_distance(wide_sanic)-base_travel, 11, 1);
  delay(75);
}