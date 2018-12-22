import json
from pathlib import Path
import subprocess
import sys
from os.path import expanduser


def PrintHelp():
    print('Too few or invalid arguments provided.')
    print('Valid options are:')
    print('builddockerimage')
    print('interactive')
    print('fullclean')
    print('configure')
    print('build')
    print('monitor')
    print('flash')
    sys.exit(2)


def CreateDefaultConfig():
    userHome = expanduser('~')
    defaultConfig = json.dumps({'buildConfig': {'options': {'idfPath': './esp/esp-idf', 'sshPath': userHome + '/.ssh', 'gitconfigPath': userHome,
                                                            'imageName': 'neopixels', 'usbDevice': '/dev/ttyUSB0'}}}, indent=4)
    outputFile = open('buildconfig.json', 'w+')
    outputFile.write(defaultConfig)


def CatBuildArg(arg):
    res = subprocess.run(
        ['cat', f'{arg}'], stdout=subprocess.PIPE, encoding='UTF-8').stdout
    return res


def BuildDockerMachine(options):
    privateKey = CatBuildArg(options['sshPath'] + '/id_rsa')
    publicKey = CatBuildArg(options['sshPath'] + '/id_rsa.pub')
    idfPath = options['idfPath']
    gitConfig = CatBuildArg(options['gitconfigPath'] + '/.gitconfig')
    command = ["docker", "build", f"-t{options['imageName']}", f"."]
    subprocess.call(command)


def main():
    # Set path for config file this should probably be in the project directory
    # as options will likely be different between projects.  The options file
    # should NOT be version controlled however as it will differ per developer
    configFile = Path('./buildconfig.json')

    # If no config file exists in this directory, generate a default one
    if not configFile.is_file():
        print('No config file present.  Default config file has been written to buildconfig.json')
        print('Customize the options in this file for your environment.')
        CreateDefaultConfig()
        sys.exit(1)

    # Get options from command line and run appropriate action
    if len(sys.argv) < 2:
        PrintHelp()

    # Read in config file
    with open(configFile, 'r') as file:
        config = json.load(file)['buildConfig']
        options = config['options']

    # Get our current path in a form that is okay for passing to Docker
    currentPath = subprocess.run('pwd', stdout=subprocess.PIPE,
                                 encoding='UTF-8').stdout
    currentPath = str.strip(currentPath)
    containerWorkingDirectory = '/proj'

    # Get user command
    val = sys.argv[1].lower()

    # Do what the user told us to do
    if val == 'builddockerimage':
        BuildDockerMachine(options)
    elif val == 'interactive':
        subprocess.run(['docker', 'run', '--rm', '-it', '--privileged', '--workdir', f'{containerWorkingDirectory}', f'-v/dev/bus/usb:/dev/bus/usb',
                f'-v{currentPath}:{containerWorkingDirectory}', f'{options["imageName"]}', '/bin/bash'])
    elif val == 'fullclean':
        subprocess.run(['docker', 'run', '--rm', '--workdir', f'{containerWorkingDirectory}', f'-v{currentPath}:{containerWorkingDirectory}',
                        f'{options["imageName"]}', 'make', 'clean'])
    elif val == 'configure':
        subprocess.run(['docker', 'run', '--rm', '-it', '--workdir', f'{containerWorkingDirectory}', f'-v{currentPath}:{containerWorkingDirectory}',
                        f'{options["imageName"]}', 'make', 'menuconfig'])
    elif val == 'build':
        subprocess.run(['docker', 'run', '--rm', '--workdir', f'{containerWorkingDirectory}', f'-v{currentPath}:{containerWorkingDirectory}',
                        f'{options["imageName"]}', 'make', '-j4', 'all'])
    elif val == 'monitor':
        subprocess.run(['docker', 'run', '--rm', '--workdir', f'{containerWorkingDirectory}', f'-v{currentPath}:{containerWorkingDirectory}',
                        f'{options["imageName"]}', 'make', 'monitor'])
    elif val == 'flash':
        subprocess.run(['docker', 'run', '--rm', '--workdir', f'{containerWorkingDirectory}', f'-v{currentPath}:{containerWorkingDirectory}',
                        f'{options["imageName"]}', 'make', 'flash'])
    else:
        PrintHelp()
    sys.exit(0)


if __name__ == "__main__":
    main()