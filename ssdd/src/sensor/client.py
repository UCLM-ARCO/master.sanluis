import sys, traceback, Ice
import SmartObject

status = 0
ic = None
try:
    ic = Ice.initialize(sys.argv)
    base = ic.stringToProxy("AnalogSink:default -p 10000")
    serverupdated = SmartObject.AnalogSinkPrx.checkedCast(base)
    if not serverupdated:
        raise RuntimeError("Invalid proxy")

    serverupdated.update("Cocina",28.0,None,None);
except:
    traceback.print_exc()
    status = 1

if ic:
    # Clean up
    try:
        ic.destroy()
    except:
        traceback.print_exc()
        status = 1

sys.exit(status)
