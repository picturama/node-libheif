let libheif

if (process.env.DEBUG) {
    libheif = require('./build/Debug/node_libheif.node')
} else {
    libheif = require('./build/Release/node_libheif.node')
}

module.exports = libheif
