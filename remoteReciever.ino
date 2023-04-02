#include <Arduino_JSON.h>
#include <EspNow.h>
#include <remoteSerial.h>
Peer baseDirection;
Peer erRingPick;
JSONVar serialData;
JSONVar pickData;
bool switchMode = false;
void setup()
{
  Serial.begin(115200);
  Serial2.begin(921600, SERIAL_8N1, 16, 17);
  registerSerial(&Serial2);
  setId("TenZZ");
  baseDirection.init("WardL");
  erPickRing.init("PICKE");
  Serial2.setTimeout(1);

  baseDirection.setOnRecieve(baseDefaultHandler);
  erRingPick.setOnRecieve(pickDefaultHandler);

  setBaseReciever(sendBase, "base");

  setSerialReciever(cross, "cro");
  setSerialReciever(circle, "cir");
  setSerialReciever(triangle, "tri");
  setSerialReciever(square, "squ");
  setSerialReciever(share, "share");
  setSerialReciever(up, "up");
  setSerialReciever(down, "dow");
  setSerialReciever(right, "rig");
  setSerialReciever(left, "lef");
  setSerialReciever(ps, "ps");
  setSerialReciever(touchPad, "tpad");
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
  Serial.println("ps - "+String(switchMode));
  switchMode = !switchMode;
}

void touchPad(String msg)
{
  Serial.println("touchPad");
}

void cross(String msg)
{
  pickData["type"]="pLvl1";
  Serial.println(JSON.stringify(pickData));
  ErRingPick.send(pickData);
}
void circle(String msg)
{
  pickData["type"]="rLvl1";
  Serial.println(JSON.stringify(pickData));
  ErRingPick.send(pickData);
}

void triangle(String msg)
{
  pickData["type"]="pLvl2";
  Serial.println(JSON.stringify(pickData));
  ErRingPick.send(pickData);
}

void square(String msg)
{
  pickData["type"]="rLvl2";
  Serial.println(JSON.stringify(pickData));
  ErRingPick.send(pickData);
}

void up(String msg)
{
  pickData["type"]="exPl";
  pickData["offset"] = -1;
  Serial.println(JSON.stringify(pickData));
  ErRingPick.send(pickData);
}

void down(String msg)
{
  pickData["type"]="exPl";
  pickData["offset"] = 1;
  Serial.println(JSON.stringify(pickData));
  ErRingPick.send(pickData);
}

void right(String msg)
{
  pickData["type"]="exRo";
  pickData["offset"] = -1;
  Serial.println(JSON.stringify(pickData));
  ErRingPick.send(pickData);
}

void left(String msg)
{
  pickData["type"]="exRo";
  pickData["offset"] = 1;
  Serial.println(JSON.stringify(pickData));
  ErRingPick.send(pickData);
}

void share(String msg)
{
  pickData["type"]="Erst";
  Serial.println(JSON.stringify(pickData));
  ErRingPick.send(pickData);
}

void baseDefaultHandler(JSONVar msg)
{

}

void pickDefaultHandler(JSONVar msg)
{
  
}