# type: ignore
Import("env")

# Генерация .hex файла после сборки
# type: ignore
env.AddPostAction(
    "$BUILD_DIR/${PROGNAME}.elf",
    env.VerboseAction(
        " ".join([
            "$OBJCOPY", "-O", "ihex",
            "$BUILD_DIR/${PROGNAME}.elf", "$BUILD_DIR/${PROGNAME}.hex"
        ]),
        "Generating HEX file"
    )
)