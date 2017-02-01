from Mechanics.API.LocalAI import LocalAI
from Mechanics.API.RemoteAI import RemoteAI
from Mechanics import Constants
import threading
import logging
log = logging.getLogger('root')


class Interface(threading.Thread):

    def __init__(self, player, event):
        threading.Thread.__init__(self)

        if Constants.Config.INTERFACE == "Local":
            log.info("Hooking AI on player (Local)")
            self.ai = LocalAI(player, event)
        else:
            log.info("Hooking AI on player (Remote)")
            self.ai = RemoteAI(player, event)

    def run(self):
        self.ai.init()
