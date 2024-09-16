import os
import sys


def execute_new_program():
    pid = os.fork()
    if pid == 0:
        os.execv(sys.executable, ['python3'] + sys.argv)


def check_fork(_, message: str, command: str) -> bool:
    if "Fork" not in command:
        return False
    if "ko" in message:
        return False

    execute_new_program()

    return True
