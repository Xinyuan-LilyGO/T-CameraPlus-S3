# SPDX-FileCopyrightText: Copyright (c) 2025 lbuque
#
# SPDX-License-Identifier: MIT

import os
import sys
import time
from os.path import join

Import("env")

try:
    import esptool
except:
    try:
        sys.path.append(join(env['UPLOADER'], '..'))
        import esptool
    except:
        env.Execute("$PYTHONEXE -m pip install esptool")
        import esptool

verbose = False

def merge_bin_files(env):
    upload_cmd = env['UPLOADERFLAGS']

    chip_type = env['BOARD_MCU']
    board_config = env.BoardConfig()
    flash_size = board_config.get("upload.flash_size", "4MB")
    flash_mode = env['BOARD_FLASH_MODE']

    OUTPUT_DIR = join(env['PROJECT_BUILD_DIR'], '..', 'bin')
    output_dir = env.GetProjectOption('merge_bin_output_dir', default=OUTPUT_DIR)
    output_file = env.GetProjectOption('merge_bin_output_file', default="{0}_{1}_{2}.bin".format(
        os.path.basename(env['PROJECT_DIR']),
        env['PIOENV'],
        time.strftime("%Y%m%d_%H%M%S", time.localtime())
    ))

    if not os.path.exists(output_dir):
        os.mkdir(output_dir)

    outputFilename = join(output_dir, output_file)

    version_tuple = tuple(map(int, esptool.__version__.split('.')[:2]))

    commands = []
    commands.append('--chip')
    commands.append(chip_type)

    if version_tuple >= (5, 0):
        commands.append('merge-bin')
    else:
        commands.append('merge_bin')

    commands.append('-o')
    commands.append(outputFilename)

    if version_tuple >= (5, 0):
        commands.append('--flash-size')
    else:
        commands.append('--flash_size')
    commands.append(flash_size)

    for item in env['FLASH_EXTRA_IMAGES']:
        commands.append(item[0])
        commands.append(upload_cmd[upload_cmd.index(item[0]) + 1])

    commands.append(env['ESP32_APP_OFFSET'])
    commands.append(join(env['PROJECT_BUILD_DIR'], env['PIOENV'], '{}.bin'.format(env['PROGNAME'])))

    esptool.main(commands)

def after_buildprog(source, target, env):
    merge_bin_files(env)

env.AddPostAction("buildprog", after_buildprog)
