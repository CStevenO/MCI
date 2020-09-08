import time
import uos
from machine import RTC,Timer
import ntptime

tim0 = Timer(0)

rtc = RTC()
ntptime.settime()
(year,month,day,week,hour,minute,second,mili) = rtc.datetime()
rtc.datetime((year,month,day,week,hour-5,minute,second,mili))
def load_alarm():
    import ujson as json
    try:
        with open("/alarm.json") as f:
            alarm = json.loads(f.read())
    except (OSError, ValueError):
        print("Couldn't load /alarm.json")
        save_alarm()
    else:
        ALARM.update(alarm)
        print("Loaded alarm from /alarm.json")

def save_alarm():
    import ujson as json
    try:
        with open("/alarm.json", "w") as f:
            f.write(json.dumps(ALARM))
    except OSError:
        print("Couldn't save /alarm.json")


def alarma():
    global com,comp_alarm
    hora = rtc.datetime()
    if com <= (int(hora[4])+int(hora[5])/60):
        comp_alarm = True

ALARM = {

}

com = 30
load_alarm()
comp_alarm = False
inh = False
x = 500000
try:
    for y in ALARM:
        if x > int(y):
            x=int(y)
    da = ALARM[str(x)].split(",")
    com = int(da[3]) + int(da[4])/60
except:
    com=30
print(com)
tim0.init(period=20000,mode=Timer.PERIODIC,callback=lambda t:alarma())
while 1:
    if comp_alarm:
        if not inh:
            print(ALARM[str(x)]+";")
            del ALARM[str(x)]
            uos.remove("/alarm.json")
            save_alarm()
            inh = True
            x=x+1
        else:
            try:
                da = alarm[str(x)].split(",")
                com = int(da[3]) + int(da[4])/60
            except:
                com = 30
            comp_alarm = False
            inh = False
