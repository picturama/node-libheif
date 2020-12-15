const libheif = require('./node-libheif')

const startTime = Date.now()
const image = libheif.loadHeifFile('../test-data/photos/heic/Apple_iPhone_XR_portrait.HEIC')
console.log('loadHeifFile took ' + (Date.now() - startTime) + ' ms - image', image)
