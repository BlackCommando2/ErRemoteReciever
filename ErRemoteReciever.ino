#include <Arduino_JSON.h>
#include <EspNow.h>
#include <remoteSerial.h>
Peer baseDirection;
Peer erRingPick;
Peer erShooter;
Peer relayMod;
JSONVar serialData;
JSONVar pickData;
JSONVar shooterData;
JSONVar relayData;
JSONVar baseERData;
JSONVar lidarData;
bool switchMode = false, shut = false, switchPwm = false;
int platformUpOffset = 1, platformDownOffset = -1;
int rotateUpOffset = 1, rotateDownOffset = -1;
int typePole = 1, setPole = 1 ;
void setup()
{
  Serial.begin(115200);
  Serial2.begin(921600, SERIAL_8N1, 16, 17);
  registerSerial(&Serial2);
  setId("TenZZ");
  baseDirection.init("WardL");
  erRingPick.init("PICKE");
  erShooter.init("EShoo");
  relayMod.init("ReLM");
  Serial2.setTimeout(1);

  baseDirection.setOnRecieve(baseDefaultHandler);
  erRingPick.setOnRecieve(setRotateOffset, "setROffset");
  erRingPick.setOnRecieve(setPlatformOffset, "setPOffset");
  erRingPick.setOnRecieve(pickDefaultHandler);
  erRingPick.setOnRecieve(setColor, "setup");

  //  setBaseReciever(sendBase, "base");
  setSerialReciever(sendBase, "base");

  setSerialReciever(defaultHandler);
  setSerialReciever(defaultHandlerJSON);
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
  setSerialReciever(touchPadRel, "trel");
  setSerialReciever(share, "share");
  setSerialReciever(option, "opt");

  setSerialReciever(rOne, "bpush");
  setSerialReciever(lOne, "lpush");

}

void loop()
{
  serialListener();
}

void sendBase(JSONVar msg)
{
  msg["type"] = "ERDR";
  baseDirection.send(msg);
//  Serial.println(msg);
}

void defaultHandler(String msg)
{
  Serial.println("default");
}

void defaultHandlerJSON(JSONVar msg)
{
  Serial.println("default");
}

void ps(String msg)
{
  if (!switchMode)
  {
    pickData["type"] = "Erst";
//    Serial.println(JSON.stringify(pickData));
    erRingPick.send(pickData);
  }
  else if (switchMode)
  {
    pickData["type"] = "resP";
    erRingPick.send(pickData);
    shooterData["type"] = "shRst";
//    Serial.println(JSON.stringify(shooterData));
    erShooter.send(shooterData);
  }
}

void touchPad(String msg)
{
  if (shut)
  {
    relayData["type"] = "close";
    relayMod.send(relayData);
  }
  else if (!shut)
  {
    relayData["type"] = "open";
    relayMod.send(relayData);
  }
//  Serial.println("touchpad pressed");
}
void touchPadRel(String msg)
{
  shut = !shut;
//  Serial.println("touchpad rel");
}

void cross(String msg)
{
  if (!switchMode)
  {
    pickData["type"] = "pLvl1";
//    Serial.println(JSON.stringify(pickData));
    erRingPick.send(pickData);
  }
  else if (switchMode)
  {
    if (setPole == 1)
    {
      pickData["spid"] = 1;
      pickData["type"] = "sPID";
      shooterData["type"] = "pOne";
//      Serial.println(JSON.stringify(shooterData));
      erShooter.send(shooterData);
      erRingPick.send(pickData);
      setPole = 2;
    }
    else if (setPole == 2)
    {
      pickData["spid"] = 1;
      pickData["type"] = "sPID";
      shooterData["type"] = "pOFa";
//      Serial.println(JSON.stringify(shooterData));
      erShooter.send(shooterData);
      erRingPick.send(pickData);
      setPole = 1;
    }
  }
}
void circle(String msg)
{
  if (!switchMode)
  {
    pickData["type"] = "rLvl1";
//    Serial.println(JSON.stringify(pickData));
    erRingPick.send(pickData);
  }
  else if (switchMode)
  {
    pickData["spid"] = 2;
    pickData["type"] = "sPID";
    shooterData["type"] = "pTwo";
//    Serial.println(JSON.stringify(shooterData));
    erShooter.send(shooterData);
    erRingPick.send(pickData);
    baseERData["type"] = "RBT2";
    baseDirection.send(baseERData);
  }
}

void triangle(String msg)
{
  if (!switchMode)
  {
    //    pickData["type"] = "plex";
    //    erRingPick.send(pickData);
//    Serial.println("switchmode");
  }
  else if (switchMode)
  {
    pickData["spid"] = 3;
    pickData["type"] = "sPID";
    erRingPick.send(pickData);
    shooterData["type"] = "pThr";
//    Serial.println(JSON.stringify(shooterData));
    erShooter.send(shooterData);
    //    baseERData["type"] = "RBT3";
    //    baseDirection.send(baseERData);
  }
}

void square(String msg)
{
  if (!switchMode)
  {
    pickData["type"] = "rLvl2";
//    Serial.println(JSON.stringify(pickData));
    erRingPick.send(pickData);
  }
  else if (switchMode)
  {
    shooterData["type"] = "pOpen";
//    Serial.println(JSON.stringify(shooterData));
    erShooter.send(shooterData);

  }
}

void up(String msg)
{
  pickData["type"] = "exPl";
  pickData["side"] = 1;
  pickData["offset"] = platformUpOffset;
//  Serial.println(JSON.stringify(pickData));
  erRingPick.send(pickData);
}

void down(String msg)
{
  pickData["type"] = "exPl";
  pickData["side"] = -1;
  pickData["offset"] = platformDownOffset;
//  Serial.println(JSON.stringify(pickData));
  erRingPick.send(pickData);
}

void right(String msg)
{
  if (!switchMode)
  {
    pickData["type"] = "exRo";
    pickData["offset"] = rotateDownOffset;
//    Serial.println(JSON.stringify(pickData));
    erRingPick.send(pickData);
  }
  else if (switchMode)
  {
    shooterData["type"] = "up";
//    Serial.println(JSON.stringify(shooterData));
    erShooter.send(shooterData);
  }
}

void left(String msg)
{
  if (!switchMode)
  {
    pickData["type"] = "exRo";
    pickData["offset"] = rotateUpOffset;
    erRingPick.send(pickData);
  }
  else if (switchMode)
  {
    shooterData["type"] = "down";
    erShooter.send(shooterData);
  }
//  Serial.println("left");
}

void share(String msg)
{
  switchPwm = !switchPwm;
}

void option(String msg)
{
  switchMode = !switchMode;
//  Serial.println("SwitchMode- " + String(switchMode));
}

void rOne(String msg)
{
  //  lidarData["type"]="stopBot";
  //  baseDirection.send(lidarData);
  shooterData["type"] = "MOVp";
  //  Serial.println(JSON.stringify(shooterData));
  erShooter.send(shooterData);
//  Serial.println("rOne");
}

void lOne(String msg)
{

  pickData["type"] = "pMove";
//  Serial.println(JSON.stringify(pickData));
  erRingPick.send(pickData);
}
void baseDefaultHandler(JSONVar msg)
{
}

void pickDefaultHandler(JSONVar msg)
{
}
void setColor(JSONVar msg)
{
  //  Serial2.print("col\n");
}
void setRotateOffset(JSONVar msg)
{
  //  Serial.println("rOff: " + JSON.stringify(msg));
  rotateUpOffset = (int)msg["rOffset"];
  rotateDownOffset = -1 * (int)msg["rOffset"];
//  Serial.println(String(rotateUpOffset) + ", " + String(rotateDownOffset));
}

void setPlatformOffset(JSONVar msg)
{
  //  Serial.println("pOff: " + JSON.stringify(msg));
  platformUpOffset = -1 * (int)msg["pOffset"];
  platformDownOffset = (int)msg["pOffset"];
//  Serial.println(String(platformUpOffset) + ", " + String(platformDownOffset));
}
