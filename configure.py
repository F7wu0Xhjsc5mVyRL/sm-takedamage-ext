import sys
from ambuild2 import run

builder = run.PrepareBuild(sourcePath=sys.path[0])
builder.default_build_folder = 'build'
builder.options.add_option('--hl2sdk-root', type=str, dest='hl2sdk_root', default='../deps',
                           help='Root search folder for HL2SDKs')
builder.options.add_option('--sm-path', type=str, dest='sm_path', default='../deps/sourcemod',
                           help='Path to SourceMod')
builder.options.add_option('--enable-debug', action='store_const', const='1', dest='debug',
                           help='Enable debugging symbols')
builder.options.add_option('--enable-optimize', action='store_const', const='1', dest='opt',
                           help='Enable optimization')
builder.options.add_option('-s', '--sdks', default='episode1', dest='sdks',
                           help='Build against specified SDKs; valid args are "all", "present", or '
                                'comma-delimited list of engine names (default: %default)')

builder.Configure()
