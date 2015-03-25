/**
 * Fucking Cat Laser
 * ===
 * Short code snippet to control an arduino and a laser for Reese the Cat's
 * entertainment. She must be entertained.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Servo.h>

Servo servoX;
Servo servoY;

int servoXPin = 9;
int servoYPin = 10;

int laserPin = 13;
int pirPin = 12;

int servoXPos = 0;
int servoYPos = 0;

int servoXOldPos;
int servoYOldPos;

boolean lock = false;

void setup()
{
  servoX.attach(servoXPin);
  servoY.attach(servoYPin);

  servoX.write(0);
  servoY.write(0);

  pinMode(laserPin, OUTPUT);
  pinMode(pirPin, INPUT);
}

void incrimentPos(int oldPos, int newPos, Servo &serv)
{
  int i = oldPos;

  // Jackpot
  int rand = random(0, 100);
  if (rand % 5 == 0) {
    serv.write(newPos);
    return;
  }

  while (i < newPos) {
    i += 1;
    serv.write(i);
    delay(random(1, 60));
  }

  while (i > newPos) {
    i -= 1;
    serv.write(i);
    delay(random(1, 60));
  }
}

void catShow()
{
  lock = true;
  int i = 0;

  digitalWrite(laserPin, HIGH);

  while(i < 100) {
    servoXOldPos = servoXPos;
    servoYOldPos = servoYPos;
    servoXPos = random(0, 35);
    servoYPos = random(0, 35);

    incrimentPos(servoYOldPos, servoYPos, servoY);
    incrimentPos(servoXOldPos, servoXPos, servoX);
    delay(random(15, 2000));
    i += 1;
  }

  digitalWrite(laserPin, LOW);

  // 10 seconds
  delay(10 * 1000);

  lock = false;
}

void doCatShow()
{
  if (lock) {
    return;
  }

  catShow();
}

void loop()
{
  if (digitalRead(pirPin) == HIGH) {
    doCatShow();
  }
}

