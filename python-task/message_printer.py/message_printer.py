'''
RICCARDO REVALOR - https://github.com/RiccardoRevalor/Policumbent_it_division_solutions/tree/main/python-task
This module mimics the behaviour of the message printer.
It reads the messages from the named pipe and prints them on the screen.
I do not close the pipe here because I close it at the end of the peripheral_reader.py script.
In my view, we can use multiple message printers to print the messages on different screens, so this is just a client.
'''

import os 
import time
import sys
import win32pipe, win32file, pywintypes


PIPE_NAME = '../tmp/peripheral_pipe'

def main():
    """
    Main function that listens for messages from the named pipe and prints them.
    """
    try:
        print(f"Connecting to named pipe: {PIPE_NAME}")
        
        # Connect to the already created named pipe
        pipe = win32file.CreateFile(
            PIPE_NAME,
            win32file.GENERIC_READ | win32file.GENERIC_WRITE, 
            0,  # No sharing
            None,  # Default security attributes
            win32file.OPEN_EXISTING,  # Open the pipe if it exists
            0,
            None
        )

        res = win32pipe.SetNamedPipeHandleState(pipe, win32pipe.PIPE_READMODE_MESSAGE, None, None) # Set the pipe to message-read mode
        
        print("Connected to the pipe.")


        while True:
            #Read msg from named pipe and print them on screen
            msg = win32file.ReadFile(pipe, 65536)[1].decode()
            print(f"Received message: {msg}")

    except KeyboardInterrupt:
        print("Exiting...")
        sys.exit(0)
    
    except pywintypes.error as e:
            if e.args[0] == 2:
                print("Error: the named pipe does not exist. Please run the peripheral_reader.py script first.")
                time.sleep(1)
            elif e.args[0] == 109:
                print("Error: the pipe is broken")



if __name__ == "__main__":
     main()

    
