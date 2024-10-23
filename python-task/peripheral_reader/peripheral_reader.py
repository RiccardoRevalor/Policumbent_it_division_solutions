'''
RICCARDO REVALOR - https://github.com/RiccardoRevalor/Policumbent_it_division_solutions/tree/main/python-task
This is the peripheral reader module.
It is responsible for reading the data from the peripheral device.
Since I use Windows OS, I will use the win32pipe module to read the data from the peripheral device.
On LInux, this can be done with os and posix modules.
It manages the creation, the handling and the closing of the named pipe.
'''

import os
import fpp
import time
import sys
import win32pipe, win32file, pywintypes



PIPE_NAME = '../tmp/peripheral_pipe'  #path pointing to the named pipe, which is a generic file
PERIPHERAL_PATH = '../peripheral/file.txt' #fancy path to the peripheral file

#Named pipe creation with win32pipe
pipe = win32pipe.CreateNamedPipe(
    PIPE_NAME,
    win32pipe.PIPE_ACCESS_DUPLEX, #access mode: DUPLEX -> read and write
    win32pipe.PIPE_TYPE_MESSAGE | win32pipe.PIPE_READMODE_MESSAGE | win32pipe.PIPE_WAIT, #message type, message-read mode, blocking mode
    1, 65536, 65536, #number of instances, buffer size, input buffer size -> Max buffer size set to 64KB
    0,
    None
)

class MyListener(fpp.Listener):

    def __init__(self, pipe):
        self.pipe = pipe
        win32pipe.ConnectNamedPipe(self.pipe, None) #connect to the named pipe

    def on_message_received(self, msg):
        # When a msg is received, write it to the pipe
        win32file.WriteFile(self.pipe, msg.encode()) #write the msg to the pipe
    
    def exit(self):
        # When the listener exits, close the pipe
        win32file.CloseHandle(self.pipe) #close the pipe

def main():
    '''
    Main function of the module. The purpose of this function is to:

    - initialize the peripheral to read from, using fpp.Peripheral
    - initialize the listener
    - initialize the notifier and give it the list of listeners to distribute the messages to
    - the listener reads the received messages and sends them to the named pipe
    '''
    listener = MyListener(pipe)  #listener initialization
    peripheral = fpp.Peripheral(PERIPHERAL_PATH)  #peripheral from which to read
    notifier = fpp.Notifier(peripheral, [listener])  #the second argument is a list containing our listener

    #read data from the peripheral and send it to the listeners



    while True:
        notifier.read() #read msg and send it to the listeners list 
        time.sleep(0.1) #sleep for 0.1 seconds to avoid busy waiting


if __name__ == '__main__':
    main()

