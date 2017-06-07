import sys, traceback, Ice
import SmartObject


class AnalogSinkI(SmartObject.AnalogSink):
    def update(self, id, value, meta, position, current=None):
        print ("Sensor en San Luis: ")
        print (value)


status = 0
ic = None

try:
    ic= Ice.initialize(sys.argv)
    adapter = ic.createObjectAdapterWithEndpoints("AnalogSinkAdapter", "default -p 10000")
    object= AnalogSinkI()
    adapter.add(object, ic.stringToIdentity("AnalogSink"))
    adapter.activate()
    ic.waitForShutdown()
except:
    traceback.print_exc()
    status = 1

if ic:
    try:
        ic.destroy()
    except:
        traceback.print_exc()
        status=1

sys.exit(status)
