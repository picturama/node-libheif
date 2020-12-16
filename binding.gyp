{
  'targets': [{
    'target_name': 'node_libheif',
    'defines': [
      'HAVE_POSIX_MEMALIGN',
      'HAVE_LIBDE265',
    ],
    'include_dirs' : [
      'src/',
      'submodules/libheif/',
      'submodules/libde265/',
      '<!@(node -p "require(\'node-addon-api\').include")'
    ],
    'dependencies': [
      '<!(node -p "require(\'node-addon-api\').gyp")'
    ],
    'sources': [
      # See `libde265_sources` in `submodules/libde265/libde265/CMakeLists.txt`
      'submodules/libde265/libde265/alloc_pool.cc',
      'submodules/libde265/libde265/bitstream.cc',
      'submodules/libde265/libde265/cabac.cc',
      'submodules/libde265/libde265/configparam.cc',
      'submodules/libde265/libde265/contextmodel.cc',
      'submodules/libde265/libde265/de265.cc',
      'submodules/libde265/libde265/deblock.cc',
      'submodules/libde265/libde265/decctx.cc',
      'submodules/libde265/libde265/dpb.cc',
      'submodules/libde265/libde265/en265.cc',
      'submodules/libde265/libde265/fallback-dct.cc',
      'submodules/libde265/libde265/fallback-motion.cc',
      'submodules/libde265/libde265/fallback.cc',
      'submodules/libde265/libde265/image-io.cc',
      'submodules/libde265/libde265/image.cc',
      'submodules/libde265/libde265/intrapred.cc',
      'submodules/libde265/libde265/md5.cc',
      'submodules/libde265/libde265/motion.cc',
      'submodules/libde265/libde265/nal-parser.cc',
      'submodules/libde265/libde265/nal.cc',
      'submodules/libde265/libde265/pps.cc',
      'submodules/libde265/libde265/quality.cc',
      'submodules/libde265/libde265/refpic.cc',
      'submodules/libde265/libde265/sao.cc',
      'submodules/libde265/libde265/scan.cc',
      'submodules/libde265/libde265/sei.cc',
      'submodules/libde265/libde265/slice.cc',
      'submodules/libde265/libde265/sps.cc',
      'submodules/libde265/libde265/threads.cc',
      'submodules/libde265/libde265/transform.cc',
      'submodules/libde265/libde265/util.cc',
      'submodules/libde265/libde265/visualize.cc',
      'submodules/libde265/libde265/vps.cc',
      'submodules/libde265/libde265/vui.cc',

      # See `libheif_la_SOURCES` in `submodules/libheif/libheif/Makefile.am`
      'submodules/libheif/libheif/bitstream.cc',
      'submodules/libheif/libheif/box.cc',
      'submodules/libheif/libheif/error.cc',
      'submodules/libheif/libheif/heif_file.cc',
      'submodules/libheif/libheif/heif_image.cc',
      'submodules/libheif/libheif/heif.cc',
      'submodules/libheif/libheif/heif_context.cc',
      'submodules/libheif/libheif/heif_hevc.cc',
      'submodules/libheif/libheif/heif_avif.cc',
      'submodules/libheif/libheif/heif_plugin_registry.cc',
      'submodules/libheif/libheif/heif_plugin.cc',
      'submodules/libheif/libheif/heif_colorconversion.cc',
      'submodules/libheif/libheif/nclx.cc',

      #'submodules/libheif/libheif/heif_decoder_aom.cc',
      #'submodules/libheif/libheif/heif_decoder_dav1d.cc',
      'submodules/libheif/libheif/heif_decoder_libde265.cc',

      # Our main file
      'src/DecodeHeifFileWorker.cc',
      'src/node_libheif.cc'
    ],
    'cflags!' : [ '-fno-exceptions' ],
    'cflags_cc!': [ '-fno-rtti', '-fno-exceptions' ],
    'xcode_settings': {
      'GCC_ENABLE_CPP_RTTI': 'YES',
      'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
    }
  }]
}
