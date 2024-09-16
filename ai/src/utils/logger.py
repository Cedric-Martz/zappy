import json
import sys
import os
from typing import Dict, Tuple, TextIO, Optional, cast
from colorama import Fore, Back, init
from datetime import datetime


init(autoreset=True)

COLOR_MAP = {
    'red': Fore.RED,
    'green': Fore.GREEN,
    'blue': Fore.BLUE,
    'cyan': Fore.CYAN,
    'magenta': Fore.MAGENTA,
    'yellow': Fore.YELLOW,
    'white': Fore.WHITE,
    'black': Fore.BLACK,
    'back_red': Back.RED,
    'back_green': Back.GREEN,
    'back_blue': Back.BLUE,
    'back_cyan': Back.CYAN,
    'back_magenta': Back.MAGENTA,
    'back_yellow': Back.YELLOW,
    'back_white': Back.WHITE,
    'back_black': Back.BLACK,
}


class Logger:
    _channels: Dict[str, Tuple[bool, TextIO, str]] = {
        "default": (True, sys.stdout, Fore.WHITE),
        "debug": (False, sys.stderr, Fore.YELLOW),
        "error": (True, sys.stderr, Fore.RED),
    }
    _colored: bool = True
    _timestamped: bool = False
    _timestamp_format: str = '%Y-%m-%d %H:%M:%S '
    _disabled: bool = False
    _display_uuid: bool = False
    _filename_uuid: bool = False
    _uuid: str = ""

    @classmethod
    def add(
        cls,
        ID: str,
        is_open: bool = True,
        channel: TextIO = sys.stdout,
        color: str = "white",
        filepath: Optional[str] = None,
        mode: str = 'a'
    ) -> None:
        if filepath:
            if cls._filename_uuid:
                directory, filename = os.path.split(filepath)
                filename = cls._uuid + "-" + filename
                filepath = os.path.join(directory, filename)
            channel = cast(TextIO, open(file=filepath, mode=mode))
        cls._channels[ID] = (is_open, channel, COLOR_MAP.get(color, COLOR_MAP['white']))

    @classmethod
    def close_files(cls) -> None:
        for _, (__, channel, ___) in cls._channels.items():
            if hasattr(channel, 'close') and channel not in (sys.stdout, sys.stderr):
                channel.close()

    @classmethod
    def log(cls, message: str, ID: str = "default", end: Optional[str] = None) -> None:
        if cls._disabled:
            return
        if ID not in cls._channels:
            print(f"ID {ID} does not exist.", file=sys.stderr, end=end)
            return

        (is_open, channel, color) = cls._channels[ID]
        if is_open:
            timestamp = datetime.now().strftime(cls._timestamp_format) if cls._timestamped else ''
            uuid = (cls._uuid + " - ") if cls._display_uuid and cls._uuid else ''
            use_color = cls._colored and channel in (sys.stdout, sys.stderr)
            color = color if use_color else ''
            print(f"{timestamp}{uuid}{color}{message}", file=channel)
            if channel not in (sys.stdout, sys.stderr):
                channel.flush()

    @classmethod
    def lock(cls, ID: str) -> None:
        if ID not in cls._channels:
            print(f"ID {ID} does not exist.", file=sys.stderr)
            return

        (_, channel, color) = cls._channels[ID]
        cls._channels[ID] = (False, channel, color)

    @classmethod
    def unlock(cls, ID: str) -> None:
        if ID not in cls._channels:
            print(f"ID {ID} does not exist.", file=sys.stderr)
            return

        (_, channel, color) = cls._channels[ID]
        cls._channels[ID] = (True, channel, color)

    @classmethod
    def lock_all(cls) -> None:
        for ID in cls._channels.keys():
            cls.lock(ID)

    @classmethod
    def unlock_all(cls) -> None:
        for ID in cls._channels.keys():
            cls.unlock(ID)

    @classmethod
    def set_color(cls, ID: str, color: str) -> None:
        if ID not in cls._channels:
            print(f"ID {ID} does not exist.", file=sys.stderr)
            return

        (is_open, channel, _) = cls._channels[ID]
        cls._channels[ID] = (is_open, channel, COLOR_MAP.get(color, COLOR_MAP['white']))

    @classmethod
    def reset_color(cls, ID: str) -> None:
        cls.set_color(ID, Fore.WHITE)

    @classmethod
    def enable_colored(cls) -> None:
        cls._colored = True

    @classmethod
    def disable_colored(cls) -> None:
        cls._colored = False

    @classmethod
    def enable_timestamp(cls) -> None:
        cls._timestamped = True

    @classmethod
    def disable_timestamp(cls) -> None:
        cls._timestamped = False

    @classmethod
    def set_timestamp_format(cls, timestamp_format: str) -> None:
        cls._timestamp_format = timestamp_format

    @classmethod
    def enable_uuid_display(cls) -> None:
        cls._display_uuid = True

    @classmethod
    def disable_uuid_display(cls) -> None:
        cls._display_uuid = False

    @classmethod
    def enable_filename_uuid(cls) -> None:
        cls._filename_uuid = True

    @classmethod
    def disable_filename_uuid(cls) -> None:
        cls._filename_uuid = False

    @classmethod
    def set_uuid(cls, uuid: str) -> None:
        cls._uuid = uuid

    @classmethod
    def load_config(cls, config_path: str) -> None:
        try:
            with open(config_path, 'r') as config_file:
                config = json.load(config_file)
                cls._colored = config.get("colored", cls._colored)
                cls._timestamped = config.get("timestamped", cls._timestamped)
                cls._timestamp_format = config.get("timestamp_format", cls._timestamp_format)
                cls._disabled = config.get("disabled", cls._disabled)
                cls._display_uuid = config.get("display_uuid", cls._display_uuid)
                cls._filename_uuid = config.get("filename_uuid", cls._filename_uuid)

                for logger_config in config.get("loggers", []):
                    if logger_config.get("disabled"):
                        cls.lock(logger_config["ID"])
                        continue
                    color = logger_config.get("color")
                    if color:
                        color = color.lower()
                        if color not in COLOR_MAP:
                            print(f"Warning: Invalid color '{color}' for logger '{logger_config['ID']}'. Using default color 'white'.")
                            color = "white"
                    else:
                        color = "white"

                    cls.add(
                        ID=logger_config["ID"],
                        is_open=logger_config.get("is_open", True),
                        channel=sys.stderr if logger_config.get("channel") == "stderr" else sys.stdout,
                        color=color,
                        filepath=logger_config.get("filepath"),
                        mode=logger_config.get("mode", 'a')
                    )
        except Exception as e:
            cls.log(f"Failed to load logger config: {e}", ID="error")


def init_logger(config_path: Optional[str] = None):
    if config_path:
        Logger.load_config(config_path)
