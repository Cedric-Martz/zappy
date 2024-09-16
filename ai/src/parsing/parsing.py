import argparse
from signal import SIGINT, signal
from sys import stderr
from src.utils.logger import Logger


class CustomArgumentParser(argparse.ArgumentParser):
    def error(self, message):
        self.print_usage(stderr)
        args = {'prog': self.prog, 'message': message}
        self.exit(84, '%(prog)s: error: %(message)s\n' % args)


def signal_handler(_, __):
    Logger.log(ID="error", message="User stopped the connection")
    exit(0)


def parse_arguments():
    signal(SIGINT, signal_handler)

    parser = CustomArgumentParser(description="Zappy AI Client", add_help=False)
    parser.add_argument('-p', '--port', type=int, required=True, help='Port number')
    parser.add_argument('-n', '--name', type=str, required=True, help='Name of the team')
    parser.add_argument('-h', '--machine', default='localhost', help='Name of the machine; localhost by default')
    parser.add_argument('-m', '--mode', default='evolving', help='Behavior of the AI, evolving by default')
    parser.add_argument('--help', action='help', default=argparse.SUPPRESS)

    args = parser.parse_args()
    if args.mode not in ["evolving", "evil"]:
        raise Exception("Invalid mode")
    return args
