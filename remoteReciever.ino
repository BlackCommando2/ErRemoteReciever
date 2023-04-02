#include <Arduino_JSON.h>
#include <EspNow.h>
#include <remoteSerial.h>
Peer baseDirection;
Peer erRingPick;
Peer erShooter;
JSONVar serialData;
JSONVar pickData;
JSONVar shooterData;

bool switchMode = false;
int platformUpOffset = 1, platformDownOffset = -1;
int rotateUpOffset = 1, rotateDownOffset = -1;

void setup()
{
  Serial.begin(115200);
  Serial2.begin(921600, SERIAL_8N1, 16, 17);
  registerSerial(&Serial2);
  setId("TenZZ");
  baseDirection.init("WardL");
  erRingPick.init("PICKE");
  erShooter.init("EShoo");
  Serial2.setTimeout(1);

  baseDirection.setOnRecieve(baseDefaultHandler);
  erRingPick.setOnRecieve(setRotateOffset, "setROffset");
  erRingPick.setOnRecieve(setPlatformOffset, "setPOffset");
  erRingPick.setOnRecieve(pickDefaultHandler);

  setBaseReciever(sendBase, "base");

  setSerialReciever(cross, "cro");
  setSerialReciever(circle, "cir");
  setSerialReciever(triangle, "tri");
  setSerialReciever(square, "squ");

  setSerialReciever(up, "up");
  setSerialReciever(down, "dow");
  setSerialReciever(right, "rig");
  setSerialReciever(left, "lef");

  setSerialReciever(ps, "ps");
  setSerialReciever(touchPad, "tpad");
  setSerialReciever(share, "share");
  setSerialReciever(option, "opt");

  setSerialReciever(rOne, "rOne");
  setSerialReciever(lOne, "lOne");
}

void loop()
{
  serialListener();
}

void sendBase(JSONVar msg)
{
  baseDirection.send(msg);
}

void ps(String msg)
{
  Serial.println("ps - " + String(switchMode));
  switchMode = !switchMode;
}

void touchPad(String msg)
{
  Serial.println("touchPad");
}

void cross(String msg)
{
  if (!switchMode)
  {
    pickData["type"] = "pLvl1";
    Serial.println(JSON.stringify(pickData));
    erRingPick.send(pickData);
  }
  else if(switchMode)
  {

  }
}
void circle(String msg)
{
  if (!switchMode)
  {
    pickData["type"] = "rLvl1";
    Serial.println(JSON.stringify(pickData));
    erRingPick.send(pickData);
  }
  else if(switchMode)
  {

  }
}

void triangle(String msg)
{
  if (!switchMode)
  {
    pickData["type"] = "pLvl2";
    Serial.println(JSON.stringify(pickData));
    erRingPick.send(pickData);
  }
  else if(switchMode)
  {

  }
}

void square(String msg)
{
  if (!switchMode)
  {
    pickData["type"] = "rLvl2";
    Serial.println(JSON.stringify(pickData));
    erRingPick.send(pickData);
  }
  else if(switchMode)
  {
    
  }
}

void up(String msg)
{
  pickData["type"] = "exPl";
  pickData["offset"] = platformUpOffset;
  Serial.println(JSON.stringify(pickData));
  erRingPick.send(pickData);
}

void down(String msg)
{
  pickData["type"] = "exPl";
  pickData["offset"] = platformDownOffset;
  Serial.println(JSON.stringify(pickData));
  erRingPick.send(pickData);
}

void right(String msg)
{
  pickData["type"] = "exRo";
  pickData["offset"] = rotateDownOffset;
  Serial.println(JSON.stringify(pickData));
  erRingPick.send(pickData);
}

void left(String msg)
{
  pickData["type"] = "exRo";
  pickData["offset"] = rotateUpOffset;
  Serial.println(JSON.stringify(pickData));
  erRingPick.send(pickData);
}

void share(String msg)
{
  pickData["type"] = "Erst";
  Serial.println(JSON.stringify(pickData));
  erRingPick.send(pickData);
}

void option(String msg)
{
  Serial.println("SwitchMode- " + String(switchMode));
  switchMode = !switchMode;
}

void rOne(String msg)
{
  shooterData["type"] = "up";
  erShooter.send(shooterData);
  Serial.println("rOne");
}

void lOne(String msg)
{
  shooterData["type"] = "down";
  erShooter.send(shooterData);
  Serial.println("lOne");
}

void baseDefaultHandler(JSONVar msg)
{
}

void pickDefaultHandler(JSONVar msg)
{
}

void setRotateOffset(JSONVar msg)
{
  rotateUpOffset = (int)msg["rOff"];
  rotateDownOffset = -1 * (int)msg["rOff"];
}

void setPlatformOffset(JSONVar msg)
{
  platformUpOffset = -1 * (int)msg["pOff"];
  platformDownOffset = (int)msg["pOff"];
}