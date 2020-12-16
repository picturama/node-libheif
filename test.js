const libheif = require('./node-libheif')

const startTime = Date.now()
libheif.decodeHeifFile('../test-data/photos/heic/Apple_iPhone_XR_portrait.HEIC')
    .then(image => {
        console.log(`decodeHeifFile took ${Date.now() - startTime} ms - image`, image)
    })
    .catch(error => {
        console.error(`Calling decodeHeifFile failed after ${Date.now() - startTime} ms`, error)
    })

console.log(`After calling decodeHeifFile (${Date.now() - startTime} ms)`)
