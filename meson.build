project('trtr', 'cpp')

sfml_system_dep = dependency('sfml-system')
sfml_window_dep = dependency('sfml-window')
sfml_graphics_dep = dependency('sfml-graphics')

source_files = ['src/main.cpp',
'src/window.cpp', 'src/board.cpp', 'src/piece.cpp',
'src/game_loop.cpp', 'src/random_generator.cpp',
'src/block.cpp', 'src/piece_preview.cpp']

executable('trtr', source_files,
  dependencies : [sfml_system_dep, sfml_window_dep, sfml_graphics_dep],
  cpp_args : '-std=c++17')
