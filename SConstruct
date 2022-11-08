def PhonyTargets(
    target,
    action,
    depends,
    env=None,
):
    # Creates a Phony target
    if not env:
        env = DefaultEnvironment()
    t = env.Alias(target, depends, action)
    env.AlwaysBuild(t)


PROJECT = "coffe-probe"
ELF = "{}.elf".format(PROJECT)
HEX = "{}.hex".format(PROJECT)

MCU = "attiny202"
FREQUENCY = str(2000000)

DEVICE_PACK_OPTS = [
    "-mmcu={}".format(MCU), "-B", "./device_pack/gcc/dev/attiny202/", "-I", "./device_pack/include/"]

env_options = {
    "CC": "avr-gcc",
    "CPPDEFINES": ["F_CPU={}".format(FREQUENCY)],
    "CFLAGS": ["-std=c99", "-Wall", "-g", "-Os"] + DEVICE_PACK_OPTS,
    "LINKFLAGS": ["-Wl,-T,avrxmega3.xn"] + DEVICE_PACK_OPTS
}

env = DefaultEnvironment(**env_options)
try:
    env.Tool("compilation_db")
except Exception:
    print("SCons version doesn't support compilation_db")

sources = Glob("main/*.c")
sources += Glob("main/peripherals/*.c")

binary = env.Program(ELF, sources)
hexfile = env.Command(
    HEX, ELF, "avr-objcopy -j .text -j .data -O ihex {} {} ".format(ELF, HEX))

try:
    compileDB = env.CompilationDatabase("compile_commands.json")
    env.Depends(binary, compileDB)
except AttributeError:
    pass

PhonyTargets(
    "size",  "avr-size --mcu={} --format=avr {}".format(MCU, ELF), binary, env)
PhonyTargets(
    "flash", f"./.env/bin/pymcuprog write -f {HEX} -d {MCU} -t uart -u /dev/ttyUSB0", hexfile, env)
