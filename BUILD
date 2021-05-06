package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "run-for-your-life",
    data = ["//content"],
    linkopts = [
        "-lSDL2",
        "-lSDL2_image",
        "-lSDL2_mixer",
        "-lnoise",
    ],
    srcs = ["main.cc"],
    deps = [
        ":game",
        ":screens",
    ],
)

# Basic framework objects

cc_library(
    name = "audio",
    srcs = ["audio.cc"],
    hdrs = ["audio.h"],
)

cc_library(
    name = "graphics",
    srcs = ["graphics.cc"],
    hdrs = ["graphics.h"],
)

cc_library(
    name = "input",
    srcs = ["input.cc"],
    hdrs = ["input.h"],
)

cc_library(
    name = "screen",
    srcs = ["screen.cc"],
    hdrs = ["screen.h"],
    deps = [
        ":audio",
        ":graphics",
        ":input",
    ]
)

cc_library(
    name = "game",
    srcs = ["game.cc"],
    hdrs = ["game.h"],
    deps = [
        ":audio",
        ":graphics",
        ":input",
        ":screen",
        ":screens",
        ":text",
    ],
)

# Graphical objects

cc_library(
    name = "animated_sprite",
    srcs = ["animated_sprite.cc"],
    hdrs = ["animated_sprite.h"],
    deps = [":sprite"],
)

cc_library(
    name = "backdrop",
    srcs = ["backdrop.cc"],
    hdrs = ["backdrop.h"],
    deps = [":graphics"],
)

cc_library(
    name = "box",
    srcs = ["box.cc"],
    hdrs = ["box.h"],
    deps = [":graphics"],
)

cc_library(
    name = "floating_text",
    srcs = ["floating_text.cc"],
    hdrs = ["floating_text.h"],
    deps = [
        ":text",
        ":objects",
    ],
)

cc_library(
    name = "sprite",
    srcs = ["sprite.cc"],
    hdrs = ["sprite.h"],
    deps = [":graphics"],
)

cc_library(
    name = "text",
    srcs = ["text.cc"],
    hdrs = ["text.h"],
    deps = [":graphics"],
)

cc_library(
    name = "screens",
    srcs = [
      "game_over_screen.cc",
      "game_screen.cc",
      "title_screen.cc",
    ],
    hdrs = [
      "game_over_screen.h",
      "game_screen.h",
      "title_screen.h",
    ],
    deps = [
        ":audio",
        ":backdrop",
        ":floating_text",
        ":map",
        ":objects",
        ":screen",
        ":text",
    ],
)

cc_library(
    name = "map",
    srcs = ["map.cc"],
    hdrs = [
        "map.h",
        "stb_perlin.h",
    ],
    deps = [
        ":graphics",
    ],
)

cc_library(
    name = "objects",
    srcs = [
        "fish.cc",
        "object.cc",
        "rock.cc",
        "seal.cc",
    ],
    hdrs = [
        "fish.h",
        "object.h",
        "rock.h",
        "seal.h",
    ],
    deps = [
        ":audio",
        ":graphics",
        ":map",
        ":player",
    ],
)

cc_library(
    name = "player",
    srcs = ["player.cc"],
    hdrs = ["player.h"],
    deps = [
        ":animated_sprite",
        ":audio",
        ":map",
        ":sprite",
    ],
)
