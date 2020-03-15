#!/usr/bin/env python

import serial
import json
from enum import Enum
import os


# ----------------------------------------------------------------------------------------------------------------------

class EventType (Enum):
    # must match nucular::EventEntity in EventTypes.h
    SWITCH_1 = 0
    SWITCH_2 = 1
    SWITCH_3 = 2
    LOADED_INDICATOR = 3
    PUSH_BUTTON = 4
    UNDEFINED = 5


# ----------------------------------------------------------------------------------------------------------------------

class PanelState:

      def __init__(self, entries_dict=None):
          # attribute names must match the output of
          # nucular::EventReceiver::onEvent()
          self.switch_1 = None  # type: bool
          self.switch_2 = None  # type: bool
          self.switch_3 = None  # type: bool
          self.loaded_indicator = None  # type: bool
          self.push_button = None  # type: bool

          self.__dict__.update(entries_dict)

      def __str__(self):
        return str(self.__dict__)

# ----------------------------------------------------------------------------------------------------------------------

class EventReceiver:

    def __init__(self):
        self.event_map = {
            EventType.SWITCH_1 : self.onSwitch1,
            EventType.SWITCH_2 : self.onSwitch2,
            EventType.SWITCH_3 : self.onSwitch3,
            EventType.LOADED_INDICATOR : self.onLoadedIndicator,
            EventType.PUSH_BUTTON : self.onPushButton
        }

        self.script_path = os.path.dirname(__file__)

    def onEventReceived(self, event_type, panel_state):
        # type: (EventType, PanelState) -> None
        self.event_map[event_type](panel_state)

    def onSwitch1(self, panel_state):
        # type: (PanelState) -> None
        print("on sw 1, state: {}".format(panel_state))
        os.system("{}/{}".format(self.script_path, "hooks/sw1.sh '{}'".format(panel_state)))

    def onSwitch2(self, panel_state):
        # type: (PanelState) -> None
        print("on sw 2, state: {}".format(panel_state))
        os.system("{}/{}".format(self.script_path, "hooks/sw2.sh '{}'".format(panel_state)))
        
    def onSwitch3(self, panel_state):
        # type: (PanelState) -> None
        print("on sw 3, state: {}".format(panel_state))
        os.system("{}/{}".format(self.script_path, "hooks/sw3.sh '{}'".format(panel_state)))
        
    def onLoadedIndicator(self, panel_state):
        # type: (PanelState) -> None
        print("on loaded indicator, state: {}".format(panel_statete))
        os.system("{}/{}".format(self.script_path, "hooks/pb.sh '{}'".format(panel_state)))

    def onPushButton(self, panel_state):
        # type: (PanelState) -> None
        print("on pb, state: {}".format(panel_statete))
        os.system("{}/{}".format(self.script_path, "hooks/pb.sh '{}'".format(panel_state)))

# ----------------------------------------------------------------------------------------------------------------------

class Monitor:
    def __init__(self, serial_port="/dev/ttyUSB0"):
      self.ser = serial.Serial(serial_port, 230400, parity="N", stopbits=1, timeout=10, xonxoff=0, rtscts=0)

    def watch(self, event_receiver):
        # type: (EventReceiver) -> None
        if self.ser.is_open:
            self.ser.close()

        self.ser.open()

        if self.ser.is_open:
            while True:
                line = self.ser.readline()
                if line:
                    print("raw line: {}".format(line))

                    event_dict = json.loads(line)
                    event_type = EventType(int(event_dict["event"]))
                    panel_state = PanelState(event_dict["state"])
                    event_receiver.onEventReceived(event_type, panel_state)
        else:
            print("fialed to open serial")

# ----------------------------------------------------------------------------------------------------------------------

if __name__ == "__main__":
    serial_port = "/dev/ttyUSB0"
    m = Monitor(serial_port)
    er = EventReceiver()
    m.watch(er)
