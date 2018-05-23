
int turnAngle = 35;
int currPos = 0;

/**
 * Check the distance from both sides and turn to safe side
 * here, we assume 180deg is initial position
 * 
 * Conditions:
 * 1. Both side have safe distance
 * 2. Right has safe distance. But not left.
 * 3. Left has safe distance. But not right.
 * 4. Both side unsafe distance.
 * 
 * @para  left  distance from left
 * @para  right distance from right
 * 
 */
void turn(int left, int right) {  
  Serial.println("now turning");
  
  if ((left > distTurn) && (right > distTurn))
  {
    Serial.println("Safe distance. Turning Right");
    turnRight();
  }
  else if ((right < distTurn) && (left > distTurn))
  {
    Serial.println("Turning Left");
    turnLeft();
  }
  else if ((right > distTurn) && (left < distTurn))
  {
    Serial.println("Turning Right");
    turnRight();
  }
  else
  {
    // if unsafe distances, no turning... and stop engine when too close( distStop)
    Serial.println("Not Safe to turn");  
  }
  
}

void turnLeft()
{
  if (!(currPos < initPos))
  {
    Serial.println("turning left");
    Serial.print("Angle: ");

    currPos = (initPos-turnAngle);
    
    wheel.write(currPos);
    delay(20);
    
    Serial.println(currPos);
  }
}

void turnRight()
{  
  if (!(currPos > initPos))
  {
    Serial.println("turning right");
    Serial.print("Angle: ");
    
    currPos = (initPos+turnAngle);
    
    wheel.write(currPos);
    delay(20);
    
    Serial.println(currPos);
  }
}

void resetTurn()
{
  Serial.println("Resetting Turn");
  
  if (currPos != initPos)
  {
    // reset turn
    Serial.print("Angle: ");
    Serial.println(initPos);
    Serial.print("AngleCurr: ");
    Serial.println(currPos);

    currPos = initPos;
    
    wheel.write(currPos);
    
    delay(20);
  }
  else 
  {
    Serial.println("Already reset");
  }
}

void stopEng()
{
  
}

