project(
  'typedraw',
  'c',
  meson_version : '>= 1.3.0',
  version : '2025.09.25-MVP',
  default_options : ['warning_level=3'],
)

dependencies = [
]

src =['launch.c']

exe = executable(
  'typedraw',
  src,
  dependencies : dependencies,
  install : true,
)

test('basic', exe)
