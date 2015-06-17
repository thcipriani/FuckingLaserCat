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

boolean lock = false;

void setup()
{
  servoX.attach(servoXPin);
  servoY.attach(servoYPin);

  servoX.write(0);
  servoY.write(0);

  pinMode(laserPin, OUTPUT);
  pinMode(pirPin, INPUT);

  // Debug
  Serial.begin(9600);
}

void incrimentPos(int newPos, Servo &serv, int newPos2, Servo &serv2)
{
  int i = serv.read();
  int j = serv2.read();
  int k = 0;

  int deltaPos = 0;
  int wait = 15;

  if (i < newPos) {
    deltaPos = newPos - i;
  } else {
    deltaPos = i - newPos;
  }

  if (j < newPos2) {
    deltaPos += newPos2 - j;
  } else {
    deltaPos += j - newPos2;
  }

  if (deltaPos > 50)
    wait = 50;

  while (k < deltaPos) {
    if (i < newPos)
      i += 1;
    else
      i -= 1;


    if (j < newPos2)
      j += 1;
    else
      j -= 1;

    serv.write(i);
    serv2.write(j);
    delay(wait);
    k += 1;
  }
}

void catShow()
{
  lock = true;
  int i = 0;
  int wait;
  int jackpot = 2000;

  digitalWrite(laserPin, HIGH);


  while(i < 100) {
    wait = random(0, 100);

    if (wait % 7 == 0)
      wait = jackpot;

    servoXPos = random(0, 50);
    servoYPos = random(0, 20);

    incrimentPos(servoYPos, servoY, servoXPos, servoX);
    delay(random(wait));
    i += 1;
  }

  digitalWrite(laserPin, LOW);

  // 10 seconds
  delay(10 * 1000);

  lock = false;
}

void loop()
{
  if (lock) {
    return;
  }

  if (digitalRead(pirPin) == HIGH) {
    catShow();
  }
}

