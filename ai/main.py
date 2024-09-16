import os
import signal
from src.loop.loop import loop
from src.parsing.parsing import parse_arguments
from src.loop.init import init
from src.utils.logger import init_logger, Logger
from src.player.socket.socket_wrapper import SocketWrapper
from uuid import uuid4


def signal_handler(_, __):
    SocketWrapper.shutdown_socket()
    Logger.log(ID="info", message="Shutdown signal sent to server.")
    Logger.close_files()
    exit(0)


def main():
    try:
        script_dir = os.path.dirname(os.path.abspath(__file__))
        config_path = os.path.join(script_dir, 'config/logger_config.json')

        uuid = uuid4()
        Logger.set_uuid(str(uuid))

        init_logger(config_path)

        signal.signal(signal.SIGINT, signal_handler)

        loop(init(parse_arguments(), uuid))
        Logger.close_files()
    except Exception as e:
        print(f"Error: {e}")
        Logger.close_files()
        exit(84)


if __name__ == "__main__":
    main()
