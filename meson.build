project(
  'vault',
  'c',
  version: '1.1.0',
  license: 'MIT',
  default_options: [
    'default_library=static',
    'c_std=c99',
    'warning_level=3',
  ],
)

buildtype = 'release'

install_headers('include/vault.h')
inc = include_directories('include')

vault_sources = [
  'source/platforms/vault_linux.c',
  'source/platforms/vault_windows.c',
  'source/vault.c',
]

vault_lib = library(
  'vault',
  vault_sources,
  include_directories: inc,
  install: true,
)

vault_dep = declare_dependency(
  include_directories: inc, 
  link_with: vault_lib,
)

pkg = import('pkgconfig')
pkg.generate(vault_lib)
